/*
 QC_QPixmapCache.cc
 
 Qore Programming Language

 Copyright (C) 2003 - 2009 Qore Technologies

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

#include "qore-qt-gui.h"

#include "QC_QPixmapCache.h"

qore_classid_t CID_QPIXMAPCACHE;
QoreClass *QC_QPixmapCache = 0;

//int cacheLimit ()
static AbstractQoreNode *f_QPixmapCache_cacheLimit(const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreBigIntNode(QPixmapCache::cacheLimit());
}

//void clear ()
static AbstractQoreNode *f_QPixmapCache_clear(const QoreListNode *params, ExceptionSink *xsink) {
   QPixmapCache::clear();
   return 0;
}

//bool find ( const QString & key, QPixmap & pm )
static AbstractQoreNode *f_QPixmapCache_find(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString key;
   if (get_qstring(p, key, xsink))
      return 0;
   p = get_param(params, 1);
   QoreQPixmap *pm = (p && p->getType() == NT_OBJECT) ? (QoreQPixmap *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPIXMAP, xsink) : 0;
   if (!pm) {
      if (!xsink->isException())
         xsink->raiseException("QPIXMAPCACHE-FIND-PARAM-ERROR", "expecting a QPixmap object as second argument to QPixmapCache::find()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> pmHolder(static_cast<AbstractPrivateData *>(pm), xsink);
   return get_bool_node(QPixmapCache::find(key, *static_cast<QPixmap *>(pm)));
}

//bool insert ( const QString & key, const QPixmap & pm )
static AbstractQoreNode *f_QPixmapCache_insert(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString key;
   if (get_qstring(p, key, xsink))
      return 0;
   p = get_param(params, 1);
   QoreQPixmap *pm = (p && p->getType() == NT_OBJECT) ? (QoreQPixmap *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPIXMAP, xsink) : 0;
   if (!pm) {
      if (!xsink->isException())
         xsink->raiseException("QPIXMAPCACHE-INSERT-PARAM-ERROR", "expecting a QPixmap object as second argument to QPixmapCache::insert()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> pmHolder(static_cast<AbstractPrivateData *>(pm), xsink);
   return get_bool_node(QPixmapCache::insert(key, *(static_cast<QPixmap *>(pm))));
}

//void remove ( const QString & key )
static AbstractQoreNode *f_QPixmapCache_remove(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   QString key;
   if (get_qstring(p, key, xsink))
      return 0;
   QPixmapCache::remove(key);
   return 0;
}

//void setCacheLimit ( int n )
static AbstractQoreNode *f_QPixmapCache_setCacheLimit(const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   int n = p ? p->getAsInt() : 0;
   QPixmapCache::setCacheLimit(n);
   return 0;
}

QoreClass *initQPixmapCacheClass() {
   QC_QPixmapCache = new QoreClass("QPixmapCache", QDOM_GUI);
   CID_QPIXMAPCACHE = QC_QPixmapCache->getID();

//   QC_QPixmapCache->setConstructor(QPIXMAPCACHE_constructor);
//   QC_QPixmapCache->setCopy((q_copy_t)QPIXMAPCACHE_copy);

   QC_QPixmapCache->addStaticMethod("cacheLimit",                  f_QPixmapCache_cacheLimit);
   QC_QPixmapCache->addStaticMethod("clear",                       f_QPixmapCache_clear);
   QC_QPixmapCache->addStaticMethod("find",                        f_QPixmapCache_find);
   QC_QPixmapCache->addStaticMethod("insert",                      f_QPixmapCache_insert);
   QC_QPixmapCache->addStaticMethod("remove",                      f_QPixmapCache_remove);
   QC_QPixmapCache->addStaticMethod("setCacheLimit",               f_QPixmapCache_setCacheLimit);

   return QC_QPixmapCache;
}
