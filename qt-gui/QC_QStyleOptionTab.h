/*
 QC_QStyleOptionTab.h
 
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

#ifndef _QORE_QT_QC_QSTYLEOPTIONTAB_H

#define _QORE_QT_QC_QSTYLEOPTIONTAB_H

#include <QStyleOptionTab>

DLLEXPORT extern qore_classid_t CID_QSTYLEOPTIONTAB;
DLLEXPORT extern class QoreClass *QC_QStyleOptionTab;

DLLEXPORT class QoreClass *initQStyleOptionTabClass(QoreClass *);

class QoreQStyleOptionTab : public AbstractPrivateData, public QStyleOptionTab
{
   public:
      DLLLOCAL QoreQStyleOptionTab() : QStyleOptionTab()
      {
      }
      DLLLOCAL QoreQStyleOptionTab(const QStyleOptionTab& other) : QStyleOptionTab(other)
      {
      }
};

#endif // _QORE_QT_QC_QSTYLEOPTIONTAB_H
