/*
 QoreAbstractQStringListModel.h
 
 Qore Programming Language

 Copyright (C) 2003 - 2009 Qore Technologies

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

#ifndef _QORE_QT_QOREABSTRACTQSTRINGLISTMODEL_H

#define _QORE_QT_QOREABSTRACTQSTRINGLISTMODEL_H

#include "QoreAbstractQAbstractListModel.h"

class QoreAbstractQStringListModel : public QoreAbstractQAbstractListModel {
   public:
      DLLLOCAL virtual QStringListModel *getQStringListModel() const = 0;
};

template<typename T, typename V>
class QoreQStringListModelBase : public QoreQAbstractListModelBase<T, V> {
   public:
      DLLLOCAL QoreQStringListModelBase(T *qo) : QoreQAbstractListModelBase<T, V>(qo) {
      }

      DLLLOCAL virtual QStringListModel *getQStringListModel() const {
         return static_cast<QStringListModel *>(&(*this->qobj));
      }
};

template<typename T, typename V>
class QoreQtQStringListModelBase : public QoreQtQAbstractListModelBase<T, V> {
   public:
      DLLLOCAL QoreQtQStringListModelBase(QoreObject *obj, T *qo) : QoreQtQAbstractListModelBase<T, V>(obj, qo) {
      }

      DLLLOCAL virtual QStringListModel *getQStringListModel() const {
         return this->qobj;
      }
};

#endif  // _QORE_QT_QOREABSTRACTQSTRINGLISTMODEL_H
