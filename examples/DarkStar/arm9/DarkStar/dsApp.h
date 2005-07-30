/*****************************  DARKSTAR  ******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest source versions can be found at:  HTTP://WWW.DARKAIN.COM/     *
\***********************************************************************/


#ifndef _DS_APP_H_
#define _DS_APP_H_


#include <NDS/DarkStar/vArray.h>


class dsApp {
  protected:
    dsApp() {
      if (!apps) apps = new vArray<dsApp*>;
      apps->appendItem(this);
    }
  public:
    virtual ~dsApp() { apps->removeItem(this); }


  public:
    virtual const char *getAppName()=0;
    virtual const char *getMenuName()=0;
    virtual void onLaunch()=0;
    virtual void onClose()=0;


  public:
    //when i switched code around, it queried in rever-alpha order
    //so i switched from first to last, and next to prev... easy fix
    inline static dsApp *getFirstApp() { return apps->getFirstItem(); }
    inline static dsApp *getNextApp(dsApp *app) { return apps->getNextItem(app); }

  private:
    static vArray<dsApp*> *apps;
};


template<class appclass>
class dsAppTemplate : public dsApp {
  public:
    dsAppTemplate() { app=0; }
    virtual ~dsAppTemplate() { delete app; app=0; }
  public:
    virtual const char *getAppName()  { return appclass::getAppName(); }
    virtual const char *getMenuName() { return appclass::getMenuName(); }
    virtual void onLaunch() { app = new appclass(); }
    virtual void onClose() { delete app; app=0; }
  private:
    appclass *app;
};


#endif //_DS_APP_H_
