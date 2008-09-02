/*
 QoreAbstractQScrollBar.h
 
 Qore Programming Language
 
 Copyright 2003 - 2008 David Nichols
 
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

#ifndef _QORE_QT_QOREABSTRACTQSCROLLBAR_H

#define _QORE_QT_QOREABSTRACTQSCROLLBAR_H

#include "QoreAbstractQAbstractSlider.h"

class QoreAbstractQScrollBar : public QoreAbstractQAbstractSlider
{
   public:
      DLLLOCAL virtual class QScrollBar *getQScrollBar() const = 0;
};

template<typename T, typename V>
class QoreQScrollBarBase : public QoreQAbstractSliderBase<T, V>
{
   public:
      DLLLOCAL QoreQScrollBarBase(T *qo) : QoreQAbstractSliderBase<T, V>(qo)
      {
      }

      DLLLOCAL virtual QScrollBar *getQScrollBar() const
      {
	 return &(*this->qobj);
      }
};

template<typename T, typename V>
class QoreQtQScrollBarBase : public QoreQtQAbstractSliderBase<T, V>
{
   public:
      DLLLOCAL QoreQtQScrollBarBase(QoreObject *obj, T *qo) : QoreQtQAbstractSliderBase<T, V>(obj, qo)
      {
      }

      DLLLOCAL virtual QScrollBar *getQScrollBar() const
      {
	 return this->qobj;
      }
};

#endif  // _QORE_QT_QOREABSTRACTQSCROLLBAR_H
