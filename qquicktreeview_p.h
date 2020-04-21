#ifndef QQUICKTREEVIEW_H
#define QQUICKTREEVIEW_H

#include <QtQuick/private/qquicktableview_p.h>

QT_BEGIN_NAMESPACE

class QQuickTreeViewPrivate;

class QQuickTreeView : public QQuickTableView
{
    Q_OBJECT
    Q_PROPERTY(int currentRow READ currentRow WRITE setCurrentRow NOTIFY currentRowChanged);
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors NOTIFY alternatingRowColorsChanged);

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

    Q_INVOKABLE QModelIndex modelIndex(int row, int column);

    void keyPressEvent(QKeyEvent *e) override;

    int currentRow() const;
    void setCurrentRow(int row);

    bool alternatingRowColors() const;
    void setAlternatingRowColors(bool alternatingRowColors);

signals:
    void currentRowChanged();
    void alternatingRowColorsChanged();
    void expanded(int row);
    void collapsed(int row);

private:
    Q_DISABLE_COPY(QQuickTreeView)
    Q_DECLARE_PRIVATE(QQuickTreeView)
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickTreeView)

#endif // QQUICKTREEVIEW_H
