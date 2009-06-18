/*
 QC_QSpacerItem.cc
 
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

#include "QC_QSpacerItem.h"

qore_classid_t CID_QSPACERITEM;
QoreClass *QC_QSpacerItem = 0;

//# QSpacerItem ( int w, int h, QSizePolicy::Policy hPolicy = QSizePolicy::Minimum, QSizePolicy::Policy vPolicy = QSizePolicy::Minimum )
static void QSPACERITEM_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int w = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int h = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QSizePolicy::Policy hPolicy = !is_nothing(p) ? (QSizePolicy::Policy)p->getAsInt() : QSizePolicy::Minimum;
   p = get_param(params, 3);
   QSizePolicy::Policy vPolicy = !is_nothing(p) ? (QSizePolicy::Policy)p->getAsInt() : QSizePolicy::Minimum;
   self->setPrivate(CID_QSPACERITEM, new QoreQSpacerItem(self, w, h, hPolicy, vPolicy));
   return;
}

static void QSPACERITEM_copy(QoreObject *self, QoreObject *old, QoreQSpacerItem *qsi, ExceptionSink *xsink) {
   xsink->raiseException("QSPACERITEM-COPY-ERROR", "objects of this class cannot be copied");
}

//void changeSize ( int w, int h, QSizePolicy::Policy hPolicy = QSizePolicy::Minimum, QSizePolicy::Policy vPolicy = QSizePolicy::Minimum )
static AbstractQoreNode *QSPACERITEM_changeSize(QoreObject *self, QoreQSpacerItem *qsi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int w = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int h = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QSizePolicy::Policy hPolicy = !is_nothing(p) ? (QSizePolicy::Policy)p->getAsInt() : QSizePolicy::Minimum;
   p = get_param(params, 3);
   QSizePolicy::Policy vPolicy = !is_nothing(p) ? (QSizePolicy::Policy)p->getAsInt() : QSizePolicy::Minimum;
   qsi->changeSize(w, h, hPolicy, vPolicy);
   return 0;
}

//virtual bool isEmpty () const
static AbstractQoreNode *QSPACERITEM_isEmpty(QoreObject *self, QoreQSpacerItem *qsi, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qsi->parent_isEmpty());
}

//virtual QSpacerItem * spacerItem ()
static AbstractQoreNode *QSPACERITEM_spacerItem(QoreObject *self, QoreQSpacerItem *qsi, const QoreListNode *params, ExceptionSink *xsink) {
   return self->refSelf();
}

QoreClass *initQSpacerItemClass(QoreClass *qlayoutitem) {
   QC_QSpacerItem = new QoreClass("QSpacerItem", QDOM_GUI);
   CID_QSPACERITEM = QC_QSpacerItem->getID();

   QC_QSpacerItem->addBuiltinVirtualBaseClass(qlayoutitem);

   QC_QSpacerItem->setConstructor(QSPACERITEM_constructor);
   QC_QSpacerItem->setCopy((q_copy_t)QSPACERITEM_copy);

   QC_QSpacerItem->addMethod("changeSize",                  (q_method_t)QSPACERITEM_changeSize);
   QC_QSpacerItem->addMethod("isEmpty",                     (q_method_t)QSPACERITEM_isEmpty);
   QC_QSpacerItem->addMethod("spacerItem",                  (q_method_t)QSPACERITEM_spacerItem);

   return QC_QSpacerItem;
}
