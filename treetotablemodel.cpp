#include "treetotablemodel.h"

TreeToTableModel::TreeToTableModel()
    : QAbstractProxyModel(nullptr)
{
}

TreeToTableModel::~TreeToTableModel()
{
}

QModelIndex TreeToTableModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column, nullptr);
}

QModelIndex TreeToTableModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}

QModelIndex TreeToTableModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    return sourceIndex;
}

QModelIndex TreeToTableModel::mapToSource(const QModelIndex &proxyIndex) const
{
    return proxyIndex;
}

int TreeToTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 6;
}

int TreeToTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}
