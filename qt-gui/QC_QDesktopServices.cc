/*
 QC_QDesktopServices.cc
 
  Qore Programming Language

 Copyright (C) 2003 - 2008 David Nichols

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

#include "QC_QDesktopServices.h"
#include "QC_QUrl.h"

qore_classid_t CID_QDESKTOPSERVICES;
QoreClass *QC_QDesktopServices = 0;

static void QDESKTOPSERVICES_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   xsink->raiseException("QDESKTOPSERVICES-CONSTRUCTOR-ERROR", "this is an abstract class and cannot be instantiated");
}

static void QDESKTOPSERVICES_copy(class QoreObject *self, class QoreObject *old, class QoreQDial *qd, ExceptionSink *xsink) {
   xsink->raiseException("QDESKTOPSERVICES-COPY-ERROR", "objects of this class cannot be copied");
}

//QString displayName ( StandardLocation type )
static AbstractQoreNode *f_QDesktopServices_displayName(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QDesktopServices::StandardLocation type = (QDesktopServices::StandardLocation)(p ? p->getAsInt() : 0);
   return new QoreStringNode(QDesktopServices::displayName(type).toUtf8().data(), QCS_UTF8);
}

//bool openUrl ( const QUrl & url )
static AbstractQoreNode *f_QDesktopServices_openUrl(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QUrl url;
   if (get_qurl(p, url, xsink))
      return 0;
   return get_bool_node(QDesktopServices::openUrl(url));
}

//void setUrlHandler ( const QString & scheme, QObject * receiver, const char * method )
static AbstractQoreNode *f_QDesktopServices_setUrlHandler(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString scheme;
   if (get_qstring(p, scheme, xsink))
      return 0;
   p = get_param(params, 1);
   QoreAbstractQObject *receiver = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (!receiver) {
      if (!xsink->isException())
         xsink->raiseException("QDESKTOPSERVICES-SETURLHANDLER-PARAM-ERROR", "expecting a QObject object as second argument to QDesktopServices::setUrlHandler()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> receiverHolder(static_cast<AbstractPrivateData *>(receiver), xsink);
   p = get_param(params, 2);
   if (!p || p->getType() != NT_STRING) {
      xsink->raiseException("QDESKTOPSERVICES-SETURLHANDLER-PARAM-ERROR", "expecting a string as third argument to QDesktopServices::setUrlHandler()");
      return 0;
   }
   const char *method = reinterpret_cast<const QoreStringNode *>(p)->getBuffer();
   QDesktopServices::setUrlHandler(scheme, receiver->getQObject(), method);
   return 0;
}

//QString storageLocation ( StandardLocation type )
static AbstractQoreNode *f_QDesktopServices_storageLocation(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QDesktopServices::StandardLocation type = (QDesktopServices::StandardLocation)(p ? p->getAsInt() : 0);
   return new QoreStringNode(QDesktopServices::storageLocation(type).toUtf8().data(), QCS_UTF8);
}

//void unsetUrlHandler ( const QString & scheme )
static AbstractQoreNode *f_QDesktopServices_unsetUrlHandler(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString scheme;
   if (get_qstring(p, scheme, xsink))
      return 0;
   QDesktopServices::unsetUrlHandler(scheme);
   return 0;
}

QoreClass *initQDesktopServicesClass() {
   QC_QDesktopServices = new QoreClass("QDesktopServices", QDOM_GUI);
   CID_QDESKTOPSERVICES = QC_QDesktopServices->getID();

   QC_QDesktopServices->setConstructor(QDESKTOPSERVICES_constructor);
   QC_QDesktopServices->setCopy((q_copy_t)QDESKTOPSERVICES_copy);

   QC_QDesktopServices->addStaticMethod("displayName",                  f_QDesktopServices_displayName);
   QC_QDesktopServices->addStaticMethod("openUrl",                      f_QDesktopServices_openUrl);
   QC_QDesktopServices->addStaticMethod("setUrlHandler",                f_QDesktopServices_setUrlHandler);
   QC_QDesktopServices->addStaticMethod("storageLocation",              f_QDesktopServices_storageLocation);
   QC_QDesktopServices->addStaticMethod("unsetUrlHandler",              f_QDesktopServices_unsetUrlHandler);

   return QC_QDesktopServices;
}
