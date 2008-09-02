/*
 QC_QFontInfo.cc
 
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

#include "QC_QFontInfo.h"
#include "QC_QFont.h"

#include "qore-qt-gui.h"

qore_classid_t CID_QFONTINFO;
class QoreClass *QC_QFontInfo = 0;

//QFontInfo ( const QFont & font )
//QFontInfo ( const QFontInfo & fi )
static void QFONTINFO_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQFont *font = p ? (QoreQFont *)p->getReferencedPrivateData(CID_QFONT, xsink) : 0;
   if (!font) {
      if (!xsink->isException())
         xsink->raiseException("QFONTINFO-QFONTINFO-PARAM-ERROR", "expecting a QFont object as first argument to QFontInfo::QFontInfo()");
      return;
   }
   ReferenceHolder<QoreQFont> fontHolder(font, xsink);
   self->setPrivate(CID_QFONTINFO, new QoreQFontInfo(*(static_cast<QFont *>(font))));
   return;
}

static void QFONTINFO_copy(class QoreObject *self, class QoreObject *old, class QoreQFontInfo *qfi, ExceptionSink *xsink)
{
   self->setPrivate(CID_QFONTINFO, new QoreQFontInfo(*qfi));
}

//bool bold () const
static AbstractQoreNode *QFONTINFO_bold(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qfi->bold());
}

//bool exactMatch () const
static AbstractQoreNode *QFONTINFO_exactMatch(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qfi->exactMatch());
}

//QString family () const
static AbstractQoreNode *QFONTINFO_family(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreStringNode(qfi->family().toUtf8().data(), QCS_UTF8);
}

//bool fixedPitch () const
static AbstractQoreNode *QFONTINFO_fixedPitch(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qfi->fixedPitch());
}

//bool italic () const
static AbstractQoreNode *QFONTINFO_italic(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qfi->italic());
}

//int pixelSize () const
static AbstractQoreNode *QFONTINFO_pixelSize(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qfi->pixelSize());
}

//int pointSize () const
static AbstractQoreNode *QFONTINFO_pointSize(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qfi->pointSize());
}

//qreal pointSizeF () const
static AbstractQoreNode *QFONTINFO_pointSizeF(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreFloatNode((double)qfi->pointSizeF());
}

//bool rawMode () const
static AbstractQoreNode *QFONTINFO_rawMode(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qfi->rawMode());
}

//QFont::Style style () const
static AbstractQoreNode *QFONTINFO_style(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qfi->style());
}

//QFont::StyleHint styleHint () const
static AbstractQoreNode *QFONTINFO_styleHint(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qfi->styleHint());
}

//int weight () const
static AbstractQoreNode *QFONTINFO_weight(QoreObject *self, QoreQFontInfo *qfi, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qfi->weight());
}

QoreClass *initQFontInfoClass()
{
   QC_QFontInfo = new QoreClass("QFontInfo", QDOM_GUI);
   CID_QFONTINFO = QC_QFontInfo->getID();

   QC_QFontInfo->setConstructor(QFONTINFO_constructor);
   QC_QFontInfo->setCopy((q_copy_t)QFONTINFO_copy);

   QC_QFontInfo->addMethod("bold",                        (q_method_t)QFONTINFO_bold);
   QC_QFontInfo->addMethod("exactMatch",                  (q_method_t)QFONTINFO_exactMatch);
   QC_QFontInfo->addMethod("family",                      (q_method_t)QFONTINFO_family);
   QC_QFontInfo->addMethod("fixedPitch",                  (q_method_t)QFONTINFO_fixedPitch);
   QC_QFontInfo->addMethod("italic",                      (q_method_t)QFONTINFO_italic);
   QC_QFontInfo->addMethod("pixelSize",                   (q_method_t)QFONTINFO_pixelSize);
   QC_QFontInfo->addMethod("pointSize",                   (q_method_t)QFONTINFO_pointSize);
   QC_QFontInfo->addMethod("pointSizeF",                  (q_method_t)QFONTINFO_pointSizeF);
   QC_QFontInfo->addMethod("rawMode",                     (q_method_t)QFONTINFO_rawMode);
   QC_QFontInfo->addMethod("style",                       (q_method_t)QFONTINFO_style);
   QC_QFontInfo->addMethod("styleHint",                   (q_method_t)QFONTINFO_styleHint);
   QC_QFontInfo->addMethod("weight",                      (q_method_t)QFONTINFO_weight);

   return QC_QFontInfo;
}
