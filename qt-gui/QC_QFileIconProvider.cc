/*
 QC_QFileIconProvider.cc
 
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

#include "QC_QFileIconProvider.h"
#include "QC_QFileInfo.h"

qore_classid_t CID_QFILEICONPROVIDER;
QoreClass *QC_QFileIconProvider = 0;

//QFileIconProvider ()
static void QFILEICONPROVIDER_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   self->setPrivate(CID_QFILEICONPROVIDER, new QoreQFileIconProvider(self));
   return;
}

static void QFILEICONPROVIDER_copy(QoreObject *self, QoreObject *old, QoreQFileIconProvider *qfip, ExceptionSink *xsink) {
   xsink->raiseException("QFILEICONPROVIDER-COPY-ERROR", "objects of this class cannot be copied");
}

//virtual QIcon icon ( IconType type ) const
//virtual QIcon icon ( const QFileInfo & info ) const
static AbstractQoreNode *QFILEICONPROVIDER_icon(QoreObject *self, QoreAbstractQFileIconProvider *qfip, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQFileInfo *info = (QoreQFileInfo *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QFILEINFO, xsink);
      if (!info) {
         if (!xsink->isException())
            xsink->raiseException("QFILEICONPROVIDER-ICON-PARAM-ERROR", "QFileIconProvider::icon() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
         return 0;
      }
      ReferenceHolder<AbstractPrivateData> infoHolder(static_cast<AbstractPrivateData *>(info), xsink);
      return return_object(QC_QIcon, new QoreQIcon(qfip->getQFileIconProvider()->icon(*(static_cast<QFileInfo *>(info)))));
   }
   QFileIconProvider::IconType type = (QFileIconProvider::IconType)(p ? p->getAsInt() : 0);
   return return_object(QC_QIcon, new QoreQIcon(qfip->getQFileIconProvider()->icon(type)));
}

//virtual QString type ( const QFileInfo & info ) const
static AbstractQoreNode *QFILEICONPROVIDER_type(QoreObject *self, QoreAbstractQFileIconProvider *qfip, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQFileInfo *info = (p && p->getType() == NT_OBJECT) ? (QoreQFileInfo *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QFILEINFO, xsink) : 0;
   if (!info) {
      if (!xsink->isException())
         xsink->raiseException("QFILEICONPROVIDER-TYPE-PARAM-ERROR", "expecting a QFileInfo object as first argument to QFileIconProvider::type()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> infoHolder(static_cast<AbstractPrivateData *>(info), xsink);
   return new QoreStringNode(qfip->getQFileIconProvider()->type(*(static_cast<QFileInfo *>(info))).toUtf8().data(), QCS_UTF8);
}

static QoreClass *initQFileIconProviderClass() {
   QC_QFileIconProvider = new QoreClass("QFileIconProvider", QDOM_GUI);
   CID_QFILEICONPROVIDER = QC_QFileIconProvider->getID();

   QC_QFileIconProvider->setConstructor(QFILEICONPROVIDER_constructor);
   QC_QFileIconProvider->setCopy((q_copy_t)QFILEICONPROVIDER_copy);

   QC_QFileIconProvider->addMethod("icon",                        (q_method_t)QFILEICONPROVIDER_icon);
   QC_QFileIconProvider->addMethod("type",                        (q_method_t)QFILEICONPROVIDER_type);

   return QC_QFileIconProvider;
}

QoreNamespace *initQFileIconProviderNS() {
   QoreNamespace *ns = new QoreNamespace("QFileIconProvider");
   ns->addSystemClass(initQFileIconProviderClass());

   ns->addConstant("Computer",                 new QoreBigIntNode(QFileIconProvider::Computer));
   ns->addConstant("Desktop",                  new QoreBigIntNode(QFileIconProvider::Desktop));
   ns->addConstant("Trashcan",                 new QoreBigIntNode(QFileIconProvider::Trashcan));
   ns->addConstant("Network",                  new QoreBigIntNode(QFileIconProvider::Network));
   ns->addConstant("Drive",                    new QoreBigIntNode(QFileIconProvider::Drive));
   ns->addConstant("Folder",                   new QoreBigIntNode(QFileIconProvider::Folder));
   ns->addConstant("File",                     new QoreBigIntNode(QFileIconProvider::File));

   return ns;
}
