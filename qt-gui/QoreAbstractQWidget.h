/*
 QoreAbstractQWidget.h
 
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

#ifndef _QORE_QOREABSTRACTQWIDGET_H

#define _QORE_QOREABSTRACTQWIDGET_H

#include "QoreAbstractQObject.h"
#include "QoreAbstractQPaintDevice.h"

#include "QC_QSize.h"

#include <QActionEvent>

class QoreQWidgetExtension : public QoreQObjectExtension
{
   protected:
      // event methods
      const QoreMethod *e_changeEvent, *e_enterEvent, *e_leaveEvent,
         *e_paintEvent, 
         *e_mouseMoveEvent, *e_mousePressEvent, 
         *e_mouseReleaseEvent, *e_mouseDoubleClickEvent,
         *e_keyPressEvent, *e_keyReleaseEvent,
         *e_resizeEvent,
         *e_moveEvent,
	 *e_actionEvent,
	 *e_closeEvent,
	 *e_contextMenuEvent,
	 *e_dragEnterEvent,
	 *e_dragMoveEvent,
	 *e_dropEvent,
	 *e_dragLeaveEvent,
	 *e_focusInEvent, *e_focusOutEvent,
	 *e_hideEvent,
	 *e_inputMethodEvent,
	 *e_showEvent,
	 *e_tabletEvent,
	 *e_wheelEvent,

	 // other methods
	 //*p_getDC,
	 *p_heightForWidth,
	 *p_inputMethodQuery,
	 *p_minimumSizeHint,
	 //*p_paintEngine,
	 //*p_releaseDC,
	 *p_setVisible,
	 *p_sizeHint
	 ;

   public:
      DLLLOCAL QoreQWidgetExtension(QoreObject *obj, QObject *qo) : QoreQObjectExtension(obj, qo)
      {
	 const QoreClass *qc = obj->getClass();
         e_paintEvent             = findMethod(qc, "paintEvent");
         e_mouseMoveEvent         = findMethod(qc, "mouseMoveEvent");
         e_mousePressEvent        = findMethod(qc, "mousePressEvent");
         e_mouseReleaseEvent      = findMethod(qc, "mouseReleaseEvent");
         e_mouseDoubleClickEvent  = findMethod(qc, "mouseDoubleClickEvent");
         e_keyPressEvent          = findMethod(qc, "keyPressEvent");
         e_keyReleaseEvent        = findMethod(qc, "keyReleaseEvent");
         e_changeEvent            = findMethod(qc, "changeEvent");
         e_enterEvent             = findMethod(qc, "enterEvent");
         e_leaveEvent             = findMethod(qc, "leaveEvent");
         e_resizeEvent            = findMethod(qc, "resizeEvent");
         e_moveEvent              = findMethod(qc, "moveEvent");
	 e_actionEvent            = findMethod(qc, "actionEvent");
	 e_closeEvent             = findMethod(qc, "closeEvent");
         e_contextMenuEvent       = findMethod(qc, "contextMenuEvent");
	 e_dragEnterEvent         = findMethod(qc, "dragEnterEvent");
	 e_dragMoveEvent          = findMethod(qc, "dragMoveEvent");
	 e_dropEvent              = findMethod(qc, "dropEvent");
	 e_dragLeaveEvent         = findMethod(qc, "dragLeaveEvent");
	 e_focusInEvent           = findMethod(qc, "focusInEvent");
	 e_focusOutEvent          = findMethod(qc, "focusOutEvent");
	 e_hideEvent              = findMethod(qc, "hideEvent");
	 e_inputMethodEvent       = findMethod(qc, "inputMethodEvent");
	 e_showEvent              = findMethod(qc, "showEvent");
	 e_tabletEvent            = findMethod(qc, "tabletEvent");
	 e_wheelEvent             = findMethod(qc, "wheelEvent");

	 //p_getDC                  = findMethod(qc, "getDC");
	 p_heightForWidth         = findMethod(qc, "heightForWidth");
	 p_inputMethodQuery       = findMethod(qc, "inputMethodQuery");
	 p_minimumSizeHint        = findMethod(qc, "minimumSizeHint");
	 //p_paintEngine            = findMethod(qc, "paintEngine");
	 //p_releaseDC              = findMethod(qc, "releaseDC");
	 p_setVisible             = findMethod(qc, "setVisible");
	 p_sizeHint               = findMethod(qc, "sizeHint");
      }
};

class QoreAbstractQWidget : public QoreAbstractQObject, public QoreAbstractQPaintDevice
{
   public:
      DLLLOCAL virtual QWidget *getQWidget() const = 0;

      // event methods
      DLLLOCAL virtual void actionEvent(QActionEvent * event) = 0;
      DLLLOCAL virtual void changeEvent(QEvent * event) = 0;
      DLLLOCAL virtual void closeEvent(QCloseEvent * event) = 0;
      DLLLOCAL virtual void contextMenuEvent(QContextMenuEvent * event) = 0;
      DLLLOCAL virtual void dragEnterEvent(QDragEnterEvent * event) = 0;
      DLLLOCAL virtual void dragLeaveEvent(QDragLeaveEvent * event) = 0;
      DLLLOCAL virtual void dragMoveEvent(QDragMoveEvent * event) = 0;
      DLLLOCAL virtual void dropEvent(QDropEvent * event) = 0;
      DLLLOCAL virtual void enterEvent(QEvent * event) = 0;
      DLLLOCAL virtual void focusInEvent(QFocusEvent * event) = 0;
      DLLLOCAL virtual void focusOutEvent(QFocusEvent * event) = 0;
      DLLLOCAL virtual void hideEvent(QHideEvent * event) = 0;
      DLLLOCAL virtual void inputMethodEvent(QInputMethodEvent * event) = 0;
      DLLLOCAL virtual void keyPressEvent(QKeyEvent * event) = 0;
      DLLLOCAL virtual void keyReleaseEvent(QKeyEvent * event) = 0;
      DLLLOCAL virtual void leaveEvent(QEvent * event) = 0;
      //DLLLOCAL virtual bool macEvent(EventHandlerCallRef caller, EventRef event) = 0;
      DLLLOCAL virtual void mouseDoubleClickEvent(QMouseEvent * event) = 0;
      DLLLOCAL virtual void mouseMoveEvent(QMouseEvent * event) = 0;
      DLLLOCAL virtual void mousePressEvent(QMouseEvent * event) = 0;
      DLLLOCAL virtual void mouseReleaseEvent(QMouseEvent * event) = 0;
      DLLLOCAL virtual void moveEvent(QMoveEvent * event) = 0;
      DLLLOCAL virtual void paintEvent(QPaintEvent * event) = 0;
      //DLLLOCAL virtual bool qwsEvent(QWSEvent * event) = 0;
      DLLLOCAL virtual void resizeEvent(QResizeEvent * event) = 0;
      DLLLOCAL virtual void showEvent(QShowEvent * event) = 0;
      DLLLOCAL virtual void tabletEvent(QTabletEvent * event) = 0;
      DLLLOCAL virtual void wheelEvent(QWheelEvent * event) = 0;
      //DLLLOCAL virtual bool winEvent(MSG * message, long * result) = 0;
      //DLLLOCAL virtual bool x11Event(XEvent * event) = 0;

      // other virtual methods
      //DLLLOCAL virtual HDC getDC () const = 0;
      DLLLOCAL virtual int heightForWidth ( int w ) const = 0;
      DLLLOCAL virtual QVariant inputMethodQuery ( Qt::InputMethodQuery query ) const = 0;
      DLLLOCAL virtual QSize minimumSizeHint () const = 0;
      //DLLLOCAL virtual QPaintEngine * paintEngine () const = 0;
      //DLLLOCAL virtual void releaseDC ( HDC hdc ) const = 0;
      DLLLOCAL virtual void setVisible ( bool visible ) = 0;
      DLLLOCAL virtual QSize sizeHint() const = 0;
};

template<typename T, typename V>
class QoreQWidgetBase : public QoreQObjectBase<T, V>
{
   public:
      DLLLOCAL QoreQWidgetBase(T *qo) : QoreQObjectBase<T, V>(qo)
      {
      }

      DLLLOCAL virtual QWidget *getQWidget() const
      {
	 return &(*this->qobj);
      }
      DLLLOCAL virtual QPaintDevice *getQPaintDevice() const
      {
	 return static_cast<QPaintDevice *>(&(*this->qobj));
      }

      DLLLOCAL virtual void actionEvent(QActionEvent * event) {
	 this->qobj->parent_actionEvent(event);
      }
      DLLLOCAL virtual void changeEvent(QEvent * event) {
	 this->qobj->parent_changeEvent(event);
      }
      DLLLOCAL virtual void closeEvent(QCloseEvent * event) {
	 this->qobj->parent_closeEvent(event);
      }
      DLLLOCAL virtual void contextMenuEvent ( QContextMenuEvent * event ) {
	 this->qobj->parent_contextMenuEvent(event); 
      } 
      DLLLOCAL virtual void dragEnterEvent ( QDragEnterEvent * event ) {
	 this->qobj->parent_dragEnterEvent(event); 
      }
      DLLLOCAL virtual void dragLeaveEvent ( QDragLeaveEvent * event ) {
	 this->qobj->parent_dragLeaveEvent(event); 
      }
      DLLLOCAL virtual void dragMoveEvent ( QDragMoveEvent * event )  {
	 this->qobj->parent_dragMoveEvent(event); 
      }
      DLLLOCAL virtual void dropEvent ( QDropEvent * event ) {	
	 this->qobj->parent_dropEvent(event); 
      }
      DLLLOCAL virtual void enterEvent ( QEvent * event ) {	
	 this->qobj->parent_enterEvent(event); 
      }
      DLLLOCAL virtual void focusInEvent ( QFocusEvent * event ) {	
	 this->qobj->parent_focusInEvent(event); 
      }
      DLLLOCAL virtual void focusOutEvent ( QFocusEvent * event ) {	
	 this->qobj->parent_focusOutEvent(event); 
      }
      DLLLOCAL virtual void hideEvent ( QHideEvent * event ) {	
	 this->qobj->parent_hideEvent(event); 
      }
      DLLLOCAL virtual void inputMethodEvent ( QInputMethodEvent * event ) { 
	 this->qobj->parent_inputMethodEvent(event); 
      }
      DLLLOCAL virtual void keyPressEvent ( QKeyEvent * event ) {	
	 this->qobj->parent_keyPressEvent(event); 
      }
      DLLLOCAL virtual void keyReleaseEvent ( QKeyEvent * event ) {	
	 this->qobj->parent_keyReleaseEvent(event); 
      }
      DLLLOCAL virtual void leaveEvent ( QEvent * event ) {	
	 this->qobj->parent_leaveEvent(event); 
      }
      /*DLLLOCAL virtual bool macEvent ( EventHandlerCallRef caller, EventRef event ) { 
	this->qobj->parent_macEvent(event);						
	}*/								
      DLLLOCAL virtual void mouseDoubleClickEvent ( QMouseEvent * event ) { 
	 this->qobj->parent_mouseDoubleClickEvent(event); 
      }
      DLLLOCAL virtual void mouseMoveEvent ( QMouseEvent * event ) {	
	 this->qobj->parent_mouseMoveEvent(event);					
      }
      DLLLOCAL virtual void mousePressEvent ( QMouseEvent * event ) {	
	 this->qobj->parent_mousePressEvent(event); 
      }
      DLLLOCAL virtual void mouseReleaseEvent ( QMouseEvent * event ) {	
	 this->qobj->parent_mouseReleaseEvent(event); 
      }
      DLLLOCAL virtual void moveEvent ( QMoveEvent * event ) {	
	 this->qobj->parent_moveEvent(event); 
      }
      DLLLOCAL virtual void paintEvent ( QPaintEvent * event ) {	
	 this->qobj->parent_paintEvent(event); 
      }
      /*DLLLOCAL virtual bool qwsEvent ( QWSEvent * event ) {	
	this->qobj->parent_qwsEvent(event);					
	}*/							
      DLLLOCAL virtual void resizeEvent ( QResizeEvent * event ) {
	 this->qobj->parent_resizeEvent(event); 
      }
      DLLLOCAL virtual void showEvent ( QShowEvent * event ) {	
	 this->qobj->parent_showEvent(event); 
      }
      DLLLOCAL virtual void tabletEvent ( QTabletEvent * event ) {	
	 this->qobj->parent_tabletEvent(event); 
      }
      DLLLOCAL virtual void wheelEvent ( QWheelEvent * event ) {	
	 this->qobj->parent_wheelEvent(event); 
      }
      /*DLLLOCAL virtual bool winEvent ( MSG * message, long * result ) {	
	this->qobj->parent_winEvent(event);						
	}									
	DLLLOCAL virtual bool x11Event ( XEvent * event ) {		
	this->qobj->parent_x11Event(event);						
	}*/ 
      DLLLOCAL virtual int heightForWidth ( int w ) const { 
	 return this->qobj->parent_heightForWidth(w); 
      } 
      DLLLOCAL virtual QVariant inputMethodQuery ( Qt::InputMethodQuery query ) const { 
	 return this->qobj->parent_inputMethodQuery(query); 
      } 
      DLLLOCAL virtual QSize minimumSizeHint () const { 
	 return this->qobj->parent_minimumSizeHint(); 
      } 
      /*DLLLOCAL virtual QPaintEngine * paintEngine () const {	
	return this->qobj->parent_paintEngine();				
	}								
	DLLLOCAL virtual void releaseDC ( HDC hdc ) const {	
	this->qobj->parent_releaseDC(hdc);				
	}*/							
      DLLLOCAL virtual void setVisible ( bool visible ) { 
	 this->qobj->parent_setVisible(visible); 
      } 
      DLLLOCAL virtual QSize sizeHint() const { 
	 return this->qobj->parent_sizeHint();
      }

      DLLLOCAL virtual QPaintEngine *parent_paintEngine() const
      {
         return this->qobj->parent_paintEngine();
      }
};

template<typename T, typename V>
class QoreQtQWidgetBase : public QoreQtQObjectBase<T, V>
{
   public:
      DLLLOCAL QoreQtQWidgetBase(QoreObject *obj, T *qo, bool n_managed = true) : QoreQtQObjectBase<T, V>(obj, qo, n_managed)
      {
      }

      DLLLOCAL virtual QWidget *getQWidget() const
      {
	 return this->qobj;
      }

      DLLLOCAL virtual QPaintDevice *getQPaintDevice() const
      {
	 return static_cast<QPaintDevice *>(this->qobj);
      }

      DLLLOCAL virtual void actionEvent(QActionEvent * event) { }
      DLLLOCAL virtual void changeEvent(QEvent * event) {}
      DLLLOCAL virtual void closeEvent(QCloseEvent * event) {}
      DLLLOCAL virtual void contextMenuEvent ( QContextMenuEvent * event ) {}
      DLLLOCAL virtual void dragEnterEvent ( QDragEnterEvent * event ) {}	
      DLLLOCAL virtual void dragLeaveEvent ( QDragLeaveEvent * event ) {}	
      DLLLOCAL virtual void dragMoveEvent ( QDragMoveEvent * event )  {}	
      DLLLOCAL virtual void dropEvent ( QDropEvent * event ) {}		
      DLLLOCAL virtual void enterEvent ( QEvent * event ) {}
      DLLLOCAL virtual void focusInEvent ( QFocusEvent * event ) {}	
      DLLLOCAL virtual void focusOutEvent ( QFocusEvent * event ) {}	
      DLLLOCAL virtual void hideEvent ( QHideEvent * event ) {}		
      DLLLOCAL virtual void inputMethodEvent ( QInputMethodEvent * event ) {} 
      DLLLOCAL virtual void keyPressEvent ( QKeyEvent * event ) {}		
      DLLLOCAL virtual void keyReleaseEvent ( QKeyEvent * event ) {}	
      DLLLOCAL virtual void leaveEvent ( QEvent * event ) {}		
      //DLLLOCAL virtual bool macEvent ( EventHandlerCallRef caller, EventRef event ) {}
      DLLLOCAL virtual void mouseDoubleClickEvent ( QMouseEvent * event ) {} 
      DLLLOCAL virtual void mouseMoveEvent ( QMouseEvent * event ) {}	
      DLLLOCAL virtual void mousePressEvent ( QMouseEvent * event ) {}	
      DLLLOCAL virtual void mouseReleaseEvent ( QMouseEvent * event ) {}	
      DLLLOCAL virtual void moveEvent ( QMoveEvent * event ) {}		
      DLLLOCAL virtual void paintEvent ( QPaintEvent * event ) {}		
      //DLLLOCAL virtual bool qwsEvent ( QWSEvent * event ) { return false; }
      DLLLOCAL virtual void resizeEvent ( QResizeEvent * event ) {}	
      DLLLOCAL virtual void showEvent ( QShowEvent * event ) {}		
      DLLLOCAL virtual void tabletEvent ( QTabletEvent * event ) {}	
      DLLLOCAL virtual void wheelEvent ( QWheelEvent * event ) {}		
      //DLLLOCAL virtual bool winEvent ( MSG * message, long * result ) { return false;}
      //DLLLOCAL virtual bool x11Event ( XEvent * event ) { return false; }
      //DLLLOCAL virtual HDC getDC () const {}
      DLLLOCAL virtual int heightForWidth ( int w ) const { return 0; }
      DLLLOCAL virtual QVariant inputMethodQuery ( Qt::InputMethodQuery query ) const { return QVariant(); }
      DLLLOCAL virtual QSize minimumSizeHint () const { return QSize(); }
      //DLLLOCAL virtual QPaintEngine * paintEngine () const { return 0; }
      //DLLLOCAL virtual void releaseDC ( HDC hdc ) const {}
      DLLLOCAL virtual void setVisible ( bool visible ) {}
      DLLLOCAL virtual QSize sizeHint() const { return QSize(); }
      DLLLOCAL virtual QPaintEngine *parent_paintEngine() const
      {
         return this->qobj->paintEngine();
      }

};

#endif
