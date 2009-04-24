/*
 QC_QItemSelectionModel.cc
 
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

#include "QC_QItemSelectionModel.h"
#include "QC_QAbstractItemModel.h"

qore_classid_t CID_QITEMSELECTIONMODEL;
QoreClass *QC_QItemSelectionModel = 0;

//QItemSelectionModel ( QAbstractItemModel * model )
//QItemSelectionModel ( QAbstractItemModel * model, QObject * parent )
static void QITEMSELECTIONMODEL_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (!p || p->getType() != NT_OBJECT) {
      xsink->raiseException("QITEMSELECTIONMODEL-CONSTRUCTOR-PARAM-ERROR", "expecting an object derived from QAbstractItemModel as the first argument to QItemSelectionModel::constructor(), got type '%s' instead", p ? p->getTypeName() : "NOTHING");
      return;
   }

   QoreAbstractQAbstractItemModel *model = (QoreAbstractQAbstractItemModel *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QABSTRACTITEMMODEL, xsink);
   if (!model) {
      if (!xsink->isException())
	 xsink->raiseException("QITEMSELECTIONMODEL-CONSTRUCTOR-PARAM-ERROR", "QItemSelectionModel::constructor() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
      return;
   }

   ReferenceHolder<AbstractPrivateData> modelHolder(static_cast<AbstractPrivateData *>(model), xsink);

   p = get_param(params, 1);
   QoreAbstractQObject *parent = (p && p->getType() == NT_OBJECT) ? (QoreAbstractQObject *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (!parent) {
      if (*xsink)
	 return;

      self->setPrivate(CID_QITEMSELECTIONMODEL, new QoreQItemSelectionModel(self, static_cast<QAbstractItemModel *>(model->getQAbstractItemModel())));
      return;
   }

   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QITEMSELECTIONMODEL, new QoreQItemSelectionModel(self, static_cast<QAbstractItemModel *>(model->getQAbstractItemModel()), parent->getQObject()));
}

static void QITEMSELECTIONMODEL_copy(QoreObject *self, QoreObject *old, QoreQItemSelectionModel *qism, ExceptionSink *xsink) {
   xsink->raiseException("QITEMSELECTIONMODEL-COPY-ERROR", "objects of this class cannot be copied");
}

//bool columnIntersectsSelection ( int column, const QModelIndex & parent ) const
static AbstractQoreNode *QITEMSELECTIONMODEL_columnIntersectsSelection(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONMODEL-COLUMNINTERSECTSSELECTION-PARAM-ERROR", "expecting a QModelIndex object as second argument to QItemSelectionModel::columnIntersectsSelection()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return get_bool_node(qism->qobj->columnIntersectsSelection(column, *(static_cast<QModelIndex *>(parent))));
}

//QModelIndex currentIndex () const
static AbstractQoreNode *QITEMSELECTIONMODEL_currentIndex(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QModelIndex, new QoreQModelIndex(qism->qobj->currentIndex()));
}

//bool hasSelection () const
static AbstractQoreNode *QITEMSELECTIONMODEL_hasSelection(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   return get_bool_node(qism->qobj->hasSelection());
}

//bool isColumnSelected ( int column, const QModelIndex & parent ) const
static AbstractQoreNode *QITEMSELECTIONMODEL_isColumnSelected(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONMODEL-ISCOLUMNSELECTED-PARAM-ERROR", "expecting a QModelIndex object as second argument to QItemSelectionModel::isColumnSelected()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return get_bool_node(qism->qobj->isColumnSelected(column, *(static_cast<QModelIndex *>(parent))));
}

//bool isRowSelected ( int row, const QModelIndex & parent ) const
static AbstractQoreNode *QITEMSELECTIONMODEL_isRowSelected(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONMODEL-ISROWSELECTED-PARAM-ERROR", "expecting a QModelIndex object as second argument to QItemSelectionModel::isRowSelected()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return get_bool_node(qism->qobj->isRowSelected(row, *(static_cast<QModelIndex *>(parent))));
}

//bool isSelected ( const QModelIndex & index ) const
static AbstractQoreNode *QITEMSELECTIONMODEL_isSelected(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONMODEL-ISSELECTED-PARAM-ERROR", "expecting a QModelIndex object as first argument to QItemSelectionModel::isSelected()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   return get_bool_node(qism->qobj->isSelected(*(static_cast<QModelIndex *>(index))));
}

//const QAbstractItemModel * model () const
static AbstractQoreNode *QITEMSELECTIONMODEL_model(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   QAbstractItemModel *qt_qobj = const_cast<QAbstractItemModel *>(qism->qobj->model());
   if (!qt_qobj)
      return 0;
   QVariant qv_ptr = qt_qobj->property("qobject");
   QoreObject *rv_obj = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
   if (rv_obj)
      return rv_obj->refSelf();
   rv_obj = new QoreObject(QC_QAbstractItemModel, getProgram());
   QoreQtQAbstractItemModel *t_qobj = new QoreQtQAbstractItemModel(rv_obj, qt_qobj);
   rv_obj->setPrivate(CID_QABSTRACTITEMMODEL, t_qobj);
   return rv_obj;
}

//bool rowIntersectsSelection ( int row, const QModelIndex & parent ) const
static AbstractQoreNode *QITEMSELECTIONMODEL_rowIntersectsSelection(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   QoreQModelIndex *parent = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!parent) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONMODEL-ROWINTERSECTSSELECTION-PARAM-ERROR", "expecting a QModelIndex object as second argument to QItemSelectionModel::rowIntersectsSelection()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   return get_bool_node(qism->qobj->rowIntersectsSelection(row, *(static_cast<QModelIndex *>(parent))));
}

//QModelIndexList selectedColumns ( int row = 0 ) const
static AbstractQoreNode *QITEMSELECTIONMODEL_selectedColumns(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int row = !is_nothing(p) ? p->getAsInt() : 0;
   return return_qmodelindexlist(qism->qobj->selectedColumns(row));
}

//QModelIndexList selectedIndexes () const
static AbstractQoreNode *QITEMSELECTIONMODEL_selectedIndexes(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   return return_qmodelindexlist(qism->qobj->selectedIndexes());
}

//QModelIndexList selectedRows ( int column = 0 ) const
static AbstractQoreNode *QITEMSELECTIONMODEL_selectedRows(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int column = !is_nothing(p) ? p->getAsInt() : 0;
   return return_qmodelindexlist(qism->qobj->selectedRows(column));
}

//const QItemSelection selection () const
static AbstractQoreNode *QITEMSELECTIONMODEL_selection(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QItemSelection, new QoreQItemSelection(qism->qobj->selection()));
}

//virtual void clear ()
static AbstractQoreNode *QITEMSELECTIONMODEL_clear(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   qism->qobj->clear();
   return 0;
}

//void clearSelection ()
static AbstractQoreNode *QITEMSELECTIONMODEL_clearSelection(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   qism->qobj->clearSelection();
   return 0;
}

//virtual void reset ()
static AbstractQoreNode *QITEMSELECTIONMODEL_reset(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   qism->qobj->reset();
   return 0;
}

//virtual void select ( const QModelIndex & index, QItemSelectionModel::SelectionFlags command )
//virtual void select ( const QItemSelection & selection, QItemSelectionModel::SelectionFlags command )
static AbstractQoreNode *QITEMSELECTIONMODEL_select(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (!p || p->getType() != NT_OBJECT) {
      xsink->raiseException("QITEMSELECTIONMODEL-SELECT-PARAM-ERROR", "expecting an object derived from QItemSelection or QModelIndex as the first argument to QItemSelectionModel::constructor(), got type '%s' instead", p ? p->getTypeName() : "NOTHING");
      return 0;
   }

   QoreQItemSelection *selection = (QoreQItemSelection *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTION, xsink);
   if (!selection) {
      QoreQModelIndex *index = (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink);
      if (!index) {
	 if (!xsink->isException())
	    xsink->raiseException("QITEMSELECTIONMODEL-SELECT-PARAM-ERROR", "QItemSelectionModel::select() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
	 return 0;
      }
      ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
      p = get_param(params, 1);
      QItemSelectionModel::SelectionFlags command = (QItemSelectionModel::SelectionFlags)(p ? p->getAsInt() : 0);
      qism->qobj->select(*(static_cast<QModelIndex *>(index)), command);
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> selectionHolder(static_cast<AbstractPrivateData *>(selection), xsink);
   p = get_param(params, 1);
   QItemSelectionModel::SelectionFlags command = (QItemSelectionModel::SelectionFlags)(p ? p->getAsInt() : 0);
   qism->qobj->select(*(static_cast<QItemSelection *>(selection)), command);
   return 0;
}

//void setCurrentIndex ( const QModelIndex & index, QItemSelectionModel::SelectionFlags command )
static AbstractQoreNode *QITEMSELECTIONMODEL_setCurrentIndex(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQModelIndex *index = (p && p->getType() == NT_OBJECT) ? (QoreQModelIndex *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QMODELINDEX, xsink) : 0;
   if (!index) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONMODEL-SETCURRENTINDEX-PARAM-ERROR", "expecting a QModelIndex object as first argument to QItemSelectionModel::setCurrentIndex()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> indexHolder(static_cast<AbstractPrivateData *>(index), xsink);
   p = get_param(params, 1);
   QItemSelectionModel::SelectionFlags command = (QItemSelectionModel::SelectionFlags)(p ? p->getAsInt() : 0);
   qism->qobj->setCurrentIndex(*(static_cast<QModelIndex *>(index)), command);
   return 0;
}

//void emitSelectionChanged ( const QItemSelection & newSelection, const QItemSelection & oldSelection )
static AbstractQoreNode *QITEMSELECTIONMODEL_emitSelectionChanged(QoreObject *self, QoreQItemSelectionModel *qism, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QoreQItemSelection *newSelection = (p && p->getType() == NT_OBJECT) ? (QoreQItemSelection *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTION, xsink) : 0;
   if (!newSelection) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONMODEL-EMITSELECTIONCHANGED-PARAM-ERROR", "expecting a QItemSelection object as first argument to QItemSelectionModel::emitSelectionChanged()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> newSelectionHolder(static_cast<AbstractPrivateData *>(newSelection), xsink);
   p = get_param(params, 1);
   QoreQItemSelection *oldSelection = (p && p->getType() == NT_OBJECT) ? (QoreQItemSelection *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QITEMSELECTION, xsink) : 0;
   if (!oldSelection) {
      if (!xsink->isException())
         xsink->raiseException("QITEMSELECTIONMODEL-EMITSELECTIONCHANGED-PARAM-ERROR", "expecting a QItemSelection object as second argument to QItemSelectionModel::emitSelectionChanged()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> oldSelectionHolder(static_cast<AbstractPrivateData *>(oldSelection), xsink);
   qism->emitSelectionChanged(*(static_cast<QItemSelection *>(newSelection)), *(static_cast<QItemSelection *>(oldSelection)));
   return 0;
}

static QoreClass *initQItemSelectionModelClass(QoreClass *qobject) {
   QC_QItemSelectionModel = new QoreClass("QItemSelectionModel", QDOM_GUI);
   CID_QITEMSELECTIONMODEL = QC_QItemSelectionModel->getID();

   QC_QItemSelectionModel->addBuiltinVirtualBaseClass(qobject);

   QC_QItemSelectionModel->setConstructor(QITEMSELECTIONMODEL_constructor);
   QC_QItemSelectionModel->setCopy((q_copy_t)QITEMSELECTIONMODEL_copy);

   QC_QItemSelectionModel->addMethod("columnIntersectsSelection",   (q_method_t)QITEMSELECTIONMODEL_columnIntersectsSelection);
   QC_QItemSelectionModel->addMethod("currentIndex",                (q_method_t)QITEMSELECTIONMODEL_currentIndex);
   QC_QItemSelectionModel->addMethod("hasSelection",                (q_method_t)QITEMSELECTIONMODEL_hasSelection);
   QC_QItemSelectionModel->addMethod("isColumnSelected",            (q_method_t)QITEMSELECTIONMODEL_isColumnSelected);
   QC_QItemSelectionModel->addMethod("isRowSelected",               (q_method_t)QITEMSELECTIONMODEL_isRowSelected);
   QC_QItemSelectionModel->addMethod("isSelected",                  (q_method_t)QITEMSELECTIONMODEL_isSelected);
   QC_QItemSelectionModel->addMethod("model",                       (q_method_t)QITEMSELECTIONMODEL_model);
   QC_QItemSelectionModel->addMethod("rowIntersectsSelection",      (q_method_t)QITEMSELECTIONMODEL_rowIntersectsSelection);
   QC_QItemSelectionModel->addMethod("selectedColumns",             (q_method_t)QITEMSELECTIONMODEL_selectedColumns);
   QC_QItemSelectionModel->addMethod("selectedIndexes",             (q_method_t)QITEMSELECTIONMODEL_selectedIndexes);
   QC_QItemSelectionModel->addMethod("selectedRows",                (q_method_t)QITEMSELECTIONMODEL_selectedRows);
   QC_QItemSelectionModel->addMethod("selection",                   (q_method_t)QITEMSELECTIONMODEL_selection);
   QC_QItemSelectionModel->addMethod("clear",                       (q_method_t)QITEMSELECTIONMODEL_clear);
   QC_QItemSelectionModel->addMethod("clearSelection",              (q_method_t)QITEMSELECTIONMODEL_clearSelection);
   QC_QItemSelectionModel->addMethod("reset",                       (q_method_t)QITEMSELECTIONMODEL_reset);
   QC_QItemSelectionModel->addMethod("select",                      (q_method_t)QITEMSELECTIONMODEL_select);
   QC_QItemSelectionModel->addMethod("setCurrentIndex",             (q_method_t)QITEMSELECTIONMODEL_setCurrentIndex);

   // private methods
   QC_QItemSelectionModel->addMethod("emitSelectionChanged",        (q_method_t)QITEMSELECTIONMODEL_emitSelectionChanged, true);

   return QC_QItemSelectionModel;
}

QoreNamespace *initQItemSelectionModelNS(QoreClass *qobject) {
   QoreNamespace *ns = new QoreNamespace("QItemSelectionModel");
   ns->addSystemClass(initQItemSelectionModelClass(QC_QObject));

   // SelectionFlag enum
   ns->addConstant("NoUpdate",                 new QoreBigIntNode(QItemSelectionModel::NoUpdate));
   ns->addConstant("Clear",                    new QoreBigIntNode(QItemSelectionModel::Clear));
   ns->addConstant("Select",                   new QoreBigIntNode(QItemSelectionModel::Select));
   ns->addConstant("Deselect",                 new QoreBigIntNode(QItemSelectionModel::Deselect));
   ns->addConstant("Toggle",                   new QoreBigIntNode(QItemSelectionModel::Toggle));
   ns->addConstant("Current",                  new QoreBigIntNode(QItemSelectionModel::Current));
   ns->addConstant("Rows",                     new QoreBigIntNode(QItemSelectionModel::Rows));
   ns->addConstant("Columns",                  new QoreBigIntNode(QItemSelectionModel::Columns));
   ns->addConstant("SelectCurrent",            new QoreBigIntNode(QItemSelectionModel::SelectCurrent));
   ns->addConstant("ToggleCurrent",            new QoreBigIntNode(QItemSelectionModel::ToggleCurrent));
   ns->addConstant("ClearAndSelect",           new QoreBigIntNode(QItemSelectionModel::ClearAndSelect));

   return ns;
}
