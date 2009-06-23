/*
 QC_QStringListModel.cc
 
 Qore Programming Language

 Copyright (C) 2003 - 2009 Qore Technologies

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

#include "QC_QStringListModel.h"

qore_classid_t CID_QSTRINGLISTMODEL;
QoreClass *QC_QStringListModel = 0;

//QStringListModel ( QObject * parent = 0 )
//QStringListModel ( const QStringList & strings, QObject * parent = 0 )
static void QSTRINGLISTMODEL_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QSTRINGLISTMODEL, new QoreQStringListModel(self));
      return;
   }
   if (p && p->getType() == NT_OBJECT) {
      QoreAbstractQObject *parent = (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink);
      if (*xsink)
         return;
      ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
      self->setPrivate(CID_QSTRINGLISTMODEL, new QoreQStringListModel(self, parent ? parent->getQObject() : 0));
      return;
   }
   if (p->getType() != NT_LIST) {
      xsink->raiseException("QSTRINGLISTMODEL-CONSTRUCTOR-ERROR", "expecting a list of strings passed to QStringListModel::constructor(), instead got type: '%s'", p->getTypeName());
      return;
   }
   QStringList strings;
   ConstListIterator li_strings(reinterpret_cast<const QoreListNode *>(p));
   while (li_strings.next()) {
      QoreStringNodeValueHelper str(li_strings.getValue());
      QString tmp;
      if (get_qstring(*str, tmp, xsink))
         return;
      strings.push_back(tmp);
   }
   p = get_param(params, 1);
   QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QSTRINGLISTMODEL, new QoreQStringListModel(self, strings, parent ? parent->getQObject() : 0));
   return;
}

static void QSTRINGLISTMODEL_copy(QoreObject *self, QoreObject *old, QoreQStringListModel *qslm, ExceptionSink *xsink) {
   xsink->raiseException("QSTRINGLISTMODEL-COPY-ERROR", "objects of this class cannot be copied");
}

//void setStringList ( const QStringList & strings )
static AbstractQoreNode *QSTRINGLISTMODEL_setStringList(QoreObject *self, QoreAbstractQStringListModel *qslm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (!p || p->getType() != NT_LIST) {
      xsink->raiseException("QSTRINGLISTMODEL-SETSTRINGLIST-ERROR", "expecting a list of strings as the sole argument to QStringList::setStringList()");
      return 0;
   }
   QStringList strings;
   ConstListIterator li_strings(reinterpret_cast<const QoreListNode *>(p));
   while (li_strings.next()) {
      QoreStringNodeValueHelper str(li_strings.getValue());
      QString tmp;
      if (get_qstring(*str, tmp, xsink))
         return 0;
      strings.push_back(tmp);
   }
   qslm->getQStringListModel()->setStringList(strings);
   return 0;
}

//QStringList stringList () const
static AbstractQoreNode *QSTRINGLISTMODEL_stringList(QoreObject *self, QoreAbstractQStringListModel *qslm, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qstringlist(qslm->getQStringListModel()->stringList());
}

QoreClass *initQStringListModelClass(QoreClass *qabstractlistmodel) {
   QC_QStringListModel = new QoreClass("QStringListModel", QDOM_GUI);
   CID_QSTRINGLISTMODEL = QC_QStringListModel->getID();

   QC_QStringListModel->addBuiltinVirtualBaseClass(qabstractlistmodel);

   QC_QStringListModel->setConstructor(QSTRINGLISTMODEL_constructor);
   QC_QStringListModel->setCopy((q_copy_t)QSTRINGLISTMODEL_copy);

   QC_QStringListModel->addMethod("setStringList",               (q_method_t)QSTRINGLISTMODEL_setStringList);
   QC_QStringListModel->addMethod("stringList",                  (q_method_t)QSTRINGLISTMODEL_stringList);

   return QC_QStringListModel;
}
