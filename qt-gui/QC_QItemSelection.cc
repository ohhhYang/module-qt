/*
 QC_QItemSelection.cc
 
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

#include "qore-qt-gui.h"

#include "QC_QItemSelection.h"

qore_classid_t CID_QITEMSELECTION;
QoreClass *QC_QItemSelection = 0;

//# QItemSelection ()
//QItemSelection ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
static void QITEMSELECTION_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QITEMSELECTION, new QoreQItemSelection());
      return;
   }
   QoreQModelIndex *topLeft = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!topLeft) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTION-CONSTRUCTOR-PARAM-ERROR", "this version of QItemSelection::constructor() expects an object derived from QModelIndex as the first argument");
      return;
   }
   ReferenceHolder<AbstractPrivateData> topLeftHolder(static_cast<AbstractPrivateData *>(topLeft), xsink);
      p = get_param(params, 1);
      QoreQModelIndex *bottomRight = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
      if (!bottomRight) {
         if (!xsink->isException())
            xsink->raiseException("QITEMSELECTION-CONSTRUCTOR-PARAM-ERROR", "this version of QItemSelection::constructor() expects an object derived from QModelIndex as the second argument");
         return;
      }
      ReferenceHolder<AbstractPrivateData> bottomRightHolder(static_cast<AbstractPrivateData *>(bottomRight), xsink);
      self->setPrivate(CID_QITEMSELECTION, new QoreQItemSelection(*(static_cast<QModelIndex *>(topLeft)), *(static_cast<QModelIndex *>(bottomRight))));
      return;
}

static void QITEMSELECTION_copy(QoreObject *self, QoreObject *old, QoreQItemSelection *qis, ExceptionSink *xsink) {
   xsink->raiseException("QITEMSELECTION-COPY-ERROR", "objects of this class cannot be copied");
}

//bool contains ( const QModelIndex & index ) const
static AbstractQoreNode *QITEMSELECTION_contains(QoreObject *self, QoreQItemSelection *qis, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTION-CONTAINS-PARAM-ERROR", "expecting a QModelIndex object as first argument to QItemSelection::contains()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return get_bool_node(qis->contains(*(static_cast<QModelIndex *>(index))));
}

//QModelIndexList indexes () const
static AbstractQoreNode *QITEMSELECTION_indexes(QoreObject *self, QoreQItemSelection *qis, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qmodelindexlist(qis->indexes());
}

//void merge ( const QItemSelection & other, QItemSelectionModel::SelectionFlags command )
static AbstractQoreNode *QITEMSELECTION_merge(QoreObject *self, QoreQItemSelection *qis, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQItemSelection *other = (p && p->getType() == NT_OBJECT) ? (QoreQItemSelection *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTION, xsink) : 0;
   if (!other) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTION-MERGE-PARAM-ERROR", "expecting a QItemSelection object as first argument to QItemSelection::merge()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> otherHolder(static_cast<AbstractPrivateData *>(other), xsink);
   p = get_param(params, 1);
   QItemSelectionModel::SelectionFlags command = (QItemSelectionModel::SelectionFlags)(p ? p->getAsInt() : 0);
   qis->merge(*(static_cast<QItemSelection *>(other)), command);
   return 0;
}

//void select ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
static AbstractQoreNode *QITEMSELECTION_select(QoreObject *self, QoreQItemSelection *qis, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *topLeft = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!topLeft) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTION-SELECT-PARAM-ERROR", "expecting a QModelIndex object as first argument to QItemSelection::select()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> topLeftHolder(static_cast<AbstractPrivateData *>(topLeft), xsink);
   p = get_param(params, 1);
   QoreQModelIndex *bottomRight = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!bottomRight) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTION-SELECT-PARAM-ERROR", "expecting a QModelIndex object as second argument to QItemSelection::select()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> bottomRightHolder(static_cast<AbstractPrivateData *>(bottomRight), xsink);
   qis->select(*(static_cast<QModelIndex *>(topLeft)), *(static_cast<QModelIndex *>(bottomRight)));
   return 0;
}

QoreClass *initQItemSelectionClass() {
   QC_QItemSelection = new QoreClass("QItemSelection", QDOM_GUI);
   CID_QITEMSELECTION = QC_QItemSelection->getID();

   QC_QItemSelection->setConstructor(QITEMSELECTION_constructor);
   QC_QItemSelection->setCopy((q_copy_t)QITEMSELECTION_copy);

   QC_QItemSelection->addMethod("contains",                    (q_method_t)QITEMSELECTION_contains);
   QC_QItemSelection->addMethod("indexes",                     (q_method_t)QITEMSELECTION_indexes);
   QC_QItemSelection->addMethod("merge",                       (q_method_t)QITEMSELECTION_merge);
   QC_QItemSelection->addMethod("select",                      (q_method_t)QITEMSELECTION_select);

   return QC_QItemSelection;
}
