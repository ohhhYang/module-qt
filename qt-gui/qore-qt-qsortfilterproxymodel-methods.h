
#if 0
class T {
#endif

  protected:

   // virtual methods
   virtual bool filterAcceptsColumn ( int source_column, const QModelIndex & source_parent ) const {
      if (!m_filterAcceptsRow)
          return QOREQTYPE::filterAcceptsColumn(source_column, source_parent);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);
      
      QoreBigIntNode * srcCol = new QoreBigIntNode(source_column);
      args->push(srcCol);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(source_parent));
      args->push(qw);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_filterAcceptsColumn, *args, &xsink), &xsink);
      if (xsink)
          return false;

      return rv ? rv->getAsBool() : false;
   }

   virtual bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const {
      if (!m_filterAcceptsRow)
          return QOREQTYPE::filterAcceptsRow(source_row, source_parent);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);
      
      QoreBigIntNode * srcRow = new QoreBigIntNode(source_row);
      args->push(srcRow);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(source_parent));
      args->push(qw);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_filterAcceptsRow, *args, &xsink), &xsink);
      if (xsink)
          return false;

      return rv ? rv->getAsBool() : false;
   }

   virtual bool lessThan (  const QModelIndex & left, const QModelIndex & right ) const {
      if (!m_lessThan)
          return QOREQTYPE::lessThan(left, right);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);
      
      QoreObject *qwL = new QoreObject(QC_QModelIndex, getProgram());
      qwL->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(left));
      args->push(qwL);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(right));
      args->push(qw);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_lessThan, *args, &xsink), &xsink);
      if (xsink)
          return false;

      return rv ? rv->getAsBool() : false;
   }

public:
   // provides access to protected functions from outside the class
    DLLLOCAL virtual bool parent_filterAcceptsColumn ( int source_column, const QModelIndex & source_parent ) const
    {
        return QOREQTYPE::filterAcceptsColumn(source_column, source_parent);
    }
    
    DLLLOCAL virtual bool parent_filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const
    {
       return QOREQTYPE::filterAcceptsRow(source_row, source_parent);
    }
    
    DLLLOCAL void parent_invalidateFilter ()
    {
       QOREQTYPE::invalidateFilter();
    }
    
    DLLLOCAL virtual bool parent_lessThan ( const QModelIndex & left, const QModelIndex & right ) const
    {
        return QOREQTYPE::lessThan(left, right);
    }

#if 0
}
#endif

#undef PARENT_IS_PRIVATE
#undef HASCHILDREN_IS_PRIVATE

