/*
 QC_QTreeWidgetItem.cc
 
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

#include "qore-qt-gui.h"

#include "QC_QTreeWidgetItem.h"
#include "QC_QTreeWidget.h"

qore_classid_t CID_QTREEWIDGETITEM;
QoreClass *QC_QTreeWidgetItem = 0;

//QTreeWidgetItem ( int type = Type )
//QTreeWidgetItem ( const QStringList & strings, int type = Type )
//QTreeWidgetItem ( QTreeWidget * parent, int type = Type )
//QTreeWidgetItem ( QTreeWidget * parent, const QStringList & strings, int type = Type )
//QTreeWidgetItem ( QTreeWidget * parent, QTreeWidgetItem * preceding, int type = Type )
//QTreeWidgetItem ( QTreeWidgetItem * parent, int type = Type )
//QTreeWidgetItem ( QTreeWidgetItem * parent, const QStringList & strings, int type = Type )
//QTreeWidgetItem ( QTreeWidgetItem * parent, QTreeWidgetItem * preceding, int type = Type )
//QTreeWidgetItem ( const QTreeWidgetItem & other )
static void QTREEWIDGETITEM_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem());
      return;
   }
   if (p && p->getType() == NT_OBJECT) {
      QoreQTreeWidget *parent = (QoreQTreeWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGET, xsink);
      if (!parent) {
	 QoreQTreeWidgetItem *i_parent = (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink);
	 if (!i_parent) {
	    if (!xsink->isException())
	       xsink->raiseException("QTREEWIDGETITEM-CONSTRUCTOR-PARAM-ERROR", "QTreeWidgetItem::constructor() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
	    return;
	 }
	 ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(i_parent), xsink);
	 p = get_param(params, 1);
	 if (p && p->getType() == NT_LIST) {
	    QStringList strings;
	    ConstListIterator li_strings(reinterpret_cast<const QoreListNode *>(p));
	    while (li_strings.next()) {
	       QoreStringNodeValueHelper str(li_strings.getValue());
	       QString tmp;
	       if (get_qstring(*str, tmp, xsink))
		  return;
	       strings.push_back(tmp);
	    }
	    p = get_param(params, 2);
	    int type = !is_nothing(p) ? p->getAsInt() : QTreeWidgetItem::Type;
	    self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem(i_parent->getQTreeWidgetItem(), strings, type));
	    return;
	 }

	 if (p && p->getType() == NT_OBJECT) {
	    QoreQTreeWidgetItem *preceding = (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink);
	    if (!preceding) {
	       if (!xsink->isException())
		  xsink->raiseException("QTREEWIDGETITEM-CONSTRUCTOR-PARAM-ERROR", "this version of QTreeWidgetItem::constructor() expects an object derived from QTreeWidgetItem as the second argument");
	       return;
	    }
	    ReferenceHolder<AbstractPrivateData> precedingHolder(static_cast<AbstractPrivateData *>(preceding), xsink);
	    p = get_param(params, 2);
	    int type = !is_nothing(p) ? p->getAsInt() : QTreeWidgetItem::Type;
	    self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem(i_parent->getQTreeWidgetItem(), preceding->getQTreeWidgetItem(), type));
	    return;
	 }	 
	 
	 int type = !is_nothing(p) ? p->getAsInt() : QTreeWidgetItem::Type;
	 self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem(i_parent->getQTreeWidgetItem(), type));
	 return;
      }

      if (p && p->getType() == NT_LIST) {
	 QStringList strings;
	 ConstListIterator li_strings(reinterpret_cast<const QoreListNode *>(p));
	 while (li_strings.next()) {
	    QoreStringNodeValueHelper str(li_strings.getValue());
	    QString tmp;
	    if (get_qstring(*str, tmp, xsink))
	       return;
	    strings.push_back(tmp);
	 }
	 p = get_param(params, 2);
	 int type = !is_nothing(p) ? p->getAsInt() : QTreeWidgetItem::Type;
	 self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem(static_cast<QTreeWidget *>(parent->qobj), strings, type));
	 return;
      }

      if (p && p->getType() == NT_OBJECT) {
	 QoreQTreeWidgetItem *preceding = (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink);
	 if (!preceding) {
	    if (!xsink->isException())
	       xsink->raiseException("QTREEWIDGETITEM-CONSTRUCTOR-PARAM-ERROR", "this version of QTreeWidgetItem::constructor() expects an object derived from QTreeWidgetItem as the second argument");
	    return;
	 }
	 ReferenceHolder<AbstractPrivateData> precedingHolder(static_cast<AbstractPrivateData *>(preceding), xsink);
	 p = get_param(params, 2);
	 int type = !is_nothing(p) ? p->getAsInt() : QTreeWidgetItem::Type;
	 self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem(static_cast<QTreeWidget *>(parent->qobj), preceding->getQTreeWidgetItem(), type));
	 return;
      }

      int type = !is_nothing(p) ? p->getAsInt() : QTreeWidgetItem::Type;
      self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem(static_cast<QTreeWidget *>(parent->qobj), type));
      return;
   }

   if (p && p->getType() == NT_LIST) {
      QStringList strings;
      ConstListIterator li_strings(reinterpret_cast<const QoreListNode *>(p));
      while (li_strings.next()) {
         QoreStringNodeValueHelper str(li_strings.getValue());
         QString tmp;
         if (get_qstring(*str, tmp, xsink))
            return;
         strings.push_back(tmp);
      }
      p = get_param(params, 1);
      int type = !is_nothing(p) ? p->getAsInt() : QTreeWidgetItem::Type;
      self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem(strings, type));
      return;
   }

   int type = !is_nothing(p) ? p->getAsInt() : QTreeWidgetItem::Type;
   self->setPrivate(CID_QTREEWIDGETITEM, new QoreQTreeWidgetItem(type));
   return;
}

static void QTREEWIDGETITEM_copy(QoreObject *self, QoreObject *old, QoreQTreeWidgetItem *qtwi, ExceptionSink *xsink) {
   xsink->raiseException("QTREEWIDGETITEM-COPY-ERROR", "objects of this class cannot be copied");
}

//void addChild ( QTreeWidgetItem * child )
static AbstractQoreNode *QTREEWIDGETITEM_addChild(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *child = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!child) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGETITEM-ADDCHILD-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidgetItem::addChild()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> childHolder(static_cast<AbstractPrivateData *>(child), xsink);
   qtwi->getQTreeWidgetItem()->addChild(child->getQTreeWidgetItem());
   return 0;
}

/*
//void addChildren ( const QList<QTreeWidgetItem *> & children )
static AbstractQoreNode *QTREEWIDGETITEM_addChildren(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QList<QTreeWidgetItem*> children = p;
   qtwi->qore_obj->addChildren(children);
   return 0;
}
*/

//QBrush background ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_background(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return return_object(QC_QBrush, new QoreQBrush(qtwi->qore_obj->background(column)));
}

//Qt::CheckState checkState ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_checkState(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreBigIntNode(qtwi->qore_obj->checkState(column));
}

//QTreeWidgetItem * child ( int index ) const
static AbstractQoreNode *QTREEWIDGETITEM_child(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   
   QTreeWidgetItem *qtwi_rv = qtwi->qore_obj->child(index);
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//int childCount () const
static AbstractQoreNode *QTREEWIDGETITEM_childCount(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtwi->qore_obj->childCount());
}

//QTreeWidgetItem::ChildIndicatorPolicy childIndicatorPolicy () const
static AbstractQoreNode *QTREEWIDGETITEM_childIndicatorPolicy(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtwi->qore_obj->childIndicatorPolicy());
}

//virtual QTreeWidgetItem * clone () const
static AbstractQoreNode *QTREEWIDGETITEM_clone(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   QTreeWidgetItem *qtwi_rv = qtwi->qore_obj->clone();
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//int columnCount () const
static AbstractQoreNode *QTREEWIDGETITEM_columnCount(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtwi->qore_obj->columnCount());
}

//virtual QVariant data ( int column, int role ) const
static AbstractQoreNode *QTREEWIDGETITEM_data(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int role = p ? p->getAsInt() : 0;
   return return_qvariant(qtwi->qore_obj->data(column, role));
}

//Qt::ItemFlags flags () const
static AbstractQoreNode *QTREEWIDGETITEM_flags(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtwi->qore_obj->flags());
}

//QFont font ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_font(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return return_object(QC_QFont, new QoreQFont(qtwi->qore_obj->font(column)));
}

//QBrush foreground ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_foreground(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return return_object(QC_QBrush, new QoreQBrush(qtwi->qore_obj->foreground(column)));
}

//QIcon icon ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_icon(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return return_object(QC_QIcon, new QoreQIcon(qtwi->qore_obj->icon(column)));
}

//int indexOfChild ( QTreeWidgetItem * child ) const
static AbstractQoreNode *QTREEWIDGETITEM_indexOfChild(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *child = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!child) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGETITEM-INDEXOFCHILD-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidgetItem::indexOfChild()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> childHolder(static_cast<AbstractPrivateData *>(child), xsink);
   return new QoreBigIntNode(qtwi->qore_obj->indexOfChild(child->getQTreeWidgetItem()));
}

//void insertChild ( int index, QTreeWidgetItem * child )
static AbstractQoreNode *QTREEWIDGETITEM_insertChild(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQTreeWidgetItem *child = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!child) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGETITEM-INSERTCHILD-PARAM-ERROR", "expecting a QTreeWidgetItem object as second argument to QTreeWidgetItem::insertChild()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> childHolder(static_cast<AbstractPrivateData *>(child), xsink);
   qtwi->qore_obj->insertChild(index, child->getQTreeWidgetItem());
   return 0;
}

/*
//void insertChildren ( int index, const QList<QTreeWidgetItem *> & children )
static AbstractQoreNode *QTREEWIDGETITEM_insertChildren(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   ??? QList<QTreeWidgetItem*> children = p;
   qtwi->qore_obj->insertChildren(index, children);
   return 0;
}
*/

//bool isDisabled () const
static AbstractQoreNode *QTREEWIDGETITEM_isDisabled(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtwi->qore_obj->isDisabled());
}

//bool isExpanded () const
static AbstractQoreNode *QTREEWIDGETITEM_isExpanded(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtwi->qore_obj->isExpanded());
}

//bool isFirstColumnSpanned () const
static AbstractQoreNode *QTREEWIDGETITEM_isFirstColumnSpanned(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtwi->qore_obj->isFirstColumnSpanned());
}

//bool isHidden () const
static AbstractQoreNode *QTREEWIDGETITEM_isHidden(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtwi->qore_obj->isHidden());
}

//bool isSelected () const
static AbstractQoreNode *QTREEWIDGETITEM_isSelected(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtwi->qore_obj->isSelected());
}

//QTreeWidgetItem * parent () const
static AbstractQoreNode *QTREEWIDGETITEM_parent(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   QTreeWidgetItem *qtwi_rv = qtwi->qore_obj->parent();
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

/*
//virtual void read ( QDataStream & in )
static AbstractQoreNode *QTREEWIDGETITEM_read(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QDataStream in = p;
   qtwi->qore_obj->read(in);
   return 0;
}
*/

//void removeChild ( QTreeWidgetItem * child )
static AbstractQoreNode *QTREEWIDGETITEM_removeChild(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *child = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!child) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGETITEM-REMOVECHILD-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidgetItem::removeChild()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> childHolder(static_cast<AbstractPrivateData *>(child), xsink);
   qtwi->qore_obj->removeChild(child->getQTreeWidgetItem());
   return 0;
}

//void setBackground ( int column, const QBrush & brush )
static AbstractQoreNode *QTREEWIDGETITEM_setBackground(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QBrush brush;
   if (get_qbrush(p, brush, xsink))
      return 0;
   qtwi->qore_obj->setBackground(column, brush);
   return 0;
}

//void setCheckState ( int column, Qt::CheckState state )
static AbstractQoreNode *QTREEWIDGETITEM_setCheckState(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   Qt::CheckState state = (Qt::CheckState)(p ? p->getAsInt() : 0);
   qtwi->qore_obj->setCheckState(column, state);
   return 0;
}

//void setChildIndicatorPolicy ( QTreeWidgetItem::ChildIndicatorPolicy policy )
static AbstractQoreNode *QTREEWIDGETITEM_setChildIndicatorPolicy(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QTreeWidgetItem::ChildIndicatorPolicy policy = (QTreeWidgetItem::ChildIndicatorPolicy)(p ? p->getAsInt() : 0);
   qtwi->qore_obj->setChildIndicatorPolicy(policy);
   return 0;
}

//virtual void setData ( int column, int role, const QVariant & value )
static AbstractQoreNode *QTREEWIDGETITEM_setData(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int role = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QVariant value;
   if (get_qvariant(p, value, xsink))
      return 0;
   qtwi->qore_obj->setData(column, role, value);
   return 0;
}

//void setDisabled ( bool disabled )
static AbstractQoreNode *QTREEWIDGETITEM_setDisabled(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool disabled = p ? p->getAsBool() : false;
   qtwi->qore_obj->setDisabled(disabled);
   return 0;
}

//void setExpanded ( bool expand )
static AbstractQoreNode *QTREEWIDGETITEM_setExpanded(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool expand = p ? p->getAsBool() : false;
   qtwi->qore_obj->setExpanded(expand);
   return 0;
}

//void setFirstColumnSpanned ( bool span )
static AbstractQoreNode *QTREEWIDGETITEM_setFirstColumnSpanned(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool span = p ? p->getAsBool() : false;
   qtwi->qore_obj->setFirstColumnSpanned(span);
   return 0;
}

//void setFlags ( Qt::ItemFlags flags )
static AbstractQoreNode *QTREEWIDGETITEM_setFlags(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::ItemFlags flags = (Qt::ItemFlags)(p ? p->getAsInt() : 0);
   qtwi->qore_obj->setFlags(flags);
   return 0;
}

//void setFont ( int column, const QFont & font )
static AbstractQoreNode *QTREEWIDGETITEM_setFont(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQFont *font = (p && p->getType() == NT_OBJECT) ? (QoreQFont *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QFONT, xsink) : 0;
   if (!font) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGETITEM-SETFONT-PARAM-ERROR", "expecting a QFont object as second argument to QTreeWidgetItem::setFont()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> fontHolder(static_cast<AbstractPrivateData *>(font), xsink);
   qtwi->qore_obj->setFont(column, *(static_cast<QFont *>(font)));
   return 0;
}

//void setForeground ( int column, const QBrush & brush )
static AbstractQoreNode *QTREEWIDGETITEM_setForeground(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QBrush brush;
   if (get_qbrush(p, brush, xsink))
      return 0;
   qtwi->qore_obj->setForeground(column, brush);
   return 0;
}

//void setHidden ( bool hide )
static AbstractQoreNode *QTREEWIDGETITEM_setHidden(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool hide = p ? p->getAsBool() : false;
   qtwi->qore_obj->setHidden(hide);
   return 0;
}

//void setIcon ( int column, const QIcon & icon )
static AbstractQoreNode *QTREEWIDGETITEM_setIcon(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQIcon *icon = (p && p->getType() == NT_OBJECT) ? (QoreQIcon *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QICON, xsink) : 0;
   if (!icon) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGETITEM-SETICON-PARAM-ERROR", "expecting a QIcon object as second argument to QTreeWidgetItem::setIcon()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> iconHolder(static_cast<AbstractPrivateData *>(icon), xsink);
   qtwi->qore_obj->setIcon(column, *(static_cast<QIcon *>(icon)));
   return 0;
}

//void setSelected ( bool select )
static AbstractQoreNode *QTREEWIDGETITEM_setSelected(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool select = p ? p->getAsBool() : false;
   qtwi->qore_obj->setSelected(select);
   return 0;
}

//void setSizeHint ( int column, const QSize & size )
static AbstractQoreNode *QTREEWIDGETITEM_setSizeHint(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQSize *size = (p && p->getType() == NT_OBJECT) ? (QoreQSize *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QSIZE, xsink) : 0;
   if (!size) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGETITEM-SETSIZEHINT-PARAM-ERROR", "expecting a QSize object as second argument to QTreeWidgetItem::setSizeHint()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> sizeHolder(static_cast<AbstractPrivateData *>(size), xsink);
   qtwi->qore_obj->setSizeHint(column, *(static_cast<QSize *>(size)));
   return 0;
}

//void setStatusTip ( int column, const QString & statusTip )
static AbstractQoreNode *QTREEWIDGETITEM_setStatusTip(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QString statusTip;
   if (get_qstring(p, statusTip, xsink))
      return 0;
   qtwi->qore_obj->setStatusTip(column, statusTip);
   return 0;
}

//void setText ( int column, const QString & text )
static AbstractQoreNode *QTREEWIDGETITEM_setText(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QString text;
   if (get_qstring(p, text, xsink))
      return 0;
   qtwi->qore_obj->setText(column, text);
   return 0;
}

//void setTextAlignment ( int column, int alignment )
static AbstractQoreNode *QTREEWIDGETITEM_setTextAlignment(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int alignment = p ? p->getAsInt() : 0;
   qtwi->qore_obj->setTextAlignment(column, alignment);
   return 0;
}

//void setToolTip ( int column, const QString & toolTip )
static AbstractQoreNode *QTREEWIDGETITEM_setToolTip(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QString toolTip;
   if (get_qstring(p, toolTip, xsink))
      return 0;
   qtwi->qore_obj->setToolTip(column, toolTip);
   return 0;
}

//void setWhatsThis ( int column, const QString & whatsThis )
static AbstractQoreNode *QTREEWIDGETITEM_setWhatsThis(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QString whatsThis;
   if (get_qstring(p, whatsThis, xsink))
      return 0;
   qtwi->qore_obj->setWhatsThis(column, whatsThis);
   return 0;
}

//QSize sizeHint ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_sizeHint(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return return_object(QC_QSize, new QoreQSize(qtwi->qore_obj->sizeHint(column)));
}

//void sortChildren ( int column, Qt::SortOrder order )
static AbstractQoreNode *QTREEWIDGETITEM_sortChildren(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   Qt::SortOrder order = (Qt::SortOrder)(p ? p->getAsInt() : 0);
   qtwi->qore_obj->sortChildren(column, order);
   return 0;
}

//QString statusTip ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_statusTip(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreStringNode(qtwi->qore_obj->statusTip(column).toUtf8().data(), QCS_UTF8);
}

//QTreeWidgetItem * takeChild ( int index )
static AbstractQoreNode *QTREEWIDGETITEM_takeChild(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;

   QTreeWidgetItem *qtwi_rv = qtwi->qore_obj->takeChild(index);
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

/*
//QList<QTreeWidgetItem *> takeChildren ()
static AbstractQoreNode *QTREEWIDGETITEM_takeChildren(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   ??? return new QoreBigIntNode(qtwi->qore_obj->takeChildren());
}
*/

//QString text ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_text(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreStringNode(qtwi->qore_obj->text(column).toUtf8().data(), QCS_UTF8);
}

//int textAlignment ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_textAlignment(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreBigIntNode(qtwi->qore_obj->textAlignment(column));
}

//QString toolTip ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_toolTip(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreStringNode(qtwi->qore_obj->toolTip(column).toUtf8().data(), QCS_UTF8);
}

//QTreeWidget * treeWidget () const
static AbstractQoreNode *QTREEWIDGETITEM_treeWidget(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   QTreeWidget *qt_qobj = qtwi->qore_obj->treeWidget();
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QTreeWidget, getProgram());
   QoreQtQTreeWidget *t_qobj = new QoreQtQTreeWidget(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QTREEWIDGET, t_qobj);
   return rv_obj;
}

//int type () const
static AbstractQoreNode *QTREEWIDGETITEM_type(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtwi->qore_obj->type());
}

//QString whatsThis ( int column ) const
static AbstractQoreNode *QTREEWIDGETITEM_whatsThis(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreStringNode(qtwi->qore_obj->whatsThis(column).toUtf8().data(), QCS_UTF8);
}

/*
//virtual void write ( QDataStream & out ) const
static AbstractQoreNode *QTREEWIDGETITEM_write(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QDataStream out = p;
   qtwi->qore_obj->write(out);
   return 0;
}
*/

//void emitDataChanged ()
static AbstractQoreNode *QTREEWIDGETITEM_emitDataChanged(QoreObject *self, QoreQTreeWidgetItem *qtwi, const QoreListNode *params, ExceptionSink *xsink) {
   qtwi->emitDataChanged();
   return 0;
}

static QoreClass *initQTreeWidgetItemClass() {
   QC_QTreeWidgetItem = new QoreClass("QTreeWidgetItem", QDOM_GUI);
   CID_QTREEWIDGETITEM = QC_QTreeWidgetItem->getID();

   QC_QTreeWidgetItem->setConstructor(QTREEWIDGETITEM_constructor);
   QC_QTreeWidgetItem->setCopy((q_copy_t)QTREEWIDGETITEM_copy);

   QC_QTreeWidgetItem->addMethod("addChild",                    (q_method_t)QTREEWIDGETITEM_addChild);
   //QC_QTreeWidgetItem->addMethod("addChildren",                 (q_method_t)QTREEWIDGETITEM_addChildren);
   QC_QTreeWidgetItem->addMethod("background",                  (q_method_t)QTREEWIDGETITEM_background);
   QC_QTreeWidgetItem->addMethod("checkState",                  (q_method_t)QTREEWIDGETITEM_checkState);
   QC_QTreeWidgetItem->addMethod("child",                       (q_method_t)QTREEWIDGETITEM_child);
   QC_QTreeWidgetItem->addMethod("childCount",                  (q_method_t)QTREEWIDGETITEM_childCount);
   QC_QTreeWidgetItem->addMethod("childIndicatorPolicy",        (q_method_t)QTREEWIDGETITEM_childIndicatorPolicy);
   QC_QTreeWidgetItem->addMethod("clone",                       (q_method_t)QTREEWIDGETITEM_clone);
   QC_QTreeWidgetItem->addMethod("columnCount",                 (q_method_t)QTREEWIDGETITEM_columnCount);
   QC_QTreeWidgetItem->addMethod("data",                        (q_method_t)QTREEWIDGETITEM_data);
   QC_QTreeWidgetItem->addMethod("flags",                       (q_method_t)QTREEWIDGETITEM_flags);
   QC_QTreeWidgetItem->addMethod("font",                        (q_method_t)QTREEWIDGETITEM_font);
   QC_QTreeWidgetItem->addMethod("foreground",                  (q_method_t)QTREEWIDGETITEM_foreground);
   QC_QTreeWidgetItem->addMethod("icon",                        (q_method_t)QTREEWIDGETITEM_icon);
   QC_QTreeWidgetItem->addMethod("indexOfChild",                (q_method_t)QTREEWIDGETITEM_indexOfChild);
   QC_QTreeWidgetItem->addMethod("insertChild",                 (q_method_t)QTREEWIDGETITEM_insertChild);
   //QC_QTreeWidgetItem->addMethod("insertChildren",              (q_method_t)QTREEWIDGETITEM_insertChildren);
   QC_QTreeWidgetItem->addMethod("isDisabled",                  (q_method_t)QTREEWIDGETITEM_isDisabled);
   QC_QTreeWidgetItem->addMethod("isExpanded",                  (q_method_t)QTREEWIDGETITEM_isExpanded);
   QC_QTreeWidgetItem->addMethod("isFirstColumnSpanned",        (q_method_t)QTREEWIDGETITEM_isFirstColumnSpanned);
   QC_QTreeWidgetItem->addMethod("isHidden",                    (q_method_t)QTREEWIDGETITEM_isHidden);
   QC_QTreeWidgetItem->addMethod("isSelected",                  (q_method_t)QTREEWIDGETITEM_isSelected);
   QC_QTreeWidgetItem->addMethod("parent",                      (q_method_t)QTREEWIDGETITEM_parent);
   //QC_QTreeWidgetItem->addMethod("read",                        (q_method_t)QTREEWIDGETITEM_read);
   QC_QTreeWidgetItem->addMethod("removeChild",                 (q_method_t)QTREEWIDGETITEM_removeChild);
   QC_QTreeWidgetItem->addMethod("setBackground",               (q_method_t)QTREEWIDGETITEM_setBackground);
   QC_QTreeWidgetItem->addMethod("setCheckState",               (q_method_t)QTREEWIDGETITEM_setCheckState);
   QC_QTreeWidgetItem->addMethod("setChildIndicatorPolicy",     (q_method_t)QTREEWIDGETITEM_setChildIndicatorPolicy);
   QC_QTreeWidgetItem->addMethod("setData",                     (q_method_t)QTREEWIDGETITEM_setData);
   QC_QTreeWidgetItem->addMethod("setDisabled",                 (q_method_t)QTREEWIDGETITEM_setDisabled);
   QC_QTreeWidgetItem->addMethod("setExpanded",                 (q_method_t)QTREEWIDGETITEM_setExpanded);
   QC_QTreeWidgetItem->addMethod("setFirstColumnSpanned",       (q_method_t)QTREEWIDGETITEM_setFirstColumnSpanned);
   QC_QTreeWidgetItem->addMethod("setFlags",                    (q_method_t)QTREEWIDGETITEM_setFlags);
   QC_QTreeWidgetItem->addMethod("setFont",                     (q_method_t)QTREEWIDGETITEM_setFont);
   QC_QTreeWidgetItem->addMethod("setForeground",               (q_method_t)QTREEWIDGETITEM_setForeground);
   QC_QTreeWidgetItem->addMethod("setHidden",                   (q_method_t)QTREEWIDGETITEM_setHidden);
   QC_QTreeWidgetItem->addMethod("setIcon",                     (q_method_t)QTREEWIDGETITEM_setIcon);
   QC_QTreeWidgetItem->addMethod("setSelected",                 (q_method_t)QTREEWIDGETITEM_setSelected);
   QC_QTreeWidgetItem->addMethod("setSizeHint",                 (q_method_t)QTREEWIDGETITEM_setSizeHint);
   QC_QTreeWidgetItem->addMethod("setStatusTip",                (q_method_t)QTREEWIDGETITEM_setStatusTip);
   QC_QTreeWidgetItem->addMethod("setText",                     (q_method_t)QTREEWIDGETITEM_setText);
   QC_QTreeWidgetItem->addMethod("setTextAlignment",            (q_method_t)QTREEWIDGETITEM_setTextAlignment);
   QC_QTreeWidgetItem->addMethod("setToolTip",                  (q_method_t)QTREEWIDGETITEM_setToolTip);
   QC_QTreeWidgetItem->addMethod("setWhatsThis",                (q_method_t)QTREEWIDGETITEM_setWhatsThis);
   QC_QTreeWidgetItem->addMethod("sizeHint",                    (q_method_t)QTREEWIDGETITEM_sizeHint);
   QC_QTreeWidgetItem->addMethod("sortChildren",                (q_method_t)QTREEWIDGETITEM_sortChildren);
   QC_QTreeWidgetItem->addMethod("statusTip",                   (q_method_t)QTREEWIDGETITEM_statusTip);
   QC_QTreeWidgetItem->addMethod("takeChild",                   (q_method_t)QTREEWIDGETITEM_takeChild);
   //QC_QTreeWidgetItem->addMethod("takeChildren",                (q_method_t)QTREEWIDGETITEM_takeChildren);
   QC_QTreeWidgetItem->addMethod("text",                        (q_method_t)QTREEWIDGETITEM_text);
   QC_QTreeWidgetItem->addMethod("textAlignment",               (q_method_t)QTREEWIDGETITEM_textAlignment);
   QC_QTreeWidgetItem->addMethod("toolTip",                     (q_method_t)QTREEWIDGETITEM_toolTip);
   QC_QTreeWidgetItem->addMethod("treeWidget",                  (q_method_t)QTREEWIDGETITEM_treeWidget);
   QC_QTreeWidgetItem->addMethod("type",                        (q_method_t)QTREEWIDGETITEM_type);
   QC_QTreeWidgetItem->addMethod("whatsThis",                   (q_method_t)QTREEWIDGETITEM_whatsThis);
   //QC_QTreeWidgetItem->addMethod("write",                       (q_method_t)QTREEWIDGETITEM_write);

   // protected functions
   QC_QTreeWidgetItem->addMethod("emitDataChanged",             (q_method_t)QTREEWIDGETITEM_emitDataChanged, true);

   return QC_QTreeWidgetItem;
}

QoreNamespace *initQTreeWidgetItemNS() {
   QoreNamespace *ns = new QoreNamespace("QTreeWidgetItem");
   ns->addSystemClass(initQTreeWidgetItemClass());

   // ItemType enum
   ns->addConstant("Type",                     new QoreBigIntNode(QTreeWidgetItem::Type));
   ns->addConstant("UserType",                 new QoreBigIntNode(QTreeWidgetItem::UserType));

   // ChildIndicatorPolicy enum
   ns->addConstant("ShowIndicator",            new QoreBigIntNode(QTreeWidgetItem::ShowIndicator));
   ns->addConstant("DontShowIndicator",        new QoreBigIntNode(QTreeWidgetItem::DontShowIndicator));
   ns->addConstant("DontShowIndicatorWhenChildless", new QoreBigIntNode(QTreeWidgetItem::DontShowIndicatorWhenChildless));
   
   return ns;
}
