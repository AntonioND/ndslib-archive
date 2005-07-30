/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_BOX_H_
#define _DS_BOX_H_


//local includes
#include <NDS/DarkStar/dsClickable.h>
#include <NDS/DarkStar/dsEnums.h>
#include "dsText.h"


class dsBox : public dsText {
  public:
    dsBox(const char *btext=0, DS_STYLE bstyle=DS_STYLE_BOX);
    dsBox(s16 bx, s16 by, s16 bw, s16 bh, const char *btext=0, DS_STYLE bstyle=DS_STYLE_BOX);
    ~dsBox();

    void renderBox(u16 *buffer);
    inline void renderBox() { renderBox(buffers); }

    void renderText(u16 *buffer, DS_TEXT_COLOR color=DS_TEXT_COLOR_NORMAL);
    inline void renderText(DS_TEXT_COLOR color=DS_TEXT_COLOR_NORMAL) { renderText(buffers, color); }

    inline void renderButton(DS_TEXT_COLOR color=DS_TEXT_COLOR_NORMAL) { renderBox();  renderText(color); }

    void eraseBox();
    void eraseText();
    inline void eraseButton() { eraseBox();  eraseText(); }

    inline void setStyle(DS_STYLE bstyle) { style = bstyle; }
    inline DS_STYLE getStyle() const { return style; }

    inline void setBoxBuffer(u16 *buf) { buffers  = buf; }
    inline void setBoxText(const char *boxtext) { text = boxtext; }
    inline u16 *getBoxBuffer() const { return buffers; }
    inline const char *getBoxText() const { return text; }

    void moveBox(s16 bx, s16 by);
    void resizeBox(s16 bw, s16 bh);
    void moveResizeBox(s16 bx, s16 by, s16 bw, s16 bh);
    void moveText(s16 tx, s16 ty);  //relative to box position

    inline u16 getBoxX()      const { return boxx; }
    inline u16 getBoxY()      const { return boxy; }
    inline u16 getBoxWidth()  const { return boxw; }
    inline u16 getBoxHeight() const { return boxh; }

  private:
    s16 boxx, boxy;
    s16 boxw, boxh;
    s16 txtx, txty;
    const char *text;
    DS_STYLE style;

  protected:
    static u16 boxStyle[4][9];
    u16 *buffers;
};


class dsToggleBox : public dsBox, public dsClickable {
  public:
    dsToggleBox(const char *btext=0, DS_STYLE bstyle0=DS_STYLE_BOX, DS_STYLE bstyle1=DS_STYLE_BOX_INV);
    dsToggleBox(s16 bx, s16 by, s16 bw, s16 bh, const char *btext=0, DS_STYLE bstyle0=DS_STYLE_BOX, DS_STYLE bstyle1=DS_STYLE_BOX_INV);
    virtual ~dsToggleBox() {}

    virtual void onClick(s16 x, s16 y) { toggleBox(true); }

    void toggleBox(bool repaint=false);
    void selSelStyle(u8 which, bool repaint=false);
    bool getBoxPushed() const { return (sel != 0); }

    inline void setStyles(DS_STYLE bstyle, u8 which) { styles[which] = bstyle; }
    inline DS_STYLE getStyles(u8 which) const { return styles[which]; }

    inline DS_SCREEN getClickScreen() const { return screen; }
    inline void setClickScreen(DS_SCREEN dsscreen) { screen = dsscreen; }

    virtual bool hitTest(s16 x, s16 y, DS_SCREEN iscreen=DS_SCREEN_MAIN);

  protected:
    DS_STYLE styles[2];
    DS_SCREEN screen;
    u8 sel;
};


class dsButton : public dsToggleBox {
  public:
    dsButton(const char *btext=0, DS_STYLE bstyle0=DS_STYLE_BOX, DS_STYLE bstyle1=DS_STYLE_BOX_INV);
    dsButton(s16 bx, s16 by, s16 bw, s16 bh, const char *btext=0, DS_STYLE bstyle0=DS_STYLE_BOX, DS_STYLE bstyle1=DS_STYLE_BOX_INV);
    virtual ~dsButton() {}

    //called when sucessful push and release occures
    virtual void onButton() {}

    virtual void onClick(s16 x, s16 y);
    virtual void onDrag(s16 x, s16 y);
    virtual void onDrop(s16 x, s16 y);
};


#endif //_DS_BOX_H_
