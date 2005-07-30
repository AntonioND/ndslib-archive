/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_BLANK_H_
#define _DS_BLANK_H_


#include "vList.h"


class dsBlank {
  public:
    dsBlank();
    virtual ~dsBlank();

    virtual void onVBlank()=0;

    static vList<dsBlank*> items;
};


#endif //_DS_BLANK_H_
