/*
 QC_QDateTime.cc
 
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
#include "QC_QDateTime.h"
#include "QC_QDate.h"
#include "QC_QTime.h"

#include "qt-core.h"

DLLLOCAL qore_classid_t CID_QDATETIME;

static void QDATETIME_constructor(class QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreQDateTime *qdt;

   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p))
      qdt = new QoreQDateTime();
   else if (p->getType() == NT_DATE) {
      const DateTimeNode *dt = reinterpret_cast<const DateTimeNode *>(p);
      qdt = new QoreQDateTime(QDate(dt->getYear(), dt->getMonth(), dt->getDay()), 
			      QTime(dt->getHour(), dt->getMinute(), dt->getSecond(), dt->getMillisecond()));
   }
   else if (p->getType() != NT_OBJECT) {
      xsink->raiseException("QDATETIME-CONSTRUCTOR-ERROR", "don't know how to handle argument of type '%s' in QDateTime::constructor()", p->getTypeName());
      return;
   }
   else {
      QoreQDate *date = p ? (QoreQDate *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QDATE, xsink) : 0;
      if (!date) {
	 xsink->raiseException("QDATETIME-CONSTRUCTOR-ERROR", "don't know how to handle argument of class '%s' in QDateTime::constructor() as first argument (expecting an object derived from QDate)", (reinterpret_cast<const QoreObject *>(p))->getClassName());
	 return;
      }
      ReferenceHolder<QoreQDate> date_holder(date, xsink);

      p = get_param(params, 1);
      if (!p || p->getType() != NT_OBJECT) {
	 qdt = new QoreQDateTime(*date);
      }
      else {
	 QoreQTime *time = p ? (QoreQTime *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QTIME, xsink) : 0;
	 if (!time) {
	    xsink->raiseException("QDATETIME-CONSTRUCTOR-ERROR", "don't know how to handle argument of class '%s' in QDateTime::constructor() as second argument (expecting an object derived from QTime)", (reinterpret_cast<const QoreObject *>(p))->getClassName());
	    return;
	 }
	 ReferenceHolder<QoreQTime> time_holder(time, xsink);

	 p = get_param(params, 2);
	 Qt::TimeSpec spec = !is_nothing(p) ? (Qt::TimeSpec)p->getAsInt() : Qt::LocalTime;
	 qdt = new QoreQDateTime(*date, *time, spec);
      }
   }
   self->setPrivate(CID_QDATETIME, qdt);
}

static void QDATETIME_copy(class QoreObject *self, class QoreObject *old, class QoreQDateTime *qf, ExceptionSink *xsink)
{
   self->setPrivate(CID_QDATETIME, new QoreQDateTime(*qf));
   //xsink->raiseException("QDATETIME-COPY-ERROR", "objects of this class cannot be copied");
}

//QDateTime addDays ( int ndays ) const
static AbstractQoreNode *QDATETIME_addDays(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int ndays = p ? p->getAsInt() : 0;
   QoreObject *o_qdt = new QoreObject(self->getClass(CID_QDATETIME), getProgram());
   QoreQDateTime *q_qdt = new QoreQDateTime(qdt->addDays(ndays));
   o_qdt->setPrivate(CID_QDATETIME, q_qdt);
   return o_qdt;
}

//QDateTime addMSecs ( qint64 msecs ) const
static AbstractQoreNode *QDATETIME_addMSecs(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int64 msecs = p ? p->getAsBigInt() : 0;
   QoreObject *o_qdt = new QoreObject(self->getClass(CID_QDATETIME), getProgram());
   QoreQDateTime *q_qdt = new QoreQDateTime(qdt->addMSecs(msecs));
   o_qdt->setPrivate(CID_QDATETIME, q_qdt);
   return o_qdt;
}

//QDateTime addMonths ( int nmonths ) const
static AbstractQoreNode *QDATETIME_addMonths(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int nmonths = p ? p->getAsInt() : 0;
   QoreObject *o_qdt = new QoreObject(self->getClass(CID_QDATETIME), getProgram());
   QoreQDateTime *q_qdt = new QoreQDateTime(qdt->addMonths(nmonths));
   o_qdt->setPrivate(CID_QDATETIME, q_qdt);
   return o_qdt;
}

//QDateTime addSecs ( int s ) const
static AbstractQoreNode *QDATETIME_addSecs(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int s = p ? p->getAsInt() : 0;
   QoreObject *o_qdt = new QoreObject(self->getClass(CID_QDATETIME), getProgram());
   QoreQDateTime *q_qdt = new QoreQDateTime(qdt->addSecs(s));
   o_qdt->setPrivate(CID_QDATETIME, q_qdt);
   return o_qdt;
}

//QDateTime addYears ( int nyears ) const
static AbstractQoreNode *QDATETIME_addYears(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int nyears = p ? p->getAsInt() : 0;
   QoreObject *o_qdt = new QoreObject(self->getClass(CID_QDATETIME), getProgram());
   QoreQDateTime *q_qdt = new QoreQDateTime(qdt->addYears(nyears));
   o_qdt->setPrivate(CID_QDATETIME, q_qdt);
   return o_qdt;
}

//QDate date () const
static AbstractQoreNode *QDATETIME_date(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qd = new QoreObject(QC_QDate, getProgram());
   QoreQDate *q_qd = new QoreQDate(qdt->date());
   o_qd->setPrivate(CID_QDATE, q_qd);
   return o_qd;
}

//int daysTo ( const QDateTime & other ) const
static AbstractQoreNode *QDATETIME_daysTo(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQDateTime *other = p ? (QoreQDateTime *)p->getReferencedPrivateData(CID_QDATETIME, xsink) : 0;
   if (!other) {
      if (!xsink->isException())
         xsink->raiseException("QDATETIME-DAYSTO-PARAM-ERROR", "expecting a QDateTime object as first argument to QDateTime::daysTo()");
      return 0;
   }
   ReferenceHolder<QoreQDateTime> holder(other, xsink);
   return new QoreBigIntNode(qdt->daysTo(*(static_cast<QDateTime *>(other))));
}

//bool isNull () const
static AbstractQoreNode *QDATETIME_isNull(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qdt->isNull());
}

//bool isValid () const
static AbstractQoreNode *QDATETIME_isValid(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qdt->isValid());
}

//int secsTo ( const QDateTime & other ) const
static AbstractQoreNode *QDATETIME_secsTo(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQDateTime *other = p ? (QoreQDateTime *)p->getReferencedPrivateData(CID_QDATETIME, xsink) : 0;
   if (!other) {
      if (!xsink->isException())
         xsink->raiseException("QDATETIME-SECSTO-PARAM-ERROR", "expecting a QDateTime object as first argument to QDateTime::secsTo()");
      return 0;
   }
   ReferenceHolder<QoreQDateTime> holder(other, xsink);
   return new QoreBigIntNode(qdt->secsTo(*(static_cast<QDateTime *>(other))));
}

//void setDate ( const QDate & date )
static AbstractQoreNode *QDATETIME_setDate(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQDate *date = p ? (QoreQDate *)p->getReferencedPrivateData(CID_QDATE, xsink) : 0;
   if (!date) {
      if (!xsink->isException())
         xsink->raiseException("QDATETIME-SETDATE-PARAM-ERROR", "expecting a QDate object as first argument to QDateTime::setDate()");
      return 0;
   }
   ReferenceHolder<QoreQDate> holder(date, xsink);
   qdt->setDate(*(static_cast<QDate *>(date)));
   return 0;
}

//void setTime ( const QTime & time )
static AbstractQoreNode *QDATETIME_setTime(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQTime *time = p ? (QoreQTime *)p->getReferencedPrivateData(CID_QTIME, xsink) : 0;
   if (!time) {
      if (!xsink->isException())
         xsink->raiseException("QDATETIME-SETTIME-PARAM-ERROR", "expecting a QTime object as first argument to QDateTime::setTime()");
      return 0;
   }
   ReferenceHolder<QoreQTime> holder(time, xsink);
   qdt->setTime(*(static_cast<QTime *>(time)));
   return 0;
}

//void setTimeSpec ( Qt::TimeSpec spec )
static AbstractQoreNode *QDATETIME_setTimeSpec(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::TimeSpec spec = (Qt::TimeSpec)(p ? p->getAsInt() : 0);
   qdt->setTimeSpec(spec);
   return 0;
}

//void setTime_t ( uint seconds )
static AbstractQoreNode *QDATETIME_setTime_t(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   unsigned seconds = p ? p->getAsBigInt() : 0;
   qdt->setTime_t(seconds);
   return 0;
}

//QTime time () const
static AbstractQoreNode *QDATETIME_time(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qt = new QoreObject(QC_QTime, getProgram());
   QoreQTime *q_qt = new QoreQTime(qdt->time());
   o_qt->setPrivate(CID_QTIME, q_qt);
   return o_qt;
}

//Qt::TimeSpec timeSpec () const
static AbstractQoreNode *QDATETIME_timeSpec(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qdt->timeSpec());
}

//QDateTime toLocalTime () const
static AbstractQoreNode *QDATETIME_toLocalTime(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qdt = new QoreObject(self->getClass(CID_QDATETIME), getProgram());
   QoreQDateTime *q_qdt = new QoreQDateTime(qdt->toLocalTime());
   o_qdt->setPrivate(CID_QDATETIME, q_qdt);
   return o_qdt;
}

//QString toString ( const QString & format ) const
//QString toString ( Qt::DateFormat format = Qt::TextDate ) const
static AbstractQoreNode *QDATETIME_toString(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   {
      QString format;
      if (!get_qstring(p, format, xsink, true))
	 return new QoreStringNode(qdt->toString(format).toUtf8().data(), QCS_UTF8);
   }
   if (*xsink)
      return 0;
   Qt::DateFormat format = (Qt::DateFormat)(p ? p->getAsInt() : 0);
   return new QoreStringNode(qdt->toString(format).toUtf8().data(), QCS_UTF8);
}

//QDateTime toTimeSpec ( Qt::TimeSpec specification ) const
static AbstractQoreNode *QDATETIME_toTimeSpec(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::TimeSpec specification = (Qt::TimeSpec)(p ? p->getAsInt() : 0);
   QoreObject *o_qdt = new QoreObject(self->getClass(CID_QDATETIME), getProgram());
   QoreQDateTime *q_qdt = new QoreQDateTime(qdt->toTimeSpec(specification));
   o_qdt->setPrivate(CID_QDATETIME, q_qdt);
   return o_qdt;
}

//uint toTime_t () const
static AbstractQoreNode *QDATETIME_toTime_t(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qdt->toTime_t());
}

//QDateTime toUTC () const
static AbstractQoreNode *QDATETIME_toUTC(QoreObject *self, QoreQDateTime *qdt, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qdt = new QoreObject(self->getClass(CID_QDATETIME), getProgram());
   QoreQDateTime *q_qdt = new QoreQDateTime(qdt->toUTC());
   o_qdt->setPrivate(CID_QDATETIME, q_qdt);
   return o_qdt;
}

class QoreClass *initQDateTimeClass()
{
   QORE_TRACE("initQDateTimeClass()");
   
   class QoreClass *QC_QDateTime = new QoreClass("QDateTime", QDOM_GUI);
   CID_QDATETIME = QC_QDateTime->getID();
   QC_QDateTime->setConstructor(QDATETIME_constructor);
   QC_QDateTime->setCopy((q_copy_t)QDATETIME_copy);

   QC_QDateTime->addMethod("addDays",                     (q_method_t)QDATETIME_addDays);
   QC_QDateTime->addMethod("addMSecs",                    (q_method_t)QDATETIME_addMSecs);
   QC_QDateTime->addMethod("addMonths",                   (q_method_t)QDATETIME_addMonths);
   QC_QDateTime->addMethod("addSecs",                     (q_method_t)QDATETIME_addSecs);
   QC_QDateTime->addMethod("addYears",                    (q_method_t)QDATETIME_addYears);
   QC_QDateTime->addMethod("date",                        (q_method_t)QDATETIME_date);
   QC_QDateTime->addMethod("daysTo",                      (q_method_t)QDATETIME_daysTo);
   QC_QDateTime->addMethod("isNull",                      (q_method_t)QDATETIME_isNull);
   QC_QDateTime->addMethod("isValid",                     (q_method_t)QDATETIME_isValid);
   QC_QDateTime->addMethod("secsTo",                      (q_method_t)QDATETIME_secsTo);
   QC_QDateTime->addMethod("setDate",                     (q_method_t)QDATETIME_setDate);
   QC_QDateTime->addMethod("setTime",                     (q_method_t)QDATETIME_setTime);
   QC_QDateTime->addMethod("setTimeSpec",                 (q_method_t)QDATETIME_setTimeSpec);
   QC_QDateTime->addMethod("setTime_t",                   (q_method_t)QDATETIME_setTime_t);
   QC_QDateTime->addMethod("time",                        (q_method_t)QDATETIME_time);
   QC_QDateTime->addMethod("timeSpec",                    (q_method_t)QDATETIME_timeSpec);
   QC_QDateTime->addMethod("toLocalTime",                 (q_method_t)QDATETIME_toLocalTime);
   QC_QDateTime->addMethod("toString",                    (q_method_t)QDATETIME_toString);
   QC_QDateTime->addMethod("toTimeSpec",                  (q_method_t)QDATETIME_toTimeSpec);
   QC_QDateTime->addMethod("toTime_t",                    (q_method_t)QDATETIME_toTime_t);
   QC_QDateTime->addMethod("toUTC",                       (q_method_t)QDATETIME_toUTC);


   return QC_QDateTime;
}
