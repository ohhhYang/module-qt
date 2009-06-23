/*
 QC_QAbstractListModel.h
 
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

#ifndef _QORE_QT_QC_QABSTRACTLISTMODEL_H

#define _QORE_QT_QC_QABSTRACTLISTMODEL_H

#include <QAbstractListModel>
#include "QoreAbstractQAbstractListModel.h"

DLLEXPORT extern qore_classid_t CID_QABSTRACTLISTMODEL;
DLLEXPORT extern QoreClass *QC_QAbstractListModel;
DLLEXPORT QoreClass *initQAbstractListModelClass(QoreClass *);

class myQAbstractListModel : public QAbstractListModel, public QoreQAbstractItemModelExtension {
#define QOREQTYPE QAbstractListModel
#define MYQOREQTYPE myQAbstractListModel
#define PARENTTYPE QAbstractItemModel
#include "qore-qt-metacode.h"
#define PARENT_IS_PRIVATE
#define HASCHILDREN_IS_PRIVATE
#define COLUMNCOUNT_IS_PRIVATE
#include "qore-qt-qabstractitemmodel-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQAbstractListModel(QoreObject *obj, QObject* parent = 0) : QAbstractListModel(parent), QoreQAbstractItemModelExtension(obj, this) {
      }
};

typedef QoreQAbstractItemModelBase<myQAbstractListModel, QoreAbstractQAbstractItemModel> QoreQAbstractListModelImpl;

class QoreQAbstractListModel : public QoreQAbstractListModelImpl {
   public:
      DLLLOCAL QoreQAbstractListModel(QoreObject *obj, QObject* parent = 0) : QoreQAbstractListModelImpl(new myQAbstractListModel(obj, parent)) { }
};

typedef QoreQtQAbstractItemModelBase<QAbstractListModel, QoreAbstractQAbstractItemModel> QoreQtQAbstractListModelImpl;

class QoreQtQAbstractListModel : public QoreQtQAbstractListModelImpl {
   public:
      DLLLOCAL QoreQtQAbstractListModel(QoreObject *obj, QAbstractListModel *qabstractlistmodel) : QoreQtQAbstractListModelImpl(obj, qabstractlistmodel) { }
};

#endif // _QORE_QT_QC_QABSTRACTLISTMODEL_H
