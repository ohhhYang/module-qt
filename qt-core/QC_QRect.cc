/*
 QC_QRect.cc
 
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

#include <qore/Qore.h>

#include "QC_QRect.h"
#include "QC_QPoint.h"
#include "QC_QSize.h"

qore_classid_t CID_QRECT;
QoreClass *QC_QRect = 0;

//QRect ()
//QRect ( const QPoint & topLeft, const QPoint & bottomRight )
//QRect ( const QPoint & topLeft, const QSize & size )
//QRect ( int x, int y, int width, int height )
static void QRECT_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QRECT, new QoreQRect());
      return;
   }
   if (p && p->getType() == NT_OBJECT) {
      const QoreObject *o = reinterpret_cast<const QoreObject *>(p);
      QoreQPoint *topLeft = (QoreQPoint *)o->getReferencedPrivateData(CID_QPOINT, xsink);
      if (!topLeft) {
	 if (!xsink->isException())
	    xsink->raiseException("QRECT-CONSTRUCTOR-PARAM-ERROR", "QRect::constructor() does not know how to handle arguments of class '%s' as passed as the first argument (expecting QPoint or int)", (reinterpret_cast<const QoreObject *>(p))->getClassName());
	 return;
      }
      ReferenceHolder<AbstractPrivateData> topLeftHolder(static_cast<AbstractPrivateData *>(topLeft), xsink);
      
      o = test_object_param(params, 1);
      QoreQSize *size = o ? (QoreQSize *)o->getReferencedPrivateData(CID_QSIZE, xsink) : 0;
      if (*xsink)
	 return;
      if (!size) {
	 QoreQPoint *bottomRight = o ? (QoreQPoint *)o->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
	 if (*xsink)
	    return;
	 if (!bottomRight) {
	    xsink->raiseException("QRECT-CONSTRUCTOR-PARAM-ERROR", "QRect::constructor() does not know how to handle arguments of class '%s' as passed as the second argument", o->getClassName());
	    return;
	 }
	 ReferenceHolder<AbstractPrivateData> bottomRightHolder(static_cast<AbstractPrivateData *>(bottomRight), xsink);
	 self->setPrivate(CID_QRECT, new QoreQRect(*(static_cast<QPoint *>(topLeft)), *(static_cast<QPoint *>(bottomRight))));
	 return;
      }
      ReferenceHolder<AbstractPrivateData> sizeHolder(static_cast<AbstractPrivateData *>(size), xsink);
      self->setPrivate(CID_QRECT, new QoreQRect(*(static_cast<QPoint *>(topLeft)), *(static_cast<QSize *>(size))));
      return;
   }
   int x = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int y = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int width = p ? p->getAsInt() : 0;
   p = get_param(params, 3);
   int height = p ? p->getAsInt() : 0;
   self->setPrivate(CID_QRECT, new QoreQRect(x, y, width, height));
   return;
}

static void QRECT_copy(class QoreObject *self, class QoreObject *old, class QoreQRect *qr, ExceptionSink *xsink)
{
   self->setPrivate(CID_QRECT, new QoreQRect(*qr));
}

//void adjust ( int dx1, int dy1, int dx2, int dy2 )
static AbstractQoreNode *QRECT_adjust(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int dx1 = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int dy1 = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int dx2 = p ? p->getAsInt() : 0;
   p = get_param(params, 3);
   int dy2 = p ? p->getAsInt() : 0;
   qr->adjust(dx1, dy1, dx2, dy2);
   return 0;
}

//QRect adjusted ( int dx1, int dy1, int dx2, int dy2 ) const
static AbstractQoreNode *QRECT_adjusted(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int dx1 = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int dy1 = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int dx2 = p ? p->getAsInt() : 0;
   p = get_param(params, 3);
   int dy2 = p ? p->getAsInt() : 0;

   QoreQRect *q_qr = new QoreQRect(qr->adjusted(dx1, dy1, dx2, dy2));
   QoreObject *o_qr = new QoreObject(self->getClass(CID_QRECT), getProgram());
   o_qr->setPrivate(CID_QRECT, q_qr);
   return o_qr;
}

//int bottom () const
static AbstractQoreNode *QRECT_bottom(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qr->bottom());
}

//QPoint bottomLeft () const
static AbstractQoreNode *QRECT_bottomLeft(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{

   QoreQPoint *q_qp = new QoreQPoint(qr->bottomLeft());
   QoreObject *o_qp = new QoreObject(QC_QPoint, getProgram());
   o_qp->setPrivate(CID_QPOINT, q_qp);
   return o_qp;
}

//QPoint bottomRight () const
static AbstractQoreNode *QRECT_bottomRight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{

   QoreQPoint *q_qp = new QoreQPoint(qr->bottomRight());
   QoreObject *o_qp = new QoreObject(QC_QPoint, getProgram());
   o_qp->setPrivate(CID_QPOINT, q_qp);
   return o_qp;
}

//QPoint center () const
static AbstractQoreNode *QRECT_center(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{

   QoreQPoint *q_qp = new QoreQPoint(qr->center());
   QoreObject *o_qp = new QoreObject(QC_QPoint, getProgram());
   o_qp->setPrivate(CID_QPOINT, q_qp);
   return o_qp;
}

//bool contains ( const QPoint & point, bool proper = false ) const
//bool contains ( int x, int y, bool proper ) const
//bool contains ( int x, int y ) const
//bool contains ( const QRect & rectangle, bool proper = false ) const
static AbstractQoreNode *QRECT_contains(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      const QoreObject *o = reinterpret_cast<const QoreObject *>(p);
      QoreQRect *rectangle = (QoreQRect *)o->getReferencedPrivateData(CID_QRECT, xsink);
      if (!rectangle) {
         QoreQPoint *point = (QoreQPoint *)o->getReferencedPrivateData(CID_QPOINT, xsink);
         if (!point) {
            if (!xsink->isException())
               xsink->raiseException("QRECT-CONTAINS-PARAM-ERROR", "QRect::contains() does not know how to handle arguments of class '%s' as passed as the first argument", o->getClassName());
            return 0;
         }
         ReferenceHolder<AbstractPrivateData> pointHolder(static_cast<AbstractPrivateData *>(point), xsink);
         p = get_param(params, 1);
         bool proper = p ? p->getAsBool() : false;
         return get_bool_node(qr->contains(*(static_cast<QPoint *>(point)), proper));
      }
      ReferenceHolder<AbstractPrivateData> rectangleHolder(static_cast<AbstractPrivateData *>(rectangle), xsink);
      p = get_param(params, 1);
      bool proper = p ? p->getAsBool() : false;
      return get_bool_node(qr->contains(*(static_cast<QRect *>(rectangle)), proper));
   }
   int x = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int y = p ? p->getAsInt() : 0;
   if (num_params(params) == 2)
      return get_bool_node(qr->contains(x, y));

   p = get_param(params, 2);
   bool proper = p ? p->getAsBool() : false;
   return get_bool_node(qr->contains(x, y, proper));
}

//void getCoords ( int * x1, int * y1, int * x2, int * y2 ) const
static AbstractQoreNode *QRECT_getCoords(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   int x1, y1, x2, y2;
   qr->getCoords(&x1, &y1, &x2, &y2);

   QoreListNode *l = new QoreListNode();
   l->push(new QoreBigIntNode(x1));
   l->push(new QoreBigIntNode(y1));
   l->push(new QoreBigIntNode(x2));
   l->push(new QoreBigIntNode(y2));
   return l;
}

//void getRect ( int * x, int * y, int * width, int * height ) const
static AbstractQoreNode *QRECT_getRect(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   int x, y, width, height;
   qr->getCoords(&x, &y, &width, &height);

   QoreListNode *l = new QoreListNode();
   l->push(new QoreBigIntNode(x));
   l->push(new QoreBigIntNode(y));
   l->push(new QoreBigIntNode(width));
   l->push(new QoreBigIntNode(height));
   return l;
}

//int height () const
static AbstractQoreNode *QRECT_height(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qr->height());
}

//QRect intersected ( const QRect & rectangle ) const
static AbstractQoreNode *QRECT_intersected(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQRect *rectangle = p ? (QoreQRect *)p->getReferencedPrivateData(CID_QRECT, xsink) : 0;
   if (!p || !rectangle)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-INTERSECTED-PARAM-ERROR", "expecting a QRect object as first argument to QRect::intersected()");
      return 0;
   }
   ReferenceHolder<QoreQRect> holder(rectangle, xsink);

   QoreQRect *q_qr = new QoreQRect(qr->intersected(*((QRect *)rectangle)));
   QoreObject *o_qr = new QoreObject(self->getClass(CID_QRECT), getProgram());
   o_qr->setPrivate(CID_QRECT, q_qr);
   return o_qr;
}

//bool intersects ( const QRect & rectangle ) const
static AbstractQoreNode *QRECT_intersects(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQRect *rectangle = p ? (QoreQRect *)p->getReferencedPrivateData(CID_QRECT, xsink) : 0;
   if (!p || !rectangle)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-INTERSECTS-PARAM-ERROR", "expecting a QRect object as first argument to QRect::intersects()");
      return 0;
   }
   ReferenceHolder<QoreQRect> holder(rectangle, xsink);
   return get_bool_node(qr->intersects(*((QRect *)rectangle)));
}

//bool isEmpty () const
static AbstractQoreNode *QRECT_isEmpty(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qr->isEmpty());
}

//bool isNull () const
static AbstractQoreNode *QRECT_isNull(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qr->isNull());
}

//bool isValid () const
static AbstractQoreNode *QRECT_isValid(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qr->isValid());
}

//int left () const
static AbstractQoreNode *QRECT_left(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qr->left());
}

//void moveBottom ( int y )
static AbstractQoreNode *QRECT_moveBottom(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int y = p ? p->getAsInt() : 0;
   qr->moveBottom(y);
   return 0;
}

//void moveBottomLeft ( const QPoint & position )
static AbstractQoreNode *QRECT_moveBottomLeft(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-MOVEBOTTOMLEFT-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::moveBottomLeft()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->moveBottomLeft(*((QPoint *)position));
   return 0;
}

//void moveBottomRight ( const QPoint & position )
static AbstractQoreNode *QRECT_moveBottomRight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-MOVEBOTTOMRIGHT-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::moveBottomRight()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->moveBottomRight(*((QPoint *)position));
   return 0;
}

//void moveCenter ( const QPoint & position )
static AbstractQoreNode *QRECT_moveCenter(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-MOVECENTER-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::moveCenter()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->moveCenter(*((QPoint *)position));
   return 0;
}

//void moveLeft ( int x )
static AbstractQoreNode *QRECT_moveLeft(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int x = p ? p->getAsInt() : 0;
   qr->moveLeft(x);
   return 0;
}

//void moveRight ( int x )
static AbstractQoreNode *QRECT_moveRight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int x = p ? p->getAsInt() : 0;
   qr->moveRight(x);
   return 0;
}

//void moveTo ( const QPoint & position )
//void moveTo ( int x, int y )
static AbstractQoreNode *QRECT_moveTo(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQPoint *position = (QoreQPoint *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QPOINT, xsink);
      if (!position)
      {
	 if (!xsink->isException())
	    xsink->raiseException("QRECT-MOVETO-PARAM-ERROR", "QRect::moveTo() cannot handle arguments of class '%s'", (reinterpret_cast<const QoreObject *>(p))->getClassName());
	 return 0;
      }
      ReferenceHolder<QoreQPoint> holder(position, xsink);
      qr->moveTo(*((QPoint *)position));
      return 0;
   }

   int x = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int y = p ? p->getAsInt() : 0;
   qr->moveTo(x, y);
   return 0;
}

//void moveTop ( int y )
static AbstractQoreNode *QRECT_moveTop(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int y = p ? p->getAsInt() : 0;
   qr->moveTop(y);
   return 0;
}

//void moveTopLeft ( const QPoint & position )
static AbstractQoreNode *QRECT_moveTopLeft(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-MOVETOPLEFT-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::moveTopLeft()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->moveTopLeft(*((QPoint *)position));
   return 0;
}

//void moveTopRight ( const QPoint & position )
static AbstractQoreNode *QRECT_moveTopRight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-MOVETOPRIGHT-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::moveTopRight()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->moveTopRight(*((QPoint *)position));
   return 0;
}

//QRect normalized () const
static AbstractQoreNode *QRECT_normalized(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{

   QoreQRect *q_qr = new QoreQRect(qr->normalized());
   QoreObject *o_qr = new QoreObject(self->getClass(CID_QRECT), getProgram());
   o_qr->setPrivate(CID_QRECT, q_qr);
   return o_qr;
}

//int right () const
static AbstractQoreNode *QRECT_right(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qr->right());
}

//void setBottom ( int y )
static AbstractQoreNode *QRECT_setBottom(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int y = p ? p->getAsInt() : 0;
   qr->setBottom(y);
   return 0;
}

//void setBottomLeft ( const QPoint & position )
static AbstractQoreNode *QRECT_setBottomLeft(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-SETBOTTOMLEFT-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::setBottomLeft()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->setBottomLeft(*((QPoint *)position));
   return 0;
}

//void setBottomRight ( const QPoint & position )
static AbstractQoreNode *QRECT_setBottomRight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-SETBOTTOMRIGHT-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::setBottomRight()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->setBottomRight(*((QPoint *)position));
   return 0;
}

//void setCoords ( int x1, int y1, int x2, int y2 )
static AbstractQoreNode *QRECT_setCoords(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int x1 = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int y1 = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int x2 = p ? p->getAsInt() : 0;
   p = get_param(params, 3);
   int y2 = p ? p->getAsInt() : 0;
   qr->setCoords(x1, y1, x2, y2);
   return 0;
}

//void setHeight ( int height )
static AbstractQoreNode *QRECT_setHeight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int height = p ? p->getAsInt() : 0;
   qr->setHeight(height);
   return 0;
}

//void setLeft ( int x )
static AbstractQoreNode *QRECT_setLeft(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int x = p ? p->getAsInt() : 0;
   qr->setLeft(x);
   return 0;
}

//void setRect ( int x, int y, int width, int height )
static AbstractQoreNode *QRECT_setRect(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int x = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int y = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int width = p ? p->getAsInt() : 0;
   p = get_param(params, 3);
   int height = p ? p->getAsInt() : 0;
   qr->setRect(x, y, width, height);
   return 0;
}

//void setRight ( int x )
static AbstractQoreNode *QRECT_setRight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int x = p ? p->getAsInt() : 0;
   qr->setRight(x);
   return 0;
}

//void setSize ( const QSize & size )
static AbstractQoreNode *QRECT_setSize(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQSize *size = p ? (QoreQSize *)p->getReferencedPrivateData(CID_QSIZE, xsink) : 0;
   if (!size) {
      if (!xsink->isException())
         xsink->raiseException("QRECT-SETSIZE-PARAM-ERROR", "expecting a QSize object as first argument to QRect::setSize()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> sizeHolder(static_cast<AbstractPrivateData *>(size), xsink);
   qr->setSize(*(static_cast<QSize *>(size)));
   return 0;
}

//void setTop ( int y )
static AbstractQoreNode *QRECT_setTop(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int y = p ? p->getAsInt() : 0;
   qr->setTop(y);
   return 0;
}

//void setTopLeft ( const QPoint & position )
static AbstractQoreNode *QRECT_setTopLeft(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-SETTOPLEFT-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::setTopLeft()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->setTopLeft(*((QPoint *)position));
   return 0;
}

//void setTopRight ( const QPoint & position )
static AbstractQoreNode *QRECT_setTopRight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQPoint *position = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!p || !position)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-SETTOPRIGHT-PARAM-ERROR", "expecting a QPoint object as first argument to QRect::setTopRight()");
      return 0;
   }
   ReferenceHolder<QoreQPoint> holder(position, xsink);
   qr->setTopRight(*((QPoint *)position));
   return 0;
}

//void setWidth ( int width )
static AbstractQoreNode *QRECT_setWidth(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int width = p ? p->getAsInt() : 0;
   qr->setWidth(width);
   return 0;
}

//void setX ( int x )
static AbstractQoreNode *QRECT_setX(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int x = p ? p->getAsInt() : 0;
   qr->setX(x);
   return 0;
}

//void setY ( int y )
static AbstractQoreNode *QRECT_setY(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int y = p ? p->getAsInt() : 0;
   qr->setY(y);
   return 0;
}

//QSize size () const
static AbstractQoreNode *QRECT_size(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qs = new QoreObject(QC_QSize, getProgram());
   QoreQSize *q_qs = new QoreQSize(qr->size());
   o_qs->setPrivate(CID_QSIZE, q_qs);
   return o_qs;
}

//int top () const
static AbstractQoreNode *QRECT_top(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qr->top());
}

//QPoint topLeft () const
static AbstractQoreNode *QRECT_topLeft(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{

   QoreQPoint *q_qp = new QoreQPoint(qr->topLeft());
   QoreObject *o_qp = new QoreObject(QC_QPoint, getProgram());
   o_qp->setPrivate(CID_QPOINT, q_qp);
   return o_qp;
}

//QPoint topRight () const
static AbstractQoreNode *QRECT_topRight(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{

   QoreQPoint *q_qp = new QoreQPoint(qr->topRight());
   QoreObject *o_qp = new QoreObject(QC_QPoint, getProgram());
   o_qp->setPrivate(CID_QPOINT, q_qp);
   return o_qp;
}

//void translate ( const QPoint & offset )
//void translate ( int dx, int dy )
static AbstractQoreNode *QRECT_translate(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQPoint *offset = (QoreQPoint *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QPOINT, xsink);
      if (!offset)
      {
	 if (!xsink->isException())
	    xsink->raiseException("QRECT-TRANSLATE-PARAM-ERROR", "QRect::translate() cannot handle arguments of class '%s'", (reinterpret_cast<const QoreObject *>(p))->getClassName());
	 return 0;
      }
      ReferenceHolder<QoreQPoint> holder(offset, xsink);
      qr->translate(*((QPoint *)offset));
      return 0;
   }

   int dx = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int dy = p ? p->getAsInt() : 0;
   qr->translate(dx, dy);
   return 0;
}

//QRect translated ( int dx, int dy ) const
//QRect translated ( const QPoint & offset ) const
static AbstractQoreNode *QRECT_translated(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQPoint *offset = (QoreQPoint *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QPOINT, xsink);
      if (!offset) {
         if (!xsink->isException())
            xsink->raiseException("QRECT-TRANSLATED-PARAM-ERROR", "QRect::translated() does not know how to handle arguments of class '%s' as passed as the first argument", (reinterpret_cast<const QoreObject *>(p))->getClassName());
         return 0;
      }
      ReferenceHolder<QoreQPoint> offsetHolder(offset, xsink);
      QoreQRect *q_qr = new QoreQRect(qr->translated(*((QPoint *)offset)));
      QoreObject *o_qr = new QoreObject(self->getClass(CID_QRECT), getProgram());
      o_qr->setPrivate(CID_QRECT, q_qr);
      return o_qr;
   }
   int dx = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int dy = p ? p->getAsInt() : 0;
   QoreQRect *q_qr = new QoreQRect(qr->translated(dx, dy));
   QoreObject *o_qr = new QoreObject(self->getClass(CID_QRECT), getProgram());
   o_qr->setPrivate(CID_QRECT, q_qr);
   return o_qr;
}

//QRect united ( const QRect & rectangle ) const
static AbstractQoreNode *QRECT_united(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQRect *rectangle = p ? (QoreQRect *)p->getReferencedPrivateData(CID_QRECT, xsink) : 0;
   if (!p || !rectangle)
   {
      if (!xsink->isException())
         xsink->raiseException("QRECT-UNITED-PARAM-ERROR", "expecting a QRect object as first argument to QRect::united()");
      return 0;
   }
   ReferenceHolder<QoreQRect> holder(rectangle, xsink);

   QoreQRect *q_qr = new QoreQRect(qr->united(*((QRect *)rectangle)));
   QoreObject *o_qr = new QoreObject(self->getClass(CID_QRECT), getProgram());
   o_qr->setPrivate(CID_QRECT, q_qr);
   return o_qr;
}

//int width () const
static AbstractQoreNode *QRECT_width(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qr->width());
}

//int x () const
static AbstractQoreNode *QRECT_x(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qr->x());
}

//int y () const
static AbstractQoreNode *QRECT_y(QoreObject *self, QoreQRect *qr, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qr->y());
}

class QoreClass *initQRectClass()
{
   QORE_TRACE("initQRectClass()");
   
   QC_QRect = new QoreClass("QRect", QDOM_GUI);
   CID_QRECT = QC_QRect->getID();
   QC_QRect->setConstructor(QRECT_constructor);
   QC_QRect->setCopy((q_copy_t)QRECT_copy);

   QC_QRect->addMethod("adjust",                      (q_method_t)QRECT_adjust);
   QC_QRect->addMethod("adjusted",                    (q_method_t)QRECT_adjusted);
   QC_QRect->addMethod("bottom",                      (q_method_t)QRECT_bottom);
   QC_QRect->addMethod("bottomLeft",                  (q_method_t)QRECT_bottomLeft);
   QC_QRect->addMethod("bottomRight",                 (q_method_t)QRECT_bottomRight);
   QC_QRect->addMethod("center",                      (q_method_t)QRECT_center);
   QC_QRect->addMethod("contains",                    (q_method_t)QRECT_contains);
   QC_QRect->addMethod("getCoords",                   (q_method_t)QRECT_getCoords);
   QC_QRect->addMethod("getRect",                     (q_method_t)QRECT_getRect);
   QC_QRect->addMethod("height",                      (q_method_t)QRECT_height);
   QC_QRect->addMethod("intersected",                 (q_method_t)QRECT_intersected);
   QC_QRect->addMethod("intersects",                  (q_method_t)QRECT_intersects);
   QC_QRect->addMethod("isEmpty",                     (q_method_t)QRECT_isEmpty);
   QC_QRect->addMethod("isNull",                      (q_method_t)QRECT_isNull);
   QC_QRect->addMethod("isValid",                     (q_method_t)QRECT_isValid);
   QC_QRect->addMethod("left",                        (q_method_t)QRECT_left);
   QC_QRect->addMethod("moveBottom",                  (q_method_t)QRECT_moveBottom);
   QC_QRect->addMethod("moveBottomLeft",              (q_method_t)QRECT_moveBottomLeft);
   QC_QRect->addMethod("moveBottomRight",             (q_method_t)QRECT_moveBottomRight);
   QC_QRect->addMethod("moveCenter",                  (q_method_t)QRECT_moveCenter);
   QC_QRect->addMethod("moveLeft",                    (q_method_t)QRECT_moveLeft);
   QC_QRect->addMethod("moveRight",                   (q_method_t)QRECT_moveRight);
   QC_QRect->addMethod("moveTo",                      (q_method_t)QRECT_moveTo);
   QC_QRect->addMethod("moveTop",                     (q_method_t)QRECT_moveTop);
   QC_QRect->addMethod("moveTopLeft",                 (q_method_t)QRECT_moveTopLeft);
   QC_QRect->addMethod("moveTopRight",                (q_method_t)QRECT_moveTopRight);
   QC_QRect->addMethod("normalized",                  (q_method_t)QRECT_normalized);
   QC_QRect->addMethod("right",                       (q_method_t)QRECT_right);
   QC_QRect->addMethod("setBottom",                   (q_method_t)QRECT_setBottom);
   QC_QRect->addMethod("setBottomLeft",               (q_method_t)QRECT_setBottomLeft);
   QC_QRect->addMethod("setBottomRight",              (q_method_t)QRECT_setBottomRight);
   QC_QRect->addMethod("setCoords",                   (q_method_t)QRECT_setCoords);
   QC_QRect->addMethod("setHeight",                   (q_method_t)QRECT_setHeight);
   QC_QRect->addMethod("setLeft",                     (q_method_t)QRECT_setLeft);
   QC_QRect->addMethod("setRect",                     (q_method_t)QRECT_setRect);
   QC_QRect->addMethod("setRight",                    (q_method_t)QRECT_setRight);
   QC_QRect->addMethod("setSize",                     (q_method_t)QRECT_setSize);
   QC_QRect->addMethod("setTop",                      (q_method_t)QRECT_setTop);
   QC_QRect->addMethod("setTopLeft",                  (q_method_t)QRECT_setTopLeft);
   QC_QRect->addMethod("setTopRight",                 (q_method_t)QRECT_setTopRight);
   QC_QRect->addMethod("setWidth",                    (q_method_t)QRECT_setWidth);
   QC_QRect->addMethod("setX",                        (q_method_t)QRECT_setX);
   QC_QRect->addMethod("setY",                        (q_method_t)QRECT_setY);
   QC_QRect->addMethod("size",                        (q_method_t)QRECT_size);
   QC_QRect->addMethod("top",                         (q_method_t)QRECT_top);
   QC_QRect->addMethod("topLeft",                     (q_method_t)QRECT_topLeft);
   QC_QRect->addMethod("topRight",                    (q_method_t)QRECT_topRight);
   QC_QRect->addMethod("translate",                   (q_method_t)QRECT_translate);
   QC_QRect->addMethod("translated",                  (q_method_t)QRECT_translated);
   QC_QRect->addMethod("united",                      (q_method_t)QRECT_united);
   QC_QRect->addMethod("width",                       (q_method_t)QRECT_width);
   QC_QRect->addMethod("x",                           (q_method_t)QRECT_x);
   QC_QRect->addMethod("y",                           (q_method_t)QRECT_y);


   return QC_QRect;
}
