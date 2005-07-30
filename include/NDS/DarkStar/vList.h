/***************************  VBASE SDK  *******************************\
*  Copyright (c) 2005 Vincent E. Milum Jr., All rights reserved.        *
*                                                                       *
*  See License.txt for more information                                 *
*                                                                       *
*  Latest SDK versions can be found at:  HTTP://www.Darkain.com         *
\***********************************************************************/


#ifndef _V_LIST_H_
#define _V_LIST_H_

#include <malloc.h>
#include "vTypes.h"


extern unsigned int volatile vlistcount;
extern unsigned int getvListCount();


#undef appendItem


template <class T>
class vList {
  private:
    typedef struct vtagLIST {
      vtagLIST  *next;
      vtagLIST  *prev;
      T          data;
    } vListItem, *LPvListItem;

  public:
    vList() {
      vlistcount+=1;
      first = NULL;
      last  = NULL;
      cache = NULL;
      count = 0;
    }


    virtual ~vList() {
      emptyItems();
      vlistcount-=1;
    }


  protected:
    //called once an item is successfully added to the list
    virtual void onInsertItem(T data, T before) {}

    //called once an item is deleted from the list.
    virtual void onDelete(T data) {}

    //this is called when one of the move operations happens,
    //this way you can update anything that depends on list
    //positioning or anything like that
    virtual void onItemMoved(T data, T before) {}

  public:
    int getItemCount() const { return count; }
    BOOL hasItems() const { return (count>0); }
    BOOL itemExists(T data) const { return !!findItem(data); }

    
    int insertItem(T data, T insert) {
      if (!data) return -1;
      LPvListItem item = findItem(insert);

      LPvListItem newitem = createNew(data);
      if (item) {
        if (item->prev) {
          item->prev->next = newitem;
          newitem->prev = item->prev;
        }
        item->prev = newitem;
        newitem->next = item;
        if (item == first) first = newitem;
      } else if (last) {
        last->next = newitem;
        newitem->prev = last;
        last = newitem;
      } else {
        last = newitem;
        first = newitem;
      }
      cache = newitem;
      if (item)  onInsertItem(data, item->data);
      else onInsertItem(data, NULL);
      return count;
    }

    inline int prependItem(T data) {
      T fdata = NULL;
      if (first) fdata = first->data;
      return insertItem(data, fdata);
    }


    inline int appendItem(T data) {
      return insertItem(data, NULL);
    }


    int removeFirstItem() { if (first) removeOld(first); return count; }
    int removeLastItem()  { if (last)  removeOld(last);  return count; }


    int removeItem(T data) {
      //this should switch over to using findItem to take advantage of auto-caching
      if (!first) return -1;
      LPvListItem item = first;
      while (item) {
        if (item->data == data) { removeOld(item); break; }
        item = item->next;
      }
      return count;
    }


    int emptyItems() {
      if (!first) return -1;
      LPvListItem item = first;
      while (item) {
        removeOld(item);
        item = first;
      }
      first = NULL;
      last = NULL;
      cache = NULL;
      count = 0;
      return count;
    }


    T getFirstItem()  const { if (first) return first->data; return NULL; }
    T getLastItem()   const { if (last)  return last->data;  return NULL; }
    T getCachedItem() const { if (cache) return cache->data; return NULL; } 


    T getNextItem(T data) const {
      LPvListItem item = findItem(data);
      if (!item) return NULL;
      if (!item->next) return NULL;
      cache = item->next;
      return cache->data;
    }

    T getPrevItem(T data) const {
      LPvListItem item = findItem(data);
      if (!item)  return NULL;
      if (!item->prev) return NULL;
      cache = item->prev;
      return cache->data;
    }

    T getItem(int id) const {
      T item = getFirstItem();
      for (int i=0; i<id; i++) item = getNextItem(item);
      return item;
    }

    int getItemIndex(T data) {
      LPvListItem item = first();
      int i=0;
      while (item) {
        if (item->data == data) return i;
        i++;
        item = item->next;
      }
      return -1;
    }


    BOOL moveItem(T data, T insert) {
      if (count < 2) return FALSE;
      LPvListItem itm = findItem(data);
      if (!itm) return FALSE;
      LPvListItem itm2 = findItem(insert);
      if (itm == itm2) return FALSE;
      if (itm->prev) itm->prev->next = itm->next;
      if (itm->next) itm->next->prev = itm->prev;
      if (itm == first) first = itm->next;
      if (itm == last) last = itm->prev;

      itm->next = itm2;
      if (itm2) {      
        itm->prev = itm2->prev;
        itm2->prev = itm;
        if (itm->prev) {
          itm->prev->next = itm;
        } else {
          first = itm;
        }
      } else {
        itm->prev = last;
        last->next = itm;
        last = itm;
      }

      onItemMoved(data, insert);
      return TRUE;
    }

    inline BOOL moveToBegining(T data) {
      T fdata = NULL;
      if (first) fdata = first->data;
      return moveItem(data, fdata);
    }

    inline BOOL moveToEnd(T data) {
      return moveItem(data, NULL);
    }

    inline BOOL chainLinkForward() {
      if (!first) return FALSE;
      return moveToEnd(first->data);
    }
   
    inline BOOL chainLinkBackward() {
      if (!last) return FALSE;
      return moveToBegining(last->data);
    }

    void reverseList() {
      LPvListItem *item = first;
      while (item) {
        LPvListItem *tmp = item->prev;
        item->prev = item->next;
        item->next = tmp;
        item = item->prev;
      }
    }


#ifdef _GBA_
  public:
    //note: this section could be optimized by updating the cache handler
    T LONG_CALL L_getFirstItem()  const { if (first) return first->data; return NULL; }
    T LONG_CALL L_getLastItem()   const { if (last)  return last->data;  return NULL; }

    T LONG_CALL L_getNextItem(T data) const {
      LPvListItem item = L_findItem(data);
      if (!item) return NULL;
      if (!item->next) return NULL;
      cache = item->next;
      return cache->data;
    }

  protected:
    inline LPvListItem LONG_CALL L_findItem(T data) const {
      if (!data) return NULL;
      if (cache) if (cache->data == data) return cache;
      if (last) if (last->data == data) return last;
      LPvListItem item = first;
      while (item) {
        if (item->data == data) {
          cache = item;
          return item;
        }
        item = item->next;
      }
      return NULL;
    }
#endif //_GBA_


  protected:
    inline LPvListItem createNew(T data) {
      LPvListItem item = (LPvListItem) malloc(sizeof(vtagLIST));
      item->next = NULL;
      item->prev = NULL;
      item->data = data;
      count++;
      return item;
    }

    inline void removeOld(LPvListItem item) {
      count--;
      if (count == 0) {
        first = NULL;
        last = NULL;
        cache = NULL;
      } else {
        if (item == cache) cache = item->next;
        if (item->next) item->next->prev = item->prev;
        if (item->prev) item->prev->next = item->next;
        if (item == first) first = item->next;
        if (item == last) last = item->prev;
      }
      onDelete(item->data);
      free(item);
    }

    inline LPvListItem findItem(T data) const {
      if (!data) return NULL;
      if (cache) if (cache->data == data) return cache;
      if (last) if (last->data == data) return last;
      LPvListItem item = first;
      while (item) {
        if (item->data == data) {
          cache = item;
          return item;
        }
        item = item->next;
      }
      return NULL;
    }

  protected:
    LPvListItem first;
    LPvListItem last;
    mutable LPvListItem cache;
    int count;
};


template <class T>
class vFreeList : public vList<T> {
  public:
    virtual ~vFreeList() { vList<T>::emptyItems(); }
    virtual void onDelete(T data) { free((void*)data); }
};

template <class T>
class vDeleteList : public vList<T> {
  public:
    virtual ~vDeleteList() { vList<T>::emptyItems(); }
    virtual void onDelete(T data) { delete data; }
};


#endif //_V_LIST_H_
