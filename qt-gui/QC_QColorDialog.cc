/*
 QC_QColorDialog.cc
 
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

#include "QC_QColorDialog.h"
#include "QC_QColor.h"
#include "QC_QWidget.h"

#include "qore-qt-gui.h"

//QRgb customColor ( int i )
static AbstractQoreNode *f_QColorDialog_customColor(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int i = p ? p->getAsInt() : 0;
   return new QoreBigIntNode(QColorDialog::customColor(i));
}

//int customCount ()
static AbstractQoreNode *f_QColorDialog_customCount(const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(QColorDialog::customCount());
}

//QColor getColor ( const QColor & initial = Qt::white, QWidget * parent = 0 )
static AbstractQoreNode *f_QColorDialog_getColor(const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQColor *initial = p ? (QoreQColor *)p->getReferencedPrivateData(CID_QCOLOR, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> initialHolder(static_cast<AbstractPrivateData *>(initial), xsink);

   p = test_object_param(params, 1);
   QoreQWidget *parent = p ? (QoreQWidget *)p->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   QoreObject *o_qc = new QoreObject(QC_QColor, getProgram());
   QoreQColor *q_qc = new QoreQColor(QColorDialog::getColor(initial ? *(static_cast<QColor *>(initial)) : Qt::white, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
   o_qc->setPrivate(CID_QCOLOR, q_qc);
   return o_qc;
}

/*
//QRgb getRgba ( QRgb initial = 0xffffffff, bool * ok = 0, QWidget * parent = 0 )
static AbstractQoreNode *f_QColorDialog_getRgba(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int64 initial = !is_nothing(p) ? p->getAsBigInt() : 0xffffffff;
   p = get_param(params, 1);
   ??? bool* ok = p;
   p = get_param(params, 2);
   QoreQWidget *parent = p ? (QoreQWidget *)p->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return new QoreBigIntNode(QColorDialog::getRgba(initial, ok, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
}
*/

//void setCustomColor ( int number, QRgb color )
static AbstractQoreNode *f_QColorDialog_setCustomColor(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int number = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int64 color = p ? p->getAsBigInt() : 0;
   QColorDialog::setCustomColor(number, color);
   return 0;
}

//void setStandardColor ( int number, QRgb color )
static AbstractQoreNode *f_QColorDialog_setStandardColor(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int number = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int64 color = p ? p->getAsBigInt() : 0;
   QColorDialog::setStandardColor(number, color);
   return 0;
}

QoreClass *initQColorDialogClass()
{
   QoreClass *QC_QColorDialog = new QoreClass("QColorDialog", QDOM_GUI);

   QC_QColorDialog->addStaticMethod("customColor",       f_QColorDialog_customColor);
   QC_QColorDialog->addStaticMethod("customCount",       f_QColorDialog_customCount);
   QC_QColorDialog->addStaticMethod("getColor",          f_QColorDialog_getColor);
   //QC_QColorDialog->addStaticMethod("getRgba",           f_QColorDialog_getRgba);
   QC_QColorDialog->addStaticMethod("setCustomColor",    f_QColorDialog_setCustomColor);
   QC_QColorDialog->addStaticMethod("setStandardColor",  f_QColorDialog_setStandardColor);

   return QC_QColorDialog;
}
