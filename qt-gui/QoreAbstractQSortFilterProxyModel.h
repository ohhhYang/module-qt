/*
 QoreAbstractQSortFilterProxyModel.h
 
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

#ifndef _QORE_QT_QOREABSTRACTQSORTFILTERPROXYMODEL_H

#define _QORE_QT_QOREABSTRACTQSORTFILTERPROXYMODEL_H

#include "QoreAbstractQAbstractProxyModel.h"

class QoreAbstractQSortFilterProxyModel : public QoreAbstractQAbstractProxyModel {
   public:
      DLLLOCAL virtual QSortFilterProxyModel *getQSortFilterProxyModel() const = 0;

      // protected methods
      virtual bool filterAcceptsColumn ( int source_column, const QModelIndex & source_parent ) const = 0;
      virtual bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const = 0;
      virtual void invalidateFilter () = 0;
      virtual bool lessThan ( const QModelIndex & left, const QModelIndex & right ) const = 0;
};

template<typename T, typename V>
class QoreQSortFilterProxyModelBase : public QoreQAbstractProxyModelBase<T, V> {
   public:
      DLLLOCAL QoreQSortFilterProxyModelBase(T *qo) : QoreQAbstractProxyModelBase<T, V>(qo) {
      }

      DLLLOCAL virtual QSortFilterProxyModel *getQSortFilterProxyModel() const {
         return static_cast<QSortFilterProxyModel *>(&(*this->qobj));
      }

      // protected methods
      DLLLOCAL virtual bool filterAcceptsColumn ( int source_column, const QModelIndex & source_parent ) const
      {
          return this->qobj->parent_filterAcceptsColumn(source_column, source_parent);
      };
      DLLLOCAL virtual bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const
      {
          return this->qobj->parent_filterAcceptsRow(source_row, source_parent);
      };
      DLLLOCAL void invalidateFilter ()
      {
          this->qobj->parent_invalidateFilter();
      };
      DLLLOCAL virtual bool lessThan ( const QModelIndex & left, const QModelIndex & right ) const
      {
          return this->qobj->parent_lessThan(left, right);
      };
};

template<typename T, typename V>
class QoreQtQSortFilterProxyModelBase : public QoreQtQAbstractProxyModelBase<T, V> {
   public:
      DLLLOCAL QoreQtQSortFilterProxyModelBase(QoreObject *obj, T *qo) : QoreQtQAbstractProxyModelBase<T, V>(obj, qo) {
      }

      DLLLOCAL virtual QSortFilterProxyModel *getQSortFilterProxyModel() const {
         return this->qobj;
      }
      
      // protected methods
      DLLLOCAL virtual bool filterAcceptsColumn ( int source_column, const QModelIndex & source_parent ) const
        { return false; };
      DLLLOCAL virtual bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const
        { return false; };
      DLLLOCAL void invalidateFilter () {};
      DLLLOCAL virtual bool lessThan ( const QModelIndex & left, const QModelIndex & right ) const
        { return false; };
};

// class QoreQSortFilterProxyModelExtension : public QoreQAbstractProxyModelExtension {
//   protected:
//     //const QoreMethod *m_filterAcceptsColumn, *m_filterAcceptsRow, *m_lessThan;
// 
//     DLLLOCAL QoreQSortFilterProxyModelExtension(QoreObject *obj, QObject *qo) : QoreQAbstractProxyModelExtension(obj, qo) {
// //         const QoreClass *qc = obj->getClass();
// 
// //          m_filterAcceptsColumn = findMethod(qc, "filterAcceptsColumn");
// //          m_filterAcceptsRow = findMethod(qc, "filterAcceptsRow");
// //          m_lessThan = findMethod(qc, "lessThan");
//     }
// };

#endif  // _QORE_QT_QOREABSTRACTQSORTFILTERPROXYMODEL_H
