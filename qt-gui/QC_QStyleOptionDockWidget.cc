/*
 QC_QStyleOptionDockWidget.cc
 
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

#include "QC_QStyleOptionDockWidget.h"

qore_classid_t CID_QSTYLEOPTIONDOCKWIDGET;
QoreClass *QC_QStyleOptionDockWidget = 0;

//bool movable
//QString title

int QStyleOptionDockWidget_Notification(QoreObject *obj, QStyleOptionDockWidget *qsodw, const char *mem, ExceptionSink *xsink) {
   AbstractQoreNode *p;

   if (!strcmp(mem, "closable")) {
      AutoVLock vl(xsink);
      p = obj->getMemberValueNoMethod(mem, &vl, xsink);
      if (*xsink)
         return 0;

      qsodw->closable = p ? p->getAsBool() : false;
      return 0;
   }

   if (!strcmp(mem, "floatable")) {
      AutoVLock vl(xsink);
      p = obj->getMemberValueNoMethod(mem, &vl, xsink);
      if (*xsink)
         return 0;

      qsodw->floatable = p ? p->getAsBool() : false;
      return 0;
   }
   return -1;
}

AbstractQoreNode *QStyleOptionDockWidget_MemberGate(QStyleOptionDockWidget *qsodw, const char *mem) {
   if (!strcmp(mem, "closeable"))
      return get_bool_node(qsodw->closable);

   if (!strcmp(mem, "floatable"))
      return get_bool_node(qsodw->floatable);

   if (!strcmp(mem, "movable"))
      return get_bool_node(qsodw->movable);

   if (!strcmp(mem, "title"))
      return new QoreStringNode(qsodw->title.toUtf8().data(), QCS_UTF8);

   return 0;
}

static AbstractQoreNode *QSTYLEOPTIONDOCKWIDGET_memberNotification(QoreObject *self, QoreQStyleOptionDockWidget *qsodw, const QoreListNode *params, ExceptionSink *xsink) {
   const QoreStringNode *str = test_string_param(params, 0);
   if (!str || !str->strlen())
      return 0;

   const char *member = str->getBuffer();
   if (!QStyleOptionDockWidget_Notification(self, qsodw, member, xsink) || *xsink)
      return 0;

   QStyleOption_Notification(self, qsodw, member, xsink);
   return 0;
}

static AbstractQoreNode *QSTYLEOPTIONDOCKWIDGET_memberGate(QoreObject *self, QoreQStyleOptionDockWidget *qsodw, const QoreListNode *params, ExceptionSink *xsink) {
   const QoreStringNode *str = test_string_param(params, 0);
   if (!str || !str->strlen())
      return 0;

   const char *member = str->getBuffer();
   AbstractQoreNode *rv = QStyleOptionDockWidget_MemberGate(qsodw, member);
   if (rv)
      return rv;

   return QStyleOption_MemberGate(qsodw, member);
}

// QStyleOptionDockWidget ()
//QStyleOptionDockWidget ( const QStyleOptionDockWidget & other )
static void QSTYLEOPTIONDOCKWIDGET_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   self->setPrivate(CID_QSTYLEOPTIONDOCKWIDGET, new QoreQStyleOptionDockWidget());
   return;
}

static void QSTYLEOPTIONDOCKWIDGET_copy(QoreObject *self, QoreObject *old, QoreQStyleOptionDockWidget *qsodw, ExceptionSink *xsink) {
   xsink->raiseException("QSTYLEOPTIONDOCKWIDGET-COPY-ERROR", "objects of this class cannot be copied");
}

static QoreClass *initQStyleOptionDockWidgetClass(QoreClass *qstyleoption) {
   QC_QStyleOptionDockWidget = new QoreClass("QStyleOptionDockWidget", QDOM_GUI);
   CID_QSTYLEOPTIONDOCKWIDGET = QC_QStyleOptionDockWidget->getID();

   QC_QStyleOptionDockWidget->addBuiltinVirtualBaseClass(qstyleoption);

   QC_QStyleOptionDockWidget->setConstructor(QSTYLEOPTIONDOCKWIDGET_constructor);
   QC_QStyleOptionDockWidget->setCopy((q_copy_t)QSTYLEOPTIONDOCKWIDGET_copy);

   // add special methods
   QC_QStyleOptionDockWidget->addMethod("memberNotification", (q_method_t)QSTYLEOPTIONDOCKWIDGET_memberNotification);
   QC_QStyleOptionDockWidget->addMethod("memberGate",         (q_method_t)QSTYLEOPTIONDOCKWIDGET_memberGate);

   return QC_QStyleOptionDockWidget;
}

QoreNamespace *initQStyleOptionDockWidgetNS(QoreClass *qstyleoption) {
   QoreNamespace *ns = new QoreNamespace("QStyleOptionDockWidget");
   ns->addSystemClass(initQStyleOptionDockWidgetClass(QC_QStyleOption));

   // StyleOptionType enum
   ns->addConstant("Type",    new QoreBigIntNode(QStyleOptionDockWidget::Type));

   // StyleOptionVersion enum
   ns->addConstant("Version", new QoreBigIntNode(QStyleOptionDockWidget::Version));

   return ns;
}
