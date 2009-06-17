/*
 QC_QMdiArea.h
 
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

#ifndef _QORE_QT_QC_QMDIAREA_H

#define _QORE_QT_QC_QMDIAREA_H

#include <QMdiArea>
#include "QoreAbstractQAbstractScrollArea.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QMDIAREA;
DLLEXPORT extern QoreClass *QC_QMdiArea;
DLLEXPORT QoreNamespace *initQMdiAreaNS(QoreClass *);

class myQMdiArea : public QMdiArea, public QoreQWidgetExtension {
#define QOREQTYPE QMdiArea
#define MYQOREQTYPE myQMdiArea
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQMdiArea(QoreObject *obj, QWidget* parent = 0) : QMdiArea(parent), QoreQWidgetExtension(obj, this) {
      }

      DLLLOCAL void pub_setupViewport(QWidget *w) {
         setupViewport(w);
      }
};

typedef QoreQAbstractScrollAreaBase<myQMdiArea, QoreAbstractQAbstractScrollArea> QoreQMdiAreaImpl;

class QoreQMdiArea : public QoreQMdiAreaImpl {
   public:
      DLLLOCAL QoreQMdiArea(QoreObject *obj, QWidget* parent = 0) : QoreQMdiAreaImpl(new myQMdiArea(obj, parent)) { }
};

typedef QoreQtQAbstractScrollAreaBase<QMdiArea, QoreAbstractQAbstractScrollArea> QoreQtQMdiAreaImpl;

class QoreQtQMdiArea : public QoreQtQMdiAreaImpl {
   public:
      DLLLOCAL QoreQtQMdiArea(QoreObject *obj, QMdiArea *qmdiarea) : QoreQtQMdiAreaImpl(obj, qmdiarea) { }
};

#endif // _QORE_QT_QC_QMDIAREA_H
