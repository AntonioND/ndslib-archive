/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#include <NDS/NDS.h>
#include <NDS/DarkStar/dsBlank.h>


vList<dsBlank*> dsBlank::items;


dsBlank::dsBlank() {
  items.appendItem(this);
}


dsBlank::~dsBlank() {
  items.removeItem(this);
}


