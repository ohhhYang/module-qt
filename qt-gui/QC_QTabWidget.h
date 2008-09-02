/*
 QC_QTabWidget.h
 
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

#ifndef _QORE_QT_QC_QTABWIDGET_H

#define _QORE_QT_QC_QTABWIDGET_H

#include <QTabWidget>
#include "QoreAbstractQWidget.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QTABWIDGET;
DLLEXPORT extern class QoreClass *QC_QTabWidget;

DLLEXPORT class QoreClass *initQTabWidgetClass(QoreClass *);

class myQTabWidget : public QTabWidget, public QoreQWidgetExtension
{
      friend class QoreQTabWidget;

#define QOREQTYPE QTabWidget
#define MYQOREQTYPE myQTabWidget
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQTabWidget(QoreObject *obj, QWidget* parent = 0) : QTabWidget(parent), QoreQWidgetExtension(obj, this)
      {
         
      }

      DLLLOCAL void parent_tabInserted ( int index )
      {
	 QTabWidget::tabInserted(index);
      }

      DLLLOCAL void parent_tabRemoved ( int index )
      {
	 QTabWidget::tabRemoved(index);
      }

};

typedef QoreQWidgetBase<myQTabWidget, QoreAbstractQWidget> QoreQTabWidgetImpl;

class QoreQTabWidget : public QoreQTabWidgetImpl
{
   public:
      DLLLOCAL QoreQTabWidget(QoreObject *obj, QWidget* parent = 0) : QoreQTabWidgetImpl(new myQTabWidget(obj, parent))
      {
      }
      DLLLOCAL void initStyleOption(QStyleOptionTabWidgetFrame *option) const
      {
	 qobj->initStyleOption(option);
      }
      DLLLOCAL void setTabBar(QTabBar *tb)
      {
	 qobj->setTabBar(tb);
      }
      DLLLOCAL QTabBar *tabBar() const
      {
	 return qobj->tabBar();
      }
      DLLLOCAL void tabInserted(int index)
      {
	 qobj->parent_tabInserted(index);
      }
      DLLLOCAL void tabRemoved(int index)
      {
	 qobj->parent_tabRemoved(index);
      }
};

#endif // _QORE_QT_QC_QTABWIDGET_H
