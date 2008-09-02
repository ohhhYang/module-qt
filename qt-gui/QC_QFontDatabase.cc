/*
 QC_QFontDatabase.cc
 
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

#include "QC_QFontDatabase.h"
#include "QC_QFont.h"
#include "QC_QFontInfo.h"

#include "qore-qt-gui.h"

qore_classid_t CID_QFONTDATABASE;
class QoreClass *QC_QFontDatabase = 0;

//QFontDatabase ()
static void QFONTDATABASE_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   self->setPrivate(CID_QFONTDATABASE, new QoreQFontDatabase());
   return;
}

static void QFONTDATABASE_copy(class QoreObject *self, class QoreObject *old, class QoreQFontDatabase *qfd, ExceptionSink *xsink)
{
   xsink->raiseException("QFONTDATABASE-COPY-ERROR", "objects of this class cannot be copied");
}

//bool bold ( const QString & family, const QString & style ) const
static AbstractQoreNode *QFONTDATABASE_bold(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString family;
   if (get_qstring(p, family,  xsink))
      return 0;

   p = get_param(params, 1);
   QString style;
   if (get_qstring(p, style, xsink))
      return 0;

   return get_bool_node(qfd->bold(family, style));
}

//QStringList families ( WritingSystem writingSystem = Any ) const
static AbstractQoreNode *QFONTDATABASE_families(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QFontDatabase::WritingSystem writingSystem = (QFontDatabase::WritingSystem)(p ? p->getAsInt() : 0);
   QStringList strlist_rv = qfd->families(writingSystem);
   QoreListNode *l = new QoreListNode();
   for (QStringList::iterator i = strlist_rv.begin(), e = strlist_rv.end(); i != e; ++i)
      l->push(new QoreStringNode((*i).toUtf8().data(), QCS_UTF8));
   return l;
}

//QFont font ( const QString & family, const QString & style, int pointSize ) const
static AbstractQoreNode *QFONTDATABASE_font(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString family;
   if (get_qstring(p, family,  xsink))
      return 0;

   p = get_param(params, 1);
   QString style;
   if (get_qstring(p, style, xsink))
      return 0;

   p = get_param(params, 2);
   int pointSize = p ? p->getAsInt() : 0;
   QoreObject *o_qf = new QoreObject(QC_QFont, getProgram());
   QoreQFont *q_qf = new QoreQFont(qfd->font(family, style, pointSize));
   o_qf->setPrivate(CID_QFONT, q_qf);
   return o_qf;
}

//bool isBitmapScalable ( const QString & family, const QString & style = QString() ) const
static AbstractQoreNode *QFONTDATABASE_isBitmapScalable(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const QoreStringNode *p = test_string_param(params, 0);
   if (!p) {
      xsink->raiseException("QFONTDATABASE-ISBITMAPSCALABLE-PARAM-ERROR", "expecting a string as first argument to QFontDatabase::isBitmapScalable()");
      return 0;
   }
   const char *family = p->getBuffer();

   p = test_string_param(params, 1);
   if (p)
      return get_bool_node(qfd->isBitmapScalable(family, p->getBuffer()));

   return get_bool_node(qfd->isBitmapScalable(family));
}

//bool isFixedPitch ( const QString & family, const QString & style = QString() ) const
static AbstractQoreNode *QFONTDATABASE_isFixedPitch(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const QoreStringNode *p = test_string_param(params, 0);
   if (!p) {
      xsink->raiseException("QFONTDATABASE-ISFIXEDPITCH-PARAM-ERROR", "expecting a string as first argument to QFontDatabase::isFixedPitch()");
      return 0;
   }
   const char *family = p->getBuffer();

   p = test_string_param(params, 1);
   const char *style = p ? p->getBuffer() : 0;
   if (style)
      return get_bool_node(qfd->isFixedPitch(family, style));

   return get_bool_node(qfd->isFixedPitch(family));
}

//bool isScalable ( const QString & family, const QString & style = QString() ) const
static AbstractQoreNode *QFONTDATABASE_isScalable(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const QoreStringNode *p = test_string_param(params, 0);
   if (!p) {
      xsink->raiseException("QFONTDATABASE-ISSCALABLE-PARAM-ERROR", "expecting a string as first argument to QFontDatabase::isScalable()");
      return 0;
   }
   const char *family = p->getBuffer();
   p = test_string_param(params, 1);
   const char *style = p ? p->getBuffer() : 0;
   if (style)
      return get_bool_node(qfd->isScalable(family, style));
   return get_bool_node(qfd->isScalable(family));
}

//bool isSmoothlyScalable ( const QString & family, const QString & style = QString() ) const
static AbstractQoreNode *QFONTDATABASE_isSmoothlyScalable(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const QoreStringNode *p = test_string_param(params, 0);
   if (!p) {
      xsink->raiseException("QFONTDATABASE-ISSMOOTHLYSCALABLE-PARAM-ERROR", "expecting a string as first argument to QFontDatabase::isSmoothlyScalable()");
      return 0;
   }
   const char *family = p->getBuffer();

   p = test_string_param(params, 1);
   const char *style = p ? p->getBuffer() : 0;
   if (style)
      return get_bool_node(qfd->isSmoothlyScalable(family, style));
   return get_bool_node(qfd->isSmoothlyScalable(family));
}

//bool italic ( const QString & family, const QString & style ) const
static AbstractQoreNode *QFONTDATABASE_italic(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString family;
   if (get_qstring(p, family,  xsink))
      return 0;

   p = get_param(params, 1);
   QString style;
   if (get_qstring(p, style, xsink))
      return 0;

   return get_bool_node(qfd->italic(family, style));
}

////QList<int> pointSizes ( const QString & family, const QString & style = QString() )
static AbstractQoreNode *QFONTDATABASE_pointSizes(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString family;
   if (get_qstring(p, family,  xsink))
      return 0;

   p = get_param(params, 1);
   QString style;

   QList<int> ilist_rv;
   if (get_qstring(p, style, xsink, true)) {
      if (*xsink)
	 return 0;
      ilist_rv = qfd->pointSizes(family);
   }
   else
      ilist_rv = qfd->pointSizes(family, style);

   QoreListNode *l = new QoreListNode();
   for (QList<int>::iterator i = ilist_rv.begin(), e = ilist_rv.end(); i != e; ++i)
      l->push(new QoreBigIntNode((*i)));
   return l;
}

//QList<int> smoothSizes ( const QString & family, const QString & style )
static AbstractQoreNode *QFONTDATABASE_smoothSizes(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString family;
   if (get_qstring(p, family, xsink))
      return 0;

   p = get_param(params, 1);
   QString style;
   if (get_qstring(p, style, xsink))
      return 0;

   QList<int> ilist_rv = qfd->smoothSizes(family, style);
   QoreListNode *l = new QoreListNode();
   for (QList<int>::iterator i = ilist_rv.begin(), e = ilist_rv.end(); i != e; ++i)
      l->push(new QoreBigIntNode((*i)));
   return l;
}

//QString styleString ( const QFont & font )
//QString styleString ( const QFontInfo & fontInfo )
static AbstractQoreNode *QFONTDATABASE_styleString(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const QoreObject *p = test_object_param(params, 0);
  
   QoreQFontInfo *fontInfo = p ? (QoreQFontInfo *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QFONTINFO, xsink) : 0;
   if (!fontInfo) {
      QoreQFont *font = p ? (QoreQFont *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QFONT, xsink) : 0;
      if (!font) {
	 if (!xsink->isException())
	    xsink->raiseException("QFONTDATABASE-STYLESTRING-PARAM-ERROR", "QFontDatabase::styleString() was expecting a QFont or QFontInfo object as the first argument"); 
	 return 0;
      }
      ReferenceHolder<QoreQFont> fontHolder(font, xsink);
      return new QoreStringNode(qfd->styleString(*(static_cast<QFont *>(font))).toUtf8().data(), QCS_UTF8);
   }
   ReferenceHolder<QoreQFontInfo> fontInfoHolder(fontInfo, xsink);
   return new QoreStringNode(qfd->styleString(*(static_cast<QFontInfo *>(fontInfo))).toUtf8().data(), QCS_UTF8);
}

//QStringList styles ( const QString & family ) const
static AbstractQoreNode *QFONTDATABASE_styles(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString family;
   if (get_qstring(p, family, xsink))
      return 0;

   QStringList styles = qfd->styles(family);
   QoreListNode *l = new QoreListNode();
   for (QStringList::iterator i = styles.begin(), e = styles.end(); i != e; ++i)
      l->push(new QoreStringNode((*i).toUtf8().data(), QCS_UTF8));
   return l;
}

//int weight ( const QString & family, const QString & style ) const
static AbstractQoreNode *QFONTDATABASE_weight(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString family;
   if (get_qstring(p, family, xsink))
      return 0;

   p = get_param(params, 1);
   QString style;
   if (get_qstring(p, style, xsink))
      return 0;

   return new QoreBigIntNode(qfd->weight(family, style));
}

//QList<WritingSystem> writingSystems () const
//QList<WritingSystem> writingSystems ( const QString & family ) const
static AbstractQoreNode *QFONTDATABASE_writingSystems(QoreObject *self, QoreQFontDatabase *qfd, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);

   QList<QFontDatabase::WritingSystem> ilist_rv;

   QString family;
   if (get_qstring(p, family, xsink, true)) {
      if (*xsink)
	 return 0;
      ilist_rv = qfd->writingSystems();
   }
   else
      ilist_rv = qfd->writingSystems(family);

   QoreListNode *l = new QoreListNode();
   for (QList<QFontDatabase::WritingSystem>::iterator i = ilist_rv.begin(), e = ilist_rv.end(); i != e; ++i)
      l->push(new QoreBigIntNode((*i)));
   return l;
}

static AbstractQoreNode *f_QFontDatabase_standardSizes(const QoreListNode *params, ExceptionSink *xsink)
{
   QList<int> list = QFontDatabase::standardSizes();
   QoreListNode *l = new QoreListNode();
   for (QList<int>::iterator i = list.begin(), e = list.end(); i != e; ++i)
      l->push(new QoreBigIntNode((*i)));
   return l;
}

QoreClass *initQFontDatabaseClass()
{
   QC_QFontDatabase = new QoreClass("QFontDatabase", QDOM_GUI);
   CID_QFONTDATABASE = QC_QFontDatabase->getID();

   QC_QFontDatabase->setConstructor(QFONTDATABASE_constructor);
   QC_QFontDatabase->setCopy((q_copy_t)QFONTDATABASE_copy);

   QC_QFontDatabase->addMethod("bold",                        (q_method_t)QFONTDATABASE_bold);
   QC_QFontDatabase->addMethod("families",                    (q_method_t)QFONTDATABASE_families);
   QC_QFontDatabase->addMethod("font",                        (q_method_t)QFONTDATABASE_font);
   QC_QFontDatabase->addMethod("isBitmapScalable",            (q_method_t)QFONTDATABASE_isBitmapScalable);
   QC_QFontDatabase->addMethod("isFixedPitch",                (q_method_t)QFONTDATABASE_isFixedPitch);
   QC_QFontDatabase->addMethod("isScalable",                  (q_method_t)QFONTDATABASE_isScalable);
   QC_QFontDatabase->addMethod("isSmoothlyScalable",          (q_method_t)QFONTDATABASE_isSmoothlyScalable);
   QC_QFontDatabase->addMethod("italic",                      (q_method_t)QFONTDATABASE_italic);
   QC_QFontDatabase->addMethod("pointSizes",                  (q_method_t)QFONTDATABASE_pointSizes);
   QC_QFontDatabase->addMethod("smoothSizes",                 (q_method_t)QFONTDATABASE_smoothSizes);
   QC_QFontDatabase->addMethod("styleString",                 (q_method_t)QFONTDATABASE_styleString);
   QC_QFontDatabase->addMethod("styles",                      (q_method_t)QFONTDATABASE_styles);
   QC_QFontDatabase->addMethod("weight",                      (q_method_t)QFONTDATABASE_weight);
   QC_QFontDatabase->addMethod("writingSystems",              (q_method_t)QFONTDATABASE_writingSystems);

   // static methods
   QC_QFontDatabase->addStaticMethod("standardSizes",     f_QFontDatabase_standardSizes);

   return QC_QFontDatabase;
}

