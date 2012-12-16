// -*- C++ -*-
/*!
 * @file  time_to_string.h
 * @brief convert time data to string data
 * @date  $Date$
 *
 * @author ç≤ÅXñÿãB (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "time_to_string.h"

/*!
 * @brief Convert time data [sec] (in double) to string (hour:min:sec)
 * @param dt Time difference obtained by difftime() [sec]
 * @return Time in string (hour:min:sec)
 */
std::string convert_timediff_to_hms(double dt){
	std::ostringstream oss;
	int sec, min, hour;
	bool neg = false;

	if(dt<0.0){ //if negative, consider absolute value
		neg = true;
		dt = -dt;
	}

	sec = (int)std::fmod(dt,60);
	dt = (dt-sec)/60; //min
	min = (int)std::fmod(dt,60);

	dt = (dt-min)/60; //hour
	hour = (int)dt;
	if(neg){ //add '-' if negative data
		oss << "-";
	}
	if(hour>0){
		oss << hour << ":";
	}
	oss << std::setw(2) << std::setfill('0') << min << ":" << std::setw(2) << std::setfill('0') << sec;

	return oss.str();
}
