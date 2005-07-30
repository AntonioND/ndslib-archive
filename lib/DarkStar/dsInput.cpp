/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>
#include <NDS/DarkStar/dsInput.h>


vList<dsInput*> dsInput::items;


dsInput::dsInput() {
  items.appendItem(this);
}


dsInput::~dsInput() {
  items.removeItem(this);
}


