/*
 QC_QSlider.cc
 
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

#include "QC_QSlider.h"
#include "QC_QAbstractSlider.h"
#include "QC_QWidget.h"

qore_classid_t CID_QSLIDER;

static void QSLIDER_constructor(class QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreQSlider *qs;
   const AbstractQoreNode *p0 = get_param(params, 0);
   const AbstractQoreNode *p1 = get_param(params, 1);
   QoreAbstractQWidget *parent;

   if (p0 && p0->getType() == NT_OBJECT)
   {
      parent = p0 ? (QoreAbstractQWidget *)(reinterpret_cast<const QoreObject *>(p0))->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
      if (!parent) {
	 xsink->raiseException("QSLIDER-CONSTRUCTOR-ERROR", "class '%s' passed as first parameter of QSlider::constructor() is not a subclass of QWidget", (reinterpret_cast<const QoreObject *>(p0))->getClassName());
	 return;
      }
      ReferenceHolder<QoreAbstractQWidget> holder(parent, xsink);
      qs = new QoreQSlider(self, parent->getQWidget());
   }
   else if (p1 && p1->getType() == NT_OBJECT) {
      parent = p1 ? (QoreAbstractQWidget *)(reinterpret_cast<const QoreObject *>(p1))->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
      if (!parent) {
	 xsink->raiseException("QSLIDER-CONSTRUCTOR-ERROR", "class '%s' passed as second parameter of QSlider::constructor() is not a subclass of QWidget", (reinterpret_cast<const QoreObject *>(p1))->getClassName());
	 return;
      }
      ReferenceHolder<QoreAbstractQWidget> holder(parent, xsink);
      int orientation = p0 ? p0->getAsInt() : 0;
      qs = new QoreQSlider(self, (Qt::Orientation)orientation, parent->getQWidget());
   }
   else
      qs = new QoreQSlider(self, (Qt::Orientation)(p0 ? p0->getAsInt() : 0));

   self->setPrivate(CID_QSLIDER, qs);
}

static void QSLIDER_copy(class QoreObject *self, class QoreObject *old, class QoreQSlider *qs, ExceptionSink *xsink)
{
   xsink->raiseException("QSLIDER-COPY-ERROR", "objects of this class cannot be copied");
}

//void setTickInterval ( int ti )
static AbstractQoreNode *QSLIDER_setTickInterval(QoreObject *self, QoreQSlider *qs, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int ti = p ? p->getAsInt() : 0;
   qs->qobj->setTickInterval(ti);
   return 0;
}

//void setTickPosition ( TickPosition position )
static AbstractQoreNode *QSLIDER_setTickPosition(QoreObject *self, QoreQSlider *qs, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QSlider::TickPosition position = (QSlider::TickPosition)(p ? p->getAsInt() : 0);
   qs->qobj->setTickPosition(position);
   return 0;
}

//int tickInterval () const
static AbstractQoreNode *QSLIDER_tickInterval(QoreObject *self, QoreQSlider *qs, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qs->qobj->tickInterval());
}

//TickPosition tickPosition () const
static AbstractQoreNode *QSLIDER_tickPosition(QoreObject *self, QoreQSlider *qs, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qs->qobj->tickPosition());
}

class QoreClass *initQSliderClass(class QoreClass *qabstractslider)
{
   QORE_TRACE("initQSliderClass()");
   
   class QoreClass *QC_QSlider = new QoreClass("QSlider", QDOM_GUI);

   CID_QSLIDER = QC_QSlider->getID();

   QC_QSlider->addBuiltinVirtualBaseClass(qabstractslider);

   QC_QSlider->setConstructor(QSLIDER_constructor);
   QC_QSlider->setCopy((q_copy_t)QSLIDER_copy);

   QC_QSlider->addMethod("setTickInterval",             (q_method_t)QSLIDER_setTickInterval);
   QC_QSlider->addMethod("setTickPosition",             (q_method_t)QSLIDER_setTickPosition);
   QC_QSlider->addMethod("tickInterval",                (q_method_t)QSLIDER_tickInterval);
   QC_QSlider->addMethod("tickPosition",                (q_method_t)QSLIDER_tickPosition);


   return QC_QSlider;
}
