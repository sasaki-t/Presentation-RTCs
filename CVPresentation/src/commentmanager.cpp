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
#include <cmath>
#include <string>
#include <list>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "commentmanager.h"


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
