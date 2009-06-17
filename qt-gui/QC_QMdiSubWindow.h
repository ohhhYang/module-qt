/*
 QC_QMdiSubWindow.h
 
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

#ifndef _QORE_QT_QC_QMDISUBWINDOW_H

#define _QORE_QT_QC_QMDISUBWINDOW_H

#include <QMdiSubWindow>
#include "QoreAbstractQWidget.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QMDISUBWINDOW;
DLLEXPORT extern QoreClass *QC_QMdiSubWindow;
DLLEXPORT QoreNamespace *initQMdiSubWindowNS(QoreClass *);

class myQMdiSubWindow : public QMdiSubWindow, public QoreQWidgetExtension {
#define QOREQTYPE QMdiSubWindow
#define MYQOREQTYPE myQMdiSubWindow
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQMdiSubWindow(QoreObject *obj, QWidget* parent = 0, Qt::WindowFlags flags = 0) : QMdiSubWindow(parent, flags), QoreQWidgetExtension(obj, this) {
      }
};

typedef QoreQWidgetBase<myQMdiSubWindow, QoreAbstractQWidget> QoreQMdiSubWindowImpl;

class QoreQMdiSubWindow : public QoreQMdiSubWindowImpl {
   public:
      DLLLOCAL QoreQMdiSubWindow(QoreObject *obj, QWidget* parent = 0, Qt::WindowFlags flags = 0) : QoreQMdiSubWindowImpl(new myQMdiSubWindow(obj, parent, flags)) { }
};

typedef QoreQtQWidgetBase<QMdiSubWindow, QoreAbstractQWidget> QoreQtQMdiSubWindowImpl;

class QoreQtQMdiSubWindow : public QoreQtQMdiSubWindowImpl {
   public:
      DLLLOCAL QoreQtQMdiSubWindow(QoreObject *obj, QMdiSubWindow *qmdisubwindow) : QoreQtQMdiSubWindowImpl(obj, qmdisubwindow) { }
};

#endif // _QORE_QT_QC_QMDISUBWINDOW_H
