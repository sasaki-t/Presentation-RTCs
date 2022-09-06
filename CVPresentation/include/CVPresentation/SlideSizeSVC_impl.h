// -*-C++-*-
/*!
 * @file  SlideSizeSVC_impl.h
 * @brief Service implementation header of SlideSize.idl
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */

#include "SlideSizeSkel.h"

#ifndef SLIDESIZESVC_IMPL_H
#define SLIDESIZESVC_IMPL_H
 
/*!
 * @class Slide_SlideSizeInfoSVC_impl
 * Example class implementing IDL interface Slide::SlideSizeInfo
 */
class Slide_SlideSizeInfoSVC_impl
 : public virtual POA_Slide::SlideSizeInfo,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~Slide_SlideSizeInfoSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
   Slide_SlideSizeInfoSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~Slide_SlideSizeInfoSVC_impl();

   // attributes and operations
   ::CORBA::Short getWidth();
   ::CORBA::Short getHeight();

   int slide_width;
   int slide_height;
};



#endif // SLIDESIZESVC_IMPL_H


