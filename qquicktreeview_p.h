#ifndef QQUICKTREEVIEW_H
#define QQUICKTREEVIEW_H

#include <QtQuick/private/qquicktableview_p.h>

QT_BEGIN_NAMESPACE

class QQuickTreeViewPrivate;

class QQuickTreeView : public QQuickTableView
{
    Q_OBJECT

public:
    QQuickTreeView(QQuickItem *parent = nullptr);
    ~QQuickTreeView() override;

    Q_INVOKABLE bool isExpanded(int row) const;
    Q_INVOKABLE bool hasChildren(int row) const;
    Q_INVOKABLE bool hasSiblings(int row) const;
    Q_INVOKABLE int depth(int row) const;

    Q_INVOKABLE void expand(int row);
    Q_INVOKABLE void collapse(int row);
    Q_INVOKABLE void toggleExpanded(int row);

    Q_INVOKABLE QModelIndex modelIndex(int row, int column);

private:
    Q_DISABLE_COPY(QQuickTreeView)
    Q_DECLARE_PRIVATE(QQuickTreeView)
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickTreeView)

#endif // QQUICKTREEVIEW_H
