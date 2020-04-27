#ifndef QQUICKTREEVIEW_H
#define QQUICKTREEVIEW_H

#include <QtQuick/private/qquicktableview_p.h>

QT_BEGIN_NAMESPACE

class QQuickTreeViewPrivate;
class QQuickTreeViewAttached;

class QQuickTreeView : public QQuickTableView
{
    Q_OBJECT

    Q_PROPERTY(QModelIndex currentViewIndex READ currentViewIndex WRITE setCurrentViewIndex NOTIFY currentViewIndexChanged);
    Q_PROPERTY(NavigateMode navigationMode READ navigationMode WRITE setNavigationMode NOTIFY navigationModeChanged);

    QML_NAMED_ELEMENT(TreeView)
    QML_ADDED_IN_MINOR_VERSION(15)
    QML_ATTACHED(QQuickTreeViewAttached)

public:
    enum NavigateMode { List, Table };
    Q_ENUM(NavigateMode)

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

    NavigateMode navigationMode() const;
    void setNavigationMode(NavigateMode navigateMode);

    void keyPressEvent(QKeyEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

    static QQuickTreeViewAttached *qmlAttachedProperties(QObject *obj);

signals:
    void currentViewIndexChanged();
    void expanded(int row);
    void collapsed(int row);
    void navigationModeChanged();

private:
    Q_DISABLE_COPY(QQuickTreeView)
    Q_DECLARE_PRIVATE(QQuickTreeView)
};

class QQuickTreeViewAttached : public QQuickTableViewAttached
{
    Q_OBJECT
    Q_PROPERTY(QQuickTreeView *view READ view NOTIFY viewChanged)
    Q_PROPERTY(bool hasChildren READ hasChildren NOTIFY hasChildrenChanged)
    Q_PROPERTY(bool isExpanded READ isExpanded NOTIFY isExpandedChanged)

public:
    QQuickTreeViewAttached(QObject *parent) : QQuickTableViewAttached(parent) {}
    QQuickTreeView *view() const { return m_view; }

    bool hasChildren() const;
    void setHasChildren(bool hasChildren);

    bool isExpanded() const;
    void setIsExpanded(bool isExpanded);

Q_SIGNALS:
    void viewChanged();
    void hasChildrenChanged();
    void isExpandedChanged();

private:
    QPointer<QQuickTreeView> m_view;
    bool m_hasChildren = false;
    bool m_isExpanded = false;

    friend class QQuickTreeViewPrivate;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickTreeView)

#endif // QQUICKTREEVIEW_H
