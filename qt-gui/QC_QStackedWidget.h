/*
 QC_QStackedWidget.h
 
 Qore Programming Language
 
 Copyright 2003 - 2008 David Nichols
 
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

#ifndef _QORE_QT_QC_QSTACKEDWIDGET_H

#define _QORE_QT_QC_QSTACKEDWIDGET_H

#include <QStackedWidget>
#include "QoreAbstractQFrame.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QSTACKEDWIDGET;
DLLEXPORT extern QoreClass *QC_QStackedWidget;
DLLEXPORT QoreClass *initQStackedWidgetClass(QoreClass *);

class myQStackedWidget : public QStackedWidget, public QoreQWidgetExtension
{
#define QOREQTYPE QStackedWidget
#define MYQOREQTYPE myQStackedWidget
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQStackedWidget(QoreObject *obj, QWidget* parent = 0) : QStackedWidget(parent), QoreQWidgetExtension(obj, this)
      {
         
      }
};

typedef QoreQFrameBase<myQStackedWidget, QoreAbstractQFrame> QoreQStackedWidgetImpl;

class QoreQStackedWidget : public QoreQStackedWidgetImpl
{
   public:
      DLLLOCAL QoreQStackedWidget(QoreObject *obj, QWidget* parent = 0) : QoreQStackedWidgetImpl(new myQStackedWidget(obj, parent))
      {
      }
};

#endif // _QORE_QT_QC_QSTACKEDWIDGET_H
