/*
 QC_QItemDelegate.h
 
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

#ifndef _QORE_QT_QC_QITEMDELEGATE_H

#define _QORE_QT_QC_QITEMDELEGATE_H

#include <QItemDelegate>
#include "QoreAbstractQItemDelegate.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QITEMDELEGATE;
DLLEXPORT extern class QoreClass *QC_QItemDelegate;

DLLEXPORT class QoreClass *initQItemDelegateClass(QoreClass *);

class myQItemDelegate : public QItemDelegate, public QoreQAbstractItemDelegateExtension
{
#define QOREQTYPE QItemDelegate
#define MYQOREQTYPE myQItemDelegate
#include "qore-qt-metacode.h"
#include "qore-qt-qabstractitemdelegate-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
   DLLLOCAL myQItemDelegate(QoreObject *obj, QObject* parent = 0) : QItemDelegate(parent), QoreQAbstractItemDelegateExtension(obj, this)
      {
         
      }
};

typedef QoreQItemDelegateBase<myQItemDelegate, QoreAbstractQItemDelegate> QoreQItemDelegateImpl;

class QoreQItemDelegate : public QoreQItemDelegateImpl
{
   public:
      DLLLOCAL QoreQItemDelegate(QoreObject *obj, QObject* parent = 0) : QoreQItemDelegateImpl(new myQItemDelegate(obj, parent))
      {
      }
};

#endif // _QORE_QT_QC_QITEMDELEGATE_H
