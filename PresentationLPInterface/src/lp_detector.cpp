// -*- C++ -*-
/*!
 * @file  lp_detectir.cpp
 * @brief Laser pointer light detection class
 * @date $Date$
 *
 * @author ç≤ÅXñÿãB (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "lp_detector.h"

/*!
 * @brief Constructor
 * @param luminance_diff Threshold for background subtraction
 * @param background_update Threshold for background update
 */
LPDetector::LPDetector(int luminance_diff, int background_update){
	initialize(luminance_diff, background_update);
}

/*!
 * @brief Constructor with background information
 * @param back_img Background image
 * @param luminance_diff Threshold for background subtraction
 * @param background_update Threshold for background update
 */
LPDetector::LPDetector(cv::Mat &back_img, int luminance_diff, int background_update){
	initialize(back_img, luminance_diff, background_update);
}

/*!
 * @brief Initialization
 * @param luminance_diff Threshold for background subtraction
 * @param background_update Threshold for background update
 * @return 0 if no error
 */
int LPDetector::initialize(int luminance_diff, int background_update){
	setThreshold(luminance_diff, background_update);
	bg.release();
	return 0;
}

/*!
 * @brief Initialization with background information
 * @param back_img Background image
 * @param luminance_diff Threshold for background subtraction
 * @param background_update Threshold for background update
 * @return 0 if no error
 */
int LPDetector::initialize(cv::Mat &back_img, int luminance_diff, int background_update){
	setThreshold(luminance_diff, background_update);
	setBackgroundImage(back_img);
	return 0;
}

/*!
 * @brief Set threshold for background subtraction
 * @param luminance_diff Threshold for background subtraction
 * @param background_update Threshold for background update
 */
void LPDetector::setThreshold(int luminance_diff, int background_update){
	th_lum_diff = luminance_diff;
	th_bg_update = background_update;
	return;
}

/*!
 * @brief Set background image (or release background image if the argument is empty image)
 * @param back_img Background image
 */
void LPDetector::setBackgroundImage(cv::Mat &back_img){
	if(!back_img.empty()){
		if(back_img.channels() == 1){ //gray scale image
			bg = back_img;
		}else{ //bgr image -> convert to gray scale image
			cv::cvtColor(back_img,bg,CV_BGR2GRAY);
		}
	}else{
		bg.release();
	}
	return;
}

/*!
 * @brief Detect laser point from the input image within the specified image coordinates
 * @param frame Input image
 * @param pt_detected Detected point
 * @param th_ipos_min Search area: coordinate of the top-left corner in the input image
 * @param th_ipos_max Search area: coordinate of the bottom-right corner in the input image
 * @return >0 if detected, 0 if not detected
 */
int LPDetector::detect(cv::Mat &frame, cv::Point &pt_detected, cv::Point th_ipos_min, cv::Point th_ipos_max){
	int x, y;
	int detect_count = 0;
	int max_lum_diff = -1; //max luminance

	cv::Mat frame_gray;
	if(frame.channels() == 1){ //gray image
		frame_gray = frame;
	}else{
		cv::cvtColor(frame,frame_gray,CV_BGR2GRAY);
	}

	if((th_ipos_min.x<0)||(th_ipos_min.x>frame.cols)){th_ipos_min.x=0;}
	if((th_ipos_min.y<0)||(th_ipos_min.y>frame.rows)){th_ipos_min.y=0;}
	if((th_ipos_max.x<0)||(th_ipos_max.x>frame.cols)){th_ipos_max.x=frame.cols;}
	if((th_ipos_max.y<0)||(th_ipos_max.y>frame.rows)){th_ipos_max.y=frame.rows;}

	for(y=th_ipos_min.y;y<th_ipos_max.y;y++){ //for each line
		unsigned char *pbg = bg.ptr<unsigned char>(y);
		unsigned char *pfg = frame_gray.ptr<unsigned char>(y);
		for(x=th_ipos_min.x;x<th_ipos_max.x;x++){ //for each BGR element
			if((*pfg)-(*pbg)>=th_lum_diff){ //difference of luminance is higherer than thresold (i.e. brighter)
				detect_count++; //increment counter
				if(*(pfg)-(*pbg)>max_lum_diff){
					max_lum_diff = *(pfg)-(*pbg);
					pt_detected.x = x;
					pt_detected.y = y;
				}
			}
			pbg += bg.channels();
			pfg += frame_gray.channels();
		}
	}

	//background update if necessary
	if(th_bg_update >= 0 && detect_count>=th_bg_update){ //th_bg_update>=0 AND # of detected points are more than th_bg_update, update background
		setBackgroundImage(frame_gray);
		//return 0;
	}

	//return detected or not
	if(detect_count > 0){ //detected
		return 1;
	}else{ //not detected
		return 0;
	}
}

/*!
 * @brief Detect laser point within the specified world coordinates
 * @param frame Input image
 * @param pt_detected Detected point
 * @param th_wpos_min Search area: coordinate of the top-left corner
 * @param th_wpos_max Search area: coordinate of the bottom-right corner
 * @param zw Z-coordinate of screen in world coordinate system
 * @param Intrinsic Intrinsic camera parameters in matrix form
 * @param Extrinsic Extrinsic camera parameters in matrix form
 * @return >0 if detected, 0 if not detected
 */
int LPDetector::detect(cv::Mat &frame, cv::Point &pt_detected, cv::Point th_wpos_min, cv::Point th_wpos_max, double zw, double Intrinsic[3][3], double Extrinsic[3][4]){
	int x, y;
	int detect_count = 0;
	int max_lum_diff = -1; //max luminance

	cv::Point pt_candidate_w;

	cv::Mat frame_gray;
	if(frame.channels() == 1){ //gray image
		frame_gray = frame;
	}else{
		cv::cvtColor(frame,frame_gray,CV_BGR2GRAY);
	}

	for(y=0;y<frame.rows;y++){ //for each line
		unsigned char *pbg = bg.ptr<unsigned char>(y);
		unsigned char *pfg = frame_gray.ptr<unsigned char>(y);
		for(x=0;x<frame.cols;x++){ //for each BGR element
			if((*pfg)-(*pbg)>=th_lum_diff){ //difference of luminance is higherer than thresold (i.e. brighter)
				pt_candidate_w = img_to_worldZ(cv::Point(x,y),zw,Intrinsic,Extrinsic);
				if((pt_candidate_w.x>=th_wpos_min.x)&&(pt_candidate_w.x<=th_wpos_max.x)&&(pt_candidate_w.y>=th_wpos_min.y)&&(pt_candidate_w.y<=th_wpos_max.y)){
					detect_count++; //increment counter
					if((*pfg)-(*pbg)>max_lum_diff){
						max_lum_diff = (*pfg)-(*pbg);
						pt_detected.x = pt_candidate_w.x;
						pt_detected.y = pt_candidate_w.y;
					}
				}
			}
			pbg += bg.channels();
			pfg += frame_gray.channels();
		}
	}

	//background update if necessary
	if(th_bg_update >= 0 && detect_count>=th_bg_update){ //th_bg_update>=0 AND # of detected points are more than th_bg_update, update background
		setBackgroundImage(frame_gray);
		//return 0;
	}

	//return detected or not
	if(detect_count > 0){ //detected
		return 1;
	}else{ //not detected
		return 0;
	}
}

/*!
 * @brief Calculate 3D position of an image point based on camera parameters and z-coordinate of the point in world coordinate system
 * @param ptImg Point on the image
 * @param zw z-coordinate of ptImg in world coordinate system
 * @param Intrinsic Intrinsic camera parameters in matrix form
 * @param Extrinsic Extrinsic camera parameters in matrix form
 * @return x and y coordinates of the ptImg in world coordinate system or (0,0) if error
 */
cv::Point LPDetector::img_to_worldZ(cv::Point ptImg, double zw, double Intrinsic[3][3], double Extrinsic[3][4]){
	cv::Point ptWorldXY;
	double P[3][4];
	int i,j,k;
	double a,b,c,d,m,n;
	double det;
	/*
	for(int x=0;x<3;x++){
		for(int y=0;y<3;y++){
			std::cerr << Intrinsic[x][y] << ' ';
		}
		std::cerr << std::endl;
	}
	for(int x=0;x<3;x++){
		for(int y=0;y<4;y++){
			std::cerr << Extrinsic[x][y] << ' ';
		}
		std::cerr << std::endl;
	}
	*/

	//Calculate P = A*[R|T]
	for(i=0;i<3;i++){
		for(j=0;j<4;j++){
			P[i][j] = 0;
			for(k=0;k<3;k++){
				P[i][j] += Intrinsic[i][k]*Extrinsic[k][j];
			}
		}
	}

	//From s*(u, v, 1)^T = P*(xw, yw, zw, 1)^T,
	//we get
	//(P[2][0]xw + P[2][1]yw + P[2][2]zw + P[2][3])*u = P[0][0]xw + P[0][1]yw + P[0][2]zw + P[0][3]
	//(P[2][0]xw + P[2][1]yw + P[2][2]zw + P[2][3])*v = P[1][0]xw + P[1][1]yw + P[1][2]zw + P[1][3]
	//These can be written as
	//a*xw + b*yw = m
	//c*xw + d*yw = n
	a = P[0][0]-ptImg.x*P[2][0];
	b = P[0][1]-ptImg.x*P[2][1];
	c = P[1][0]-ptImg.y*P[2][0];
	d = P[1][1]-ptImg.y*P[2][1];
	m = -(P[0][2]-ptImg.x*P[2][2])*zw - (P[0][3]-ptImg.x*P[2][3]);
	n = -(P[1][2]-ptImg.y*P[2][2])*zw - (P[1][3]-ptImg.y*P[2][3]);

	det = a*d-b*c;
	if(det == 0){
		std::cerr << "Error in LPDetector::img_to_worldZ(): no solution" << std::endl;
		ptWorldXY.x = 0;
		ptWorldXY.y = 0;
	}else{
		ptWorldXY.x = (d*m-b*n)/(a*d-b*c);
		ptWorldXY.y = (-c*m+a*n)/(a*d-b*c);
	}

	return ptWorldXY;
}

