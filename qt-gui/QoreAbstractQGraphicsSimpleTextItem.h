/*
 QoreAbstractQGraphicsSimpleTextItem.h
 
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

#ifndef _QORE_QT_QOREABSTRACTQGRAPHICSSIMPLETEXTITEM_H

#define _QORE_QT_QOREABSTRACTQGRAPHICSSIMPLETEXTITEM_H

#include "QoreAbstractQAbstractGraphicsShapeItem.h"

class QoreAbstractQGraphicsSimpleTextItem : public QoreAbstractQAbstractGraphicsShapeItem
{
   public:
      DLLLOCAL virtual QGraphicsSimpleTextItem *getQGraphicsSimpleTextItem() const = 0;
};

template<typename T, typename V>
class QoreQGraphicsSimpleTextItemBase : public QoreQAbstractGraphicsShapeItemBase<T, V>
{
   public:
      DLLLOCAL QoreQGraphicsSimpleTextItemBase(T *qo) : QoreQAbstractGraphicsShapeItemBase<T, V>(qo)
      {
      }

      DLLLOCAL virtual QGraphicsSimpleTextItem *getQGraphicsSimpleTextItem() const
      {
         return static_cast<QGraphicsSimpleTextItem *>(&(*this->qobj));
      }
};

template<typename T, typename V>
class QoreQtQGraphicsSimpleTextItemBase : public QoreQtQAbstractGraphicsShapeItemBase<T, V>
{
   public:
      DLLLOCAL QoreQtQGraphicsSimpleTextItemBase(T *qo, bool managed = true) : QoreQtQAbstractGraphicsShapeItemBase<T, V>(qo, managed)
      {
      }

      DLLLOCAL virtual QGraphicsSimpleTextItem *getQGraphicsSimpleTextItem() const
      {
         return this->qobj;
      }
};

#endif  // _QORE_QT_QOREABSTRACT%s_H
