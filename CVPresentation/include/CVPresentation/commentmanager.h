// -*- C++ -*-
/*!
 * @file  commentmanager.h
 * @brief Comment and CommentManager class
 * @date  $Date$
 *
 * @author ç≤ÅXñÿãB (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#ifndef COMMENT_MANAGER_H
#define COMMENT_MANAGER_H

#include <list>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


/*!
 * @class Comment
 * @brief Comment class
 */
class Comment{
	//Parameters of characters in comment
	int font; //font
	double scale; //size
	cv::Scalar color; //color
	int thick; //thickness

	//Text size information
	cv::Size size;
	int baseline;

	//Text
	std::string str;

	//Current position
	cv::Point pos;

public:
	Comment(std::string &st, int txtfont = cv::FONT_HERSHEY_COMPLEX, double txtscale = 1.0, cv::Scalar txtcolor=cv::Scalar(0,0,255), int txtthick = 2, cv::Point initpos=cv::Size(-1,-1));

	/*!
	 * @brief Get comment height and width
	 * @return Size of comment
	 */
	cv::Size getSize(){return size;}
	/*!
	 * @brief Get comment position
	 * @return Position of comment
	 */
	cv::Point getPosition(){return pos;}

	//Functions to change text position
	/*!
	 * @brief Change comment position
	 */
	void changePositionRelative(cv::Point pt){pos += pt;}
	/*!
	 * @brief Change comment position
	 */
	void changePositionRelative(int dx, int dy){
		pos.x += dx;
		pos.y += dy;
	}
	/*!
	 * @brief Change comment position
	 */
	void changePositionRelativeX(int dx){pos.x += dx;}
	/*!
	 * @brief Change comment position
	 */
	void changePositionRelativeY(int dy){pos.y += dy;}

	/*!
	 * @brief Change comment position
	 */
	void changePositionAbsolute(cv::Point pt){pos = pt;}
	/*!
	 * @brief Change comment position
	 */
	void changePositionAbsolute(int x, int y){
		pos.x = x;
		pos.y = y;
	}
	/*!
	 * @brief Change comment position
	 */
	void changePositionAbsoluteX(int x){pos.x = x;}
	/*!
	 * @brief Change comment position
	 */
	void changePositionAbsoluteY(int y){pos.y = y;}

	/*!
	 * @brief Check if comment display is finished
	 * @return true if finished
	 */
	bool checkFinish(){
		if(pos.x + size.width <=0){
			return true;
		}
		return false;
	}

	/*!
	 * @brief Put comment to image
	 * @param img Image to put comment
	 */
	void putComment(cv::Mat &img){
		cv::putText(img, str, pos, font, scale, color, thick, CV_AA, false);
	}
};

/*!
 * @class CommentManager
 * @brief Class for comment management
 */
class CommentManager{
	cv::Mat *pimg;

	std::list<Comment> CmtList;
	int basespeed;

	int findSpace(Comment &cmt);
public:
	CommentManager(cv::Mat *p=NULL, int bspeed=2);
	int initialize(cv::Mat *p=NULL, int bspeed=2);
	int setSpeed(int bspeed);
	/*!
	 * @brief Set image where comments are put
	 * @return p pointer to the image
	 */
	void setImage(cv::Mat *p){pimg = p;}

	int addComment(Comment &cmt);
	int updateComment();

	/*!
	 * @brief Check if comment is stored in the list
	 * @return true if comment list is empty
	 */
	bool empty(){return CmtList.empty();}
};

#endif
