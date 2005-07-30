/***************************  VBASE SDK  *******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest SDK versions can be found at:  HTTP://www.Darkain.com         *
\***********************************************************************/


#ifndef _V_ARRAY_H_
#define _V_ARRAY_H_

#include <malloc.h>
#include "vTypes.h"


template <class T>
class vArray {
  public:
    vArray() {
      array = NULL;
      size = 0;
    }

    ~vArray() {
      free(array);
    }

    int getItemCount() { return size; }


    void appendItem(T item) {
      size++;
      array = (T*)realloc(array, sizeof(T)*size);
      array[size-1] = item;
    }

    void removeLastItem() {
      if (size == 0) return;
      size--;
      array = (T*)realloc(array, sizeof(T)*size);
    }

    void removeFirstItem() {
      if (size == 0) return;
      for (int i=0; i<size-1; i++) {
        array[i] = array[i+1];
      }
      removeLastItem();
    }

    void removeItem(int pos) {
      if (size == 0) return;
      if (pos >= size) return;
      if (pos < 0) return;
      for (int i=pos; i<size-1; i++) {
        array[i] = array[i+1];
      }
      removeLastItem();
    }

    void removeItem(T item) {
      removeItem(getItemPos(item));
    }

    int getItemPos(T item) {
      if (size == 0) return -1;
      for (int i=0; i<size; i++) {
        if (array[i] == item) return i;
      }
      return -1;
    }

    T getItem(int pos) {
      if (size == 0) return NULL;
      if (pos >= size) return NULL;
      if (pos < 0) return NULL;
      return array[pos];
    }

    T getFirstItem() {
      if (size == 0) return NULL;
      return array[0];
    }

    T getLastItem() {
      if (size == 0) return NULL;
      return array[size-1];
    }

    T getNextItem(T item) {
      return getItem(getItemPos(item)+1);
    }

    T getPrevItem(T item) {
      return getItem(getItemPos(item)-1);
    }

  private:
    T *array;
    int size;
};


#endif //_V_ARRAY_H_
