/*
 QoreAbstractQMainWindow.h
 
 Qore Programming Language

 Copyright (C) 2003 - 2009 David Nichols

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
 */

#ifndef _QORE_QT_QOREABSTRACTQMAINWINDOW_H

#define _QORE_QT_QOREABSTRACTQMAINWINDOW_H

#include "QoreAbstractQWidget.h"

class QoreAbstractQMainWindow : public QoreAbstractQWidget {
   public:
      DLLLOCAL virtual QMainWindow *getQMainWindow() const = 0;
      DLLLOCAL virtual QMenu *createPopupMenu() = 0;
};

template<typename T, typename V>
class QoreQMainWindowBase : public QoreQWidgetBase<T, V> {
   public:
      DLLLOCAL QoreQMainWindowBase(T *qo) : QoreQWidgetBase<T, V>(qo) {
      }

      DLLLOCAL virtual QMainWindow *getQMainWindow() const {
         return static_cast<QMainWindow *>(&(*this->qobj));
      }

      DLLLOCAL virtual QMenu *createPopupMenu() {
	 return this->qobj->parent_createPopupMenu();
      }
};

template<typename T, typename V>
class QoreQtQMainWindowBase : public QoreQtQWidgetBase<T, V> {
   public:
      DLLLOCAL QoreQtQMainWindowBase(QoreObject *obj, T *qo) : QoreQtQWidgetBase<T, V>(obj, qo) {
      }

      DLLLOCAL virtual QMainWindow *getQMainWindow() const {
         return this->qobj;
      }

      DLLLOCAL virtual QMenu *createPopupMenu() {
	 return this->qobj->createPopupMenu();
      }
};

#endif  // _QORE_QT_QOREABSTRACTQMAINWINDOW_H
