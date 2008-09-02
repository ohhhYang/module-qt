/*
 QC_QLCDNumber.cc
 
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

#include "QC_QLCDNumber.h"
#include "QC_QWidget.h"

qore_classid_t CID_QLCDNUMBER;

//QLCDNumber ( QWidget * parent = 0 )
//QLCDNumber ( uint numDigits, QWidget * parent = 0 )
static void QLCDNUMBER_constructor(class QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreQLCDNumber *qlcdn;
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() != NT_OBJECT)
   {
      int num_digits = p->getAsInt();
      QoreObject *o = test_object_param(params, 1);
      QoreAbstractQWidget *parent = o ? (QoreAbstractQWidget *)o->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
      if (*xsink)
	 return;
      ReferenceHolder<QoreAbstractQWidget> holder(parent, xsink);
      qlcdn = new QoreQLCDNumber(self, num_digits, parent ? parent->getQWidget() : 0);
   }
   else {
      const QoreObject *o = reinterpret_cast<const QoreObject *>(p);
      QoreAbstractQWidget *parent = o ? (QoreAbstractQWidget *)o->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
      if (*xsink)
	 return;
      ReferenceHolder<QoreAbstractQWidget> holder(parent, xsink);
      qlcdn = new QoreQLCDNumber(self, parent ? parent->getQWidget() : 0);
   }

   self->setPrivate(CID_QLCDNUMBER, qlcdn);
}

static void QLCDNUMBER_copy(class QoreObject *self, class QoreObject *old, class QoreQLCDNumber *qlcdn, ExceptionSink *xsink)
{
   xsink->raiseException("QLCDNUMBER-COPY-ERROR", "objects of this class cannot be copied");
}

static class AbstractQoreNode *QLCDNUMBER_setSegmentStyle(class QoreObject *self, class QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (!is_nothing(p))
      qlcdn->qobj->setSegmentStyle((QLCDNumber::SegmentStyle)p->getAsInt());
   return 0;
}

static class AbstractQoreNode *QLCDNUMBER_setNumDigits(class QoreObject *self, class QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (!is_nothing(p))
      qlcdn->qobj->setNumDigits(p->getAsInt());
   return 0;
}

static class AbstractQoreNode *QLCDNUMBER_numDigits(class QoreObject *self, class QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qlcdn->qobj->numDigits());
}

static class AbstractQoreNode *QLCDNUMBER_smallDecimalPoint(class QoreObject *self, class QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qlcdn->qobj->smallDecimalPoint());
}

static class AbstractQoreNode *QLCDNUMBER_value(class QoreObject *self, class QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreFloatNode(qlcdn->qobj->value());
}

static class AbstractQoreNode *QLCDNUMBER_intValue(class QoreObject *self, class QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qlcdn->qobj->intValue());
}

static class AbstractQoreNode *QLCDNUMBER_setMode(class QoreObject *self, class QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (!is_nothing(p))
      qlcdn->qobj->setMode((QLCDNumber::Mode)p->getAsInt());
   return 0;
}

static class AbstractQoreNode *QLCDNUMBER_checkOverflow(class QoreObject *self, class QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool rc;
   if (p && p->getType() == NT_FLOAT)
      rc = qlcdn->qobj->checkOverflow(reinterpret_cast<const QoreFloatNode *>(p)->f);
   else
      rc = qlcdn->qobj->checkOverflow(p ? p->getAsInt() : 0);
   return get_bool_node(rc);
}

// slots

//void display ( int num )
static AbstractQoreNode *QLCDNUMBER_display(QoreObject *self, QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   qore_type_t ptype = p ? p->getType() : 0;
   if (ptype == NT_FLOAT)
      qlcdn->qobj->display(reinterpret_cast<const QoreFloatNode *>(p)->f);
   else if (ptype == NT_STRING)
      qlcdn->qobj->display((reinterpret_cast<const QoreStringNode *>(p))->getBuffer());
   else {
      int num = p ? p->getAsInt() : 0;
      qlcdn->qobj->display(num);
   }
   return 0;
}

//void setBinMode ()
static AbstractQoreNode *QLCDNUMBER_setBinMode(QoreObject *self, QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   qlcdn->qobj->setBinMode();
   return 0;
}

//void setDecMode ()
static AbstractQoreNode *QLCDNUMBER_setDecMode(QoreObject *self, QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   qlcdn->qobj->setDecMode();
   return 0;
}

//void setHexMode ()
static AbstractQoreNode *QLCDNUMBER_setHexMode(QoreObject *self, QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   qlcdn->qobj->setHexMode();
   return 0;
}

//void setOctMode ()
static AbstractQoreNode *QLCDNUMBER_setOctMode(QoreObject *self, QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   qlcdn->qobj->setOctMode();
   return 0;
}

//void setSmallDecimalPoint ( bool )
static AbstractQoreNode *QLCDNUMBER_setSmallDecimalPoint(QoreObject *self, QoreQLCDNumber *qlcdn, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool b = p ? p->getAsBool() : 0;
   qlcdn->qobj->setSmallDecimalPoint(b);
   return 0;
}

class QoreClass *initQLCDNumberClass(class QoreClass *qframe)
{
   QORE_TRACE("initQLCDNumberClass()");
   
   class QoreClass *QC_QLCDNumber = new QoreClass("QLCDNumber", QDOM_GUI);
   CID_QLCDNUMBER = QC_QLCDNumber->getID();

   QC_QLCDNumber->addBuiltinVirtualBaseClass(qframe);

   QC_QLCDNumber->setConstructor(QLCDNUMBER_constructor);
   QC_QLCDNumber->setCopy((q_copy_t)QLCDNUMBER_copy);

   QC_QLCDNumber->addMethod("setSegmentStyle",        (q_method_t)QLCDNUMBER_setSegmentStyle);
   QC_QLCDNumber->addMethod("setNumDigits",           (q_method_t)QLCDNUMBER_setNumDigits);
   QC_QLCDNumber->addMethod("numDigits",              (q_method_t)QLCDNUMBER_numDigits);
   QC_QLCDNumber->addMethod("smallDecimalPoint",      (q_method_t)QLCDNUMBER_smallDecimalPoint);
   QC_QLCDNumber->addMethod("value",                  (q_method_t)QLCDNUMBER_value);
   QC_QLCDNumber->addMethod("intValue",               (q_method_t)QLCDNUMBER_intValue);
   QC_QLCDNumber->addMethod("setMode",                (q_method_t)QLCDNUMBER_setMode);
   QC_QLCDNumber->addMethod("checkOverflow",          (q_method_t)QLCDNUMBER_checkOverflow);

   // slots
   QC_QLCDNumber->addMethod("display",                (q_method_t)QLCDNUMBER_display);
   QC_QLCDNumber->addMethod("setBinMode",             (q_method_t)QLCDNUMBER_setBinMode);
   QC_QLCDNumber->addMethod("setDecMode",             (q_method_t)QLCDNUMBER_setDecMode);
   QC_QLCDNumber->addMethod("setHexMode",             (q_method_t)QLCDNUMBER_setHexMode);
   QC_QLCDNumber->addMethod("setOctMode",             (q_method_t)QLCDNUMBER_setOctMode);
   QC_QLCDNumber->addMethod("setSmallDecimalPoint",   (q_method_t)QLCDNUMBER_setSmallDecimalPoint);


   return QC_QLCDNumber;
}
