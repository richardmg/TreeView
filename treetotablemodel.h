#ifndef TreeToTableModel_H
#define TreeToTableModel_H

#include <QAbstractProxyModel>
#include <QModelIndex>
#include <QVariant>

class TreeToTableModel : public QAbstractProxyModel
{
    Q_OBJECT

public:
    explicit TreeToTableModel();
    ~TreeToTableModel() override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
};

#endif // TreeToTableModel_H
