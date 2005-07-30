/***************************  VBASE SDK  *******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest SDK versions can be found at:  HTTP://www.Darkain.com         *
\***********************************************************************/


#ifndef __NAME_H_
#define __NAME_H_


#include "vTypes.h"
#include <malloc.h>


class vName {
  public:
    vName(const char *initialName=NULL) {
      name = NULL;
      setName(initialName, FALSE);
    }

    virtual ~vName() {
      free((void*)name);
      name = NULL;
    }

    virtual void onNameChange(const char *newname) {}

  public:
    inline const char *getName(const char *defVal=NULL) const {
      if (!name) return defVal;
      return name;
    }

    void setName(const char *newName, BOOL cb=TRUE) {
      if (newName == name) return;
      if (!newName) {
        free(name);
        name = NULL;
        if (cb) onNameChange(NULL);
        return;
      }
      int len = strlen(newName)+1;
      name = (char*)realloc(name, len);
      memcpy(name, newName, len);
      if (cb) onNameChange(name);
    }

    //dont use this one, use setName instead
    void setNameBuffer(char *newName, BOOL cb=TRUE) {
      if (name == newName) return;
      free(name);
      name = newName;
      if (cb) onNameChange(name);
    }

  private:
    char *name;
};


#endif //__NAME_H_
