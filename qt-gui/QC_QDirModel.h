/*
 QC_QDirModel.h
 
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

#ifndef _QORE_QT_QC_QDIRMODEL_H

#define _QORE_QT_QC_QDIRMODEL_H

#include <QDirModel>
#include "QoreAbstractQAbstractItemModel.h"
#include "qore-qt-events.h"

#include <QC_QMimeData.h>

DLLEXPORT extern qore_classid_t CID_QDIRMODEL;
DLLEXPORT extern QoreClass *QC_QDirModel;
DLLEXPORT QoreNamespace *initQDirModelNS(QoreClass *);

class myQDirModel : public QDirModel, public QoreQAbstractItemModelExtension {
#define QOREQTYPE QDirModel
#define MYQOREQTYPE myQDirModel
#include "qore-qt-metacode.h"
#include "qore-qt-qabstractitemmodel-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQDirModel(QoreObject *obj, const QStringList& nameFilters, QDir::Filters filters, QDir::SortFlags sort, QObject* parent = 0) : QDirModel(nameFilters, filters, sort, parent), QoreQAbstractItemModelExtension(obj, this) {
      }
      DLLLOCAL myQDirModel(QoreObject *obj, QObject* parent = 0) : QDirModel(parent), QoreQAbstractItemModelExtension(obj, this) {
      }
};

typedef QoreQAbstractItemModelBase<myQDirModel, QoreAbstractQAbstractItemModel> QoreQDirModelImpl;

class QoreQDirModel : public QoreQDirModelImpl {
   public:
      DLLLOCAL QoreQDirModel(QoreObject *obj, const QStringList& nameFilters, QDir::Filters filters, QDir::SortFlags sort, QObject* parent = 0) : QoreQDirModelImpl(new myQDirModel(obj, nameFilters, filters, sort, parent)) { }
      DLLLOCAL QoreQDirModel(QoreObject *obj, QObject* parent = 0) : QoreQDirModelImpl(new myQDirModel(obj, parent)) { }
};

typedef QoreQtQAbstractItemModelBase<QDirModel, QoreAbstractQAbstractItemModel> QoreQtQDirModelImpl;

class QoreQtQDirModel : public QoreQtQDirModelImpl {
   public:
      DLLLOCAL QoreQtQDirModel(QoreObject *obj, QDirModel *qdirmodel) : QoreQtQDirModelImpl(obj, qdirmodel) { }
};

#endif // _QORE_QT_QC_QDIRMODEL_H
