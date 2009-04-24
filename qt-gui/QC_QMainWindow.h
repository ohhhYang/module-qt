/*
 QC_QMainWindow.h
 
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

#ifndef _QORE_QT_QC_QMAINWINDOW_H

#define _QORE_QT_QC_QMAINWINDOW_H

#include <QMainWindow>
#include "QoreAbstractQMainWindow.h"
#include "qore-qt-events.h"
#include "QoreAbstractQMainWindow.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QMAINWINDOW;
DLLEXPORT extern QoreClass *QC_QMainWindow;
DLLEXPORT QoreNamespace *initQMainWindowNS(QoreClass *);

   class myQMainWindow : public QMainWindow, public QoreQWidgetExtension {
#define QOREQTYPE QMainWindow
#define MYQOREQTYPE myQMainWindow
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   private:
      const QoreMethod *m_createPopupMenu;

      void qmainwindow_init(const QoreClass *qc) {
	 m_createPopupMenu = findMethod(qc, "createPopupMenu");
      }

   protected:
      QMenu *createPopupMenu() {
	 if (!m_createPopupMenu)
	    return QMainWindow::createPopupMenu();

	 ExceptionSink xsink;
	 ReferenceHolder<AbstractQoreNode> rv(dispatch_event_intern(qore_obj, m_createPopupMenu, 0, &xsink), &xsink);
	 if (xsink)
	    return 0;

	 if (is_nothing(*rv))
	    return 0;

         if (rv->getType() != NT_OBJECT) {
            xsink.raiseException("CREATEPOPUPMENU-ERROR", "the createPopupMenu() method did not return an object derived from QMenu");
            return 0;
         }
         
         QoreObject *o = reinterpret_cast<QoreObject *>(*rv);
         QoreAbstractQMenu *qm = o ? (QoreAbstractQMenu *)o->getReferencedPrivateData(CID_QMENU, &xsink) : 0;

         if (!qm) {
            xsink.raiseException("CREATEPOPUPMENU-ERROR", "the createPopupMenu() method did not return an object derived from QMenu");
            return 0;
         }
         ReferenceHolder<AbstractPrivateData> menuHolder(qm, &xsink);
         return qm->getQMenu();
      }

   public:
      DLLLOCAL myQMainWindow(QoreObject *obj, QWidget* parent = 0, Qt::WindowFlags flags = 0) : QMainWindow(parent, flags), QoreQWidgetExtension(obj, this) {
         qmainwindow_init(obj->getClass());
      }

      DLLLOCAL QMenu *parent_createPopupMenu() {
	 return QMainWindow::createPopupMenu();	 
      }
};

typedef QoreQMainWindowBase<myQMainWindow, QoreAbstractQMainWindow> QoreQMainWindowImpl;

class QoreQMainWindow : public QoreQMainWindowImpl {
   public:
      DLLLOCAL QoreQMainWindow(QoreObject *obj, QWidget* parent = 0, Qt::WindowFlags flags = 0) : QoreQMainWindowImpl(new myQMainWindow(obj, parent, flags)) { }
};

typedef QoreQtQMainWindowBase<QMainWindow, QoreAbstractQMainWindow> QoreQtQMainWindowImpl;

class QoreQtQMainWindow : public QoreQtQMainWindowImpl {
   public:
      DLLLOCAL QoreQtQMainWindow(QoreObject *obj, QMainWindow *qmainwindow) : QoreQtQMainWindowImpl(obj, qmainwindow) { }
};

#endif // _QORE_QT_QC_QMAINWINDOW_H
