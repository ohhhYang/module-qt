/*
 QC_QGroupBox.cc
 
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

#include "QC_QGroupBox.h"
#include "QC_QWidget.h"

qore_classid_t CID_QGROUPBOX;
class QoreClass *QC_QGroupBox = 0;

//QGroupBox ( QWidget * parent = 0 )
//QGroupBox ( const QString & title, QWidget * parent = 0 )
static void QGROUPBOX_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   QString title;

   const AbstractQoreNode *p = get_param(params, 0);

   bool got_title = !get_qstring(p, title, xsink, true);
   if (got_title)
      p = get_param(params, 1);

   const QoreObject *o = dynamic_cast<const QoreObject *>(p);
   QoreQWidget *parent = o ? (QoreQWidget *)o->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   ReferenceHolder<QoreQWidget> parentHolder(parent, xsink);
   if (got_title)
      self->setPrivate(CID_QGROUPBOX, new QoreQGroupBox(self, title, parent ? parent->getQWidget() : 0));
   else
      self->setPrivate(CID_QGROUPBOX, new QoreQGroupBox(self, parent ? parent->getQWidget() : 0));

   return;
}

static void QGROUPBOX_copy(class QoreObject *self, class QoreObject *old, class QoreQGroupBox *qgb, ExceptionSink *xsink)
{
   xsink->raiseException("QGROUPBOX-COPY-ERROR", "objects of this class cannot be copied");
}

//Qt::Alignment alignment () const
static AbstractQoreNode *QGROUPBOX_alignment(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qgb->getQGroupBox()->alignment());
}

//bool isCheckable () const
static AbstractQoreNode *QGROUPBOX_isCheckable(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qgb->getQGroupBox()->isCheckable());
}

//bool isChecked () const
static AbstractQoreNode *QGROUPBOX_isChecked(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qgb->getQGroupBox()->isChecked());
}

//bool isFlat () const
static AbstractQoreNode *QGROUPBOX_isFlat(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qgb->getQGroupBox()->isFlat());
}

//void setAlignment ( int alignment )
static AbstractQoreNode *QGROUPBOX_setAlignment(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int alignment = p ? p->getAsInt() : 0;
   qgb->getQGroupBox()->setAlignment(alignment);
   return 0;
}

//void setCheckable ( bool checkable )
static AbstractQoreNode *QGROUPBOX_setCheckable(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool checkable = p ? p->getAsBool() : false;
   qgb->getQGroupBox()->setCheckable(checkable);
   return 0;
}

//void setFlat ( bool flat )
static AbstractQoreNode *QGROUPBOX_setFlat(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool flat = p ? p->getAsBool() : false;
   qgb->getQGroupBox()->setFlat(flat);
   return 0;
}

//void setTitle ( const QString & title )
static AbstractQoreNode *QGROUPBOX_setTitle(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   const QoreStringNode *p = test_string_param(params, 0);
   if (!p) {
      xsink->raiseException("QGROUPBOX-SETTITLE-PARAM-ERROR", "expecting a string as first argument to QGroupBox::setTitle()");
      return 0;
   }
   const char *title = p->getBuffer();
   qgb->getQGroupBox()->setTitle(title);
   return 0;
}

//QString title () const
static AbstractQoreNode *QGROUPBOX_title(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreStringNode(qgb->getQGroupBox()->title().toUtf8().data(), QCS_UTF8);
}

//void setChecked ( bool checked )
static AbstractQoreNode *QGROUPBOX_setChecked(QoreObject *self, QoreAbstractQGroupBox *qgb, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool checked = p ? p->getAsBool() : false;
   qgb->getQGroupBox()->setChecked(checked);
   return 0;
}

QoreClass *initQGroupBoxClass(QoreClass *qwidget)
{
   QC_QGroupBox = new QoreClass("QGroupBox", QDOM_GUI);
   CID_QGROUPBOX = QC_QGroupBox->getID();

   QC_QGroupBox->addBuiltinVirtualBaseClass(qwidget);

   QC_QGroupBox->setConstructor(QGROUPBOX_constructor);
   QC_QGroupBox->setCopy((q_copy_t)QGROUPBOX_copy);

   QC_QGroupBox->addMethod("alignment",                   (q_method_t)QGROUPBOX_alignment);
   QC_QGroupBox->addMethod("isCheckable",                 (q_method_t)QGROUPBOX_isCheckable);
   QC_QGroupBox->addMethod("isChecked",                   (q_method_t)QGROUPBOX_isChecked);
   QC_QGroupBox->addMethod("isFlat",                      (q_method_t)QGROUPBOX_isFlat);
   QC_QGroupBox->addMethod("setAlignment",                (q_method_t)QGROUPBOX_setAlignment);
   QC_QGroupBox->addMethod("setCheckable",                (q_method_t)QGROUPBOX_setCheckable);
   QC_QGroupBox->addMethod("setFlat",                     (q_method_t)QGROUPBOX_setFlat);
   QC_QGroupBox->addMethod("setTitle",                    (q_method_t)QGROUPBOX_setTitle);
   QC_QGroupBox->addMethod("title",                       (q_method_t)QGROUPBOX_title);
   QC_QGroupBox->addMethod("setChecked",                  (q_method_t)QGROUPBOX_setChecked);

   return QC_QGroupBox;
}
