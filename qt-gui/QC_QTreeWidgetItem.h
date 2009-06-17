/*
 QC_QTreeWidgetItem.h
 
 Qore Programming Language

 Copyright (C) 2003 - 2009 David Nichols

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

#ifndef _QORE_QT_QC_QTREEWIDGETITEM_H

#define _QORE_QT_QC_QTREEWIDGETITEM_H

#include <QTreeWidgetItem>

DLLEXPORT extern qore_classid_t CID_QTREEWIDGETITEM;
DLLEXPORT extern QoreClass *QC_QTreeWidgetItem;
DLLEXPORT QoreNamespace *initQTreeWidgetItemNS();

class myQTreeWidgetItem : public QTreeWidgetItem {
   public:
      DLLLOCAL void pub_emitDataChanged() {
	 return emitDataChanged();
      }
};

class QoreQTreeWidgetItem : public AbstractPrivateData {   
   public:
      QTreeWidgetItem *qore_obj;
      
      DLLLOCAL QoreQTreeWidgetItem(int type = QTreeWidgetItem::Type) : qore_obj(new QTreeWidgetItem(type)) { }
      DLLLOCAL QoreQTreeWidgetItem(const QStringList& strings, int type = QTreeWidgetItem::Type) : qore_obj(new QTreeWidgetItem(strings, type)) { }
      DLLLOCAL QoreQTreeWidgetItem(QTreeWidget* parent, int type = QTreeWidgetItem::Type) : qore_obj(new QTreeWidgetItem(parent, type)) { }
      DLLLOCAL QoreQTreeWidgetItem(QTreeWidget* parent, const QStringList& strings, int type = QTreeWidgetItem::Type) : qore_obj(new QTreeWidgetItem(parent, strings, type)) { }
      DLLLOCAL QoreQTreeWidgetItem(QTreeWidget* parent, QTreeWidgetItem* preceding, int type = QTreeWidgetItem::Type) : qore_obj(new QTreeWidgetItem(parent, preceding, type)) { }
      DLLLOCAL QoreQTreeWidgetItem(QTreeWidgetItem* parent, int type = QTreeWidgetItem::Type) : qore_obj(new QTreeWidgetItem(parent, type)) { }
      DLLLOCAL QoreQTreeWidgetItem(QTreeWidgetItem* parent, const QStringList& strings, int type = QTreeWidgetItem::Type) : qore_obj(new QTreeWidgetItem(parent, strings, type)) { }
      DLLLOCAL QoreQTreeWidgetItem(QTreeWidgetItem* parent, QTreeWidgetItem* preceding, int type = QTreeWidgetItem::Type) : qore_obj(new QTreeWidgetItem(parent, preceding, type)) { }
      DLLLOCAL QoreQTreeWidgetItem(const QTreeWidgetItem& other) : qore_obj(new QTreeWidgetItem(other)) { }

      /*
      DLLLOCAL ~QoreQTreeWidgetItem() {
      }
      */

      DLLLOCAL void emitDataChanged() {
	 reinterpret_cast<myQTreeWidgetItem *>(qore_obj)->pub_emitDataChanged();
      }

      DLLLOCAL QTreeWidgetItem *getQTreeWidgetItem() {
	 return qore_obj;
      }
};

class QoreQtQTreeWidgetItem : public QoreQTreeWidgetItem {
   public:
      DLLLOCAL QoreQtQTreeWidgetItem(QTreeWidgetItem *no) {
	 qore_obj = no;
      }
};

#endif // _QORE_QT_QC_QTREEWIDGETITEM_H
