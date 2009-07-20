
#if 0
class T {
#endif

protected:

   // virtual methods
   virtual QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const {
      if (!m_mapFromSource)
          return QOREQTYPE::mapFromSource(sourceIndex);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(sourceIndex));
      args->push(qw);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_mapFromSource, *args, &xsink), &xsink);
      if (xsink)
          return QModelIndex();

      QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQModelIndex *qmi = o ? (QoreQModelIndex *)o->getReferencedPrivateData(CID_QMODELINDEX, &xsink) : 0;

      if (!qmi) {
          xsink.raiseException("MAPFROMSOURCE-ERROR", "the mapFromSource() method did not return a QModelIndex object");
          return QModelIndex();
      }
      ReferenceHolder<QoreQModelIndex> qmiHolder(qmi, &xsink);

      QModelIndex rv_qmi = *(static_cast<QModelIndex *>(qmi));
      return rv_qmi;
   }

   virtual QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const {
      if (!m_mapToSource)
          return QOREQTYPE::mapToSource(proxyIndex);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(proxyIndex));
      args->push(qw);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_mapToSource, *args, &xsink), &xsink);
      if (xsink)
          return QModelIndex();

      QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQModelIndex *qmi = o ? (QoreQModelIndex *)o->getReferencedPrivateData(CID_QMODELINDEX, &xsink) : 0;

      if (!qmi) {
          xsink.raiseException("MAPTOSOURCE-ERROR", "the mapFromSource() method did not return a QModelIndex object");
          return QModelIndex();
      }
      ReferenceHolder<QoreQModelIndex> qmiHolder(qmi, &xsink);

      QModelIndex rv_qmi = *(static_cast<QModelIndex *>(qmi));
      return rv_qmi;
   }


   virtual QItemSelection mapSelectionFromSource ( const QItemSelection & sourceSelection ) const {
      if (!m_mapSelectionFromSource)
          return QOREQTYPE::mapSelectionFromSource(sourceSelection);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QItemSelection, getProgram());
      qw->setPrivate(CID_QITEMSELECTION, new QoreQItemSelection(sourceSelection));
      args->push(qw);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_mapSelectionFromSource, *args, &xsink), &xsink);
      if (xsink)
          return QItemSelection();

      QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQItemSelection *qmi = o ? (QoreQItemSelection *)o->getReferencedPrivateData(CID_QITEMSELECTION, &xsink) : 0;

      if (!qmi) {
          xsink.raiseException("MAPSELECTIONFROMSOURCE-ERROR", "the mapSelectionFromSource() method did not return a QItemSelection object");
          return QItemSelection();
      }
      ReferenceHolder<QoreQItemSelection> qmiHolder(qmi, &xsink);

      QItemSelection rv_qmi = *(static_cast<QItemSelection *>(qmi));
      return rv_qmi;
   }

   virtual QItemSelection mapSelectionToSource ( const QItemSelection & sourceSelection ) const {
      if (!m_mapSelectionFromSource)
          return QOREQTYPE::mapSelectionToSource(sourceSelection);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);
    
      QoreObject *qw = new QoreObject(QC_QItemSelection, getProgram());
      qw->setPrivate(CID_QITEMSELECTION, new QoreQItemSelection(sourceSelection));
      args->push(qw);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_mapSelectionToSource, *args, &xsink), &xsink);
      if (xsink)
          return QItemSelection();

      QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQItemSelection *qmi = o ? (QoreQItemSelection *)o->getReferencedPrivateData(CID_QITEMSELECTION, &xsink) : 0;

      if (!qmi) {
          xsink.raiseException("MAPSELECTIONTOSOURCE-ERROR", "the mapSelectionToSource() method did not return a QItemSelection object");
          return QItemSelection();
      }
      ReferenceHolder<QoreQItemSelection> qmiHolder(qmi, &xsink);

      QItemSelection rv_qmi = *(static_cast<QItemSelection *>(qmi));
      return rv_qmi;
   }


   virtual void setSourceModel ( QAbstractItemModel * sourceModel ) {
      if (!m_setSourceModel)
         return QOREQTYPE::setSourceModel(sourceModel);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QAbstractItemModel, getProgram());
      qw->setPrivate(CID_QABSTRACTITEMMODEL, new QoreQAbstractItemModel(qw, sourceModel));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_setSourceModel, *args, &xsink), &xsink);
   }


   
#if 0
}
#endif

#undef PARENT_IS_PRIVATE
#undef HASCHILDREN_IS_PRIVATE

