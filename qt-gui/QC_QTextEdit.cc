/*
 QC_QTextEdit.cc
 
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

#include "QC_QTextEdit.h"
#include "QC_QWidget.h"
#include "QC_QPoint.h"
#include "QC_QMenu.h"
#include "QC_QTextCharFormat.h"
#include "QC_QFont.h"
#include "QC_QUrl.h"
#include "QC_QPrinter.h"
#include "QC_QColor.h"
#include "QC_QTextBrowser.h"

#include "qore-qt-gui.h"

qore_classid_t CID_QTEXTEDIT;
class QoreClass *QC_QTextEdit = 0;

//QTextEdit ( QWidget * parent = 0 )
//QTextEdit ( const QString & text, QWidget * parent = 0 )
static void QTEXTEDIT_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QTEXTEDIT, new QoreQTextEdit(self));
      return;
   }
   if (p && p->getType() == NT_OBJECT) {
      QoreQWidget *parent = (QoreQWidget *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QWIDGET, xsink);
      if (*xsink)
         return;
      ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
      self->setPrivate(CID_QTEXTEDIT, new QoreQTextEdit(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
      return;
   }
   QString text;
   if (get_qstring(p, text, xsink))
      return;

   const QoreObject *o = test_object_param(params, 1);
   QoreQWidget *parent = o ? (QoreQWidget *)o->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QTEXTEDIT, new QoreQTextEdit(self, text, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
   return;
}

static void QTEXTEDIT_copy(class QoreObject *self, class QoreObject *old, class QoreQTextEdit *qte, ExceptionSink *xsink)
{
   xsink->raiseException("QTEXTEDIT-COPY-ERROR", "objects of this class cannot be copied");
}

//bool acceptRichText () const
static AbstractQoreNode *QTEXTEDIT_acceptRichText(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qte->getQTextEdit()->acceptRichText());
}

//Qt::Alignment alignment () const
static AbstractQoreNode *QTEXTEDIT_alignment(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->alignment());
}

//QString anchorAt ( const QPoint & pos ) const
static AbstractQoreNode *QTEXTEDIT_anchorAt(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *pos = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!pos) {
      if (!xsink->isException())
         xsink->raiseException("QTEXTEDIT-ANCHORAT-PARAM-ERROR", "expecting a QPoint object as first argument to QTextEdit::anchorAt()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> posHolder(static_cast<AbstractPrivateData *>(pos), xsink);
   return new QoreStringNode(qte->getQTextEdit()->anchorAt(*(static_cast<QPoint *>(pos))).toUtf8().data(), QCS_UTF8);
}

//AutoFormatting autoFormatting () const
static AbstractQoreNode *QTEXTEDIT_autoFormatting(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->autoFormatting());
}

//bool canPaste () const
static AbstractQoreNode *QTEXTEDIT_canPaste(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qte->getQTextEdit()->canPaste());
}

//QMenu * createStandardContextMenu ()
static AbstractQoreNode *QTEXTEDIT_createStandardContextMenu(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QMenu *qt_qobj = qte->getQTextEdit()->createStandardContextMenu();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      rv_obj->ref();
   else {
      rv_obj = new QoreObject(QC_QMenu, getProgram());
      QoreQtQMenu *t_qobj = new QoreQtQMenu(rv_obj, qt_qobj);
      rv_obj->setPrivate(CID_QMENU, t_qobj);
   }
   return rv_obj;
}

//QTextCharFormat currentCharFormat () const
static AbstractQoreNode *QTEXTEDIT_currentCharFormat(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qtcf = new QoreObject(QC_QTextCharFormat, getProgram());
   QoreQTextCharFormat *q_qtcf = new QoreQTextCharFormat(qte->getQTextEdit()->currentCharFormat());
   o_qtcf->setPrivate(CID_QTEXTCHARFORMAT, q_qtcf);
   return o_qtcf;
}

//QFont currentFont () const
static AbstractQoreNode *QTEXTEDIT_currentFont(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qf = new QoreObject(QC_QFont, getProgram());
   QoreQFont *q_qf = new QoreQFont(qte->getQTextEdit()->currentFont());
   o_qf->setPrivate(CID_QFONT, q_qf);
   return o_qf;
}

/*
//QTextCursor cursorForPosition ( const QPoint & pos ) const
static AbstractQoreNode *QTEXTEDIT_cursorForPosition(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *pos = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!pos) {
      if (!xsink->isException())
         xsink->raiseException("QTEXTEDIT-CURSORFORPOSITION-PARAM-ERROR", "expecting a QPoint object as first argument to QTextEdit::cursorForPosition()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> posHolder(static_cast<AbstractPrivateData *>(pos), xsink);
   ??? return new QoreBigIntNode(qte->getQTextEdit()->cursorForPosition(*(static_cast<QPoint *>(pos))));
}
*/

/*
//QRect cursorRect ( const QTextCursor & cursor ) const
//QRect cursorRect () const
static AbstractQoreNode *QTEXTEDIT_cursorRect(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      QoreObject *o_qr = new QoreObject(QC_QRect, getProgram());
      QoreQRect *q_qr = new QoreQRect(qte->getQTextEdit()->cursorRect());
      o_qr->setPrivate(CID_QRECT, q_qr);
      return o_qr;
   }
   ??? QTextCursor cursor = p;
   QoreObject *o_qr = new QoreObject(QC_QRect, getProgram());
   QoreQRect *q_qr = new QoreQRect(qte->getQTextEdit()->cursorRect(cursor));
   o_qr->setPrivate(CID_QRECT, q_qr);
   return o_qr;
}
*/

//int cursorWidth () const
static AbstractQoreNode *QTEXTEDIT_cursorWidth(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->cursorWidth());
}

/*
//QTextDocument * document () const
static AbstractQoreNode *QTEXTEDIT_document(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   ??? return new QoreBigIntNode(qte->getQTextEdit()->document());
}
*/

//QString documentTitle () const
static AbstractQoreNode *QTEXTEDIT_documentTitle(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreStringNode(qte->getQTextEdit()->documentTitle().toUtf8().data(), QCS_UTF8);
}

//void ensureCursorVisible ()
static AbstractQoreNode *QTEXTEDIT_ensureCursorVisible(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   qte->getQTextEdit()->ensureCursorVisible();
   return 0;
}

/*
//QList<ExtraSelection> extraSelections () const
static AbstractQoreNode *QTEXTEDIT_extraSelections(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   ??? return new QoreBigIntNode(qte->getQTextEdit()->extraSelections());
}
*/

//bool find ( const QString & exp, QTextDocument::FindFlags options = 0 )
static AbstractQoreNode *QTEXTEDIT_find(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString exp;
   if (get_qstring(p, exp, xsink))
      return 0;
   p = get_param(params, 1);
   QTextDocument::FindFlags options = (QTextDocument::FindFlags)(!is_nothing(p) ? p->getAsInt() : 0);
   return get_bool_node(qte->getQTextEdit()->find(exp, options));
}

//QString fontFamily () const
static AbstractQoreNode *QTEXTEDIT_fontFamily(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreStringNode(qte->getQTextEdit()->fontFamily().toUtf8().data(), QCS_UTF8);
}

//bool fontItalic () const
static AbstractQoreNode *QTEXTEDIT_fontItalic(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qte->getQTextEdit()->fontItalic());
}

//qreal fontPointSize () const
static AbstractQoreNode *QTEXTEDIT_fontPointSize(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreFloatNode((double)qte->getQTextEdit()->fontPointSize());
}

//bool fontUnderline () const
static AbstractQoreNode *QTEXTEDIT_fontUnderline(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qte->getQTextEdit()->fontUnderline());
}

//int fontWeight () const
static AbstractQoreNode *QTEXTEDIT_fontWeight(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->fontWeight());
}

//bool isReadOnly () const
static AbstractQoreNode *QTEXTEDIT_isReadOnly(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qte->getQTextEdit()->isReadOnly());
}

//bool isUndoRedoEnabled () const
static AbstractQoreNode *QTEXTEDIT_isUndoRedoEnabled(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qte->getQTextEdit()->isUndoRedoEnabled());
}

//int lineWrapColumnOrWidth () const
static AbstractQoreNode *QTEXTEDIT_lineWrapColumnOrWidth(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->lineWrapColumnOrWidth());
}

//LineWrapMode lineWrapMode () const
static AbstractQoreNode *QTEXTEDIT_lineWrapMode(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->lineWrapMode());
}

//virtual QVariant loadResource ( int type, const QUrl & name )
static AbstractQoreNode *QTEXTEDIT_loadResource(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int type = p ? p->getAsInt() : 0;

   const QoreObject *o = test_object_param(params, 1);
   QoreQUrl *name = o ? (QoreQUrl *)o->getReferencedPrivateData(CID_QURL, xsink) : 0;
   if (!name) {
      if (!xsink->isException())
         xsink->raiseException("QTEXTEDIT-LOADRESOURCE-PARAM-ERROR", "expecting a QUrl object as second argument to QTextEdit::loadResource()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> nameHolder(static_cast<AbstractPrivateData *>(name), xsink);
   return return_qvariant(qte->getQTextEdit()->loadResource(type, *(static_cast<QUrl *>(name))));
}

//void mergeCurrentCharFormat ( const QTextCharFormat & modifier )
static AbstractQoreNode *QTEXTEDIT_mergeCurrentCharFormat(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQTextCharFormat *modifier = p ? (QoreQTextCharFormat *)p->getReferencedPrivateData(CID_QTEXTCHARFORMAT, xsink) : 0;
   if (!modifier) {
      if (!xsink->isException())
         xsink->raiseException("QTEXTEDIT-MERGECURRENTCHARFORMAT-PARAM-ERROR", "expecting a QTextCharFormat object as first argument to QTextEdit::mergeCurrentCharFormat()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> modifierHolder(static_cast<AbstractPrivateData *>(modifier), xsink);
   qte->getQTextEdit()->mergeCurrentCharFormat(*(static_cast<QTextCharFormat *>(modifier)));
   return 0;
}

//void moveCursor ( QTextCursor::MoveOperation operation, QTextCursor::MoveMode mode = QTextCursor::MoveAnchor )
static AbstractQoreNode *QTEXTEDIT_moveCursor(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QTextCursor::MoveOperation operation = (QTextCursor::MoveOperation)(p ? p->getAsInt() : 0);
   p = get_param(params, 1);
   QTextCursor::MoveMode mode = !is_nothing(p) ? (QTextCursor::MoveMode)p->getAsInt() : QTextCursor::MoveAnchor;
   qte->getQTextEdit()->moveCursor(operation, mode);
   return 0;
}

//bool overwriteMode () const
static AbstractQoreNode *QTEXTEDIT_overwriteMode(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qte->getQTextEdit()->overwriteMode());
}

//void print ( QPrinter * printer ) const
static AbstractQoreNode *QTEXTEDIT_print(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPrinter *printer = p ? (QoreQPrinter *)p->getReferencedPrivateData(CID_QPRINTER, xsink) : 0;
   if (!printer) {
      if (!xsink->isException())
         xsink->raiseException("QTEXTEDIT-PRINT-PARAM-ERROR", "expecting a QPrinter object as first argument to QTextEdit::print()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> printerHolder(static_cast<AbstractPrivateData *>(printer), xsink);
   qte->getQTextEdit()->print(static_cast<QPrinter *>(printer));
   return 0;
}

//void setAcceptRichText ( bool accept )
static AbstractQoreNode *QTEXTEDIT_setAcceptRichText(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool accept = p ? p->getAsBool() : false;
   qte->getQTextEdit()->setAcceptRichText(accept);
   return 0;
}

//void setAutoFormatting ( AutoFormatting features )
static AbstractQoreNode *QTEXTEDIT_setAutoFormatting(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QTextEdit::AutoFormatting features = (QTextEdit::AutoFormatting)(p ? p->getAsInt() : 0);
   qte->getQTextEdit()->setAutoFormatting(features);
   return 0;
}

//void setCurrentCharFormat ( const QTextCharFormat & format )
static AbstractQoreNode *QTEXTEDIT_setCurrentCharFormat(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQTextCharFormat *format = p ? (QoreQTextCharFormat *)p->getReferencedPrivateData(CID_QTEXTCHARFORMAT, xsink) : 0;
   if (!format) {
      if (!xsink->isException())
         xsink->raiseException("QTEXTEDIT-SETCURRENTCHARFORMAT-PARAM-ERROR", "expecting a QTextCharFormat object as first argument to QTextEdit::setCurrentCharFormat()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> formatHolder(static_cast<AbstractPrivateData *>(format), xsink);
   qte->getQTextEdit()->setCurrentCharFormat(*(static_cast<QTextCharFormat *>(format)));
   return 0;
}

//void setCursorWidth ( int width )
static AbstractQoreNode *QTEXTEDIT_setCursorWidth(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int width = p ? p->getAsInt() : 0;
   qte->getQTextEdit()->setCursorWidth(width);
   return 0;
}

/*
//void setDocument ( QTextDocument * document )
static AbstractQoreNode *QTEXTEDIT_setDocument(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QTextDocument* document = p;
   qte->getQTextEdit()->setDocument(document);
   return 0;
}
*/

//void setDocumentTitle ( const QString & title )
static AbstractQoreNode *QTEXTEDIT_setDocumentTitle(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString title;
   if (get_qstring(p, title, xsink))
      return 0;
   qte->getQTextEdit()->setDocumentTitle(title);
   return 0;
}

/*
//void setExtraSelections ( const QList<ExtraSelection> & selections )
static AbstractQoreNode *QTEXTEDIT_setExtraSelections(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QList<ExtraSelection> selections = p;
   qte->getQTextEdit()->setExtraSelections(selections);
   return 0;
}
*/

//void setLineWrapColumnOrWidth ( int w )
static AbstractQoreNode *QTEXTEDIT_setLineWrapColumnOrWidth(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int w = p ? p->getAsInt() : 0;
   qte->getQTextEdit()->setLineWrapColumnOrWidth(w);
   return 0;
}

//void setLineWrapMode ( LineWrapMode mode )
static AbstractQoreNode *QTEXTEDIT_setLineWrapMode(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QTextEdit::LineWrapMode mode = (QTextEdit::LineWrapMode)(p ? p->getAsInt() : 0);
   qte->getQTextEdit()->setLineWrapMode(mode);
   return 0;
}

//void setOverwriteMode ( bool overwrite )
static AbstractQoreNode *QTEXTEDIT_setOverwriteMode(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool overwrite = p ? p->getAsBool() : false;
   qte->getQTextEdit()->setOverwriteMode(overwrite);
   return 0;
}

//void setReadOnly ( bool ro )
static AbstractQoreNode *QTEXTEDIT_setReadOnly(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool ro = p ? p->getAsBool() : false;
   qte->getQTextEdit()->setReadOnly(ro);
   return 0;
}

//void setTabChangesFocus ( bool b )
static AbstractQoreNode *QTEXTEDIT_setTabChangesFocus(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool b = p ? p->getAsBool() : false;
   qte->getQTextEdit()->setTabChangesFocus(b);
   return 0;
}

//void setTabStopWidth ( int width )
static AbstractQoreNode *QTEXTEDIT_setTabStopWidth(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int width = p ? p->getAsInt() : 0;
   qte->getQTextEdit()->setTabStopWidth(width);
   return 0;
}

/*
//void setTextCursor ( const QTextCursor & cursor )
static AbstractQoreNode *QTEXTEDIT_setTextCursor(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QTextCursor cursor = p;
   qte->getQTextEdit()->setTextCursor(cursor);
   return 0;
}
*/

//void setTextInteractionFlags ( Qt::TextInteractionFlags flags )
static AbstractQoreNode *QTEXTEDIT_setTextInteractionFlags(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::TextInteractionFlags flags = (Qt::TextInteractionFlags)(p ? p->getAsInt() : 0);
   qte->getQTextEdit()->setTextInteractionFlags(flags);
   return 0;
}

//void setUndoRedoEnabled ( bool enable )
static AbstractQoreNode *QTEXTEDIT_setUndoRedoEnabled(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qte->getQTextEdit()->setUndoRedoEnabled(enable);
   return 0;
}

//void setWordWrapMode ( QTextOption::WrapMode policy )
static AbstractQoreNode *QTEXTEDIT_setWordWrapMode(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QTextOption::WrapMode policy = (QTextOption::WrapMode)(p ? p->getAsInt() : 0);
   qte->getQTextEdit()->setWordWrapMode(policy);
   return 0;
}

//bool tabChangesFocus () const
static AbstractQoreNode *QTEXTEDIT_tabChangesFocus(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qte->getQTextEdit()->tabChangesFocus());
}

//int tabStopWidth () const
static AbstractQoreNode *QTEXTEDIT_tabStopWidth(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->tabStopWidth());
}

//QColor textColor () const
static AbstractQoreNode *QTEXTEDIT_textColor(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qc = new QoreObject(QC_QColor, getProgram());
   QoreQColor *q_qc = new QoreQColor(qte->getQTextEdit()->textColor());
   o_qc->setPrivate(CID_QCOLOR, q_qc);
   return o_qc;
}

/*
//QTextCursor textCursor () const
static AbstractQoreNode *QTEXTEDIT_textCursor(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   ??? return new QoreBigIntNode(qte->getQTextEdit()->textCursor());
}
*/

//Qt::TextInteractionFlags textInteractionFlags () const
static AbstractQoreNode *QTEXTEDIT_textInteractionFlags(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->textInteractionFlags());
}

//QString toHtml () const
static AbstractQoreNode *QTEXTEDIT_toHtml(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreStringNode(qte->getQTextEdit()->toHtml().toUtf8().data(), QCS_UTF8);
}

//QString toPlainText () const
static AbstractQoreNode *QTEXTEDIT_toPlainText(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreStringNode(qte->getQTextEdit()->toPlainText().toUtf8().data(), QCS_UTF8);
}

//QTextOption::WrapMode wordWrapMode () const
static AbstractQoreNode *QTEXTEDIT_wordWrapMode(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qte->getQTextEdit()->wordWrapMode());
}

//void append ( const QString & text )
static AbstractQoreNode *QTEXTEDIT_append(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString text;
   if (get_qstring(p, text, xsink))
      return 0;
   qte->getQTextEdit()->append(text);
   return 0;
}

//void clear ()
static AbstractQoreNode *QTEXTEDIT_clear(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   qte->getQTextEdit()->clear();
   return 0;
}

//void copy ()
static AbstractQoreNode *QTEXTEDIT_qt_copy(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   qte->getQTextEdit()->copy();
   return 0;
}

//void cut ()
static AbstractQoreNode *QTEXTEDIT_cut(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   qte->getQTextEdit()->cut();
   return 0;
}

//void insertHtml ( const QString & text )
static AbstractQoreNode *QTEXTEDIT_insertHtml(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString text;
   if (get_qstring(p, text, xsink))
      return 0;
   qte->getQTextEdit()->insertHtml(text);
   return 0;
}

//void insertPlainText ( const QString & text )
static AbstractQoreNode *QTEXTEDIT_insertPlainText(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString text;
   if (get_qstring(p, text, xsink))
      return 0;
   qte->getQTextEdit()->insertPlainText(text);
   return 0;
}

//void paste ()
static AbstractQoreNode *QTEXTEDIT_paste(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   qte->getQTextEdit()->paste();
   return 0;
}

//void redo ()
static AbstractQoreNode *QTEXTEDIT_redo(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   qte->getQTextEdit()->redo();
   return 0;
}

//void scrollToAnchor ( const QString & name )
static AbstractQoreNode *QTEXTEDIT_scrollToAnchor(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString name;
   if (get_qstring(p, name, xsink))
      return 0;
   qte->getQTextEdit()->scrollToAnchor(name);
   return 0;
}

//void selectAll ()
static AbstractQoreNode *QTEXTEDIT_selectAll(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   qte->getQTextEdit()->selectAll();
   return 0;
}

//void setAlignment ( Qt::Alignment a )
static AbstractQoreNode *QTEXTEDIT_setAlignment(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::Alignment a = (Qt::Alignment)(p ? p->getAsInt() : 0);
   qte->getQTextEdit()->setAlignment(a);
   return 0;
}

//void setCurrentFont ( const QFont & f )
static AbstractQoreNode *QTEXTEDIT_setCurrentFont(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQFont *f = p ? (QoreQFont *)p->getReferencedPrivateData(CID_QFONT, xsink) : 0;
   if (!f) {
      if (!xsink->isException())
         xsink->raiseException("QTEXTEDIT-SETCURRENTFONT-PARAM-ERROR", "expecting a QFont object as first argument to QTextEdit::setCurrentFont()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> fHolder(static_cast<AbstractPrivateData *>(f), xsink);
   qte->getQTextEdit()->setCurrentFont(*(static_cast<QFont *>(f)));
   return 0;
}

//void setFontFamily ( const QString & fontFamily )
static AbstractQoreNode *QTEXTEDIT_setFontFamily(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString fontFamily;
   if (get_qstring(p, fontFamily, xsink))
      return 0;
   qte->getQTextEdit()->setFontFamily(fontFamily);
   return 0;
}

//void setFontItalic ( bool italic )
static AbstractQoreNode *QTEXTEDIT_setFontItalic(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool italic = p ? p->getAsBool() : false;
   qte->getQTextEdit()->setFontItalic(italic);
   return 0;
}

//void setFontPointSize ( qreal s )
static AbstractQoreNode *QTEXTEDIT_setFontPointSize(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   qreal s = p ? p->getAsFloat() : 0.0;
   qte->getQTextEdit()->setFontPointSize(s);
   return 0;
}

//void setFontUnderline ( bool underline )
static AbstractQoreNode *QTEXTEDIT_setFontUnderline(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool underline = p ? p->getAsBool() : false;
   qte->getQTextEdit()->setFontUnderline(underline);
   return 0;
}

//void setFontWeight ( int weight )
static AbstractQoreNode *QTEXTEDIT_setFontWeight(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int weight = p ? p->getAsInt() : 0;
   qte->getQTextEdit()->setFontWeight(weight);
   return 0;
}

//void setHtml ( const QString & text )
static AbstractQoreNode *QTEXTEDIT_setHtml(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString text;
   if (get_qstring(p, text, xsink))
      return 0;
   qte->getQTextEdit()->setHtml(text);
   return 0;
}

//void setPlainText ( const QString & text )
static AbstractQoreNode *QTEXTEDIT_setPlainText(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString text;
   if (get_qstring(p, text, xsink))
      return 0;
   qte->getQTextEdit()->setPlainText(text);
   return 0;
}

//void setText ( const QString & text )
static AbstractQoreNode *QTEXTEDIT_setText(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString text;
   if (get_qstring(p, text, xsink))
      return 0;
   qte->getQTextEdit()->setText(text);
   return 0;
}

//void setTextColor ( const QColor & c )
static AbstractQoreNode *QTEXTEDIT_setTextColor(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQColor *c = p ? (QoreQColor *)p->getReferencedPrivateData(CID_QCOLOR, xsink) : 0;
   if (!c) {
      if (!xsink->isException())
         xsink->raiseException("QTEXTEDIT-SETTEXTCOLOR-PARAM-ERROR", "expecting a QColor object as first argument to QTextEdit::setTextColor()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> cHolder(static_cast<AbstractPrivateData *>(c), xsink);
   qte->getQTextEdit()->setTextColor(*(static_cast<QColor *>(c)));
   return 0;
}

//void undo ()
static AbstractQoreNode *QTEXTEDIT_undo(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   qte->getQTextEdit()->undo();
   return 0;
}

//void zoomIn ( int range = 1 )
static AbstractQoreNode *QTEXTEDIT_zoomIn(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int range = !is_nothing(p) ? p->getAsInt() : 1;
   qte->getQTextEdit()->zoomIn(range);
   return 0;
}

//void zoomOut ( int range = 1 )
static AbstractQoreNode *QTEXTEDIT_zoomOut(QoreObject *self, QoreAbstractQTextEdit *qte, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int range = !is_nothing(p) ? p->getAsInt() : 1;
   qte->getQTextEdit()->zoomOut(range);
   return 0;
}

static QoreClass *initQTextEditClass(QoreClass *qabstractscrollarea)
{
   QC_QTextEdit = new QoreClass("QTextEdit", QDOM_GUI);
   CID_QTEXTEDIT = QC_QTextEdit->getID();

   QC_QTextEdit->addBuiltinVirtualBaseClass(qabstractscrollarea);

   QC_QTextEdit->setConstructor(QTEXTEDIT_constructor);
   QC_QTextEdit->setCopy((q_copy_t)QTEXTEDIT_copy);

   QC_QTextEdit->addMethod("acceptRichText",              (q_method_t)QTEXTEDIT_acceptRichText);
   QC_QTextEdit->addMethod("alignment",                   (q_method_t)QTEXTEDIT_alignment);
   QC_QTextEdit->addMethod("anchorAt",                    (q_method_t)QTEXTEDIT_anchorAt);
   QC_QTextEdit->addMethod("autoFormatting",              (q_method_t)QTEXTEDIT_autoFormatting);
   QC_QTextEdit->addMethod("canPaste",                    (q_method_t)QTEXTEDIT_canPaste);
   QC_QTextEdit->addMethod("createStandardContextMenu",   (q_method_t)QTEXTEDIT_createStandardContextMenu);
   QC_QTextEdit->addMethod("currentCharFormat",           (q_method_t)QTEXTEDIT_currentCharFormat);
   QC_QTextEdit->addMethod("currentFont",                 (q_method_t)QTEXTEDIT_currentFont);
   //QC_QTextEdit->addMethod("cursorForPosition",           (q_method_t)QTEXTEDIT_cursorForPosition);
   //QC_QTextEdit->addMethod("cursorRect",                  (q_method_t)QTEXTEDIT_cursorRect);
   QC_QTextEdit->addMethod("cursorWidth",                 (q_method_t)QTEXTEDIT_cursorWidth);
   //QC_QTextEdit->addMethod("document",                    (q_method_t)QTEXTEDIT_document);
   QC_QTextEdit->addMethod("documentTitle",               (q_method_t)QTEXTEDIT_documentTitle);
   QC_QTextEdit->addMethod("ensureCursorVisible",         (q_method_t)QTEXTEDIT_ensureCursorVisible);
   //QC_QTextEdit->addMethod("extraSelections",             (q_method_t)QTEXTEDIT_extraSelections);
   QC_QTextEdit->addMethod("find",                        (q_method_t)QTEXTEDIT_find);
   QC_QTextEdit->addMethod("fontFamily",                  (q_method_t)QTEXTEDIT_fontFamily);
   QC_QTextEdit->addMethod("fontItalic",                  (q_method_t)QTEXTEDIT_fontItalic);
   QC_QTextEdit->addMethod("fontPointSize",               (q_method_t)QTEXTEDIT_fontPointSize);
   QC_QTextEdit->addMethod("fontUnderline",               (q_method_t)QTEXTEDIT_fontUnderline);
   QC_QTextEdit->addMethod("fontWeight",                  (q_method_t)QTEXTEDIT_fontWeight);
   QC_QTextEdit->addMethod("isReadOnly",                  (q_method_t)QTEXTEDIT_isReadOnly);
   QC_QTextEdit->addMethod("isUndoRedoEnabled",           (q_method_t)QTEXTEDIT_isUndoRedoEnabled);
   QC_QTextEdit->addMethod("lineWrapColumnOrWidth",       (q_method_t)QTEXTEDIT_lineWrapColumnOrWidth);
   QC_QTextEdit->addMethod("lineWrapMode",                (q_method_t)QTEXTEDIT_lineWrapMode);
   QC_QTextEdit->addMethod("loadResource",                (q_method_t)QTEXTEDIT_loadResource);
   QC_QTextEdit->addMethod("mergeCurrentCharFormat",      (q_method_t)QTEXTEDIT_mergeCurrentCharFormat);
   QC_QTextEdit->addMethod("moveCursor",                  (q_method_t)QTEXTEDIT_moveCursor);
   QC_QTextEdit->addMethod("overwriteMode",               (q_method_t)QTEXTEDIT_overwriteMode);
   QC_QTextEdit->addMethod("print",                       (q_method_t)QTEXTEDIT_print);
   QC_QTextEdit->addMethod("setAcceptRichText",           (q_method_t)QTEXTEDIT_setAcceptRichText);
   QC_QTextEdit->addMethod("setAutoFormatting",           (q_method_t)QTEXTEDIT_setAutoFormatting);
   QC_QTextEdit->addMethod("setCurrentCharFormat",        (q_method_t)QTEXTEDIT_setCurrentCharFormat);
   QC_QTextEdit->addMethod("setCursorWidth",              (q_method_t)QTEXTEDIT_setCursorWidth);
   //QC_QTextEdit->addMethod("setDocument",                 (q_method_t)QTEXTEDIT_setDocument);
   QC_QTextEdit->addMethod("setDocumentTitle",            (q_method_t)QTEXTEDIT_setDocumentTitle);
   //QC_QTextEdit->addMethod("setExtraSelections",          (q_method_t)QTEXTEDIT_setExtraSelections);
   QC_QTextEdit->addMethod("setLineWrapColumnOrWidth",    (q_method_t)QTEXTEDIT_setLineWrapColumnOrWidth);
   QC_QTextEdit->addMethod("setLineWrapMode",             (q_method_t)QTEXTEDIT_setLineWrapMode);
   QC_QTextEdit->addMethod("setOverwriteMode",            (q_method_t)QTEXTEDIT_setOverwriteMode);
   QC_QTextEdit->addMethod("setReadOnly",                 (q_method_t)QTEXTEDIT_setReadOnly);
   QC_QTextEdit->addMethod("setTabChangesFocus",          (q_method_t)QTEXTEDIT_setTabChangesFocus);
   QC_QTextEdit->addMethod("setTabStopWidth",             (q_method_t)QTEXTEDIT_setTabStopWidth);
   //QC_QTextEdit->addMethod("setTextCursor",               (q_method_t)QTEXTEDIT_setTextCursor);
   QC_QTextEdit->addMethod("setTextInteractionFlags",     (q_method_t)QTEXTEDIT_setTextInteractionFlags);
   QC_QTextEdit->addMethod("setUndoRedoEnabled",          (q_method_t)QTEXTEDIT_setUndoRedoEnabled);
   QC_QTextEdit->addMethod("setWordWrapMode",             (q_method_t)QTEXTEDIT_setWordWrapMode);
   QC_QTextEdit->addMethod("tabChangesFocus",             (q_method_t)QTEXTEDIT_tabChangesFocus);
   QC_QTextEdit->addMethod("tabStopWidth",                (q_method_t)QTEXTEDIT_tabStopWidth);
   QC_QTextEdit->addMethod("textColor",                   (q_method_t)QTEXTEDIT_textColor);
   //QC_QTextEdit->addMethod("textCursor",                  (q_method_t)QTEXTEDIT_textCursor);
   QC_QTextEdit->addMethod("textInteractionFlags",        (q_method_t)QTEXTEDIT_textInteractionFlags);
   QC_QTextEdit->addMethod("toHtml",                      (q_method_t)QTEXTEDIT_toHtml);
   QC_QTextEdit->addMethod("toPlainText",                 (q_method_t)QTEXTEDIT_toPlainText);
   QC_QTextEdit->addMethod("wordWrapMode",                (q_method_t)QTEXTEDIT_wordWrapMode);
   QC_QTextEdit->addMethod("append",                      (q_method_t)QTEXTEDIT_append);
   QC_QTextEdit->addMethod("clear",                       (q_method_t)QTEXTEDIT_clear);
   QC_QTextEdit->addMethod("qt_copy",                     (q_method_t)QTEXTEDIT_qt_copy);
   QC_QTextEdit->addMethod("cut",                         (q_method_t)QTEXTEDIT_cut);
   QC_QTextEdit->addMethod("insertHtml",                  (q_method_t)QTEXTEDIT_insertHtml);
   QC_QTextEdit->addMethod("insertPlainText",             (q_method_t)QTEXTEDIT_insertPlainText);
   QC_QTextEdit->addMethod("paste",                       (q_method_t)QTEXTEDIT_paste);
   QC_QTextEdit->addMethod("redo",                        (q_method_t)QTEXTEDIT_redo);
   QC_QTextEdit->addMethod("scrollToAnchor",              (q_method_t)QTEXTEDIT_scrollToAnchor);
   QC_QTextEdit->addMethod("selectAll",                   (q_method_t)QTEXTEDIT_selectAll);
   QC_QTextEdit->addMethod("setAlignment",                (q_method_t)QTEXTEDIT_setAlignment);
   QC_QTextEdit->addMethod("setCurrentFont",              (q_method_t)QTEXTEDIT_setCurrentFont);
   QC_QTextEdit->addMethod("setFontFamily",               (q_method_t)QTEXTEDIT_setFontFamily);
   QC_QTextEdit->addMethod("setFontItalic",               (q_method_t)QTEXTEDIT_setFontItalic);
   QC_QTextEdit->addMethod("setFontPointSize",            (q_method_t)QTEXTEDIT_setFontPointSize);
   QC_QTextEdit->addMethod("setFontUnderline",            (q_method_t)QTEXTEDIT_setFontUnderline);
   QC_QTextEdit->addMethod("setFontWeight",               (q_method_t)QTEXTEDIT_setFontWeight);
   QC_QTextEdit->addMethod("setHtml",                     (q_method_t)QTEXTEDIT_setHtml);
   QC_QTextEdit->addMethod("setPlainText",                (q_method_t)QTEXTEDIT_setPlainText);
   QC_QTextEdit->addMethod("setText",                     (q_method_t)QTEXTEDIT_setText);
   QC_QTextEdit->addMethod("setTextColor",                (q_method_t)QTEXTEDIT_setTextColor);
   QC_QTextEdit->addMethod("undo",                        (q_method_t)QTEXTEDIT_undo);
   QC_QTextEdit->addMethod("zoomIn",                      (q_method_t)QTEXTEDIT_zoomIn);
   QC_QTextEdit->addMethod("zoomOut",                     (q_method_t)QTEXTEDIT_zoomOut);

   return QC_QTextEdit;
}

QoreNamespace *initQTextEditNS(QoreClass *qabstractscrollarea)
{
   QoreNamespace *ns = new QoreNamespace("QTextEdit");

   QoreClass *qtextedit;
   ns->addSystemClass((qtextedit = initQTextEditClass(qabstractscrollarea)));
   ns->addSystemClass(initQTextBrowserClass(qtextedit));

   // LineWrapMode enum
   ns->addConstant("NoWrap",                   new QoreBigIntNode(QTextEdit::NoWrap));
   ns->addConstant("WidgetWidth",              new QoreBigIntNode(QTextEdit::WidgetWidth));
   ns->addConstant("FixedPixelWidth",          new QoreBigIntNode(QTextEdit::FixedPixelWidth));
   ns->addConstant("FixedColumnWidth",         new QoreBigIntNode(QTextEdit::FixedColumnWidth));

   // AutoFormattingFlag enum
   ns->addConstant("AutoNone",                 new QoreBigIntNode(QTextEdit::AutoNone));
   ns->addConstant("AutoBulletList",           new QoreBigIntNode(QTextEdit::AutoBulletList));
   ns->addConstant("AutoAll",                  new QoreBigIntNode(QTextEdit::AutoAll));

   return ns;
}

