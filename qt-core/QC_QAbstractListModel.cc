/*
 QC_QAbstractListModel.cc
 
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

#include "qt-core.h"

#include "QC_QAbstractListModel.h"

qore_classid_t CID_QABSTRACTLISTMODEL;
QoreClass *QC_QAbstractListModel = 0;

//QAbstractListModel ( QObject * parent = 0 )
static void QABSTRACTLISTMODEL_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QABSTRACTLISTMODEL, new QoreQAbstractListModel(self, parent ? parent->getQObject() : 0));
   return;
}

static void QABSTRACTLISTMODEL_copy(QoreObject *self, QoreObject *old, QoreQAbstractListModel *qalm, ExceptionSink *xsink) {
   xsink->raiseException("QABSTRACTLISTMODEL-COPY-ERROR", "objects of this class cannot be copied");
}

//virtual QModelIndex index ( int row, int column = 0, const QModelIndex & parent = QModelIndex() ) const
static AbstractQoreNode *QABSTRACTLISTMODEL_index(QoreObject *self, QoreAbstractQAbstractListModel *qalm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int column = !is_nothing(p) ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qalm->getQAbstractListModel()->index(row, column, *(static_cast<QModelIndex *>(parent)))));
}

QoreClass *initQAbstractListModelClass(QoreClass *qabstractitemmodel) {
   QC_QAbstractListModel = new QoreClass("QAbstractListModel", QDOM_GUI);
   CID_QABSTRACTLISTMODEL = QC_QAbstractListModel->getID();

   QC_QAbstractListModel->addBuiltinVirtualBaseClass(qabstractitemmodel);

   QC_QAbstractListModel->setConstructor(QABSTRACTLISTMODEL_constructor);
   QC_QAbstractListModel->setCopy((q_copy_t)QABSTRACTLISTMODEL_copy);

   QC_QAbstractListModel->addMethod("index",                       (q_method_t)QABSTRACTLISTMODEL_index);

   return QC_QAbstractListModel;
}
