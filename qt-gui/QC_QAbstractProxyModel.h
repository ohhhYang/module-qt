/*
 QC_QAbstractProxyModel.h
 
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

#ifndef _QORE_QT_QC_QABSTRACTPROXYMODEL_H

#define _QORE_QT_QC_QABSTRACTPROXYMODEL_H

#include <QAbstractProxyModel>
#include "QoreAbstractQAbstractProxyModel.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QABSTRACTPROXYMODEL;
DLLEXPORT extern QoreClass *QC_QAbstractProxyModel;
DLLEXPORT QoreClass *initQAbstractProxyModelClass(QoreClass *);

class myQAbstractProxyModel : public QAbstractProxyModel, public QoreQAbstractProxyModelExtension {
#define QOREQTYPE QAbstractProxyModel
#define MYQOREQTYPE myQAbstractProxyModel
// mandatory for columnCount virtual method
#undef COLUMNCOUNT_IS_PRIVATE
#include "qore-qt-metacode.h"
// mandatory for parent's virtual methods
#include "qore-qt-qabstractitemmodel-methods.h"
// mandatory for proxymodel's virtual methods
#include "qore-qt-qabstractproxymodel-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQAbstractProxyModel(QoreObject *obj, QObject* parent = 0) : QAbstractProxyModel(parent), QoreQAbstractProxyModelExtension(obj, this) {
      }
};

typedef QoreQAbstractItemModelBase<myQAbstractProxyModel, QoreAbstractQAbstractItemModel> QoreQAbstractProxyModelImpl;

class QoreQAbstractProxyModel : public QoreQAbstractProxyModelImpl {
   public:
      DLLLOCAL QoreQAbstractProxyModel(QoreObject *obj, QObject* parent = 0) : QoreQAbstractProxyModelImpl(new myQAbstractProxyModel(obj, parent)) { }
};

typedef QoreQtQAbstractItemModelBase<QAbstractProxyModel, QoreAbstractQAbstractItemModel> QoreQtQAbstractProxyModelImpl;

class QoreQtQAbstractProxyModel : public QoreQtQAbstractProxyModelImpl {
   public:
      DLLLOCAL QoreQtQAbstractProxyModel(QoreObject *obj, QAbstractProxyModel *qabstractproxymodel) : QoreQtQAbstractProxyModelImpl(obj, qabstractproxymodel) { }
};

#endif // _QORE_QT_QC_QABSTRACTPROXYMODEL_H
