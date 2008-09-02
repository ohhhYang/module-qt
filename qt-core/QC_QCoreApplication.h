/*
 QC_QCoreApplication.h
 
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

#ifndef _QORE_QT_QC_QCOREAPPLICATION_H

#define _QORE_QT_QC_QCOREAPPLICATION_H

#include <QCoreApplication>
#include "QoreAbstractQCoreApplication.h"

DLLEXPORT extern qore_classid_t CID_QCOREAPPLICATION;
DLLEXPORT extern QoreClass *QC_QCoreApplication;

DLLEXPORT QoreClass *initQCoreApplicationClass(QoreClass *);

class myQCoreApplication : public QCoreApplication, public QoreQObjectExtension
{
#define QOREQTYPE QCoreApplication
#define MYQOREQTYPE myQCoreApplication
#include "qore-qt-metacode.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQCoreApplication(QoreObject *obj, int& argc, char ** argv) : QCoreApplication(argc, argv), QoreQObjectExtension(obj, this)
      {
      }
};

class myQCoreApplicationWithArgs : public myQCoreApplication
{
   private:
      QoreQtArgs *qt_args;

   public:
      DLLLOCAL myQCoreApplicationWithArgs(QoreObject *obj, int& argc, char ** argv) : myQCoreApplication(obj, argc, argv), qt_args(0)
      {
      }

      DLLLOCAL myQCoreApplicationWithArgs(QoreObject *obj, QoreQtArgs *n_qt_args) : myQCoreApplication(obj, n_qt_args->get_argc(), n_qt_args->get_argv()), qt_args(n_qt_args)
      {
      }

      DLLLOCAL ~myQCoreApplicationWithArgs()
      {
	 delete qt_args;
      }
};

typedef QoreQCoreApplicationBase<myQCoreApplicationWithArgs, QoreAbstractQCoreApplication> QoreQCoreApplicationImpl;

class QoreQCoreApplication : public QoreQCoreApplicationImpl
{
   public:
      DLLLOCAL QoreQCoreApplication(QoreObject *obj, int& argc, char ** argv) : QoreQCoreApplicationImpl(new myQCoreApplicationWithArgs(obj, argc, argv))
      {
      }
      DLLLOCAL QoreQCoreApplication(QoreObject *obj, QoreQtArgs *qt_args) : QoreQCoreApplicationImpl(new myQCoreApplicationWithArgs(obj, qt_args))
      {
      }
};

typedef QoreQtQCoreApplicationBase<QCoreApplication, QoreAbstractQCoreApplication> QoreQtQCoreApplicationImpl;

class QoreQtQCoreApplication : public QoreQtQCoreApplicationImpl
{
  public:
   DLLLOCAL QoreQtQCoreApplication(QoreObject *obj, QCoreApplication *qcoreapplication) : QoreQtQCoreApplicationImpl(obj, qcoreapplication)
   {
   }
};

#endif // _QORE_QT_QC_QCOREAPPLICATION_H
