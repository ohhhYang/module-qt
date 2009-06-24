/*
 QC_QStringListModel.h
 
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

#ifndef _QORE_QT_QC_QSTRINGLISTMODEL_H

#define _QORE_QT_QC_QSTRINGLISTMODEL_H

#include <QStringListModel>
#include "QoreAbstractQStringListModel.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QSTRINGLISTMODEL;
DLLEXPORT extern QoreClass *QC_QStringListModel;
DLLEXPORT QoreClass *initQStringListModelClass(QoreClass *);

class myQStringListModel : public QStringListModel, public QoreQAbstractItemModelExtension {
#define QOREQTYPE QStringListModel
#define MYQOREQTYPE myQStringListModel
#define PARENTTYPE QAbstractItemModel
#include "qore-qt-metacode.h"
#define PARENT_IS_PRIVATE
#define HASCHILDREN_IS_PRIVATE
#define COLUMNCOUNT_IS_PRIVATE
#include "qore-qt-qabstractitemmodel-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQStringListModel(QoreObject *obj, QObject* parent = 0) : QStringListModel(parent), QoreQAbstractItemModelExtension(obj, this) {
      }
      DLLLOCAL myQStringListModel(QoreObject *obj, const QStringList& strings, QObject* parent = 0) : QStringListModel(strings, parent), QoreQAbstractItemModelExtension(obj, this) {
      }
};

typedef QoreQStringListModelBase<myQStringListModel, QoreAbstractQAbstractItemModel> QoreQStringListModelImpl;

class QoreQStringListModel : public QoreQStringListModelImpl {
   public:
      DLLLOCAL QoreQStringListModel(QoreObject *obj, QObject* parent = 0) : QoreQStringListModelImpl(new myQStringListModel(obj, parent)) { }
      DLLLOCAL QoreQStringListModel(QoreObject *obj, const QStringList& strings, QObject* parent = 0) : QoreQStringListModelImpl(new myQStringListModel(obj, strings, parent)) { }
};

typedef QoreQtQStringListModelBase<QStringListModel, QoreAbstractQAbstractItemModel> QoreQtQStringListModelImpl;

class QoreQtQStringListModel : public QoreQtQStringListModelImpl {
   public:
      DLLLOCAL QoreQtQStringListModel(QoreObject *obj, QStringListModel *qstringlistmodel) : QoreQtQStringListModelImpl(obj, qstringlistmodel) { }
};

#endif // _QORE_QT_QC_QSTRINGLISTMODEL_H
