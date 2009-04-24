/*
 QC_QStatusBar.cc
 
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

#include "QC_QStatusBar.h"

qore_classid_t CID_QSTATUSBAR;
QoreClass *QC_QStatusBar = 0;

//QStatusBar ( QWidget * parent = 0 )
static void QSTATUSBAR_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *parent = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QSTATUSBAR, new QoreQStatusBar(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
   return;
}

static void QSTATUSBAR_copy(QoreObject *self, QoreObject *old, QoreQStatusBar *qsb, ExceptionSink *xsink) {
   xsink->raiseException("QSTATUSBAR-COPY-ERROR", "objects of this class cannot be copied");
}

//void addPermanentWidget ( QWidget * widget, int stretch = 0 )
static AbstractQoreNode *QSTATUSBAR_addPermanentWidget(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QSTATUSBAR-ADDPERMANENTWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QStatusBar::addPermanentWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   p = get_param(params, 1);
   int stretch = !is_nothing(p) ? p->getAsInt() : 0;
   qsb->qobj->addPermanentWidget(static_cast<QWidget *>(widget->getQWidget()), stretch);
   return 0;
}

//void addWidget ( QWidget * widget, int stretch = 0 )
static AbstractQoreNode *QSTATUSBAR_addWidget(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QSTATUSBAR-ADDWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QStatusBar::addWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   p = get_param(params, 1);
   int stretch = !is_nothing(p) ? p->getAsInt() : 0;
   qsb->qobj->addWidget(static_cast<QWidget *>(widget->getQWidget()), stretch);
   return 0;
}

//QString currentMessage () const
static AbstractQoreNode *QSTATUSBAR_currentMessage(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreStringNode(qsb->qobj->currentMessage().toUtf8().data(), QCS_UTF8);
}

//int insertPermanentWidget ( int index, QWidget * widget, int stretch = 0 )
static AbstractQoreNode *QSTATUSBAR_insertPermanentWidget(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QSTATUSBAR-INSERTPERMANENTWIDGET-PARAM-ERROR", "expecting a QWidget object as second argument to QStatusBar::insertPermanentWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   p = get_param(params, 2);
   int stretch = !is_nothing(p) ? p->getAsInt() : 0;
   return new QoreBigIntNode(qsb->qobj->insertPermanentWidget(index, static_cast<QWidget *>(widget->getQWidget()), stretch));
}

//int insertWidget ( int index, QWidget * widget, int stretch = 0 )
static AbstractQoreNode *QSTATUSBAR_insertWidget(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QSTATUSBAR-INSERTWIDGET-PARAM-ERROR", "expecting a QWidget object as second argument to QStatusBar::insertWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   p = get_param(params, 2);
   int stretch = !is_nothing(p) ? p->getAsInt() : 0;
   return new QoreBigIntNode(qsb->qobj->insertWidget(index, static_cast<QWidget *>(widget->getQWidget()), stretch));
}

//bool isSizeGripEnabled () const
static AbstractQoreNode *QSTATUSBAR_isSizeGripEnabled(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qsb->qobj->isSizeGripEnabled());
}

//void removeWidget ( QWidget * widget )
static AbstractQoreNode *QSTATUSBAR_removeWidget(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QSTATUSBAR-REMOVEWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QStatusBar::removeWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   qsb->qobj->removeWidget(static_cast<QWidget *>(widget->getQWidget()));
   return 0;
}

//void setSizeGripEnabled ( bool )
static AbstractQoreNode *QSTATUSBAR_setSizeGripEnabled(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool b = p ? p->getAsBool() : false;
   qsb->qobj->setSizeGripEnabled(b);
   return 0;
}

//void clearMessage ()
static AbstractQoreNode *QSTATUSBAR_clearMessage(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   qsb->qobj->clearMessage();
   return 0;
}

//void showMessage ( const QString & message, int timeout = 0 )
static AbstractQoreNode *QSTATUSBAR_showMessage(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString message;
   if (get_qstring(p, message, xsink))
      return 0;
   p = get_param(params, 1);
   int timeout = !is_nothing(p) ? p->getAsInt() : 0;
   qsb->qobj->showMessage(message, timeout);
   return 0;
}

//void hideOrShow ()
static AbstractQoreNode *QSTATUSBAR_hideOrShow(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   qsb->hideOrShow();
   return 0;
}

//void reformat ()
static AbstractQoreNode *QSTATUSBAR_reformat(QoreObject *self, QoreQStatusBar *qsb, const QoreListNode *params, ExceptionSink *xsink) {
   qsb->reformat();
   return 0;
}

QoreClass *initQStatusBarClass(QoreClass *qwidget) {
   QC_QStatusBar = new QoreClass("QStatusBar", QDOM_GUI);
   CID_QSTATUSBAR = QC_QStatusBar->getID();

   QC_QStatusBar->addBuiltinVirtualBaseClass(qwidget);

   QC_QStatusBar->setConstructor(QSTATUSBAR_constructor);
   QC_QStatusBar->setCopy((q_copy_t)QSTATUSBAR_copy);

   QC_QStatusBar->addMethod("addPermanentWidget",          (q_method_t)QSTATUSBAR_addPermanentWidget);
   QC_QStatusBar->addMethod("addWidget",                   (q_method_t)QSTATUSBAR_addWidget);
   QC_QStatusBar->addMethod("currentMessage",              (q_method_t)QSTATUSBAR_currentMessage);
   QC_QStatusBar->addMethod("insertPermanentWidget",       (q_method_t)QSTATUSBAR_insertPermanentWidget);
   QC_QStatusBar->addMethod("insertWidget",                (q_method_t)QSTATUSBAR_insertWidget);
   QC_QStatusBar->addMethod("isSizeGripEnabled",           (q_method_t)QSTATUSBAR_isSizeGripEnabled);
   QC_QStatusBar->addMethod("removeWidget",                (q_method_t)QSTATUSBAR_removeWidget);
   QC_QStatusBar->addMethod("setSizeGripEnabled",          (q_method_t)QSTATUSBAR_setSizeGripEnabled);
   QC_QStatusBar->addMethod("clearMessage",                (q_method_t)QSTATUSBAR_clearMessage);
   QC_QStatusBar->addMethod("showMessage",                 (q_method_t)QSTATUSBAR_showMessage);

   // private methods
   QC_QStatusBar->addMethod("hideOrShow",                  (q_method_t)QSTATUSBAR_hideOrShow, true);
   QC_QStatusBar->addMethod("reformat",                    (q_method_t)QSTATUSBAR_reformat, true);

   return QC_QStatusBar;
}
