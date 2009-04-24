/*
 QoreAbstractQTreeView.h
 
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

#ifndef _QORE_QT_QOREABSTRACTQTREEVIEW_H

#define _QORE_QT_QOREABSTRACTQTREEVIEW_H

#include "QoreAbstractQAbstractItemView.h"

class QoreAbstractQTreeView : public QoreAbstractQAbstractItemView {
   public:
      DLLLOCAL virtual QTreeView *getQTreeView() const = 0;

      // protected methods
      virtual void drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const = 0;
      virtual void drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const = 0;
      virtual void drawTree ( QPainter * painter, const QRegion & region ) const = 0;
      virtual int horizontalOffset () const = 0;
      virtual int indexRowSizeHint ( const QModelIndex & index ) const = 0;
      virtual QModelIndex moveCursor ( int cursorAction, Qt::KeyboardModifiers modifiers ) = 0;
      virtual int rowHeight ( const QModelIndex & index ) const = 0;
      virtual void rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end ) = 0;
      virtual void rowsInserted ( const QModelIndex & parent, int start, int end ) = 0;
      virtual void scrollContentsBy ( int dx, int dy ) = 0;
      virtual void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags command ) = 0;
      virtual int sizeHintForColumn ( int column ) const = 0;
      virtual int verticalOffset () const = 0;
      virtual QRegion visualRegionForSelection ( const QItemSelection & selection ) const = 0;
      virtual void columnCountChanged ( int oldCount, int newCount ) = 0;
      virtual void columnMoved () = 0;
      virtual void columnResized ( int column, int oldSize, int newSize ) = 0;
      virtual void rowsRemoved ( const QModelIndex & parent, int start, int end ) = 0;
};

template<typename T, typename V>
class QoreQTreeViewBase : public QoreQAbstractItemViewBase<T, V> {
   public:
      DLLLOCAL QoreQTreeViewBase(T *qo) : QoreQAbstractItemViewBase<T, V>(qo) {
      }

      DLLLOCAL virtual QTreeView *getQTreeView() const {
         return static_cast<QTreeView *>(&(*this->qobj));
      }

      // protected methods
      virtual void drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const {
	 this->qobj->parent_drawBranches(painter, rect, index);
      }
      virtual void drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	 this->qobj->parent_drawRow(painter, option, index);
      }
      virtual void drawTree ( QPainter * painter, const QRegion & region ) const {
	 this->qobj->parent_drawTree(painter, region);
      }
      virtual int horizontalOffset () const {
	 return this->qobj->parent_horizontalOffset();
      }
      virtual int indexRowSizeHint ( const QModelIndex & index ) const {
	 return this->qobj->parent_indexRowSizeHint(index);
      }
      virtual QModelIndex moveCursor ( int cursorAction, Qt::KeyboardModifiers modifiers ) {
	 return this->qobj->parent_moveCursor(cursorAction, modifiers);
      }
      virtual int rowHeight ( const QModelIndex & index ) const {
	 return this->qobj->parent_rowHeight(index);
      }
      virtual void rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end ) {
	 this->qobj->parent_rowsAboutToBeRemoved(parent, start, end);
      }
      virtual void rowsInserted ( const QModelIndex & parent, int start, int end ) {
	 this->qobj->parent_rowsInserted(parent, start, end);
      }
      virtual void scrollContentsBy ( int dx, int dy ) {
	 this->qobj->parent_scrollContentsBy(dx, dy);
      }
      virtual void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags command ) {
	 this->qobj->parent_setSelection(rect, command);
      }
      virtual int sizeHintForColumn ( int column ) const {
	 return this->qobj->parent_sizeHintForColumn(column);
      }
      virtual int verticalOffset () const {
	 return this->qobj->parent_verticalOffset();
      }
      virtual QRegion visualRegionForSelection ( const QItemSelection & selection ) const {
	 return this->qobj->parent_visualRegionForSelection(selection);
      }
      virtual void columnCountChanged ( int oldCount, int newCount ) {
	 this->qobj->parent_columnCountChanged(oldCount, newCount);
      }
      virtual void columnMoved () {
	 this->qobj->parent_columnMoved();
      }
      virtual void columnResized ( int column, int oldSize, int newSize ) {
	 this->qobj->parent_columnResized(column, oldSize, newSize);
      }
      virtual void rowsRemoved ( const QModelIndex & parent, int start, int end ) {
	 this->qobj->parent_rowsRemoved(parent, start, end);
      }
};

template<typename T, typename V>
class QoreQtQTreeViewBase : public QoreQtQAbstractItemViewBase<T, V> {
   public:
      DLLLOCAL QoreQtQTreeViewBase(QoreObject *obj, T *qo) : QoreQtQAbstractItemViewBase<T, V>(obj, qo) {
      }

      DLLLOCAL virtual QTreeView *getQTreeView() const {
         return this->qobj;
      }

      // protected methods
      virtual void drawBranches ( QPainter * painter, const QRect & rect, const QModelIndex & index ) const {
      }
      virtual void drawRow ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
      }
      virtual void drawTree ( QPainter * painter, const QRegion & region ) const {
      }
      virtual int horizontalOffset () const {
	 return 0;
      }
      virtual int indexRowSizeHint ( const QModelIndex & index ) const {
	 return 0;
      }
      virtual QModelIndex moveCursor ( int cursorAction, Qt::KeyboardModifiers modifiers ) {
	 return QModelIndex();
      }
      virtual int rowHeight ( const QModelIndex & index ) const {
	 return 0;
      }
      virtual void rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end ) {
      }
      virtual void rowsInserted ( const QModelIndex & parent, int start, int end ) {
      }
      virtual void scrollContentsBy ( int dx, int dy ) {
      }
      virtual void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags command ) {
      }
      virtual int sizeHintForColumn ( int column ) const {
	 return 0;
      }
      virtual int verticalOffset () const {
	 return 0;
      }
      virtual QRegion visualRegionForSelection ( const QItemSelection & selection ) const {
	 return QRegion();
      }
      virtual void columnCountChanged ( int oldCount, int newCount ) {
      }
      virtual void columnMoved () {
      }
      virtual void columnResized ( int column, int oldSize, int newSize ) {
      }
      virtual void rowsRemoved ( const QModelIndex & parent, int start, int end ) {
      }
};

class QoreQTreeViewExtension : public QoreQWidgetExtension {
   protected:
      const QoreMethod *m_scrollTo, 
	 *m_visualRect,
	 *m_drawBranches,
	 *m_drawRow,
	 *m_horizontalOffset,
	 *m_moveCursor,
	 *m_rowsAboutToBeRemoved,
	 *m_rowsInserted,
	 *m_scrollContentsBy,
	 *m_setSelection,
	 *m_sizeHintForColumn,
	 *m_verticalOffset,
	 *m_visualRegionForSelection;

   public:
      DLLLOCAL QoreQTreeViewExtension(QoreObject *obj, QObject *qo) : QoreQWidgetExtension(obj, qo) {
         const QoreClass *qc = obj->getClass();
	 
	 m_scrollTo                 = findMethod(qc, "scrollTo");
	 m_visualRect               = findMethod(qc, "visualRect");
	 m_drawBranches             = findMethod(qc, "drawBranches");
	 m_drawRow                  = findMethod(qc, "drawRow");
	 m_horizontalOffset         = findMethod(qc, "horizontalOffset");
	 m_moveCursor               = findMethod(qc, "moveCursor");
	 m_rowsAboutToBeRemoved     = findMethod(qc, "rowsAboutToBeRemoved");
	 m_rowsInserted             = findMethod(qc, "rowsInserted");
	 m_scrollContentsBy         = findMethod(qc, "scrollContentsBy");
	 m_setSelection             = findMethod(qc, "setSelection");
	 m_sizeHintForColumn        = findMethod(qc, "sizeHintForColumn");
	 m_verticalOffset           = findMethod(qc, "verticalOffset");
	 m_visualRegionForSelection = findMethod(qc, "visualRegionForSelection");	 
      }
};

#endif  // _QORE_QT_QOREABSTRACTQTREEVIEW_H
