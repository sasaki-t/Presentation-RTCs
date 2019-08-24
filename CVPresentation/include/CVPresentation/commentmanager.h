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
#include <opencv2/imgproc/imgproc.hpp>


enum cpkeytype{
	FONT, 
	SCALE_ABS, 
	SCALE_REL, 
	SCALE_RATIO,
	SCALE_ABS_WITH_THICKNESS, 
	SCALE_REL_WITH_THICKNESS, 
	SCALE_AND_THICKNESS_RATIO,
	COLOR, 
	THICKNESS_ABS,
	THICKNESS_REL,
	THICKNESS_RATIO,
	THICKNESS_ABS_WITH_SCALE,
	THICKNESS_REL_WITH_SCALE,
};

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

/*!
 * @class CommentParamKey
 * @brief CommentParamKey class
 */
class CommentParamKey{
public:
	std::string name;
	enum cpkeytype type;

	std::vector<double> val;

	/*!
	 * @brief Constructor
	 */
	CommentParamKey(){;}
	/*!
	 * @brief Constructor
	 * @param n Command name
	 * @param kt Command type
	 * @param ret_val Return value when the command is called
	 */
	CommentParamKey(const char* n, cpkeytype kt, std::vector<double> ret_val){
		initialize(n, kt, ret_val);
	}

	/*!
	 * @brief Initialization
	 * @param n Command name
	 * @param kt Command type
	 * @param ret_val Return value when the command is called
	 */
	int initialize(const char* n, cpkeytype kt, std::vector<double> ret_val){
		name = n;
		type = kt;
		val = ret_val;
		return 0;
	}
};

/*!
 * @class CommentGenerator
 * @brief CommentGerarator class
 */
class CommentGenerator{
	std::vector<CommentParamKey> keys;

	//comment parameters
	int font;
	double scale;
	cv::Scalar color;
	double thick;

	//utilities
	std::vector<double> setRGBVec(double R, double G, double B);
	int get_nonnegative_value(std::string &cmd, std::string::size_type &loc, double &value);

	int checkKey(std::string &cmd, std::string::size_type &loc);
	int checkRGB(std::string &cmd, std::string::size_type &loc);
	int checkSIZE(std::string &cmd, std::string::size_type &loc);

	int getFunctionArgs(std::string &cmd, std::string::size_type &loc, std::string &name, int argc, std::vector<double> &values);
public:
	/*!
	 * @brief Constructor
	 * @param txtfont Text font type
	 * @param txtscale Text size
	 * @param txtcolor Text color
	 * @param txtthick Text thickness
	 */
	CommentGenerator(int txtfont = cv::FONT_HERSHEY_COMPLEX, double txtscale = 1.0, cv::Scalar txtcolor=cv::Scalar(0,0,255), double txtthick = 2){
		setParams(txtfont, txtscale, txtcolor, txtthick);
		resetKeys();
	}
	/*!
	 * @brief Register commands
	 */
	void registKey(CommentParamKey k){keys.push_back(k);}
	void resetKeys();

	int setParams(int txtfont = cv::FONT_HERSHEY_COMPLEX, double txtscale = 1.0, cv::Scalar txtcolor=cv::Scalar(0,0,255), double txtthick = 2);
	int setParams(std::string &cmd); //set parameters using string

	/*!
	 * @brief Generate comment
	 * @param st Comment text
	 * @param initpos Initial text position
	 * @return Comment
	 */
	Comment generateComment(std::string &st,cv::Point initpos=cv::Size(-1,-1)){
		return Comment(st, font, scale, color, (int)(thick+0.5), initpos);
	}
};

#endif
