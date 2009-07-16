/*
 QC_QRadialGradient.cc
 
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

#include "QC_QRadialGradient.h"

qore_classid_t CID_QRADIALGRADIENT;
QoreClass *QC_QRadialGradient = 0;

//QRadialGradient ()
//QRadialGradient ( const QPointF & center, qreal radius, const QPointF & focalPoint )
//QRadialGradient ( qreal cx, qreal cy, qreal radius, qreal fx, qreal fy )
//QRadialGradient ( const QPointF & center, qreal radius )
//QRadialGradient ( qreal cx, qreal cy, qreal radius )
static void QRADIALGRADIENT_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QRADIALGRADIENT, new QoreQRadialGradient());
      return;
   }
   
   if (p && p->getType() == NT_OBJECT) {
      QoreQPointF *center = (QoreQPointF *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPOINTF, xsink);
      if (!center) {
          if (!xsink->isException())
              xsink->raiseException("QRADIALGRADIENT-CONSTRUCTOR-PARAM-ERROR", "QRadialGradient::constructor() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
          return;
      }
      ReferenceHolder<AbstractPrivateData> centerHolder(static_cast<AbstractPrivateData *>(center), xsink);
      p = get_param(params, 1);
      qreal radius = p ? p->getAsFloat() : 0.0;
      
      if (params->size() == 2)
      {
          self->setPrivate(CID_QRADIALGRADIENT, new QoreQRadialGradient(*(static_cast<QPointF *>(center)), radius));
          return;
      }
      p = get_param(params, 2);
      QoreQPointF *focalPoint = (p && p->getType() == NT_OBJECT) ? (QoreQPointF *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPOINTF, xsink) : 0;
      if (!focalPoint) {
          if (!xsink->isException())
              xsink->raiseException("QRADIALGRADIENT-CONSTRUCTOR-PARAM-ERROR", "this version of QRadialGradient::constructor() expects an object derived from QPointF as the third argument");
          return;
      }
      ReferenceHolder<AbstractPrivateData> focalPointHolder(static_cast<AbstractPrivateData *>(focalPoint), xsink);
      self->setPrivate(CID_QRADIALGRADIENT, new QoreQRadialGradient(*(static_cast<QPointF *>(center)), radius, *(static_cast<QPointF *>(focalPoint))));
      return;
  }

   p = get_param(params, 0);
   qreal cx = p ? p->getAsFloat() : 0.0;
   p = get_param(params, 1);
   qreal cy = p ? p->getAsFloat() : 0.0;
   p = get_param(params, 2);
   qreal radius = p ? p->getAsFloat() : 0.0;
   if (params->size() == 3)
   {
      self->setPrivate(CID_QRADIALGRADIENT, new QoreQRadialGradient(cx, cy, radius));
      return;
   }
   p = get_param(params, 3);
   qreal fx = p ? p->getAsFloat() : 0.0;
   p = get_param(params, 4);
   qreal fy = p ? p->getAsFloat() : 0.0;
   self->setPrivate(CID_QRADIALGRADIENT, new QoreQRadialGradient(cx, cy, radius, fx, fy));
   return;
}

static void QRADIALGRADIENT_copy(QoreObject *self, QoreObject *old, QoreQRadialGradient *qrg, ExceptionSink *xsink) {
   xsink->raiseException("QRADIALGRADIENT-COPY-ERROR", "objects of this class cannot be copied");
}

//QPointF center () const
static AbstractQoreNode *QRADIALGRADIENT_center(QoreObject *self, QoreQRadialGradient *qrg, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QPointF, new QoreQPointF(qrg->center()));
}

//QPointF focalPoint () const
static AbstractQoreNode *QRADIALGRADIENT_focalPoint(QoreObject *self, QoreQRadialGradient *qrg, const QoreListNode *params, ExceptionSink *xsink) {
   return return_object(QC_QPointF, new QoreQPointF(qrg->focalPoint()));
}

//qreal radius () const
static AbstractQoreNode *QRADIALGRADIENT_radius(QoreObject *self, QoreQRadialGradient *qrg, const QoreListNode *params, ExceptionSink *xsink) {
   return new QoreFloatNode(qrg->radius());
}

//void setCenter ( const QPointF & center )
//void setCenter ( qreal x, qreal y )
static AbstractQoreNode *QRADIALGRADIENT_setCenter(QoreObject *self, QoreQRadialGradient *qrg, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQPointF *center = (QoreQPointF *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPOINTF, xsink);
      if (!center) {
         if (!xsink->isException())
            xsink->raiseException("QRADIALGRADIENT-SETCENTER-PARAM-ERROR", "QRadialGradient::setCenter() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
         return 0;
      }
      ReferenceHolder<AbstractPrivateData> centerHolder(static_cast<AbstractPrivateData *>(center), xsink);
      qrg->setCenter(*(static_cast<QPointF *>(center)));
      return 0;
   }
   qreal x = p ? p->getAsFloat() : 0.0;
   p = get_param(params, 1);
   qreal y = p ? p->getAsFloat() : 0.0;
   qrg->setCenter(x, y);
   return 0;
}

//void setFocalPoint ( const QPointF & focalPoint )
//void setFocalPoint ( qreal x, qreal y )
static AbstractQoreNode *QRADIALGRADIENT_setFocalPoint(QoreObject *self, QoreQRadialGradient *qrg, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   if (p && p->getType() == NT_OBJECT) {
      QoreQPointF *focalPoint = (QoreQPointF *)reinterpret_cast<const QoreObject *>(p)->getReferencedPrivateData(CID_QPOINTF, xsink);
      if (!focalPoint) {
         if (!xsink->isException())
            xsink->raiseException("QRADIALGRADIENT-SETFOCALPOINT-PARAM-ERROR", "QRadialGradient::setFocalPoint() does not know how to handle arguments of class '%s' as passed as the first argument", reinterpret_cast<const QoreObject *>(p)->getClassName());
         return 0;
      }
      ReferenceHolder<AbstractPrivateData> focalPointHolder(static_cast<AbstractPrivateData *>(focalPoint), xsink);
      qrg->setFocalPoint(*(static_cast<QPointF *>(focalPoint)));
      return 0;
   }
   qreal x = p ? p->getAsFloat() : 0.0;
   p = get_param(params, 1);
   qreal y = p ? p->getAsFloat() : 0.0;
   qrg->setFocalPoint(x, y);
   return 0;
}

//void setRadius ( qreal radius )
static AbstractQoreNode *QRADIALGRADIENT_setRadius(QoreObject *self, QoreQRadialGradient *qrg, const QoreListNode *params, ExceptionSink *xsink) {
   const AbstractQoreNode *p = get_param(params, 0);
   qreal radius = p ? p->getAsFloat() : 0.0;
   qrg->setRadius(radius);
   return 0;
}

QoreClass *initQRadialGradientClass(QoreClass *qgradient) {
   QC_QRadialGradient = new QoreClass("QRadialGradient", QDOM_GUI);
   CID_QRADIALGRADIENT = QC_QRadialGradient->getID();

   QC_QRadialGradient->addBuiltinVirtualBaseClass(qgradient);

   QC_QRadialGradient->setConstructor(QRADIALGRADIENT_constructor);
   QC_QRadialGradient->setCopy((q_copy_t)QRADIALGRADIENT_copy);

   QC_QRadialGradient->addMethod("center",                      (q_method_t)QRADIALGRADIENT_center);
   QC_QRadialGradient->addMethod("focalPoint",                  (q_method_t)QRADIALGRADIENT_focalPoint);
   QC_QRadialGradient->addMethod("radius",                      (q_method_t)QRADIALGRADIENT_radius);
   QC_QRadialGradient->addMethod("setCenter",                   (q_method_t)QRADIALGRADIENT_setCenter);
   QC_QRadialGradient->addMethod("setFocalPoint",               (q_method_t)QRADIALGRADIENT_setFocalPoint);
   QC_QRadialGradient->addMethod("setRadius",                   (q_method_t)QRADIALGRADIENT_setRadius);

   return QC_QRadialGradient;
}
