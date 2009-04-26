/*
 qore_magic_holder.h
 
 Qore Programming Language
 
 Copyright 2003 - 2009 David Nichols
 
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

#ifndef _QORE_QOREMAGICHOLDER_H

#define _QORE_QOREMAGICHOLDER_H

#define QORE_MAGIC_DATA 0xbadee1deadbeef59ll

class qore_magic_holder // : protected QoreReferenceCounter 
{
   private:
      unsigned long long magic;
      AbstractQoreNode *data;

      DLLLOCAL void deref_intern() {
	 if (data) {
	    ExceptionSink xsink;
	    data->deref(&xsink);
	 } 
      }

/*
      DLLLOCAL ~qore_magic_holder() {
	 deref_intern();
      }
*/

   public:
      DLLLOCAL qore_magic_holder() : magic(QORE_MAGIC_DATA), data(0) {
      }
      DLLLOCAL qore_magic_holder(const AbstractQoreNode *d) : magic(QORE_MAGIC_DATA), data(d ? d->refSelf() : 0) {
      }
/*
      DLLLOCAL void ref() {
	 if (this && magic == QORE_MAGIC_DATA)
	    ROreference();
      }
      DLLLOCAL void deref() {
	 if (this && magic == QORE_MAGIC_DATA && ROdereference()) {
	    magic = 0;
	    delete this;
	 }
      }
*/
      DLLLOCAL void assign(const AbstractQoreNode *d) {
	 deref_intern();
	 data = d ? d->refSelf() : 0;
      }
      DLLLOCAL AbstractQoreNode *get() {
	 if (!this || magic != QORE_MAGIC_DATA || !data)
	    return 0;
	 return data->refSelf();
      }
#ifdef DEBUG
      DLLLOCAL const AbstractQoreNode *peek() const {
	 if (!this || magic != QORE_MAGIC_DATA || !data)
	    return 0;
	 return data;
      }
#endif
};

#endif
