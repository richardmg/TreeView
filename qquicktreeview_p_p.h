#ifndef QQUICKTREEVIEW_P_H
#define QQUICKTREEVIEW_P_H

#include <QtQuick/private/qquicktableview_p_p.h>

QT_BEGIN_NAMESPACE

class QQuickTreeViewPrivate : public QQuickTableViewPrivate
{
public:
    ~QQuickTreeViewPrivate() override;
    Q_DECLARE_PUBLIC(QQuickTreeView)

    void syncModel() override;

private:
    QQuickTreeModelAdaptor1 m_proxyModel;
};

#endif // QQUICKTREEVIEW_P_H
