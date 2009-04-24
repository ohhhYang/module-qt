/*
 QoreAbstractQDockWidget.h
 
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

#ifndef _QORE_QT_QOREABSTRACTQDOCKWIDGET_H

#define _QORE_QT_QOREABSTRACTQDOCKWIDGET_H

#include "QoreAbstractQWidget.h"

class QoreAbstractQDockWidget : public QoreAbstractQWidget {
   public:
      DLLLOCAL virtual QDockWidget *getQDockWidget() const = 0;

      DLLLOCAL virtual void initStyleOption ( QStyleOptionDockWidget * option, ExceptionSink *xsink ) const = 0;
};

template<typename T, typename V>
class QoreQDockWidgetBase : public QoreQWidgetBase<T, V> {
   public:
      DLLLOCAL QoreQDockWidgetBase(T *qo) : QoreQWidgetBase<T, V>(qo) {
      }

      DLLLOCAL virtual QDockWidget *getQDockWidget() const {
         return static_cast<QDockWidget *>(&(*this->qobj));
      }

      DLLLOCAL virtual void initStyleOption ( QStyleOptionDockWidget * option, ExceptionSink *xsink ) const {
	 this->qobj->parent_initStyleOption(option);
      }

};

template<typename T, typename V>
class QoreQtQDockWidgetBase : public QoreQtQWidgetBase<T, V> {
   public:
      DLLLOCAL QoreQtQDockWidgetBase(QoreObject *obj, T *qo) : QoreQtQWidgetBase<T, V>(obj, qo) {
      }

      DLLLOCAL virtual QDockWidget *getQDockWidget() const {
         return this->qobj;
      }

      DLLLOCAL virtual void initStyleOption ( QStyleOptionDockWidget * option, ExceptionSink *xsink ) const {
	 xsink->raiseException("QDOCKWIDGET-INITSTYLEOPTION-ERROR", "cannot call protected member functions of non-Qore QDockWidget objects");
      }
};

#endif  // _QORE_QT_QOREABSTRACTQDOCKWIDGET_H
