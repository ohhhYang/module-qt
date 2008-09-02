/*
 QC_QFocusEvent.h
 
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

#ifndef _QORE_QT_QC_QFOCUSEVENT_H

#define _QORE_QT_QC_QFOCUSEVENT_H

#include <QFocusEvent>

DLLEXPORT extern qore_classid_t CID_QFOCUSEVENT;
DLLEXPORT extern class QoreClass *QC_QFocusEvent;

DLLEXPORT class QoreClass *initQFocusEventClass(QoreClass *);

class QoreQFocusEvent : public AbstractPrivateData, public QFocusEvent
{
   public:
      DLLLOCAL QoreQFocusEvent(Type type, Qt::FocusReason reason = Qt::OtherFocusReason) : QFocusEvent(type, reason)
      {
      }
      DLLLOCAL QoreQFocusEvent(const QFocusEvent &event) : QFocusEvent(event)
      {
      }
};

#endif // _QORE_QT_QC_QFOCUSEVENT_H
