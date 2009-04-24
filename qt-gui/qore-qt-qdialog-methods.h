
#include "qore-qt-widget-events.h"

#if 0
class T {
#endif

   public:
      DLLLOCAL virtual void accept() { 
	 if (!m_accept) {
	    QOREQTYPE::accept();
	    return;
	 }

	 dispatch_event(qore_obj, m_accept);
      }

      DLLLOCAL virtual void done(int r) {
	 if (!m_done) {
	    QOREQTYPE::done(r);
	    return;
	 }

	 ExceptionSink xsink;
	 ReferenceHolder<QoreListNode> args(new QoreListNode, &xsink);
	 args->push(new QoreBigIntNode(r));

	 dispatch_event_intern(qore_obj, m_done, *args, &xsink);
      }

      DLLLOCAL virtual void reject() {
	 if (!m_reject) {
	    QOREQTYPE::reject();
	    return;
	 }

	 dispatch_event(qore_obj, m_reject);
      }

      DLLLOCAL virtual void parent_accept() {
	 QOREQTYPE::accept();
      }

      DLLLOCAL virtual void parent_done(int r) {
	 QOREQTYPE::done(r);
      }

      DLLLOCAL virtual void parent_reject() {
	 QOREQTYPE::reject();
      }

#if 0
}
#endif

