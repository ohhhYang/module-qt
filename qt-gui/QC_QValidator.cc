/*
 QC_QValidator.cc
 
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

#include "QC_QValidator.h"
#include "QC_QObject.h"
#include "QC_QLocale.h"

#include "qore-qt-gui.h"

qore_classid_t CID_QVALIDATOR;
class QoreClass *QC_QValidator = 0;

//QValidator ( QObject * parent )
static void QVALIDATOR_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreAbstractQObject *parent = p ? (QoreAbstractQObject *)p->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QVALIDATOR-CONSTRUCTOR-PARAM-ERROR", "expecting a QObject object as first argument to QValidator::constructor()");
      return;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QVALIDATOR, new QoreQValidator(self, parent->getQObject()));
   return;
}

static void QVALIDATOR_copy(class QoreObject *self, class QoreObject *old, class QoreQValidator *qv, ExceptionSink *xsink)
{
   xsink->raiseException("QVALIDATOR-COPY-ERROR", "objects of this class cannot be copied");
}

//virtual void fixup ( QString & input ) const
static AbstractQoreNode *QVALIDATOR_fixup(QoreObject *self, QoreAbstractQValidator *qv, const QoreListNode *params, ExceptionSink *xsink)
{
   const ReferenceNode *p = test_reference_param(params, 0);
   if (!p) {
      xsink->raiseException("QVALIDATOR-FIXUP-ERROR", "expecting a reference as sole argument to QValidator::fixup()");
      return 0;
   }

   AutoVLock vl(xsink);
   ReferenceHelper ref(p, vl, xsink);
   if (!ref)
      return 0;

   QString input;
   if (get_qstring(ref.getValue(), input, xsink))
      return 0;
   qv->fixup(input);

   ref.assign(new QoreStringNode(input.toUtf8().data(), QCS_UTF8), xsink);

   return 0;
}

//QLocale locale () const
static AbstractQoreNode *QVALIDATOR_locale(QoreObject *self, QoreAbstractQValidator *qv, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_ql = new QoreObject(QC_QLocale, getProgram());
   QoreQLocale *q_ql = new QoreQLocale(qv->getQValidator()->locale());
   o_ql->setPrivate(CID_QLOCALE, q_ql);
   return o_ql;
}

//void setLocale ( const QLocale & locale )
static AbstractQoreNode *QVALIDATOR_setLocale(QoreObject *self, QoreAbstractQValidator *qv, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQLocale *locale = p ? (QoreQLocale *)p->getReferencedPrivateData(CID_QLOCALE, xsink) : 0;
   if (!locale) {
      if (!xsink->isException())
         xsink->raiseException("QVALIDATOR-SETLOCALE-PARAM-ERROR", "expecting a QLocale object as first argument to QValidator::setLocale()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> localeHolder(static_cast<AbstractPrivateData *>(locale), xsink);
   qv->getQValidator()->setLocale(*(static_cast<QLocale *>(locale)));
   return 0;
}

//virtual State validate ( QString & input, int & pos ) const = 0
static AbstractQoreNode *QVALIDATOR_validate(QoreObject *self, QoreAbstractQValidator *qv, const QoreListNode *params, ExceptionSink *xsink)
{
   const ReferenceNode *p0 = test_reference_param(params, 0);
   if (!p0) {
      xsink->raiseException("QVALIDATOR-VALIDATE-ERROR", "expecting a reference as first argument to QValidator::validate()");
      return 0;
   }
   
   const ReferenceNode *p1 = test_reference_param(params, 1);
   if (!p1) {
      xsink->raiseException("QVALIDATOR-VALIDATE-ERROR", "expecting a reference as second argument to QValidator::validate()");
      return 0;
   }

   AutoVLock vl(xsink);
   ReferenceHelper ref0(p0, vl, xsink);
   if (!ref0)
      return 0;

   ReferenceHelper ref1(p1, vl, xsink);
   if (!ref1)
      return 0;
      
   QString input;
   if (get_qstring(ref0.getValue(), input, xsink))
      return 0;
   
   const AbstractQoreNode *v1 = ref1.getValue();
   int pos = v1 ? v1->getAsInt() : 0;

   QValidator::State rc = qv->validate(input, pos);

   if (ref0.assign(new QoreStringNode(input.toUtf8().data(), QCS_UTF8), xsink))
      return 0;

   ref1.assign(new QoreBigIntNode(pos), xsink);

   return new QoreBigIntNode(rc);
}


QoreClass *initQValidatorClass(QoreClass *qobject)
{
   QC_QValidator = new QoreClass("QValidator", QDOM_GUI);
   CID_QVALIDATOR = QC_QValidator->getID();

   QC_QValidator->addBuiltinVirtualBaseClass(qobject);

   QC_QValidator->setConstructor(QVALIDATOR_constructor);
   QC_QValidator->setCopy((q_copy_t)QVALIDATOR_copy);

   QC_QValidator->addMethod("fixup",                       (q_method_t)QVALIDATOR_fixup);
   QC_QValidator->addMethod("locale",                      (q_method_t)QVALIDATOR_locale);
   QC_QValidator->addMethod("setLocale",                   (q_method_t)QVALIDATOR_setLocale);
   QC_QValidator->addMethod("validate",                    (q_method_t)QVALIDATOR_validate);

   return QC_QValidator;
}
