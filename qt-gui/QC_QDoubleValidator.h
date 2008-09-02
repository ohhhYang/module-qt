/*
 QC_QDoubleValidator.h
 
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

#ifndef _QORE_QT_QC_QDOUBLEVALIDATOR_H

#define _QORE_QT_QC_QDOUBLEVALIDATOR_H

#include <QDoubleValidator>
#include "QoreAbstractQValidator.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QDOUBLEVALIDATOR;
DLLEXPORT extern class QoreClass *QC_QDoubleValidator;

DLLEXPORT class QoreClass *initQDoubleValidatorClass(QoreClass *);

class myQDoubleValidator : public QDoubleValidator, public QoreQValidatorExtension
{
  private:
      const QoreMethod *m_setRange;

      void qdv_init(const QoreClass *qc)
      {
	 m_setRange = findMethod(qc, "setRange");
      }

#define QOREQTYPE QDoubleValidator
#define MYQOREQTYPE myQDoubleValidator
#include "qore-qt-metacode.h"
#include "qore-qt-qvalidator-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQDoubleValidator(QoreObject *obj, QObject* parent) : QDoubleValidator(parent), QoreQValidatorExtension(obj, this)
      {
         
	 qdv_init(obj->getClass());
      }
      DLLLOCAL myQDoubleValidator(QoreObject *obj, double bottom, double top, int decimals, QObject* parent) : QDoubleValidator(bottom, top, decimals, parent), QoreQValidatorExtension(obj, this)
      {
         
	 qdv_init(obj->getClass());
      }

      DLLLOCAL void parent_setRange(double minimum, double maximum, int decimals = 0)
      {
	 QDoubleValidator::setRange(minimum, maximum, decimals);
      }

      DLLLOCAL virtual void setRange(double minimum, double maximum, int decimals = 0)
      {
	 if (!m_setRange) {
	    QDoubleValidator::setRange(minimum, maximum, decimals);
	    return;
	 }
	 QoreListNode *args = new QoreListNode();
	 args->push(new QoreFloatNode(minimum));
	 args->push(new QoreFloatNode(maximum));
	 args->push(new QoreBigIntNode(decimals));

	 ExceptionSink xsink;
	 discard(dispatch_event_intern(qore_obj, m_setRange, args, &xsink), &xsink);
      }
};

typedef QoreQValidatorBase<myQDoubleValidator, QoreAbstractQValidator> QoreQDoubleValidatorImpl;

class QoreQDoubleValidator : public QoreQDoubleValidatorImpl
{
   public:
      DLLLOCAL QoreQDoubleValidator(QoreObject *obj, QObject* parent) : QoreQDoubleValidatorImpl(new myQDoubleValidator(obj, parent))
      {
      }
      DLLLOCAL QoreQDoubleValidator(QoreObject *obj, double bottom, double top, int decimals, QObject* parent) : QoreQDoubleValidatorImpl(new myQDoubleValidator(obj, bottom, top, decimals, parent))
      {
      }
      DLLLOCAL void setRange(double minimum, double maximum, int decimals = 0)
      {
	 qobj->parent_setRange(minimum, maximum, decimals);
      }
};

#endif // _QORE_QT_QC_QDOUBLEVALIDATOR_H
