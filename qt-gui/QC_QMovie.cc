/*
 QC_QMovie.cc
 
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

#include "QC_QMovie.h"
#include "QC_QObject.h"
#include "QC_QColor.h"
#include "QC_QImage.h"
#include "QC_QPixmap.h"
#include "QC_QByteArray.h"
#include "QC_QRect.h"
#include "QC_QSize.h"

qore_classid_t CID_QMOVIE;
class QoreClass *QC_QMovie = 0;

//QMovie ( QObject * parent = 0 )
//QMovie ( QIODevice * device, const QByteArray & format = QByteArray(), QObject * parent = 0 )
//QMovie ( const QString & fileName, const QByteArray & format = QByteArray(), QObject * parent = 0 )
static void QMOVIE_constructor(QoreObject *self, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (is_nothing(p)) {
      self->setPrivate(CID_QMOVIE, new QoreQMovie(self));
      return;
   }
   if (p && p->getType() == NT_OBJECT) {
      QoreAbstractQObject *parent = (QoreAbstractQObject *)(reinterpret_cast<const QoreObject *>(p))->getReferencedPrivateData(CID_QOBJECT, xsink);
      if (*xsink)
         return;
      ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
      self->setPrivate(CID_QMOVIE, new QoreQMovie(self, parent ? parent->getQObject() : 0));
      return;
   }
   QString fileName;
   if (get_qstring(p, fileName, xsink))
      return;
   p = get_param(params, 1);
   QByteArray format;
   if (get_qbytearray(p, format, xsink, true))
      format = QByteArray();

   const QoreObject *o = test_object_param(params, 2);
   QoreAbstractQObject *parent = o ? (QoreAbstractQObject *)o->getReferencedPrivateData(CID_QOBJECT, xsink) : 0;
   if (*xsink)
      return;
   ReferenceHolder<AbstractPrivateData> parentHolder(static_cast<AbstractPrivateData *>(parent), xsink);
   self->setPrivate(CID_QMOVIE, new QoreQMovie(self, fileName, format, parent ? parent->getQObject() : 0));
   return;
}

static void QMOVIE_copy(class QoreObject *self, class QoreObject *old, class QoreQMovie *qm, ExceptionSink *xsink)
{
   self->setPrivate(CID_QMOVIE, new QoreQMovie(*qm));
   //xsink->raiseException("QMOVIE-COPY-ERROR", "objects of this class cannot be copied");
}

//QColor backgroundColor () const
static AbstractQoreNode *QMOVIE_backgroundColor(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qc = new QoreObject(QC_QColor, getProgram());
   QoreQColor *q_qc = new QoreQColor(qm->qobj->backgroundColor());
   o_qc->setPrivate(CID_QCOLOR, q_qc);
   return o_qc;
}

//CacheMode cacheMode () const
static AbstractQoreNode *QMOVIE_cacheMode(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qm->qobj->cacheMode());
}

//int currentFrameNumber () const
static AbstractQoreNode *QMOVIE_currentFrameNumber(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qm->qobj->currentFrameNumber());
}

//QImage currentImage () const
static AbstractQoreNode *QMOVIE_currentImage(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qi = new QoreObject(QC_QImage, getProgram());
   QoreQImage *q_qi = new QoreQImage(qm->qobj->currentImage());
   o_qi->setPrivate(CID_QIMAGE, q_qi);
   return o_qi;
}

//QPixmap currentPixmap () const
static AbstractQoreNode *QMOVIE_currentPixmap(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qp = new QoreObject(QC_QPixmap, getProgram());
   QoreQPixmap *q_qp = new QoreQPixmap(qm->qobj->currentPixmap());
   o_qp->setPrivate(CID_QPIXMAP, q_qp);
   return o_qp;
}

/*
//QIODevice * device () const
static AbstractQoreNode *QMOVIE_device(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   ??? return new QoreBigIntNode(qm->qobj->device());
}
*/

//QString fileName () const
static AbstractQoreNode *QMOVIE_fileName(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreStringNode(qm->qobj->fileName().toUtf8().data(), QCS_UTF8);
}

//QByteArray format () const
static AbstractQoreNode *QMOVIE_format(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qba = new QoreObject(QC_QByteArray, getProgram());
   QoreQByteArray *q_qba = new QoreQByteArray(qm->qobj->format());
   o_qba->setPrivate(CID_QBYTEARRAY, q_qba);
   return o_qba;
}

//int frameCount () const
static AbstractQoreNode *QMOVIE_frameCount(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qm->qobj->frameCount());
}

//QRect frameRect () const
static AbstractQoreNode *QMOVIE_frameRect(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qr = new QoreObject(QC_QRect, getProgram());
   QoreQRect *q_qr = new QoreQRect(qm->qobj->frameRect());
   o_qr->setPrivate(CID_QRECT, q_qr);
   return o_qr;
}

//bool isValid () const
static AbstractQoreNode *QMOVIE_isValid(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qm->qobj->isValid());
}

//bool jumpToFrame ( int frameNumber )
static AbstractQoreNode *QMOVIE_jumpToFrame(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int frameNumber = p ? p->getAsInt() : 0;
   return get_bool_node(qm->qobj->jumpToFrame(frameNumber));
}

//int loopCount () const
static AbstractQoreNode *QMOVIE_loopCount(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qm->qobj->loopCount());
}

//int nextFrameDelay () const
static AbstractQoreNode *QMOVIE_nextFrameDelay(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qm->qobj->nextFrameDelay());
}

//QSize scaledSize ()
static AbstractQoreNode *QMOVIE_scaledSize(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qs = new QoreObject(QC_QSize, getProgram());
   QoreQSize *q_qs = new QoreQSize(qm->qobj->scaledSize());
   o_qs->setPrivate(CID_QSIZE, q_qs);
   return o_qs;
}

//void setBackgroundColor ( const QColor & color )
static AbstractQoreNode *QMOVIE_setBackgroundColor(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQColor *color = p ? (QoreQColor *)p->getReferencedPrivateData(CID_QCOLOR, xsink) : 0;
   if (!color) {
      if (!xsink->isException())
         xsink->raiseException("QMOVIE-SETBACKGROUNDCOLOR-PARAM-ERROR", "expecting a QColor object as first argument to QMovie::setBackgroundColor()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> colorHolder(static_cast<AbstractPrivateData *>(color), xsink);
   qm->qobj->setBackgroundColor(*(static_cast<QColor *>(color)));
   return 0;
}

//void setCacheMode ( CacheMode mode )
static AbstractQoreNode *QMOVIE_setCacheMode(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QMovie::CacheMode mode = (QMovie::CacheMode)(p ? p->getAsInt() : 0);
   qm->qobj->setCacheMode(mode);
   return 0;
}

/*
//void setDevice ( QIODevice * device )
static AbstractQoreNode *QMOVIE_setDevice(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   ??? QIODevice* device = p;
   qm->qobj->setDevice(device);
   return 0;
}
*/

//void setFileName ( const QString & fileName )
static AbstractQoreNode *QMOVIE_setFileName(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString fileName;
   if (get_qstring(p, fileName, xsink))
      return 0;
   qm->qobj->setFileName(fileName);

   return 0;
}

//void setFormat ( const QByteArray & format )
static AbstractQoreNode *QMOVIE_setFormat(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QByteArray format;
   if (get_qbytearray(p, format, xsink))
      return 0;
   qm->qobj->setFormat(format);
   return 0;
}

//void setScaledSize ( const QSize & size )
static AbstractQoreNode *QMOVIE_setScaledSize(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *p = test_object_param(params, 0);
   QoreQSize *size = p ? (QoreQSize *)p->getReferencedPrivateData(CID_QSIZE, xsink) : 0;
   if (!size) {
      if (!xsink->isException())
         xsink->raiseException("QMOVIE-SETSCALEDSIZE-PARAM-ERROR", "expecting a QSize object as first argument to QMovie::setScaledSize()");
      return 0;
   }
   ReferenceHolder<AbstractPrivateData> sizeHolder(static_cast<AbstractPrivateData *>(size), xsink);
   qm->qobj->setScaledSize(*(static_cast<QSize *>(size)));
   return 0;
}

//int speed () const
static AbstractQoreNode *QMOVIE_speed(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qm->qobj->speed());
}

//MovieState state () const
static AbstractQoreNode *QMOVIE_state(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return new QoreBigIntNode(qm->qobj->state());
}

//bool jumpToNextFrame ()
static AbstractQoreNode *QMOVIE_jumpToNextFrame(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   return get_bool_node(qm->qobj->jumpToNextFrame());
}

//void setPaused ( bool paused )
static AbstractQoreNode *QMOVIE_setPaused(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   bool paused = p ? p->getAsBool() : false;
   qm->qobj->setPaused(paused);
   return 0;
}

//void setSpeed ( int percentSpeed )
static AbstractQoreNode *QMOVIE_setSpeed(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int percentSpeed = p ? p->getAsInt() : 0;
   qm->qobj->setSpeed(percentSpeed);
   return 0;
}

//void start ()
static AbstractQoreNode *QMOVIE_start(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   qm->qobj->start();
   return 0;
}

//void stop ()
static AbstractQoreNode *QMOVIE_stop(QoreObject *self, QoreQMovie *qm, const QoreListNode *params, ExceptionSink *xsink)
{
   qm->qobj->stop();
   return 0;
}

static AbstractQoreNode *f_QMovie_supportedFormats(const QoreListNode *params, ExceptionSink *xsink)
{
   QoreListNode *ql = new QoreListNode();

   QList<QByteArray> l = QMovie::supportedFormats();
   for (QList<QByteArray>::iterator i = l.begin(), e=l.end(); i != e; ++i)
      ql->push(new QoreStringNode((*i).data()));

   return ql;
}

QoreClass *initQMovieClass(QoreClass *qobject)
{
   QC_QMovie = new QoreClass("QMovie", QDOM_GUI);
   CID_QMOVIE = QC_QMovie->getID();

   QC_QMovie->addBuiltinVirtualBaseClass(qobject);

   QC_QMovie->setConstructor(QMOVIE_constructor);
   QC_QMovie->setCopy((q_copy_t)QMOVIE_copy);

   QC_QMovie->addMethod("backgroundColor",             (q_method_t)QMOVIE_backgroundColor);
   QC_QMovie->addMethod("cacheMode",                   (q_method_t)QMOVIE_cacheMode);
   QC_QMovie->addMethod("currentFrameNumber",          (q_method_t)QMOVIE_currentFrameNumber);
   QC_QMovie->addMethod("currentImage",                (q_method_t)QMOVIE_currentImage);
   QC_QMovie->addMethod("currentPixmap",               (q_method_t)QMOVIE_currentPixmap);
   //QC_QMovie->addMethod("device",                      (q_method_t)QMOVIE_device);
   QC_QMovie->addMethod("fileName",                    (q_method_t)QMOVIE_fileName);
   QC_QMovie->addMethod("format",                      (q_method_t)QMOVIE_format);
   QC_QMovie->addMethod("frameCount",                  (q_method_t)QMOVIE_frameCount);
   QC_QMovie->addMethod("frameRect",                   (q_method_t)QMOVIE_frameRect);
   QC_QMovie->addMethod("isValid",                     (q_method_t)QMOVIE_isValid);
   QC_QMovie->addMethod("jumpToFrame",                 (q_method_t)QMOVIE_jumpToFrame);
   QC_QMovie->addMethod("loopCount",                   (q_method_t)QMOVIE_loopCount);
   QC_QMovie->addMethod("nextFrameDelay",              (q_method_t)QMOVIE_nextFrameDelay);
   QC_QMovie->addMethod("scaledSize",                  (q_method_t)QMOVIE_scaledSize);
   QC_QMovie->addMethod("setBackgroundColor",          (q_method_t)QMOVIE_setBackgroundColor);
   QC_QMovie->addMethod("setCacheMode",                (q_method_t)QMOVIE_setCacheMode);
   //QC_QMovie->addMethod("setDevice",                   (q_method_t)QMOVIE_setDevice);
   QC_QMovie->addMethod("setFileName",                 (q_method_t)QMOVIE_setFileName);
   QC_QMovie->addMethod("setFormat",                   (q_method_t)QMOVIE_setFormat);
   QC_QMovie->addMethod("setScaledSize",               (q_method_t)QMOVIE_setScaledSize);
   QC_QMovie->addMethod("speed",                       (q_method_t)QMOVIE_speed);
   QC_QMovie->addMethod("state",                       (q_method_t)QMOVIE_state);
   QC_QMovie->addMethod("jumpToNextFrame",             (q_method_t)QMOVIE_jumpToNextFrame);
   QC_QMovie->addMethod("setPaused",                   (q_method_t)QMOVIE_setPaused);
   QC_QMovie->addMethod("setSpeed",                    (q_method_t)QMOVIE_setSpeed);
   QC_QMovie->addMethod("start",                       (q_method_t)QMOVIE_start);
   QC_QMovie->addMethod("stop",                        (q_method_t)QMOVIE_stop);

   // static methods
   QC_QMovie->addStaticMethod("supportedFormats", f_QMovie_supportedFormats);

   return QC_QMovie;
}
