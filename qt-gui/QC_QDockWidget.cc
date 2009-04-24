/*
 QC_QDockWidget.cc
 
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

#include "QC_QDockWidget.h"

qore_classid_t CID_QDOCKWIDGET;
QoreClass *QC_QDockWidget = 0;

//QDockWidget ( const QString & title, QWidget * parent = 0, Qt::WindowFlags flags = 0 )
//QDockWidget ( QWidget * parent = 0, Qt::WindowFlags flags = 0 )
static void QDOCKWIDGET_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QDOCKWIDGET, new QoreQDockWidget(self));
      return;
   }

   int got_string = 0;
   QString title;
   if (get_qstring(p, title, xsink, true)) {
      if (*xsink)
	 return;
   }
   else {
      got_string = 1;
      p = get_param(params, 1);
   }

   QoreQWidget *parent = 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(xsink);

   if (p && p->getType() == NT_OBJECT) {
      parent = (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink);
      if (*xsink)
         return;
      if (parent)
	 parentHolder = parent;
   }

   p = get_param(params, 1 + got_string);
   if (is_nothing(p)) {
      if (got_string)
	 self->setPrivate(CID_QDOCKWIDGET, new QoreQDockWidget(self, title, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
      else
	 self->setPrivate(CID_QDOCKWIDGET, new QoreQDockWidget(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));	 
      return;
   }

   Qt::WindowFlags flags = (Qt::WindowFlags)(!is_nothing(p) ? p->getAsInt() : 0);
   if (got_string)
      self->setPrivate(CID_QDOCKWIDGET, new QoreQDockWidget(self, title, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0, flags));
   else
      self->setPrivate(CID_QDOCKWIDGET, new QoreQDockWidget(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0, flags));
}

static void QDOCKWIDGET_copy(QoreObject *self, QoreObject *old, QoreQDockWidget *qdw, ExceptionSink *xsink) {
   xsink->raiseException("QDOCKWIDGET-COPY-ERROR", "objects of this class cannot be copied");
}

//Qt::DockWidgetAreas allowedAreas () const
static AbstractQoreNode *QDOCKWIDGET_allowedAreas(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qdw->getQDockWidget()->allowedAreas());
}

//DockWidgetFeatures features () const
static AbstractQoreNode *QDOCKWIDGET_features(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qdw->getQDockWidget()->features());
}

//bool isAreaAllowed ( Qt::DockWidgetArea area ) const
static AbstractQoreNode *QDOCKWIDGET_isAreaAllowed(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::DockWidgetArea area = (Qt::DockWidgetArea)(p ? p->getAsInt() : 0);
   return get_bool_node(qdw->getQDockWidget()->isAreaAllowed(area));
}

//bool isFloating () const
static AbstractQoreNode *QDOCKWIDGET_isFloating(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qdw->getQDockWidget()->isFloating());
}

//void setAllowedAreas ( Qt::DockWidgetAreas areas )
static AbstractQoreNode *QDOCKWIDGET_setAllowedAreas(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::DockWidgetAreas areas = (Qt::DockWidgetAreas)(p ? p->getAsInt() : 0);
   qdw->getQDockWidget()->setAllowedAreas(areas);
   return 0;
}

//void setFeatures ( DockWidgetFeatures features )
static AbstractQoreNode *QDOCKWIDGET_setFeatures(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QDockWidget::DockWidgetFeatures features = (QDockWidget::DockWidgetFeatures)(p ? p->getAsInt() : 0);
   qdw->getQDockWidget()->setFeatures(features);
   return 0;
}

//void setFloating ( bool floating )
static AbstractQoreNode *QDOCKWIDGET_setFloating(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool floating = p ? p->getAsBool() : false;
   qdw->getQDockWidget()->setFloating(floating);
   return 0;
}

//void setTitleBarWidget ( QWidget * widget )
static AbstractQoreNode *QDOCKWIDGET_setTitleBarWidget(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QDOCKWIDGET-SETTITLEBARWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QDockWidget::setTitleBarWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   qdw->getQDockWidget()->setTitleBarWidget(static_cast<QWidget *>(widget->getQWidget()));
   return 0;
}

//void setWidget ( QWidget * widget )
static AbstractQoreNode *QDOCKWIDGET_setWidget(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QDOCKWIDGET-SETWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QDockWidget::setWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   qdw->getQDockWidget()->setWidget(static_cast<QWidget *>(widget->getQWidget()));
   return 0;
}

//QWidget * titleBarWidget () const
static AbstractQoreNode *QDOCKWIDGET_titleBarWidget(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qwidget(qdw->getQDockWidget()->titleBarWidget());
}

//QAction * toggleViewAction () const
static AbstractQoreNode *QDOCKWIDGET_toggleViewAction(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qaction(qdw->getQDockWidget()->toggleViewAction());
}

//QWidget * widget () const
static AbstractQoreNode *QDOCKWIDGET_widget(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qwidget(qdw->getQDockWidget()->widget());
}

//void initStyleOption ( QStyleOptionDockWidget * option ) const
static AbstractQoreNode *QDOCKWIDGET_initStyleOption(QoreObject *self, QoreAbstractQDockWidget *qdw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQStyleOptionDockWidget *option = (p && p->getType() == NT_OBJECT) ? (QoreQStyleOptionDockWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QSTYLEOPTIONDOCKWIDGET, xsink) : 0;
   if (!option) {
      if (!xsink->isException())
         xsink->raiseException("QDOCKWIDGET-INITSTYLEOPTION-PARAM-ERROR", "expecting a QStyleOptionDockWidget object as first argument to QDockWidget::initStyleOption()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> optionHolder(static_cast<AbstractPrivateData *>(option), xsink);
   qdw->initStyleOption(static_cast<QStyleOptionDockWidget *>(option), xsink);
   return 0;
}

static QoreClass *initQDockWidgetClass(QoreClass *qwidget) {
   QC_QDockWidget = new QoreClass("QDockWidget", QDOM_GUI);
   CID_QDOCKWIDGET = QC_QDockWidget->getID();

   QC_QDockWidget->addBuiltinVirtualBaseClass(qwidget);

   QC_QDockWidget->setConstructor(QDOCKWIDGET_constructor);
   QC_QDockWidget->setCopy((q_copy_t)QDOCKWIDGET_copy);

   QC_QDockWidget->addMethod("allowedAreas",                (q_method_t)QDOCKWIDGET_allowedAreas);
   QC_QDockWidget->addMethod("features",                    (q_method_t)QDOCKWIDGET_features);
   QC_QDockWidget->addMethod("isAreaAllowed",               (q_method_t)QDOCKWIDGET_isAreaAllowed);
   QC_QDockWidget->addMethod("isFloating",                  (q_method_t)QDOCKWIDGET_isFloating);
   QC_QDockWidget->addMethod("setAllowedAreas",             (q_method_t)QDOCKWIDGET_setAllowedAreas);
   QC_QDockWidget->addMethod("setFeatures",                 (q_method_t)QDOCKWIDGET_setFeatures);
   QC_QDockWidget->addMethod("setFloating",                 (q_method_t)QDOCKWIDGET_setFloating);
   QC_QDockWidget->addMethod("setTitleBarWidget",           (q_method_t)QDOCKWIDGET_setTitleBarWidget);
   QC_QDockWidget->addMethod("setWidget",                   (q_method_t)QDOCKWIDGET_setWidget);
   QC_QDockWidget->addMethod("titleBarWidget",              (q_method_t)QDOCKWIDGET_titleBarWidget);
   QC_QDockWidget->addMethod("toggleViewAction",            (q_method_t)QDOCKWIDGET_toggleViewAction);
   QC_QDockWidget->addMethod("widget",                      (q_method_t)QDOCKWIDGET_widget);

   // private methods
   QC_QDockWidget->addMethod("initStyleOption",             (q_method_t)QDOCKWIDGET_initStyleOption, true);

   return QC_QDockWidget;
}

QoreNamespace *initQDockWidgetNS(QoreClass *qwidget) {
   QoreNamespace *ns = new QoreNamespace("QDockWidget");
   ns->addSystemClass(initQDockWidgetClass(QC_QWidget));

   // QDockWidgetFeatures enum
   ns->addConstant("DockWidgetClosable",         new QoreBigIntNode(QDockWidget::DockWidgetClosable));
   ns->addConstant("DockWidgetMovable",          new QoreBigIntNode(QDockWidget::DockWidgetMovable));
   ns->addConstant("DockWidgetFloatable",        new QoreBigIntNode(QDockWidget::DockWidgetFloatable));
   ns->addConstant("DockWidgetVerticalTitleBar", new QoreBigIntNode(QDockWidget::DockWidgetVerticalTitleBar));
   ns->addConstant("DockWidgetFeatureMask",      new QoreBigIntNode(QDockWidget::DockWidgetFeatureMask));
   ns->addConstant("AllDockWidgetFeatures",      new QoreBigIntNode(QDockWidget::AllDockWidgetFeatures));
   ns->addConstant("NoDockWidgetFeatures",       new QoreBigIntNode(QDockWidget::NoDockWidgetFeatures));
   //ns->addConstant("Reserved",                   new QoreBigIntNode(QDockWidget::Reserved));

   return ns;
}
