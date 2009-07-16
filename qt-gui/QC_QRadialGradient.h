/*
 QC_QRadialGradient.h
 
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

#ifndef _QORE_QT_QC_QRADIALGRADIENT_H

#define _QORE_QT_QC_QRADIALGRADIENT_H

#include <QRadialGradient>
#include "QC_QGradient.h"

DLLEXPORT extern qore_classid_t CID_QRADIALGRADIENT;
DLLEXPORT extern QoreClass *QC_QRadialGradient;
DLLEXPORT QoreClass *initQRadialGradientClass(QoreClass *);

class QoreQRadialGradient : public QoreAbstractQGradient, public QRadialGradient {
   public:
      DLLLOCAL QoreQRadialGradient() : QRadialGradient() { }
      DLLLOCAL QoreQRadialGradient(const QPointF& center, qreal radius, const QPointF& focalPoint) : QRadialGradient(center, radius, focalPoint) { }
      DLLLOCAL QoreQRadialGradient(qreal cx, qreal cy, qreal radius, qreal fx, qreal fy) : QRadialGradient(cx, cy, radius, fx, fy) { }
      DLLLOCAL QoreQRadialGradient(const QPointF& center, qreal radius) : QRadialGradient(center, radius) { }
      DLLLOCAL QoreQRadialGradient(qreal cx, qreal cy, qreal radius) : QRadialGradient(cx, cy, radius) { }

      DLLLOCAL virtual QGradient *getQGradient()
      {
         return this;
      }

};

#endif // _QORE_QT_QC_QRADIALGRADIENT_H
