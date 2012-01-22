#include <plexylistmodel.h>


namespace PlexyDesk
{

PlexyListModel::PlexyListModel(DataPlugin* prototype, QObject *parent) :
        QAbstractListModel(parent), m_prototype(prototype)
{
    setRoleNames(m_prototype->roleNames());
}

int PlexyListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QVariant PlexyListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_list.size())
        return QVariant();
    return m_list.at(index.row())->data(role);
}

PlexyListModel::~PlexyListModel() {
    delete m_prototype;
    clear();
}

void PlexyListModel::appendRow(DataPlugin *item)
{
    appendRows(QList<DataPlugin*>() << item);
}

void PlexyListModel::appendRows(const QList<DataPlugin *> &items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);
    foreach(DataPlugin *item, items) {
        connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
        m_list.append(item);
    }
    endInsertRows();
}

void PlexyListModel::insertRow(int row, DataPlugin *item)
{
    beginInsertRows(QModelIndex(), row, row);
    connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
    m_list.insert(row, item);
    endInsertRows();
}

void PlexyListModel::handleItemChange()
{
    DataPlugin* item = static_cast<DataPlugin*>(sender());
    QModelIndex index = indexFromItem(item);
    if(index.isValid())
        emit dataChanged(index, index);
}

DataPlugin * PlexyListModel::find(const QString &id) const
{
    foreach(DataPlugin* item, m_list) {
        if(item->id() == id) return item;
    }
    return 0;
}

QModelIndex PlexyListModel::indexFromItem(const DataPlugin *item) const
{
    Q_ASSERT(item);
    for(int row=0; row<m_list.size(); ++row) {
        if(m_list.at(row) == item) return index(row);
    }
    return QModelIndex();
}

void PlexyListModel::clear()
{
    qDeleteAll(m_list);
    m_list.clear();
}

bool PlexyListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || row >= m_list.size()) return false;
    beginRemoveRows(QModelIndex(), row, row);
    delete m_list.takeAt(row);
    endRemoveRows();
    return true;
}

bool PlexyListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || (row+count) >= m_list.size()) return false;
    beginRemoveRows(QModelIndex(), row, row+count-1);
    for(int i=0; i<count; ++i) {
        delete m_list.takeAt(row);
    }
    endRemoveRows();
    return true;
}

DataPlugin * PlexyListModel::takeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    DataPlugin* item = m_list.takeAt(row);
    endRemoveRows();
    return item;
}

} // namespace PlexyDesk
