/*
 QC_QTabBar.h
 
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

#ifndef _QORE_QT_QC_QTABBAR_H

#define _QORE_QT_QC_QTABBAR_H

#include <QTabBar>
#include "QoreAbstractQTabBar.h"
#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QTABBAR;
DLLEXPORT extern class QoreClass *QC_QTabBar;

DLLEXPORT class QoreClass *initQTabBarClass(QoreClass *);

class myQTabBar : public QTabBar, public QoreQWidgetExtension
{
#define QOREQTYPE QTabBar
#define MYQOREQTYPE myQTabBar
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQTabBar(QoreObject *obj, QWidget* parent = 0) : QTabBar(parent), QoreQWidgetExtension(obj, this)
      {
         
      }

      void parent_initStyleOption ( QStyleOptionTab * option, int tabIndex ) const
      {
         QTabBar::initStyleOption(option, tabIndex);
      }

      void parent_tabInserted ( int index )
      {
         QTabBar::tabInserted(index);
      }

      void parent_tabLayoutChange ()
      {
         QTabBar::tabLayoutChange();
      }

      void parent_tabRemoved ( int index )
      {
         QTabBar::tabRemoved(index);
      }

      QSize parent_tabSizeHint ( int index ) const
      {
         return QTabBar::tabSizeHint(index);
      }
};

typedef QoreQTabBarBase<myQTabBar, QoreAbstractQTabBar> QoreQTabBarImpl;

class QoreQTabBar : public QoreQTabBarImpl
{
   public:
      DLLLOCAL QoreQTabBar(QoreObject *obj, QWidget* parent = 0) : QoreQTabBarImpl(new myQTabBar(obj, parent))
      {
      }
};

typedef QoreQtQTabBarBase<QTabBar, QoreAbstractQTabBar> QoreQtQTabBarImpl;

class QoreQtQTabBar : public QoreQtQTabBarImpl
{
   public:
      DLLLOCAL QoreQtQTabBar(QoreObject *obj, QTabBar *qtabbar) : QoreQtQTabBarImpl(obj, qtabbar)
      {
      }
};

#endif // _QORE_QT_QC_QTABBAR_H
