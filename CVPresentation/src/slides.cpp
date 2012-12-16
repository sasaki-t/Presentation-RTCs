// -*- C++ -*-
/*!
 * @file  slides.cpp
 * @brief Slides class
 * @date  $Date$
 *
 * @author ç≤ÅXñÿãB (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "slides.h"

//--- Member functions for slide class ---
/*!
 * @brief Constructor
 * @param name Slide filename
 * @param initial_index Initial slide number
 * @param size Slide image size
 */
Slides::Slides(const char* name, int initial_index, cv::Size size){
	initialize(name, initial_index,size);
}

/*!
 * @brief Initialization
 * @param name Slide filename
 * @param initial_index Initial slide number
 * @param size Slide image size
 * @return 0 if no error
 */
int Slides::initialize(const char* name, int initial_index, cv::Size size){
	int res;

	slide_name = name;
	ind_init = initial_index;
	ind = ind_init;

	res = setSize(size);
	if(res<0){
		return res;
	}

	res = setAbsolute(ind);
	if(res<0){
		std::cerr << "Cannot find initial slide" << std::endl;
		return res;
	}

	return res;
}

/*!
 * @brief Set slide image size
 * @param size Slide image size
 * @return 0 if no error
 */
int Slides::setSize(cv::Size size){
	if((size.width<0)||(size.height<0)){
		std::cerr << "Invalid image size" << std::endl;
		return -1;
	}

	slide_size = size;
	return 0;
}

/*!
 * @brief Set slide image based on the slide number
 * @param index Slide number
 * @return 0 if no error
 */
int Slides::setAbsolute(unsigned int index){
	unsigned int new_index = index;
	cv::Mat new_img;
	std::ostringstream oss;
	std::string st = slide_name;
	std::string::size_type loc = st.find("*"); //index of "*"
	int ndigits; //# of digits
	int interpolation = cv::INTER_LINEAR;

	//--- Create slide name ---
	while(loc!=std::string::npos){
		//calculate how many # of digits are necessary
		ndigits = 1;
		while(loc+ndigits<st.size()){
			if(st[loc+ndigits]!='*'){
				break;
			}
			ndigits++;
		}

		//replace characters from "*" to "index"
		oss.str(""); //clear stream string
		oss.clear(std::stringstream::goodbit); //reset flag
		oss << std::setw(ndigits) << std::setfill('0') << index; //create index with at least ndigits width
		st.replace(loc, ndigits, oss.str());

		loc = st.find("*", loc+ndigits); //search new "*"
	}
	//--- End create slide name ---

	std::cout << "try to open: " << st << std::endl;
	new_img = cv::imread(st);
	if(new_img.empty()){
		return -1; //no error message shown because this may mean that the presentor reaches the final slide.
	}
	std::cout << " ...success" << std::endl;

	//--- Update slide image using specified size ---
	if(slide_size.width==0){
		if(slide_size.height==0){ //slide_size == (0,0)
			slide_img = new_img;
		}else{ //slide_size.width==0 && slide_size.height>0
			cv::resize(new_img, slide_img, cv::Size(0,0), (double)slide_size.height/new_img.rows, (double)slide_size.height/new_img.rows, interpolation);
		}
	}else if(slide_size.height==0){ //slide_size.height==0 && slide_size.width>0
		cv::resize(new_img, slide_img, cv::Size(0,0), (double)slide_size.width/new_img.cols, (double)slide_size.width/new_img.cols, interpolation);
	}else{ //slide_size.height>0 && slide_size.width>0
		cv::resize(new_img, slide_img, slide_size, 0, 0, interpolation);
	}
	//--- End update slide image using specified size ---

	ind = new_index; //update slide number

	return 0;
}

