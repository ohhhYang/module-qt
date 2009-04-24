/*
 QC_QAbstractTableModel.cc
 
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

#include "QC_QAbstractTableModel.h"

qore_classid_t CID_QABSTRACTTABLEMODEL;
QoreClass *QC_QAbstractTableModel = 0;

//QAbstractTableModel ( QObject * parent = 0 )
static void QABSTRACTTABLEMODEL_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QABSTRACTTABLEMODEL, new QoreQAbstractTableModel(self, parent ? parent->getQObject() : 0));
   return;
}

static void QABSTRACTTABLEMODEL_copy(QoreObject *self, QoreObject *old, QoreQAbstractTableModel *qatm, ExceptionSink *xsink) {
   xsink->raiseException("QABSTRACTTABLEMODEL-COPY-ERROR", "objects of this class cannot be copied");
}

//virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const
static AbstractQoreNode *QABSTRACTTABLEMODEL_index(QoreObject *self, QoreAbstractQAbstractTableModel *qatm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qatm->getQAbstractTableModel()->index(row, column, *(static_cast<QModelIndex *>(parent)))));
}

QoreClass *initQAbstractTableModelClass(QoreClass *qabstractitemmodel) {
   QC_QAbstractTableModel = new QoreClass("QAbstractTableModel", QDOM_GUI);
   CID_QABSTRACTTABLEMODEL = QC_QAbstractTableModel->getID();

   QC_QAbstractTableModel->addBuiltinVirtualBaseClass(qabstractitemmodel);

   QC_QAbstractTableModel->setConstructor(QABSTRACTTABLEMODEL_constructor);
   QC_QAbstractTableModel->setCopy((q_copy_t)QABSTRACTTABLEMODEL_copy);

   QC_QAbstractTableModel->addMethod("index",                       (q_method_t)QABSTRACTTABLEMODEL_index);

   return QC_QAbstractTableModel;
}
