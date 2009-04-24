/*
 QC_QAbstractTableModel.h
 
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

#ifndef _QORE_QT_QC_QABSTRACTTABLEMODEL_H

#define _QORE_QT_QC_QABSTRACTTABLEMODEL_H

#include <QAbstractTableModel>
#include "QoreAbstractQAbstractTableModel.h"

DLLEXPORT extern qore_classid_t CID_QABSTRACTTABLEMODEL;
DLLEXPORT extern QoreClass *QC_QAbstractTableModel;
DLLEXPORT QoreClass *initQAbstractTableModelClass(QoreClass *);

class myQAbstractTableModel : public QAbstractTableModel, public QoreQAbstractItemModelExtension {
#define QOREQTYPE QAbstractTableModel
#define MYQOREQTYPE myQAbstractTableModel
#define PARENTTYPE QAbstractItemModel
#include "qore-qt-metacode.h"
#define PARENT_IS_PRIVATE
#define HASCHILDREN_IS_PRIVATE
#include "qore-qt-qabstractitemmodel-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQAbstractTableModel(QoreObject *obj, QObject* parent = 0) : QAbstractTableModel(parent), QoreQAbstractItemModelExtension(obj, this) {
      }
};

typedef QoreQAbstractTableModelBase<myQAbstractTableModel, QoreAbstractQAbstractTableModel> QoreQAbstractTableModelImpl;

class QoreQAbstractTableModel : public QoreQAbstractTableModelImpl {
   public:
      DLLLOCAL QoreQAbstractTableModel(QoreObject *obj, QObject* parent = 0) : QoreQAbstractTableModelImpl(new myQAbstractTableModel(obj, parent)) { }
};

typedef QoreQtQAbstractTableModelBase<QAbstractTableModel, QoreAbstractQAbstractTableModel, QAbstractItemModel> QoreQtQAbstractTableModelImpl;

class QoreQtQAbstractTableModel : public QoreQtQAbstractTableModelImpl {
   public:
      DLLLOCAL QoreQtQAbstractTableModel(QoreObject *obj, QAbstractTableModel *qabstracttablemodel) : QoreQtQAbstractTableModelImpl(obj, qabstracttablemodel) { }
};

#endif // _QORE_QT_QC_QABSTRACTTABLEMODEL_H
