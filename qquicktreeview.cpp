#include <QtCore/qobject.h>
#include "qquicktreeview_p.h"
#include "qquicktreemodeladaptor_p.h"

#include "qquicktreeview_p_p.h"

QT_BEGIN_NAMESPACE

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
    QObjectPrivate::connect(&m_proxyModel, &QAbstractItemModel::rowsInserted, this, &QQuickTreeViewPrivate::modelUpdated);
    QObjectPrivate::connect(&m_proxyModel, &QAbstractItemModel::rowsRemoved, this, &QQuickTreeViewPrivate::modelUpdated);

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

void QQuickTreeViewPrivate::modelUpdated()
{
    emitCurrentRowIfChanged();
}

void QQuickTreeViewPrivate::emitCurrentRowIfChanged()
{
    // m_currentIndex is a QPersistentModelIndex which will update automatically, so
    // we need this extra detour to check if is has changed after a model change.
    if (m_emittedCurrentRow == m_currentIndex.row())
        return;

    m_emittedCurrentRow = m_currentIndex.row();
    emit q_func()->currentRowChanged();
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
    Q_D(const QQuickTreeView);
    if (row < 0 || row >= d->m_proxyModel.rowCount())
        return false;

    return d_func()->m_proxyModel.isExpanded(row);
}

bool QQuickTreeView::hasChildren(int row) const
{
    Q_D(const QQuickTreeView);
    if (row < 0 || row >= d->m_proxyModel.rowCount())
        return false;

    return d_func()->m_proxyModel.hasChildren(row);
}

bool QQuickTreeView::hasSiblings(int row) const
{
    Q_D(const QQuickTreeView);
    if (row < 0 || row >= d->m_proxyModel.rowCount())
        return false;

    return d_func()->m_proxyModel.hasSiblings(row);
}

int QQuickTreeView::depth(int row) const
{
    Q_D(const QQuickTreeView);
    if (row < 0 || row >= d->m_proxyModel.rowCount())
        return -1;

    return d_func()->m_proxyModel.depthAtRow(row);
}

void QQuickTreeView::expand(int row)
{
    Q_D(QQuickTreeView);
    if (row < 0 || row >= d->m_proxyModel.rowCount())
        return;

    if (d->m_proxyModel.isExpanded(row))
        return;

    d->m_proxyModel.expandRow(row);
    emit expanded(row);
}

void QQuickTreeView::collapse(int row)
{
    Q_D(QQuickTreeView);
    if (row < 0 || row >= d->m_proxyModel.rowCount())
        return;

    if (!d->m_proxyModel.isExpanded(row))
        return;

    d_func()->m_proxyModel.collapseRow(row);
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

QModelIndex QQuickTreeView::modelIndex(int row, int column)
{
    Q_D(QQuickTreeView);

    const QModelIndex index = d->m_proxyModel.index(row, column);
    if (!index.isValid())
        return index;

    return d_func()->m_proxyModel.mapToModel(index);
}

int QQuickTreeView::currentRow() const
{
    return d_func()->m_currentIndex.row();
}

void QQuickTreeView::setCurrentRow(int row)
{
    Q_D(QQuickTreeView);
    if (d->m_currentIndex.row() == row)
        return;

    d->m_currentIndex = d->m_proxyModel.index(row, 0);
    d->emitCurrentRowIfChanged();
}

void QQuickTreeView::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        setCurrentRow(qMax(0, currentRow() - 1));
        break;
    case Qt::Key_Down:
        setCurrentRow(qMin(rows() - 1, currentRow() + 1));
        break;
    case Qt::Key_Left:
        collapse(currentRow());
        break;
    case Qt::Key_Right:
        expand(currentRow());
        break;
    default:
        break;
    }
}

bool QQuickTreeView::alternatingRowColors() const
{
    return d_func()->m_alternatingRowColors;
}

void QQuickTreeView::setAlternatingRowColors(bool alternatingRowColors)
{
    Q_D(QQuickTreeView);
    if (d->m_alternatingRowColors == alternatingRowColors)
        return;

    d->m_alternatingRowColors = alternatingRowColors;
    emit alternatingRowColorsChanged();
}

#include "moc_qquicktreeview_p.cpp"

QT_END_NAMESPACE
