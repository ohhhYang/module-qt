/*
 QC_QDockWidget.h
 
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

#ifndef _QORE_QT_QC_QDOCKWIDGET_H

#define _QORE_QT_QC_QDOCKWIDGET_H

#include <QDockWidget>
#include "QoreAbstractQDockWidget.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QDOCKWIDGET;
DLLEXPORT extern QoreClass *QC_QDockWidget;
DLLEXPORT QoreNamespace *initQDockWidgetNS(QoreClass *);

class myQDockWidget : public QDockWidget, public QoreQWidgetExtension {
#define QOREQTYPE QDockWidget
#define MYQOREQTYPE myQDockWidget
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQDockWidget(QoreObject *obj, const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0) : QDockWidget(title, parent, flags), QoreQWidgetExtension(obj, this) {
      }
      DLLLOCAL myQDockWidget(QoreObject *obj, QWidget* parent = 0, Qt::WindowFlags flags = 0) : QDockWidget(parent, flags), QoreQWidgetExtension(obj, this) {
      }

      DLLLOCAL void parent_initStyleOption ( QStyleOptionDockWidget * option ) const {
	 initStyleOption(option);
      }
};

typedef QoreQDockWidgetBase<myQDockWidget, QoreAbstractQDockWidget> QoreQDockWidgetImpl;

class QoreQDockWidget : public QoreQDockWidgetImpl {
   public:
      DLLLOCAL QoreQDockWidget(QoreObject *obj, const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0) : QoreQDockWidgetImpl(new myQDockWidget(obj, title, parent, flags)) { }
      DLLLOCAL QoreQDockWidget(QoreObject *obj, QWidget* parent = 0, Qt::WindowFlags flags = 0) : QoreQDockWidgetImpl(new myQDockWidget(obj, parent, flags)) { }
};

typedef QoreQtQDockWidgetBase<QDockWidget, QoreAbstractQDockWidget> QoreQtQDockWidgetImpl;

class QoreQtQDockWidget : public QoreQtQDockWidgetImpl {
   public:
      DLLLOCAL QoreQtQDockWidget(QoreObject *obj, QDockWidget *qdockwidget) : QoreQtQDockWidgetImpl(obj, qdockwidget) { }
};

#endif // _QORE_QT_QC_QDOCKWIDGET_H
