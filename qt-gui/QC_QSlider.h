/*
 QC_QSlider.h
 
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

#ifndef _QORE_QC_QSLIDER_H

#define _QORE_QC_QSLIDER_H

#include "QoreAbstractQAbstractSlider.h"

#include <QSlider>

#include "qore-qt-events.h"

DLLEXPORT extern qore_classid_t CID_QSLIDER;

DLLEXPORT class QoreClass *initQSliderClass(class QoreClass *qframe);

class myQSlider : public QSlider, public QoreQWidgetExtension
{
#define QOREQTYPE QSlider
#define MYQOREQTYPE myQSlider
#include "qore-qt-metacode.h"
#include "qore-qt-widget-events.h"
#undef MYQOREQTYPE
#undef QOREQTYPE

   public:
      DLLLOCAL myQSlider(QoreObject *obj, QWidget *parent = 0) : QSlider(parent), QoreQWidgetExtension(obj, this)
      {
	 
	 //init_widget_events();
      }
      DLLLOCAL myQSlider(QoreObject *obj, Qt::Orientation orientation, QWidget *parent = 0) : QSlider(orientation, parent), QoreQWidgetExtension(obj, this)
      {
	 
	 //init_widget_events();
      }
};

typedef QoreQAbstractSliderBase<myQSlider, QoreAbstractQAbstractSlider> QoreQSliderImpl;

class QoreQSlider : public QoreQSliderImpl
{
   public:
      DLLLOCAL QoreQSlider(QoreObject *obj, QWidget *parent = 0) : QoreQSliderImpl(new myQSlider(obj, parent))
      {
      }
      DLLLOCAL QoreQSlider(QoreObject *obj, Qt::Orientation orientation, QWidget *parent = 0) : QoreQSliderImpl(new myQSlider(obj, orientation, parent))
      {
      }
};

#endif
