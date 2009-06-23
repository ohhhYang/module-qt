/*
 QoreAbstractQAbstractItemModel.h
 
 Qore Programming Language
 
 Copyright 2003 - 2009 David Nichols
 
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

#ifndef _QORE_QOREABSTRACTQABSTRACTITEMMODEL_H

#define _QORE_QOREABSTRACTQABSTRACTITEMMODEL_H

#include "QoreAbstractQObject.h"

#include "QC_QModelIndex.h"
#include "QC_QMimeData.h"

#include <set>

typedef std::set<AbstractQoreNode *> node_set_t;

extern qore_classid_t CID_QWIDGET;

class QoreAbstractQAbstractItemModel : public QoreAbstractQObject {
   public:
      virtual QModelIndex qoreCreateIndex(int row, int column, const AbstractQoreNode *data) const = 0;
      virtual bool isQoreData(const AbstractQoreNode *data) = 0;

      virtual QAbstractItemModel *getQAbstractItemModel() const = 0;

      // protected methods
      virtual void beginInsertColumns ( const QModelIndex & parent, int first, int last ) = 0;
      virtual void beginInsertRows ( const QModelIndex & parent, int first, int last ) = 0;
      virtual void beginRemoveColumns ( const QModelIndex & parent, int first, int last ) = 0;
      virtual void beginRemoveRows ( const QModelIndex & parent, int first, int last )  = 0;
      virtual void changePersistentIndex ( const QModelIndex & from, const QModelIndex & to ) = 0; 
      virtual void changePersistentIndexList ( const QModelIndexList & from, const QModelIndexList & to ) = 0; 
      virtual QModelIndex createIndex ( int row, int column, void *ptr = 0 ) const = 0;
      virtual QModelIndex createIndex ( int row, int column, quint32 id ) const = 0;
      virtual void endInsertColumns () = 0;
      virtual void endInsertRows () = 0;
      virtual void endRemoveColumns () = 0;
      virtual void endRemoveRows () = 0;
      virtual QModelIndexList persistentIndexList () const = 0;
      virtual void reset () = 0;
};

template<typename T, typename V>
class QoreQAbstractItemModelBase : public QoreQObjectBase<T, V> {
   public:
      DLLLOCAL QoreQAbstractItemModelBase(T *qo) : QoreQObjectBase<T, V>(qo) {
      }
      DLLLOCAL virtual QAbstractItemModel *getQAbstractItemModel() const {
	 return &(*this->qobj);
      }

      DLLLOCAL virtual QModelIndex qoreCreateIndex(int row, int column, const AbstractQoreNode *data) const {
	 return this->qobj->qoreCreateIndex(row, column, data);
      }
      DLLLOCAL virtual bool isQoreData(const AbstractQoreNode *data) {
	 return this->qobj->isQoreData(data);
      }

      // protected methods
      DLLLOCAL virtual void beginInsertColumns ( const QModelIndex & parent, int first, int last ) {
	 this->qobj->parent_beginInsertColumns(parent, first, last);
      }
      DLLLOCAL virtual void beginInsertRows ( const QModelIndex & parent, int first, int last ) {
	 this->qobj->parent_beginInsertRows(parent, first, last);
      }
      DLLLOCAL virtual void beginRemoveColumns ( const QModelIndex & parent, int first, int last ) {
	 this->qobj->parent_beginRemoveColumns(parent, first, last);
      }
      DLLLOCAL virtual void beginRemoveRows ( const QModelIndex & parent, int first, int last )  {
	 this->qobj->parent_beginRemoveRows(parent, first, last);
      }
      DLLLOCAL virtual void changePersistentIndex ( const QModelIndex & from, const QModelIndex & to ) {
	 this->qobj->parent_changePersistentIndex(from, to);
      }
      DLLLOCAL virtual void changePersistentIndexList ( const QModelIndexList & from, const QModelIndexList & to ) {
	 this->qobj->parent_changePersistentIndexList(from, to);
      }
      DLLLOCAL virtual QModelIndex createIndex ( int row, int column, void * ptr = 0 ) const { 
	 return this->qobj->parent_createIndex(row, column, ptr);
      }
      DLLLOCAL virtual QModelIndex createIndex ( int row, int column, quint32 id ) const {
	 return this->qobj->parent_createIndex(row, column, id);
      }
      DLLLOCAL virtual void endInsertColumns () {
	 this->qobj->parent_endInsertColumns();
      }
      DLLLOCAL virtual void endInsertRows () {
	 this->qobj->parent_endInsertRows();
      }
      DLLLOCAL virtual void endRemoveColumns () {
	 this->qobj->parent_endRemoveColumns();
      }
      DLLLOCAL virtual void endRemoveRows () {
	 this->qobj->parent_endRemoveRows();
      }
      DLLLOCAL virtual QModelIndexList persistentIndexList () const {
	 return this->qobj->parent_persistentIndexList();
      }
      DLLLOCAL virtual void reset () {
	 this->qobj->parent_reset();
      }

};

template<typename T, typename V>
class QoreQtQAbstractItemModelBase : public QoreQtQObjectBase<T, V> {
   public:
      DLLLOCAL QoreQtQAbstractItemModelBase(QoreObject *obj, T *qo) : QoreQtQObjectBase<T, V>(obj, qo) {
      }

      DLLLOCAL virtual QModelIndex qoreCreateIndex(int row, int column, const AbstractQoreNode *data) const {
	 return QModelIndex();
      }
      DLLLOCAL virtual bool isQoreData(const AbstractQoreNode *data) {
	 return false;
      }

      // protected methods
      DLLLOCAL virtual void beginInsertColumns ( const QModelIndex & parent, int first, int last ) {}
      DLLLOCAL virtual void beginInsertRows ( const QModelIndex & parent, int first, int last ) {}
      DLLLOCAL virtual void beginRemoveColumns ( const QModelIndex & parent, int first, int last ) {}
      DLLLOCAL virtual void beginRemoveRows ( const QModelIndex & parent, int first, int last )  {}
      DLLLOCAL virtual void changePersistentIndex ( const QModelIndex & from, const QModelIndex & to ) {} 
      DLLLOCAL virtual void changePersistentIndexList ( const QModelIndexList & from, const QModelIndexList & to ) {} 
      DLLLOCAL virtual QModelIndex createIndex ( int row, int column, void * ptr = 0 ) const { return QModelIndex(); }
      DLLLOCAL virtual QModelIndex createIndex ( int row, int column, quint32 id ) const { return QModelIndex(); }
      DLLLOCAL virtual void endInsertColumns () {}
      DLLLOCAL virtual void endInsertRows () {}
      DLLLOCAL virtual void endRemoveColumns () {}
      DLLLOCAL virtual void endRemoveRows () {}
      DLLLOCAL virtual QModelIndexList persistentIndexList () const { return QModelIndexList(); }
      DLLLOCAL virtual void reset () {}

      DLLLOCAL virtual QAbstractItemModel *getQAbstractItemModel() const {
         return this->qobj;
      }
};

class QoreQAbstractItemModelExtension : public QoreQObjectExtension {
   protected:
      mutable node_set_t node_set;

      const QoreMethod *m_buddy, *m_canFetchMore, *m_columnCount, *m_data, *m_dropMimeData, *m_fetchMore,
	 *m_flags, *m_hasChildren, *m_headerData, *m_index, *m_insertColumns, *m_insertRows, *m_itemData,
	 *m_match, *m_mimeData, *m_mimeTypes, *m_parent, *m_removeColumns, *m_removeRows, *m_rowCount,
	 *m_setData, *m_setHeaderData, *m_setItemData, *m_sort, *m_span, *m_supportedDropActions;

   DLLLOCAL QoreQAbstractItemModelExtension(QoreObject *obj, QObject *qo) : QoreQObjectExtension(obj, qo) {
         const QoreClass *qc = obj->getClass();

	 m_buddy                = findMethod(qc, "buddy");
	 m_canFetchMore         = findMethod(qc, "canFetchMore");
	 m_columnCount          = findMethod(qc, "columnCount");
	 m_data                 = findMethod(qc, "data");
	 m_dropMimeData         = findMethod(qc, "dropMimeData");
	 m_fetchMore            = findMethod(qc, "fetchMore");
	 m_flags                = findMethod(qc, "flags");
	 m_hasChildren          = findMethod(qc, "hasChildren");
	 m_headerData           = findMethod(qc, "headerData");
	 m_index                = findMethod(qc, "index");
	 m_insertColumns        = findMethod(qc, "insertColumns");
	 m_insertRows           = findMethod(qc, "insertRows");
	 m_itemData             = findMethod(qc, "itemData");
	 m_match                = findMethod(qc, "match");
	 m_mimeData             = findMethod(qc, "mimeData");
	 m_mimeTypes            = findMethod(qc, "mimeTypes");
	 m_parent               = findMethod(qc, "parent");
	 m_removeColumns        = findMethod(qc, "removeColumns");
	 m_removeRows           = findMethod(qc, "removeRows");
	 m_rowCount             = findMethod(qc, "rowCount");
	 m_setData              = findMethod(qc, "setData");
	 m_setHeaderData        = findMethod(qc, "setHeaderData");
	 m_setItemData          = findMethod(qc, "setItemData");
	 m_sort                 = findMethod(qc, "sort");
	 m_span                 = findMethod(qc, "span");
	 m_supportedDropActions = findMethod(qc, "supportedDropActions");
      }
};

#endif
