/*
 qt-core.h
 
 Qore Programming Language
 
 Copyright 2003 - 2009 David Nichols
 
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

#ifndef _QORE_QT_CORE_H
#define _QORE_QT_CORE_H

#include "../config.h"
#include <qore/Qore.h>

#include <QDate>
#include <QDateTime>
#include <QObject>
#include <QList>
#include <QStringList>
#include <QModelIndex>
#include <QItemSelection>

#include <map>

typedef std::map<int, const char *> qt_enum_map_t;

#include "BrushStyleNode.h"
#include "PenStyleNode.h"

DLLEXPORT extern QoreNamespace *QtNS, *QEventNS;

DLLEXPORT int get_qdate(const AbstractQoreNode *n, QDate &date, ExceptionSink *xsink);
DLLEXPORT int get_qtime(const AbstractQoreNode *n, QTime &time, ExceptionSink *xsink);
DLLEXPORT int get_qdatetime(const AbstractQoreNode *n, QDateTime &dt, ExceptionSink *xsink);
DLLEXPORT int get_qvariant(const AbstractQoreNode *n, QVariant &qv, ExceptionSink *xsink, bool suppress_exception = false);
DLLEXPORT int get_qbytearray(const AbstractQoreNode *n, QByteArray &qba, ExceptionSink *xsink, bool suppress_exception = false);
DLLEXPORT int get_qchar(const AbstractQoreNode *n, QChar &c, ExceptionSink *xsink, bool suppress_exception = false);
DLLEXPORT int get_qstring(const AbstractQoreNode *n, QString &str, ExceptionSink *xsink, bool suppress_exception = false);
DLLEXPORT int get_qmodelindexlist(const AbstractQoreNode *n, QModelIndexList &qmi, ExceptionSink *xsink, bool suppress_exception = false);

DLLEXPORT QString to_qstring(const AbstractQoreNode *n, ExceptionSink *xsink);
DLLEXPORT QModelIndexList to_qmodelindexlist(const AbstractQoreNode *n, ExceptionSink *xsink);
DLLEXPORT QVariant to_qvariant(const AbstractQoreNode *n, ExceptionSink *xsink);

DLLEXPORT QoreObject *return_object(const QoreClass *qclass, AbstractPrivateData *data);
DLLEXPORT QoreObject *return_qobject(QObject *o);
DLLEXPORT QoreObject *return_qevent(QEvent *event);
DLLEXPORT QoreListNode *return_qmodelindexlist(const QModelIndexList &qmil);

DLLEXPORT AbstractQoreNode *return_qvariant(const QVariant &qv);
DLLEXPORT QoreListNode *return_qstringlist(const QStringList &l);

typedef AbstractQoreNode *(*return_qvariant_hook_t)(const QVariant &qv);
typedef QoreObject *(*return_qobject_hook_t)(QObject *o);
typedef QoreObject *(*return_qevent_hook_t)(QEvent *e);

// returns true if the arugment was processed
typedef bool(*get_qvariant_hook_t)(const QoreObject *obj, QVariant &qva, ExceptionSink *xsink);

DLLEXPORT void register_return_qvariant_hook(return_qvariant_hook_t hook);
DLLEXPORT void register_return_qobject_hook(return_qobject_hook_t hook);
DLLEXPORT void register_return_qevent_hook(return_qevent_hook_t hook);

DLLEXPORT void register_get_qvariant_hook(get_qvariant_hook_t hook);

class QoreQtAbstractDynamicTypeHelper;

DLLEXPORT void register_qqt_dynamic_type(QoreQtAbstractDynamicTypeHelper *t);

class QoreQtArgs {
   private:
      int argc;
      char **argv;
      QoreListNode *new_args;

   public:
      DLLLOCAL QoreQtArgs() : argc(0), argv(0), new_args(0) {
      }

      DLLLOCAL QoreQtArgs(const QoreListNode *args) {
	 if (!args || !args->size()) {
	    argc = 0;
	    argv = 0;
	    new_args = 0;
	    return;
	 }

	 argc = args->size();
	 argv = new char*[argc];	 
	 new_args = new QoreListNode();

	 ConstListIterator li(args);
	 while (li.next()) {
	    QoreStringNodeValueHelper str(li.getValue());
	    QoreStringNode *p = str.getReferencedValue();
	    new_args->push(p);
	    argv[li.index()] = (char *)p->getBuffer();
	 }
      }

      DLLLOCAL ~QoreQtArgs() {
	 if (argv)
	    delete [] argv;
	 if (new_args) {
	    ExceptionSink xsink;
	    new_args->deref(&xsink);
	 }
      }

      int &get_argc() { return argc; }
      char **get_argv() { return argv; } 
};

DLLEXPORT const QoreMethod *findUserMethod(const QoreClass *oc, const char *name);

#endif
