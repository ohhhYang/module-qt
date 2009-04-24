/*
 QC_QItemSelectionModel.h
 
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

#ifndef _QORE_QT_QC_QITEMSELECTIONMODEL_H

#define _QORE_QT_QC_QITEMSELECTIONMODEL_H

#include <QItemSelectionModel>
#include "QoreAbstractQObject.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QITEMSELECTIONMODEL;
DLLEXPORT extern QoreClass *QC_QItemSelectionModel;
DLLEXPORT QoreNamespace *initQItemSelectionModelNS(QoreClass *);

class myQItemSelectionModel : public QItemSelectionModel, public QoreQObjectExtension {
#define QOREQTYPE QItemSelectionModel
#define MYQOREQTYPE myQItemSelectionModel
#include "qore-qt-metacode.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQItemSelectionModel(QoreObject *obj, QAbstractItemModel* model) : QItemSelectionModel(model), QoreQObjectExtension(obj, this) {
      }
      DLLLOCAL myQItemSelectionModel(QoreObject *obj, QAbstractItemModel* model, QObject* parent) : QItemSelectionModel(model, parent), QoreQObjectExtension(obj, this) {
      }

      DLLLOCAL void parent_emitSelectionChanged ( const QItemSelection & newSelection, const QItemSelection & oldSelection ) {
	 emitSelectionChanged(newSelection, oldSelection);
      }
};

typedef QoreQObjectBase<myQItemSelectionModel, QoreAbstractQObject> QoreQItemSelectionModelImpl;

class QoreQItemSelectionModel : public QoreQItemSelectionModelImpl {
   public:
      DLLLOCAL QoreQItemSelectionModel(QoreObject *obj, QAbstractItemModel* model) : QoreQItemSelectionModelImpl(new myQItemSelectionModel(obj, model)) { }
      DLLLOCAL QoreQItemSelectionModel(QoreObject *obj, QAbstractItemModel* model, QObject* parent) : QoreQItemSelectionModelImpl(new myQItemSelectionModel(obj, model, parent)) { }

      DLLLOCAL void emitSelectionChanged ( const QItemSelection & newSelection, const QItemSelection & oldSelection ) {
	 qobj->parent_emitSelectionChanged(newSelection, oldSelection);
      }

};

typedef QoreQtQObjectBase<QItemSelectionModel, QoreAbstractQObject> QoreQtQItemSelectionModelImpl;

class QoreQtQItemSelectionModel : public QoreQtQItemSelectionModelImpl {
   public:
      DLLLOCAL QoreQtQItemSelectionModel(QoreObject *obj, QItemSelectionModel *qitemselectionmodel) : QoreQtQItemSelectionModelImpl(obj, qitemselectionmodel) { }
};

#endif // _QORE_QT_QC_QITEMSELECTIONMODEL_H
