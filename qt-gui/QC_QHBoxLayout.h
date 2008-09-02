/*
 QC_QHBoxLayout.h
 
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

#ifndef _QORE_QC_QHBOXLAYOUT_H

#define _QORE_QC_QHBOXLAYOUT_H

#include "QoreAbstractQBoxLayout.h"
#include "QC_QLayout.h"

#include <QHBoxLayout>

DLLEXPORT extern qore_classid_t CID_QHBOXLAYOUT;

DLLEXPORT class QoreClass *initQHBoxLayoutClass(class QoreClass *qboxlayout);

class myQHBoxLayout : public QHBoxLayout, public QoreQLayoutExtension
{
#define QOREQTYPE QHBoxLayout
#define MYQOREQTYPE myQHBoxLayout
#include "qore-qt-metacode.h"
#include "qore-qt-qlayout-methods.h"
#undef MYQOREQTYPE
#undef QOREQTYPE
   public:
      DLLLOCAL myQHBoxLayout(QoreObject *obj) : QHBoxLayout(), QoreQLayoutExtension(obj, this)
      {
      }
      DLLLOCAL myQHBoxLayout(QoreObject *obj, QWidget *parent) : QHBoxLayout(parent), QoreQLayoutExtension(obj, this)
      {
      }
};

typedef QoreQBoxLayoutBase<myQHBoxLayout, QoreAbstractQBoxLayout> QoreQHBoxLayoutImpl;

class QoreQHBoxLayout : public QoreQHBoxLayoutImpl
{
   public:
      DLLLOCAL QoreQHBoxLayout(QoreObject *obj) : QoreQHBoxLayoutImpl(new myQHBoxLayout(obj))
      {
      }

      DLLLOCAL QoreQHBoxLayout(QoreObject *obj, QWidget *parent) : QoreQHBoxLayoutImpl(new myQHBoxLayout(obj, parent))
      {
      }
};

#endif
