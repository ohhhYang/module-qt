/*
 QC_QTreeView.cc
 
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

#include "QC_QModelIndex.h"
#include "QC_QTreeView.h"
#include "QC_QHeaderView.h"

qore_classid_t CID_QTREEVIEW;
QoreClass *QC_QTreeView = 0;

// QTreeView ( QWidget * parent = 0 )
static void QTREEVIEW_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQWidget *parent = (p && p->getType() == NT_OBJECT) ? (QoreQWidget *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QTREEVIEW, new QoreQTreeView(self, parent ? static_cast<QWidget *>(parent->getQWidget()) : 0));
   return;
}

static void QTREEVIEW_copy(QoreObject *self, QoreObject *old, QoreQTreeView *qtv, ExceptionSink *xsink) {
   xsink->raiseException("QTREEVIEW-COPY-ERROR", "objects of this class cannot be copied");
}

//bool allColumnsShowFocus () const
static AbstractQoreNode *QTREEVIEW_allColumnsShowFocus(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->allColumnsShowFocus());
}

//int autoExpandDelay () const
static AbstractQoreNode *QTREEVIEW_autoExpandDelay(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtv->getQTreeView()->autoExpandDelay());
}

//int columnAt ( int x ) const
static AbstractQoreNode *QTREEVIEW_columnAt(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int x = p ? p->getAsInt() : 0;
   return new QoreBigIntNode(qtv->getQTreeView()->columnAt(x));
}

//int columnViewportPosition ( int column ) const
static AbstractQoreNode *QTREEVIEW_columnViewportPosition(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreBigIntNode(qtv->getQTreeView()->columnViewportPosition(column));
}

//int columnWidth ( int column ) const
static AbstractQoreNode *QTREEVIEW_columnWidth(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreBigIntNode(qtv->getQTreeView()->columnWidth(column));
}

//bool expandsOnDoubleClick () const
static AbstractQoreNode *QTREEVIEW_expandsOnDoubleClick(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->expandsOnDoubleClick());
}

//QHeaderView * header () const
static AbstractQoreNode *QTREEVIEW_header(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   QoreObject *o_qhv = new QoreObject(QC_QHeaderView, getProgram());
   QHeaderView *hv = qtv->getQTreeView()->header();
   QoreQtQHeaderView *q_qhv = new QoreQtQHeaderView(o_qhv, hv);
   o_qhv->setPrivate(CID_QHEADERVIEW, q_qhv);
   return o_qhv;
}

//int indentation () const
static AbstractQoreNode *QTREEVIEW_indentation(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtv->getQTreeView()->indentation());
}

//QModelIndex indexAbove ( const QModelIndex & index ) const
static AbstractQoreNode *QTREEVIEW_indexAbove(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-INDEXABOVE-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::indexAbove()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qtv->getQTreeView()->indexAbove(*(static_cast<QModelIndex *>(index)))));
}

//QModelIndex indexBelow ( const QModelIndex & index ) const
static AbstractQoreNode *QTREEVIEW_indexBelow(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-INDEXBELOW-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::indexBelow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qtv->getQTreeView()->indexBelow(*(static_cast<QModelIndex *>(index)))));
}

//bool isAnimated () const
static AbstractQoreNode *QTREEVIEW_isAnimated(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->isAnimated());
}

//bool isColumnHidden ( int column ) const
static AbstractQoreNode *QTREEVIEW_isColumnHidden(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return get_bool_node(qtv->getQTreeView()->isColumnHidden(column));
}

//bool isExpanded ( const QModelIndex & index ) const
static AbstractQoreNode *QTREEVIEW_isExpanded(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-ISEXPANDED-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::isExpanded()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return get_bool_node(qtv->getQTreeView()->isExpanded(*(static_cast<QModelIndex *>(index))));
}

//bool isFirstColumnSpanned ( int row, const QModelIndex & parent ) const
static AbstractQoreNode *QTREEVIEW_isFirstColumnSpanned(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-ISFIRSTCOLUMNSPANNED-PARAM-ERROR", "expecting a QModelIndex object as second argument to QTreeView::isFirstColumnSpanned()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return get_bool_node(qtv->getQTreeView()->isFirstColumnSpanned(row, *(static_cast<QModelIndex *>(parent))));
}

//bool isHeaderHidden () const
static AbstractQoreNode *QTREEVIEW_isHeaderHidden(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->isHeaderHidden());
}

//bool isRowHidden ( int row, const QModelIndex & parent ) const
static AbstractQoreNode *QTREEVIEW_isRowHidden(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-ISROWHIDDEN-PARAM-ERROR", "expecting a QModelIndex object as second argument to QTreeView::isRowHidden()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return get_bool_node(qtv->getQTreeView()->isRowHidden(row, *(static_cast<QModelIndex *>(parent))));
}

//bool isSortingEnabled () const
static AbstractQoreNode *QTREEVIEW_isSortingEnabled(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->isSortingEnabled());
}

//bool itemsExpandable () const
static AbstractQoreNode *QTREEVIEW_itemsExpandable(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->itemsExpandable());
}

//bool rootIsDecorated () const
static AbstractQoreNode *QTREEVIEW_rootIsDecorated(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->rootIsDecorated());
}

//virtual void scrollTo ( const QModelIndex & index, ScrollHint hint = EnsureVisible )
static AbstractQoreNode *QTREEVIEW_scrollTo(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-SCROLLTO-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::scrollTo()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   p = get_param(params, 1);
   QTreeView::ScrollHint hint = !is_nothing(p) ? (QTreeView::ScrollHint)p->getAsInt() : QTreeView::EnsureVisible;
   qtv->getQTreeView()->QTreeView::scrollTo(*(static_cast<QModelIndex *>(index)), hint);
   return 0;
}

//void setAllColumnsShowFocus ( bool enable )
static AbstractQoreNode *QTREEVIEW_setAllColumnsShowFocus(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setAllColumnsShowFocus(enable);
   return 0;
}

//void setAnimated ( bool enable )
static AbstractQoreNode *QTREEVIEW_setAnimated(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setAnimated(enable);
   return 0;
}

//void setAutoExpandDelay ( int delay )
static AbstractQoreNode *QTREEVIEW_setAutoExpandDelay(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int delay = p ? p->getAsInt() : 0;
   qtv->getQTreeView()->setAutoExpandDelay(delay);
   return 0;
}

//void setColumnHidden ( int column, bool hide )
static AbstractQoreNode *QTREEVIEW_setColumnHidden(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   bool hide = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setColumnHidden(column, hide);
   return 0;
}

//void setColumnWidth ( int column, int width )
static AbstractQoreNode *QTREEVIEW_setColumnWidth(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int width = p ? p->getAsInt() : 0;
   qtv->getQTreeView()->setColumnWidth(column, width);
   return 0;
}

//void setExpanded ( const QModelIndex & index, bool expanded )
static AbstractQoreNode *QTREEVIEW_setExpanded(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-SETEXPANDED-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::setExpanded()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   p = get_param(params, 1);
   bool expanded = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setExpanded(*(static_cast<QModelIndex *>(index)), expanded);
   return 0;
}

//void setExpandsOnDoubleClick ( bool enable )
static AbstractQoreNode *QTREEVIEW_setExpandsOnDoubleClick(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setExpandsOnDoubleClick(enable);
   return 0;
}

//void setFirstColumnSpanned ( int row, const QModelIndex & parent, bool span )
static AbstractQoreNode *QTREEVIEW_setFirstColumnSpanned(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-SETFIRSTCOLUMNSPANNED-PARAM-ERROR", "expecting a QModelIndex object as second argument to QTreeView::setFirstColumnSpanned()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 2);
   bool span = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setFirstColumnSpanned(row, *(static_cast<QModelIndex *>(parent)), span);
   return 0;
}

//void setHeader ( QHeaderView * header )
static AbstractQoreNode *QTREEVIEW_setHeader(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQHeaderView *header = (p && p->getType() == NT_OBJECT) ? (QoreQHeaderView *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QHEADERVIEW, xsink) : 0;
   if (!header) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-SETHEADER-PARAM-ERROR", "expecting a QHeaderView object as first argument to QTreeView::setHeader()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> headerHolder(static_cast<AbstractPrivateData *>(header), xsink);
   qtv->getQTreeView()->setHeader(static_cast<QHeaderView *>(header->getQHeaderView()));
   return 0;
}

//void setHeaderHidden ( bool hide )
static AbstractQoreNode *QTREEVIEW_setHeaderHidden(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool hide = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setHeaderHidden(hide);
   return 0;
}

//void setIndentation ( int i )
static AbstractQoreNode *QTREEVIEW_setIndentation(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int i = p ? p->getAsInt() : 0;
   qtv->getQTreeView()->setIndentation(i);
   return 0;
}

//void setItemsExpandable ( bool enable )
static AbstractQoreNode *QTREEVIEW_setItemsExpandable(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setItemsExpandable(enable);
   return 0;
}

//void setRootIsDecorated ( bool show )
static AbstractQoreNode *QTREEVIEW_setRootIsDecorated(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool show = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setRootIsDecorated(show);
   return 0;
}

//void setRowHidden ( int row, const QModelIndex & parent, bool hide )
static AbstractQoreNode *QTREEVIEW_setRowHidden(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-SETROWHIDDEN-PARAM-ERROR", "expecting a QModelIndex object as second argument to QTreeView::setRowHidden()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 2);
   bool hide = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setRowHidden(row, *(static_cast<QModelIndex *>(parent)), hide);
   return 0;
}

//void setSortingEnabled ( bool enable )
static AbstractQoreNode *QTREEVIEW_setSortingEnabled(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setSortingEnabled(enable);
   return 0;
}

//void setUniformRowHeights ( bool uniform )
static AbstractQoreNode *QTREEVIEW_setUniformRowHeights(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool uniform = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setUniformRowHeights(uniform);
   return 0;
}

//void setWordWrap ( bool on )
static AbstractQoreNode *QTREEVIEW_setWordWrap(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool on = p ? p->getAsBool() : false;
   qtv->getQTreeView()->setWordWrap(on);
   return 0;
}

//void sortByColumn ( int column, Qt::SortOrder order )
static AbstractQoreNode *QTREEVIEW_sortByColumn(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   Qt::SortOrder order = (Qt::SortOrder)(p ? p->getAsInt() : 0);
   qtv->getQTreeView()->sortByColumn(column, order);
   return 0;
}

//bool uniformRowHeights () const
static AbstractQoreNode *QTREEVIEW_uniformRowHeights(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->uniformRowHeights());
}

//virtual QRect visualRect ( const QModelIndex & index ) const
static AbstractQoreNode *QTREEVIEW_visualRect(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-VISUALRECT-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::visualRect()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return return_object(QC_QRect, new QoreQRect(qtv->getQTreeView()->QTreeView::visualRect(*(static_cast<QModelIndex *>(index)))));
}

//bool wordWrap () const
static AbstractQoreNode *QTREEVIEW_wordWrap(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qtv->getQTreeView()->wordWrap());
}

//# void collapse ( const QModelIndex & index )
static AbstractQoreNode *QTREEVIEW_collapse(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-COLLAPSE-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::collapse()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   qtv->getQTreeView()->collapse(*(static_cast<QModelIndex *>(index)));
   return 0;
}

//void collapseAll ()
static AbstractQoreNode *QTREEVIEW_collapseAll(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   qtv->getQTreeView()->collapseAll();
   return 0;
}

//void expand ( const QModelIndex & index )
static AbstractQoreNode *QTREEVIEW_expand(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-EXPAND-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::expand()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   qtv->getQTreeView()->expand(*(static_cast<QModelIndex *>(index)));
   return 0;
}

//void expandAll ()
static AbstractQoreNode *QTREEVIEW_expandAll(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   qtv->getQTreeView()->expandAll();
   return 0;
}

//void expandToDepth ( int depth )
static AbstractQoreNode *QTREEVIEW_expandToDepth(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int depth = p ? p->getAsInt() : 0;
   qtv->getQTreeView()->expandToDepth(depth);
   return 0;
}

//void hideColumn ( int column )
static AbstractQoreNode *QTREEVIEW_hideColumn(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   qtv->getQTreeView()->hideColumn(column);
   return 0;
}

//void resizeColumnToContents ( int column )
static AbstractQoreNode *QTREEVIEW_resizeColumnToContents(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   qtv->getQTreeView()->resizeColumnToContents(column);
   return 0;
}

//void showColumn ( int column )
static AbstractQoreNode *QTREEVIEW_showColumn(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   qtv->getQTreeView()->showColumn(column);
   return 0;
}

// virtual void drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const
static AbstractQoreNode *QTREEVIEW_drawBranches(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQPainter *painter = (p && p->getType() == NT_OBJECT) ? (QoreQPainter *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPAINTER, xsink) : 0;
   if (!painter) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-DRAWBRANCHES-PARAM-ERROR", "expecting a QPainter object as first argument to QTreeView::drawBranches()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> painterHolder(static_cast<AbstractPrivateData *>(painter), xsink);
   p = get_param(params, 1);
   QoreQRect *rect = (p && p->getType() == NT_OBJECT) ? (QoreQRect *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QRECT, xsink) : 0;
   if (!rect) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-DRAWBRANCHES-PARAM-ERROR", "expecting a QRect object as second argument to QTreeView::drawBranches()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> rectHolder(static_cast<AbstractPrivateData *>(rect), xsink);
   p = get_param(params, 2);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-DRAWBRANCHES-PARAM-ERROR", "expecting a QModelIndex object as third argument to QTreeView::drawBranches()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   qtv->drawBranches(static_cast<QPainter *>(painter->getQPainter()), *(static_cast<QRect *>(rect)), *(static_cast<QModelIndex *>(index)));
   return 0;
}

//virtual void drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
static AbstractQoreNode *QTREEVIEW_drawRow(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQPainter *painter = (p && p->getType() == NT_OBJECT) ? (QoreQPainter *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPAINTER, xsink) : 0;
   if (!painter) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-DRAWROW-PARAM-ERROR", "expecting a QPainter object as first argument to QTreeView::drawRow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> painterHolder(static_cast<AbstractPrivateData *>(painter), xsink);
   p = get_param(params, 1);
   QoreQStyleOptionViewItem *option = (p && p->getType() == NT_OBJECT) ? (QoreQStyleOptionViewItem *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QSTYLEOPTIONVIEWITEM, xsink) : 0;
   if (!option) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-DRAWROW-PARAM-ERROR", "expecting a QStyleOptionViewItem object as second argument to QTreeView::drawRow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> optionHolder(static_cast<AbstractPrivateData *>(option), xsink);
   p = get_param(params, 2);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-DRAWROW-PARAM-ERROR", "expecting a QModelIndex object as third argument to QTreeView::drawRow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   qtv->drawRow(static_cast<QPainter *>(painter->getQPainter()), *(static_cast<QStyleOptionViewItem *>(option)), *(static_cast<QModelIndex *>(index)));
   return 0;
}

//void drawTree ( QPainter * painter, const QRegion & region ) const
static AbstractQoreNode *QTREEVIEW_drawTree(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQPainter *painter = (p && p->getType() == NT_OBJECT) ? (QoreQPainter *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPAINTER, xsink) : 0;
   if (!painter) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-DRAWTREE-PARAM-ERROR", "expecting a QPainter object as first argument to QTreeView::drawTree()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> painterHolder(static_cast<AbstractPrivateData *>(painter), xsink);
   p = get_param(params, 1);
   QoreQRegion *region = (p && p->getType() == NT_OBJECT) ? (QoreQRegion *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QREGION, xsink) : 0;
   if (!region) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-DRAWTREE-PARAM-ERROR", "expecting a QRegion object as second argument to QTreeView::drawTree()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> regionHolder(static_cast<AbstractPrivateData *>(region), xsink);
   qtv->drawTree(static_cast<QPainter *>(painter->getQPainter()), *(static_cast<QRegion *>(region)));
   return 0;
}

//virtual int horizontalOffset () const
static AbstractQoreNode *QTREEVIEW_horizontalOffset(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtv->horizontalOffset());
}

//int indexRowSizeHint ( const QModelIndex & index ) const
static AbstractQoreNode *QTREEVIEW_indexRowSizeHint(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-INDEXROWSIZEHINT-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::indexRowSizeHint()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return new QoreBigIntNode(qtv->indexRowSizeHint(*(static_cast<QModelIndex *>(index))));
}

//virtual QModelIndex moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
static AbstractQoreNode *QTREEVIEW_moveCursor(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int cursorAction = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   Qt::KeyboardModifiers modifiers = (Qt::KeyboardModifiers)(p ? p->getAsInt() : 0);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qtv->moveCursor(cursorAction, modifiers)));
}

//int rowHeight ( const QModelIndex & index ) const
static AbstractQoreNode *QTREEVIEW_rowHeight(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-ROWHEIGHT-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::rowHeight()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return new QoreBigIntNode(qtv->rowHeight(*(static_cast<QModelIndex *>(index))));
}

//virtual void rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end )
static AbstractQoreNode *QTREEVIEW_rowsAboutToBeRemoved(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-ROWSABOUTTOBEREMOVED-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::rowsAboutToBeRemoved()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 1);
   int start = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int end = p ? p->getAsInt() : 0;
   qtv->rowsAboutToBeRemoved(*(static_cast<QModelIndex *>(parent)), start, end);
   return 0;
}

//virtual void rowsInserted ( const QModelIndex & parent, int start, int end )
static AbstractQoreNode *QTREEVIEW_rowsInserted(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-ROWSINSERTED-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::rowsInserted()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 1);
   int start = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int end = p ? p->getAsInt() : 0;
   qtv->rowsInserted(*(static_cast<QModelIndex *>(parent)), start, end);
   return 0;
}

//virtual void scrollContentsBy ( int dx, int dy )
static AbstractQoreNode *QTREEVIEW_scrollContentsBy(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int dx = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int dy = p ? p->getAsInt() : 0;
   qtv->scrollContentsBy(dx, dy);
   return 0;
}

//virtual void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags command )
static AbstractQoreNode *QTREEVIEW_setSelection(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQRect *rect = (p && p->getType() == NT_OBJECT) ? (QoreQRect *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QRECT, xsink) : 0;
   if (!rect) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-SETSELECTION-PARAM-ERROR", "expecting a QRect object as first argument to QTreeView::setSelection()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> rectHolder(static_cast<AbstractPrivateData *>(rect), xsink);
   p = get_param(params, 1);
   QItemSelectionModel::SelectionFlags command = (QItemSelectionModel::SelectionFlags)(p ? p->getAsInt() : 0);
   qtv->setSelection(*(static_cast<QRect *>(rect)), command);
   return 0;
}

//virtual int sizeHintForColumn ( int column ) const
static AbstractQoreNode *QTREEVIEW_sizeHintForColumn(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   return new QoreBigIntNode(qtv->sizeHintForColumn(column));
}

//virtual int verticalOffset () const
static AbstractQoreNode *QTREEVIEW_verticalOffset(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qtv->verticalOffset());
}

//virtual QRegion visualRegionForSelection ( const QItemSelection & selection ) const
static AbstractQoreNode *QTREEVIEW_visualRegionForSelection(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQItemSelection *selection = (p && p->getType() == NT_OBJECT) ? (QoreQItemSelection *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTION, xsink) : 0;
   if (!selection) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-VISUALREGIONFORSELECTION-PARAM-ERROR", "expecting a QItemSelection object as first argument to QTreeView::visualRegionForSelection()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> selectionHolder(static_cast<AbstractPrivateData *>(selection), xsink);
   return return_object(QC_QRegion, new QoreQRegion(qtv->visualRegionForSelection(*(static_cast<QItemSelection *>(selection)))));
}

// void columnCountChanged ( int oldCount, int newCount )
static AbstractQoreNode *QTREEVIEW_columnCountChanged(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int oldCount = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int newCount = p ? p->getAsInt() : 0;
   qtv->columnCountChanged(oldCount, newCount);
   return 0;
}

//void columnMoved ()
static AbstractQoreNode *QTREEVIEW_columnMoved(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   qtv->columnMoved();
   return 0;
}

//void columnResized ( int column, int oldSize, int newSize )
static AbstractQoreNode *QTREEVIEW_columnResized(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int oldSize = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int newSize = p ? p->getAsInt() : 0;
   qtv->columnResized(column, oldSize, newSize);
   return 0;
}

//void rowsRemoved ( const QModelIndex & parent, int start, int end )
static AbstractQoreNode *QTREEVIEW_rowsRemoved(QoreObject *self, QoreAbstractQTreeView *qtv, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QTREEVIEW-ROWSREMOVED-PARAM-ERROR", "expecting a QModelIndex object as first argument to QTreeView::rowsRemoved()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 1);
   int start = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int end = p ? p->getAsInt() : 0;
   qtv->rowsRemoved(*(static_cast<QModelIndex *>(parent)), start, end);
   return 0;
}

QoreClass *initQTreeViewClass(QoreClass *qabstractitemview) {
   QC_QTreeView = new QoreClass("QTreeView", QDOM_GUI);
   CID_QTREEVIEW = QC_QTreeView->getID();

   QC_QTreeView->addBuiltinVirtualBaseClass(qabstractitemview);

   QC_QTreeView->setConstructor(QTREEVIEW_constructor);
   QC_QTreeView->setCopy((q_copy_t)QTREEVIEW_copy);

   QC_QTreeView->addMethod("allColumnsShowFocus",         (q_method_t)QTREEVIEW_allColumnsShowFocus);
   QC_QTreeView->addMethod("autoExpandDelay",             (q_method_t)QTREEVIEW_autoExpandDelay);
   QC_QTreeView->addMethod("columnAt",                    (q_method_t)QTREEVIEW_columnAt);
   QC_QTreeView->addMethod("columnViewportPosition",      (q_method_t)QTREEVIEW_columnViewportPosition);
   QC_QTreeView->addMethod("columnWidth",                 (q_method_t)QTREEVIEW_columnWidth);
   QC_QTreeView->addMethod("expandsOnDoubleClick",        (q_method_t)QTREEVIEW_expandsOnDoubleClick);
   QC_QTreeView->addMethod("header",                      (q_method_t)QTREEVIEW_header);
   QC_QTreeView->addMethod("indentation",                 (q_method_t)QTREEVIEW_indentation);
   QC_QTreeView->addMethod("indexAbove",                  (q_method_t)QTREEVIEW_indexAbove);
   QC_QTreeView->addMethod("indexBelow",                  (q_method_t)QTREEVIEW_indexBelow);
   QC_QTreeView->addMethod("isAnimated",                  (q_method_t)QTREEVIEW_isAnimated);
   QC_QTreeView->addMethod("isColumnHidden",              (q_method_t)QTREEVIEW_isColumnHidden);
   QC_QTreeView->addMethod("isExpanded",                  (q_method_t)QTREEVIEW_isExpanded);
   QC_QTreeView->addMethod("isFirstColumnSpanned",        (q_method_t)QTREEVIEW_isFirstColumnSpanned);
   QC_QTreeView->addMethod("isHeaderHidden",              (q_method_t)QTREEVIEW_isHeaderHidden);
   QC_QTreeView->addMethod("isRowHidden",                 (q_method_t)QTREEVIEW_isRowHidden);
   QC_QTreeView->addMethod("isSortingEnabled",            (q_method_t)QTREEVIEW_isSortingEnabled);
   QC_QTreeView->addMethod("itemsExpandable",             (q_method_t)QTREEVIEW_itemsExpandable);
   QC_QTreeView->addMethod("rootIsDecorated",             (q_method_t)QTREEVIEW_rootIsDecorated);
   QC_QTreeView->addMethod("scrollTo",                    (q_method_t)QTREEVIEW_scrollTo);
   QC_QTreeView->addMethod("setAllColumnsShowFocus",      (q_method_t)QTREEVIEW_setAllColumnsShowFocus);
   QC_QTreeView->addMethod("setAnimated",                 (q_method_t)QTREEVIEW_setAnimated);
   QC_QTreeView->addMethod("setAutoExpandDelay",          (q_method_t)QTREEVIEW_setAutoExpandDelay);
   QC_QTreeView->addMethod("setColumnHidden",             (q_method_t)QTREEVIEW_setColumnHidden);
   QC_QTreeView->addMethod("setColumnWidth",              (q_method_t)QTREEVIEW_setColumnWidth);
   QC_QTreeView->addMethod("setExpanded",                 (q_method_t)QTREEVIEW_setExpanded);
   QC_QTreeView->addMethod("setExpandsOnDoubleClick",     (q_method_t)QTREEVIEW_setExpandsOnDoubleClick);
   QC_QTreeView->addMethod("setFirstColumnSpanned",       (q_method_t)QTREEVIEW_setFirstColumnSpanned);
   QC_QTreeView->addMethod("setHeader",                   (q_method_t)QTREEVIEW_setHeader);
   QC_QTreeView->addMethod("setHeaderHidden",             (q_method_t)QTREEVIEW_setHeaderHidden);
   QC_QTreeView->addMethod("setIndentation",              (q_method_t)QTREEVIEW_setIndentation);
   QC_QTreeView->addMethod("setItemsExpandable",          (q_method_t)QTREEVIEW_setItemsExpandable);
   QC_QTreeView->addMethod("setRootIsDecorated",          (q_method_t)QTREEVIEW_setRootIsDecorated);
   QC_QTreeView->addMethod("setRowHidden",                (q_method_t)QTREEVIEW_setRowHidden);
   QC_QTreeView->addMethod("setSortingEnabled",           (q_method_t)QTREEVIEW_setSortingEnabled);
   QC_QTreeView->addMethod("setUniformRowHeights",        (q_method_t)QTREEVIEW_setUniformRowHeights);
   QC_QTreeView->addMethod("setWordWrap",                 (q_method_t)QTREEVIEW_setWordWrap);
   QC_QTreeView->addMethod("sortByColumn",                (q_method_t)QTREEVIEW_sortByColumn);
   QC_QTreeView->addMethod("uniformRowHeights",           (q_method_t)QTREEVIEW_uniformRowHeights);
   QC_QTreeView->addMethod("visualRect",                  (q_method_t)QTREEVIEW_visualRect);
   QC_QTreeView->addMethod("wordWrap",                    (q_method_t)QTREEVIEW_wordWrap);
   QC_QTreeView->addMethod("collapse",                    (q_method_t)QTREEVIEW_collapse);
   QC_QTreeView->addMethod("collapseAll",                 (q_method_t)QTREEVIEW_collapseAll);
   QC_QTreeView->addMethod("expand",                      (q_method_t)QTREEVIEW_expand);
   QC_QTreeView->addMethod("expandAll",                   (q_method_t)QTREEVIEW_expandAll);
   QC_QTreeView->addMethod("expandToDepth",               (q_method_t)QTREEVIEW_expandToDepth);
   QC_QTreeView->addMethod("hideColumn",                  (q_method_t)QTREEVIEW_hideColumn);
   QC_QTreeView->addMethod("resizeColumnToContents",      (q_method_t)QTREEVIEW_resizeColumnToContents);
   QC_QTreeView->addMethod("showColumn",                  (q_method_t)QTREEVIEW_showColumn);

   // private methods
   QC_QTreeView->addMethod("drawBranches",                (q_method_t)QTREEVIEW_drawBranches, true);
   QC_QTreeView->addMethod("drawRow",                     (q_method_t)QTREEVIEW_drawRow, true);
   QC_QTreeView->addMethod("drawTree",                    (q_method_t)QTREEVIEW_drawTree, true);
   QC_QTreeView->addMethod("horizontalOffset",            (q_method_t)QTREEVIEW_horizontalOffset, true);
   QC_QTreeView->addMethod("indexRowSizeHint",            (q_method_t)QTREEVIEW_indexRowSizeHint, true);
   QC_QTreeView->addMethod("moveCursor",                  (q_method_t)QTREEVIEW_moveCursor, true);
   QC_QTreeView->addMethod("rowHeight",                   (q_method_t)QTREEVIEW_rowHeight, true);
   QC_QTreeView->addMethod("rowsAboutToBeRemoved",        (q_method_t)QTREEVIEW_rowsAboutToBeRemoved, true);
   QC_QTreeView->addMethod("rowsInserted",                (q_method_t)QTREEVIEW_rowsInserted, true);
   QC_QTreeView->addMethod("scrollContentsBy",            (q_method_t)QTREEVIEW_scrollContentsBy, true);
   QC_QTreeView->addMethod("setSelection",                (q_method_t)QTREEVIEW_setSelection, true);
   QC_QTreeView->addMethod("sizeHintForColumn",           (q_method_t)QTREEVIEW_sizeHintForColumn, true);
   QC_QTreeView->addMethod("verticalOffset",              (q_method_t)QTREEVIEW_verticalOffset, true);
   QC_QTreeView->addMethod("visualRegionForSelection",    (q_method_t)QTREEVIEW_visualRegionForSelection, true);
   QC_QTreeView->addMethod("columnCountChanged",          (q_method_t)QTREEVIEW_columnCountChanged, true);
   QC_QTreeView->addMethod("columnMoved",                 (q_method_t)QTREEVIEW_columnMoved, true);
   QC_QTreeView->addMethod("columnResized",               (q_method_t)QTREEVIEW_columnResized, true);
   QC_QTreeView->addMethod("rowsRemoved",                 (q_method_t)QTREEVIEW_rowsRemoved, true);

   return QC_QTreeView;
}
