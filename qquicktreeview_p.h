#ifndef QQUICKTREEVIEW_H
#define QQUICKTREEVIEW_H

#include <QtQuick/private/qquicktableview_p.h>

QT_BEGIN_NAMESPACE

class QQuickTreeViewPrivate;

class QQuickTreeView : public QQuickTableView
{
    Q_OBJECT
    Q_PROPERTY(QModelIndex currentViewIndex READ currentViewIndex WRITE setCurrentViewIndex NOTIFY currentViewIndexChanged);
    Q_PROPERTY(QQmlComponent *indicator READ indicator WRITE setIndicator NOTIFY indicatorChanged)

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

    Q_INVOKABLE int columnAtPos(int x, bool includeSpacing);
    Q_INVOKABLE int rowAtPos(int y, bool includeSpacing);

    Q_INVOKABLE QModelIndex viewIndex(int column, int row);
    Q_INVOKABLE QModelIndex mapToModel(const QModelIndex &viewIndex);
    Q_INVOKABLE QModelIndex mapFromModel(const QModelIndex &modelIndex);

    QModelIndex currentViewIndex() const;
    void setCurrentViewIndex(const QModelIndex &viewIndex);

    void keyPressEvent(QKeyEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

    QQmlComponent * indicator() const;
    void setIndicator(QQmlComponent * indicator);

signals:
    void currentViewIndexChanged();
    void expanded(int row);
    void collapsed(int row);
    void indicatorChanged();

private:
    Q_DISABLE_COPY(QQuickTreeView)
    Q_DECLARE_PRIVATE(QQuickTreeView)
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickTreeView)

#endif // QQUICKTREEVIEW_H
