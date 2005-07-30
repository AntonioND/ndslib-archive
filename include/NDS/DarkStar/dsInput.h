/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_INPUT_H_
#define _DS_INPUT_H_


#include "vList.h"


class dsInput {
  public:
    dsInput();
    virtual ~dsInput();

    virtual void onKeyChange(u32 inputState, u32 lastState)=0;

    static vList<dsInput*> items;
};


#endif //_DS_INPUT_H_
