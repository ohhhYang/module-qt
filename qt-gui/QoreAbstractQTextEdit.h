/*
 QoreAbstractQTextEdit.h
 
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

#ifndef _QORE_QT_QOREABSTRACTQTEXTEDIT_H

#define _QORE_QT_QOREABSTRACTQTEXTEDIT_H

#include "QoreAbstractQAbstractScrollArea.h"

class QoreAbstractQTextEdit : public QoreAbstractQAbstractScrollArea
{
   public:
      DLLLOCAL virtual QTextEdit *getQTextEdit() const = 0;
};

template<typename T, typename V>
class QoreQTextEditBase : public QoreQAbstractScrollAreaBase<T, V>
{
   public:
      DLLLOCAL QoreQTextEditBase(T *qo) : QoreQAbstractScrollAreaBase<T, V>(qo)
      {
      }
      DLLLOCAL virtual QTextEdit *getQTextEdit() const
      {
         return &(*this->qobj);
      }
};

template<typename T, typename V>
class QoreQtQTextEditBase : public QoreQtQAbstractScrollAreaBase<T, V>
{
   public:
      DLLLOCAL QoreQtQTextEditBase(QoreObject *obj, T *qo) : QoreQtQAbstractScrollAreaBase<T, V>(obj, qo)
      {
      }

      DLLLOCAL virtual QTextEdit *getQTextEdit() const
      {
         return this->qobj;
      }
};

#endif  // _QORE_QT_QOREABSTRACTQTEXTEDIT_H
