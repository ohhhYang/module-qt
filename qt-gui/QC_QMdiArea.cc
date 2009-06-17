/*
 QC_QMdiArea.cc
 
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

#include "QC_QMdiArea.h"
#include "QC_QMdiSubWindow.h"

qore_classid_t CID_QMDIAREA;
QoreClass *QC_QMdiArea = 0;

//QMdiArea ( QWidget * parent = 0 )
static void QMDIAREA_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *parent = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QMDIAREA, new QoreQMdiArea(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
   return;
}

static void QMDIAREA_copy(QoreObject *self, QoreObject *old, QoreQMdiArea *qma, ExceptionSink *xsink) {
   xsink->raiseException("QMDIAREA-COPY-ERROR", "objects of this class cannot be copied");
}

//WindowOrder activationOrder () const
static AbstractQoreNode *QMDIAREA_activationOrder(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qma->qobj->activationOrder());
}

static AbstractQoreNode *getQoreQMdiSubWindow(QMdiSubWindow *qt_qobj) {
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QMdiSubWindow, getProgram());
   QoreQtQMdiSubWindow *t_qobj = new QoreQtQMdiSubWindow(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QMDISUBWINDOW, t_qobj);
   return rv_obj;
}

//QMdiSubWindow * activeSubWindow () const
static AbstractQoreNode *QMDIAREA_activeSubWindow(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   QMdiSubWindow *qt_qobj = qma->qobj->activeSubWindow();
   return getQoreQMdiSubWindow(qt_qobj);
}

//QMdiSubWindow * addSubWindow ( QWidget * widget, Qt::WindowFlags windowFlags = 0 )
static AbstractQoreNode *QMDIAREA_addSubWindow(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QMDIAREA-ADDSUBWINDOW-PARAM-ERROR", "expecting a QWidget object as first argument to QMdiArea::addSubWindow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   p = get_param(params, 1);
   Qt::WindowFlags windowFlags = (Qt::WindowFlags)(!is_nothing(p) ? p->getAsInt() : 0);
   QMdiSubWindow *qt_qobj = qma->qobj->addSubWindow(static_cast<QWidget *>(widget->getQWidget()), windowFlags);
   return getQoreQMdiSubWindow(qt_qobj);
}

//QBrush background () const
static AbstractQoreNode *QMDIAREA_background(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QBrush, new QoreQBrush(qma->qobj->background()));
}

//QMdiSubWindow * currentSubWindow () const
static AbstractQoreNode *QMDIAREA_currentSubWindow(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   QMdiSubWindow *qt_qobj = qma->qobj->currentSubWindow();
   return getQoreQMdiSubWindow(qt_qobj);
}

//bool documentMode () const
static AbstractQoreNode *QMDIAREA_documentMode(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qma->qobj->documentMode());
}

//void removeSubWindow ( QWidget * widget )
static AbstractQoreNode *QMDIAREA_removeSubWindow(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QMDIAREA-REMOVESUBWINDOW-PARAM-ERROR", "expecting a QWidget object as first argument to QMdiArea::removeSubWindow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   qma->qobj->removeSubWindow(static_cast<QWidget *>(widget->getQWidget()));
   return 0;
}

//void setActivationOrder ( WindowOrder order )
static AbstractQoreNode *QMDIAREA_setActivationOrder(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QMdiArea::WindowOrder order = (QMdiArea::WindowOrder)(p ? p->getAsInt() : 0);
   qma->qobj->setActivationOrder(order);
   return 0;
}

//void setBackground ( const QBrush & background )
static AbstractQoreNode *QMDIAREA_setBackground(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QBrush background;
   if (get_qbrush(p, background, xsink))
      return 0;
   qma->qobj->setBackground(background);
   return 0;
}

//void setDocumentMode ( bool enabled )
static AbstractQoreNode *QMDIAREA_setDocumentMode(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enabled = p ? p->getAsBool() : false;
   qma->qobj->setDocumentMode(enabled);
   return 0;
}

//void setOption ( AreaOption option, bool on = true )
static AbstractQoreNode *QMDIAREA_setOption(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QMdiArea::AreaOption option = (QMdiArea::AreaOption)(p ? p->getAsInt() : 0);
   p = get_param(params, 1);
   bool on = !is_nothing(p) ? p->getAsBool() : true;
   qma->qobj->setOption(option, on);
   return 0;
}

//void setTabPosition ( QTabWidget::TabPosition position )
static AbstractQoreNode *QMDIAREA_setTabPosition(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QTabWidget::TabPosition position = (QTabWidget::TabPosition)(p ? p->getAsInt() : 0);
   qma->qobj->setTabPosition(position);
   return 0;
}

//void setTabShape ( QTabWidget::TabShape shape )
static AbstractQoreNode *QMDIAREA_setTabShape(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QTabWidget::TabShape shape = (QTabWidget::TabShape)(p ? p->getAsInt() : 0);
   qma->qobj->setTabShape(shape);
   return 0;
}

//void setViewMode ( ViewMode mode )
static AbstractQoreNode *QMDIAREA_setViewMode(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QMdiArea::ViewMode mode = (QMdiArea::ViewMode)(p ? p->getAsInt() : 0);
   qma->qobj->setViewMode(mode);
   return 0;
}

//QList<QMdiSubWindow *> subWindowList ( WindowOrder order = CreationOrder ) const
static AbstractQoreNode *QMDIAREA_subWindowList(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QMdiArea::WindowOrder order = !is_nothing(p) ? (QMdiArea::WindowOrder)p->getAsInt() : QMdiArea::CreationOrder;
   
   QList<QMdiSubWindow *> l_rv = qma->qobj->subWindowList(order);
   QoreListNode *l = new QoreListNode();
   for (QList<QMdiSubWindow *>::iterator i = l_rv.begin(), e = l_rv.end(); i != e; ++i) {
      l->push(getQoreQMdiSubWindow(*i));
   }

   return l;
}

//QTabWidget::TabPosition tabPosition () const
static AbstractQoreNode *QMDIAREA_tabPosition(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qma->qobj->tabPosition());
}

//QTabWidget::TabShape tabShape () const
static AbstractQoreNode *QMDIAREA_tabShape(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qma->qobj->tabShape());
}

//bool testOption ( AreaOption option ) const
static AbstractQoreNode *QMDIAREA_testOption(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QMdiArea::AreaOption option = (QMdiArea::AreaOption)(p ? p->getAsInt() : 0);
   return get_bool_node(qma->qobj->testOption(option));
}

//ViewMode viewMode () const
static AbstractQoreNode *QMDIAREA_viewMode(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qma->qobj->viewMode());
}

// void activateNextSubWindow ()
static AbstractQoreNode *QMDIAREA_activateNextSubWindow(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   qma->qobj->activateNextSubWindow();
   return 0;
}

//void activatePreviousSubWindow ()
static AbstractQoreNode *QMDIAREA_activatePreviousSubWindow(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   qma->qobj->activatePreviousSubWindow();
   return 0;
}

//void cascadeSubWindows ()
static AbstractQoreNode *QMDIAREA_cascadeSubWindows(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   qma->qobj->cascadeSubWindows();
   return 0;
}

//void closeActiveSubWindow ()
static AbstractQoreNode *QMDIAREA_closeActiveSubWindow(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   qma->qobj->closeActiveSubWindow();
   return 0;
}

//void closeAllSubWindows ()
static AbstractQoreNode *QMDIAREA_closeAllSubWindows(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   qma->qobj->closeAllSubWindows();
   return 0;
}

//void setActiveSubWindow ( QMdiSubWindow * window )
static AbstractQoreNode *QMDIAREA_setActiveSubWindow(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQMdiSubWindow *window = (p && p->getType() == NT_OBJECT) ? (QoreQMdiSubWindow *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMDISUBWINDOW, xsink) : 0;
   if (!window) {
      if (!xsink->isException())
         xsink->raiseException("QMDIAREA-SETACTIVESUBWINDOW-PARAM-ERROR", "expecting a QMdiSubWindow object as first argument to QMdiArea::setActiveSubWindow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> windowHolder(static_cast<AbstractPrivateData *>(window), xsink);
   qma->qobj->setActiveSubWindow(static_cast<QMdiSubWindow *>(window->qobj));
   return 0;
}

//void tileSubWindows ()
static AbstractQoreNode *QMDIAREA_tileSubWindows(QoreObject *self, QoreQMdiArea *qma, const QoreListNode *params, ExceptionSink *xsink) {
   qma->qobj->tileSubWindows();
   return 0;
}

static QoreClass *initQMdiAreaClass(QoreClass *qabstractscrollarea) {
   QC_QMdiArea = new QoreClass("QMdiArea", QDOM_GUI);
   CID_QMDIAREA = QC_QMdiArea->getID();

   QC_QMdiArea->addBuiltinVirtualBaseClass(qabstractscrollarea);

   QC_QMdiArea->setConstructor(QMDIAREA_constructor);
   QC_QMdiArea->setCopy((q_copy_t)QMDIAREA_copy);

   QC_QMdiArea->addMethod("activationOrder",             (q_method_t)QMDIAREA_activationOrder);
   QC_QMdiArea->addMethod("activeSubWindow",             (q_method_t)QMDIAREA_activeSubWindow);
   QC_QMdiArea->addMethod("addSubWindow",                (q_method_t)QMDIAREA_addSubWindow);
   QC_QMdiArea->addMethod("background",                  (q_method_t)QMDIAREA_background);
   QC_QMdiArea->addMethod("currentSubWindow",            (q_method_t)QMDIAREA_currentSubWindow);
   QC_QMdiArea->addMethod("documentMode",                (q_method_t)QMDIAREA_documentMode);
   QC_QMdiArea->addMethod("removeSubWindow",             (q_method_t)QMDIAREA_removeSubWindow);
   QC_QMdiArea->addMethod("setActivationOrder",          (q_method_t)QMDIAREA_setActivationOrder);
   QC_QMdiArea->addMethod("setBackground",               (q_method_t)QMDIAREA_setBackground);
   QC_QMdiArea->addMethod("setDocumentMode",             (q_method_t)QMDIAREA_setDocumentMode);
   QC_QMdiArea->addMethod("setOption",                   (q_method_t)QMDIAREA_setOption);
   QC_QMdiArea->addMethod("setTabPosition",              (q_method_t)QMDIAREA_setTabPosition);
   QC_QMdiArea->addMethod("setTabShape",                 (q_method_t)QMDIAREA_setTabShape);
   QC_QMdiArea->addMethod("setViewMode",                 (q_method_t)QMDIAREA_setViewMode);
   QC_QMdiArea->addMethod("subWindowList",               (q_method_t)QMDIAREA_subWindowList);
   QC_QMdiArea->addMethod("tabPosition",                 (q_method_t)QMDIAREA_tabPosition);
   QC_QMdiArea->addMethod("tabShape",                    (q_method_t)QMDIAREA_tabShape);
   QC_QMdiArea->addMethod("testOption",                  (q_method_t)QMDIAREA_testOption);
   QC_QMdiArea->addMethod("viewMode",                    (q_method_t)QMDIAREA_viewMode);

   // public slots
   QC_QMdiArea->addMethod("activateNextSubWindow",       (q_method_t)QMDIAREA_activateNextSubWindow);
   QC_QMdiArea->addMethod("activatePreviousSubWindow",   (q_method_t)QMDIAREA_activatePreviousSubWindow);
   QC_QMdiArea->addMethod("cascadeSubWindows",           (q_method_t)QMDIAREA_cascadeSubWindows);
   QC_QMdiArea->addMethod("closeActiveSubWindow",        (q_method_t)QMDIAREA_closeActiveSubWindow);
   QC_QMdiArea->addMethod("closeAllSubWindows",          (q_method_t)QMDIAREA_closeAllSubWindows);
   QC_QMdiArea->addMethod("setActiveSubWindow",          (q_method_t)QMDIAREA_setActiveSubWindow);
   QC_QMdiArea->addMethod("tileSubWindows",              (q_method_t)QMDIAREA_tileSubWindows);

   return QC_QMdiArea;
}

QoreNamespace *initQMdiAreaNS(QoreClass *qabstractscrollarea) {
   QoreNamespace *ns = new QoreNamespace("QMdiArea");
   ns->addSystemClass(initQMdiAreaClass(QC_QAbstractScrollArea));

   // AreaOption enum
   ns->addConstant("DontMaximizeSubWindowOnActivation", new QoreBigIntNode(QMdiArea::DontMaximizeSubWindowOnActivation));

   // WindowOrder enum
   ns->addConstant("CreationOrder",            new QoreBigIntNode(QMdiArea::CreationOrder));
   ns->addConstant("StackingOrder",            new QoreBigIntNode(QMdiArea::StackingOrder));
   ns->addConstant("ActivationHistoryOrder",   new QoreBigIntNode(QMdiArea::ActivationHistoryOrder));

   // ViewMode enum
   ns->addConstant("SubWindowView",            new QoreBigIntNode(QMdiArea::SubWindowView));
   ns->addConstant("TabbedView",               new QoreBigIntNode(QMdiArea::TabbedView));
   
   return ns;
}
