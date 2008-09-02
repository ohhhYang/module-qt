/*
  PenStyleNode.h

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

#ifndef _QORE_QT_PENSTYLENODE_H

#define _QORE_QT_PENSTYLENODE_H

#include <QPen>

DLLEXPORT extern qore_type_t NT_PENSTYLE;

class PenStyleNode : public SimpleValueQoreNode
{
   private:
      Qt::PenStyle val;

      DLLLOCAL virtual bool getAsBoolImpl() const;
      DLLLOCAL virtual int getAsIntImpl() const;
      DLLLOCAL virtual int64 getAsBigIntImpl() const;
      DLLLOCAL virtual double getAsFloatImpl() const;

   public:
      DLLLOCAL PenStyleNode(Qt::PenStyle v) : SimpleValueQoreNode(NT_PENSTYLE), val(v)
      {
      }

      DLLLOCAL ~PenStyleNode()
      {
      }

      // get the value of the type in a string context (default implementation = del = false and returns NullString)
      // if del is true, then the returned QoreString * should be deleted, if false, then it must not be
      // use the QoreStringValueHelper class (defined in QoreStringNode.h) instead of using this function directly
      DLLLOCAL virtual QoreString *getStringRepresentation(bool &del) const;

      // concatenate string representation to a QoreString (no action for complex types = default implementation)
      DLLLOCAL virtual void getStringRepresentation(QoreString &str) const;

      // get string representation (for %n and %N), foff is for multi-line formatting offset, -1 = no line breaks
      // if del is true, then the returned QoreString * should be deleted, if false, then it must not be
      // the ExceptionSink is only needed for QoreObject where a method may be executed
      // use the QoreNodeAsStringHelper class (defined in QoreStringNode.h) instead of using this function directly
      DLLLOCAL virtual QoreString *getAsString(bool &del, int foff, class ExceptionSink *xsink) const;

      DLLLOCAL virtual int getAsString(QoreString &str, int foff, class ExceptionSink *xsink) const;

      DLLLOCAL virtual class AbstractQoreNode *realCopy() const;

      // the type passed must always be equal to the current type
      DLLLOCAL virtual bool is_equal_soft(const AbstractQoreNode *v, ExceptionSink *xsink) const;

      DLLLOCAL virtual bool is_equal_hard(const AbstractQoreNode *v, ExceptionSink *xsink) const;

      // returns the type name as a c string
      DLLLOCAL virtual const char *getTypeName() const;

      DLLLOCAL Qt::PenStyle getStyle() const
      {
	 return val;
      }
};

void addPenStyleType();

static inline const PenStyleNode *test_penstyle_param(const QoreListNode *n, int i)
{
   if (!n) return 0;
   return dynamic_cast<const PenStyleNode *>(n->retrieve_entry(i));
}

#endif
