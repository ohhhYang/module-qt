#!/usr/bin/env qore

# $Self is basically a direct port of the QT tutorial to Qore 
# using Qore's "qt" module.  

# Note that Qore's "qt" module requires QT 4.3 or above 

# use the "qt-gui" module
%requires qt-gui >= 0.0.3

# $self is an object-oriented program, the application class is "editable_tree_model"
%exec-class editable_tree_model
# require all variables to be explicitly declared
%require-our
# enable all parse warnings
%enable-all-warnings

class Ui_MainWindow {
    setupUi($MainWindow) {
        if (!strlen($MainWindow.objectName()))
            $MainWindow.setObjectName("MainWindow");
        $MainWindow.resize(573, 468);
        $.exitAction = new QAction($MainWindow);
        $.exitAction.setObjectName("exitAction");
        $.insertRowAction = new QAction($MainWindow);
        $.insertRowAction.setObjectName("insertRowAction");
        $.removeRowAction = new QAction($MainWindow);
        $.removeRowAction.setObjectName("removeRowAction");
        $.insertColumnAction = new QAction($MainWindow);
        $.insertColumnAction.setObjectName("insertColumnAction");
        $.removeColumnAction = new QAction($MainWindow);
        $.removeColumnAction.setObjectName("removeColumnAction");
        $.insertChildAction = new QAction($MainWindow);
        $.insertChildAction.setObjectName("insertChildAction");
        $.centralwidget = new QWidget($MainWindow);
        $.centralwidget.setObjectName("centralwidget");
        $.vboxLayout = new QVBoxLayout($.centralwidget);
        $.vboxLayout.setSpacing(0);
        $.vboxLayout.setMargin(0);
        $.vboxLayout.setObjectName("vboxLayout");
        $.view = new QTreeView($.centralwidget);
        $.view.setObjectName("view");
        $.view.setAlternatingRowColors(True);
        $.view.setSelectionBehavior(QAbstractItemView::SelectItems);
        $.view.setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        $.view.setAnimated(False);
        $.view.setAllColumnsShowFocus(True);

        $.vboxLayout.addWidget($.view);

        $MainWindow.setCentralWidget($.centralwidget);
        $.menubar = new QMenuBar($MainWindow);
        $.menubar.setObjectName("menubar");
        $.menubar.setGeometry(new QRect(0, 0, 573, 31));
        $.fileMenu = new QMenu($.menubar);
        $.fileMenu.setObjectName("fileMenu");
        $.actionsMenu = new QMenu($.menubar);
        $.actionsMenu.setObjectName("actionsMenu");
        $MainWindow.setMenuBar($.menubar);
        $.statusbar = new QStatusBar($MainWindow);
        $.statusbar.setObjectName("statusbar");
        $MainWindow.setStatusBar($.statusbar);

        $.menubar.addAction($.fileMenu.menuAction());
        $.menubar.addAction($.actionsMenu.menuAction());
        $.fileMenu.addAction($.exitAction);
        $.actionsMenu.addAction($.insertRowAction);
        $.actionsMenu.addAction($.insertColumnAction);
        $.actionsMenu.addSeparator();
        $.actionsMenu.addAction($.removeRowAction);
        $.actionsMenu.addAction($.removeColumnAction);
        $.actionsMenu.addSeparator();
        $.actionsMenu.addAction($.insertChildAction);

        $.retranslateUi($MainWindow);

        QMetaObject::connectSlotsByName($MainWindow);
    } # setupUi

    retranslateUi($MainWindow) {
        $MainWindow.setWindowTitle(QApplication::translate("MainWindow", "Editable Tree Model", 0, QCoreApplication::UnicodeUTF8));
        $.exitAction.setText(QApplication::translate("MainWindow", "E&xit", 0, QCoreApplication::UnicodeUTF8));
        $.exitAction.setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QCoreApplication::UnicodeUTF8));
        $.insertRowAction.setText(QApplication::translate("MainWindow", "Insert Row", 0, QCoreApplication::UnicodeUTF8));
        $.insertRowAction.setShortcut(QApplication::translate("MainWindow", "Ctrl+I, R", 0, QCoreApplication::UnicodeUTF8));
        $.removeRowAction.setText(QApplication::translate("MainWindow", "Remove Row", 0, QCoreApplication::UnicodeUTF8));
        $.removeRowAction.setShortcut(QApplication::translate("MainWindow", "Ctrl+R, R", 0, QCoreApplication::UnicodeUTF8));
        $.insertColumnAction.setText(QApplication::translate("MainWindow", "Insert Column", 0, QCoreApplication::UnicodeUTF8));
        $.insertColumnAction.setShortcut(QApplication::translate("MainWindow", "Ctrl+I, C", 0, QCoreApplication::UnicodeUTF8));
        $.removeColumnAction.setText(QApplication::translate("MainWindow", "Remove Column", 0, QCoreApplication::UnicodeUTF8));
        $.removeColumnAction.setShortcut(QApplication::translate("MainWindow", "Ctrl+R, C", 0, QCoreApplication::UnicodeUTF8));
        $.insertChildAction.setText(QApplication::translate("MainWindow", "Insert Child", 0, QCoreApplication::UnicodeUTF8));
        $.insertChildAction.setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QCoreApplication::UnicodeUTF8));
        $.fileMenu.setTitle(QApplication::translate("MainWindow", "&File", 0, QCoreApplication::UnicodeUTF8));
        $.actionsMenu.setTitle(QApplication::translate("MainWindow", "&Actions", 0, QCoreApplication::UnicodeUTF8));
    } # retranslateUi
}

class MainWindow inherits QMainWindow, private Ui_MainWindow {

    constructor($parent) : QMainWindow($parent) {
	$.setupUi($self);

	my $headers = (TR("Title"), TR("Description"));

	my $file = new File();
	$file.open("default.txt");
	my $model = new TreeModel($headers, $file.read(-1));
	$file.close();

	$.view.setModel($model);
	for (my $column = 0; $column < $model.columnCount(); ++$column)
	    $.view.resizeColumnToContents($column);

	QAPP().connect($.exitAction, SIGNAL("triggered()"), SLOT("quit()"));

	$.connect($.view.selectionModel(),
		  SIGNAL("selectionChanged(const QItemSelection &, const QItemSelection &)"),
		  SLOT("updateActions()"));

	$.connect($.actionsMenu,        SIGNAL("aboutToShow()"), SLOT("updateActions()"));
	$.connect($.insertRowAction,    SIGNAL("triggered()"),   SLOT("insertRow()"));
	$.connect($.insertColumnAction, SIGNAL("triggered()"),   SLOT("insertColumn()"));
	$.connect($.removeRowAction,    SIGNAL("triggered()"),   SLOT("removeRow()"));
	$.connect($.removeColumnAction, SIGNAL("triggered()"),   SLOT("removeColumn()"));
	$.connect($.insertChildAction,  SIGNAL("triggered()"),   SLOT("insertChild()"));
	
	$.updateActions();

	# FIXME: eliminate the need for this
	$.model = $model;
    }

    updateActions() {
	my $hasSelection = boolean(strlen($.view.selectionModel().selection()));
	$.removeRowAction.setEnabled($hasSelection);
	$.removeColumnAction.setEnabled($hasSelection);

	my $hasCurrent = $.view.selectionModel().currentIndex().isValid();
	$.insertRowAction.setEnabled($hasCurrent);
	$.insertColumnAction.setEnabled($hasCurrent);

	if ($hasCurrent) {
	    $.view.closePersistentEditor($.view.selectionModel().currentIndex());

	    my $row = $.view.selectionModel().currentIndex().row();
	    my $column = $.view.selectionModel().currentIndex().column();
	    if ($.view.selectionModel().currentIndex().parent().isValid())
		$.statusBar().showMessage(sprintf(TR("Position: (%d,%d)"), $row, $column));
	    else
		$.statusBar().showMessage(sprintf(TR("Position: (%d,%d) in top level"), $row, $column));
	}
    }

    private insertChild() {
	my $index = $.view.selectionModel().currentIndex();
	printf("MainWindow::insertChild() this=%x index=%s\n", ad($self), gi($index));
	my $model = $.view.model();

	if ($model.columnCount($index) == 0) {
	    if (!$model.insertColumn(0, $index))
		return;
	}
	
	if (!$model.insertRow(0, $index))
	    return;

	for (my $column = 0; $column < $model.columnCount($index); ++$column) {
	    my $child = $model.index(0, $column, $index);
	    $model.setData($child, new QVariant("[No data]"), Qt::EditRole);
	    if (!strlen($model.headerData($column, Qt::Horizontal)))
		$model.setHeaderData($column, Qt::Horizontal, new QVariant("[No header]"), Qt::EditRole);
	}

	$.view.selectionModel().setCurrentIndex($model.index(0, 0, $index), QItemSelectionModel::ClearAndSelect);
	$.updateActions();
    }

    private insertColumn($parent) {
	if (!exists $parent) {
	    $parent = new QModelIndex();
	    #printf("MainWindow::insertColumn() creating invalid index %s\n", gi($parent));
	}

	my $model = $.view.model();
	my $column = $.view.selectionModel().currentIndex().column();

	# Insert a column in the parent item.
	my $changed = $model.insertColumn($column + 1, $parent);
	if ($changed)
	    $model.setHeaderData($column + 1, Qt::Horizontal, new QVariant("[No header]"), Qt::EditRole);
	
	$.updateActions();

	return $changed;
    }

    private insertRow() {
	my $index = $.view.selectionModel().currentIndex();
	my $model = $.view.model();

	if (!$model.insertRow($index.row()+1, $index.parent()))
	    return;

	$.updateActions();
	
	for (my $column = 0; $column < $model.columnCount($index.parent()); ++$column) {
	    #printf("MainWindow::insertRow() column=%d index.row=%n index.parent=%s\n", $column, $index.row(), gi($index.parent()));
	    my $child = $model.index($index.row() + 1, $column, $index.parent());
	    $model.setData($child, new QVariant("[No data]"), Qt::EditRole);
	}
    }

    private removeColumn($parent) {
	if (!exists $parent) {
	    $parent = new QModelIndex();
	    #printf("MainWindow::removeColumn() creating invalid index %s\n", gi($parent));
	}

	my $model = $.view.model();
	my $column = $.view.selectionModel().currentIndex().column();

	# Insert columns in each child of the parent item.
	my $changed = $model.removeColumn($column, $parent);

	if (!$parent.isValid() && $changed)
	    $.updateActions();

	return $changed;
    }

    private removeRow() {
	my $index = $.view.selectionModel().currentIndex();
	my $model = $.view.model();
	if ($model.removeRow($index.row(), $index.parent()))
	    $.updateActions();
    }
}

sub indexof($list, $v) {
    #printf("indexof() elements=%d inlist=%n\n", elements $list, inlist($v, $list));
    for (my $i = 0; $i < elements $list; ++$i) {
	if ($list[$i] == $v) {
	    #printf("indexof returning %d\n", $i);
	    return $i;
	}
    }
    return -1;
}

sub get_stack() {
    if (!HAVE_RUNTIME_THREAD_STACK_TRACE)
        return;
    my $stack = getAllThreadCallStacks(){gettid()};
    splice $stack, 0, 2;
    return map $1.type != "new-thread" ? sprintf("%s:%d %s()", $1.file, $1.line, $1.function) : "new-thread", $stack;
}

sub gi($o) {
    if ($o instanceof QModelIndex) {
	if ($o.row() == -1)
	    return sprintf("QMI(%x: INVALID)", ad($o));
	return sprintf("QMI(%x: %d/%d = %n)", ad($o), $o.row(), $o.column(), $o.internalPointer().data(0));
    }
    return sprintf("%s:%x", getClassName($o), ad($o)); 
}
sub ad($o) { return dbg_node_addr($o); }
class TreeItem {
    private $.childItems, $.itemData, $.parentItem;

    constructor($data, $parent) {
	#printf("TreeItem::constructor(data=%n, parent=%s) this=%x\n", $data, gi($parent), ad($self));
	$.parentItem = $parent;
	$.itemData = $data;
	$.childItems = ();
    }

    child($number) {
	#printf("TreeItem::child(%d) this=%x returning %x\n", $number, ad($self), ad($.childItems[$number]));
	return $.childItems[$number];
    }

    childCount() {
	return elements $.childItems;
    }

    childNumber() {
	if (exists $.parentItem) {
	    if (!elements $.parentItem.childItems) {
		printf("ERROR: this=%x parentItem=%x has no children (%N)\n", ad($self), ad($.parentItem), $.parentItem.childItems);
	    }
	    #printf("TreeItem::childNumber() %x returning %d\n", 
	    return indexof($.parentItem.childItems, $self);
	}

	return 0;
    }

    columnCount() {
	return elements $.itemData;
    }

    data($column) {
	#printf("TreeITem::data(%d) returning %n\n", $column, $.itemData[$column]);
	return $.itemData[$column];
    }

    insertChildren($position, $count, $columns) {
	if ($position < 0 || $position > elements $.childItems)
	    return False;

	for (my $row = 0; $row < $count; ++$row) {
	    my $data[$columns - 1] = NOTHING;
	    my $item = new TreeItem($data, $self);
	    if (elements $.childTems > $position)
		splice $.childItems, $position, 0, $item;
	    else
		$.childItems[$position] = $item;
	}
	
	return True;
    }

    insertColumns($position, $columns) {
	if ($position < 0 || $position > elements $.itemData)
	    return False;

	for (my $column = 0; $column < $columns; ++$column) {
	    if (elements $.itemData > $position)
		splice $.itemData, $position, 0, NOTHING;
	    else
		$.itemData[$position] = NOTHING;
	}

	foreach my $child in ($.childItems)
	    $child.insertColumns($position, $columns);

	return True;
    }

    parent() {
	return $.parentItem;
    }

    removeChildren($position, $count) {
	if ($position < 0 || $position + $count > elements $.childItems)
	    return False;

	for (my $row = 0; $row < $count; ++$row)
	    splice $.childItems, $position, 1;

	return True;
    }

    removeColumns($position, $columns) {
	if ($position < 0 || $position + $columns > elements $.itemData)
	    return False;

	for (my $column = 0; $column < $columns; ++$column)
	    splice $.itemData, $position, 1;
	foreach my $child in ($.childItems)
	    $child.removeColumns($position, $columns);

	return True;
    }

    setData($column, $value) {
	if ($column < 0 || $column >= elements $.itemData)
	    return False;

	$.itemData[$column] = $value;
	#printf("TreeItem::setData(col=%n, value=%n) this=%x it=%n\n", $column, $value, dbg_node_addr($self), $.itemData);
	return True;
    }
}

sub gb($num) {
    if (!$num)
	return;
    my $str = "                                                ";
    return substr($str, -$num);
}

class TreeModel inherits QAbstractItemModel {
    private $.rootItem;

    constructor($headers, $data, $parent) : QAbstractItemModel($parent) {
	my $rootData = ();
	foreach my $header in ($headers)
	    $rootData += $header;

	$.rootItem = new TreeItem($rootData);
	$.setupModelData(split("\n", $data), $.rootItem);

	$.showAll();
	exit();
    }

    showAll($parent, $offset) {
	printf("%sTreeModel::showAll(%s) rows=%d columns=%d\n", gb($offset), gi($parent), $.rowCount($parent), $.columnCount($parent));
	for (my $i = 0; $i < $.rowCount($parent); ++$i) {
	    printf("%s1: %s: rc=%d\n", gb($offset), gi($parent), $.rowCount($parent));
	    my $index = $.index($i, 0, $parent);
	    printf("%s2: %s: rc=%d\n", gb($offset), gi($parent), $.rowCount($parent));
	    my $item = $.getItem($index);
	    
	    printf("%s%d: %s: hc=%n, child=%s, ccnt=%n, c#=%n: %s\n", gb($offset), $i, gi($index), $.hasChildren($index), gi($item.child()), $item.childCount(), $item.childNumber(), $item.data(0));
	    printf("%s3: %s: rc=%d\n", gb($offset), gi($parent), $.rowCount($parent));
	    if ($.hasChildren($index)) {
		$.showAll($index, $offset + 2);
	    }
	}
    }

    columnCount() {
	return $.rootItem.columnCount();
    }

    data($index, $role) {
	#printf("data(index=%n, role=%n) (index valid=%n)\n", $index, $role, $index.isValid());

	if (!$index.isValid()) {
	    #printf("TreeModel::data(%s, %n) this=%x index is invalid, returning NOTHING\n", gi($index), $role, ad($self));
	    return;
	}

	if ($role != Qt::DisplayRole && $role != Qt::EditRole)
	    return;
	
	my $item = $.getItem($index);

	#printf("TreeModel::data() this=%x item=%s column=%s returning %n\n", ad($self), gi($item), $index.column(), $item.data($index.column()));

	return $item.data($index.column());
    }

    flags($index) {
	if (!$index.isValid())
	    return 0;

	return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    getItem($index) {
	if (exists $index && $index.isValid()) {
	    my $item = $index.internalPointer();
	    #if (exists $item) printf("TreeModel::getItem(%s) this=%x returning=%s\n", gi($index), ad($self), gi($item));
	    if (exists $item) return $item;
	}

	#printf("%N\n", get_stack());
	#printf("TreeModel::getItem(%s) this=%x: invalid index, returning root item\n", gi($index), ad($self));

	return $.rootItem;
    }

    headerData($section, $orientation, $role) {
	if ($orientation == Qt::Horizontal && $role == Qt::DisplayRole)
	    return $.rootItem.data($section);

	return;
    }

    index($row, $column, $parent) {
	if (exists $parent && $parent.isValid() && $parent.column() != 0) {
	    my $rv = new QModelIndex();
	    printf("TreeModel::index(%n, %n, %s) pc=%n rv=%s\n", $row, $column, gi($parent), $parent.column(), gi($rv));
	    return $rv;
	}

	my $parentItem = $.getItem($parent);

	my $childItem = $parentItem.child($row);

	my $rv;
	if (exists $childItem) {
	    if (exists $parent) printf("1: index: %s\n", gi($parent));
	    $rv = $.createIndex($row, $column, $childItem);
	}
	else
	    $rv = new QModelIndex();
	if (exists $childItem) printf("TreeModel::index(%n, %n, %s) ci=%s rv=%s\n", $row, $column, gi($parent), gi($childItem), gi($rv));
	return $rv;
    }

    insertColumns($position, $columns, $parent) {
	$.beginInsertColumns($parent, $position, $position + $columns - 1);
	my $success = $.rootItem.insertColumns($position, $columns);
	$.endInsertColumns();

	#printf("TreeModel::insertColumn(%d, %n, %s) this=%x rv=%n\n", $position, $columns, gi($parent), ad($self), $success); 
	return $success;
    }

    insertRows($position, $rows, $parent) {
	my $parentItem = $.getItem($parent);
	
	$.beginInsertRows($parent, $position, $position + $rows - 1);
	my $success = $parentItem.insertChildren($position, $rows, $.rootItem.columnCount());
	$.endInsertRows();

	return $success;
    }

    parent($index) {
	if (!$index.isValid()) {
	    #printf("QTreeModel::parent(%s) returning same invalid index\n", gi($index));
	    return $index;
	}

	my $childItem = $.getItem($index);
	my $parentItem = $childItem.parent();

	my $rv;
	if ($parentItem == $.rootItem)
	    $rv = new QModelIndex();
	else
	    $rv = $.createIndex($parentItem.childNumber(), 0, $parentItem);
	#printf("TreeModel::parent(%s) this=%x createIndex(%d, 0, %s) = %s\n", gi($index), ad($self), $parentItem.childNumber(), gi($parentItem), gi($rv));
	return $rv;
    }

    removeColumns($position, $columns, $parent) {
	$.beginRemoveColumns($parent, $position, $position + $columns - 1);
	my $success = $.rootItem.removeColumns($position, $columns);
	$.endRemoveColumns();

	if ($.rootItem.columnCount() == 0)
	    $.removeRows(0, $.rowCount());

	return $success;
    }

    removeRows($position, $rows, $parent) {
	my $parentItem = $.getItem($parent);
	
	$.beginRemoveRows($parent, $position, $position + $rows - 1);
	my $success = $parentItem.removeChildren($position, $rows);
	$.endRemoveRows();
	
	return $success;
    }

    rowCount($parent) {
	my $parentItem = $.getItem($parent);
	
	my $rv = $parentItem.childCount();
	#printf("TreeModel::rowCount(%s) this=%x rc=%n\n", gi($parent), ad($self), $rv);
	return $rv;
    }
    
    setData($index, $value, $role) {
	if ($role != Qt::EditRole)
	    return False;

	#printf("setData(index=%n, value=%n, role=%n)\n", $index, $value, $role);
	
	my $item = $.getItem($index);
	my $result = $item.setData($index.column(), $value);
	
	if ($result)
	    $.emit("dataChanged(const QModelIndex &, QModelIndex &)");
	
	return $result;
    }
    
    setHeaderData($section, $orientation, $value, $role) {
	if ($role != Qt::EditRole || $orientation != Qt::Horizontal)
	    return False;
	
	my $result = $.rootItem.setData($section, $value);
	
	if ($result)
	    $.emit("headerDataChanged(int, int, int)");
	
	return $result;
    }
    
    setupModelData($lines, $parent) {
	my $parents = list($parent);
	my $indentations = list(0);

	my $number = 0;

	while ($number < elements $lines) {
	    my $position = 0;
	    while ($position < elements $lines[$number]) {
		if ($lines[$number][$position] != " ")
		    break;
		$position++;
	    }
 
	    #printf("number=%n lines=%n position=%n indentations=%n parents=(%d) lpcc=%d\n", $number, elements $lines, $position, $indentations, elements $parents, $parents[elements $parents - 1].childCount());

	    my $lineData = trim(substr($lines[$number], $position));

	    if (strlen($lineData)) {
		# Read the column data from the rest of the line.
		my $columnData = select split("\t", $lineData), strlen($1);		
		
		if ($position > $indentations[elements $indentations - 1]) {
		    # The last child of the current parent is now the new parent
		    # unless the current parent has no children.
		    
		    my $lp = $parents[elements $parents - 1];
		    if ($lp.childCount() > 0) {
			my $lc = $lp.child($lp.childCount() - 1);
			#printf("last child of last parent: %s (%x)\n", getClassName($lc), dbg_node_addr($lc));
			$parents += $lp.child($lp.childCount() - 1);
			$indentations += $position;
		    }
		} else {
		    while ($position < $indentations[elements $indentations - 1] && elements $parents > 0) {
			pop $parents;
			pop $indentations;
		    }
		}

		# Append a new item to the current parent's list of children.
		my $lp = $parents[elements $parents - 1];
		$lp.insertChildren($lp.childCount(), 1, $.rootItem.columnCount());
		for (my $column = 0; $column < elements $columnData; ++$column) {
		    #printf("column=%n lp=%x cc=%N cd=%n\n", $column, dbg_node_addr($lp), $lp.childCount(), $columnData[$column]);
		    #printf("%d/%d: %n\n", $number, $column, $columnData[$column]);
		    $lp.child($lp.childCount() - 1).setData($column, $columnData[$column]);
		}
	    }
	    
	    $number++;
	}
    }
}

class editable_tree_model inherits QApplication {
    constructor() {
	my $window = new MainWindow();
	$window.show();
	return $.exec();
    }
}

