/*
 QoreAbstractQTreeWidgetItem.h
 
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

#ifndef _QORE_QT_QOREABSTRACTQTREEWIDGETITEM_H

#define _QORE_QT_QOREABSTRACTQTREEWIDGETITEM_H

class QoreAbstractQTreeWidgetItem {
   public:
      DLLLOCAL virtual QTreeWidgetItem *getQTreeWidgetItem() const = 0;
};

template<typename T, typename V>
class QoreQTreeWidgetItemBase : public QoreBase<T, V> {
   public:
      DLLLOCAL QoreQTreeWidgetItemBase(T *qo) : QoreBase<T, V>(qo) {
      }

      DLLLOCAL virtual QTreeWidgetItem *getQTreeWidgetItem() const {
         return static_cast<QTreeWidgetItem *>(&(*this->qobj));
      }
};

template<typename T, typename V>
class QoreQtQTreeWidgetItemBase : public QoreQtBase<T, V> {
   public:
      DLLLOCAL QoreQtQTreeWidgetItemBase(QoreObject *obj, T *qo) : QoreQtBase<T, V>(obj, qo) {
      }

      DLLLOCAL virtual QTreeWidgetItem *getQTreeWidgetItem() const {
         return this->qobj;
      }
};

#endif  // _QORE_QT_QOREABSTRACTQTREEWIDGETITEM_H
