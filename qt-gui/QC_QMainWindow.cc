/*
 QC_QMainWindow.cc
 
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

#include "QC_QMainWindow.h"
#include "QC_QStatusBar.h"
#include "QC_QMenuBar.h"
#include "QC_QDockWidget.h"
#include "QC_QToolBar.h"

qore_classid_t CID_QMAINWINDOW;
QoreClass *QC_QMainWindow = 0;

//QMainWindow ( QWidget * parent = 0, Qt::WindowFlags flags = 0 )
static void QMAINWINDOW_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *parent = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 1);
   Qt::WindowFlags flags = (Qt::WindowFlags)(!is_nothing(p) ? p->getAsInt() : 0);
   self->setPrivate(CID_QMAINWINDOW, new QoreQMainWindow(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0, flags));
   return;
}

static void QMAINWINDOW_copy(QoreObject *self, QoreObject *old, QoreQMainWindow *qmw, ExceptionSink *xsink) {
   xsink->raiseException("QMAINWINDOW-COPY-ERROR", "objects of this class cannot be copied");
}

//void addDockWidget ( Qt::DockWidgetArea area, QDockWidget * dockwidget )
//void addDockWidget ( Qt::DockWidgetArea area, QDockWidget * dockwidget, Qt::Orientation orientation )
static AbstractQoreNode *QMAINWINDOW_addDockWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::DockWidgetArea area = (Qt::DockWidgetArea)(p ? p->getAsInt() : 0);
   p = get_param(params, 1);
   if (!p || p->getType() != NT_OBJECT) {
      xsink->raiseException("QMAINWINDOW-ADDDOCKWIDGET-PARAM-ERROR", "QMainWindow::addDockWidget() expects an object derived from QDockWidget as the second argument");
      return 0;
   }

   QoreQDockWidget *dockwidget = (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink);
   if (!dockwidget) {
      if (!xsink->isException())
	 xsink->raiseException("QMAINWINDOW-ADDDOCKWIDGET-PARAM-ERROR", "QMainWindow::addDockWidget() does not know how to handle arguments of class '%s' as passed as the second argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> dockwidgetHolder(static_cast<AbstractPrivateData *>(dockwidget), xsink);

   if (num_params(params) < 3) {
      qmw->getQMainWindow()->addDockWidget(area, static_cast<QDockWidget *>(dockwidget->qobj));
      return 0;
   }

   p = get_param(params, 2);
   Qt::Orientation orientation = (Qt::Orientation)(p ? p->getAsInt() : 0);
   qmw->getQMainWindow()->addDockWidget(area, static_cast<QDockWidget *>(dockwidget->qobj), orientation);
   return 0;
}

//void addToolBar ( Qt::ToolBarArea area, QToolBar * toolbar )
//void addToolBar ( QToolBar * toolbar )
//QToolBar * addToolBar ( const QString & title )
static AbstractQoreNode *QMAINWINDOW_addToolBar(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQToolBar *toolbar = (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink);
      if (!toolbar) {
         if (!xsink->isException())
            xsink->raiseException("QMAINWINDOW-ADDTOOLBAR-PARAM-ERROR", "QMainWindow::addToolBar() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
         return 0;
      }
      ReferenceHolder<AbstractPrivateData> toolbarHolder(static_cast<AbstractPrivateData *>(toolbar), xsink);
      qmw->getQMainWindow()->addToolBar(static_cast<QToolBar *>(toolbar->qobj));
      return 0;
   }
   if (p && p->getType() == NT_STRING) {
      QString title;
      if (get_qstring(p, title, xsink))
         return 0;
      QToolBar *qt_qobj = qmw->getQMainWindow()->addToolBar(title);
      if (!qt_qobj)
	 return 0;
      QVariant qv_ptr = qt_qobj->property("qobject");
      QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
      if (rv_obj)
	 return rv_obj->refSelf();
      rv_obj = new QoreObject(QC_QToolBar, getProgram());
      QoreQtQToolBar *t_qobj = new QoreQtQToolBar(rv_obj, qt_qobj);
      rv_obj->setPrivate(CID_QTOOLBAR, t_qobj);
      return rv_obj;
   }

   Qt::ToolBarArea area = (Qt::ToolBarArea)(p ? p->getAsInt() : 0);
   p = get_param(params, 1);
   QoreQToolBar *toolbar = (p && p->getType() == NT_OBJECT) ? (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink) : 0;
   if (!toolbar) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-ADDTOOLBAR-PARAM-ERROR", "this version of QMainWindow::addToolBar() expects an object derived from QToolBar as the second argument");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> toolbarHolder(static_cast<AbstractPrivateData *>(toolbar), xsink);
   qmw->getQMainWindow()->addToolBar(area, static_cast<QToolBar *>(toolbar->qobj));
   return 0;
}

//void addToolBarBreak ( Qt::ToolBarArea area = Qt::TopToolBarArea )
static AbstractQoreNode *QMAINWINDOW_addToolBarBreak(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::ToolBarArea area = !is_nothing(p) ? (Qt::ToolBarArea)p->getAsInt() : Qt::TopToolBarArea;
   qmw->getQMainWindow()->addToolBarBreak(area);
   return 0;
}

//QWidget * centralWidget () const
static AbstractQoreNode *QMAINWINDOW_centralWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qwidget(qmw->getQMainWindow()->centralWidget());
}

//Qt::DockWidgetArea corner ( Qt::Corner corner ) const
static AbstractQoreNode *QMAINWINDOW_corner(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::Corner corner = (Qt::Corner)(p ? p->getAsInt() : 0);
   return new QoreBigIntNode(qmw->getQMainWindow()->corner(corner));
}

//virtual QMenu * createPopupMenu ()
static AbstractQoreNode *QMAINWINDOW_createPopupMenu(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   QMenu *qt_qobj = qmw->createPopupMenu();
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

//DockOptions dockOptions () const
static AbstractQoreNode *QMAINWINDOW_dockOptions(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qmw->getQMainWindow()->dockOptions());
}

//Qt::DockWidgetArea dockWidgetArea ( QDockWidget * dockwidget ) const
static AbstractQoreNode *QMAINWINDOW_dockWidgetArea(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQDockWidget *dockwidget = (p && p->getType() == NT_OBJECT) ? (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink) : 0;
   if (!dockwidget) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-DOCKWIDGETAREA-PARAM-ERROR", "expecting a QDockWidget object as first argument to QMainWindow::dockWidgetArea()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> dockwidgetHolder(static_cast<AbstractPrivateData *>(dockwidget), xsink);
   return new QoreBigIntNode(qmw->getQMainWindow()->dockWidgetArea(static_cast<QDockWidget *>(dockwidget->qobj)));
}

//bool documentMode () const
static AbstractQoreNode *QMAINWINDOW_documentMode(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qmw->getQMainWindow()->documentMode());
}

//QSize iconSize () const
static AbstractQoreNode *QMAINWINDOW_iconSize(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QSize, new QoreQSize(qmw->getQMainWindow()->iconSize()));
}

//void insertToolBar ( QToolBar * before, QToolBar * toolbar )
static AbstractQoreNode *QMAINWINDOW_insertToolBar(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQToolBar *before = (p && p->getType() == NT_OBJECT) ? (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink) : 0;
   if (!before) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-INSERTTOOLBAR-PARAM-ERROR", "expecting a QToolBar object as first argument to QMainWindow::insertToolBar()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> beforeHolder(static_cast<AbstractPrivateData *>(before), xsink);
   p = get_param(params, 1);
   QoreQToolBar *toolbar = (p && p->getType() == NT_OBJECT) ? (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink) : 0;
   if (!toolbar) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-INSERTTOOLBAR-PARAM-ERROR", "expecting a QToolBar object as second argument to QMainWindow::insertToolBar()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> toolbarHolder(static_cast<AbstractPrivateData *>(toolbar), xsink);
   qmw->getQMainWindow()->insertToolBar(static_cast<QToolBar *>(before->qobj), static_cast<QToolBar *>(toolbar->qobj));
   return 0;
}

//void insertToolBarBreak ( QToolBar * before )
static AbstractQoreNode *QMAINWINDOW_insertToolBarBreak(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQToolBar *before = (p && p->getType() == NT_OBJECT) ? (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink) : 0;
   if (!before) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-INSERTTOOLBARBREAK-PARAM-ERROR", "expecting a QToolBar object as first argument to QMainWindow::insertToolBarBreak()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> beforeHolder(static_cast<AbstractPrivateData *>(before), xsink);
   qmw->getQMainWindow()->insertToolBarBreak(static_cast<QToolBar *>(before->qobj));
   return 0;
}

//bool isAnimated () const
static AbstractQoreNode *QMAINWINDOW_isAnimated(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qmw->getQMainWindow()->isAnimated());
}

//bool isDockNestingEnabled () const
static AbstractQoreNode *QMAINWINDOW_isDockNestingEnabled(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qmw->getQMainWindow()->isDockNestingEnabled());
}

//QMenuBar * menuBar () const
static AbstractQoreNode *QMAINWINDOW_menuBar(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   QMenuBar *qt_qobj = qmw->getQMainWindow()->menuBar();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QMenuBar, getProgram());
   QoreQtQMenuBar *t_qobj = new QoreQtQMenuBar(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QMENUBAR, t_qobj);
   return rv_obj;
}

//QWidget * menuWidget () const
static AbstractQoreNode *QMAINWINDOW_menuWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qwidget(qmw->getQMainWindow()->menuWidget());
}

//void removeDockWidget ( QDockWidget * dockwidget )
static AbstractQoreNode *QMAINWINDOW_removeDockWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQDockWidget *dockwidget = (p && p->getType() == NT_OBJECT) ? (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink) : 0;
   if (!dockwidget) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-REMOVEDOCKWIDGET-PARAM-ERROR", "expecting a QDockWidget object as first argument to QMainWindow::removeDockWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> dockwidgetHolder(static_cast<AbstractPrivateData *>(dockwidget), xsink);
   qmw->getQMainWindow()->removeDockWidget(static_cast<QDockWidget *>(dockwidget->qobj));
   return 0;
}

//void removeToolBar ( QToolBar * toolbar )
static AbstractQoreNode *QMAINWINDOW_removeToolBar(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQToolBar *toolbar = (p && p->getType() == NT_OBJECT) ? (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink) : 0;
   if (!toolbar) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-REMOVETOOLBAR-PARAM-ERROR", "expecting a QToolBar object as first argument to QMainWindow::removeToolBar()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> toolbarHolder(static_cast<AbstractPrivateData *>(toolbar), xsink);
   qmw->getQMainWindow()->removeToolBar(static_cast<QToolBar *>(toolbar->qobj));
   return 0;
}

//void removeToolBarBreak ( QToolBar * before )
static AbstractQoreNode *QMAINWINDOW_removeToolBarBreak(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQToolBar *before = (p && p->getType() == NT_OBJECT) ? (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink) : 0;
   if (!before) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-REMOVETOOLBARBREAK-PARAM-ERROR", "expecting a QToolBar object as first argument to QMainWindow::removeToolBarBreak()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> beforeHolder(static_cast<AbstractPrivateData *>(before), xsink);
   qmw->getQMainWindow()->removeToolBarBreak(static_cast<QToolBar *>(before->qobj));
   return 0;
}

//bool restoreDockWidget ( QDockWidget * dockwidget )
static AbstractQoreNode *QMAINWINDOW_restoreDockWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQDockWidget *dockwidget = (p && p->getType() == NT_OBJECT) ? (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink) : 0;
   if (!dockwidget) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-RESTOREDOCKWIDGET-PARAM-ERROR", "expecting a QDockWidget object as first argument to QMainWindow::restoreDockWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> dockwidgetHolder(static_cast<AbstractPrivateData *>(dockwidget), xsink);
   return get_bool_node(qmw->getQMainWindow()->restoreDockWidget(static_cast<QDockWidget *>(dockwidget->qobj)));
}

//bool restoreState ( const QByteArray & state, int version = 0 )
static AbstractQoreNode *QMAINWINDOW_restoreState(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QByteArray state;
   if (get_qbytearray(p, state, xsink))
      return 0;
   p = get_param(params, 1);
   int version = !is_nothing(p) ? p->getAsInt() : 0;
   return get_bool_node(qmw->getQMainWindow()->restoreState(state, version));
}

//QByteArray saveState ( int version = 0 ) const
static AbstractQoreNode *QMAINWINDOW_saveState(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int version = !is_nothing(p) ? p->getAsInt() : 0;
   return return_object(QC_QByteArray, new QoreQByteArray(qmw->getQMainWindow()->saveState(version)));
}

//void setCentralWidget ( QWidget * widget )
static AbstractQoreNode *QMAINWINDOW_setCentralWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-SETCENTRALWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QMainWindow::setCentralWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   qmw->getQMainWindow()->setCentralWidget(static_cast<QWidget *>(widget->getQWidget()));
   return 0;
}

//void setCorner ( Qt::Corner corner, Qt::DockWidgetArea area )
static AbstractQoreNode *QMAINWINDOW_setCorner(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::Corner corner = (Qt::Corner)(p ? p->getAsInt() : 0);
   p = get_param(params, 1);
   Qt::DockWidgetArea area = (Qt::DockWidgetArea)(p ? p->getAsInt() : 0);
   qmw->getQMainWindow()->setCorner(corner, area);
   return 0;
}

//void setDockOptions ( DockOptions options )
static AbstractQoreNode *QMAINWINDOW_setDockOptions(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QMainWindow::DockOptions options = (QMainWindow::DockOptions)(p ? p->getAsInt() : 0);
   qmw->getQMainWindow()->setDockOptions(options);
   return 0;
}

//void setDocumentMode ( bool enabled )
static AbstractQoreNode *QMAINWINDOW_setDocumentMode(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enabled = p ? p->getAsBool() : false;
   qmw->getQMainWindow()->setDocumentMode(enabled);
   return 0;
}

//void setIconSize ( const QSize & iconSize )
static AbstractQoreNode *QMAINWINDOW_setIconSize(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQSize *iconSize = (p && p->getType() == NT_OBJECT) ? (QoreQSize *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QSIZE, xsink) : 0;
   if (!iconSize) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-SETICONSIZE-PARAM-ERROR", "expecting a QSize object as first argument to QMainWindow::setIconSize()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> iconSizeHolder(static_cast<AbstractPrivateData *>(iconSize), xsink);
   qmw->getQMainWindow()->setIconSize(*(static_cast<QSize *>(iconSize)));
   return 0;
}

//void setMenuBar ( QMenuBar * menuBar )
static AbstractQoreNode *QMAINWINDOW_setMenuBar(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQMenuBar *menuBar = (p && p->getType() == NT_OBJECT) ? (QoreQMenuBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMENUBAR, xsink) : 0;
   if (!menuBar) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-SETMENUBAR-PARAM-ERROR", "expecting a QMenuBar object as first argument to QMainWindow::setMenuBar()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> menuBarHolder(static_cast<AbstractPrivateData *>(menuBar), xsink);
   qmw->getQMainWindow()->setMenuBar(static_cast<QMenuBar *>(menuBar->getQMenuBar()));
   return 0;
}

//void setMenuWidget ( QWidget * menuBar )
static AbstractQoreNode *QMAINWINDOW_setMenuWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *menuBar = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!menuBar) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-SETMENUWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QMainWindow::setMenuWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> menuBarHolder(static_cast<AbstractPrivateData *>(menuBar), xsink);
   qmw->getQMainWindow()->setMenuWidget(static_cast<QWidget *>(menuBar->getQWidget()));
   return 0;
}

//void setStatusBar ( QStatusBar * statusbar )
static AbstractQoreNode *QMAINWINDOW_setStatusBar(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQStatusBar *statusbar = (p && p->getType() == NT_OBJECT) ? (QoreQStatusBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QSTATUSBAR, xsink) : 0;
   if (!statusbar) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-SETSTATUSBAR-PARAM-ERROR", "expecting a QStatusBar object as first argument to QMainWindow::setStatusBar()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> statusbarHolder(static_cast<AbstractPrivateData *>(statusbar), xsink);
   qmw->getQMainWindow()->setStatusBar(static_cast<QStatusBar *>(statusbar->qobj));
   return 0;
}

//void setTabPosition ( Qt::DockWidgetAreas areas, QTabWidget::TabPosition tabPosition )
static AbstractQoreNode *QMAINWINDOW_setTabPosition(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::DockWidgetAreas areas = (Qt::DockWidgetAreas)(p ? p->getAsInt() : 0);
   p = get_param(params, 1);
   QTabWidget::TabPosition tabPosition = (QTabWidget::TabPosition)(p ? p->getAsInt() : 0);
   qmw->getQMainWindow()->setTabPosition(areas, tabPosition);
   return 0;
}

//void setTabShape ( QTabWidget::TabShape tabShape )
static AbstractQoreNode *QMAINWINDOW_setTabShape(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QTabWidget::TabShape tabShape = (QTabWidget::TabShape)(p ? p->getAsInt() : 0);
   qmw->getQMainWindow()->setTabShape(tabShape);
   return 0;
}

//void setToolButtonStyle ( Qt::ToolButtonStyle toolButtonStyle )
static AbstractQoreNode *QMAINWINDOW_setToolButtonStyle(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::ToolButtonStyle toolButtonStyle = (Qt::ToolButtonStyle)(p ? p->getAsInt() : 0);
   qmw->getQMainWindow()->setToolButtonStyle(toolButtonStyle);
   return 0;
}

//void setUnifiedTitleAndToolBarOnMac ( bool set )
static AbstractQoreNode *QMAINWINDOW_setUnifiedTitleAndToolBarOnMac(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool set = p ? p->getAsBool() : false;
   qmw->getQMainWindow()->setUnifiedTitleAndToolBarOnMac(set);
   return 0;
}

//void splitDockWidget ( QDockWidget * first, QDockWidget * second, Qt::Orientation orientation )
static AbstractQoreNode *QMAINWINDOW_splitDockWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQDockWidget *first = (p && p->getType() == NT_OBJECT) ? (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink) : 0;
   if (!first) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-SPLITDOCKWIDGET-PARAM-ERROR", "expecting a QDockWidget object as first argument to QMainWindow::splitDockWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> firstHolder(static_cast<AbstractPrivateData *>(first), xsink);
   p = get_param(params, 1);
   QoreQDockWidget *second = (p && p->getType() == NT_OBJECT) ? (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink) : 0;
   if (!second) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-SPLITDOCKWIDGET-PARAM-ERROR", "expecting a QDockWidget object as second argument to QMainWindow::splitDockWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> secondHolder(static_cast<AbstractPrivateData *>(second), xsink);
   p = get_param(params, 2);
   Qt::Orientation orientation = (Qt::Orientation)(p ? p->getAsInt() : 0);
   qmw->getQMainWindow()->splitDockWidget(static_cast<QDockWidget *>(first->qobj), static_cast<QDockWidget *>(second->qobj), orientation);
   return 0;
}

//QStatusBar * statusBar () const
static AbstractQoreNode *QMAINWINDOW_statusBar(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   QStatusBar *qt_qobj = qmw->getQMainWindow()->statusBar();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QStatusBar, getProgram());
   QoreQtQStatusBar *t_qobj = new QoreQtQStatusBar(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QSTATUSBAR, t_qobj);
   return rv_obj;
}

//QTabWidget::TabPosition tabPosition ( Qt::DockWidgetArea area ) const
static AbstractQoreNode *QMAINWINDOW_tabPosition(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::DockWidgetArea area = (Qt::DockWidgetArea)(p ? p->getAsInt() : 0);
   return new QoreBigIntNode(qmw->getQMainWindow()->tabPosition(area));
}

//QTabWidget::TabShape tabShape () const
static AbstractQoreNode *QMAINWINDOW_tabShape(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qmw->getQMainWindow()->tabShape());
}

//QList<QDockWidget *> tabifiedDockWidgets ( QDockWidget * dockwidget ) const
static AbstractQoreNode *QMAINWINDOW_tabifiedDockWidgets(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQDockWidget *dockwidget = (p && p->getType() == NT_OBJECT) ? (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink) : 0;
   if (!dockwidget) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-TABIFIEDDOCKWIDGETS-PARAM-ERROR", "expecting a QDockWidget object as first argument to QMainWindow::tabifiedDockWidgets()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> dockwidgetHolder(static_cast<AbstractPrivateData *>(dockwidget), xsink);
   QList<QDockWidget *>ql = qmw->getQMainWindow()->tabifiedDockWidgets(static_cast<QDockWidget *>(dockwidget->qobj));

   QoreListNode *rv = new QoreListNode;
   for (QList<QDockWidget *>::iterator i = ql.begin(), e = ql.end(); i != e; ++i) {
      QoreObject *rv_obj = new QoreObject(QC_QDockWidget, getProgram());
      QoreQtQDockWidget *t_qobj = new QoreQtQDockWidget(rv_obj, *i);
      rv_obj->setPrivate(CID_QDOCKWIDGET, t_qobj);
      rv->push(rv_obj);
   }

   return rv;
}

//void tabifyDockWidget ( QDockWidget * first, QDockWidget * second )
static AbstractQoreNode *QMAINWINDOW_tabifyDockWidget(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQDockWidget *first = (p && p->getType() == NT_OBJECT) ? (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink) : 0;
   if (!first) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-TABIFYDOCKWIDGET-PARAM-ERROR", "expecting a QDockWidget object as first argument to QMainWindow::tabifyDockWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> firstHolder(static_cast<AbstractPrivateData *>(first), xsink);
   p = get_param(params, 1);
   QoreQDockWidget *second = (p && p->getType() == NT_OBJECT) ? (QoreQDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QDOCKWIDGET, xsink) : 0;
   if (!second) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-TABIFYDOCKWIDGET-PARAM-ERROR", "expecting a QDockWidget object as second argument to QMainWindow::tabifyDockWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> secondHolder(static_cast<AbstractPrivateData *>(second), xsink);
   qmw->getQMainWindow()->tabifyDockWidget(static_cast<QDockWidget *>(first->qobj), static_cast<QDockWidget *>(second->qobj));
   return 0;
}

//Qt::ToolBarArea toolBarArea ( QToolBar * toolbar ) const
static AbstractQoreNode *QMAINWINDOW_toolBarArea(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQToolBar *toolbar = (p && p->getType() == NT_OBJECT) ? (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink) : 0;
   if (!toolbar) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-TOOLBARAREA-PARAM-ERROR", "expecting a QToolBar object as first argument to QMainWindow::toolBarArea()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> toolbarHolder(static_cast<AbstractPrivateData *>(toolbar), xsink);
   return new QoreBigIntNode(qmw->getQMainWindow()->toolBarArea(static_cast<QToolBar *>(toolbar->qobj)));
}

//bool toolBarBreak ( QToolBar * toolbar ) const
static AbstractQoreNode *QMAINWINDOW_toolBarBreak(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQToolBar *toolbar = (p && p->getType() == NT_OBJECT) ? (QoreQToolBar *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTOOLBAR, xsink) : 0;
   if (!toolbar) {
      if (!xsink->isException())
         xsink->raiseException("QMAINWINDOW-TOOLBARBREAK-PARAM-ERROR", "expecting a QToolBar object as first argument to QMainWindow::toolBarBreak()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> toolbarHolder(static_cast<AbstractPrivateData *>(toolbar), xsink);
   return get_bool_node(qmw->getQMainWindow()->toolBarBreak(static_cast<QToolBar *>(toolbar->qobj)));
}

//Qt::ToolButtonStyle toolButtonStyle () const
static AbstractQoreNode *QMAINWINDOW_toolButtonStyle(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qmw->getQMainWindow()->toolButtonStyle());
}

//bool unifiedTitleAndToolBarOnMac () const
static AbstractQoreNode *QMAINWINDOW_unifiedTitleAndToolBarOnMac(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qmw->getQMainWindow()->unifiedTitleAndToolBarOnMac());
}

//void setAnimated ( bool enabled )
static AbstractQoreNode *QMAINWINDOW_setAnimated(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enabled = p ? p->getAsBool() : false;
   qmw->getQMainWindow()->setAnimated(enabled);
   return 0;
}

//void setDockNestingEnabled ( bool enabled )
static AbstractQoreNode *QMAINWINDOW_setDockNestingEnabled(QoreObject *self, QoreAbstractQMainWindow *qmw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enabled = p ? p->getAsBool() : false;
   qmw->getQMainWindow()->setDockNestingEnabled(enabled);
   return 0;
}

static QoreClass *initQMainWindowClass(QoreClass *qwidget) {
   QC_QMainWindow = new QoreClass("QMainWindow", QDOM_GUI);
   CID_QMAINWINDOW = QC_QMainWindow->getID();

   QC_QMainWindow->addBuiltinVirtualBaseClass(qwidget);

   QC_QMainWindow->setConstructor(QMAINWINDOW_constructor);
   QC_QMainWindow->setCopy((q_copy_t)QMAINWINDOW_copy);

   QC_QMainWindow->addMethod("addDockWidget",               (q_method_t)QMAINWINDOW_addDockWidget);
   QC_QMainWindow->addMethod("addToolBar",                  (q_method_t)QMAINWINDOW_addToolBar);
   QC_QMainWindow->addMethod("addToolBarBreak",             (q_method_t)QMAINWINDOW_addToolBarBreak);
   QC_QMainWindow->addMethod("centralWidget",               (q_method_t)QMAINWINDOW_centralWidget);
   QC_QMainWindow->addMethod("corner",                      (q_method_t)QMAINWINDOW_corner);
   QC_QMainWindow->addMethod("createPopupMenu",             (q_method_t)QMAINWINDOW_createPopupMenu);
   QC_QMainWindow->addMethod("dockOptions",                 (q_method_t)QMAINWINDOW_dockOptions);
   QC_QMainWindow->addMethod("dockWidgetArea",              (q_method_t)QMAINWINDOW_dockWidgetArea);
   QC_QMainWindow->addMethod("documentMode",                (q_method_t)QMAINWINDOW_documentMode);
   QC_QMainWindow->addMethod("iconSize",                    (q_method_t)QMAINWINDOW_iconSize);
   QC_QMainWindow->addMethod("insertToolBar",               (q_method_t)QMAINWINDOW_insertToolBar);
   QC_QMainWindow->addMethod("insertToolBarBreak",          (q_method_t)QMAINWINDOW_insertToolBarBreak);
   QC_QMainWindow->addMethod("isAnimated",                  (q_method_t)QMAINWINDOW_isAnimated);
   QC_QMainWindow->addMethod("isDockNestingEnabled",        (q_method_t)QMAINWINDOW_isDockNestingEnabled);
   QC_QMainWindow->addMethod("menuBar",                     (q_method_t)QMAINWINDOW_menuBar);
   QC_QMainWindow->addMethod("menuWidget",                  (q_method_t)QMAINWINDOW_menuWidget);
   QC_QMainWindow->addMethod("removeDockWidget",            (q_method_t)QMAINWINDOW_removeDockWidget);
   QC_QMainWindow->addMethod("removeToolBar",               (q_method_t)QMAINWINDOW_removeToolBar);
   QC_QMainWindow->addMethod("removeToolBarBreak",          (q_method_t)QMAINWINDOW_removeToolBarBreak);
   QC_QMainWindow->addMethod("restoreDockWidget",           (q_method_t)QMAINWINDOW_restoreDockWidget);
   QC_QMainWindow->addMethod("restoreState",                (q_method_t)QMAINWINDOW_restoreState);
   QC_QMainWindow->addMethod("saveState",                   (q_method_t)QMAINWINDOW_saveState);
   QC_QMainWindow->addMethod("setCentralWidget",            (q_method_t)QMAINWINDOW_setCentralWidget);
   QC_QMainWindow->addMethod("setCorner",                   (q_method_t)QMAINWINDOW_setCorner);
   QC_QMainWindow->addMethod("setDockOptions",              (q_method_t)QMAINWINDOW_setDockOptions);
   QC_QMainWindow->addMethod("setDocumentMode",             (q_method_t)QMAINWINDOW_setDocumentMode);
   QC_QMainWindow->addMethod("setIconSize",                 (q_method_t)QMAINWINDOW_setIconSize);
   QC_QMainWindow->addMethod("setMenuBar",                  (q_method_t)QMAINWINDOW_setMenuBar);
   QC_QMainWindow->addMethod("setMenuWidget",               (q_method_t)QMAINWINDOW_setMenuWidget);
   QC_QMainWindow->addMethod("setStatusBar",                (q_method_t)QMAINWINDOW_setStatusBar);
   QC_QMainWindow->addMethod("setTabPosition",              (q_method_t)QMAINWINDOW_setTabPosition);
   QC_QMainWindow->addMethod("setTabShape",                 (q_method_t)QMAINWINDOW_setTabShape);
   QC_QMainWindow->addMethod("setToolButtonStyle",          (q_method_t)QMAINWINDOW_setToolButtonStyle);
   QC_QMainWindow->addMethod("setUnifiedTitleAndToolBarOnMac", (q_method_t)QMAINWINDOW_setUnifiedTitleAndToolBarOnMac);
   QC_QMainWindow->addMethod("splitDockWidget",             (q_method_t)QMAINWINDOW_splitDockWidget);
   QC_QMainWindow->addMethod("statusBar",                   (q_method_t)QMAINWINDOW_statusBar);
   QC_QMainWindow->addMethod("tabPosition",                 (q_method_t)QMAINWINDOW_tabPosition);
   QC_QMainWindow->addMethod("tabShape",                    (q_method_t)QMAINWINDOW_tabShape);
   QC_QMainWindow->addMethod("tabifiedDockWidgets",         (q_method_t)QMAINWINDOW_tabifiedDockWidgets);
   QC_QMainWindow->addMethod("tabifyDockWidget",            (q_method_t)QMAINWINDOW_tabifyDockWidget);
   QC_QMainWindow->addMethod("toolBarArea",                 (q_method_t)QMAINWINDOW_toolBarArea);
   QC_QMainWindow->addMethod("toolBarBreak",                (q_method_t)QMAINWINDOW_toolBarBreak);
   QC_QMainWindow->addMethod("toolButtonStyle",             (q_method_t)QMAINWINDOW_toolButtonStyle);
   QC_QMainWindow->addMethod("unifiedTitleAndToolBarOnMac", (q_method_t)QMAINWINDOW_unifiedTitleAndToolBarOnMac);
   QC_QMainWindow->addMethod("setAnimated",                 (q_method_t)QMAINWINDOW_setAnimated);
   QC_QMainWindow->addMethod("setDockNestingEnabled",       (q_method_t)QMAINWINDOW_setDockNestingEnabled);

   return QC_QMainWindow;
}

QoreNamespace *initQMainWindowNS(QoreClass *qwidget) {
   QoreNamespace *ns = new QoreNamespace("QMainWindow");
   ns->addSystemClass(initQMainWindowClass(QC_QWidget));

   // DockOption enum
   ns->addConstant("AnimatedDocks",            new QoreBigIntNode(QMainWindow::AnimatedDocks));
   ns->addConstant("AllowNestedDocks",         new QoreBigIntNode(QMainWindow::AllowNestedDocks));
   ns->addConstant("AllowTabbedDocks",         new QoreBigIntNode(QMainWindow::AllowTabbedDocks));
   ns->addConstant("ForceTabbedDocks",         new QoreBigIntNode(QMainWindow::ForceTabbedDocks));
   ns->addConstant("VerticalTabs",             new QoreBigIntNode(QMainWindow::VerticalTabs));

   return ns;
}
