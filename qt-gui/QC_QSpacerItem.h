/*
 QC_QSpacerItem.h
 
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

#ifndef _QORE_QT_QC_QSPACERITEM_H

#define _QORE_QT_QC_QSPACERITEM_H

#include <QSpacerItem>
#include "QoreAbstractQLayoutItem.h"
#include "QC_QLayout.h"

DLLEXPORT extern qore_classid_t CID_QSPACERITEM;
DLLEXPORT extern QoreClass *QC_QSpacerItem;
DLLEXPORT QoreClass *initQSpacerItemClass(QoreClass *);

class QoreQSpacerItem : public QoreAbstractQLayoutItemData, public QSpacerItem, public QoreQLayoutItemExtension {
#define QOREQTYPE QSpacerItem
#include "qore-qt-qlayoutitem-methods.h"
#undef QOREQTYPE

   public:
      DLLLOCAL QoreQSpacerItem(QoreObject *obj, int w, int h, QSizePolicy::Policy hPolicy = QSizePolicy::Minimum, QSizePolicy::Policy vPolicy = QSizePolicy::Minimum) : QSpacerItem(w, h, hPolicy, vPolicy), QoreQLayoutItemExtension(obj) { }

      DLLLOCAL virtual QLayoutItem *getQLayoutItem() const {
         return const_cast<QLayoutItem *>(static_cast<const QLayoutItem *>(this));
      }
};

#endif // _QORE_QT_QC_QSPACERITEM_H
