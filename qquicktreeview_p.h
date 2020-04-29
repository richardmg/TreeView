#ifndef QQUICKTREEVIEW_H
#define QQUICKTREEVIEW_H

#include <QtQuick/private/qquicktableview_p.h>

QT_BEGIN_NAMESPACE

class QQuickTreeViewPrivate;
class QQuickTreeViewAttached;

class QQuickTreeViewStyleHints : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor indicator MEMBER m_indicator NOTIFY indicatorChanged);
    Q_PROPERTY(QColor overlay MEMBER m_overlay NOTIFY overlayChanged);
    Q_PROPERTY(QColor foregroundOdd MEMBER m_foregroundOdd NOTIFY foregroundOddChanged);
    Q_PROPERTY(QColor backgroundOdd MEMBER m_backgroundOdd NOTIFY backgroundOddChanged);
    Q_PROPERTY(QColor foregroundEven MEMBER m_foregroundEven NOTIFY foregroundEvenChanged);
    Q_PROPERTY(QColor backgroundEven MEMBER m_backgroundEven NOTIFY backgroundEvenChanged);
    Q_PROPERTY(QColor foregroundCurrent MEMBER m_foregroundCurrent NOTIFY foregroundCurrentChanged);
    Q_PROPERTY(QColor backgroundCurrent MEMBER m_backgroundCurrent NOTIFY backgroundCurrentChanged);
    Q_PROPERTY(qreal indent MEMBER m_indent NOTIFY indentChanged);
    Q_PROPERTY(qreal columnPadding MEMBER m_columnPadding NOTIFY columnPaddingChanged);

    QML_NAMED_ELEMENT(TreeViewStyleHints)
    QML_UNCREATABLE("TreeViewStyleHints is not creatable")
    QML_ADDED_IN_MINOR_VERSION(15)

signals:
    void indicatorChanged();
    void overlayChanged();
    void foregroundOddChanged();
    void backgroundOddChanged();
    void foregroundEvenChanged();
    void backgroundEvenChanged();
    void foregroundCurrentChanged();
    void backgroundCurrentChanged();
    void indentChanged();
    void columnPaddingChanged();

private:
    QColor m_indicator;
    QColor m_overlay;
    QColor m_foregroundOdd;
    QColor m_backgroundOdd;
    QColor m_foregroundEven;
    QColor m_backgroundEven;
    QColor m_foregroundCurrent;
    QColor m_backgroundCurrent;
    qreal m_indent = 0;
    qreal m_columnPadding = 0;
};

class QQuickTreeView : public QQuickTableView
{
    Q_OBJECT

    Q_PROPERTY(QModelIndex currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged);
    Q_PROPERTY(QModelIndex currentModelIndex READ currentModelIndex WRITE setCurrentModelIndex NOTIFY currentModelIndexChanged);
    Q_PROPERTY(QQuickItem *currentItem READ currentItem NOTIFY currentItemChanged);
    Q_PROPERTY(NavigateMode navigationMode READ navigationMode WRITE setNavigationMode NOTIFY navigationModeChanged);
    Q_PROPERTY(QQuickTreeViewStyleHints *styleHints READ styleHints CONSTANT);

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

    Q_INVOKABLE void collapseModelIndex(const QModelIndex &modelIndex);
    Q_INVOKABLE void expandModelIndex(const QModelIndex &modelIndex);
    Q_INVOKABLE void toggleModelIndexExpanded(const QModelIndex &modelIndex);

    Q_INVOKABLE int columnAtPos(int x, bool includeSpacing);
    Q_INVOKABLE int rowAtPos(int y, bool includeSpacing);

    Q_INVOKABLE QQuickItem *itemAtCell(const QPoint &cell) const;
    Q_INVOKABLE QQuickItem *itemAtIndex(const QModelIndex &viewIndex) const;
    Q_INVOKABLE QQuickItem *itemAtModelIndex(const QModelIndex &modelIndex) const;

    Q_INVOKABLE QModelIndex viewIndex(int column, int row);
    Q_INVOKABLE QModelIndex mapToModel(const QModelIndex &viewIndex) const;
    Q_INVOKABLE QModelIndex mapFromModel(const QModelIndex &modelIndex) const;

    QModelIndex currentIndex() const;
    void setCurrentIndex(const QModelIndex &index);
    QQuickItem *currentItem() const;

    QModelIndex currentModelIndex() const;
    void setCurrentModelIndex(const QModelIndex &modelIndex);

    NavigateMode navigationMode() const;
    void setNavigationMode(NavigateMode navigateMode);

    QQuickTreeViewStyleHints *styleHints();

    static QQuickTreeViewAttached *qmlAttachedProperties(QObject *obj);

protected:
    void viewportMoved(Qt::Orientations orientation) override;
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

signals:
    void currentIndexChanged();
    void currentModelIndexChanged();
    void expanded(int row);
    void collapsed(int row);
    void navigationModeChanged();
    void currentItemChanged();

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
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)

public:
    QQuickTreeViewAttached(QObject *parent) : QQuickTableViewAttached(parent) {}
    QQuickTreeView *view() const { return m_view; }

    bool hasChildren() const;
    void setHasChildren(bool hasChildren);

    bool isExpanded() const;
    void setIsExpanded(bool isExpanded);

    int depth();
    void setDepth(int depth);

Q_SIGNALS:
    void viewChanged();
    void hasChildrenChanged();
    void isExpandedChanged();
    void depthChanged();

private:
    QPointer<QQuickTreeView> m_view;
    bool m_hasChildren = false;
    bool m_isExpanded = false;
    int m_depth = -1;

    friend class QQuickTreeViewPrivate;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickTreeView)

#endif // QQUICKTREEVIEW_H
