/*
 QC_QFileIconProvider.h
 
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

#ifndef _QORE_QT_QC_QFILEICONPROVIDER_H

#define _QORE_QT_QC_QFILEICONPROVIDER_H

#include <QFileIconProvider>
#include <QC_QFileInfo.h>

DLLEXPORT extern qore_classid_t CID_QFILEICONPROVIDER;
DLLEXPORT extern QoreClass *QC_QFileIconProvider;
DLLEXPORT QoreNamespace *initQFileIconProviderNS();

class QoreAbstractQFileIconProvider : public AbstractPrivateData {
   public:
      virtual QFileIconProvider *getQFileIconProvider() const = 0;
};

class myQFileIconProvider : public QFileIconProvider, public QoreQtEventDispatcher {
   private:
      const QoreMethod *m_icon, *m_type;
      QoreObject *qore_obj;

   public:
      DLLLOCAL myQFileIconProvider(QoreObject *qo) : qore_obj(qo) {
	 const QoreClass *qc = qo->getClass();
         m_icon = qc->findMethod("icon");
	 m_type = qc->findMethod("type");
      }
      
      DLLLOCAL QIcon icon ( IconType type ) const {
	 if (!m_icon)
	    return QFileIconProvider::icon(type);

	 ExceptionSink xsink;
         ReferenceHolder<QoreListNode> args(new QoreListNode(), &xsink);
	 args->push(new QoreBigIntNode(type));
	 
	 ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_icon, *args, &xsink), &xsink);
	 if (xsink)
	    return QIcon();

	 QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
         QoreQIcon *qi = o ? (QoreQIcon *)o->getReferencedPrivateData(CID_QICON, &xsink) : 0;

         if (!qi) {
            xsink.raiseException("ICON-ERROR", "the icon() method did not return a QIcon object");
            return QIcon();
         }
         ReferenceHolder<QoreQIcon> iconHolder(qi, &xsink);
         QIcon rv_qi = *(static_cast<QIcon *>(qi));
         return rv_qi;
      }

      DLLLOCAL QIcon icon ( const QFileInfo & info ) const {
	 if (!m_icon)
	    return QFileIconProvider::icon(info);

	 ExceptionSink xsink;
         ReferenceHolder<QoreListNode> args(new QoreListNode(), &xsink);
	 args->push(return_object(QC_QFileInfo, new QoreQFileInfo(info)));

	 ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_icon, *args, &xsink), &xsink);
	 if (xsink)
	    return QIcon();

	 QoreObject *o = rv && rv->getType() == NT_OBJECT ? reinterpret_cast<QoreObject *>(*rv) : 0;
         QoreQIcon *qi = o ? (QoreQIcon *)o->getReferencedPrivateData(CID_QICON, &xsink) : 0;

         if (!qi) {
            xsink.raiseException("ICON-ERROR", "the icon() method did not return a QIcon object");
            return QIcon();
         }
         ReferenceHolder<QoreQIcon> iconHolder(qi, &xsink);
         QIcon rv_qi = *(static_cast<QIcon *>(qi));
         return rv_qi;
      }

      DLLLOCAL QString type ( const QFileInfo & info ) const {
	 if (!m_icon)
	    return QFileIconProvider::type(info);

	 ExceptionSink xsink;
         ReferenceHolder<QoreListNode> args(new QoreListNode(), &xsink);
	 args->push(return_object(QC_QFileInfo, new QoreQFileInfo(info)));

	 ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_icon, *args, &xsink), &xsink);
	 if (xsink)
	    return QString();

	 return to_qstring(*rv, &xsink);
      }
};

class QoreQFileIconProvider : public QoreAbstractQFileIconProvider {
   private:
      myQFileIconProvider *fip;

   public:
      DLLLOCAL QoreQFileIconProvider(QoreObject *qo) : fip(new myQFileIconProvider(qo)) { }
      DLLLOCAL ~QoreQFileIconProvider() {
	 delete fip;
      }

      DLLLOCAL virtual QFileIconProvider *getQFileIconProvider() const {
	 return fip;
      }      
};

class QoreQtQFileIconProvider : public QoreAbstractQFileIconProvider {
   private:
      QFileIconProvider *fip;

   public:
      DLLLOCAL QoreQtQFileIconProvider(QFileIconProvider *n_fip) : fip(n_fip) {}

      DLLLOCAL virtual QFileIconProvider *getQFileIconProvider() const {
	 return fip;
      }      
};

#endif // _QORE_QT_QC_QFILEICONPROVIDER_H
