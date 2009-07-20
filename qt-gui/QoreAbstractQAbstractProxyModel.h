/*
 QoreAbstractQAbstractProxyModel.h
 
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

#ifndef _QORE_QT_QOREABSTRACTQABSTRACTPROXYMODEL_H

#define _QORE_QT_QOREABSTRACTQABSTRACTPROXYMODEL_H

#include "QoreAbstractQAbstractItemModel.h"

class QoreAbstractQAbstractProxyModel : public QoreAbstractQAbstractItemModel {
   public:
      DLLLOCAL virtual QAbstractProxyModel *getQAbstractProxyModel() const = 0;
};

template<typename T, typename V>
class QoreQAbstractProxyModelBase : public QoreQAbstractItemModelBase<T, V> {
   public:
      DLLLOCAL QoreQAbstractProxyModelBase(T *qo) : QoreQAbstractItemModelBase<T, V>(qo) {
      }

      DLLLOCAL virtual QAbstractProxyModel *getQAbstractProxyModel() const {
         return static_cast<QAbstractProxyModel *>(&(*this->qobj));
      }
};

template<typename T, typename V>
class QoreQtQAbstractProxyModelBase : public QoreQtQAbstractItemModelBase<T, V> {
   public:
      DLLLOCAL QoreQtQAbstractProxyModelBase(QoreObject *obj, T *qo) : QoreQtQAbstractItemModelBase<T, V>(obj, qo) {
      }

      DLLLOCAL virtual QAbstractProxyModel *getQAbstractProxyModel() const {
         return this->qobj;
      }
};


class QoreQAbstractProxyModelExtension : public QoreQAbstractItemModelExtension {
  protected:
    const QoreMethod *m_mapFromSource, *m_mapSelectionFromSource, *m_mapSelectionToSource, *m_mapToSource, *m_setSourceModel;

    DLLLOCAL QoreQAbstractProxyModelExtension(QoreObject *obj, QObject *qo) : QoreQAbstractItemModelExtension(obj, qo) {
         const QoreClass *qc = obj->getClass();

	 m_mapFromSource = findMethod(qc, "mapFromSource");
         m_mapSelectionFromSource = findMethod(qc, "mapSelectionFromSource");
         m_mapSelectionToSource = findMethod(qc, "mapSelectionToSource");
         m_mapToSource = findMethod(qc, "mapToSource");
         m_setSourceModel = findMethod(qc, "setSourceModel");
    }
};

#endif  // _QORE_QT_QOREABSTRACTQABSTRACTPROXYMODEL_H

