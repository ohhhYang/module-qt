/*
 QC_QMdiSubWindow.cc
 
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

#include "QC_QMdiSubWindow.h"
#include "QC_QMdiArea.h"

qore_classid_t CID_QMDISUBWINDOW;
QoreClass *QC_QMdiSubWindow = 0;

//QMdiSubWindow ( QWidget * parent = 0, Qt::WindowFlags flags = 0 )
static void QMDISUBWINDOW_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *parent = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 1);
   Qt::WindowFlags flags = (Qt::WindowFlags)(!is_nothing(p) ? p->getAsInt() : 0);
   self->setPrivate(CID_QMDISUBWINDOW, new QoreQMdiSubWindow(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0, flags));
   return;
}

static void QMDISUBWINDOW_copy(QoreObject *self, QoreObject *old, QoreQMdiSubWindow *qmsw, ExceptionSink *xsink) {
   xsink->raiseException("QMDISUBWINDOW-COPY-ERROR", "objects of this class cannot be copied");
}

//bool isShaded () const
static AbstractQoreNode *QMDISUBWINDOW_isShaded(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qmsw->qobj->isShaded());
}

//int keyboardPageStep () const
static AbstractQoreNode *QMDISUBWINDOW_keyboardPageStep(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qmsw->qobj->keyboardPageStep());
}

//int keyboardSingleStep () const
static AbstractQoreNode *QMDISUBWINDOW_keyboardSingleStep(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qmsw->qobj->keyboardSingleStep());
}

//QMdiArea * mdiArea () const
static AbstractQoreNode *QMDISUBWINDOW_mdiArea(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   QMdiArea *qt_qobj = qmsw->qobj->mdiArea();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QMdiArea, getProgram());
   QoreQtQMdiArea *t_qobj = new QoreQtQMdiArea(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QMDIAREA, t_qobj);
   return rv_obj;
}

//void setKeyboardPageStep ( int step )
static AbstractQoreNode *QMDISUBWINDOW_setKeyboardPageStep(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int step = p ? p->getAsInt() : 0;
   qmsw->qobj->setKeyboardPageStep(step);
   return 0;
}

//void setKeyboardSingleStep ( int step )
static AbstractQoreNode *QMDISUBWINDOW_setKeyboardSingleStep(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int step = p ? p->getAsInt() : 0;
   qmsw->qobj->setKeyboardSingleStep(step);
   return 0;
}

//void setOption ( SubWindowOption option, bool on = true )
static AbstractQoreNode *QMDISUBWINDOW_setOption(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QMdiSubWindow::SubWindowOption option = (QMdiSubWindow::SubWindowOption)(p ? p->getAsInt() : 0);
   p = get_param(params, 1);
   bool on = !is_nothing(p) ? p->getAsBool() : true;
   qmsw->qobj->setOption(option, on);
   return 0;
}

//void setSystemMenu ( QMenu * systemMenu )
static AbstractQoreNode *QMDISUBWINDOW_setSystemMenu(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQMenu *systemMenu = (p && p->getType() == NT_OBJECT) ? (QoreQMenu *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMENU, xsink) : 0;
   if (!systemMenu) {
      if (!xsink->isException())
         xsink->raiseException("QMDISUBWINDOW-SETSYSTEMMENU-PARAM-ERROR", "expecting a QMenu object as first argument to QMdiSubWindow::setSystemMenu()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> systemMenuHolder(static_cast<AbstractPrivateData *>(systemMenu), xsink);
   qmsw->qobj->setSystemMenu(static_cast<QMenu *>(systemMenu->qobj));
   return 0;
}

//void setWidget ( QWidget * widget )
static AbstractQoreNode *QMDISUBWINDOW_setWidget(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QMDISUBWINDOW-SETWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QMdiSubWindow::setWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   qmsw->qobj->setWidget(static_cast<QWidget *>(widget->getQWidget()));
   return 0;
}

//QMenu * systemMenu () const
static AbstractQoreNode *QMDISUBWINDOW_systemMenu(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   QMenu *qt_qobj = qmsw->qobj->systemMenu();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QMenu, getProgram());
   QoreQtQMenu *t_qobj = new QoreQtQMenu(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QMENU, t_qobj);
   return rv_obj;
}

//bool testOption ( SubWindowOption option ) const
static AbstractQoreNode *QMDISUBWINDOW_testOption(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QMdiSubWindow::SubWindowOption option = (QMdiSubWindow::SubWindowOption)(p ? p->getAsInt() : 0);
   return get_bool_node(qmsw->qobj->testOption(option));
}

//QWidget * widget () const
static AbstractQoreNode *QMDISUBWINDOW_widget(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qwidget(qmsw->qobj->widget());
}

//void showShaded ()
static AbstractQoreNode *QMDISUBWINDOW_showShaded(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   qmsw->qobj->showShaded();
   return 0;
}

//void showSystemMenu ()
static AbstractQoreNode *QMDISUBWINDOW_showSystemMenu(QoreObject *self, QoreQMdiSubWindow *qmsw, const QoreListNode *params, ExceptionSink *xsink) {
   qmsw->qobj->showSystemMenu();
   return 0;
}

static QoreClass *initQMdiSubWindowClass(QoreClass *qwidget) {
   QC_QMdiSubWindow = new QoreClass("QMdiSubWindow", QDOM_GUI);
   CID_QMDISUBWINDOW = QC_QMdiSubWindow->getID();

   QC_QMdiSubWindow->addBuiltinVirtualBaseClass(qwidget);

   QC_QMdiSubWindow->setConstructor(QMDISUBWINDOW_constructor);
   QC_QMdiSubWindow->setCopy((q_copy_t)QMDISUBWINDOW_copy);

   QC_QMdiSubWindow->addMethod("isShaded",                    (q_method_t)QMDISUBWINDOW_isShaded);
   QC_QMdiSubWindow->addMethod("keyboardPageStep",            (q_method_t)QMDISUBWINDOW_keyboardPageStep);
   QC_QMdiSubWindow->addMethod("keyboardSingleStep",          (q_method_t)QMDISUBWINDOW_keyboardSingleStep);
   QC_QMdiSubWindow->addMethod("mdiArea",                     (q_method_t)QMDISUBWINDOW_mdiArea);
   QC_QMdiSubWindow->addMethod("setKeyboardPageStep",         (q_method_t)QMDISUBWINDOW_setKeyboardPageStep);
   QC_QMdiSubWindow->addMethod("setKeyboardSingleStep",       (q_method_t)QMDISUBWINDOW_setKeyboardSingleStep);
   QC_QMdiSubWindow->addMethod("setOption",                   (q_method_t)QMDISUBWINDOW_setOption);
   QC_QMdiSubWindow->addMethod("setSystemMenu",               (q_method_t)QMDISUBWINDOW_setSystemMenu);
   QC_QMdiSubWindow->addMethod("setWidget",                   (q_method_t)QMDISUBWINDOW_setWidget);
   QC_QMdiSubWindow->addMethod("systemMenu",                  (q_method_t)QMDISUBWINDOW_systemMenu);
   QC_QMdiSubWindow->addMethod("testOption",                  (q_method_t)QMDISUBWINDOW_testOption);
   QC_QMdiSubWindow->addMethod("widget",                      (q_method_t)QMDISUBWINDOW_widget);
   QC_QMdiSubWindow->addMethod("showShaded",                  (q_method_t)QMDISUBWINDOW_showShaded);
   QC_QMdiSubWindow->addMethod("showSystemMenu",              (q_method_t)QMDISUBWINDOW_showSystemMenu);

   return QC_QMdiSubWindow;
}

QoreNamespace *initQMdiSubWindowNS(QoreClass *qwidget) {
   QoreNamespace *ns = new QoreNamespace("QMdiSubWindow");
   ns->addSystemClass(initQMdiSubWindowClass(QC_QWidget));

   // SubWindowOption enum
   ns->addConstant("AllowOutsideAreaHorizontally", new QoreBigIntNode(QMdiSubWindow::AllowOutsideAreaHorizontally));
   ns->addConstant("AllowOutsideAreaVertically", new QoreBigIntNode(QMdiSubWindow::AllowOutsideAreaVertically));
   ns->addConstant("RubberBandResize",         new QoreBigIntNode(QMdiSubWindow::RubberBandResize));
   ns->addConstant("RubberBandMove",           new QoreBigIntNode(QMdiSubWindow::RubberBandMove));

   return ns;
}
