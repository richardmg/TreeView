#include "qquicktreeview.h"

#include <QtQuick/private/qquicktableview_p_p.h>

class QQuickTreeViewPrivate : public QQuickTableViewPrivate
{

    ~QQuickTreeViewPrivate() override;
    Q_DECLARE_PUBLIC(QQuickTreeView)
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
