/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _CHECKSOUT_BOX_H_
#define _CHECKSOUT_BOX_H_


//DarkStar includes
#include <NDS/DarkStar/dsClickable.h>


class dsChecksOut;


class dsChecksOutBox : public dsClickRect {
  public:
    dsChecksOutBox(u8 ix, u8 iy, dsChecksOut *dscheckout);
    virtual ~dsChecksOutBox();

    virtual void onClick(s16 x, s16 y);

    void render();
    void invert();

    void setValue(u8 value);
    inline u8 getValue() const { return val; }

  private:
    u8 xx, yy;
    u8 val;
    dsChecksOut *checkout;
};


#endif //_CHECKSOUT_BOX_H_
