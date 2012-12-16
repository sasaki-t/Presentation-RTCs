// -*- C++ -*-
/*!
 * @file  lp_detectir.h
 * @brief Laser pointer light detection class
 * @date $Date$
 *
 * @author ç≤ÅXñÿãB (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#ifndef LP_DETECTOR_H
#define LP_DETECTOR_H

#include <opencv2/core/core.hpp>

/*!
 * @class LPDetector
 * @brief Detect laser pointer light based on background subtraction
 */
class LPDetector{
	cv::Mat bg; //background image

	//threshold for detection of laser lights
	int th_lum_diff; //difference of luminance

	//threshold for update background (if th_bg_update<0, no update done)
	int th_bg_update;

public:
	LPDetector(int luminance_diff=0, int background_update=-1);
	LPDetector(cv::Mat &back_img, int luminance_diff=0, int background_update=-1);

	int initialize(int luminance_diff=0, int background_update=-1); //initialize
	int initialize(cv::Mat &back_img, int luminance_diff=0, int background_update=-1); //initialize with background information

	void setThreshold(int luminance_diff, int background_update=-1);
	void setBackgroundImage(cv::Mat &back_img);

	/*!
	 * @brief Check if background is set
	 * @return true if no background is set
	 */
	bool backgroundEmpty(){return bg.empty();}

	int detect(cv::Mat &frame, cv::Point &pt_detected, cv::Point th_ipos_min=cv::Point(0,0), cv::Point th_ipos_max=cv::Point(-1,-1)); //detect laser point within the specified image coordinates
	int detect(cv::Mat &frame, cv::Point &pt_detected, cv::Point th_min_wpos, cv::Point th_max_wpos, double zw, double Intrinsic[3][3], double Extrinsic[3][4]); //detect laser point within the specified world coordinates

	cv::Point img_to_worldZ(cv::Point ptImg, double zw, double Intrinsic[3][3], double Extrinsic[3][4]); //3D reconstruction
};

#endif
