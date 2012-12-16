// -*-C++-*-
/*!
 * @file  SlideSizeSVC_impl.cpp
 * @brief Service implementation code of SlideSize.idl
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */

#include "SlideSizeSVC_impl.h"

/*
 * Example implementational code for IDL interface Slide::SlideSizeInfo
 */
SlideSizeInfoSVC_impl::SlideSizeInfoSVC_impl()
{
  // Please add extra constructor code here.
  slide_width = -1;
  slide_height = -1;
}


SlideSizeInfoSVC_impl::~SlideSizeInfoSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
CORBA::Short SlideSizeInfoSVC_impl::getWidth()
{
  // Please insert your code here and remove the following warning pragma
  return slide_width;
}

CORBA::Short SlideSizeInfoSVC_impl::getHeight()
{
  // Please insert your code here and remove the following warning pragma
  return slide_height;
}



// End of example implementational code



