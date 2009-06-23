/*
 QC_QDirModel.cc
 
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

#include "QC_QDirModel.h"

qore_classid_t CID_QDIRMODEL;
QoreClass *QC_QDirModel = 0;

//QDirModel ( const QStringList & nameFilters, QDir::Filters filters, QDir::SortFlags sort, QObject * parent = 0 )
//QDirModel ( QObject * parent = 0 )
static void QDIRMODEL_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QDIRMODEL, new QoreQDirModel(self));
      return;
   }
   if (p->getType() == NT_OBJECT) {
      QoreAbstractQObject *parent = (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink);
      if (*xsink)
         return;
      ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
      self->setPrivate(CID_QDIRMODEL, new QoreQDirModel(self, parent ? parent->getQObject() : 0));
      return;
   }
   
   if (p->getType() != NT_LIST) {
      xsink->raiseException("QDIRMODEL-CONSTRUCTOR-ERROR", "unexpected type passed to QDirModel::constructor(): %n", p->getTypeName());
      return;
   }
   QStringList nameFilters;
   ConstListIterator li_nameFilters(reinterpret_cast<const QoreListNode *>(p));
   while (li_nameFilters.next()) {
      QoreStringNodeValueHelper str(li_nameFilters.getValue());
      QString tmp;
      if (get_qstring(*str, tmp, xsink))
         return;
      nameFilters.push_back(tmp);
   }
   p = get_param(params, 1);
   QDir::Filters filters = (QDir::Filters)(p ? p->getAsInt() : 0);
   p = get_param(params, 2);
   QDir::SortFlags sort = (QDir::SortFlags)(p ? p->getAsInt() : 0);
   p = get_param(params, 3);
   QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QDIRMODEL, new QoreQDirModel(self, nameFilters, filters, sort, parent ? parent->getQObject() : 0));
   return;
}

static void QDIRMODEL_copy(QoreObject *self, QoreObject *old, QoreQDirModel *qdm, ExceptionSink *xsink) {
   xsink->raiseException("QDIRMODEL-COPY-ERROR", "objects of this class cannot be copied");
}

//virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const
static AbstractQoreNode *QDIRMODEL_columnCount(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return new QoreBigIntNode(qdm->qobj->QDirModel::columnCount(*(static_cast<QModelIndex *>(parent))));
}

//virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const
static AbstractQoreNode *QDIRMODEL_data(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-DATA-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::data()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   p = get_param(params, 1);
   int role = !is_nothing(p) ? p->getAsInt() : Qt::DisplayRole;
   return return_qvariant(qdm->qobj->QDirModel::data(*(static_cast<QModelIndex *>(index)), role));
}

//virtual bool dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent )
static AbstractQoreNode *QDIRMODEL_dropMimeData(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQMimeData *data = (p && p->getType() == NT_OBJECT) ? (QoreQMimeData *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMIMEDATA, xsink) : 0;
   if (!data) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-DROPMIMEDATA-PARAM-ERROR", "expecting a QMimeData object as first argument to QDirModel::dropMimeData()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> dataHolder(static_cast<AbstractPrivateData *>(data), xsink);
   p = get_param(params, 1);
   Qt::DropAction action = (Qt::DropAction)(p ? p->getAsInt() : 0);
   p = get_param(params, 2);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 3);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 4);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-DROPMIMEDATA-PARAM-ERROR", "expecting a QModelIndex object as fifth argument to QDirModel::dropMimeData()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return get_bool_node(qdm->qobj->QDirModel::dropMimeData(static_cast<QMimeData *>(data->qobj), action, row, column, *(static_cast<QModelIndex *>(parent))));
}

//QIcon fileIcon ( const QModelIndex & index ) const
static AbstractQoreNode *QDIRMODEL_fileIcon(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-FILEICON-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::fileIcon()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return return_object(QC_QIcon, new QoreQIcon(qdm->qobj->fileIcon(*(static_cast<QModelIndex *>(index)))));
}

//QFileInfo fileInfo ( const QModelIndex & index ) const
static AbstractQoreNode *QDIRMODEL_fileInfo(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-FILEINFO-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::fileInfo()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return return_object(QC_QFileInfo, new QoreQFileInfo(qdm->qobj->fileInfo(*(static_cast<QModelIndex *>(index)))));
}

//QString fileName ( const QModelIndex & index ) const
static AbstractQoreNode *QDIRMODEL_fileName(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-FILENAME-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::fileName()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return new QoreStringNode(qdm->qobj->fileName(*(static_cast<QModelIndex *>(index))).toUtf8().data(), QCS_UTF8);
}

//QString filePath ( const QModelIndex & index ) const
static AbstractQoreNode *QDIRMODEL_filePath(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-FILEPATH-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::filePath()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return new QoreStringNode(qdm->qobj->filePath(*(static_cast<QModelIndex *>(index))).toUtf8().data(), QCS_UTF8);
}

//QDir::Filters filter () const
static AbstractQoreNode *QDIRMODEL_filter(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qdm->qobj->filter());
}

//virtual Qt::ItemFlags flags ( const QModelIndex & index ) const
static AbstractQoreNode *QDIRMODEL_flags(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-FLAGS-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::flags()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return new QoreBigIntNode(qdm->qobj->QDirModel::flags(*(static_cast<QModelIndex *>(index))));
}

//virtual bool hasChildren ( const QModelIndex & parent = QModelIndex() ) const
static AbstractQoreNode *QDIRMODEL_hasChildren(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return get_bool_node(qdm->qobj->QDirModel::hasChildren(*(static_cast<QModelIndex *>(parent))));
}

//virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const
static AbstractQoreNode *QDIRMODEL_headerData(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int section = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   Qt::Orientation orientation = (Qt::Orientation)(p ? p->getAsInt() : 0);
   p = get_param(params, 2);
   int role = !is_nothing(p) ? p->getAsInt() : Qt::DisplayRole;
   return return_qvariant(qdm->qobj->QDirModel::headerData(section, orientation, role));
}

//QFileIconProvider * iconProvider () const
static AbstractQoreNode *QDIRMODEL_iconProvider(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QFileIconProvider, new QoreQtQFileIconProvider(qdm->qobj->QDirModel::iconProvider()));
}

//virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const
//QModelIndex index ( const QString & path, int column = 0 ) const
static AbstractQoreNode *QDIRMODEL_index(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_STRING) {
      QString path;
      if (get_qstring(p, path, xsink))
         return 0;
      p = get_param(params, 1);
      int column = !is_nothing(p) ? p->getAsInt() : 0;
      return return_object(QC_QModelIndex, new QoreQModelIndex(qdm->qobj->QDirModel::index(path, column)));
   }
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qdm->qobj->QDirModel::index(row, column, *(static_cast<QModelIndex *>(parent)))));
}

//bool isDir ( const QModelIndex & index ) const
static AbstractQoreNode *QDIRMODEL_isDir(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-ISDIR-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::isDir()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return get_bool_node(qdm->qobj->isDir(*(static_cast<QModelIndex *>(index))));
}

//bool isReadOnly () const
static AbstractQoreNode *QDIRMODEL_isReadOnly(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qdm->qobj->isReadOnly());
}

//bool lazyChildCount () const
static AbstractQoreNode *QDIRMODEL_lazyChildCount(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qdm->qobj->lazyChildCount());
}

//virtual QMimeData * mimeData ( const QModelIndexList & indexes ) const
static AbstractQoreNode *QDIRMODEL_mimeData(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QModelIndexList indexes;
   if (get_qmodelindexlist(p, indexes, xsink))
      return 0;
   QMimeData *qt_qobj = qdm->qobj->QDirModel::mimeData(indexes);
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

//virtual QStringList mimeTypes () const
static AbstractQoreNode *QDIRMODEL_mimeTypes(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qstringlist(qdm->qobj->QDirModel::mimeTypes());
}

//QModelIndex mkdir ( const QModelIndex & parent, const QString & name )
static AbstractQoreNode *QDIRMODEL_mkdir(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-MKDIR-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::mkdir()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   p = get_param(params, 1);
   QString name;
   if (get_qstring(p, name, xsink))
      return 0;
   return return_object(QC_QModelIndex, new QoreQModelIndex(qdm->qobj->mkdir(*(static_cast<QModelIndex *>(parent)), name)));
}

//QStringList nameFilters () const
static AbstractQoreNode *QDIRMODEL_nameFilters(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qstringlist(qdm->qobj->nameFilters());
}

//virtual QModelIndex parent ( const QModelIndex & child ) const
static AbstractQoreNode *QDIRMODEL_parent(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *child = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!child) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-PARENT-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::parent()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> childHolder(static_cast<AbstractPrivateData *>(child), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qdm->qobj->QDirModel::parent(*(static_cast<QModelIndex *>(child)))));
}

//bool remove ( const QModelIndex & index )
static AbstractQoreNode *QDIRMODEL_remove(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-REMOVE-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::remove()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return get_bool_node(qdm->qobj->remove(*(static_cast<QModelIndex *>(index))));
}

//bool resolveSymlinks () const
static AbstractQoreNode *QDIRMODEL_resolveSymlinks(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qdm->qobj->resolveSymlinks());
}

//bool rmdir ( const QModelIndex & index )
static AbstractQoreNode *QDIRMODEL_rmdir(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-RMDIR-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::rmdir()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return get_bool_node(qdm->qobj->rmdir(*(static_cast<QModelIndex *>(index))));
}

//virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const
static AbstractQoreNode *QDIRMODEL_rowCount(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return new QoreBigIntNode(qdm->qobj->QDirModel::rowCount(*(static_cast<QModelIndex *>(parent))));
}

//virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole )
static AbstractQoreNode *QDIRMODEL_setData(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-SETDATA-PARAM-ERROR", "expecting a QModelIndex object as first argument to QDirModel::setData()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   p = get_param(params, 1);
   QVariant value;
   if (get_qvariant(p, value, xsink))
      return 0;
   p = get_param(params, 2);
   int role = !is_nothing(p) ? p->getAsInt() : Qt::EditRole;
   return get_bool_node(qdm->qobj->QDirModel::setData(*(static_cast<QModelIndex *>(index)), value, role));
}

//void setFilter ( QDir::Filters filters )
static AbstractQoreNode *QDIRMODEL_setFilter(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QDir::Filters filters = (QDir::Filters)(p ? p->getAsInt() : 0);
   qdm->qobj->setFilter(filters);
   return 0;
}

//void setIconProvider ( QFileIconProvider * provider )
static AbstractQoreNode *QDIRMODEL_setIconProvider(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreAbstractQFileIconProvider *provider = (p && p->getType() == NT_OBJECT) ? (QoreQFileIconProvider *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QFILEICONPROVIDER, xsink) : 0;
   if (!provider) {
      if (!xsink->isException())
         xsink->raiseException("QDIRMODEL-SETICONPROVIDER-PARAM-ERROR", "expecting a QFileIconProvider object as first argument to QDirModel::setIconProvider()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> providerHolder(static_cast<AbstractPrivateData *>(provider), xsink);
   qdm->qobj->QDirModel::setIconProvider(static_cast<QFileIconProvider *>(provider->getQFileIconProvider()));
   return 0;
}

//void setLazyChildCount ( bool enable )
static AbstractQoreNode *QDIRMODEL_setLazyChildCount(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qdm->qobj->setLazyChildCount(enable);
   return 0;
}

//void setNameFilters ( const QStringList & filters )
static AbstractQoreNode *QDIRMODEL_setNameFilters(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);

   if (!p || p->getType() != NT_LIST) {
      xsink->raiseException("QDIRMODEL-SETNAMEFILTERS-ERROR", "expecting a list of strings passed to QDirModel::setNameFilters()");
      return 0;
   }
   QStringList filters;
   ConstListIterator li_filters(reinterpret_cast<const QoreListNode *>(p));
   while (li_filters.next()) {
      QoreStringNodeValueHelper str(li_filters.getValue());
      QString tmp;
      if (get_qstring(*str, tmp, xsink))
         return 0;
      filters.push_back(tmp);
   }
   qdm->qobj->setNameFilters(filters);
   return 0;
}

//void setReadOnly ( bool enable )
static AbstractQoreNode *QDIRMODEL_setReadOnly(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qdm->qobj->setReadOnly(enable);
   return 0;
}

//void setResolveSymlinks ( bool enable )
static AbstractQoreNode *QDIRMODEL_setResolveSymlinks(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qdm->qobj->setResolveSymlinks(enable);
   return 0;
}

//void setSorting ( QDir::SortFlags sort )
static AbstractQoreNode *QDIRMODEL_setSorting(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QDir::SortFlags sort = (QDir::SortFlags)(p ? p->getAsInt() : 0);
   qdm->qobj->setSorting(sort);
   return 0;
}

//virtual void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder )
static AbstractQoreNode *QDIRMODEL_sort(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   Qt::SortOrder order = !is_nothing(p) ? (Qt::SortOrder)p->getAsInt() : Qt::AscendingOrder;
   qdm->qobj->QDirModel::sort(column, order);
   return 0;
}

//QDir::SortFlags sorting () const
static AbstractQoreNode *QDIRMODEL_sorting(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qdm->qobj->sorting());
}

//virtual Qt::DropActions supportedDropActions () const
static AbstractQoreNode *QDIRMODEL_supportedDropActions(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qdm->qobj->QDirModel::supportedDropActions());
}

//void refresh ( const QModelIndex & parent = QModelIndex() )
static AbstractQoreNode *QDIRMODEL_refresh(QoreObject *self, QoreQDirModel *qdm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (*xsink)
      return 0;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   qdm->qobj->refresh(*(static_cast<QModelIndex *>(parent)));
   return 0;
}

static QoreClass *initQDirModelClass(QoreClass *qabstractitemmodel) {
   QC_QDirModel = new QoreClass("QDirModel", QDOM_GUI);
   CID_QDIRMODEL = QC_QDirModel->getID();

   QC_QDirModel->addBuiltinVirtualBaseClass(qabstractitemmodel);

   QC_QDirModel->setConstructor(QDIRMODEL_constructor);
   QC_QDirModel->setCopy((q_copy_t)QDIRMODEL_copy);

   QC_QDirModel->addMethod("columnCount",                 (q_method_t)QDIRMODEL_columnCount);
   QC_QDirModel->addMethod("data",                        (q_method_t)QDIRMODEL_data);
   QC_QDirModel->addMethod("dropMimeData",                (q_method_t)QDIRMODEL_dropMimeData);
   QC_QDirModel->addMethod("fileIcon",                    (q_method_t)QDIRMODEL_fileIcon);
   QC_QDirModel->addMethod("fileInfo",                    (q_method_t)QDIRMODEL_fileInfo);
   QC_QDirModel->addMethod("fileName",                    (q_method_t)QDIRMODEL_fileName);
   QC_QDirModel->addMethod("filePath",                    (q_method_t)QDIRMODEL_filePath);
   QC_QDirModel->addMethod("filter",                      (q_method_t)QDIRMODEL_filter);
   QC_QDirModel->addMethod("flags",                       (q_method_t)QDIRMODEL_flags);
   QC_QDirModel->addMethod("hasChildren",                 (q_method_t)QDIRMODEL_hasChildren);
   QC_QDirModel->addMethod("headerData",                  (q_method_t)QDIRMODEL_headerData);
   QC_QDirModel->addMethod("iconProvider",                (q_method_t)QDIRMODEL_iconProvider);
   QC_QDirModel->addMethod("index",                       (q_method_t)QDIRMODEL_index);
   QC_QDirModel->addMethod("isDir",                       (q_method_t)QDIRMODEL_isDir);
   QC_QDirModel->addMethod("isReadOnly",                  (q_method_t)QDIRMODEL_isReadOnly);
   QC_QDirModel->addMethod("lazyChildCount",              (q_method_t)QDIRMODEL_lazyChildCount);
   QC_QDirModel->addMethod("mimeData",                    (q_method_t)QDIRMODEL_mimeData);
   QC_QDirModel->addMethod("mimeTypes",                   (q_method_t)QDIRMODEL_mimeTypes);
   QC_QDirModel->addMethod("mkdir",                       (q_method_t)QDIRMODEL_mkdir);
   QC_QDirModel->addMethod("nameFilters",                 (q_method_t)QDIRMODEL_nameFilters);
   QC_QDirModel->addMethod("parent",                      (q_method_t)QDIRMODEL_parent);
   QC_QDirModel->addMethod("remove",                      (q_method_t)QDIRMODEL_remove);
   QC_QDirModel->addMethod("resolveSymlinks",             (q_method_t)QDIRMODEL_resolveSymlinks);
   QC_QDirModel->addMethod("rmdir",                       (q_method_t)QDIRMODEL_rmdir);
   QC_QDirModel->addMethod("rowCount",                    (q_method_t)QDIRMODEL_rowCount);
   QC_QDirModel->addMethod("setData",                     (q_method_t)QDIRMODEL_setData);
   QC_QDirModel->addMethod("setFilter",                   (q_method_t)QDIRMODEL_setFilter);
   QC_QDirModel->addMethod("setIconProvider",             (q_method_t)QDIRMODEL_setIconProvider);
   QC_QDirModel->addMethod("setLazyChildCount",           (q_method_t)QDIRMODEL_setLazyChildCount);
   QC_QDirModel->addMethod("setNameFilters",              (q_method_t)QDIRMODEL_setNameFilters);
   QC_QDirModel->addMethod("setReadOnly",                 (q_method_t)QDIRMODEL_setReadOnly);
   QC_QDirModel->addMethod("setResolveSymlinks",          (q_method_t)QDIRMODEL_setResolveSymlinks);
   QC_QDirModel->addMethod("setSorting",                  (q_method_t)QDIRMODEL_setSorting);
   QC_QDirModel->addMethod("sort",                        (q_method_t)QDIRMODEL_sort);
   QC_QDirModel->addMethod("sorting",                     (q_method_t)QDIRMODEL_sorting);
   QC_QDirModel->addMethod("supportedDropActions",        (q_method_t)QDIRMODEL_supportedDropActions);
   QC_QDirModel->addMethod("refresh",                     (q_method_t)QDIRMODEL_refresh);

   return QC_QDirModel;
}

QoreNamespace *initQDirModelNS(QoreClass *qabstractitemmodel) {
   QoreNamespace *ns = new QoreNamespace("QDirModel");
   ns->addSystemClass(initQDirModelClass(QC_QAbstractItemModel));

   return ns;
}
