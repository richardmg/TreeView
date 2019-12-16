#include "qquicktreeview.h"

#include <QtQuick/private/qquicktableview_p_p.h>
#include "qquicktreemodeladaptor_p.h"

QT_BEGIN_NAMESPACE

class QQuickTreeViewPrivate : public QQuickTableViewPrivate
{
public:
    ~QQuickTreeViewPrivate() override;
    Q_DECLARE_PUBLIC(QQuickTreeView)

    QQuickTreeModelAdaptor1 m_adaptor;
};

QQuickTreeViewPrivate::~QQuickTreeViewPrivate()
{
}

QQuickTreeView::QQuickTreeView(QQuickItem *parent)
    : QQuickTableView(*(new QQuickTreeViewPrivate), parent)
{
}

QQuickTreeView::~QQuickTreeView()
{
}

void QQuickTreeView::setModel(const QVariant &newModel)
{
    QVariant effectiveModelVariant = newModel;
    if (effectiveModelVariant.userType() == qMetaTypeId<QJSValue>())
        effectiveModelVariant = effectiveModelVariant.value<QJSValue>().toVariant();

    if (effectiveModelVariant.isNull()) {
        d_func()->m_adaptor.setModel(nullptr);
        QQuickTableView::setModel(QVariant());
        return;
    }

    const auto qaim = qobject_cast<QAbstractItemModel *>(qvariant_cast<QAbstractItemModel*>(effectiveModelVariant));
    if (!qaim) {
        qmlWarning(this) << "TreeView only accepts models of type QAbstractItemModel";
        return;
    }

    d_func()->m_adaptor.setModel(qaim);
    QQuickTableView::setModel(newModel);
}

bool QQuickTreeView::isExpanded(int row) const
{
    return d_func()->m_adaptor.isExpanded(row);
}

bool QQuickTreeView::hasChildren(int row) const
{
    return d_func()->m_adaptor.hasChildren(row);
}

bool QQuickTreeView::hasSiblings(int row) const
{
    return d_func()->m_adaptor.hasSiblings(row);
}

int QQuickTreeView::depth(int row) const
{
    return d_func()->m_adaptor.depthAtRow(row);
}

void QQuickTreeView::expand(int row)
{
    d_func()->m_adaptor.expandRow(row);
}

void QQuickTreeView::collapse(int row)
{
    d_func()->m_adaptor.collapseRow(row);
}

void QQuickTreeView::toggleExpanded(int row)
{
    if (isExpanded(row))
        collapse(row);
    else
        expand(row);
}

#include "moc_qquicktreeview.cpp"

QT_END_NAMESPACE
