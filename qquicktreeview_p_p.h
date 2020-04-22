#ifndef QQUICKTREEVIEW_P_H
#define QQUICKTREEVIEW_P_H

#include <QtQuick/private/qquicktableview_p_p.h>
#include "qquicktreemodeladaptor_p.h"

QT_BEGIN_NAMESPACE

class QQuickTreeViewPrivate : public QQuickTableViewPrivate
{
    Q_DECLARE_PUBLIC(QQuickTreeView)

public:
    QQuickTreeViewPrivate();
    ~QQuickTreeViewPrivate() override;

    QVariant modelImpl() const override;
    void setModelImpl(const QVariant &newModel) override;

    void emitCurrentRowIfChanged();

    qreal effectiveRowHeight(int row) const;
    qreal effectiveColumnWidth(int column) const;

public Q_SLOTS:
    void modelUpdated();
    void modelLayoutChanged(const QList<QPersistentModelIndex> &, QAbstractItemModel::LayoutChangeHint);

public:
    // QQuickTreeModelAdaptor1 basically takes a tree model and flattens
    // it into a list (which will be displayed in the first column of
    // the table). Each node in the tree can have several columns of
    // data in the model, which we show in the remaining columns of the table.
    QQuickTreeModelAdaptor m_proxyModel;
    QVariant m_assignedModel;
    QPersistentModelIndex m_currentProxyIndex;
    int m_emittedCurrentRow = -1;
    bool m_alternatingRowColors = true;
};

#endif // QQUICKTREEVIEW_P_H
