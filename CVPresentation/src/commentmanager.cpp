// -*- C++ -*-
/*!
 * @file  commentmanager.cpp
 * @brief Comment and CommentManager class
 * @date  $Date$
 *
 * @author ç≤ÅXñÿãB (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <stdexcept>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "commentmanager.h"

#define SET_FONT 1
#define SET_SCALE 2
#define SET_COLOR 3
#define SET_THICKNESS 4
#define SET_SCALE_AND_THICKNESS 5

#define FIND_INT 1
#define FIND_DECIMAL 2

/*!
 * @brief Constructor
 * @param st Text of the comment
 * @param txtfont Text font type
 * @param txtscale Text size
 * @param txtcolor Text color
 * @param txtthick Text thickness
 * @param initpos Initial text position
 */
Comment::Comment(std::string &st, int txtfont, double txtscale, cv::Scalar txtcolor, int txtthick, cv::Point initpos){
	str = st;

	font = txtfont;
	scale = txtscale;
	color = txtcolor;
	thick = txtthick;
	
	size = cv::getTextSize(str, font, txtscale, txtthick, &baseline);

	pos.x = initpos.x;
	pos.y = initpos.y;
}

/*!
 * @brief Constructor
 * @param p Pointer to the image where comments are put
 * @param bspeed Comment speed
 */
CommentManager::CommentManager(cv::Mat *p, int bspeed){
	initialize(p, bspeed);
}

/*!
 * @brief Initialization
 * @param p Pointer to the image where comments are put
 * @param bspeed Comment speed
 * @return 0 if no error
 */
int CommentManager::initialize(cv::Mat *p, int bspeed){
	int res;

	CmtList.clear();
	res = setSpeed(bspeed);
	if(res!=0){
		return res;
	}
	setImage(p);

	return 0;
}

/*!
 * @brief Set comment speed
 * @param bspeed Comment speed
 * @return 0 if no error
 */
int CommentManager::setSpeed(int bspeed){
	if(bspeed<0){
		std::cerr << "Error in CommentManager::setSpeed(): Invalid argument" << std::endl;
		return -1;
	}
	basespeed = bspeed;
	return 0;
}

/*!
 * @brief Update comment position based on the comment speed parameter
 * @return 0 if no error
 */
int CommentManager::updateComment(){
	std::list<Comment>::iterator it = CmtList.begin();
	int dx;

	//if(pimg == NULL){return -1;} //this check is not necessary because comments cannot be added without image

	while(it != CmtList.end()){ //for each comment
		dx = ((*it).getSize().width/(pimg->cols/2)+1)*basespeed; //calculate the next position based on the text width and basespeed
		(*it).changePositionRelativeX(-dx); //move the comment
		
		if((*it).checkFinish()){ //if finish
			it = CmtList.erase(it); //remove the data
		}else{ //otherwise put the text
			(*it).putComment(*pimg);
			it++;
		}
	}

	return 0;
}

/*!
 * @brief Add comment to comment list
 * @param cmt Comment to be added
 * @return 0 if no error
 */
int CommentManager::addComment(Comment &cmt){
	int res;

	if(pimg==NULL){
		std::cerr << "Image not specified" << std::endl;
		return -1;
	}

	//std::cerr << cmt.getPosition().x << ' ' << cmt.getPosition().y << std::endl;
	if(cmt.getPosition().x == -1){
		cmt.changePositionAbsoluteX(pimg->cols);
	}
	if(cmt.getPosition().y == -1){
		res = findSpace(cmt);
		if(res<0){
			return -2;
		}
		cmt.changePositionAbsoluteY(res);
	}
	//std::cerr << cmt.getPosition().x << ' ' << cmt.getPosition().y << std::endl;
	CmtList.push_back(cmt);

	return 0;
}

/*!
 * @brief Find space where a comment is put
 * @param cmt Comment
 * @return Position where comment can be put, <0 if error
 */
int CommentManager::findSpace(Comment &cmt){
	const int xmargin = 5;
	const int ymargin = 5;
	int i;
	int cur_space;
	int cur_index;

	std::vector<int> space;
	int size = (int) std::ceil((double)(pimg->rows)/(cmt.getSize().height+ymargin));
	std::list<Comment>::iterator it = CmtList.begin();

	if(size<=0){return -1;}
	space.resize(size,0);

	while(it != CmtList.end()){ //for each comment
		cur_space = pimg->cols - ((*it).getPosition().x+(*it).getSize().width+xmargin); //caclurate right space
		cur_index = ((*it).getPosition().y-(*it).getSize().height)/(cmt.getSize().height+ymargin); //calculate the index

		if(space[cur_index] > cur_space){ //if smaller space
			space[cur_index] = cur_space; //update the space (i.e. consider only the worst case.)
		}

		it++;
	}

	cur_index = 0;
	cur_space = space[0];
	for(i=0;i<size;i++){
		if(space[i]==0){ //if enough space
			return (i+1)*(cmt.getSize().height+ymargin);
		}else{
			if(cur_space<space[i]){ //if larger space found
				cur_space = space[i]; //store the data
				cur_index = i;
			}
		}
	}
	return (cur_index+1)*(cmt.getSize().height+ymargin);
}

/*!
 * @brief Register default commands
 */
void CommentGenerator::resetKeys(){
	keys.clear();

	//register scale keys
	registKey(CommentParamKey("big", SCALE_AND_THICKNESS_RATIO, std::vector<double>(1,2.0)));
	registKey(CommentParamKey("small", SCALE_AND_THICKNESS_RATIO, std::vector<double>(1,0.5)));

	//register color keys
	registKey(CommentParamKey("black", COLOR, setRGBVec(0,0,0)));
	registKey(CommentParamKey("gray", COLOR, setRGBVec(128,128,128)));
	registKey(CommentParamKey("silver", COLOR, setRGBVec(192,192,192)));
	registKey(CommentParamKey("white", COLOR, setRGBVec(255,255,255)));
	registKey(CommentParamKey("blue", COLOR, setRGBVec(0,0,255)));
	registKey(CommentParamKey("navy", COLOR, setRGBVec(0,0,128)));
	registKey(CommentParamKey("teal", COLOR, setRGBVec(0,128,128)));
	registKey(CommentParamKey("green", COLOR, setRGBVec(0,128,0)));
	registKey(CommentParamKey("aqua", COLOR, setRGBVec(0,255,255)));
	registKey(CommentParamKey("lime", COLOR, setRGBVec(0,255,0)));
	registKey(CommentParamKey("yellow", COLOR, setRGBVec(255,255,0)));
	registKey(CommentParamKey("fuchsia", COLOR, setRGBVec(255,0,255)));
	registKey(CommentParamKey("olive", COLOR, setRGBVec(128,128,0)));
	registKey(CommentParamKey("purple", COLOR, setRGBVec(128,0,128)));
	registKey(CommentParamKey("maroon", COLOR, setRGBVec(128,0,0)));
	registKey(CommentParamKey("red", COLOR, setRGBVec(255,0,0)));

	//register thickness key
	//registKey(CommentParamKey("bold", THICKNESS_RATIO, std::vector<double>(1, 2.0)));

	return;
}

/*!
 * @brief Set parameters
 * @param txtfont Text font type
 * @param txtscale Text size
 * @param txtcolor Text color
 * @param txtthick Text thickness
 * @return 0 if no error
 */
int CommentGenerator::setParams(int txtfont, double txtscale, cv::Scalar txtcolor, double txtthick){
	font = txtfont;
	scale = txtscale;
	color = txtcolor;
	thick = txtthick;

	return 0;
}

/*!
 * @brief Set parameters
 * @param cmd Command to change parameters
 * @return 0 if no error
 */
int CommentGenerator::setParams(std::string &cmd){
	std::string::size_type loc = 0;

	int res;

	//flags
	bool delimiter_required = false;
	bool font_set = false;
	bool scale_set = false;
	bool color_set = false;
	bool thick_set = false;

	while((loc!=std::string::npos)&&(loc<cmd.size())){ //if not empty, read command
		//std::cout << loc << '/' << cmd.size() << std::endl;
		// ------------- Ignore spaces -----------------------------
		if(cmd[loc] == ' '){
			loc++;
			continue;
		}
		// ------------ End ignore spaces --------------------------

		// --------------- Check delimiter -------------------------
		if(delimiter_required){
			if(cmd[loc] == ','){
				loc++;
				delimiter_required = false;
				continue;
			}else{
				std::cerr << "Error in CommentGenerator::setParams(): invalid command - expected \',\'" << std::endl;
				return -1;
			}
		}
		// ------------ End check delimiter ------------------------
		
		// --------------- Check command ---------------------------
		res = checkKey(cmd, loc); //Check if the command is one of the keys
		if(res==0){ //if not keys
			res = checkRGB(cmd, loc); //Check if the command is an RGB command
			if(res==0){ //if not RGB command
				res = checkSIZE(cmd, loc); //Check if the command is a number
			}
		}

		//Check result
		if(res>0){
			delimiter_required = true;
			if(res==SET_FONT){
				if(font_set){
					std::cerr << "Warning in CommentGenerator::setParams(): multiple font paramters in command" << std::endl;
				}
				font_set = true;
			}else if(res==SET_SCALE){
				if(scale_set){
					std::cerr << "Warning in CommentGenerator::setParams(): multiple scale paramters in command" << std::endl;
				}
				scale_set = true;
			}else if(res==SET_COLOR){
				if(color_set){
					std::cerr << "Warning in CommentGenerator::setParams(): multiple color paramters in command" << std::endl;
				}
				color_set = true;
			}else if(res==SET_THICKNESS){
				if(thick_set){
					std::cerr << "Warning in CommentGenerator::setParams(): multiple thickness paramters in command" << std::endl;
				}
				thick_set = true;
			}else if(res==SET_SCALE_AND_THICKNESS){
				if(scale_set){
					std::cerr << "Warning in CommentGenerator::setParams(): multiple scale paramters in command" << std::endl;
				}
				if(thick_set){
					std::cerr << "Warning in CommentGenerator::setParams(): multiple thickness paramters in command" << std::endl;
				}
				scale_set = true;
				thick_set = true;
			}
		}else if(res<0){ //error in command
			return -1;
		}else{ //cannot find any commands
			std::cerr << "Error in CommentGenerator::setParams(): invalid command - command undefined" << std::endl;
			return -1;
		}
		// --------------- End check command -----------------------
	} //end while((loc!=std::string::npos)&&(loc<cmd.size()))

	return 0;
}

/*!
 * @brief Set parameters if key is specified in command
 * @param cmd Command
 * @param loc Position of the first character to be checked
 * @return SET_COLOR, SET_THICKNESS or SET_SCALE if corresponding parameter is set, 0 if no keys found
 */
int CommentGenerator::checkKey(std::string &cmd, std::string::size_type &loc){
	//if(loc >= cmd.size()){return 0;}

	for(unsigned int i=0;i<keys.size();i++){
		if(cmd.substr(loc, keys[i].name.size()) == keys[i].name){ //find key
			loc+=keys[i].name.size();
			switch(keys[i].type){
				case SCALE_ABS:
					scale = keys[i].val[0];
					return SET_SCALE;
				case SCALE_ABS_WITH_THICKNESS:
					thick = (keys[i].val[0]/scale)*thick;
					scale = keys[i].val[0];
					return SET_SCALE_AND_THICKNESS;
				case SCALE_REL:
					scale += keys[i].val[0];
					return SET_SCALE;
				case SCALE_REL_WITH_THICKNESS:
					thick = ((scale+keys[i].val[0])/scale)*thick;
					scale += keys[i].val[0];
					return SET_SCALE_AND_THICKNESS;
				case SCALE_RATIO:
					scale *= keys[i].val[0];
					return SET_SCALE;
				case SCALE_AND_THICKNESS_RATIO:
					thick *= keys[i].val[0];
					scale *= keys[i].val[0];
					return SET_SCALE_AND_THICKNESS;
				case COLOR:
					color = CV_RGB(keys[i].val[0],keys[i].val[1],keys[i].val[2]);
					return SET_COLOR;
				case THICKNESS_ABS:
					thick = keys[i].val[0];
					return SET_THICKNESS;
				case THICKNESS_ABS_WITH_SCALE:
					scale = (keys[i].val[0]/thick)*scale;
					thick = keys[i].val[0];
					return SET_SCALE_AND_THICKNESS;
				case THICKNESS_REL:
					thick += keys[i].val[0];
					return SET_THICKNESS;
				case THICKNESS_REL_WITH_SCALE:
					scale = ((thick+keys[i].val[0])/thick)*scale;
					thick = keys[i].val[0];
					return SET_SCALE_AND_THICKNESS;
				case THICKNESS_RATIO:
					thick *= keys[i].val[0];
					return SET_THICKNESS;
				default:
					std::cerr << "Error in CommentGenerator::checkKey(): undefined key type" << std::endl;
					return -1; //error
			}
		} //end if(cmd.substr(loc, keys[i].name.size()) == keys[i].name)
	}//end for(i)

	return 0; //not found
}

/*!
 * @brief Set color parameter if RGB command is specified
 * @param cmd Command
 * @param loc Position of the first character to be checked
 * @return SET_COLOR if color parameter is set, 0 if not RGB command
 */
int CommentGenerator::checkRGB(std::string &cmd, std::string::size_type &loc){
	int res;
	std::vector<double> color_tmp;
	std::string func_name("RGB(");

	res = getFunctionArgs(cmd, loc, func_name, 3, color_tmp);
	if(res>0){
		for(int i=0;i<3;i++){
			if(color_tmp[i]<0||color_tmp[i]>255){
				std::cerr << "Error in CommentGenerator::checkRGB(): invalid command - RGB values must be [0, 255]" << std::endl;
				return -4; //error
			}
			if(std::floor(color_tmp[i]) != std::ceil(color_tmp[i])){
				std::cerr << "Error in CommentGenerator::checkRGB(): invalid command - expected integer value" << std::endl;
				return -4; //error
			}
		}
		color.val[0] = color_tmp[2];
		color.val[1] = color_tmp[1];
		color.val[2] = color_tmp[0];
		return SET_COLOR; //found
	}
	return res;
}

/*!
 * @brief Set size and thickness parameters if SIZE command is specified
 * @param cmd Command
 * @param loc Position of the first character to be checked
 * @return SET_SCALE_AND_THICKNESS if size and thickness parameter is set, 0 if not SIZE command
 */
int CommentGenerator::checkSIZE(std::string &cmd, std::string::size_type &loc){
	int res;
	std::vector<double> value_tmp;
	std::string func_name("SIZE(");

	res = getFunctionArgs(cmd, loc, func_name, 1, value_tmp);
	if(res>0){
		if(value_tmp[0]<=0){
			std::cerr << "Error in CommentGenerator::checkSIZE(): invalid command - SIZE values must be >0" << std::endl;
			return -4; //error
		}
		thick = (value_tmp[0]/scale)*thick;
		scale = value_tmp[0];

		return SET_SCALE_AND_THICKNESS; //found
	}
	return res;

}

/*!
 * @brief Get function argments if function is specified
 * @param cmd Command
 * @param loc Position of the first character to be checked
 * @param name Function name
 * @param argc # of arguments
 * @param values argment values
 * @return >0 if no error, 0 if not specified function
 */
int CommentGenerator::getFunctionArgs(std::string &cmd, std::string::size_type &loc, std::string &name, int argc, std::vector<double> &values){
	int res;
	double val;

	if(argc<=0){
		return -1; //error
	}
	values.resize(argc);

	if(name[name.size()-1]!='('){
		name.push_back('(');
	}

	try{
		if(cmd.substr(loc,name.size())==name){ //if function name
			loc+=name.size();

			//Get first arg-1 argments
			for(int i=0;i<argc-1;i++){
				//Ignore spaces
				while(cmd.at(loc) == ' '){
					loc++;
				}
				res = get_nonnegative_value(cmd, loc, val);
				if(res<=0){
					std::cerr << "Error in CommentGenerator::getFunctionArgs(): invalid command - expected positive number" << std::endl;
					return -2; //error
				}

				values[i] = val; //get the value

				//Ignore spaces
				while(cmd.at(loc) == ' '){
					loc++;
				}
				//Check delimiter
				if(cmd.at(loc) == ','){
					loc++;
				}else if(cmd.at(loc) == ')'){
					std::cerr << "Error in CommentGenerator::getFunctionArgs(): invalid command - too few arguments" << std::endl;
					return -2; //error
				}else{
					std::cerr << "Error in CommentGenerator::getFunctionArgs(): invalid command - expected \',\'" << std::endl;
					return -2; //error
				}
			}

			//Get last argument
			//Ignore spaces
			while(cmd.at(loc) == ' '){
				loc++;
			}
			res = get_nonnegative_value(cmd, loc, val);
			if(res<=0){
				std::cerr << "Error in CommentGenerator::getFunctionArgs(): invalid command - expected positive number" << std::endl;
				return -2; //error
			}
			values[argc-1] = val; //get the value

			//Ignore spaces
			while(cmd.at(loc) == ' '){
				loc++;
			}
			//Check delimiter
			if(cmd.at(loc) == ')'){
				loc++;
			}else{
				std::cerr << "Error in CommentGenerator::getFunctionArgs(): invalid command - expected \')\'" << std::endl;
				return -2; //error
			}

			return 1; //found
		}
	}catch(std::out_of_range){
		std::cerr << "Error in CommentGenerator::getFunctionArgs(): invalid command - expected \')\'" << std::endl;
		return -3; //error
	}

	return 0; //not found
}

/*!
 * @brief Get nonnegative value 
 * @param cmd Command
 * @param loc Position of first character to be checked
 * @param value Obtained value
 * @return FIND_INT if integer, FIND_DECIMAL if decimal number, 0 if not a number
 */
int CommentGenerator::get_nonnegative_value(std::string &cmd, std::string::size_type &loc, double &value){
	std::string::size_type loc_end;
	std::string::size_type loc_dot;

	if(loc >= cmd.size()){return 0;}

	loc_end = cmd.substr(loc).find_first_not_of("0123456789.");
	if(loc_end!=0){ //the first character is a number
		loc_dot = cmd.substr(loc,loc_end).find_first_of('.');
		if((loc_dot==std::string::npos) && ((cmd[loc]!='0')||(loc_end==1))){ //check if integer: (no '.') and (only 0 or the first character is not 0)
			value = std::atof(cmd.substr(loc,loc_end).c_str());
			if(loc_end==std::string::npos){
				loc_end=cmd.substr(loc,loc_end).size();
			}
			loc += loc_end;
			return FIND_INT; //integer
		}else if( //check if decimal number:
			(loc_dot==cmd.substr(loc,loc_end).find_last_of('.')) // only one '.'
			&&
			((cmd[loc]!='0')||(loc_dot==1)) // the first character is not 0 or the second character is '.'
			&&
			(loc_dot!=cmd.substr(loc,loc_end).size()-1)// '.' is not placed at the end of the number
		){
			value = std::atof(cmd.substr(loc,loc_end).c_str());
			if(loc_end==std::string::npos){
				loc_end=cmd.substr(loc,loc_end).size();
			}
			loc += loc_end;
			return FIND_DECIMAL; //decimal number
		}else{ //error
			return -1;
		}
	}

	return 0; //not found
}

/*!
 * @brief Generate three-element vector which contains RGB information
 */
std::vector<double> CommentGenerator::setRGBVec(double R, double G, double B){
	std::vector<double> vec(3,0);
	vec[0] = R;
	vec[1] = G;
	vec[2] = B;

	return vec;
}
