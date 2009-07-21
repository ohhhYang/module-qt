/*
 QC_QSortFilterProxyModel.h
 
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

#ifndef _QORE_QT_QC_QSORTFILTERPROXYMODEL_H

#define _QORE_QT_QC_QSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "QoreAbstractQSortFilterProxyModel.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QSORTFILTERPROXYMODEL;
DLLEXPORT extern QoreClass *QC_QSortFilterProxyModel;
DLLEXPORT QoreClass *initQSortFilterProxyModelClass(QoreClass *);

class myQSortFilterProxyModel : public QSortFilterProxyModel, public QoreQSortFilterProxyModelExtension {
#define QOREQTYPE QSortFilterProxyModel
#define MYQOREQTYPE myQSortFilterProxyModel
#include "qore-qt-metacode.h"
#include "qore-qt-qabstractitemmodel-methods.h"
#include "qore-qt-qabstractproxymodel-methods.h"
#include "qore-qt-qsortfilterproxymodel-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQSortFilterProxyModel(QoreObject *obj, QObject* parent = 0) : QSortFilterProxyModel(parent), QoreQSortFilterProxyModelExtension(obj, this) {
      }
};

typedef QoreQAbstractProxyModelBase<myQSortFilterProxyModel, QoreAbstractQAbstractProxyModel> QoreQSortFilterProxyModelImpl;

class QoreQSortFilterProxyModel : public QoreQSortFilterProxyModelImpl {
   public:
      DLLLOCAL QoreQSortFilterProxyModel(QoreObject *obj, QObject* parent = 0) : QoreQSortFilterProxyModelImpl(new myQSortFilterProxyModel(obj, parent)) { }
};

typedef QoreQtQAbstractProxyModelBase<QSortFilterProxyModel, QoreAbstractQAbstractProxyModel> QoreQtQSortFilterProxyModelImpl;

class QoreQtQSortFilterProxyModel : public QoreQtQSortFilterProxyModelImpl {
   public:
      DLLLOCAL QoreQtQSortFilterProxyModel(QoreObject *obj, QSortFilterProxyModel *qsortfilterproxymodel) : QoreQtQSortFilterProxyModelImpl(obj, qsortfilterproxymodel) { }
};

#endif // _QORE_QT_QC_QSORTFILTERPROXYMODEL_H
