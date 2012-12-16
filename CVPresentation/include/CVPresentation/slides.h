// -*- C++ -*-
/*!
 * @file  slides.h
 * @brief Slides class
 * @date  $Date$
 *
 * @author ç≤ÅXñÿãB (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#ifndef SLIDES_H
#define SLIDES_H

#include <string>
#include <opencv2/core/core.hpp>

/*!
 * @class Slides
 * @brief Slide class
 */
class Slides{
	std::string slide_name; //slide name - set "test***.jpg" if slide name is, for example, "test001.jpg", "test002.jpg", ...,
	                        //             set "test*.jpg" if slide name is, for example, "test1.jpg", "test2.jpg", ..., "test10.jpg", ...
	unsigned int ind_init; //initial slide number - set 1 if the first slide is, for example, "test001.jpg"
	unsigned int ind; //index of the current slide

	cv::Size slide_size; //slide size - if silde_size = (0,0), the slide size will be the same as the original image size
	                     //           - if silde_size = (x,0) or (0,y) (x>0, y>0), the original image will be magnified by x/original_width or y/original_height times and the aspect ratio is kept
public:
	cv::Mat slide_img;

	/*!
	 * @brief Constructor
	 */
	Slides(){;}
	Slides(const char* name, int initial_index=0, cv::Size size=cv::Size(0,0)); //constructor with initialization

	int initialize(const char* name, int initial_index=0, cv::Size size=cv::Size(0,0)); //set parameters
	int setSize(cv::Size size);

	int setAbsolute(unsigned int index); //set specified slide image to slide_img
	/*!
	 * @brief Set slide image based on the slide number
	 * @param index Slide number
	 * @return 0 if no error
	 */
	int setRelative(int index){ //set specified slide image to slide_img
		if(index<0&&ind<ind_init-index){return setAbsolute(ind_init);}
		return setAbsolute(ind+index);
	}
	/*!
	 * @brief Set next slide
	 * @return 0 if no error
	 */
	int setNext(){return setAbsolute(ind+1);}
	/*!
	 * @brief Set previous slide
	 * @return 0 if no error
	 */
	int setPrevious(){
		if(ind<ind_init+1){return 0;} //no need to change slide
		return setAbsolute(ind-1);
	}
	/*!
	 * @brief Reload current slide
	 * @return 0 if no error
	 */
	int reload(){return setAbsolute(ind);} //reload current slide

	/*!
	 * @brief Check if slide is set
	 * @return true if slide image is not set
	 */
	bool empty(){return slide_img.empty();} //whether slide is set or not
	/*!
	 * @brief Get current slide number
	 * @return current slide number
	 */
	unsigned int getSlideNumber(){return ind;}
};

#endif
