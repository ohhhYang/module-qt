/*
 QC_QSettings.h
 
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

#ifndef _QORE_QT_QC_QSETTINGS_H

#define _QORE_QT_QC_QSETTINGS_H

#include <QSettings>
#include "QoreAbstractQObject.h"

DLLEXPORT extern qore_classid_t CID_QSETTINGS;
DLLEXPORT extern QoreClass *QC_QSettings;
DLLEXPORT QoreNamespace *initQSettingsNS(QoreClass *);

class myQSettings : public QSettings, public QoreQObjectExtension {
#define QOREQTYPE QSettings
#define MYQOREQTYPE myQSettings
#include "qore-qt-metacode.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQSettings(QoreObject *obj, const QString& organization, const QString& application = QString(), QObject* parent = 0) : QSettings(organization, application, parent), QoreQObjectExtension(obj, this) {
      }
      DLLLOCAL myQSettings(QoreObject *obj, QSettings::Scope scope, const QString& organization, const QString& application = QString(), QObject* parent = 0) : QSettings(scope, organization, application, parent), QoreQObjectExtension(obj, this) {
      }
      DLLLOCAL myQSettings(QoreObject *obj, QSettings::Format format, QSettings::Scope scope, const QString& organization, const QString& application = QString(), QObject* parent = 0) : QSettings(format, scope, organization, application, parent), QoreQObjectExtension(obj, this) {
      }
      DLLLOCAL myQSettings(QoreObject *obj, const QString& fileName,QSettings:: Format format, QObject* parent = 0) : QSettings(fileName, format, parent), QoreQObjectExtension(obj, this) {
      }
      DLLLOCAL myQSettings(QoreObject *obj, QObject* parent = 0) : QSettings(parent), QoreQObjectExtension(obj, this) {
      }
};

typedef QoreQObjectBase<myQSettings, QoreAbstractQObject> QoreQSettingsImpl;

class QoreQSettings : public QoreQSettingsImpl {
   public:
      DLLLOCAL QoreQSettings(QoreObject *obj, const QString& organization, const QString& application = QString(), QObject* parent = 0) : QoreQSettingsImpl(new myQSettings(obj, organization, application, parent)) { }
      DLLLOCAL QoreQSettings(QoreObject *obj, QSettings::Scope scope, const QString& organization, const QString& application = QString(), QObject* parent = 0) : QoreQSettingsImpl(new myQSettings(obj, scope, organization, application, parent)) { }
      DLLLOCAL QoreQSettings(QoreObject *obj, QSettings::Format format, QSettings::Scope scope, const QString& organization, const QString& application = QString(), QObject* parent = 0) : QoreQSettingsImpl(new myQSettings(obj, format, scope, organization, application, parent)) { }
      DLLLOCAL QoreQSettings(QoreObject *obj, const QString& fileName, QSettings::Format format, QObject* parent = 0) : QoreQSettingsImpl(new myQSettings(obj, fileName, format, parent)) { }
      DLLLOCAL QoreQSettings(QoreObject *obj, QObject* parent = 0) : QoreQSettingsImpl(new myQSettings(obj, parent)) { }
};

typedef QoreQtQObjectBase<QSettings, QoreAbstractQObject> QoreQtQSettingsImpl;

class QoreQtQSettings : public QoreQtQSettingsImpl {
   public:
      DLLLOCAL QoreQtQSettings(QoreObject *obj, QSettings *qsettings) : QoreQtQSettingsImpl(obj, qsettings) { }
};

#endif // _QORE_QT_QC_QSETTINGS_H
