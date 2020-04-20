#include "qquicktreeview_p.h"
#include "qquicktreemodeladaptor_p.h"

#include "qquicktreeview_p_p.h"

QT_BEGIN_NAMESPACE

QQuickTreeViewPrivate::~QQuickTreeViewPrivate()
{
}

void QQuickTreeViewPrivate::setModelImpl(const QVariant &newModel)
{
    Q_Q(QQuickTreeView);

    QVariant effectiveModelVariant = newModel;
    if (effectiveModelVariant.userType() == qMetaTypeId<QJSValue>())
        effectiveModelVariant = effectiveModelVariant.value<QJSValue>().toVariant();

    if (effectiveModelVariant.isNull()) {
        m_proxyModel.setModel(nullptr);
        return;
    }

    const auto qaim = qobject_cast<QAbstractItemModel *>(qvariant_cast<QAbstractItemModel*>(effectiveModelVariant));
    if (!qaim) {
        qmlWarning(q) << "TreeView only accepts models of type QAbstractItemModel";
        return;
    }

    m_proxyModel.setModel(qaim);
}

QQuickTreeView::QQuickTreeView(QQuickItem *parent)
    : QQuickTableView(*(new QQuickTreeViewPrivate), parent)
{
    const auto qaim = static_cast<QAbstractItemModel *>(&d_func()->m_proxyModel);
    const auto model = QVariant::fromValue(qaim);
    QQuickTableView::setModel(model);
}

QQuickTreeView::~QQuickTreeView()
{
}

bool QQuickTreeView::isExpanded(int row) const
{
    return d_func()->m_proxyModel.isExpanded(row);
}

bool QQuickTreeView::hasChildren(int row) const
{
    return d_func()->m_proxyModel.hasChildren(row);
}

bool QQuickTreeView::hasSiblings(int row) const
{
    return d_func()->m_proxyModel.hasSiblings(row);
}

int QQuickTreeView::depth(int row) const
{
    return d_func()->m_proxyModel.depthAtRow(row);
}

void QQuickTreeView::expand(int row)
{
    d_func()->m_proxyModel.expandRow(row);
}

void QQuickTreeView::collapse(int row)
{
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
    return d_func()->m_proxyModel.mapToModel(index);
}

#include "moc_qquicktreeview_p.cpp"

QT_END_NAMESPACE
