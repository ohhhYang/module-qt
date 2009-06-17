/*
  qt-module.cc
  
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

#include "qore-qt-gui.h"

#include "QC_QApplication.h"
#include "QC_QCoreApplication.h"
#include "QC_QPushButton.h"
#include "QC_QFont.h"
#include "QC_QMatrix.h"
#include "QC_QWidget.h"
#include "QC_QFrame.h"
#include "QC_QLCDNumber.h"
#include "QC_QLayout.h"
#include "QC_QBoxLayout.h"
#include "QC_QVBoxLayout.h"
#include "QC_QHBoxLayout.h"
#include "QC_QGridLayout.h"
#include "QC_QBrush.h"
#include "QC_QColor.h"
#include "QC_QPalette.h"
#include "QC_QPaintDevice.h"
#include "QC_QPainter.h"
#include "QC_QRegion.h"
#include "QC_QLabel.h"
#include "QC_QAbstractSlider.h"
#include "QC_QSlider.h"
#include "QC_QPicture.h"
#include "QC_QPixmap.h"
#include "QC_QBitmap.h"
#include "QC_QMovie.h"
#include "QC_QShortcut.h"
#include "QC_QImage.h"
#include "QC_QIcon.h"
#include "QC_QKeySequence.h"
#include "QC_QAction.h"
#include "QC_QActionGroup.h"
#include "QC_QPolygon.h"
#include "QC_QPolygonF.h"
#include "QC_QAbstractButton.h"
#include "QC_QMenu.h"
#include "QC_QToolButton.h"
#include "QC_QDialog.h"
#include "QC_QLineEdit.h"
#include "QC_QTextLength.h"
#include "QC_QTextFormat.h"
#include "QC_QTextBlockFormat.h"
#include "QC_QTextCharFormat.h"
#include "QC_QPen.h"
#include "QC_QTextFrameFormat.h"
#include "QC_QTextTableFormat.h"
#include "QC_QTextListFormat.h"
#include "QC_QTextImageFormat.h"
#include "QC_QCalendarWidget.h"
#include "QC_QStyleOption.h"
#include "QC_QStyleOptionViewItem.h"
#include "QC_QStyleOptionViewItemV2.h"
#include "QC_QAbstractItemDelegate.h"
#include "QC_QItemDelegate.h"
#include "QC_QComboBox.h"
#include "QC_QCheckBox.h"
#include "QC_QAbstractSpinBox.h"
#include "QC_QDateTimeEdit.h"
#include "QC_QGroupBox.h"
#include "QC_QDateEdit.h"
#include "QC_QFontMetrics.h"
#include "QC_QFontDatabase.h"
#include "QC_QFontInfo.h"
#include "QC_QScrollBar.h"
#include "QC_QAbstractScrollArea.h"
#include "QC_QScrollArea.h"
#include "QC_QClipboard.h"
#include "QC_QFontComboBox.h"
#include "QC_QMainWindow.h"
#include "QC_QRadioButton.h"
#include "QC_QStyle.h"
#include "QC_QStyleOptionComplex.h"
#include "QC_QStyleOptionComboBox.h"
#include "QC_QStyleOptionGroupBox.h"
#include "QC_QStyleOptionSizeGrip.h"
#include "QC_QStyleOptionSlider.h"
#include "QC_QStyleOptionSpinBox.h"
#include "QC_QStyleOptionTitleBar.h"
#include "QC_QStyleOptionToolButton.h"
#include "QC_QSpinBox.h"
#include "QC_QAbstractItemView.h"
#include "QC_QTableView.h"
#include "QC_QTableWidget.h"
#include "QC_QTableWidgetItem.h"
#include "QC_QStyleOptionMenuItem.h"
#include "QC_QMessageBox.h"
#include "QC_QStyleOptionButton.h"
#include "QC_QFileDialog.h"
#include "QC_QHeaderView.h"
#include "QC_QMenuBar.h"
#include "QC_QPrinter.h"
#include "QC_QPrintDialog.h"
#include "QC_QValidator.h"
#include "QC_QDoubleValidator.h"
#include "QC_QIntValidator.h"
#include "QC_QRegExpValidator.h"
#include "QC_QColorDialog.h"
#include "QC_QInputDialog.h"
#include "QC_QImageWriter.h"
#include "QC_QDial.h"
#include "QC_QStackedWidget.h"
#include "QC_QDoubleSpinBox.h"
#include "QC_QTimeEdit.h"
#include "QC_QProgressBar.h"
#include "QC_QPainterPath.h"
#include "QC_QPaintEngine.h"
#include "QC_QTextEdit.h"
#include "QC_QTabBar.h"
#include "QC_QStyleOptionTab.h"
#include "QC_QStyleOptionTabWidgetFrame.h"
#include "QC_QTabWidget.h"
#include "QC_QDesktopWidget.h"
#include "QC_QSystemTrayIcon.h"
#include "QC_QWizard.h"
#include "QC_QWizardPage.h"
#include "QC_QListView.h"
#include "QC_QListWidgetItem.h"
#include "QC_QDialogButtonBox.h"
#include "QC_QToolBar.h"
#include "QC_QProgressDialog.h"
#include "QC_QFontDialog.h"
#include "QC_QErrorMessage.h"
#include "QC_QStackedLayout.h"
#include "QC_QGradient.h"
#include "QC_QLayoutItem.h"
#include "QC_QWidgetItem.h"
#include "QC_QCursor.h"
#include "QC_QStyleOptionGraphicsItem.h"
#include "QC_QTransform.h"
#include "QC_QSplashScreen.h"
#include "QC_QSplitter.h"
#include "QC_QSplitterHandle.h"
#include "QC_QGraphicsItem.h"
#include "QC_QTextLine.h"
#include "QC_QTextOption.h"
#include "QC_QTextLayout.h"
#include "QC_QGraphicsSceneEvent.h"
#include "QC_QGraphicsSceneContextMenuEvent.h"
#include "QC_QGraphicsSceneDragDropEvent.h"
#include "QC_QGraphicsSceneHelpEvent.h"
#include "QC_QGraphicsSceneHoverEvent.h"
#include "QC_QGraphicsSceneMouseEvent.h"
#include "QC_QGraphicsSceneWheelEvent.h"
#include "QC_QDesktopServices.h"
#include "QC_QItemSelectionRange.h"
#include "QC_QFileIconProvider.h"
#include "QC_QDirModel.h"
#include "QC_QStatusBar.h"
#include "QC_QItemSelection.h"
#include "QC_QItemSelectionModel.h"
#include "QC_QStyleOptionDockWidget.h"
#include "QC_QDockWidget.h"
#include "QC_QTreeView.h"
#include "QC_QSpacerItem.h"
#include "QC_QMdiArea.h"
#include "QC_QMdiSubWindow.h"
#include "QC_QTreeWidgetItem.h"
#include "QC_QTreeWidget.h"

#include <QPalette>
#include <QToolTip>
#include <QStyleFactory>

#include <assert.h>

static QoreStringNode *qt_module_init();
static void qt_module_ns_init(QoreNamespace *rns, QoreNamespace *qns);
static void qt_module_delete();

DLLEXPORT char qore_module_name[] = "qt-gui";
DLLEXPORT char qore_module_version[] = PACKAGE_VERSION;
DLLEXPORT char qore_module_description[] = "QT 4 module";
DLLEXPORT char qore_module_author[] = "David Nichols";
DLLEXPORT char qore_module_url[] = "http://www.qoretechnologies.com/qore";
DLLEXPORT int qore_module_api_major = QORE_MODULE_API_MAJOR;
DLLEXPORT int qore_module_api_minor = QORE_MODULE_API_MINOR;
DLLEXPORT qore_module_init_t qore_module_init = qt_module_init;
DLLEXPORT qore_module_ns_init_t qore_module_ns_init = qt_module_ns_init;
DLLEXPORT qore_module_delete_t qore_module_delete = qt_module_delete;
// assume LGPL for qt >= 4.5
#if QT_VERSION >= 0x040500
DLLEXPORT qore_license_t qore_module_license = QL_LGPL;
#else
DLLEXPORT qore_license_t qore_module_license = QL_GPL;
#endif
DLLEXPORT const char *qore_module_dependencies[] = { "qt-core", 0 };

static class AbstractQoreNode *f_QAPP(const QoreListNode *params, class ExceptionSink *xsink) {
   return get_qore_qapp();
}

static AbstractQoreNode *f_QToolTip_font(const QoreListNode *params, ExceptionSink *xsink) {
   QoreObject *o_qf = new QoreObject(QC_QFont, getProgram());
   QoreQFont *q_qf = new QoreQFont(QToolTip::font());
   o_qf->setPrivate(CID_QFONT, q_qf);
   return o_qf;
}

//void hideText ()
static AbstractQoreNode *f_QToolTip_hideText(const QoreListNode *params, ExceptionSink *xsink)
{
   QToolTip::hideText();
   return 0;
}

//QPalette palette ()
static AbstractQoreNode *f_QToolTip_palette(const QoreListNode *params, ExceptionSink *xsink)
{
   QoreObject *o_qp = new QoreObject(QC_QPalette, getProgram());
   QoreQPalette *q_qp = new QoreQPalette(QToolTip::palette());
   o_qp->setPrivate(CID_QPALETTE, q_qp);
   return o_qp;
}

//void setFont ( const QFont & font )
static AbstractQoreNode *f_QToolTip_setFont(const QoreListNode *params, ExceptionSink *xsink)
{
   const QoreObject *p = test_object_param(params, 0);
   QoreQFont *font = p ? (QoreQFont *)p->getReferencedPrivateData(CID_QFONT, xsink) : 0;
   if (!font) {
      if (!xsink->isException())
         xsink->raiseException("QTOOLTIP-SETFONT-PARAM-ERROR", "expecting a QFont object as first argument to QToolTip_setFont()");
      return 0;
   }
   ReferenceHolder<QoreQFont> fontHolder(font, xsink);
   QToolTip::setFont(*(static_cast<QFont *>(font)));
   return 0;
}

//void setPalette ( const QPalette & palette )
static AbstractQoreNode *f_QToolTip_setPalette(const QoreListNode *params, ExceptionSink *xsink)
{
   const QoreObject *p = test_object_param(params, 0);
   QoreQPalette *palette = p ? (QoreQPalette *)p->getReferencedPrivateData(CID_QPALETTE, xsink) : 0;
   if (!palette) {
      if (!xsink->isException())
         xsink->raiseException("QTOOLTIP-SETPALETTE-PARAM-ERROR", "expecting a QPalette object as first argument to QToolTip_setPalette()");
      return 0;
   }
   ReferenceHolder<QoreQPalette> paletteHolder(palette, xsink);
   QToolTip::setPalette(*(palette->getQPalette()));
   return 0;
}


//void showText ( const QPoint & pos, const QString & text, QWidget * w, const QRect & rect ) 
//void showText ( const QPoint & pos, const QString & text, QWidget * w = 0 )
static class AbstractQoreNode *f_QToolTip_showText(const QoreListNode *params, class ExceptionSink *xsink)
{
   const QoreObject *p = test_object_param(params, 0);
   QoreQPoint *pos = p ? (QoreQPoint *)p->getReferencedPrivateData(CID_QPOINT, xsink) : 0;
   if (!pos) {
      if (!xsink->isException())
	 xsink->raiseException("QTOOLTIP-SHOWTEXT-PARAM-ERROR", "QToolTip_showText() was expecting a QPoint as the first argument");
      return 0;
   }
   ReferenceHolder<QoreQPoint> posHolder(pos, xsink);
   const QoreStringNode *str = test_string_param(params, 1);
   if (!str) {
      xsink->raiseException("QTOOLTIP-SHOWTEXT-PARAM-ERROR", "expecting a string as second argument to QToolTip_showText()");
      return 0;
   }
   const char *text = str->getBuffer();

   p = test_object_param(params, 2);
   QoreQWidget *w = p ? (QoreQWidget *)p->getReferencedPrivateData(CID_QWIDGET, xsink) : 0;
   if (p && !w) {
      if (!xsink->isException())
	 xsink->raiseException("QTOOLTIP-SHOWTEXT-PARAM-ERROR", "QToolTip_showText() does not know how to handle arguments of class '%s' as passed as the third argument", p->getClass()->getName());
      return 0;
   }
   ReferenceHolder<QoreQWidget> wHolder(w, xsink);

   QoreQRect *rect = 0;
   if (w) {
      p = test_object_param(params, 3);
      rect = p ? (QoreQRect *)p->getReferencedPrivateData(CID_QRECT, xsink) : 0;
      if (!rect && p) {
	 if (!xsink->isException())
	    xsink->raiseException("QTOOLTIP-SHOWTEXT-PARAM-ERROR", "this version of QToolTip_showText() does not know how to handle arguments of class '%s' as passed as the fourth argument", p->getClass()->getName());
	 return 0;
      }
   }
   ReferenceHolder<QoreQRect> rectHolder(rect, xsink);

   if (rect)
      QToolTip::showText(*(static_cast<QPoint *>(pos)), text, w ? w->getQWidget() : 0, *(static_cast<QRect *>(rect)));
   else
      QToolTip::showText(*(static_cast<QPoint *>(pos)), text, w ? w->getQWidget() : 0);

   return 0;
}

//QStyle * create ( const QString & key )
AbstractQoreNode *f_QStyleFactory_create(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   QString key;
   if (get_qstring(p, key, xsink))
      return 0;

   return return_qstyle(key, QStyleFactory::create(key), xsink);
}

//QStringList keys ()
static AbstractQoreNode *f_QStyleFactory_keys(const QoreListNode *params, ExceptionSink *xsink)
{
   QStringList strlist_rv = QStyleFactory::keys();
   QoreListNode *l = new QoreListNode();
   for (QStringList::iterator i = strlist_rv.begin(), e = strlist_rv.end(); i != e; ++i)
      l->push(new QoreStringNode((*i).toUtf8().data(), QCS_UTF8));
   return l;
}

//int qAlpha ( QRgb rgba )
static AbstractQoreNode *f_qAlpha(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   return new QoreBigIntNode(qAlpha(p ? p->getAsBigInt() : 0));
}

//int qBlue ( QRgb rgb )
static AbstractQoreNode *f_qBlue(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   return new QoreBigIntNode(qBlue(p ? p->getAsBigInt() : 0));
}

//int qGray ( int r, int g, int b )
//int qGray ( QRgb rgb )
static AbstractQoreNode *f_qGray(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   if (num_params(params) == 1)
      return new QoreBigIntNode(qGray(p ? p->getAsBigInt() : 0));
   int r = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int g = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int b = p ? p->getAsInt() : 0;

   return new QoreBigIntNode(qGray(r, g, b));
}

//int qGreen ( QRgb rgb )
static AbstractQoreNode *f_qGreen(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   return new QoreBigIntNode(qGreen(p ? p->getAsBigInt() : 0));
}

//int qRed ( QRgb rgb )
static AbstractQoreNode *f_qRed(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   return new QoreBigIntNode(qRed(p ? p->getAsBigInt() : 0));
}

//QRgb qRgb ( int r, int g, int b )
static AbstractQoreNode *f_qRgb(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int r = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int g = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int b = p ? p->getAsInt() : 0;

   return new QoreBigIntNode(qRgb(r, g, b));
}

//QRgb qRgba ( int r, int g, int b, int a )
static AbstractQoreNode *f_qRgba(const QoreListNode *params, ExceptionSink *xsink)
{
   const AbstractQoreNode *p = get_param(params, 0);
   int r = p ? p->getAsInt() : 0;
   p = get_param(params, 1);
   int g = p ? p->getAsInt() : 0;
   p = get_param(params, 2);
   int b = p ? p->getAsInt() : 0;
   p = get_param(params, 3);
   int a = p ? p->getAsInt() : 0;

   return new QoreBigIntNode(qRgba(r, g, b, a));
}

static QoreNamespace qt_ns("Qt");

static void init_namespace()
{
    // the order is sensitive here as child classes need the parent IDs
   QoreClass *qwidget, *qlayout,
      *qboxlayout, *qpaintdevice, *qpixmap;

   qt_ns.addSystemClass(initQApplicationClass(QC_QCoreApplication));
   qt_ns.addSystemClass(initQActionClass(QC_QObject));
   qt_ns.addSystemClass(initQActionGroupClass(QC_QObject));
   qt_ns.addSystemClass(initQShortcutClass(QC_QObject));

   qt_ns.addSystemClass((qpaintdevice = initQPaintDeviceClass()));
   qt_ns.addSystemClass(initQPictureClass(qpaintdevice));

   qt_ns.addSystemClass((qpixmap = initQPixmapClass(qpaintdevice)));
   qt_ns.addSystemClass(initQBitmapClass(qpixmap));

   qt_ns.addSystemClass((qwidget = initQWidgetClass(QC_QObject, qpaintdevice)));

   qt_ns.addSystemClass(initQBrushClass());
   qt_ns.addSystemClass(initQColorClass());

   qt_ns.addSystemClass(initQColorDialogClass());

   qt_ns.addSystemClass(initQKeySequenceClass());
   qt_ns.addSystemClass(initQMatrixClass());

   QoreNamespace *qimage = new QoreNamespace("QImage");

   // InvertMode enum
   qimage->addConstant("InvertRgb",                new QoreBigIntNode(QImage::InvertRgb));
   qimage->addConstant("InvertRgba",               new QoreBigIntNode(QImage::InvertRgba));

   // Format enum
   qimage->addConstant("Format_Invalid",           new QoreBigIntNode(QImage::Format_Invalid));
   qimage->addConstant("Format_Mono",              new QoreBigIntNode(QImage::Format_Mono));
   qimage->addConstant("Format_MonoLSB",           new QoreBigIntNode(QImage::Format_MonoLSB));
   qimage->addConstant("Format_Indexed8",          new QoreBigIntNode(QImage::Format_Indexed8));
   qimage->addConstant("Format_RGB32",             new QoreBigIntNode(QImage::Format_RGB32));
   qimage->addConstant("Format_ARGB32",            new QoreBigIntNode(QImage::Format_ARGB32));
   qimage->addConstant("Format_ARGB32_Premultiplied", new QoreBigIntNode(QImage::Format_ARGB32_Premultiplied));
   qimage->addConstant("Format_RGB16",             new QoreBigIntNode(QImage::Format_RGB16));

   qimage->addSystemClass(initQImageClass(qpaintdevice));

   qt_ns.addInitialNamespace(qimage);

   QoreNamespace *qregion = new QoreNamespace("QRegion");
   
   // RegionType enum
   qregion->addConstant("Rectangle",                new QoreBigIntNode(QRegion::Rectangle));
   qregion->addConstant("Ellipse",                  new QoreBigIntNode(QRegion::Ellipse));

   qregion->addSystemClass(initQRegionClass());

   qt_ns.addInitialNamespace(qregion);

   QoreClass *qlayoutitem;
   qt_ns.addSystemClass((qlayoutitem = initQLayoutItemClass()));

   QoreNamespace *qlayout_ns = new QoreNamespace("QLayout");

   qlayout_ns->addSystemClass((qlayout = initQLayoutClass(QC_QObject, qlayoutitem)));
   qlayout_ns->addSystemClass(initQGridLayoutClass(qlayout));

   qlayout_ns->addSystemClass((qboxlayout = initQBoxLayoutClass(qlayout)));
   qlayout_ns->addSystemClass(initQVBoxLayoutClass(qboxlayout));
   qlayout_ns->addSystemClass(initQHBoxLayoutClass(qboxlayout));

   qlayout_ns->addConstant("SetNoConstraint",          new QoreBigIntNode(QLayout::SetNoConstraint));
   qlayout_ns->addConstant("SetMinimumSize",           new QoreBigIntNode(QLayout::SetMinimumSize));
   qlayout_ns->addConstant("SetFixedSize",             new QoreBigIntNode(QLayout::SetFixedSize));
   qlayout_ns->addConstant("SetMaximumSize",           new QoreBigIntNode(QLayout::SetMaximumSize));
   qlayout_ns->addConstant("SetMinAndMaxSize",         new QoreBigIntNode(QLayout::SetMinAndMaxSize));

   qt_ns.addInitialNamespace(qlayout_ns);

   QoreNamespace *qmovie = new QoreNamespace("QMovie");

   // MovieState enum
   qmovie->addConstant("NotRunning",               new QoreBigIntNode(QMovie::NotRunning));
   qmovie->addConstant("Paused",                   new QoreBigIntNode(QMovie::Paused));
   qmovie->addConstant("Running",                  new QoreBigIntNode(QMovie::Running));

   // CacheMode enum
   qmovie->addConstant("CacheNone",                new QoreBigIntNode(QMovie::CacheNone));
   qmovie->addConstant("CacheAll",                 new QoreBigIntNode(QMovie::CacheAll));

   qmovie->addSystemClass(initQMovieClass(QC_QObject));

   qt_ns.addInitialNamespace(qmovie);

   QoreNamespace *qsizepolicy = new QoreNamespace("QSizePolicy");

   // PolicyFlag enum
   qsizepolicy->addConstant("GrowFlag",                 new QoreBigIntNode(QSizePolicy::GrowFlag));
   qsizepolicy->addConstant("ExpandFlag",               new QoreBigIntNode(QSizePolicy::ExpandFlag));
   qsizepolicy->addConstant("ShrinkFlag",               new QoreBigIntNode(QSizePolicy::ShrinkFlag));
   qsizepolicy->addConstant("IgnoreFlag",               new QoreBigIntNode(QSizePolicy::IgnoreFlag));

   // Policy enum
   qsizepolicy->addConstant("Fixed",                    new QoreBigIntNode(QSizePolicy::Fixed));
   qsizepolicy->addConstant("Minimum",                  new QoreBigIntNode(QSizePolicy::Minimum));
   qsizepolicy->addConstant("Maximum",                  new QoreBigIntNode(QSizePolicy::Maximum));
   qsizepolicy->addConstant("Preferred",                new QoreBigIntNode(QSizePolicy::Preferred));
   qsizepolicy->addConstant("MinimumExpanding",         new QoreBigIntNode(QSizePolicy::MinimumExpanding));
   qsizepolicy->addConstant("Expanding",                new QoreBigIntNode(QSizePolicy::Expanding));
   qsizepolicy->addConstant("Ignored",                  new QoreBigIntNode(QSizePolicy::Ignored));

   // ControlType enum
   qsizepolicy->addConstant("DefaultType",              new QoreBigIntNode(QSizePolicy::DefaultType));
   qsizepolicy->addConstant("ButtonBox",                new QoreBigIntNode(QSizePolicy::ButtonBox));
   qsizepolicy->addConstant("CheckBox",                 new QoreBigIntNode(QSizePolicy::CheckBox));
   qsizepolicy->addConstant("ComboBox",                 new QoreBigIntNode(QSizePolicy::ComboBox));
   qsizepolicy->addConstant("Frame",                    new QoreBigIntNode(QSizePolicy::Frame));
   qsizepolicy->addConstant("GroupBox",                 new QoreBigIntNode(QSizePolicy::GroupBox));
   qsizepolicy->addConstant("Label",                    new QoreBigIntNode(QSizePolicy::Label));
   qsizepolicy->addConstant("Line",                     new QoreBigIntNode(QSizePolicy::Line));
   qsizepolicy->addConstant("LineEdit",                 new QoreBigIntNode(QSizePolicy::LineEdit));
   qsizepolicy->addConstant("PushButton",               new QoreBigIntNode(QSizePolicy::PushButton));
   qsizepolicy->addConstant("RadioButton",              new QoreBigIntNode(QSizePolicy::RadioButton));
   qsizepolicy->addConstant("Slider",                   new QoreBigIntNode(QSizePolicy::Slider));
   qsizepolicy->addConstant("SpinBox",                  new QoreBigIntNode(QSizePolicy::SpinBox));
   qsizepolicy->addConstant("TabWidget",                new QoreBigIntNode(QSizePolicy::TabWidget));
   qsizepolicy->addConstant("ToolButton",               new QoreBigIntNode(QSizePolicy::ToolButton));

   qt_ns.addInitialNamespace(qsizepolicy);

   QoreNamespace *qicon = new QoreNamespace("QIcon");

   // Mode enum
   qicon->addConstant("Normal",                   new QoreBigIntNode(QIcon::Normal));
   qicon->addConstant("Disabled",                 new QoreBigIntNode(QIcon::Disabled));
   qicon->addConstant("Active",                   new QoreBigIntNode(QIcon::Active));
   qicon->addConstant("Selected",                 new QoreBigIntNode(QIcon::Selected));

   // State enum
   qicon->addConstant("On",                       new QoreBigIntNode(QIcon::On));
   qicon->addConstant("Off",                      new QoreBigIntNode(QIcon::Off));

   qicon->addSystemClass(initQIconClass());
   qt_ns.addInitialNamespace(qicon);

   qt_ns.addInitialNamespace(initQPaletteNS());

   QoreNamespace *qpainter_ns = new QoreNamespace("QPainter");
   
   // RenderHint enum
   qpainter_ns->addConstant("Antialiasing",             new QoreBigIntNode(QPainter::Antialiasing));
   qpainter_ns->addConstant("TextAntialiasing",         new QoreBigIntNode(QPainter::TextAntialiasing));
   qpainter_ns->addConstant("SmoothPixmapTransform",    new QoreBigIntNode(QPainter::SmoothPixmapTransform));
   qpainter_ns->addConstant("HighQualityAntialiasing",  new QoreBigIntNode(QPainter::HighQualityAntialiasing));
   
   // CompositionMode enum
   qpainter_ns->addConstant("CompositionMode_SourceOver",      new QoreBigIntNode(QPainter::CompositionMode_SourceOver));
   qpainter_ns->addConstant("CompositionMode_DestinationOver", new QoreBigIntNode(QPainter::CompositionMode_DestinationOver));
   qpainter_ns->addConstant("CompositionMode_Clear",           new QoreBigIntNode(QPainter::CompositionMode_Clear));
   qpainter_ns->addConstant("CompositionMode_Source",          new QoreBigIntNode(QPainter::CompositionMode_Source));
   qpainter_ns->addConstant("CompositionMode_Destination",     new QoreBigIntNode(QPainter::CompositionMode_Destination));
   qpainter_ns->addConstant("CompositionMode_SourceIn",        new QoreBigIntNode(QPainter::CompositionMode_SourceIn));
   qpainter_ns->addConstant("CompositionMode_DestinationIn",   new QoreBigIntNode(QPainter::CompositionMode_DestinationIn));
   qpainter_ns->addConstant("CompositionMode_SourceOut",       new QoreBigIntNode(QPainter::CompositionMode_SourceOut));
   qpainter_ns->addConstant("CompositionMode_DestinationOut",  new QoreBigIntNode(QPainter::CompositionMode_DestinationOut));
   qpainter_ns->addConstant("CompositionMode_SourceAtop",      new QoreBigIntNode(QPainter::CompositionMode_SourceAtop));
   qpainter_ns->addConstant("CompositionMode_DestinationAtop", new QoreBigIntNode(QPainter::CompositionMode_DestinationAtop));
   qpainter_ns->addConstant("CompositionMode_Xor",             new QoreBigIntNode(QPainter::CompositionMode_Xor));
   qpainter_ns->addConstant("CompositionMode_Plus",            new QoreBigIntNode(QPainter::CompositionMode_Plus));
   qpainter_ns->addConstant("CompositionMode_Multiply",        new QoreBigIntNode(QPainter::CompositionMode_Multiply));
   qpainter_ns->addConstant("CompositionMode_Screen",          new QoreBigIntNode(QPainter::CompositionMode_Screen));
   qpainter_ns->addConstant("CompositionMode_Overlay",         new QoreBigIntNode(QPainter::CompositionMode_Overlay));
   qpainter_ns->addConstant("CompositionMode_Darken",          new QoreBigIntNode(QPainter::CompositionMode_Darken));
   qpainter_ns->addConstant("CompositionMode_Lighten",         new QoreBigIntNode(QPainter::CompositionMode_Lighten));
   qpainter_ns->addConstant("CompositionMode_ColorDodge",      new QoreBigIntNode(QPainter::CompositionMode_ColorDodge));
   qpainter_ns->addConstant("CompositionMode_ColorBurn",       new QoreBigIntNode(QPainter::CompositionMode_ColorBurn));
   qpainter_ns->addConstant("CompositionMode_HardLight",       new QoreBigIntNode(QPainter::CompositionMode_HardLight));
   qpainter_ns->addConstant("CompositionMode_SoftLight",       new QoreBigIntNode(QPainter::CompositionMode_SoftLight));
   qpainter_ns->addConstant("CompositionMode_Difference",      new QoreBigIntNode(QPainter::CompositionMode_Difference));
   qpainter_ns->addConstant("CompositionMode_Exclusion",       new QoreBigIntNode(QPainter::CompositionMode_Exclusion));

   qpainter_ns->addSystemClass(initQPainterClass());

   qt_ns.addInitialNamespace(qpainter_ns);

   QoreClass *qabstractbutton, *qtextformat, *qtextframeformat, *qtextcharformat,
      *qstyleoption, *qstyleoptionviewitem, *qabstractitemdelegate,
      *qabstractspinbox, *qdatetimeedit, *qabstractscrollarea, 
      *qcombobox, *qstyleoptioncomplex,
      *qtableview, *qdialog, *qvalidator;

   QoreNamespace *qdialog_ns = new QoreNamespace("QDialog");

   qdialog_ns->addSystemClass((qdialog = initQDialogClass(qwidget)));
   qdialog_ns->addInitialNamespace(initQFileDialogNS(qdialog));
   qdialog_ns->addSystemClass(initQPrintDialogClass(qdialog));

   qdialog_ns->addSystemClass(initQFontDialogClass());
   qdialog_ns->addSystemClass(initQInputDialogClass());

   qdialog_ns->addConstant("Rejected",   new QoreBigIntNode(QDialog::Rejected));
   qdialog_ns->addConstant("Accepted",   new QoreBigIntNode(QDialog::Accepted));
 
   qt_ns.addInitialNamespace(initQStyleNS(QC_QObject));

   // automatically added classes
   qt_ns.addSystemClass(initQPolygonClass());
   qt_ns.addSystemClass(initQPolygonFClass());
   qt_ns.addSystemClass((qabstractbutton = initQAbstractButtonClass(qwidget)));
   qt_ns.addSystemClass(initQPushButtonClass(qabstractbutton));
   qt_ns.addSystemClass(initQMenuClass(qwidget));
   qt_ns.addSystemClass(initQToolButtonClass(qabstractbutton));
   qt_ns.addSystemClass(initQTextLengthClass());
   qt_ns.addSystemClass((qtextformat = initQTextFormatClass()));
   qt_ns.addSystemClass(initQTextBlockFormatClass(qtextformat));
   qt_ns.addSystemClass((qtextcharformat = initQTextCharFormatClass(qtextformat)));
   qt_ns.addSystemClass(initQPenClass());
   qt_ns.addSystemClass((qtextframeformat = initQTextFrameFormatClass(qtextformat)));
   qt_ns.addSystemClass(initQTextTableFormatClass(qtextframeformat));
   qt_ns.addSystemClass(initQTextListFormatClass(qtextformat));
   qt_ns.addSystemClass(initQTextImageFormatClass(qtextcharformat));
   qt_ns.addSystemClass((qstyleoption = initQStyleOptionClass()));
   qt_ns.addSystemClass((qstyleoptioncomplex = initQStyleOptionComplexClass(qstyleoption)));
   qt_ns.addSystemClass(initQStyleOptionComboBoxClass(qstyleoptioncomplex));
   qt_ns.addSystemClass(initQStyleOptionGroupBoxClass(qstyleoptioncomplex));
   qt_ns.addSystemClass(initQStyleOptionSizeGripClass(qstyleoptioncomplex));
   qt_ns.addSystemClass(initQStyleOptionSliderClass(qstyleoptioncomplex));
   qt_ns.addSystemClass(initQStyleOptionSpinBoxClass(qstyleoptioncomplex));
   qt_ns.addSystemClass(initQStyleOptionTitleBarClass(qstyleoptioncomplex));
   qt_ns.addSystemClass(initQStyleOptionToolButtonClass(qstyleoptioncomplex));
   qt_ns.addInitialNamespace(initQStyleOptionButtonNS(qstyleoption));
   qt_ns.addSystemClass((qstyleoptionviewitem = initQStyleOptionViewItemClass(qstyleoption)));
   qt_ns.addSystemClass(initQStyleOptionViewItemV2Class(qstyleoptionviewitem));
   qt_ns.addSystemClass((qabstractitemdelegate = initQAbstractItemDelegateClass(QC_QObject)));
   qt_ns.addSystemClass(initQItemDelegateClass(qabstractitemdelegate));
   qt_ns.addSystemClass((qcombobox = initQComboBoxClass(qwidget)));
   qt_ns.addSystemClass(initQCheckBoxClass(qabstractbutton));
   qt_ns.addSystemClass((qabstractspinbox = initQAbstractSpinBoxClass(qwidget)));
   qt_ns.addSystemClass(initQGroupBoxClass(qwidget));
   qt_ns.addSystemClass(initQFontMetricsClass());
   qt_ns.addSystemClass(initQFontDatabaseClass());
   qt_ns.addSystemClass(initQFontInfoClass());

   qt_ns.addSystemClass(initQFontComboBoxClass(qcombobox));
   qt_ns.addInitialNamespace(initQMainWindowNS(qwidget));
   qt_ns.addSystemClass(initQRadioButtonClass(qabstractbutton));
   qt_ns.addSystemClass(initQSpinBoxClass(qabstractspinbox));
   qt_ns.addSystemClass(initQTableWidgetItemClass());
   qt_ns.addSystemClass(initQStyleOptionMenuItemClass(qstyleoption));
   qt_ns.addSystemClass(initQMenuBarClass(qwidget));
   qt_ns.addSystemClass((qvalidator = initQValidatorClass(QC_QObject)));
   qt_ns.addSystemClass(initQDoubleValidatorClass(qvalidator));
   qt_ns.addSystemClass(initQIntValidatorClass(qvalidator));
   qt_ns.addSystemClass(initQRegExpValidatorClass(qvalidator));
   qt_ns.addSystemClass(initQImageWriterClass());
   qt_ns.addSystemClass(initQDoubleSpinBoxClass(qabstractspinbox));
   qt_ns.addSystemClass(initQProgressBarClass(qwidget));
   qt_ns.addSystemClass(initQPainterPathClass());
   qt_ns.addSystemClass(initQPaintEngineClass());
   qt_ns.addSystemClass(initQTabBarClass(qwidget));
   qt_ns.addSystemClass(initQStyleOptionTabClass(qstyleoption));
   qt_ns.addSystemClass(initQStyleOptionTabWidgetFrameClass(qstyleoption));
   qt_ns.addSystemClass(initQTabWidgetClass(qwidget));

   qt_ns.addSystemClass(initQDesktopWidgetClass(qwidget));
   qt_ns.addSystemClass(initQWizardPageClass(qwidget));
   qt_ns.addInitialNamespace(initQListWidgetItemNS());
   qt_ns.addInitialNamespace(initQDialogButtonBoxNS(qwidget));
   qt_ns.addInitialNamespace(initQToolBarNS(qwidget));
   qdialog_ns->addSystemClass(initQProgressDialogClass(qdialog));
   qdialog_ns->addSystemClass(initQErrorMessageClass(qdialog));
   qt_ns.addSystemClass(initQStackedLayoutClass(qlayout));
   qt_ns.addInitialNamespace(initQGradientNS());
   qt_ns.addSystemClass(initQWidgetItemClass(qlayoutitem));
   qt_ns.addSystemClass(initQCursorClass());
   qt_ns.addInitialNamespace(initQStyleOptionGraphicsItemNS(qstyleoption));
   qt_ns.addInitialNamespace(initQTransformNS());
   qt_ns.addSystemClass(initQSplashScreenClass(qwidget));
   qt_ns.addSystemClass(initQSplitterClass(qwidget));
   qt_ns.addSystemClass(initQSplitterHandleClass(qwidget));
   qt_ns.addInitialNamespace(initQGraphicsItemNS());
   qt_ns.addInitialNamespace(initQTextLineNS());
   qt_ns.addInitialNamespace(initQTextOptionNS());
   qt_ns.addInitialNamespace(initQTextLayoutNS());

   // add QBoxLayout namespace and constants
   QoreNamespace *qbl = new QoreNamespace("QBoxLayout");

   // Direction enum
   qbl->addConstant("LeftToRight",    new QoreBigIntNode(QBoxLayout::LeftToRight));
   qbl->addConstant("RightToLeft",    new QoreBigIntNode(QBoxLayout::RightToLeft));
   qbl->addConstant("TopToBottom",    new QoreBigIntNode(QBoxLayout::TopToBottom));
   qbl->addConstant("BottomToTop",    new QoreBigIntNode(QBoxLayout::BottomToTop));

   qt_ns.addInitialNamespace(qbl);

   qt_ns.addInitialNamespace(initQSystemTrayIconNS(QC_QObject));

   QoreNamespace *qdatetimeedit_ns = new QoreNamespace("QDateTimeEdit");
   
   // Section enum
   qdatetimeedit_ns->addConstant("NoSection",                new QoreBigIntNode(QDateTimeEdit::NoSection));
   qdatetimeedit_ns->addConstant("AmPmSection",              new QoreBigIntNode(QDateTimeEdit::AmPmSection));
   qdatetimeedit_ns->addConstant("MSecSection",              new QoreBigIntNode(QDateTimeEdit::MSecSection));
   qdatetimeedit_ns->addConstant("SecondSection",            new QoreBigIntNode(QDateTimeEdit::SecondSection));
   qdatetimeedit_ns->addConstant("MinuteSection",            new QoreBigIntNode(QDateTimeEdit::MinuteSection));
   qdatetimeedit_ns->addConstant("HourSection",              new QoreBigIntNode(QDateTimeEdit::HourSection));
   qdatetimeedit_ns->addConstant("DaySection",               new QoreBigIntNode(QDateTimeEdit::DaySection));
   qdatetimeedit_ns->addConstant("MonthSection",             new QoreBigIntNode(QDateTimeEdit::MonthSection));
   qdatetimeedit_ns->addConstant("YearSection",              new QoreBigIntNode(QDateTimeEdit::YearSection));
   qdatetimeedit_ns->addConstant("TimeSections_Mask",        new QoreBigIntNode(QDateTimeEdit::TimeSections_Mask));
   qdatetimeedit_ns->addConstant("DateSections_Mask",        new QoreBigIntNode(QDateTimeEdit::DateSections_Mask));

   qdatetimeedit_ns->addSystemClass((qdatetimeedit = initQDateTimeEditClass(qabstractspinbox)));
   qdatetimeedit_ns->addSystemClass(initQDateEditClass(qdatetimeedit));
   qdatetimeedit_ns->addSystemClass(initQTimeEditClass(qdatetimeedit));

   qt_ns.addInitialNamespace(qdatetimeedit_ns);

   qdialog_ns->addInitialNamespace(initQWizardNS(qdialog));

   QoreNamespace *qmessagebox = new QoreNamespace("QMessageBox");
   qmessagebox->addSystemClass(initQMessageBoxClass(qdialog));

   // Icon enum
   qmessagebox->addConstant("NoIcon",                   new QoreBigIntNode(QMessageBox::NoIcon));
   qmessagebox->addConstant("Information",              new QoreBigIntNode(QMessageBox::Information));
   qmessagebox->addConstant("Warning",                  new QoreBigIntNode(QMessageBox::Warning));
   qmessagebox->addConstant("Critical",                 new QoreBigIntNode(QMessageBox::Critical));
   qmessagebox->addConstant("Question",                 new QoreBigIntNode(QMessageBox::Question));

   // ButtonRole enum
   qmessagebox->addConstant("InvalidRole",              new QoreBigIntNode(QMessageBox::InvalidRole));
   qmessagebox->addConstant("AcceptRole",               new QoreBigIntNode(QMessageBox::AcceptRole));
   qmessagebox->addConstant("RejectRole",               new QoreBigIntNode(QMessageBox::RejectRole));
   qmessagebox->addConstant("DestructiveRole",          new QoreBigIntNode(QMessageBox::DestructiveRole));
   qmessagebox->addConstant("ActionRole",               new QoreBigIntNode(QMessageBox::ActionRole));
   qmessagebox->addConstant("HelpRole",                 new QoreBigIntNode(QMessageBox::HelpRole));
   qmessagebox->addConstant("YesRole",                  new QoreBigIntNode(QMessageBox::YesRole));
   qmessagebox->addConstant("NoRole",                   new QoreBigIntNode(QMessageBox::NoRole));
   qmessagebox->addConstant("ResetRole",                new QoreBigIntNode(QMessageBox::ResetRole));
   qmessagebox->addConstant("ApplyRole",                new QoreBigIntNode(QMessageBox::ApplyRole));

   // StandardButton enum
   qmessagebox->addConstant("NoButton",                 new QoreBigIntNode(QMessageBox::NoButton));
   qmessagebox->addConstant("Ok",                       new QoreBigIntNode(QMessageBox::Ok));
   qmessagebox->addConstant("Save",                     new QoreBigIntNode(QMessageBox::Save));
   qmessagebox->addConstant("SaveAll",                  new QoreBigIntNode(QMessageBox::SaveAll));
   qmessagebox->addConstant("Open",                     new QoreBigIntNode(QMessageBox::Open));
   qmessagebox->addConstant("Yes",                      new QoreBigIntNode(QMessageBox::Yes));
   qmessagebox->addConstant("YesToAll",                 new QoreBigIntNode(QMessageBox::YesToAll));
   qmessagebox->addConstant("No",                       new QoreBigIntNode(QMessageBox::No));
   qmessagebox->addConstant("NoToAll",                  new QoreBigIntNode(QMessageBox::NoToAll));
   qmessagebox->addConstant("Abort",                    new QoreBigIntNode(QMessageBox::Abort));
   qmessagebox->addConstant("Retry",                    new QoreBigIntNode(QMessageBox::Retry));
   qmessagebox->addConstant("Ignore",                   new QoreBigIntNode(QMessageBox::Ignore));
   qmessagebox->addConstant("Close",                    new QoreBigIntNode(QMessageBox::Close));
   qmessagebox->addConstant("Cancel",                   new QoreBigIntNode(QMessageBox::Cancel));
   qmessagebox->addConstant("Discard",                  new QoreBigIntNode(QMessageBox::Discard));
   qmessagebox->addConstant("Help",                     new QoreBigIntNode(QMessageBox::Help));
   qmessagebox->addConstant("Apply",                    new QoreBigIntNode(QMessageBox::Apply));
   qmessagebox->addConstant("Reset",                    new QoreBigIntNode(QMessageBox::Reset));
   qmessagebox->addConstant("RestoreDefaults",          new QoreBigIntNode(QMessageBox::RestoreDefaults));
   qmessagebox->addConstant("FirstButton",              new QoreBigIntNode(QMessageBox::FirstButton));
   qmessagebox->addConstant("LastButton",               new QoreBigIntNode(QMessageBox::LastButton));
   qmessagebox->addConstant("YesAll",                   new QoreBigIntNode(QMessageBox::YesAll));
   qmessagebox->addConstant("NoAll",                    new QoreBigIntNode(QMessageBox::NoAll));
   qmessagebox->addConstant("Default",                  new QoreBigIntNode(QMessageBox::Default));
   qmessagebox->addConstant("Escape",                   new QoreBigIntNode(QMessageBox::Escape));
   qmessagebox->addConstant("FlagMask",                 new QoreBigIntNode(QMessageBox::FlagMask));
   qmessagebox->addConstant("ButtonMask",               new QoreBigIntNode(QMessageBox::ButtonMask));

   qdialog_ns->addInitialNamespace(qmessagebox);

   qt_ns.addInitialNamespace(qdialog_ns);

   QoreNamespace *qprinter = new QoreNamespace("QPrinter");

   qprinter->addSystemClass(initQPrinterClass(qpaintdevice));

   // PrinterMode enum
   qprinter->addConstant("ScreenResolution",         new QoreBigIntNode(QPrinter::ScreenResolution));
   qprinter->addConstant("PrinterResolution",        new QoreBigIntNode(QPrinter::PrinterResolution));
   qprinter->addConstant("HighResolution",           new QoreBigIntNode(QPrinter::HighResolution));

   // Orientation enum
   qprinter->addConstant("Portrait",                 new QoreBigIntNode(QPrinter::Portrait));
   qprinter->addConstant("Landscape",                new QoreBigIntNode(QPrinter::Landscape));

   // PageSize enum
   qprinter->addConstant("A4",                       new QoreBigIntNode(QPrinter::A4));
   qprinter->addConstant("B5",                       new QoreBigIntNode(QPrinter::B5));
   qprinter->addConstant("Letter",                   new QoreBigIntNode(QPrinter::Letter));
   qprinter->addConstant("Legal",                    new QoreBigIntNode(QPrinter::Legal));
   qprinter->addConstant("Executive",                new QoreBigIntNode(QPrinter::Executive));
   qprinter->addConstant("A0",                       new QoreBigIntNode(QPrinter::A0));
   qprinter->addConstant("A1",                       new QoreBigIntNode(QPrinter::A1));
   qprinter->addConstant("A2",                       new QoreBigIntNode(QPrinter::A2));
   qprinter->addConstant("A3",                       new QoreBigIntNode(QPrinter::A3));
   qprinter->addConstant("A5",                       new QoreBigIntNode(QPrinter::A5));
   qprinter->addConstant("A6",                       new QoreBigIntNode(QPrinter::A6));
   qprinter->addConstant("A7",                       new QoreBigIntNode(QPrinter::A7));
   qprinter->addConstant("A8",                       new QoreBigIntNode(QPrinter::A8));
   qprinter->addConstant("A9",                       new QoreBigIntNode(QPrinter::A9));
   qprinter->addConstant("B0",                       new QoreBigIntNode(QPrinter::B0));
   qprinter->addConstant("B1",                       new QoreBigIntNode(QPrinter::B1));
   qprinter->addConstant("B10",                      new QoreBigIntNode(QPrinter::B10));
   qprinter->addConstant("B2",                       new QoreBigIntNode(QPrinter::B2));
   qprinter->addConstant("B3",                       new QoreBigIntNode(QPrinter::B3));
   qprinter->addConstant("B4",                       new QoreBigIntNode(QPrinter::B4));
   qprinter->addConstant("B6",                       new QoreBigIntNode(QPrinter::B6));
   qprinter->addConstant("B7",                       new QoreBigIntNode(QPrinter::B7));
   qprinter->addConstant("B8",                       new QoreBigIntNode(QPrinter::B8));
   qprinter->addConstant("B9",                       new QoreBigIntNode(QPrinter::B9));
   qprinter->addConstant("C5E",                      new QoreBigIntNode(QPrinter::C5E));
   qprinter->addConstant("Comm10E",                  new QoreBigIntNode(QPrinter::Comm10E));
   qprinter->addConstant("DLE",                      new QoreBigIntNode(QPrinter::DLE));
   qprinter->addConstant("Folio",                    new QoreBigIntNode(QPrinter::Folio));
   qprinter->addConstant("Ledger",                   new QoreBigIntNode(QPrinter::Ledger));
   qprinter->addConstant("Tabloid",                  new QoreBigIntNode(QPrinter::Tabloid));
   qprinter->addConstant("Custom",                   new QoreBigIntNode(QPrinter::Custom));

   // PageOrder enum
   qprinter->addConstant("FirstPageFirst",           new QoreBigIntNode(QPrinter::FirstPageFirst));
   qprinter->addConstant("LastPageFirst",            new QoreBigIntNode(QPrinter::LastPageFirst));
   
   // ColorMode enum
   qprinter->addConstant("GrayScale",                new QoreBigIntNode(QPrinter::GrayScale));
   qprinter->addConstant("Color",                    new QoreBigIntNode(QPrinter::Color));

   // PaperSource enum
   qprinter->addConstant("OnlyOne",                  new QoreBigIntNode(QPrinter::OnlyOne));
   qprinter->addConstant("Lower",                    new QoreBigIntNode(QPrinter::Lower));
   qprinter->addConstant("Middle",                   new QoreBigIntNode(QPrinter::Middle));
   qprinter->addConstant("Manual",                   new QoreBigIntNode(QPrinter::Manual));
   qprinter->addConstant("Envelope",                 new QoreBigIntNode(QPrinter::Envelope));
   qprinter->addConstant("EnvelopeManual",           new QoreBigIntNode(QPrinter::EnvelopeManual));
   qprinter->addConstant("Auto",                     new QoreBigIntNode(QPrinter::Auto));
   qprinter->addConstant("Tractor",                  new QoreBigIntNode(QPrinter::Tractor));
   qprinter->addConstant("SmallFormat",              new QoreBigIntNode(QPrinter::SmallFormat));
   qprinter->addConstant("LargeFormat",              new QoreBigIntNode(QPrinter::LargeFormat));
   qprinter->addConstant("LargeCapacity",            new QoreBigIntNode(QPrinter::LargeCapacity));
   qprinter->addConstant("Cassette",                 new QoreBigIntNode(QPrinter::Cassette));
   qprinter->addConstant("FormSource",               new QoreBigIntNode(QPrinter::FormSource));
   qprinter->addConstant("MaxPageSource",            new QoreBigIntNode(QPrinter::MaxPageSource));

   // PrinterState enum
   qprinter->addConstant("Idle",                     new QoreBigIntNode(QPrinter::Idle));
   qprinter->addConstant("Active",                   new QoreBigIntNode(QPrinter::Active));
   qprinter->addConstant("Aborted",                  new QoreBigIntNode(QPrinter::Aborted));
   qprinter->addConstant("Error",                    new QoreBigIntNode(QPrinter::Error));

   // OutputFormat enum
   qprinter->addConstant("NativeFormat",             new QoreBigIntNode(QPrinter::NativeFormat));
   qprinter->addConstant("PdfFormat",                new QoreBigIntNode(QPrinter::PdfFormat));
   qprinter->addConstant("PostScriptFormat",         new QoreBigIntNode(QPrinter::PostScriptFormat));

   // PrintRange enum
   qprinter->addConstant("AllPages",                 new QoreBigIntNode(QPrinter::AllPages));
   qprinter->addConstant("Selection",                new QoreBigIntNode(QPrinter::Selection));
   qprinter->addConstant("PageRange",                new QoreBigIntNode(QPrinter::PageRange));

   qt_ns.addNamespace(qprinter);

   QoreNamespace *qlineedit = new QoreNamespace("QLineEdit");

   // EchoMode enum
   qlineedit->addConstant("Normal",                   new QoreBigIntNode(QLineEdit::Normal));
   qlineedit->addConstant("NoEcho",                   new QoreBigIntNode(QLineEdit::NoEcho));
   qlineedit->addConstant("Password",                 new QoreBigIntNode(QLineEdit::Password));
   qlineedit->addConstant("PasswordEchoOnEdit",       new QoreBigIntNode(QLineEdit::PasswordEchoOnEdit));

   qlineedit->addSystemClass(initQLineEditClass(qwidget));

   qt_ns.addNamespace(qlineedit);

   // add event class hierarchy in QtGui
   QoreClass *qinputevent, *qdropevent, *qdragmoveevent;

   QoreNamespace *qevent_ns = new QoreNamespace("QEvent");
   qevent_ns->addSystemClass(initQPaintEventClass(QC_QEvent));
   qevent_ns->addSystemClass(initQMoveEventClass(QC_QEvent));
   qevent_ns->addSystemClass(initQResizeEventClass(QC_QEvent));

   qevent_ns->addSystemClass((qinputevent = initQInputEventClass(QC_QEvent)));
   qevent_ns->addSystemClass(initQKeyEventClass(qinputevent));
   qevent_ns->addSystemClass(initQMouseEventClass(qinputevent));
   qevent_ns->addSystemClass(initQContextMenuEventClass(qinputevent));
   qevent_ns->addSystemClass(initQTabletEventClass(qinputevent));
   qevent_ns->addSystemClass(initQWheelEventClass(qinputevent));

   qevent_ns->addSystemClass(initQActionEventClass(QC_QEvent));
   qevent_ns->addSystemClass(initQCloseEventClass(QC_QEvent));

   qevent_ns->addSystemClass((qdropevent = initQDropEventClass(QC_QEvent)));
   qevent_ns->addSystemClass((qdragmoveevent = initQDragMoveEventClass(qdropevent)));
   qevent_ns->addSystemClass(initQDragEnterEventClass(qdragmoveevent));

   qevent_ns->addSystemClass(initQDragLeaveEventClass(QC_QEvent));
   qevent_ns->addSystemClass(initQFocusEventClass(QC_QEvent));
   qevent_ns->addSystemClass(initQHideEventClass(QC_QEvent));
   qevent_ns->addSystemClass(initQInputMethodEventClass(QC_QEvent));
   qevent_ns->addSystemClass(initQShowEventClass(QC_QEvent));
   qevent_ns->addSystemClass(initQHelpEventClass(QC_QEvent));

   QoreClass *qgraphicssceneevent;
   qevent_ns->addSystemClass((qgraphicssceneevent = initQGraphicsSceneEventClass(QC_QEvent)));
   qevent_ns->addNamespace(initQGraphicsSceneContextMenuEventNS(qgraphicssceneevent));
   qevent_ns->addSystemClass(initQGraphicsSceneDragDropEventClass(qgraphicssceneevent));
   qevent_ns->addSystemClass(initQGraphicsSceneHelpEventClass(qgraphicssceneevent));
   qevent_ns->addSystemClass(initQGraphicsSceneHoverEventClass(qgraphicssceneevent));
   qevent_ns->addSystemClass(initQGraphicsSceneMouseEventClass(qgraphicssceneevent));
   qevent_ns->addSystemClass(initQGraphicsSceneWheelEventClass(qgraphicssceneevent));
   qt_ns.addNamespace(qevent_ns);

   QoreNamespace *qclipboard = new QoreNamespace("QClipboard");
   
   // Mode enum
   qclipboard->addConstant("Clipboard",                new QoreBigIntNode(QClipboard::Clipboard));
   qclipboard->addConstant("Selection",                new QoreBigIntNode(QClipboard::Selection));
   qclipboard->addConstant("FindBuffer",               new QoreBigIntNode(QClipboard::FindBuffer));
   qclipboard->addConstant("LastMode",                 new QoreBigIntNode(QClipboard::LastMode));

   qclipboard->addSystemClass(initQClipboardClass(QC_QObject));

   qt_ns.addNamespace(qclipboard);

   QoreNamespace *qcalendarwidget = new QoreNamespace("QCalendarWidget");

   qcalendarwidget->addSystemClass(initQCalendarWidgetClass(qwidget));

   // SelectionMode enum
   qcalendarwidget->addConstant("NoSelection",              new QoreBigIntNode(QCalendarWidget::NoSelection));
   qcalendarwidget->addConstant("SingleSelection",          new QoreBigIntNode(QCalendarWidget::SingleSelection));

   // HorizontalHeaderFormat enum
   qcalendarwidget->addConstant("NoHorizontalHeader",       new QoreBigIntNode(QCalendarWidget::NoHorizontalHeader));
   qcalendarwidget->addConstant("SingleLetterDayNames",     new QoreBigIntNode(QCalendarWidget::SingleLetterDayNames));
   qcalendarwidget->addConstant("ShortDayNames",            new QoreBigIntNode(QCalendarWidget::ShortDayNames));
   qcalendarwidget->addConstant("LongDayNames",             new QoreBigIntNode(QCalendarWidget::LongDayNames));

   // VeritcalHeaderFormat enum
   qcalendarwidget->addConstant("NoVerticalHeader",         new QoreBigIntNode(QCalendarWidget::NoVerticalHeader));
   qcalendarwidget->addConstant("ISOWeekNumbers",           new QoreBigIntNode(QCalendarWidget::ISOWeekNumbers));

   qt_ns.addNamespace(qcalendarwidget);

   // add QFrame namespaces and constants
   QoreNamespace *qframens = new QoreNamespace("QFrame");
   QoreClass *qframe;

   qframens->addSystemClass((qframe = initQFrameClass(qwidget)));
   qframens->addSystemClass(initQLabelClass(qframe));
   qframens->addSystemClass((qabstractscrollarea = initQAbstractScrollAreaClass(qframe)));
   qframens->addSystemClass(initQScrollAreaClass(qabstractscrollarea));
   qframens->addInitialNamespace(initQTextEditNS(qabstractscrollarea));
   qframens->addSystemClass(initQStackedWidgetClass(qframe));

   // Shadow enum
   qframens->addConstant("Plain",    new QoreBigIntNode(QFrame::Plain));
   qframens->addConstant("Raised",   new QoreBigIntNode(QFrame::Raised));
   qframens->addConstant("Sunken",   new QoreBigIntNode(QFrame::Sunken));

   // Shape enum
   qframens->addConstant("NoFrame",      new QoreBigIntNode(QFrame::NoFrame));
   qframens->addConstant("Box",          new QoreBigIntNode(QFrame::Box));
   qframens->addConstant("Panel",        new QoreBigIntNode(QFrame::Panel));
   qframens->addConstant("StyledPanel",  new QoreBigIntNode(QFrame::StyledPanel));
   qframens->addConstant("HLine",        new QoreBigIntNode(QFrame::HLine));
   qframens->addConstant("VLine",        new QoreBigIntNode(QFrame::VLine));
   qframens->addConstant("WinPanel",     new QoreBigIntNode(QFrame::WinPanel));

   // StyleMask
   qframens->addConstant("Shadow_Mask",  new QoreBigIntNode(QFrame::Shadow_Mask));
   qframens->addConstant("Shape_Mask",   new QoreBigIntNode(QFrame::Shape_Mask));

   qt_ns.addNamespace(qframens);

   // add QLCDNumber namespace and constants
   class QoreNamespace *qlcdn = new QoreNamespace("QLCDNumber");
   qlcdn->addSystemClass(initQLCDNumberClass(qframe));

   qlcdn->addConstant("Outline",   new QoreBigIntNode(QLCDNumber::Outline));
   qlcdn->addConstant("Filled",    new QoreBigIntNode(QLCDNumber::Filled));
   qlcdn->addConstant("Flat",      new QoreBigIntNode(QLCDNumber::Flat));
   qlcdn->addConstant("Hex",       new QoreBigIntNode(QLCDNumber::Hex));
   qlcdn->addConstant("Dec",       new QoreBigIntNode(QLCDNumber::Dec));
   qlcdn->addConstant("Oct",       new QoreBigIntNode(QLCDNumber::Oct));
   qlcdn->addConstant("Bin",       new QoreBigIntNode(QLCDNumber::Bin));

   qt_ns.addNamespace(qlcdn);

   QoreNamespace *qabstractitemview_ns = initQAbstractItemViewNS(qabstractscrollarea);
   
   qabstractitemview_ns->addSystemClass((qtableview = initQTableViewClass(QC_QAbstractItemView)));
   qabstractitemview_ns->addSystemClass(initQTableWidgetClass(qtableview));

   qabstractitemview_ns->addNamespace(initQListViewNS(QC_QAbstractItemView));
   
   QoreNamespace *qheaderview = new QoreNamespace("QHeaderView");

   // ResizeMode enum
   qheaderview->addConstant("Interactive",              new QoreBigIntNode(QHeaderView::Interactive));
   qheaderview->addConstant("Stretch",                  new QoreBigIntNode(QHeaderView::Stretch));
   qheaderview->addConstant("Fixed",                    new QoreBigIntNode(QHeaderView::Fixed));
   qheaderview->addConstant("ResizeToContents",         new QoreBigIntNode(QHeaderView::ResizeToContents));
   qheaderview->addConstant("Custom",                   new QoreBigIntNode(QHeaderView::Custom));

   qheaderview->addSystemClass(initQHeaderViewClass(QC_QAbstractItemView));

   qabstractitemview_ns->addNamespace(qheaderview);
   qabstractitemview_ns->addSystemClass(initQTreeViewClass(QC_QAbstractItemView));

   qt_ns.addNamespace(qabstractitemview_ns);

   // add QFont namespaces and constants
   QoreNamespace *qf = new QoreNamespace("QFont");
   qf->addSystemClass(initQFontClass());

   // Weight enum
   qf->addConstant("Light",    new QoreBigIntNode(QFont::Light));
   qf->addConstant("Normal",   new QoreBigIntNode(QFont::Normal));
   qf->addConstant("DemiBold", new QoreBigIntNode(QFont::DemiBold));
   qf->addConstant("Bold",     new QoreBigIntNode(QFont::Bold));
   qf->addConstant("Black",    new QoreBigIntNode(QFont::Black));

   // StyleHint enum
   qf->addConstant("Helvetica",    new QoreBigIntNode(QFont::Helvetica));
   qf->addConstant("SansSerif",    new QoreBigIntNode(QFont::SansSerif));
   qf->addConstant("Times",        new QoreBigIntNode(QFont::Times));
   qf->addConstant("Serif",        new QoreBigIntNode(QFont::Serif));
   qf->addConstant("Courier",      new QoreBigIntNode(QFont::Courier));
   qf->addConstant("TypeWriter",   new QoreBigIntNode(QFont::TypeWriter));
   qf->addConstant("OldEnglish",   new QoreBigIntNode(QFont::OldEnglish));
   qf->addConstant("Decorative",   new QoreBigIntNode(QFont::Decorative));
   qf->addConstant("System",       new QoreBigIntNode(QFont::System));
   qf->addConstant("AnyStyle",     new QoreBigIntNode(QFont::AnyStyle));

   // StyleStrategy
   qf->addConstant("PreferDefault",    new QoreBigIntNode(QFont::PreferDefault));
   qf->addConstant("PreferBitmap",     new QoreBigIntNode(QFont::PreferBitmap));
   qf->addConstant("PreferDevice",     new QoreBigIntNode(QFont::PreferDevice));
   qf->addConstant("PreferOutline",    new QoreBigIntNode(QFont::PreferOutline));
   qf->addConstant("ForceOutline",     new QoreBigIntNode(QFont::ForceOutline));
   qf->addConstant("PreferMatch",      new QoreBigIntNode(QFont::PreferMatch));
   qf->addConstant("PreferQuality",    new QoreBigIntNode(QFont::PreferQuality));
   qf->addConstant("PreferAntialias",  new QoreBigIntNode(QFont::PreferAntialias));
   qf->addConstant("NoAntialias",      new QoreBigIntNode(QFont::NoAntialias));
   qf->addConstant("OpenGLCompatible", new QoreBigIntNode(QFont::OpenGLCompatible));
   qf->addConstant("NoFontMerging",    new QoreBigIntNode(QFont::NoFontMerging));

   // Style enum
   qf->addConstant("StyleNormal",   new QoreBigIntNode(QFont::StyleNormal));
   qf->addConstant("StyleItalic",   new QoreBigIntNode(QFont::StyleItalic));
   qf->addConstant("StyleOblique",  new QoreBigIntNode(QFont::StyleOblique));

   // Stretch enum
   qf->addConstant("UltraCondensed",  new QoreBigIntNode(QFont::UltraCondensed));
   qf->addConstant("ExtraCondensed",  new QoreBigIntNode(QFont::ExtraCondensed));
   qf->addConstant("Condensed",       new QoreBigIntNode(QFont::Condensed));
   qf->addConstant("SemiCondensed",   new QoreBigIntNode(QFont::SemiCondensed));
   qf->addConstant("Unstretched",     new QoreBigIntNode(QFont::Unstretched));
   qf->addConstant("SemiExpanded",    new QoreBigIntNode(QFont::SemiExpanded));
   qf->addConstant("Expanded",        new QoreBigIntNode(QFont::Expanded));
   qf->addConstant("ExtraExpanded",   new QoreBigIntNode(QFont::ExtraExpanded));
   qf->addConstant("UltraExpanded",   new QoreBigIntNode(QFont::UltraExpanded));

   qt_ns.addNamespace(qf);

   // add QAbstractSlider namespace and constants
   QoreNamespace *qas = new QoreNamespace("QAbstractSlider");

   QoreClass *qabstractslider;
   qas->addSystemClass((qabstractslider = initQAbstractSliderClass(qwidget)));
   qas->addSystemClass(initQScrollBarClass(qabstractslider));
   qas->addSystemClass(initQDialClass(qabstractslider));

   qas->addConstant("SliderNoAction",        new QoreBigIntNode(QAbstractSlider::SliderNoAction));
   qas->addConstant("SliderSingleStepAdd",   new QoreBigIntNode(QAbstractSlider::SliderSingleStepAdd));
   qas->addConstant("SliderSingleStepSub",   new QoreBigIntNode(QAbstractSlider::SliderSingleStepSub));
   qas->addConstant("SliderPageStepAdd",     new QoreBigIntNode(QAbstractSlider::SliderPageStepAdd));
   qas->addConstant("SliderPageStepSub",     new QoreBigIntNode(QAbstractSlider::SliderPageStepSub));
   qas->addConstant("SliderToMinimum",       new QoreBigIntNode(QAbstractSlider::SliderToMinimum));
   qas->addConstant("SliderToMaximum",       new QoreBigIntNode(QAbstractSlider::SliderToMaximum));
   qas->addConstant("SliderMove",            new QoreBigIntNode(QAbstractSlider::SliderMove));
   qt_ns.addNamespace(qas);

   QoreNamespace *qslider = new QoreNamespace("QSlider");

   // TickPosition enum
   qslider->addConstant("NoTicks",                  new QoreBigIntNode(QSlider::NoTicks));
   qslider->addConstant("TicksAbove",               new QoreBigIntNode(QSlider::TicksAbove));
   qslider->addConstant("TicksLeft",                new QoreBigIntNode(QSlider::TicksLeft));
   qslider->addConstant("TicksBelow",               new QoreBigIntNode(QSlider::TicksBelow));
   qslider->addConstant("TicksRight",               new QoreBigIntNode(QSlider::TicksRight));
   qslider->addConstant("TicksBothSides",           new QoreBigIntNode(QSlider::TicksBothSides));

   qslider->addSystemClass(initQSliderClass(qabstractslider));

   QoreClass *QC_QToolTip = new QoreClass("QToolTip", QDOM_GUI);
   // QToolTip static methods
   QC_QToolTip->addStaticMethod("font",              f_QToolTip_font);
   QC_QToolTip->addStaticMethod("hideText",          f_QToolTip_hideText);
   QC_QToolTip->addStaticMethod("palette",           f_QToolTip_palette);
   QC_QToolTip->addStaticMethod("setFont",           f_QToolTip_setFont);
   QC_QToolTip->addStaticMethod("setPalette",        f_QToolTip_setPalette);
   QC_QToolTip->addStaticMethod("showText",          f_QToolTip_showText);
   qt_ns.addSystemClass(QC_QToolTip);

   QoreClass *QC_QStyleFactory = new QoreClass("QStyleFactory", QDOM_GUI);
   // QStyleFactory static functions
   QC_QStyleFactory->addStaticMethod("create",       f_QStyleFactory_create);
   QC_QStyleFactory->addStaticMethod("keys",         f_QStyleFactory_keys);
   qt_ns.addSystemClass(QC_QStyleFactory);

   qt_ns.addInitialNamespace(qslider);
   qt_ns.addSystemClass(initQDesktopServicesClass());
   qt_ns.addSystemClass(initQItemSelectionRangeClass());
   qt_ns.addInitialNamespace(initQFileIconProviderNS());
   qt_ns.addInitialNamespace(initQDirModelNS(QC_QAbstractItemModel));
   qt_ns.addSystemClass(initQStatusBarClass(QC_QWidget));
   qt_ns.addSystemClass(initQItemSelectionClass());
   qt_ns.addInitialNamespace(initQItemSelectionModelNS(QC_QObject));
   qt_ns.addInitialNamespace(initQStyleOptionDockWidgetNS(QC_QStyleOption));
   qt_ns.addInitialNamespace(initQDockWidgetNS(QC_QWidget));
   qt_ns.addSystemClass(initQSpacerItemClass(QC_QLayoutItem));
   qt_ns.addInitialNamespace(initQMdiAreaNS(QC_QAbstractScrollArea));
   qt_ns.addInitialNamespace(initQMdiSubWindowNS(QC_QWidget));
   qt_ns.addInitialNamespace(initQTreeWidgetItemNS());
   qt_ns.addSystemClass(initQTreeWidgetClass(QC_QTreeView));

   // add here
   
}

class QoreQtQFont : public QoreQtAbstractDynamicTypeHelper {
   public:
      DLLLOCAL QoreQtQFont() : QoreQtAbstractDynamicTypeHelper("QFont") {
      }
      DLLLOCAL virtual void add_qore_arg(QoreListNode &args, void *arg) {
	 QFont *qfont = reinterpret_cast<QFont *>(arg);

	 QoreObject *o_qf = new QoreObject(QC_QFont, getProgram());
	 QoreQFont *q_qf = new QoreQFont(*qfont);
	 o_qf->setPrivate(CID_QFONT, q_qf);

	 args.push(o_qf);
      }
      DLLLOCAL virtual void add_qt_arg(void *&ptr, void *&save, const AbstractQoreNode *val) {
	 assert(false);
      }
      DLLLOCAL virtual void del_arg(void *ptr) {
      }
      DLLLOCAL virtual void do_return(void *rv, const AbstractQoreNode *val) {
	 assert(false);
      }
};

class QoreQtQListWidgetItemPtr : public QoreQtAbstractDynamicTypeHelper {
   public:
      DLLLOCAL QoreQtQListWidgetItemPtr() : QoreQtAbstractDynamicTypeHelper("QListWidgetItem*") {
      }
      DLLLOCAL virtual void add_qore_arg(QoreListNode &args, void *arg) {
	 QListWidgetItem *qlwi = *(reinterpret_cast<QListWidgetItem **>(arg));
	 
	 QoreObject *o_qlwi = new QoreObject(QC_QListWidgetItem, getProgram());
	 QoreQListWidgetItem *q_qlwi = new QoreQListWidgetItem(qlwi);
	 o_qlwi->setPrivate(CID_QLISTWIDGETITEM, q_qlwi);

	 args.push(o_qlwi);
      }
      DLLLOCAL virtual void add_qt_arg(void *&ptr, void *&save, const AbstractQoreNode *val) {
	 ExceptionSink xsink;

	 QoreQListWidgetItem *qlwi = (val && val->getType() == NT_OBJECT) ? (QoreQListWidgetItem *)(reinterpret_cast<const QoreObject *>(val))->getReferencedPrivateData(CID_QLISTWIDGETITEM, &xsink) : 0;

	 save = qlwi;
	 ptr = save;
      }
      DLLLOCAL virtual void del_arg(void *ptr) {
      }
      DLLLOCAL virtual void do_return(void *rv, const AbstractQoreNode *val) {
	 assert(false);
      }
};

class QoreQtQWidgetPtr : public QoreQtAbstractDynamicTypeHelper {
   public:
      DLLLOCAL QoreQtQWidgetPtr() : QoreQtAbstractDynamicTypeHelper("QWidget*") {
      }
      DLLLOCAL virtual void add_qore_arg(QoreListNode &args, void *arg) {
	 QWidget *qw = *(reinterpret_cast<QWidget **>(arg));
	 
	 QoreObject *o_qw = new QoreObject(QC_QWidget, getProgram());
	 QoreQtQWidget *q_qw = new QoreQtQWidget(o_qw, qw, false);
	 o_qw->setPrivate(CID_QWIDGET, q_qw);

	 args.push(o_qw);
      }
      DLLLOCAL virtual void add_qt_arg(void *&ptr, void *&save, const AbstractQoreNode *val) {
	 ExceptionSink xsink;

	 QoreQWidget *widget = (val && val->getType() == NT_OBJECT) ? (QoreQWidget *)(reinterpret_cast<const QoreObject *>(val))->getReferencedPrivateData(CID_QWIDGET, &xsink) : 0;

	 save = widget;
	 ptr = save;
      }
      DLLLOCAL virtual void del_arg(void *ptr) {
      }
      DLLLOCAL virtual void do_return(void *rv, const AbstractQoreNode *val) {
	 assert(false);
      }
};

class QoreQtActivationReasonEnum : public QoreQtInt {
   public:
      DLLLOCAL QoreQtActivationReasonEnum() : QoreQtInt("QSystemTrayIcon::ActivationReason") {}
};

DLLLOCAL QoreQtQFont qqt_qfont;
DLLLOCAL QoreQtQListWidgetItemPtr qqt_qlistwidgetitem_ptr;
DLLLOCAL QoreQtQWidgetPtr qqt_qwidget_ptr;
DLLLOCAL QoreQtActivationReasonEnum qqt_qactivationreason_ptr;

static class QoreStringNode *qt_module_init() {
   // register dynamic signal/slot type support in this module
   register_qqt_dynamic_type(&qqt_qfont);
   register_qqt_dynamic_type(&qqt_qlistwidgetitem_ptr);
   register_qqt_dynamic_type(&qqt_qwidget_ptr);
   register_qqt_dynamic_type(&qqt_qactivationreason_ptr);

   // add hooks to qt-core functionality
   register_return_qvariant_hook(return_gui_qvariant);
   register_return_qobject_hook(return_gui_qobject);
   register_return_qevent_hook(return_gui_qevent);

   register_get_qvariant_hook(get_gui_qvariant);
   
   // initialize namespace (must come after type initialization)
   init_namespace();

   builtinFunctions.add("QAPP",                       f_QAPP, QDOM_GUI);

   builtinFunctions.add("qAlpha",                     f_qAlpha, QDOM_GUI);
   builtinFunctions.add("qBlue",                      f_qBlue, QDOM_GUI);
   builtinFunctions.add("qGray",                      f_qGray, QDOM_GUI);
   builtinFunctions.add("qGray",                      f_qGray, QDOM_GUI);
   builtinFunctions.add("qGreen",                     f_qGreen, QDOM_GUI);
   builtinFunctions.add("qRed",                       f_qRed, QDOM_GUI);
   builtinFunctions.add("qRgb",                       f_qRgb, QDOM_GUI);
   builtinFunctions.add("qRgba",                      f_qRgba, QDOM_GUI);

   return 0;
}

static void qt_module_ns_init(QoreNamespace *rns, QoreNamespace *qns) {
   qns->addNamespace(qt_ns.copy());
}

static void qt_module_delete() {
   if (C_Clipboard) {
      ExceptionSink xsink;
      C_Clipboard->deref(&xsink);
   }
}
