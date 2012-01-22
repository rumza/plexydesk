#ifndef PLEXY_LIST_MODEL_H
#define PLEXY_LIST_MODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <dataplugin.h>

namespace PlexyDesk
{

class PlexyListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PlexyListModel(DataPlugin* prototype, QObject* parent = 0);
    virtual ~PlexyListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void appendRow(DataPlugin* item);
    void appendRows(const QList<DataPlugin*> &items);
    void insertRow(int row, DataPlugin* item);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    DataPlugin* takeRow(int row);
    DataPlugin* find(const QString &id) const;
    QModelIndex indexFromItem( const DataPlugin* item) const;
    void clear();

private Q_SLOTS:
    void handleItemChange();

private:
    DataPlugin* m_prototype;
    QList<DataPlugin*> m_list;
};
} // namespace Plexydesk

#endif // PLEXY_LIST_MODEL_H
