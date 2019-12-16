#ifndef QQUICKTREEVIEW_H
#define QQUICKTREEVIEW_H

#include <QtQuick/private/qquicktableview_p.h>

QT_BEGIN_NAMESPACE

class QQuickTreeView : public QQuickTableView
{
public:
    QQuickTreeView(QQuickItem *parent = nullptr);
    ~QQuickTreeView() override;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickTreeView)

#endif // QQUICKTREEVIEW_H
