
#if 0
class T {
#endif

protected:

   // virtual methods
   virtual QModelIndex buddy ( const QModelIndex & index ) const {
      if (!m_buddy)
	 return QOREQTYPE::buddy(index);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
      args->push(qw);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_buddy, *args, &xsink), &xsink);
      if (xsink)
	 return QModelIndex();

      QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQModelIndex *qmi = o ? (QoreQModelIndex *)o->getReferencedPrivateData(CID_QMODELINDEX, &xsink) : 0;

      if (!qmi) {
	 xsink.raiseException("BUDDY-ERROR", "the buddy() method did not return a QModelIndex object");
	 return QModelIndex();
      }
      ReferenceHolder<QoreQModelIndex> qmiHolder(qmi, &xsink);

      QModelIndex rv_qmi = *(static_cast<QModelIndex *>(qmi));
      return rv_qmi;
   }

   virtual bool canFetchMore ( const QModelIndex & parent ) const {
      if (!m_canFetchMore)
	 return QOREQTYPE::canFetchMore(parent);
      
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_canFetchMore, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : false;
   }

#ifndef COLUMNCOUNT_IS_PRIVATE
   virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const {
      if (!m_columnCount)
	 return QOREQTYPE::columnCount(parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_columnCount, *args, &xsink), &xsink);
      return rv ? rv->getAsInt() : 0;
   }
#endif

   virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const {
      if (!m_data)
	 return QOREQTYPE::data(index, role);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
      args->push(qw);

      args->push(new QoreBigIntNode(role));

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_data, *args, &xsink), &xsink);

      return to_qvariant(*rv, &xsink);
   }
   
   virtual bool dropMimeData ( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent ) {
      if (!m_dropMimeData)
	 return QOREQTYPE::dropMimeData(data, action, row, column, parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qo = new QoreObject(QC_QMimeData, getProgram());
      qo->setPrivate(CID_QMIMEDATA, new QoreQtQMimeData(qo, const_cast<QMimeData *>(data), false));
      args->push(qo);

      args->push(new QoreBigIntNode(action));
      args->push(new QoreBigIntNode(row));
      args->push(new QoreBigIntNode(column));

      qo = new QoreObject(QC_QModelIndex, getProgram());
      qo->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qo);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_dropMimeData, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : false;
   }

   virtual void fetchMore ( const QModelIndex & parent ) {
      if (!m_fetchMore) {
	 QOREQTYPE::fetchMore(parent);
	 return;
      }
      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_fetchMore, *args, &xsink), &xsink);
   }

   virtual Qt::ItemFlags flags ( const QModelIndex & index ) const {
      if (!m_flags)
	 return QOREQTYPE::flags(index);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_flags, *args, &xsink), &xsink);
      return rv ? (Qt::ItemFlags)rv->getAsInt() : Qt::NoItemFlags;
   }

#ifndef HASCHILDREN_IS_PRIVATE
   virtual bool hasChildren ( const QModelIndex & parent = QModelIndex() ) const {
      if (!m_hasChildren)
	 return QOREQTYPE::hasChildren(parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_hasChildren, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : false;
   }
#endif

   virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const {
      if (!m_headerData)
	 return QOREQTYPE::headerData(section, orientation, role);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      args->push(new QoreBigIntNode(section));
      args->push(new QoreBigIntNode(orientation));
      args->push(new QoreBigIntNode(role));

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_headerData, *args, &xsink), &xsink);

      return to_qvariant(*rv, &xsink);
   }

   virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const {
      if (!m_index)
	 return QOREQTYPE::index(row, column, parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      args->push(new QoreBigIntNode(row));
      args->push(new QoreBigIntNode(column));

      QoreObject *qo = new QoreObject(QC_QModelIndex, getProgram());
      qo->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qo);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_index, *args, &xsink), &xsink);

      QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQModelIndex *qmi = o ? (QoreQModelIndex *)o->getReferencedPrivateData(CID_QMODELINDEX, &xsink) : 0;

      if (!qmi) {
	 xsink.raiseException("BUDDY-ERROR", "the index() method did not return a QModelIndex object");
	 return QModelIndex();
      }
      ReferenceHolder<QoreQModelIndex> qmiHolder(qmi, &xsink);

      QModelIndex rv_qmi = *(static_cast<QModelIndex *>(qmi));
      return rv_qmi;
   }

   virtual bool insertColumns ( int column, int count, const QModelIndex & parent = QModelIndex() ) {
      if (!m_insertColumns)
	 return QOREQTYPE::insertColumns(column, count, parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      args->push(new QoreBigIntNode(column));
      args->push(new QoreBigIntNode(count));

      QoreObject *qo = new QoreObject(QC_QModelIndex, getProgram());
      qo->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qo);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_insertColumns, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : false;
   }

   virtual bool insertRows ( int row, int count, const QModelIndex & parent = QModelIndex() ) {
      if (!m_insertRows)
	 return QOREQTYPE::insertRows(row, count, parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      args->push(new QoreBigIntNode(row));
      args->push(new QoreBigIntNode(count));

      QoreObject *qo = new QoreObject(QC_QModelIndex, getProgram());
      qo->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qo);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_insertRows, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : false;
   }
   
   virtual QMap<int, QVariant> itemData ( const QModelIndex & index ) const {
      if (!m_itemData)
	 return QOREQTYPE::itemData(index);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_itemData, *args, &xsink), &xsink);
      if (!rv || rv->getType() != NT_HASH) {
	 xsink.raiseException("ITEMDATA-ERROR", "itemData() did not return a hash: type returned: %s", rv ? rv->getTypeName() : "NOTHING");
	 return QMap<int, QVariant>();
      }

      QMap<int, QVariant> hrv;
      ConstHashIterator hi(reinterpret_cast<const QoreHashNode *>(*rv));
      while (hi.next()) {
	 int index = atoi(hi.getKey());
	 hrv[index] = to_qvariant(hi.getValue(), &xsink);
      }
      return hrv;
   }

   virtual QModelIndexList match ( const QModelIndex & start, int role, const QVariant & value, int hits = 1, Qt::MatchFlags flags = Qt::MatchFlags( Qt::MatchStartsWith | Qt::MatchWrap ) ) const {
      if (!m_match)
	 return QOREQTYPE::match(start, role, value, hits, flags);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(start));
      args->push(qw);

      args->push(new QoreBigIntNode(role));
      args->push(return_qvariant(value));
      args->push(new QoreBigIntNode(hits));
      args->push(new QoreBigIntNode(flags));

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_match, *args, &xsink), &xsink);
      return to_qmodelindexlist(*rv, &xsink);
   }

   virtual QMimeData * mimeData ( const QModelIndexList & indexes ) const {
      if (!m_mimeData)
	 return QOREQTYPE::mimeData(indexes);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);
      
      args->push(return_qmodelindexlist(indexes));

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_mimeData, *args, &xsink), &xsink);
      if (is_nothing(*rv))
	 return 0;

      QoreObject *o = rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQMimeData *qmd = o ? (QoreQMimeData *)o->getReferencedPrivateData(CID_QMIMEDATA, &xsink) : 0;

      if (!qmd) {
	 xsink.raiseException("MIMEDATA-ERROR", "the mimeData() method did not return a QMimeData object");
	 return 0;
      }
      ReferenceHolder<QoreQMimeData> qmdHolder(qmd, &xsink);
      return qmd->getQMimeData();
   }

   virtual QStringList mimeTypes () const {
      if (!m_mimeTypes)
	 return QOREQTYPE::mimeTypes();

      ExceptionSink xsink;
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_mimeTypes, 0, &xsink), &xsink);

      QStringList srv;
      if (!is_nothing(*rv)) {
	 if (rv->getType() != NT_LIST) {
	    QoreStringNodeValueHelper str(*rv);
	    srv.push_back(str->getBuffer());
	 }
	 else {
	    ConstListIterator li(reinterpret_cast<const QoreListNode *>(*rv));
	    while (li.next()) {
	       QoreStringNodeValueHelper str(li.getValue());
	       srv.push_back(str->getBuffer());	       
	    }
	 }
      }

      return srv;
   }

#ifndef PARENT_IS_PRIVATE
   virtual QModelIndex parent ( const QModelIndex & index ) const {
      if (!m_parent)
	 return QOREQTYPE::parent(index);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_parent, *args, &xsink), &xsink);
      if (xsink)
	 return QModelIndex();

      QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQModelIndex *qmi = o ? (QoreQModelIndex *)o->getReferencedPrivateData(CID_QMODELINDEX, &xsink) : 0;

      if (!qmi) {
	 xsink.raiseException("PARENT-ERROR", "the parent() method did not return a QModelIndex object");
	 return QModelIndex();
      }
      ReferenceHolder<QoreQModelIndex> qmiHolder(qmi, &xsink);

      QModelIndex rv_qmi = *(static_cast<QModelIndex *>(qmi));
      return rv_qmi;
   }
#endif

   virtual bool removeColumns ( int column, int count, const QModelIndex & parent = QModelIndex() ) {
      if (!m_removeColumns)
	 return QOREQTYPE::removeColumns(column, count, parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      args->push(new QoreBigIntNode(column));
      args->push(new QoreBigIntNode(count));

      QoreObject *qo = new QoreObject(QC_QModelIndex, getProgram());
      qo->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qo);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_removeColumns, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : false;
   }

   virtual bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() ) {
      if (!m_removeRows)
	 return QOREQTYPE::removeRows(row, count, parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      args->push(new QoreBigIntNode(row));
      args->push(new QoreBigIntNode(count));

      QoreObject *qo = new QoreObject(QC_QModelIndex, getProgram());
      qo->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qo);
      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_removeRows, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : false;
   }

   virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const {
      if (!m_rowCount)
	 return QOREQTYPE::rowCount(parent);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(parent));
      args->push(qw);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_rowCount, *args, &xsink), &xsink);
      return rv ? rv->getAsInt() : 0;
   }

   virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole ) {
      if (!m_setData)
	 return QOREQTYPE::setData(index, value, role);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
      args->push(qw);

      args->push(return_qvariant(value));
      args->push(new QoreBigIntNode(role));

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_setData, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : 0;
   }

   virtual bool setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole ) {
      if (!m_setHeaderData)
	 return QOREQTYPE::setHeaderData(section, orientation, value, role);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      args->push(new QoreBigIntNode(section));
      args->push(new QoreBigIntNode(orientation));
      args->push(return_qvariant(value));
      args->push(new QoreBigIntNode(role));

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_setHeaderData, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : 0;
   }

   virtual bool setItemData ( const QModelIndex & index, const QMap<int, QVariant> & roles ) {
      if (!m_setItemData)
	 return QOREQTYPE::setItemData(index, roles);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
      qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
      args->push(qw);

      QoreHashNode *h = new QoreHashNode();
      for (QMap<int, QVariant>::const_iterator i = roles.begin(), e = roles.end(); i != e; ++i) {
	 QoreString tmp((int64)i.key());
	 h->setKeyValue(tmp.getBuffer(), return_qvariant(i.value()), &xsink);
      }
      args->push(h);

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_setItemData, *args, &xsink), &xsink);
      return rv ? rv->getAsBool() : 0;

      return false;
   }

   virtual void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder ) {
      if (!m_sort) {
	 QOREQTYPE::sort(column, order);
	 return;
      }

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      args->push(new QoreBigIntNode(column));
      args->push(new QoreBigIntNode(order));

      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_sort, *args, &xsink), &xsink);
   }

   virtual QSize span ( const QModelIndex & index ) const {
      if (!m_span)
	 return QOREQTYPE::span(index);

      ExceptionSink xsink;
      ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

      QoreObject *qo = new QoreObject(QC_QModelIndex, getProgram());
      qo->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
      args->push(qo);

      
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_span, *args, &xsink), &xsink);
      if (xsink)
	 return QSize();

      qo = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
      QoreQSize *qs = qo ? (QoreQSize *)qo->getReferencedPrivateData(CID_QSIZE, &xsink) : 0;

      if (!qs) {
	 xsink.raiseException("SPAN-ERROR", "the span() method did not return a QSize object");
	 return QSize();
      }
      ReferenceHolder<QoreQSize> sizeHolder(qs, &xsink);
      QSize rv_qs = *(static_cast<QSize *>(qs));
      return rv_qs;
   }

   virtual Qt::DropActions supportedDropActions () const {
      if (!m_supportedDropActions)
	 return QOREQTYPE::supportedDropActions();

      ExceptionSink xsink;
      ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_supportedDropActions, 0, &xsink), &xsink);

      return rv ? (Qt::DropActions)rv->getAsInt() : Qt::IgnoreAction;
   }

public:
   // provides access to protected functions from outside the class
   DLLLOCAL virtual void parent_beginInsertColumns ( const QModelIndex & parent, int first, int last ) {
      QOREQTYPE::beginInsertColumns(parent, first, last);
   }
   DLLLOCAL virtual void parent_beginInsertRows ( const QModelIndex & parent, int first, int last ) {
      QOREQTYPE::beginInsertRows(parent, first, last);
   }
   DLLLOCAL virtual void parent_beginRemoveColumns ( const QModelIndex & parent, int first, int last ) {
      QOREQTYPE::beginRemoveColumns(parent, first, last);
   }
   DLLLOCAL virtual void parent_beginRemoveRows ( const QModelIndex & parent, int first, int last )  {
      QOREQTYPE::beginRemoveRows(parent, first, last);
   }
   DLLLOCAL virtual void parent_changePersistentIndex ( const QModelIndex & from, const QModelIndex & to ) {
      QOREQTYPE::changePersistentIndex(from, to);
   }
   DLLLOCAL virtual void parent_changePersistentIndexList ( const QModelIndexList & from, const QModelIndexList & to ) {
      QOREQTYPE::changePersistentIndexList(from, to);
   }
   DLLLOCAL virtual QModelIndex parent_createIndex ( int row, int column, void * ptr = 0 ) const { 
      return QOREQTYPE::createIndex(row, column, ptr);
   }
   DLLLOCAL virtual QModelIndex parent_createIndex ( int row, int column, quint32 id ) const {
      return QOREQTYPE::createIndex(row, column, id);
   }
   DLLLOCAL virtual void parent_endInsertColumns () {
      QOREQTYPE::endInsertColumns();
   }
   DLLLOCAL virtual void parent_endInsertRows () {
      QOREQTYPE::endInsertRows();
   }
   DLLLOCAL virtual void parent_endRemoveColumns () {
      QOREQTYPE::endRemoveColumns();
   }
   DLLLOCAL virtual void parent_endRemoveRows () {
      QOREQTYPE::endRemoveRows();
   }
   DLLLOCAL virtual QModelIndexList parent_persistentIndexList () const {
      return QOREQTYPE::persistentIndexList();
   }
   DLLLOCAL virtual void parent_reset () {
      QOREQTYPE::reset();
   }

   DLLLOCAL QModelIndex qoreCreateIndex(int row, int column, const AbstractQoreNode *data) const {
      //printd(5, "QoreAbstractQAbstractItemModel::qoreCreateIndex(row=%d, column=%d, data=%p) this=%p\n", row, column, data, this);
	 
      if (data) {
	 AbstractQoreNode *d = const_cast<AbstractQoreNode *>(data);
	 std::pair<node_set_t::iterator, bool> rv = node_set.insert(d);
	 if (rv.second) {
	    d->ref();
	 }
      }

      return QOREQTYPE::createIndex(row, column, (void *)data);
   }

   DLLLOCAL bool isQoreData(const AbstractQoreNode *data) {
      return node_set.find(const_cast<AbstractQoreNode *>(data)) != node_set.end();
   }
   
#if 0
}
#endif

#undef PARENT_IS_PRIVATE
#undef HASCHILDREN_IS_PRIVATE

