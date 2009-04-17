/*
 QC_QItemSelectionRange.cc
 
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

#include "QC_QItemSelectionRange.h"

qore_classid_t CID_QITEMSELECTIONRANGE;
QoreClass *QC_QItemSelectionRange = 0;

//QItemSelectionRange ()
//QItemSelectionRange ( const QItemSelectionRange & other )
//QItemSelectionRange ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
//QItemSelectionRange ( const QModelIndex & index )
static void QITEMSELECTIONRANGE_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QITEMSELECTIONRANGE, new QoreQItemSelectionRange());
      return;
   }

   const QoreObject *o = (p && p->getType() == NT_OBJECT) ? reinterpret_cast<const QoreObject *>(p) : 0;
   if (!o) {
      xsink->raiseException("QITEMSELECTIONRANGE-CONSTRUCTOR-ERROR", "expecting a QModelIndex object as the first argument to QItemSelectionRange::constructor()");
      return;
   }

   QoreQModelIndex *index = (QoreQModelIndex *)o->getReferencedPrivateData(CID_QMODELINDEX, xsink);
   if (!index) {
      if (!xsink->isException())
	 xsink->raiseException("QITEMSELECTIONRANGE-CONSTRUCTOR-PARAM-ERROR", "QItemSelectionRange::constructor() does not know how to handle arguments of class '%s' as passed as the first argument", o->getClassName());
      return;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);

   p = get_param(params, 1);
   QoreQModelIndex *bottomRight = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!bottomRight) {
      if (*xsink)
	 return;

      self->setPrivate(CID_QITEMSELECTIONRANGE, new QoreQItemSelectionRange(*(static_cast<QModelIndex *>(index))));
      return;
   }

   ReferenceHolder<AbstractPrivateData> bottomRightHolder(static_cast<AbstractPrivateData *>(bottomRight), xsink);
   self->setPrivate(CID_QITEMSELECTIONRANGE, new QoreQItemSelectionRange(*(static_cast<QModelIndex *>(index)), *(static_cast<QModelIndex *>(bottomRight))));
}

static void QITEMSELECTIONRANGE_copy(QoreObject *self, QoreObject *old, QoreQItemSelectionRange *qisr, ExceptionSink *xsink) {
   self->setPrivate(CID_QITEMSELECTIONRANGE, new QoreQItemSelectionRange(*qisr));
}

//int bottom () const
static AbstractQoreNode *QITEMSELECTIONRANGE_bottom(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qisr->bottom());
}

//QModelIndex bottomRight () const
static AbstractQoreNode *QITEMSELECTIONRANGE_bottomRight(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QModelIndex, new QoreQModelIndex(qisr->bottomRight()));
}

//bool contains ( const QModelIndex & index ) const
//bool contains ( int row, int column, const QModelIndex & parentIndex ) const
static AbstractQoreNode *QITEMSELECTIONRANGE_contains(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      const QoreObject *o = reinterpret_cast<const QoreObject *>(p);
      QoreQModelIndex *index = (QoreQModelIndex *)o->getReferencedPrivateData(CID_QMODELINDEX, xsink);
      if (!index) {
         if (!xsink->isException())
            xsink->raiseException("QITEMSELECTIONRANGE-CONTAINS-PARAM-ERROR", "QItemSelectionRange::contains() does not know how to handle arguments of class '%s' as passed as the first argument", o->getClassName());
         return 0;
      }
      ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
      return get_bool_node(qisr->contains(*(static_cast<QModelIndex *>(index))));
   }

   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QoreQModelIndex *parentIndex = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parentIndex) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONRANGE-CONTAINS-PARAM-ERROR", "this version of QItemSelectionRange::contains() expects an object derived from QModelIndex as the third argument");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentIndexHolder(static_cast<AbstractPrivateData *>(parentIndex), xsink);
   return get_bool_node(qisr->contains(row, column, *(static_cast<QModelIndex *>(parentIndex))));
}

//int height () const
static AbstractQoreNode *QITEMSELECTIONRANGE_height(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qisr->height());
}

/*
//QModelIndexList indexes () const
static AbstractQoreNode *QITEMSELECTIONRANGE_indexes(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   ??? return new QoreBigIntNode(qisr->indexes());
}
*/

//QItemSelectionRange intersected ( const QItemSelectionRange & other ) const
static AbstractQoreNode *QITEMSELECTIONRANGE_intersected(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQItemSelectionRange *other = (p && p->getType() == NT_OBJECT) ? (QoreQItemSelectionRange *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTIONRANGE, xsink) : 0;
   if (!other) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONRANGE-INTERSECTED-PARAM-ERROR", "expecting a QItemSelectionRange object as first argument to QItemSelectionRange::intersected()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> otherHolder(static_cast<AbstractPrivateData *>(other), xsink);
   return return_object(self->getClass(CID_QITEMSELECTIONRANGE), new QoreQItemSelectionRange(qisr->intersected(*(static_cast<QItemSelectionRange *>(other)))));
}

//bool intersects ( const QItemSelectionRange & other ) const
static AbstractQoreNode *QITEMSELECTIONRANGE_intersects(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQItemSelectionRange *other = (p && p->getType() == NT_OBJECT) ? (QoreQItemSelectionRange *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTIONRANGE, xsink) : 0;
   if (!other) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONRANGE-INTERSECTS-PARAM-ERROR", "expecting a QItemSelectionRange object as first argument to QItemSelectionRange::intersects()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> otherHolder(static_cast<AbstractPrivateData *>(other), xsink);
   return get_bool_node(qisr->intersects(*(static_cast<QItemSelectionRange *>(other))));
}

//bool isValid () const
static AbstractQoreNode *QITEMSELECTIONRANGE_isValid(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qisr->isValid());
}

//int left () const
static AbstractQoreNode *QITEMSELECTIONRANGE_left(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qisr->left());
}

//const QAbstractItemModel * model () const
static AbstractQoreNode *QITEMSELECTIONRANGE_model(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   QAbstractItemModel *qt_qobj = const_cast<QAbstractItemModel *>(qisr->model());
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

//QModelIndex parent () const
static AbstractQoreNode *QITEMSELECTIONRANGE_parent(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QModelIndex, new QoreQModelIndex(qisr->parent()));
}

//int right () const
static AbstractQoreNode *QITEMSELECTIONRANGE_right(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qisr->right());
}

//int top () const
static AbstractQoreNode *QITEMSELECTIONRANGE_top(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qisr->top());
}

//QModelIndex topLeft () const
static AbstractQoreNode *QITEMSELECTIONRANGE_topLeft(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QModelIndex, new QoreQModelIndex(qisr->topLeft()));
}

//int width () const
static AbstractQoreNode *QITEMSELECTIONRANGE_width(QoreObject *self, QoreQItemSelectionRange *qisr, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qisr->width());
}

QoreClass *initQItemSelectionRangeClass() {
   QC_QItemSelectionRange = new QoreClass("QItemSelectionRange", QDOM_GUI);
   CID_QITEMSELECTIONRANGE = QC_QItemSelectionRange->getID();

   QC_QItemSelectionRange->setConstructor(QITEMSELECTIONRANGE_constructor);
   QC_QItemSelectionRange->setCopy((q_copy_t)QITEMSELECTIONRANGE_copy);

   QC_QItemSelectionRange->addMethod("bottom",                      (q_method_t)QITEMSELECTIONRANGE_bottom);
   QC_QItemSelectionRange->addMethod("bottomRight",                 (q_method_t)QITEMSELECTIONRANGE_bottomRight);
   QC_QItemSelectionRange->addMethod("contains",                    (q_method_t)QITEMSELECTIONRANGE_contains);
   QC_QItemSelectionRange->addMethod("height",                      (q_method_t)QITEMSELECTIONRANGE_height);
   //QC_QItemSelectionRange->addMethod("indexes",                     (q_method_t)QITEMSELECTIONRANGE_indexes);
   QC_QItemSelectionRange->addMethod("intersected",                 (q_method_t)QITEMSELECTIONRANGE_intersected);
   QC_QItemSelectionRange->addMethod("intersects",                  (q_method_t)QITEMSELECTIONRANGE_intersects);
   QC_QItemSelectionRange->addMethod("isValid",                     (q_method_t)QITEMSELECTIONRANGE_isValid);
   QC_QItemSelectionRange->addMethod("left",                        (q_method_t)QITEMSELECTIONRANGE_left);
   QC_QItemSelectionRange->addMethod("model",                       (q_method_t)QITEMSELECTIONRANGE_model);
   QC_QItemSelectionRange->addMethod("parent",                      (q_method_t)QITEMSELECTIONRANGE_parent);
   QC_QItemSelectionRange->addMethod("right",                       (q_method_t)QITEMSELECTIONRANGE_right);
   QC_QItemSelectionRange->addMethod("top",                         (q_method_t)QITEMSELECTIONRANGE_top);
   QC_QItemSelectionRange->addMethod("topLeft",                     (q_method_t)QITEMSELECTIONRANGE_topLeft);
   QC_QItemSelectionRange->addMethod("width",                       (q_method_t)QITEMSELECTIONRANGE_width);

   return QC_QItemSelectionRange;
}
