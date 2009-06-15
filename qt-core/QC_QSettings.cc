/*
 QC_QSettings.cc
 
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

#include "qt-core.h"

#include "QC_QSettings.h"

qore_classid_t CID_QSETTINGS;
QoreClass *QC_QSettings = 0;

//QSettings ( const QString & organization, const QString & application = QString(), QObject * parent = 0 )
//QSettings ( Scope scope, const QString & organization, const QString & application = QString(), QObject * parent = 0 )
//QSettings ( Format format, Scope scope, const QString & organization, const QString & application = QString(), QObject * parent = 0 )
//QSettings ( const QString & fileName, Format format, QObject * parent = 0 )
//QSettings ( QObject * parent = 0 )
static void QSETTINGS_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QSETTINGS, new QoreQSettings(self));
      return;
   }
   if (p && p->getType() == NT_OBJECT) {
      QoreAbstractQObject *parent = (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink);
      if (*xsink)
         return;
      ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
      self->setPrivate(CID_QSETTINGS, new QoreQSettings(self, parent ? parent->getQObject() : 0));
      return;
   }

   if (p && p->getType() == NT_STRING) {
      QString organization;
      if (get_qstring(p, organization, xsink))
         return;
      p = get_param(params, 1);
      if (p && p->getType() == NT_STRING) {
         QString application;
         if (get_qstring(p, application, xsink, true))
            application = QString();
         p = get_param(params, 2);
         QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
         if (*xsink)
            return;
         ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
         self->setPrivate(CID_QSETTINGS, new QoreQSettings(self, organization, application, parent ? parent->getQObject() : 0));
         return;
      }
      QSettings::Format format = (QSettings::Format)(p ? p->getAsInt() : 0);
      p = get_param(params, 2);
      QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
      if (*xsink)
         return;
      ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
      self->setPrivate(CID_QSETTINGS, new QoreQSettings(self, organization, format, parent ? parent->getQObject() : 0));
      return;
   }

   int offset = 0;
   int i0 = p ? p->getAsInt() : 0;
   
   QSettings::Format format;
   QSettings::Scope scope;
   
   p = get_param(params, 1);
   if (p && p->getType() == NT_STRING) {
      scope = (QSettings::Scope)i0;
   }
   else {
      offset = 1;
      format = (QSettings::Format)i0;
      scope = (QSettings::Scope)(p ? p->getAsInt() : 0);
      p = get_param(params, 2);
   }

   QString organization;
   if (get_qstring(p, organization, xsink))
      return;

   p = get_param(params, 2 + offset);
   QString application;
   if (get_qstring(p, application, xsink, true))
      application = QString();

   p = get_param(params, 3 + offset);
   QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);

   QoreQSettings *qs;
   if (offset)
      qs = new QoreQSettings(self, format, scope, organization, application, parent ? parent->getQObject() : 0);
   else
      qs = new QoreQSettings(self, scope, organization, application, parent ? parent->getQObject() : 0);

   self->setPrivate(CID_QSETTINGS, qs);
}

static void QSETTINGS_copy(QoreObject *self, QoreObject *old, QoreQSettings *qs, ExceptionSink *xsink) {
   xsink->raiseException("QSETTINGS-COPY-ERROR", "objects of this class cannot be copied");
}

//QStringList allKeys () const
static AbstractQoreNode *QSETTINGS_allKeys(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qstringlist(qs->qobj->allKeys());
}

//QString applicationName () const
static AbstractQoreNode *QSETTINGS_applicationName(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreStringNode(qs->qobj->applicationName().toUtf8().data(), QCS_UTF8);
}

//void beginGroup ( const QString & prefix )
static AbstractQoreNode *QSETTINGS_beginGroup(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString prefix;
   if (get_qstring(p, prefix, xsink))
      return 0;
   qs->qobj->beginGroup(prefix);
   return 0;
}

//int beginReadArray ( const QString & prefix )
static AbstractQoreNode *QSETTINGS_beginReadArray(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString prefix;
   if (get_qstring(p, prefix, xsink))
      return 0;
   return new QoreBigIntNode(qs->qobj->beginReadArray(prefix));
}

//void beginWriteArray ( const QString & prefix, int size = -1 )
static AbstractQoreNode *QSETTINGS_beginWriteArray(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString prefix;
   if (get_qstring(p, prefix, xsink))
      return 0;
   p = get_param(params, 1);
   int size = !is_nothing(p) ? p->getAsInt() : -1;
   qs->qobj->beginWriteArray(prefix, size);
   return 0;
}

//QStringList childGroups () const
static AbstractQoreNode *QSETTINGS_childGroups(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qstringlist(qs->qobj->childGroups());
}

//QStringList childKeys () const
static AbstractQoreNode *QSETTINGS_childKeys(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qstringlist(qs->qobj->childKeys());
}

//void clear ()
static AbstractQoreNode *QSETTINGS_clear(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   qs->qobj->clear();
   return 0;
}

//bool contains ( const QString & key ) const
static AbstractQoreNode *QSETTINGS_contains(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString key;
   if (get_qstring(p, key, xsink))
      return 0;
   return get_bool_node(qs->qobj->contains(key));
}

//void endArray ()
static AbstractQoreNode *QSETTINGS_endArray(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   qs->qobj->endArray();
   return 0;
}

//void endGroup ()
static AbstractQoreNode *QSETTINGS_endGroup(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   qs->qobj->endGroup();
   return 0;
}

//bool fallbacksEnabled () const
static AbstractQoreNode *QSETTINGS_fallbacksEnabled(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qs->qobj->fallbacksEnabled());
}

//QString fileName () const
static AbstractQoreNode *QSETTINGS_fileName(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreStringNode(qs->qobj->fileName().toUtf8().data(), QCS_UTF8);
}

//Format format () const
static AbstractQoreNode *QSETTINGS_format(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qs->qobj->format());
}

//QString group () const
static AbstractQoreNode *QSETTINGS_group(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreStringNode(qs->qobj->group().toUtf8().data(), QCS_UTF8);
}

/*
//QTextCodec * iniCodec () const
static AbstractQoreNode *QSETTINGS_iniCodec(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   ??? return new QoreBigIntNode(qs->qobj->iniCodec());
}
*/

//bool isWritable () const
static AbstractQoreNode *QSETTINGS_isWritable(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qs->qobj->isWritable());
}

//QString organizationName () const
static AbstractQoreNode *QSETTINGS_organizationName(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreStringNode(qs->qobj->organizationName().toUtf8().data(), QCS_UTF8);
}

//void remove ( const QString & key )
static AbstractQoreNode *QSETTINGS_remove(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString key;
   if (get_qstring(p, key, xsink))
      return 0;
   qs->qobj->remove(key);
   return 0;
}

//Scope scope () const
static AbstractQoreNode *QSETTINGS_scope(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qs->qobj->scope());
}

//void setArrayIndex ( int i )
static AbstractQoreNode *QSETTINGS_setArrayIndex(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int i = p ? p->getAsInt() : 0;
   qs->qobj->setArrayIndex(i);
   return 0;
}

//void setFallbacksEnabled ( bool b )
static AbstractQoreNode *QSETTINGS_setFallbacksEnabled(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool b = p ? p->getAsBool() : false;
   qs->qobj->setFallbacksEnabled(b);
   return 0;
}

/*
//void setIniCodec ( QTextCodec * codec )
//void setIniCodec ( const char * codecName )
static AbstractQoreNode *QSETTINGS_setIniCodec(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QTextCodec* codec = p;
   qs->qobj->setIniCodec(codec);
   return 0;
}
*/

//void setValue ( const QString & key, const QVariant & value )
static AbstractQoreNode *QSETTINGS_setValue(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString key;
   if (get_qstring(p, key, xsink))
      return 0;
   p = get_param(params, 1);
   QVariant value;
   if (get_qvariant(p, value, xsink))
      return 0;
   qs->qobj->setValue(key, value);
   return 0;
}

//Status status () const
static AbstractQoreNode *QSETTINGS_status(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qs->qobj->status());
}

//void sync ()
static AbstractQoreNode *QSETTINGS_sync(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   qs->qobj->sync();
   return 0;
}

//QVariant value ( const QString & key, const QVariant & defaultValue = QVariant() ) const
static AbstractQoreNode *QSETTINGS_value(QoreObject *self, QoreQSettings *qs, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString key;
   if (get_qstring(p, key, xsink))
      return 0;
   p = get_param(params, 1);
   QVariant defaultValue;
   if (get_qvariant(p, defaultValue, xsink, true))
      defaultValue = QVariant();
   return return_qvariant(qs->qobj->value(key, defaultValue));
}

//Format defaultFormat ()
static AbstractQoreNode *f_QSettings_defaultFormat(const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(QSettings::defaultFormat());
}

/*
//Format registerFormat ( const QString & extension, ReadFunc readFunc, WriteFunc writeFunc, Qt::CaseSensitivity caseSensitivity = Qt::CaseSensitive )
static AbstractQoreNode *f_QSettings_registerFormat(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString extension;
   if (get_qstring(p, extension, xsink))
      return 0;
   p = get_param(params, 1);
   QSettings::ReadFunc readFunc = (QSettings::ReadFunc)(p ? p->getAsInt() : 0);
   p = get_param(params, 2);
   QSettings::WriteFunc writeFunc = (QSettings::WriteFunc)(p ? p->getAsInt() : 0);
   p = get_param(params, 3);
   Qt::CaseSensitivity caseSensitivity = !is_nothing(p) ? (Qt::CaseSensitivity)p->getAsInt() : Qt::CaseSensitive;
   ??? return new QoreBigIntNode(QSettings::registerFormat(extension, readFunc, writeFunc, caseSensitivity));
}
*/

//void setDefaultFormat ( Format format )
static AbstractQoreNode *f_QSettings_setDefaultFormat(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QSettings::Format format = (QSettings::Format)(p ? p->getAsInt() : 0);
   QSettings::setDefaultFormat(format);
   return 0;
}

//void setPath ( Format format, Scope scope, const QString & path )
static AbstractQoreNode *f_QSettings_setPath(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QSettings::Format format = (QSettings::Format)(p ? p->getAsInt() : 0);
   p = get_param(params, 1);
   QSettings::Scope scope = (QSettings::Scope)(p ? p->getAsInt() : 0);
   p = get_param(params, 2);
   QString path;
   if (get_qstring(p, path, xsink))
      return 0;
   QSettings::setPath(format, scope, path);
   return 0;
}

static QoreClass *initQSettingsClass(QoreClass *qobject) {
   QC_QSettings = new QoreClass("QSettings", QDOM_GUI);
   CID_QSETTINGS = QC_QSettings->getID();

   QC_QSettings->addBuiltinVirtualBaseClass(qobject);

   QC_QSettings->setConstructor(QSETTINGS_constructor);
   QC_QSettings->setCopy((q_copy_t)QSETTINGS_copy);

   QC_QSettings->addMethod("allKeys",                     (q_method_t)QSETTINGS_allKeys);
   QC_QSettings->addMethod("applicationName",             (q_method_t)QSETTINGS_applicationName);
   QC_QSettings->addMethod("beginGroup",                  (q_method_t)QSETTINGS_beginGroup);
   QC_QSettings->addMethod("beginReadArray",              (q_method_t)QSETTINGS_beginReadArray);
   QC_QSettings->addMethod("beginWriteArray",             (q_method_t)QSETTINGS_beginWriteArray);
   QC_QSettings->addMethod("childGroups",                 (q_method_t)QSETTINGS_childGroups);
   QC_QSettings->addMethod("childKeys",                   (q_method_t)QSETTINGS_childKeys);
   QC_QSettings->addMethod("clear",                       (q_method_t)QSETTINGS_clear);
   QC_QSettings->addMethod("contains",                    (q_method_t)QSETTINGS_contains);
   QC_QSettings->addMethod("endArray",                    (q_method_t)QSETTINGS_endArray);
   QC_QSettings->addMethod("endGroup",                    (q_method_t)QSETTINGS_endGroup);
   QC_QSettings->addMethod("fallbacksEnabled",            (q_method_t)QSETTINGS_fallbacksEnabled);
   QC_QSettings->addMethod("fileName",                    (q_method_t)QSETTINGS_fileName);
   QC_QSettings->addMethod("format",                      (q_method_t)QSETTINGS_format);
   QC_QSettings->addMethod("group",                       (q_method_t)QSETTINGS_group);
   //QC_QSettings->addMethod("iniCodec",                    (q_method_t)QSETTINGS_iniCodec);
   QC_QSettings->addMethod("isWritable",                  (q_method_t)QSETTINGS_isWritable);
   QC_QSettings->addMethod("organizationName",            (q_method_t)QSETTINGS_organizationName);
   QC_QSettings->addMethod("remove",                      (q_method_t)QSETTINGS_remove);
   QC_QSettings->addMethod("scope",                       (q_method_t)QSETTINGS_scope);
   QC_QSettings->addMethod("setArrayIndex",               (q_method_t)QSETTINGS_setArrayIndex);
   QC_QSettings->addMethod("setFallbacksEnabled",         (q_method_t)QSETTINGS_setFallbacksEnabled);
   //QC_QSettings->addMethod("setIniCodec",                 (q_method_t)QSETTINGS_setIniCodec);
   QC_QSettings->addMethod("setValue",                    (q_method_t)QSETTINGS_setValue);
   QC_QSettings->addMethod("status",                      (q_method_t)QSETTINGS_status);
   QC_QSettings->addMethod("sync",                        (q_method_t)QSETTINGS_sync);
   QC_QSettings->addMethod("value",                       (q_method_t)QSETTINGS_value);

   // static methods
   QC_QSettings->addStaticMethod("defaultFormat",               f_QSettings_defaultFormat);
   //QC_QSettings->addStaticMethod("registerFormat",              f_QSettings_registerFormat);
   QC_QSettings->addStaticMethod("setDefaultFormat",            f_QSettings_setDefaultFormat);
   QC_QSettings->addStaticMethod("setPath",                     f_QSettings_setPath);

   return QC_QSettings;
}

QoreNamespace *initQSettingsNS(QoreClass *qobject) {
   QoreNamespace *ns = new QoreNamespace("QSettings");
   ns->addSystemClass(initQSettingsClass(QC_QObject));

   // Status enum
   ns->addConstant("NoError",                  new QoreBigIntNode(QSettings::NoError));
   ns->addConstant("AccessError",              new QoreBigIntNode(QSettings::AccessError));
   ns->addConstant("FormatError",              new QoreBigIntNode(QSettings::FormatError));

   // Format enum
   ns->addConstant("NativeFormat",             new QoreBigIntNode(QSettings::NativeFormat));
   ns->addConstant("IniFormat",                new QoreBigIntNode(QSettings::IniFormat));
   ns->addConstant("InvalidFormat",            new QoreBigIntNode(QSettings::InvalidFormat));
   ns->addConstant("CustomFormat1",            new QoreBigIntNode(QSettings::CustomFormat1));
   ns->addConstant("CustomFormat2",            new QoreBigIntNode(QSettings::CustomFormat2));
   ns->addConstant("CustomFormat3",            new QoreBigIntNode(QSettings::CustomFormat3));
   ns->addConstant("CustomFormat4",            new QoreBigIntNode(QSettings::CustomFormat4));
   ns->addConstant("CustomFormat5",            new QoreBigIntNode(QSettings::CustomFormat5));
   ns->addConstant("CustomFormat6",            new QoreBigIntNode(QSettings::CustomFormat6));
   ns->addConstant("CustomFormat7",            new QoreBigIntNode(QSettings::CustomFormat7));
   ns->addConstant("CustomFormat8",            new QoreBigIntNode(QSettings::CustomFormat8));
   ns->addConstant("CustomFormat9",            new QoreBigIntNode(QSettings::CustomFormat9));
   ns->addConstant("CustomFormat10",           new QoreBigIntNode(QSettings::CustomFormat10));
   ns->addConstant("CustomFormat11",           new QoreBigIntNode(QSettings::CustomFormat11));
   ns->addConstant("CustomFormat12",           new QoreBigIntNode(QSettings::CustomFormat12));
   ns->addConstant("CustomFormat13",           new QoreBigIntNode(QSettings::CustomFormat13));
   ns->addConstant("CustomFormat14",           new QoreBigIntNode(QSettings::CustomFormat14));
   ns->addConstant("CustomFormat15",           new QoreBigIntNode(QSettings::CustomFormat15));
   ns->addConstant("CustomFormat16",           new QoreBigIntNode(QSettings::CustomFormat16));

   // Scope enum
   ns->addConstant("UserScope",                new QoreBigIntNode(QSettings::UserScope));
   ns->addConstant("SystemScope",              new QoreBigIntNode(QSettings::SystemScope));

   return ns;
}
