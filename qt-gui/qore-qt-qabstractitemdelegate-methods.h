
#if 0
class T {
#endif

   protected:
      virtual QWidget * createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	 if (!m_createEditor)
	    return QOREQTYPE::createEditor(parent, option, index);

	 ExceptionSink xsink;
	 ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

	 args->push(return_qobject(parent));

	 QoreObject *qw = new QoreObject(QC_QStyleOptionViewItem, getProgram());
	 qw->setPrivate(CID_QSTYLEOPTIONVIEWITEM, new QoreQStyleOptionViewItem(option));
	 args->push(qw);
	 
	 qw = new QoreObject(QC_QModelIndex, getProgram());
	 qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
	 args->push(qw);

	 ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_createEditor, *args, &xsink), &xsink);

	 if (xsink)
            return QOREQTYPE::createEditor(parent, option, index);
	 
	 QoreObject *o = dynamic_cast<QoreObject *>(*rv);
	 QoreQWidget *qqw = o ? (QoreQWidget *)o->getReferencedPrivateData(CID_QWIDGET, &xsink) : 0;

         if (!qqw) {
            xsink.raiseException("CREATEEDITOR-ERROR", "the createEditor() method did not return a QWidget object");
            return QOREQTYPE::createEditor(parent, option, index);
         }
         ReferenceHolder<QoreQWidget> sizeHolder(qqw, &xsink);
	 return qqw->getQWidget();
      }

      virtual bool editorEvent ( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index ) {
	 if (!m_editorEvent)
	    return QOREQTYPE::editorEvent(event, model, option, index);

	 ExceptionSink xsink;
	 ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

	 QoreObject *o = new QoreObject(QC_QEvent, getProgram());
	 o->setPrivate(CID_QEVENT, new QoreQEvent(*event));
	 args->push(o);

	 // FIXME: find derived class from QAbstractItemModel and instantiate qore class
	 o = new QoreObject(QC_QAbstractItemModel, getProgram());
	 o->setPrivate(CID_QABSTRACTITEMMODEL, new QoreQtQAbstractItemModel(o, model));
	 args->push(o);

	 o = new QoreObject(QC_QStyleOptionViewItem, getProgram());
	 o->setPrivate(CID_QSTYLEOPTIONVIEWITEM, new QoreQStyleOptionViewItem(option));
	 args->push(o);

	 o = new QoreObject(QC_QModelIndex, getProgram());
	 o->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
	 args->push(o);

	 return dispatch_event_bool(qore_obj, m_editorEvent, *args, &xsink);
      }

      virtual void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	 if (!m_paint) {
	    QOREQTYPE::paint(painter, option, index);
	    return;
	 }

	 ExceptionSink xsink;
	 ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

	 QoreObject *o = new QoreObject(QC_QPainter, getProgram());
	 o->setPrivate(CID_QPAINTER, new QoreQPainter(painter));
	 args->push(o);

	 o = new QoreObject(QC_QStyleOptionViewItem, getProgram());
	 o->setPrivate(CID_QSTYLEOPTIONVIEWITEM, new QoreQStyleOptionViewItem(option));
	 args->push(o);

	 o = new QoreObject(QC_QModelIndex, getProgram());
	 o->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
	 args->push(o);

	 dispatch_event(qore_obj, m_paint, *args, &xsink);
      }

      virtual void setEditorData ( QWidget * editor, const QModelIndex & index ) const {
	 if (!m_setEditorData)
	    return QOREQTYPE::setEditorData(editor, index);

	 ExceptionSink xsink;
	 ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

	 args->push(return_qobject(editor));

	 QoreObject *qw = new QoreObject(QC_QModelIndex, getProgram());
	 qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
	 args->push(qw);

	 dispatch_event(qore_obj, m_setEditorData, *args, &xsink);
      }

      virtual void setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const {
	 if (!m_setModelData) {
	    QOREQTYPE::setModelData(editor, model, index);
	    return;
	 }

	 ExceptionSink xsink;
	 ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

	 QoreObject *qw = 0;
	 if (editor) {
	    QVariant qv_ptr = editor->property("qobject");
	    qw = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
	    if (qw) 
	       qw->ref();
	 }
	 args->push(qw);

	 // FIXME: find derived class from QAbstractItemModel and instantiate qore class
	 QoreObject *o = new QoreObject(QC_QAbstractItemModel, getProgram());
	 o->setPrivate(CID_QABSTRACTITEMMODEL, new QoreQtQAbstractItemModel(o, model));
	 args->push(o);

	 qw = new QoreObject(QC_QModelIndex, getProgram());
	 qw->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
	 args->push(qw);

	 dispatch_event(qore_obj, m_setModelData, *args, &xsink);
      }

      virtual QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	 if (!m_sizeHint)
	    return QOREQTYPE::sizeHint(option, index);

	 ExceptionSink xsink;
	 ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

	 QoreObject *o = new QoreObject(QC_QStyleOptionViewItem, getProgram());
	 o->setPrivate(CID_QSTYLEOPTIONVIEWITEM, new QoreQStyleOptionViewItem(option));
	 args->push(o);
	 
	 o = new QoreObject(QC_QModelIndex, getProgram());
	 o->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
	 args->push(o);

	 ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_sizeHint, *args, &xsink), &xsink);
	 
	 if (xsink)
            return QOREQTYPE::sizeHint(option, index);
	 
         o = dynamic_cast<QoreObject *>(*rv);
	 QoreQSize *qs = o ? (QoreQSize *)o->getReferencedPrivateData(CID_QSIZE, &xsink) : 0;

         if (!qs) {
            xsink.raiseException("SIZEHINT-ERROR", "the sizeHint() method did not return a QSize object");
            return QOREQTYPE::sizeHint(option, index);
         }
         ReferenceHolder<QoreQSize> sizeHolder(qs, &xsink);
         QSize rv_qs = *(static_cast<QSize *>(qs));
         return rv_qs;
      }

      virtual void updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	 if (!m_updateEditorGeometry) {
	    QOREQTYPE::updateEditorGeometry(editor, option, index);
	    return;
	 }

	 ExceptionSink xsink;
	 ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);

	 QoreObject *o = 0;
	 if (editor) {
	    QVariant qv_ptr = editor->property("qobject");
	    o = reinterpret_cast<QoreObject *>(qv_ptr.toULongLong());
	    if (o) 
	       o->ref();
	 }
	 args->push(o);

	 o = new QoreObject(QC_QStyleOptionViewItem, getProgram());
	 o->setPrivate(CID_QSTYLEOPTIONVIEWITEM, new QoreQStyleOptionViewItem(option));
	 args->push(o);

	 o = new QoreObject(QC_QModelIndex, getProgram());
	 o->setPrivate(CID_QMODELINDEX, new QoreQModelIndex(index));
	 args->push(o);

	 dispatch_event(qore_obj, m_updateEditorGeometry, *args, &xsink);
      }
#if 0
}
#endif

