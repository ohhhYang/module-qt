/*
 QC_QSortFilterProxyModel.cc
 
 Qore Programming Language

 Copyright (C) 2003 - 2009 Qore Technologies

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

#include "QC_QSortFilterProxyModel.h"

qore_classid_t CID_QSORTFILTERPROXYMODEL;
QoreClass *QC_QSortFilterProxyModel = 0;

//QSortFilterProxyModel ( QObject * parent = 0 )
static void QSORTFILTERPROXYMODEL_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QSORTFILTERPROXYMODEL, new QoreQSortFilterProxyModel(self, parent ? parent->getQObject() : 0));
   return;
}

static void QSORTFILTERPROXYMODEL_copy(QoreObject *self, QoreObject *old, QoreQSortFilterProxyModel *qsfpm, ExceptionSink *xsink) {
   xsink->raiseException("QSORTFILTERPROXYMODEL-COPY-ERROR", "objects of this class cannot be copied");
}

//bool dynamicSortFilter () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_dynamicSortFilter(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qsfpm->getQSortFilterProxyModel()->dynamicSortFilter());
}

//Qt::CaseSensitivity filterCaseSensitivity () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_filterCaseSensitivity(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qsfpm->getQSortFilterProxyModel()->filterCaseSensitivity());
}

//int filterKeyColumn () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_filterKeyColumn(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qsfpm->getQSortFilterProxyModel()->filterKeyColumn());
}

//QRegExp filterRegExp () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_filterRegExp(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QRegExp, new QoreQRegExp(qsfpm->getQSortFilterProxyModel()->filterRegExp()));
}

//int filterRole () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_filterRole(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qsfpm->getQSortFilterProxyModel()->filterRole());
}

//bool isSortLocaleAware () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_isSortLocaleAware(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qsfpm->getQSortFilterProxyModel()->isSortLocaleAware());
}

//virtual QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_mapFromSource(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *sourceIndex = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!sourceIndex) {
      if (!xsink->isException())
         xsink->raiseException("QSORTFILTERPROXYMODEL-MAPFROMSOURCE-PARAM-ERROR", "expecting a QModelIndex object as first argument to QSortFilterProxyModel::mapFromSource()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> sourceIndexHolder(static_cast<AbstractPrivateData *>(sourceIndex), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qsfpm->getQSortFilterProxyModel()->mapFromSource(*(static_cast<QModelIndex *>(sourceIndex)))));
}

//virtual QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_mapToSource(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *proxyIndex = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!proxyIndex) {
      if (!xsink->isException())
         xsink->raiseException("QSORTFILTERPROXYMODEL-MAPTOSOURCE-PARAM-ERROR", "expecting a QModelIndex object as first argument to QSortFilterProxyModel::mapToSource()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> proxyIndexHolder(static_cast<AbstractPrivateData *>(proxyIndex), xsink);
   return return_object(QC_QModelIndex, new QoreQModelIndex(qsfpm->getQSortFilterProxyModel()->mapToSource(*(static_cast<QModelIndex *>(proxyIndex)))));
}

//void setDynamicSortFilter ( bool enable )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setDynamicSortFilter(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool enable = p ? p->getAsBool() : false;
   qsfpm->getQSortFilterProxyModel()->setDynamicSortFilter(enable);
   return 0;
}

//void setFilterCaseSensitivity ( Qt::CaseSensitivity cs )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setFilterCaseSensitivity(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::CaseSensitivity cs = (Qt::CaseSensitivity)(p ? p->getAsInt() : 0);
   qsfpm->getQSortFilterProxyModel()->setFilterCaseSensitivity(cs);
   return 0;
}

//void setFilterKeyColumn ( int column )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setFilterKeyColumn(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   qsfpm->getQSortFilterProxyModel()->setFilterKeyColumn(column);
   return 0;
}

//void setFilterRegExp ( const QRegExp & regExp )
//void setFilterRegExp ( const QString & pattern )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setFilterRegExp(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQRegExp *regExp = (QoreQRegExp *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QREGEXP, xsink);
      if (!regExp) {
         if (!xsink->isException())
            xsink->raiseException("QSORTFILTERPROXYMODEL-SETFILTERREGEXP-PARAM-ERROR", "QSortFilterProxyModel::setFilterRegExp() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
         return 0;
      }
      ReferenceHolder<AbstractPrivateData> regExpHolder(static_cast<AbstractPrivateData *>(regExp), xsink);
      qsfpm->getQSortFilterProxyModel()->setFilterRegExp(*(static_cast<QRegExp *>(regExp)));
      return 0;
   }
   QString pattern;
   if (get_qstring(p, pattern, xsink))
      return 0;
   qsfpm->getQSortFilterProxyModel()->setFilterRegExp(pattern);
   return 0;
}

//void setFilterRole ( int role )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setFilterRole(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int role = p ? p->getAsInt() : 0;
   qsfpm->getQSortFilterProxyModel()->setFilterRole(role);
   return 0;
}

//void setSortCaseSensitivity ( Qt::CaseSensitivity cs )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setSortCaseSensitivity(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   Qt::CaseSensitivity cs = (Qt::CaseSensitivity)(p ? p->getAsInt() : 0);
   qsfpm->getQSortFilterProxyModel()->setSortCaseSensitivity(cs);
   return 0;
}

//void setSortLocaleAware ( bool on )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setSortLocaleAware(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   bool on = p ? p->getAsBool() : false;
   qsfpm->getQSortFilterProxyModel()->setSortLocaleAware(on);
   return 0;
}

//void setSortRole ( int role )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setSortRole(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int role = p ? p->getAsInt() : 0;
   qsfpm->getQSortFilterProxyModel()->setSortRole(role);
   return 0;
}

//Qt::CaseSensitivity sortCaseSensitivity () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_sortCaseSensitivity(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qsfpm->getQSortFilterProxyModel()->sortCaseSensitivity());
}

//int sortColumn () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_sortColumn(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qsfpm->getQSortFilterProxyModel()->sortColumn());
}

//Qt::SortOrder sortOrder () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_sortOrder(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qsfpm->getQSortFilterProxyModel()->sortOrder());
}

//int sortRole () const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_sortRole(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(qsfpm->getQSortFilterProxyModel()->sortRole());
}

//void invalidate ()
static AbstractQoreNode *QSORTFILTERPROXYMODEL_invalidate(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   qsfpm->getQSortFilterProxyModel()->invalidate();
   return 0;
}

//void setFilterFixedString ( const QString & pattern )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setFilterFixedString(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString pattern;
   if (get_qstring(p, pattern, xsink))
      return 0;
   qsfpm->getQSortFilterProxyModel()->setFilterFixedString(pattern);
   return 0;
}

//void setFilterWildcard ( const QString & pattern )
static AbstractQoreNode *QSORTFILTERPROXYMODEL_setFilterWildcard(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString pattern;
   if (get_qstring(p, pattern, xsink))
      return 0;
   qsfpm->getQSortFilterProxyModel()->setFilterWildcard(pattern);
   return 0;
}

//virtual bool filterAcceptsColumn ( int source_column, const QModelIndex & source_parent ) const
/*static AbstractQoreNode *QSORTFILTERPROXYMODEL_filterAcceptsColumn(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int source_column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *source_parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!source_parent) {
      if (!xsink->isException())
         xsink->raiseException("QSORTFILTERPROXYMODEL-FILTERACCEPTSCOLUMN-PARAM-ERROR", "expecting a QModelIndex object as second argument to QSortFilterProxyModel::filterAcceptsColumn()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> source_parentHolder(static_cast<AbstractPrivateData *>(source_parent), xsink);
   return get_bool_node(qsfpm->getQSortFilterProxyModel()->filterAcceptsColumn(source_column, *(static_cast<QModelIndex *>(source_parent))));
}


//virtual bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_filterAcceptsRow(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int source_row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *source_parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!source_parent) {
      if (!xsink->isException())
         xsink->raiseException("QSORTFILTERPROXYMODEL-FILTERACCEPTSROW-PARAM-ERROR", "expecting a QModelIndex object as second argument to QSortFilterProxyModel::filterAcceptsRow()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> source_parentHolder(static_cast<AbstractPrivateData *>(source_parent), xsink);
   return get_bool_node(qsfpm->getQSortFilterProxyModel()->filterAcceptsRow(source_row, *(static_cast<QModelIndex *>(source_parent))));
}

//void invalidateFilter ()
static AbstractQoreNode *QSORTFILTERPROXYMODEL_invalidateFilter(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   qsfpm->getQSortFilterProxyModel()->invalidateFilter();
   return 0;
}

//virtual bool lessThan ( const QModelIndex & left, const QModelIndex & right ) const
static AbstractQoreNode *QSORTFILTERPROXYMODEL_lessThan(QoreObject *self, QoreAbstractQSortFilterProxyModel *qsfpm, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *left = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!left) {
      if (!xsink->isException())
         xsink->raiseException("QSORTFILTERPROXYMODEL-LESSTHAN-PARAM-ERROR", "expecting a QModelIndex object as first argument to QSortFilterProxyModel::lessThan()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> leftHolder(static_cast<AbstractPrivateData *>(left), xsink);
   p = get_param(params, 1);
   QoreQModelIndex *right = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!right) {
      if (!xsink->isException())
         xsink->raiseException("QSORTFILTERPROXYMODEL-LESSTHAN-PARAM-ERROR", "expecting a QModelIndex object as second argument to QSortFilterProxyModel::lessThan()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> rightHolder(static_cast<AbstractPrivateData *>(right), xsink);
   return get_bool_node(qsfpm->getQSortFilterProxyModel()->lessThan(*(static_cast<QModelIndex *>(left)), *(static_cast<QModelIndex *>(right))));
}
*/
QoreClass *initQSortFilterProxyModelClass(QoreClass *qabstractproxymodel) {
   QC_QSortFilterProxyModel = new QoreClass("QSortFilterProxyModel", QDOM_GUI);
   CID_QSORTFILTERPROXYMODEL = QC_QSortFilterProxyModel->getID();

   QC_QSortFilterProxyModel->addBuiltinVirtualBaseClass(qabstractproxymodel);

   QC_QSortFilterProxyModel->setConstructor(QSORTFILTERPROXYMODEL_constructor);
   QC_QSortFilterProxyModel->setCopy((q_copy_t)QSORTFILTERPROXYMODEL_copy);

   QC_QSortFilterProxyModel->addMethod("dynamicSortFilter",           (q_method_t)QSORTFILTERPROXYMODEL_dynamicSortFilter);
   QC_QSortFilterProxyModel->addMethod("filterCaseSensitivity",       (q_method_t)QSORTFILTERPROXYMODEL_filterCaseSensitivity);
   QC_QSortFilterProxyModel->addMethod("filterKeyColumn",             (q_method_t)QSORTFILTERPROXYMODEL_filterKeyColumn);
   QC_QSortFilterProxyModel->addMethod("filterRegExp",                (q_method_t)QSORTFILTERPROXYMODEL_filterRegExp);
   QC_QSortFilterProxyModel->addMethod("filterRole",                  (q_method_t)QSORTFILTERPROXYMODEL_filterRole);
   QC_QSortFilterProxyModel->addMethod("isSortLocaleAware",           (q_method_t)QSORTFILTERPROXYMODEL_isSortLocaleAware);
   QC_QSortFilterProxyModel->addMethod("mapFromSource",               (q_method_t)QSORTFILTERPROXYMODEL_mapFromSource);
   QC_QSortFilterProxyModel->addMethod("mapToSource",                 (q_method_t)QSORTFILTERPROXYMODEL_mapToSource);
   QC_QSortFilterProxyModel->addMethod("setDynamicSortFilter",        (q_method_t)QSORTFILTERPROXYMODEL_setDynamicSortFilter);
   QC_QSortFilterProxyModel->addMethod("setFilterCaseSensitivity",    (q_method_t)QSORTFILTERPROXYMODEL_setFilterCaseSensitivity);
   QC_QSortFilterProxyModel->addMethod("setFilterKeyColumn",          (q_method_t)QSORTFILTERPROXYMODEL_setFilterKeyColumn);
   QC_QSortFilterProxyModel->addMethod("setFilterRegExp",             (q_method_t)QSORTFILTERPROXYMODEL_setFilterRegExp);
   QC_QSortFilterProxyModel->addMethod("setFilterRole",               (q_method_t)QSORTFILTERPROXYMODEL_setFilterRole);
   QC_QSortFilterProxyModel->addMethod("setSortCaseSensitivity",      (q_method_t)QSORTFILTERPROXYMODEL_setSortCaseSensitivity);
   QC_QSortFilterProxyModel->addMethod("setSortLocaleAware",          (q_method_t)QSORTFILTERPROXYMODEL_setSortLocaleAware);
   QC_QSortFilterProxyModel->addMethod("setSortRole",                 (q_method_t)QSORTFILTERPROXYMODEL_setSortRole);
   QC_QSortFilterProxyModel->addMethod("sortCaseSensitivity",         (q_method_t)QSORTFILTERPROXYMODEL_sortCaseSensitivity);
   QC_QSortFilterProxyModel->addMethod("sortColumn",                  (q_method_t)QSORTFILTERPROXYMODEL_sortColumn);
   QC_QSortFilterProxyModel->addMethod("sortOrder",                   (q_method_t)QSORTFILTERPROXYMODEL_sortOrder);
   QC_QSortFilterProxyModel->addMethod("sortRole",                    (q_method_t)QSORTFILTERPROXYMODEL_sortRole);
   QC_QSortFilterProxyModel->addMethod("invalidate",                  (q_method_t)QSORTFILTERPROXYMODEL_invalidate);
   QC_QSortFilterProxyModel->addMethod("setFilterFixedString",        (q_method_t)QSORTFILTERPROXYMODEL_setFilterFixedString);
   QC_QSortFilterProxyModel->addMethod("setFilterWildcard",           (q_method_t)QSORTFILTERPROXYMODEL_setFilterWildcard);
   //QC_QSortFilterProxyModel->addMethod("filterAcceptsColumn",         (q_method_t)QSORTFILTERPROXYMODEL_filterAcceptsColumn);
   //QC_QSortFilterProxyModel->addMethod("filterAcceptsRow",            (q_method_t)QSORTFILTERPROXYMODEL_filterAcceptsRow);
   //QC_QSortFilterProxyModel->addMethod("invalidateFilter",            (q_method_t)QSORTFILTERPROXYMODEL_invalidateFilter);
   //QC_QSortFilterProxyModel->addMethod("lessThan",                    (q_method_t)QSORTFILTERPROXYMODEL_lessThan);

   return QC_QSortFilterProxyModel;
}
