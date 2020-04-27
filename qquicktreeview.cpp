#include <QtCore/qobject.h>
#include <QtQml/qqmlcontext.h>

#include "qquicktreemodeladaptor_p.h"

#include "qquicktreeview_p_p.h"

QT_BEGIN_NAMESPACE

/*!
    \qmlproperty int QtQuick::TreeView::currentRow

    This property holds the row that has been selected as current. Selecting
    a row to be current is done by either using the arrow keys, clicking on a row
    with the mouse, or assign a value to it explicitly.

    \note \c currentRow holds the row number as shown in the view (counting from the
    root node, as if the tree model was a flat structure). It is not the same as a
    row in the model, which is always relative to the parent node. To get the
    corresponding row in the model, use \l modelIndex():
    \code
    var index = modelIndex(currentRow, 0).row;
    \endcode

    \sa modelIndex()
*/

QQuickTreeViewPrivate::QQuickTreeViewPrivate()
    : QQuickTableViewPrivate()
{
}

QQuickTreeViewPrivate::~QQuickTreeViewPrivate()
{
}

QVariant QQuickTreeViewPrivate::modelImpl() const
{
    return m_assignedModel;
}

void QQuickTreeViewPrivate::setModelImpl(const QVariant &newModel)
{
    Q_Q(QQuickTreeView);

    if (newModel == m_assignedModel)
        return;

    m_assignedModel = newModel;
    QVariant effectiveModel = m_assignedModel;
    if (effectiveModel.userType() == qMetaTypeId<QJSValue>())
        effectiveModel = effectiveModel.value<QJSValue>().toVariant();

    if (effectiveModel.isNull())
        m_proxyModel.setModel(nullptr);
    else if (const auto qaim = qvariant_cast<QAbstractItemModel*>(effectiveModel))
        m_proxyModel.setModel(qaim);
    else
        qmlWarning(q) << "treeView only accept models of type QAbstractItemModel";


    scheduleRebuildTable(QQuickTableViewPrivate::RebuildOption::All);
    emit q->modelChanged();
}

void QQuickTreeViewPrivate::syncModel()
{
    if (model) {
        QObjectPrivate::disconnect(model, &QQmlInstanceModel::initItem, this, &QQuickTreeViewPrivate::initItemCallback);
        QObjectPrivate::disconnect(model, &QQmlInstanceModel::itemReused, this, &QQuickTreeViewPrivate::itemReusedCallback);
    }

    QQuickTableViewPrivate::syncModel();

    if (model) {
        QObjectPrivate::connect(model, &QQmlInstanceModel::initItem, this, &QQuickTreeViewPrivate::initItemCallback);
        QObjectPrivate::connect(model, &QQmlInstanceModel::itemReused, this, &QQuickTreeViewPrivate::itemReusedCallback);
    }
}

void QQuickTreeViewPrivate::modelUpdated()
{
    emitModelChanges();
}

void QQuickTreeViewPrivate::emitModelChanges()
{
    // m_currentIndex is a QPersistentModelIndex which will update automatically, so
    // we need this extra detour to check if is has changed after a model change.
    if (m_currentViewIndexEmitted != m_currentViewIndex) {
        m_currentViewIndexEmitted = m_currentViewIndex;
        emit q_func()->currentViewIndexChanged();
    }
}

QQuickTreeViewAttached *QQuickTreeViewPrivate::getAttachedObject(const QObject *object) const
{
    QObject *attachedObject = qmlAttachedPropertiesObject<QQuickTreeView>(object);
    return static_cast<QQuickTreeViewAttached *>(attachedObject);
}

void QQuickTreeViewPrivate::initItemCallback(int modelIndex, QObject *object)
{
    Q_UNUSED(modelIndex);
    Q_Q(QQuickTreeView);

    if (auto attached = getAttachedObject(object)) {
        const auto context = qmlContext(object);
        const int row = context->contextProperty("row").toInt();
        attached->setIsExpanded(q->isExpanded(row));
        attached->setHasChildren(q->hasChildren(row));
    }
}

void QQuickTreeViewPrivate::itemReusedCallback(int modelIndex, QObject *object)
{
    Q_UNUSED(modelIndex);
    Q_Q(QQuickTreeView);

    if (auto attached = getAttachedObject(object)) {
        const auto context = qmlContext(object);
        const int row = context->contextProperty("row").toInt();
        attached->setIsExpanded(q->isExpanded(row));
        attached->setHasChildren(q->hasChildren(row));
    }
}

QQuickItem *QQuickTreeViewPrivate::itemAtCell(const QPoint &cell) const
{
    // (copy from qquicktableview in Qt6)
    const int modelIndex = modelIndexAtCell(cell);
    if (!loadedItems.contains(modelIndex))
        return nullptr;
    return loadedItems.value(modelIndex)->item;
}

qreal QQuickTreeViewPrivate::effectiveRowHeight(int row) const
{
    // (copy from qquicktableview in Qt6)
    return loadedTableItem(QPoint(leftColumn(), row))->geometry().height();
}

qreal QQuickTreeViewPrivate::effectiveColumnWidth(int column) const
{
    // (copy from qquicktableview in Qt6)
    return loadedTableItem(QPoint(column, topRow()))->geometry().width();
}

QQuickTreeView::QQuickTreeView(QQuickItem *parent)
    : QQuickTableView(*(new QQuickTreeViewPrivate), parent)
{
    Q_D(QQuickTreeView);

    // QQuickTableView will only ever see the proxy model
    const auto proxy = QVariant::fromValue(std::addressof(d->m_proxyModel));
    d->QQuickTableViewPrivate::setModelImpl(proxy);

    QObjectPrivate::connect(&d->m_proxyModel, &QAbstractItemModel::rowsInserted, d, &QQuickTreeViewPrivate::modelUpdated);
    QObjectPrivate::connect(&d->m_proxyModel, &QAbstractItemModel::rowsRemoved, d, &QQuickTreeViewPrivate::modelUpdated);
    QObjectPrivate::connect(&d->m_proxyModel, &QAbstractItemModel::rowsMoved, d, &QQuickTreeViewPrivate::modelUpdated);
    QObjectPrivate::connect(&d->m_proxyModel, &QAbstractItemModel::modelReset, d, &QQuickTreeViewPrivate::modelUpdated);
    QObjectPrivate::connect(&d->m_proxyModel, &QAbstractItemModel::layoutChanged, d, &QQuickTreeViewPrivate::modelUpdated);
}

QQuickTreeView::~QQuickTreeView()
{
}

bool QQuickTreeView::isExpanded(int row) const
{
    if (row < 0 || row >= rows())
        return false;

    return d_func()->m_proxyModel.isExpanded(row);
}

bool QQuickTreeView::hasChildren(int row) const
{
    if (row < 0 || row >= rows())
        return false;

    return d_func()->m_proxyModel.hasChildren(row);
}

bool QQuickTreeView::hasSiblings(int row) const
{
    if (row < 0 || row >= rows())
        return false;

    return d_func()->m_proxyModel.hasSiblings(row);
}

int QQuickTreeView::depth(int row) const
{
    if (row < 0 || row >= rows())
        return -1;

    return d_func()->m_proxyModel.depthAtRow(row);
}

void QQuickTreeView::expand(int row)
{
    Q_D(QQuickTreeView);
    if (row < 0 || row >= rows())
        return;

    if (d->m_proxyModel.isExpanded(row))
        return;

    d->m_proxyModel.expandRow(row);

    if (const auto delegateItem = d->itemAtCell(QPoint(0, row))) {
        if (auto attached = d->getAttachedObject(delegateItem))
            attached->setIsExpanded(true);
    }

    emit expanded(row);
}

void QQuickTreeView::collapse(int row)
{
    Q_D(QQuickTreeView);
    if (row < 0 || row >= rows())
        return;

    if (!d->m_proxyModel.isExpanded(row))
        return;

    d_func()->m_proxyModel.collapseRow(row);

    if (const auto delegateItem = d->itemAtCell(QPoint(0, row))) {
        if (auto attached = d->getAttachedObject(delegateItem))
            attached->setIsExpanded(false);
    }

    emit collapsed(row);
}

void QQuickTreeView::toggleExpanded(int row)
{
    if (isExpanded(row))
        collapse(row);
    else
        expand(row);
}

int QQuickTreeView::rowAtPos(int y, bool includeSpacing)
{
    // (copy from qquicktableview in Qt6)
    Q_D(const QQuickTreeView);

    if (!boundingRect().contains(QPointF(x(), y)))
        return -1;

    const qreal vSpace = d->cellSpacing.height();
    qreal currentRowEnd = d->loadedTableOuterRect.y() - contentY();
    int foundRow = -1;

    for (auto const row : qAsConst(d->loadedRows).keys()) {
        currentRowEnd += d->effectiveRowHeight(row);
        if (y < currentRowEnd) {
            foundRow = row;
            break;
        }
        currentRowEnd += vSpace;
        if (!includeSpacing && y < currentRowEnd) {
            // Hit spacing
            return -1;
        }
        if (includeSpacing && y < currentRowEnd - (vSpace / 2)) {
            foundRow = row;
            break;
        }
    }

    return foundRow;
}

int QQuickTreeView::columnAtPos(int x, bool includeSpacing)
{
    // (copy from qquicktableview in Qt6)
    Q_D(const QQuickTreeView);

    if (!boundingRect().contains(QPointF(x, y())))
        return -1;

    const qreal hSpace = d->cellSpacing.width();
    qreal currentColumnEnd = d->loadedTableOuterRect.x() - contentX();
    int foundColumn = -1;

    for (auto const column : qAsConst(d->loadedColumns).keys()) {
        currentColumnEnd += d->effectiveColumnWidth(column);
        if (x < currentColumnEnd) {
            foundColumn = column;
            break;
        }
        currentColumnEnd += hSpace;
        if (!includeSpacing && x < currentColumnEnd) {
            // Hit spacing
            return -1;
        } else if (includeSpacing && x < currentColumnEnd - (hSpace / 2)) {
            foundColumn = column;
            break;
        }
    }

    return foundColumn;
}

QModelIndex QQuickTreeView::viewIndex(int column, int row)
{
    return d_func()->m_proxyModel.index(row, column);
}

QModelIndex QQuickTreeView::mapToModel(const QModelIndex &viewIndex)
{
    return d_func()->m_proxyModel.mapToModel(viewIndex);
}

QModelIndex QQuickTreeView::mapFromModel(const QModelIndex &modelIndex)
{
    return d_func()->m_proxyModel.mapFromModel(modelIndex);
}

QModelIndex QQuickTreeView::currentViewIndex() const
{
    return d_func()->m_currentViewIndex;
}

void QQuickTreeView::setCurrentViewIndex(const QModelIndex &viewIndex)
{
    Q_D(QQuickTreeView);
    if (d->m_currentViewIndex == viewIndex)
        return;

    d->m_currentViewIndex = viewIndex;
    d->m_currentViewIndexEmitted = viewIndex;
    emit currentViewIndexChanged();
}

void QQuickTreeViewPrivate::moveCurrentViewIndex(int directionX, int directionY)
{
    Q_Q(QQuickTreeView);
    const int row = qBound(0, m_currentViewIndex.row() + directionY, q->rows() - 1);
    const int column = qBound(0, m_currentViewIndex.column() + directionX, q->columns() - 1);
    q->setCurrentViewIndex(q->viewIndex(column, row));
}

void QQuickTreeView::keyPressEvent(QKeyEvent *e)
{
    Q_D(QQuickTreeView);

    switch (e->key()) {
    case Qt::Key_Up:
        d->moveCurrentViewIndex(0, -1);
        break;
    case Qt::Key_Down:
        d->moveCurrentViewIndex(0, 1);
        break;
    case Qt::Key_Left:
        if (d->m_navigationMode == QQuickTreeView::Table)
            d->moveCurrentViewIndex(-1, 0);
        else
            collapse(d->m_currentViewIndex.row());
        break;
    case Qt::Key_Right:
        if (d->m_navigationMode == QQuickTreeView::Table)
            d->moveCurrentViewIndex(1, 0);
        else
            expand(d->m_currentViewIndex.row());
        break;
    case Qt::Key_Space:
        toggleExpanded(d->m_currentViewIndex.row());
        break;
    default:
        break;
    }
}

void QQuickTreeView::mouseReleaseEvent(QMouseEvent *e)
{
    const int column = columnAtPos(e->pos().x(), true);
    const int row = rowAtPos(e->pos().y(), true);
    if (column == -1 || row == -1)
        return;

    if (d_func()->m_navigationMode == Table)
        setCurrentViewIndex(viewIndex(column, row));
    else
        setCurrentViewIndex(viewIndex(0, row));
}

void QQuickTreeView::mouseDoubleClickEvent(QMouseEvent *e)
{
    const int row = rowAtPos(e->pos().y(), true);
    if (row == -1)
        return;

    toggleExpanded(row);
}

QQuickTreeViewAttached *QQuickTreeView::qmlAttachedProperties(QObject *obj)
{
    return new QQuickTreeViewAttached(obj);
}

QQuickTreeView::NavigateMode QQuickTreeView::navigationMode() const
{
    return d_func()->m_navigationMode;
}

void QQuickTreeView::setNavigationMode(QQuickTreeView::NavigateMode navigateMode)
{
    Q_D(QQuickTreeView);
    if (d->m_navigationMode == navigateMode)
        return;

    d->m_navigationMode = navigateMode;
    emit navigationModeChanged();
}

bool QQuickTreeViewAttached::hasChildren() const
{
    return m_hasChildren;
}

void QQuickTreeViewAttached::setHasChildren(bool hasChildren)
{
    if (m_hasChildren == hasChildren)
        return;

    m_hasChildren = hasChildren;
    emit hasChildrenChanged();
}

bool QQuickTreeViewAttached::isExpanded() const
{
    return m_isExpanded;
}

void QQuickTreeViewAttached::setIsExpanded(bool isExpanded)
{
    if (m_isExpanded == isExpanded)
        return;

    m_isExpanded = isExpanded;
    emit isExpandedChanged();
}

#include "moc_qquicktreeview_p.cpp"

QT_END_NAMESPACE
