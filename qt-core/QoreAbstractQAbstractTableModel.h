/*
 QoreAbstractQAbstractTableModel.h
 
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

#ifndef _QORE_QT_QOREABSTRACTQABSTRACTTABLEMODEL_H

#define _QORE_QT_QOREABSTRACTQABSTRACTTABLEMODEL_H

#include "QoreAbstractQAbstractItemModel.h"

class QoreAbstractQAbstractTableModel : public QoreAbstractQAbstractItemModel {
   public:
      DLLLOCAL virtual QAbstractTableModel *getQAbstractTableModel() const = 0;
};

template<typename T, typename V>
class QoreQAbstractTableModelBase : public QoreQAbstractItemModelBase<T, V> {
   public:
      DLLLOCAL QoreQAbstractTableModelBase(T *qo) : QoreQAbstractItemModelBase<T, V>(qo) {
      }

      DLLLOCAL virtual QAbstractTableModel *getQAbstractTableModel() const {
         return static_cast<QAbstractTableModel *>(&(*this->qobj));
      }
};

template<typename T, typename V, typename P = T>
class QoreQtQAbstractTableModelBase : public QoreQtQAbstractItemModelBase<T, V, P> {
   public:
      DLLLOCAL QoreQtQAbstractTableModelBase(QoreObject *obj, T *qo) : QoreQtQAbstractItemModelBase<T, V, P>(obj, qo) {
      }

      DLLLOCAL virtual QAbstractTableModel *getQAbstractTableModel() const {
         return this->qobj;
      }
};

#endif  // _QORE_QT_QOREABSTRACTQABSTRACTTABLEMODEL_H
