/*
 QC_QTreeView.h
 
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

#ifndef _QORE_QT_QC_QTREEVIEW_H

#define _QORE_QT_QC_QTREEVIEW_H

#include <QTreeView>
#include "QoreAbstractQTreeView.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QTREEVIEW;
DLLEXPORT extern QoreClass *QC_QTreeView;
DLLEXPORT QoreClass *initQTreeViewClass(QoreClass *);

   class myQTreeView : public QTreeView, public QoreQTreeViewExtension {
#define QOREQTYPE QTreeView
#define MYQOREQTYPE myQTreeView
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

      DLLLOCAL virtual void scrollTo ( const QModelIndex & index, ScrollHint hint = EnsureVisible ) {
	 if (!m_scrollTo) {
	    QTreeView::scrollTo(index, hint);
	    return;
	 }
      }

      DLLLOCAL virtual QRect visualRect ( const QModelIndex & index ) const {
	 if (!m_visualRect)
	    return QTreeView::visualRect(index);

	 return QRect();
      }

      DLLLOCAL virtual void drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const {
	 if (!m_drawBranches) {
	    QTreeView::drawBranches(painter, rect, index);
	    return;
	 }
      }
      DLLLOCAL virtual void drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	 if (!m_drawRow) {
	    QTreeView::drawRow(painter, option, index);
	    return;
	 }
      }
      DLLLOCAL virtual int horizontalOffset () const {
	 if (!m_horizontalOffset)
	    return QTreeView::horizontalOffset();

	 return 0;
      }
      DLLLOCAL virtual QModelIndex moveCursor ( QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers ) {
	 if (!m_moveCursor)
	    return QTreeView::moveCursor(cursorAction, modifiers);

	 return QModelIndex();
      }
      DLLLOCAL virtual void rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end ) {
	 if (!m_rowsAboutToBeRemoved) {
	    QTreeView::rowsAboutToBeRemoved(parent, start, end);
	    return;
	 }
      }
      DLLLOCAL virtual void rowsInserted ( const QModelIndex & parent, int start, int end ) {
	 if (!m_rowsInserted) {
	    QTreeView::rowsInserted(parent, start, end);
	    return;
	 }
      }
      DLLLOCAL virtual void scrollContentsBy ( int dx, int dy ) {
	 if (!m_scrollContentsBy) {
	    QTreeView::scrollContentsBy(dx, dy);
	    return;
	 }
      }
      DLLLOCAL virtual void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags command ) {
	 if (!m_setSelection) {
	    QTreeView::setSelection(rect, command);
	    return;
	 }
      }
      DLLLOCAL virtual int sizeHintForColumn ( int column ) const {
	 if (!m_sizeHintForColumn)
	    return QTreeView::sizeHintForColumn(column);
	 return 0;
      }
      DLLLOCAL virtual int verticalOffset () const {
	 if (!m_verticalOffset)
	    return QTreeView::verticalOffset();
	 return 0;
      }
      DLLLOCAL virtual QRegion visualRegionForSelection ( const QItemSelection & selection ) const {
	 if (!m_visualRegionForSelection)
	    return QTreeView::visualRegionForSelection(selection);
	 return QRegion();
      }

   public:
      DLLLOCAL myQTreeView(QoreObject *obj, QWidget* parent = 0) : QTreeView(parent), QoreQTreeViewExtension(obj, this) {
      }

      // access to protected methods
      DLLLOCAL virtual void parent_drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const {
	 QTreeView::drawBranches(painter, rect, index);
      }
      DLLLOCAL virtual void parent_drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	 QTreeView::drawRow(painter, option, index);
      }
      DLLLOCAL virtual void parent_drawTree ( QPainter * painter, const QRegion & region ) const {
	 QTreeView::drawTree(painter, region);
      }
      DLLLOCAL virtual int parent_horizontalOffset () const {
	 return QTreeView::horizontalOffset();
      }
      DLLLOCAL virtual int parent_indexRowSizeHint ( const QModelIndex & index ) const {
	 return QTreeView::indexRowSizeHint(index);
      }
      DLLLOCAL virtual QModelIndex parent_moveCursor ( int cursorAction, Qt::KeyboardModifiers modifiers ) {
	 return QTreeView::moveCursor((QAbstractItemView::CursorAction)cursorAction, modifiers);
      }
      DLLLOCAL virtual int parent_rowHeight ( const QModelIndex & index ) const {
	 return QTreeView::rowHeight(index);
      }
      DLLLOCAL virtual void parent_rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end ) {
	 QTreeView::rowsAboutToBeRemoved(parent, start, end);
      }
      DLLLOCAL virtual void parent_rowsInserted ( const QModelIndex & parent, int start, int end ) {
	 QTreeView::rowsInserted(parent, start, end);
      }
      DLLLOCAL virtual void parent_scrollContentsBy ( int dx, int dy ) {
	 QTreeView::scrollContentsBy(dx, dy);
      }
      DLLLOCAL virtual void parent_setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags command ) {
	 QTreeView::setSelection(rect, command);
      }
      DLLLOCAL virtual int parent_sizeHintForColumn ( int column ) const {
	 return QTreeView::sizeHintForColumn(column);
      }
      DLLLOCAL virtual int parent_verticalOffset () const {
	 return QTreeView::verticalOffset();
      }
      DLLLOCAL virtual QRegion parent_visualRegionForSelection ( const QItemSelection & selection ) const {
	 return QTreeView::visualRegionForSelection(selection);
      }
      DLLLOCAL virtual void parent_columnCountChanged ( int oldCount, int newCount ) {
	 QTreeView::columnCountChanged(oldCount, newCount);
      }
      DLLLOCAL virtual void parent_columnMoved () {
	 QTreeView::columnMoved();
      }
      DLLLOCAL virtual void parent_columnResized ( int column, int oldSize, int newSize ) {
	 QTreeView::columnResized(column, oldSize, newSize);
      }
      DLLLOCAL virtual void parent_rowsRemoved ( const QModelIndex & parent, int start, int end ) {
	 QTreeView::rowsRemoved(parent, start, end);
      }

      DLLLOCAL void pub_setupViewport(QWidget *w) {
         setupViewport(w);
      }

};

typedef QoreQTreeViewBase<myQTreeView, QoreAbstractQTreeView> QoreQTreeViewImpl;

class QoreQTreeView : public QoreQTreeViewImpl {
   public:
      DLLLOCAL QoreQTreeView(QoreObject *obj, QWidget* parent = 0) : QoreQTreeViewImpl(new myQTreeView(obj, parent)) { }
};

typedef QoreQtQTreeViewBase<QTreeView, QoreAbstractQTreeView> QoreQtQTreeViewImpl;

class QoreQtQTreeView : public QoreQtQTreeViewImpl {
   public:
      DLLLOCAL QoreQtQTreeView(QoreObject *obj, QTreeView *qtreeview) : QoreQtQTreeViewImpl(obj, qtreeview) { }
};

#endif // _QORE_QT_QC_QTREEVIEW_H
