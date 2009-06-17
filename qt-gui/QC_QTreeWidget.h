/*
 QC_QTreeWidget.h
 
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

#ifndef _QORE_QT_QC_QTREEWIDGET_H

#define _QORE_QT_QC_QTREEWIDGET_H

#include <QTreeWidget>
#include "QoreAbstractQTreeView.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QTREEWIDGET;
DLLEXPORT extern QoreClass *QC_QTreeWidget;
DLLEXPORT QoreClass *initQTreeWidgetClass(QoreClass *);

class myQTreeWidget : public QTreeWidget, public QoreQTreeViewExtension {
#define QOREQTYPE QTreeWidget
#define MYQOREQTYPE myQTreeWidget
#include "qore-qt-metacode.h"
#include "qore-qt-qtreeview-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQTreeWidget(QoreObject *obj, QWidget* parent = 0) : QTreeWidget(parent), QoreQTreeViewExtension(obj, this) {
      }
};

typedef QoreQTreeViewBase<myQTreeWidget, QoreAbstractQTreeView> QoreQTreeWidgetImpl;

class QoreQTreeWidget : public QoreQTreeWidgetImpl {
   public:
      DLLLOCAL QoreQTreeWidget(QoreObject *obj, QWidget* parent = 0) : QoreQTreeWidgetImpl(new myQTreeWidget(obj, parent)) { }
};

typedef QoreQtQTreeViewBase<QTreeWidget, QoreAbstractQTreeView> QoreQtQTreeWidgetImpl;

class QoreQtQTreeWidget : public QoreQtQTreeWidgetImpl {
   public:
      DLLLOCAL QoreQtQTreeWidget(QoreObject *obj, QTreeWidget *qtreewidget) : QoreQtQTreeWidgetImpl(obj, qtreewidget) { }
};

#endif // _QORE_QT_QC_QTREEWIDGET_H
