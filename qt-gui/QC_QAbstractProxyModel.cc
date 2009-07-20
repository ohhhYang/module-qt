/*
 QC_QAbstractProxyModel.cc
 
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

#include "qore-qt-gui.h"

#include "QC_QAbstractProxyModel.h"

qore_classid_t CID_QABSTRACTPROXYMODEL;
QoreClass *QC_QAbstractProxyModel = 0;

//QAbstractProxyModel ( QObject * parent = 0 )
static void QABSTRACTPROXYMODEL_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QABSTRACTPROXYMODEL, new QoreQAbstractProxyModel(self, parent ? parent->getQObject() : 0));
   return;
}

static void QABSTRACTPROXYMODEL_copy(QoreObject *self, QoreObject *old, QoreQAbstractProxyModel *qapm, ExceptionSink *xsink) {
   xsink->raiseException("QABSTRACTPROXYMODEL-COPY-ERROR", "objects of this class cannot be copied");
}

//virtual QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const = 0
static AbstractQoreNode *QABSTRACTPROXYMODEL_mapFromSource(QoreObject *self, QoreAbstractQAbstractProxyModel *qapm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *sourceIndex = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!sourceIndex) {
      if (!xsink->isException())
         xsink->raiseException("QABSTRACTPROXYMODEL-MAPFROMSOURCE-PARAM-ERROR", "expecting a QModelIndex object as first argument to QAbstractProxyModel::mapFromSource()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> sourceIndexHolder(static_cast<AbstractPrivateData *>(sourceIndex), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qapm->getQAbstractProxyModel()->mapFromSource(*(static_cast<QModelIndex *>(sourceIndex)))));
}

//virtual QItemSelection mapSelectionFromSource ( const QItemSelection & sourceSelection ) const
static AbstractQoreNode *QABSTRACTPROXYMODEL_mapSelectionFromSource(QoreObject *self, QoreAbstractQAbstractProxyModel *qapm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQItemSelection *sourceSelection = (p && p->getType() == NT_OBJECT) ? (QoreQItemSelection *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTION, xsink) : 0;
   if (!sourceSelection) {
      if (!xsink->isException())
         xsink->raiseException("QABSTRACTPROXYMODEL-MAPSELECTIONFROMSOURCE-PARAM-ERROR", "expecting a QItemSelection object as first argument to QAbstractProxyModel::mapSelectionFromSource()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> sourceSelectionHolder(static_cast<AbstractPrivateData *>(sourceSelection), xsink);
   return return_object(QC_QItemSelection, new QoreQItemSelection(qapm->getQAbstractProxyModel()->mapSelectionFromSource(*(static_cast<QItemSelection *>(sourceSelection)))));
}

//virtual QItemSelection mapSelectionToSource ( const QItemSelection & proxySelection ) const
static AbstractQoreNode *QABSTRACTPROXYMODEL_mapSelectionToSource(QoreObject *self, QoreAbstractQAbstractProxyModel *qapm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQItemSelection *proxySelection = (p && p->getType() == NT_OBJECT) ? (QoreQItemSelection *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTION, xsink) : 0;
   if (!proxySelection) {
      if (!xsink->isException())
         xsink->raiseException("QABSTRACTPROXYMODEL-MAPSELECTIONTOSOURCE-PARAM-ERROR", "expecting a QItemSelection object as first argument to QAbstractProxyModel::mapSelectionToSource()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> proxySelectionHolder(static_cast<AbstractPrivateData *>(proxySelection), xsink);
   return return_object(QC_QItemSelection, new QoreQItemSelection(qapm->getQAbstractProxyModel()->mapSelectionToSource(*(static_cast<QItemSelection *>(proxySelection)))));
}

//virtual QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const = 0
static AbstractQoreNode *QABSTRACTPROXYMODEL_mapToSource(QoreObject *self, QoreAbstractQAbstractProxyModel *qapm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *proxyIndex = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!proxyIndex) {
      if (!xsink->isException())
         xsink->raiseException("QABSTRACTPROXYMODEL-MAPTOSOURCE-PARAM-ERROR", "expecting a QModelIndex object as first argument to QAbstractProxyModel::mapToSource()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> proxyIndexHolder(static_cast<AbstractPrivateData *>(proxyIndex), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qapm->getQAbstractProxyModel()->mapToSource(*(static_cast<QModelIndex *>(proxyIndex)))));
}

//virtual void setSourceModel ( QAbstractItemModel * sourceModel )
static AbstractQoreNode *QABSTRACTPROXYMODEL_setSourceModel(QoreObject *self, QoreAbstractQAbstractProxyModel *qapm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQAbstractItemModel *sourceModel = (p && p->getType() == NT_OBJECT) ? (QoreQAbstractItemModel *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QABSTRACTITEMMODEL, xsink) : 0;
   if (!sourceModel) {
      if (!xsink->isException())
         xsink->raiseException("QABSTRACTPROXYMODEL-SETSOURCEMODEL-PARAM-ERROR", "expecting a QAbstractItemModel object as first argument to QAbstractProxyModel::setSourceModel()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> sourceModelHolder(static_cast<AbstractPrivateData *>(sourceModel), xsink);
   qapm->getQAbstractProxyModel()->setSourceModel(static_cast<QAbstractItemModel *>(sourceModel->getQAbstractItemModel()));
   return 0;
}

//QAbstractItemModel * sourceModel () const
static AbstractQoreNode *QABSTRACTPROXYMODEL_sourceModel(QoreObject *self, QoreAbstractQAbstractProxyModel *qapm, const QoreListNode *params, ExceptionSink *xsink) {
   QAbstractItemModel *qt_qobj = qapm->getQAbstractProxyModel()->sourceModel();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QAbstractItemModel, getProgram());
   QoreQtQAbstractItemModel *t_qobj = new QoreQtQAbstractItemModel(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QABSTRACTITEMMODEL, t_qobj);
   return rv_obj;
}

QoreClass *initQAbstractProxyModelClass(QoreClass *qabstractitemmodel) {
   QC_QAbstractProxyModel = new QoreClass("QAbstractProxyModel", QDOM_GUI);
   CID_QABSTRACTPROXYMODEL = QC_QAbstractProxyModel->getID();

   QC_QAbstractProxyModel->addBuiltinVirtualBaseClass(qabstractitemmodel);

   QC_QAbstractProxyModel->setConstructor(QABSTRACTPROXYMODEL_constructor);
   QC_QAbstractProxyModel->setCopy((q_copy_t)QABSTRACTPROXYMODEL_copy);

   QC_QAbstractProxyModel->addMethod("mapFromSource",               (q_method_t)QABSTRACTPROXYMODEL_mapFromSource);
   QC_QAbstractProxyModel->addMethod("mapSelectionFromSource",      (q_method_t)QABSTRACTPROXYMODEL_mapSelectionFromSource);
   QC_QAbstractProxyModel->addMethod("mapSelectionToSource",        (q_method_t)QABSTRACTPROXYMODEL_mapSelectionToSource);
   QC_QAbstractProxyModel->addMethod("mapToSource",                 (q_method_t)QABSTRACTPROXYMODEL_mapToSource);
   QC_QAbstractProxyModel->addMethod("setSourceModel",              (q_method_t)QABSTRACTPROXYMODEL_setSourceModel);
   QC_QAbstractProxyModel->addMethod("sourceModel",                 (q_method_t)QABSTRACTPROXYMODEL_sourceModel);

   return QC_QAbstractProxyModel;
}
