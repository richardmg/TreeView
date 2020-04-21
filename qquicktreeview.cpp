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

    d->m_proxyModel.expandRow(row);
}

void QQuickTreeView::collapse(int row)
{
    Q_D(QQuickTreeView);
    if (row < 0 || row >= d->m_proxyModel.rowCount())
        return;

    d_func()->m_proxyModel.collapseRow(row);
}

void QQuickTreeView::toggleExpanded(int row)
{
    if (isExpanded(row))
        collapse(row);
    else
        expand(row);
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

#include "moc_qquicktreeview_p.cpp"

QT_END_NAMESPACE
