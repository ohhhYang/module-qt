/*
 QC_QTreeView.h
 
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

#ifndef _QORE_QT_QC_QTREEVIEW_H

#define _QORE_QT_QC_QTREEVIEW_H

#include <QTreeView>
#include "QoreAbstractQTreeView.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QTREEVIEW;
DLLEXPORT extern QoreClass *QC_QTreeView;
DLLEXPORT QoreClass *initQTreeViewClass(QoreClass *);

   class myQTreeView : public QTreeView, public QoreQTreeViewExtension {
#define QOREQTYPE QTreeView
#define MYQOREQTYPE myQTreeView
#include "qore-qt-metacode.h"
#include "qore-qt-qtreeview-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQTreeView(QoreObject *obj, QWidget* parent = 0) : QTreeView(parent), QoreQTreeViewExtension(obj, this) {
      }
};

typedef QoreQTreeViewBase<myQTreeView, QoreAbstractQTreeView> QoreQTreeViewImpl;

class QoreQTreeView : public QoreQTreeViewImpl {
   public:
      DLLLOCAL QoreQTreeView(QoreObject *obj, QWidget* parent = 0) : QoreQTreeViewImpl(new myQTreeView(obj, parent)) { }
};

typedef QoreQtQTreeViewBase<QTreeView, QoreAbstractQTreeView> QoreQtQTreeViewImpl;

class QoreQtQTreeView : public QoreQtQTreeViewImpl {
   public:
      DLLLOCAL QoreQtQTreeView(QoreObject *obj, QTreeView *qtreeview) : QoreQtQTreeViewImpl(obj, qtreeview) { }
};

#endif // _QORE_QT_QC_QTREEVIEW_H
