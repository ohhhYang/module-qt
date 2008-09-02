/*
 QC_QScrollArea.cc
 
 Qore Programming Language
 
 Copyright 2003 - 2008 David Nichols
 
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

#include <qore/Qore.h>

#include "QC_QScrollArea.h"
#include "QC_QWidget.h"

#include "qore-qt-gui.h"

qore_classid_t CID_QSCROLLAREA;
class QoreClass *QC_QScrollArea = 0;

//QScrollArea ( QWidget * parent = 0 )
static void QSCROLLAREA_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   const QoreObject *o = dynamic_cast<const QoreObject *>(p);
   QoreQWidget *parent = o ? (QoreQWidget *)o->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return;
   if (!is_nothing(p) && !parent) {
      xsink->raiseException("QSCROLLAREA-CONSTRUCTOR-PARAM-ERROR", "expecting either NOTHING or a QWidget object as first argument to QScrollArea::constructor()");
      return;
   }
   ReferenceHolder<QoreQWidget> parentHolder(parent, xsink);
   self->setPrivate(CID_QSCROLLAREA, new QoreQScrollArea(self, parent ? parent->getQWidget() : 0));
   return;
}

static void QSCROLLAREA_copy(class QoreObject *self, class QoreObject *old, class QoreQScrollArea *qsa, ExceptionSink *xsink)
{
   xsink->raiseException("QSCROLLAREA-COPY-ERROR", "objects of this class cannot be copied");
}

//Qt::Alignment alignment () const
static AbstractQoreNode *QSCROLLAREA_alignment(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qsa->qobj->alignment());
}

//void ensureVisible ( int x, int y, int xmargin = 50, int ymargin = 50 )
static AbstractQoreNode *QSCROLLAREA_ensureVisible(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int x = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int y = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int xmargin = !is_nothing(p) ? p->getAsInt() : 50;
   p = get_param(params, 3);
   int ymargin = !is_nothing(p) ? p->getAsInt() : 50;
   qsa->qobj->ensureVisible(x, y, xmargin, ymargin);
   return 0;
}

//void ensureWidgetVisible ( QWidget * childWidget, int xmargin = 50, int ymargin = 50 )
static AbstractQoreNode *QSCROLLAREA_ensureWidgetVisible(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o = test_object_param(params, 0);
   QoreQWidget *childWidget = o ? (QoreQWidget *)o->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!childWidget) {
      if (!xsink->isException())
         xsink->raiseException("QSCROLLAREA-ENSUREWIDGETVISIBLE-PARAM-ERROR", "expecting a QWidget object as first argument to QScrollArea::ensureWidgetVisible()");
      return 0;
   }
   ReferenceHolder<QoreQWidget> childWidgetHolder(childWidget, xsink);

   const AbstractQoreNode *p = get_param(params, 1);
   int xmargin = !is_nothing(p) ? p->getAsInt() : 50;
   p = get_param(params, 2);
   int ymargin = !is_nothing(p) ? p->getAsInt() : 50;
   qsa->qobj->ensureWidgetVisible(static_cast<QWidget *>(childWidget->getQWidget()), xmargin, ymargin);
   return 0;
}

//void setAlignment ( Qt::Alignment )
static AbstractQoreNode *QSCROLLAREA_setAlignment(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::Alignment alignment = (Qt::Alignment)(p ? p->getAsInt() : 0);
   qsa->qobj->setAlignment(alignment);
   return 0;
}

//void setWidget ( QWidget * widget )
static AbstractQoreNode *QSCROLLAREA_setWidget(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQWidget *widget = p ? (QoreQWidget *)p->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QSCROLLAREA-SETWIDGET-PARAM-ERROR", "expecting a QWidget object as first argument to QScrollArea::setWidget()");
      return 0;
   }
   ReferenceHolder<QoreQWidget> widgetHolder(widget, xsink);
   //printd(5, "QScrollArea::setWidget(%08p) this=%08p\n", qsa, widget->getQWidget());
   qsa->qobj->setWidget(static_cast<QWidget *>(widget->getQWidget()));
   return 0;
}

//void setWidgetResizable ( bool resizable )
static AbstractQoreNode *QSCROLLAREA_setWidgetResizable(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool resizable = p ? p->getAsBool() : false;
   qsa->qobj->setWidgetResizable(resizable);
   return 0;
}

//QWidget * takeWidget ()
static AbstractQoreNode *QSCROLLAREA_takeWidget(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   QWidget *qt_qobj = qsa->qobj->takeWidget();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   assert(rv_obj);
   rv_obj->ref();
   return rv_obj;
}

//QWidget * widget () const
static AbstractQoreNode *QSCROLLAREA_widget(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   QWidget *qt_qobj = qsa->qobj->widget();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   assert(rv_obj);
   rv_obj->ref();
   return rv_obj;
}

//bool widgetResizable () const
static AbstractQoreNode *QSCROLLAREA_widgetResizable(QoreObject *self, QoreQScrollArea *qsa, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qsa->qobj->widgetResizable());
}

QoreClass *initQScrollAreaClass(QoreClass *qabstractscrollarea)
{
   QC_QScrollArea = new QoreClass("QScrollArea", QDOM_GUI);
   CID_QSCROLLAREA = QC_QScrollArea->getID();

   QC_QScrollArea->addBuiltinVirtualBaseClass(qabstractscrollarea);

   QC_QScrollArea->setConstructor(QSCROLLAREA_constructor);
   QC_QScrollArea->setCopy((q_copy_t)QSCROLLAREA_copy);

   QC_QScrollArea->addMethod("alignment",                   (q_method_t)QSCROLLAREA_alignment);
   QC_QScrollArea->addMethod("ensureVisible",               (q_method_t)QSCROLLAREA_ensureVisible);
   QC_QScrollArea->addMethod("ensureWidgetVisible",         (q_method_t)QSCROLLAREA_ensureWidgetVisible);
   QC_QScrollArea->addMethod("setAlignment",                (q_method_t)QSCROLLAREA_setAlignment);
   QC_QScrollArea->addMethod("setWidget",                   (q_method_t)QSCROLLAREA_setWidget);
   QC_QScrollArea->addMethod("setWidgetResizable",          (q_method_t)QSCROLLAREA_setWidgetResizable);
   QC_QScrollArea->addMethod("takeWidget",                  (q_method_t)QSCROLLAREA_takeWidget);
   QC_QScrollArea->addMethod("widget",                      (q_method_t)QSCROLLAREA_widget);
   QC_QScrollArea->addMethod("widgetResizable",             (q_method_t)QSCROLLAREA_widgetResizable);

   return QC_QScrollArea;
}
