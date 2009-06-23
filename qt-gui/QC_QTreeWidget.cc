/*
 QC_QTreeWidget.cc
 
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

#include "QC_QTreeWidget.h"
#include "QC_QTreeWidgetItem.h"

qore_classid_t CID_QTREEWIDGET;
QoreClass *QC_QTreeWidget = 0;

// QTreeWidget ( QWidget * parent = 0 )
static void QTREEWIDGET_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *parent = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QTREEWIDGET, new QoreQTreeWidget(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
   return;
}

static void QTREEWIDGET_copy(QoreObject *self, QoreObject *old, QoreQTreeWidget *qtw, ExceptionSink *xsink) {
   xsink->raiseException("QTREEWIDGET-COPY-ERROR", "objects of this class cannot be copied");
}

//void addTopLevelItem ( QTreeWidgetItem * item )
static AbstractQoreNode *QTREEWIDGET_addTopLevelItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-ADDTOPLEVELITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::addTopLevelItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   qtw->qobj->addTopLevelItem(item->getQTreeWidgetItem());
   return 0;
}

/*
//void addTopLevelItems ( const QList<QTreeWidgetItem *> & items )
static AbstractQoreNode *QTREEWIDGET_addTopLevelItems(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QList<QTreeWidgetItem*> items = p;
   qtw->qobj->addTopLevelItems(items);
   return 0;
}
*/

//void closePersistentEditor ( QTreeWidgetItem * item, int column = 0 )
static AbstractQoreNode *QTREEWIDGET_closePersistentEditor(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-CLOSEPERSISTENTEDITOR-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::closePersistentEditor()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   int column = !is_nothing(p) ? p->getAsInt() : 0;
   qtw->qobj->closePersistentEditor(item->getQTreeWidgetItem(), column);
   return 0;
}

//int columnCount () const
static AbstractQoreNode *QTREEWIDGET_columnCount(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtw->qobj->columnCount());
}

//int currentColumn () const
static AbstractQoreNode *QTREEWIDGET_currentColumn(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtw->qobj->currentColumn());
}

//QTreeWidgetItem * currentItem () const
static AbstractQoreNode *QTREEWIDGET_currentItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   QTreeWidgetItem *qtwi_rv = qtw->qobj->currentItem();
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//void editItem ( QTreeWidgetItem * item, int column = 0 )
static AbstractQoreNode *QTREEWIDGET_editItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-EDITITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::editItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   int column = !is_nothing(p) ? p->getAsInt() : 0;
   qtw->qobj->editItem(item->getQTreeWidgetItem(), column);
   return 0;
}

/*
//QList<QTreeWidgetItem *> findItems ( const QString & text, Qt::MatchFlags flags, int column = 0 ) const
static AbstractQoreNode *QTREEWIDGET_findItems(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString text;
   if (get_qstring(p, text, xsink))
      return 0;
   p = get_param(params, 1);
   Qt::MatchFlags flags = (Qt::MatchFlags)(p ? p->getAsInt() : 0);
   p = get_param(params, 2);
   int column = !is_nothing(p) ? p->getAsInt() : 0;
   ??? return new QoreBigIntNode(qtw->qobj->findItems(text, flags, column));
}
*/

//QTreeWidgetItem * headerItem () const
static AbstractQoreNode *QTREEWIDGET_headerItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   QTreeWidgetItem *qtwi_rv = qtw->qobj->headerItem();
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//int indexOfTopLevelItem ( QTreeWidgetItem * item ) const
static AbstractQoreNode *QTREEWIDGET_indexOfTopLevelItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-INDEXOFTOPLEVELITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::indexOfTopLevelItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   return new QoreBigIntNode(qtw->qobj->indexOfTopLevelItem(item->getQTreeWidgetItem()));
}

//void insertTopLevelItem ( int index, QTreeWidgetItem * item )
static AbstractQoreNode *QTREEWIDGET_insertTopLevelItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-INSERTTOPLEVELITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as second argument to QTreeWidget::insertTopLevelItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   qtw->qobj->insertTopLevelItem(index, item->getQTreeWidgetItem());
   return 0;
}

/*
//void insertTopLevelItems ( int index, const QList<QTreeWidgetItem *> & items )
static AbstractQoreNode *QTREEWIDGET_insertTopLevelItems(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   ??? QList<QTreeWidgetItem*> items = p;
   qtw->qobj->insertTopLevelItems(index, items);
   return 0;
}
*/

//QTreeWidgetItem * invisibleRootItem () const
static AbstractQoreNode *QTREEWIDGET_invisibleRootItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   QTreeWidgetItem *qtwi_rv = qtw->qobj->invisibleRootItem();
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//bool isFirstItemColumnSpanned ( const QTreeWidgetItem * item ) const
static AbstractQoreNode *QTREEWIDGET_isFirstItemColumnSpanned(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-ISFIRSTITEMCOLUMNSPANNED-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::isFirstItemColumnSpanned()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   return get_bool_node(qtw->qobj->isFirstItemColumnSpanned(item->getQTreeWidgetItem()));
}

//QTreeWidgetItem * itemAbove ( const QTreeWidgetItem * item ) const
static AbstractQoreNode *QTREEWIDGET_itemAbove(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-ITEMABOVE-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::itemAbove()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   QTreeWidgetItem *qtwi_rv = qtw->qobj->itemAbove(item->getQTreeWidgetItem());
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//QTreeWidgetItem * itemAt ( const QPoint & p ) const
//QTreeWidgetItem * itemAt ( int x, int y ) const
static AbstractQoreNode *QTREEWIDGET_itemAt(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQPoint *p = (QoreQPoint *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPOINT, xsink);
      if (!p) {
         if (!xsink->isException())
            xsink->raiseException("QTREEWIDGET-ITEMAT-PARAM-ERROR", "QTreeWidget::itemAt() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
         return 0;
      }
      ReferenceHolder<AbstractPrivateData> pHolder(static_cast<AbstractPrivateData *>(p), xsink);
      QTreeWidgetItem *qtwi_rv = qtw->qobj->itemAt(*(static_cast<QPoint *>(p)));
      return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
   }
   int x = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int y = p ? p->getAsInt() : 0;
   QTreeWidgetItem *qtwi_rv = qtw->qobj->itemAt(x, y);
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//QTreeWidgetItem * itemBelow ( const QTreeWidgetItem * item ) const
static AbstractQoreNode *QTREEWIDGET_itemBelow(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-ITEMBELOW-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::itemBelow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   QTreeWidgetItem *qtwi_rv = qtw->qobj->itemBelow(item->getQTreeWidgetItem());
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//QWidget * itemWidget ( QTreeWidgetItem * item, int column ) const
static AbstractQoreNode *QTREEWIDGET_itemWidget(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-ITEMWIDGET-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::itemWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   int column = p ? p->getAsInt() : 0;
   return return_qwidget(qtw->qobj->itemWidget(item->getQTreeWidgetItem(), column));
}

//void openPersistentEditor ( QTreeWidgetItem * item, int column = 0 )
static AbstractQoreNode *QTREEWIDGET_openPersistentEditor(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-OPENPERSISTENTEDITOR-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::openPersistentEditor()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   int column = !is_nothing(p) ? p->getAsInt() : 0;
   qtw->qobj->openPersistentEditor(item->getQTreeWidgetItem(), column);
   return 0;
}

//void removeItemWidget ( QTreeWidgetItem * item, int column )
static AbstractQoreNode *QTREEWIDGET_removeItemWidget(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-REMOVEITEMWIDGET-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::removeItemWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   int column = p ? p->getAsInt() : 0;
   qtw->qobj->removeItemWidget(item->getQTreeWidgetItem(), column);
   return 0;
}

/*
//QList<QTreeWidgetItem *> selectedItems () const
static AbstractQoreNode *QTREEWIDGET_selectedItems(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   ??? return new QoreBigIntNode(qtw->qobj->selectedItems());
}
*/

//void setColumnCount ( int columns )
static AbstractQoreNode *QTREEWIDGET_setColumnCount(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int columns = p ? p->getAsInt() : 0;
   qtw->qobj->setColumnCount(columns);
   return 0;
}

//void setCurrentItem ( QTreeWidgetItem * item )
//void setCurrentItem ( QTreeWidgetItem * item, int column )
//void setCurrentItem ( QTreeWidgetItem * item, int column, QItemSelectionModel::SelectionFlags command )
static AbstractQoreNode *QTREEWIDGET_setCurrentItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = p && p->getType() == NT_OBJECT ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;

   if (!item) {
      if (!xsink->isException())
	 xsink->raiseException("QTREEWIDGET-SETCURRENTITEM-PARAM-ERROR", "QTreeWidget::setCurrentItem() ", reinterpret_cast<const QoreObject *>(p)->getClassName());
      return 0;
   }

   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);

   if (num_params(params) == 1) {
      qtw->qobj->setCurrentItem(item->getQTreeWidgetItem());
      return 0;
   }

   p = get_param(params, 1);
   int column = p ? p->getAsInt() : 0;

   if (num_params(params) == 2) {
      qtw->qobj->setCurrentItem(item->getQTreeWidgetItem(), column);
      return 0;
   }

   p = get_param(params, 2);
   QItemSelectionModel::SelectionFlags command = (QItemSelectionModel::SelectionFlags)(p ? p->getAsInt() : 0);
   qtw->qobj->setCurrentItem(item->getQTreeWidgetItem(), column, command);
   return 0;
}

//void setFirstItemColumnSpanned ( const QTreeWidgetItem * item, bool span )
static AbstractQoreNode *QTREEWIDGET_setFirstItemColumnSpanned(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-SETFIRSTITEMCOLUMNSPANNED-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::setFirstItemColumnSpanned()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   bool span = p ? p->getAsBool() : false;
   qtw->qobj->setFirstItemColumnSpanned(item->getQTreeWidgetItem(), span);
   return 0;
}

//void setHeaderItem ( QTreeWidgetItem * item )
static AbstractQoreNode *QTREEWIDGET_setHeaderItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-SETHEADERITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::setHeaderItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   qtw->qobj->setHeaderItem(item->getQTreeWidgetItem());
   return 0;
}

//void setHeaderLabel ( const QString & label )
static AbstractQoreNode *QTREEWIDGET_setHeaderLabel(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString label;
   if (get_qstring(p, label, xsink))
      return 0;
   qtw->qobj->setHeaderLabel(label);
   return 0;
}

//void setHeaderLabels ( const QStringList & labels )
static AbstractQoreNode *QTREEWIDGET_setHeaderLabels(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (!p || p->getType() != NT_LIST) {
      xsink->raiseException("QTREEWIDGET-SETHEADERLABELS-ERROR", "expecting a list of strings passed to QTreeWidget::setHeaderLabels()");
      return 0;
   }
   QStringList labels;
   ConstListIterator li_labels(reinterpret_cast<const QoreListNode *>(p));
   while (li_labels.next()) {
      QoreStringNodeValueHelper str(li_labels.getValue());
      QString tmp;
      if (get_qstring(*str, tmp, xsink))
         return 0;
      labels.push_back(tmp);
   }
   qtw->qobj->setHeaderLabels(labels);
   return 0;
}

//void setItemWidget ( QTreeWidgetItem * item, int column, QWidget * widget )
static AbstractQoreNode *QTREEWIDGET_setItemWidget(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-SETITEMWIDGET-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::setItemWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QoreQWidget *widget = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (!widget) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-SETITEMWIDGET-PARAM-ERROR", "expecting a QWidget object as third argument to QTreeWidget::setItemWidget()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> widgetHolder(static_cast<AbstractPrivateData *>(widget), xsink);
   qtw->qobj->setItemWidget(item->getQTreeWidgetItem(), column, static_cast<QWidget *>(widget->getQWidget()));
   return 0;
}

//int sortColumn () const
static AbstractQoreNode *QTREEWIDGET_sortColumn(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtw->qobj->sortColumn());
}

//void sortItems ( int column, Qt::SortOrder order )
static AbstractQoreNode *QTREEWIDGET_sortItems(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   Qt::SortOrder order = (Qt::SortOrder)(p ? p->getAsInt() : 0);
   qtw->qobj->sortItems(column, order);
   return 0;
}

//QTreeWidgetItem * takeTopLevelItem ( int index )
static AbstractQoreNode *QTREEWIDGET_takeTopLevelItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   QTreeWidgetItem *qtwi_rv = qtw->qobj->takeTopLevelItem(index);
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//QTreeWidgetItem * topLevelItem ( int index ) const
static AbstractQoreNode *QTREEWIDGET_topLevelItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int index = p ? p->getAsInt() : 0;
   QTreeWidgetItem *qtwi_rv = qtw->qobj->topLevelItem(index);
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}

//int topLevelItemCount () const
static AbstractQoreNode *QTREEWIDGET_topLevelItemCount(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtw->qobj->topLevelItemCount());
}

//QRect visualItemRect ( const QTreeWidgetItem * item ) const
static AbstractQoreNode *QTREEWIDGET_visualItemRect(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-VISUALITEMRECT-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::visualItemRect()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   return return_object(QC_QRect, new QoreQRect(qtw->qobj->visualItemRect(item->getQTreeWidgetItem())));
}

//# void clear ()
static AbstractQoreNode *QTREEWIDGET_clear(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   qtw->qobj->clear();
   return 0;
}

//void collapseItem ( const QTreeWidgetItem * item )
static AbstractQoreNode *QTREEWIDGET_collapseItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-COLLAPSEITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::collapseItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   qtw->qobj->collapseItem(item->getQTreeWidgetItem());
   return 0;
}

//void expandItem ( const QTreeWidgetItem * item )
static AbstractQoreNode *QTREEWIDGET_expandItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-EXPANDITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::expandItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   qtw->qobj->expandItem(item->getQTreeWidgetItem());
   return 0;
}

//void scrollToItem ( const QTreeWidgetItem * item, QAbstractItemView::ScrollHint hint = EnsureVisible )
static AbstractQoreNode *QTREEWIDGET_scrollToItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-SCROLLTOITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::scrollToItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   QAbstractItemView::ScrollHint hint = !is_nothing(p) ? (QAbstractItemView::ScrollHint)p->getAsInt() : QTreeWidget::EnsureVisible;
   qtw->qobj->scrollToItem(item->getQTreeWidgetItem(), hint);
   return 0;
}

/*
// virtual bool dropMimeData ( QTreeWidgetItem * parent, int index, const QMimeData * data, Qt::DropAction action )
static AbstractQoreNode *QTREEWIDGET_dropMimeData(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *parent = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-DROPMIMEDATA-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::dropMimeData()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 1);
   int index = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QoreQMimeData *data = (p && p->getType() == NT_OBJECT) ? (QoreQMimeData *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMIMEDATA, xsink) : 0;
   if (!data) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-DROPMIMEDATA-PARAM-ERROR", "expecting a QMimeData object as third argument to QTreeWidget::dropMimeData()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> dataHolder(static_cast<AbstractPrivateData *>(data), xsink);
   p = get_param(params, 3);
   Qt::DropAction action = (Qt::DropAction)(p ? p->getAsInt() : 0);
   return get_bool_node(qtw->qobj->dropMimeData(parent->getQTreeWidgetItem(), index, static_cast<QMimeData *>(data->qobj), action));
}

//QModelIndex indexFromItem ( QTreeWidgetItem * item, int column = 0 ) const
static AbstractQoreNode *QTREEWIDGET_indexFromItem(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQTreeWidgetItem *item = (p && p->getType() == NT_OBJECT) ? (QoreQTreeWidgetItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QTREEWIDGETITEM, xsink) : 0;
   if (!item) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-INDEXFROMITEM-PARAM-ERROR", "expecting a QTreeWidgetItem object as first argument to QTreeWidget::indexFromItem()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> itemHolder(static_cast<AbstractPrivateData *>(item), xsink);
   p = get_param(params, 1);
   int column = !is_nothing(p) ? p->getAsInt() : 0;
   return return_object(QC_QModelIndex, new QoreQModelIndex(qtw->qobj->indexFromItem(item->getQTreeWidgetItem(), column)));
}

//QTreeWidgetItem * itemFromIndex ( const QModelIndex & index ) const
static AbstractQoreNode *QTREEWIDGET_itemFromIndex(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEWIDGET-ITEMFROMINDEX-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeWidget::itemFromIndex()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   QTreeWidgetItem *qtwi_rv = qtw->qobj->itemFromIndex(*(static_cast<QModelIndex *>(index)));
   return qtwi_rv ? return_object(QC_QTreeWidgetItem, new QoreQtQTreeWidgetItem(qtwi_rv)) : 0;
}
*/
/*
//virtual QMimeData * mimeData ( const QList<QTreeWidgetItem *> items ) const
static AbstractQoreNode *QTREEWIDGET_mimeData(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QList<QTreeWidgetItem*> items = p;
   QMimeData *qt_qobj = qtw->qobj->mimeData(items);
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QMimeData, getProgram());
   QoreQtQMimeData *t_qobj = new QoreQtQMimeData(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QMIMEDATA, t_qobj);
   return rv_obj;
}
*/

/*
//virtual QStringList mimeTypes () const
static AbstractQoreNode *QTREEWIDGET_mimeTypes(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qstringlist(qtw->qobj->mimeTypes());
}

//virtual Qt::DropActions supportedDropActions () const
static AbstractQoreNode *QTREEWIDGET_supportedDropActions(QoreObject *self, QoreQTreeWidget *qtw, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtw->qobj->supportedDropActions());
}
*/

QoreClass *initQTreeWidgetClass(QoreClass *qtreeview) {
   QC_QTreeWidget = new QoreClass("QTreeWidget", QDOM_GUI);
   CID_QTREEWIDGET = QC_QTreeWidget->getID();

   QC_QTreeWidget->addBuiltinVirtualBaseClass(qtreeview);

   QC_QTreeWidget->setConstructor(QTREEWIDGET_constructor);
   QC_QTreeWidget->setCopy((q_copy_t)QTREEWIDGET_copy);

   QC_QTreeWidget->addMethod("addTopLevelItem",             (q_method_t)QTREEWIDGET_addTopLevelItem);
   //QC_QTreeWidget->addMethod("addTopLevelItems",            (q_method_t)QTREEWIDGET_addTopLevelItems);
   QC_QTreeWidget->addMethod("closePersistentEditor",       (q_method_t)QTREEWIDGET_closePersistentEditor);
   QC_QTreeWidget->addMethod("columnCount",                 (q_method_t)QTREEWIDGET_columnCount);
   QC_QTreeWidget->addMethod("currentColumn",               (q_method_t)QTREEWIDGET_currentColumn);
   QC_QTreeWidget->addMethod("currentItem",                 (q_method_t)QTREEWIDGET_currentItem);
   QC_QTreeWidget->addMethod("editItem",                    (q_method_t)QTREEWIDGET_editItem);
   //QC_QTreeWidget->addMethod("findItems",                   (q_method_t)QTREEWIDGET_findItems);
   QC_QTreeWidget->addMethod("headerItem",                  (q_method_t)QTREEWIDGET_headerItem);
   QC_QTreeWidget->addMethod("indexOfTopLevelItem",         (q_method_t)QTREEWIDGET_indexOfTopLevelItem);
   QC_QTreeWidget->addMethod("insertTopLevelItem",          (q_method_t)QTREEWIDGET_insertTopLevelItem);
   //QC_QTreeWidget->addMethod("insertTopLevelItems",         (q_method_t)QTREEWIDGET_insertTopLevelItems);
   QC_QTreeWidget->addMethod("invisibleRootItem",           (q_method_t)QTREEWIDGET_invisibleRootItem);
   QC_QTreeWidget->addMethod("isFirstItemColumnSpanned",    (q_method_t)QTREEWIDGET_isFirstItemColumnSpanned);
   QC_QTreeWidget->addMethod("itemAbove",                   (q_method_t)QTREEWIDGET_itemAbove);
   QC_QTreeWidget->addMethod("itemAt",                      (q_method_t)QTREEWIDGET_itemAt);
   QC_QTreeWidget->addMethod("itemBelow",                   (q_method_t)QTREEWIDGET_itemBelow);
   QC_QTreeWidget->addMethod("itemWidget",                  (q_method_t)QTREEWIDGET_itemWidget);
   QC_QTreeWidget->addMethod("openPersistentEditor",        (q_method_t)QTREEWIDGET_openPersistentEditor);
   QC_QTreeWidget->addMethod("removeItemWidget",            (q_method_t)QTREEWIDGET_removeItemWidget);
   //QC_QTreeWidget->addMethod("selectedItems",               (q_method_t)QTREEWIDGET_selectedItems);
   QC_QTreeWidget->addMethod("setColumnCount",              (q_method_t)QTREEWIDGET_setColumnCount);
   QC_QTreeWidget->addMethod("setCurrentItem",              (q_method_t)QTREEWIDGET_setCurrentItem);
   QC_QTreeWidget->addMethod("setFirstItemColumnSpanned",   (q_method_t)QTREEWIDGET_setFirstItemColumnSpanned);
   QC_QTreeWidget->addMethod("setHeaderItem",               (q_method_t)QTREEWIDGET_setHeaderItem);
   QC_QTreeWidget->addMethod("setHeaderLabel",              (q_method_t)QTREEWIDGET_setHeaderLabel);
   QC_QTreeWidget->addMethod("setHeaderLabels",             (q_method_t)QTREEWIDGET_setHeaderLabels);
   QC_QTreeWidget->addMethod("setItemWidget",               (q_method_t)QTREEWIDGET_setItemWidget);
   QC_QTreeWidget->addMethod("sortColumn",                  (q_method_t)QTREEWIDGET_sortColumn);
   QC_QTreeWidget->addMethod("sortItems",                   (q_method_t)QTREEWIDGET_sortItems);
   QC_QTreeWidget->addMethod("takeTopLevelItem",            (q_method_t)QTREEWIDGET_takeTopLevelItem);
   QC_QTreeWidget->addMethod("topLevelItem",                (q_method_t)QTREEWIDGET_topLevelItem);
   QC_QTreeWidget->addMethod("topLevelItemCount",           (q_method_t)QTREEWIDGET_topLevelItemCount);
   QC_QTreeWidget->addMethod("visualItemRect",              (q_method_t)QTREEWIDGET_visualItemRect);
   QC_QTreeWidget->addMethod("clear",                       (q_method_t)QTREEWIDGET_clear);
   QC_QTreeWidget->addMethod("collapseItem",                (q_method_t)QTREEWIDGET_collapseItem);
   QC_QTreeWidget->addMethod("expandItem",                  (q_method_t)QTREEWIDGET_expandItem);
   QC_QTreeWidget->addMethod("scrollToItem",                (q_method_t)QTREEWIDGET_scrollToItem);

   /*
   QC_QTreeWidget->addMethod("dropMimeData",                (q_method_t)QTREEWIDGET_dropMimeData, true);
   QC_QTreeWidget->addMethod("indexFromItem",               (q_method_t)QTREEWIDGET_indexFromItem, true);
   QC_QTreeWidget->addMethod("itemFromIndex",               (q_method_t)QTREEWIDGET_itemFromIndex, true);
   //QC_QTreeWidget->addMethod("mimeData",                    (q_method_t)QTREEWIDGET_mimeData, true);
   QC_QTreeWidget->addMethod("mimeTypes",                   (q_method_t)QTREEWIDGET_mimeTypes, true);
   QC_QTreeWidget->addMethod("supportedDropActions",        (q_method_t)QTREEWIDGET_supportedDropActions, true);
   */

   return QC_QTreeWidget;
}
