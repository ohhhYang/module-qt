/*
 QC_QRegExpValidator.h
 
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

#ifndef _QORE_QT_QC_QREGEXPVALIDATOR_H

#define _QORE_QT_QC_QREGEXPVALIDATOR_H

#include <QRegExpValidator>
#include "QoreAbstractQValidator.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QREGEXPVALIDATOR;
DLLEXPORT extern class QoreClass *QC_QRegExpValidator;

DLLEXPORT class QoreClass *initQRegExpValidatorClass(QoreClass *);

class myQRegExpValidator : public QRegExpValidator, public QoreQValidatorExtension
{
#define QOREQTYPE QRegExpValidator
#define MYQOREQTYPE myQRegExpValidator
#include "qore-qt-metacode.h"
#include "qore-qt-qvalidator-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQRegExpValidator(QoreObject *obj, QObject* parent) : QRegExpValidator(parent), QoreQValidatorExtension(obj, this)
      {
         
      }
      DLLLOCAL myQRegExpValidator(QoreObject *obj, const QRegExp& rx, QObject* parent) : QRegExpValidator(rx, parent), QoreQValidatorExtension(obj, this)
      {
         
      }
};

typedef QoreQValidatorBase<myQRegExpValidator, QoreAbstractQValidator> QoreQRegExpValidatorImpl;

class QoreQRegExpValidator : public QoreQRegExpValidatorImpl
{
   public:
      DLLLOCAL QoreQRegExpValidator(QoreObject *obj, QObject* parent) : QoreQRegExpValidatorImpl(new myQRegExpValidator(obj, parent))
      {
      }
      DLLLOCAL QoreQRegExpValidator(QoreObject *obj, const QRegExp& rx, QObject* parent) : QoreQRegExpValidatorImpl(new myQRegExpValidator(obj, rx, parent))
      {
      }
};

#endif // _QORE_QT_QC_QREGEXPVALIDATOR_H
