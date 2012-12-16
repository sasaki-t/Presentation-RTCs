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

#ifndef TIME_TO_STRING_H
#define TIME_TO_STRING_H

#include <string>

std::string convert_timediff_to_hms(double dt); //convert time data [sec] (in double) to string (hour:min:sec)

#endif
