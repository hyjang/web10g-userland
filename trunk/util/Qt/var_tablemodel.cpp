#include "var_tablemodel.hpp"
#include <QSet>
#include <QDebug>
#include <QString>

VarTableModel::VarTableModel(QObject *parent, estats_nl_client *nl_client, int cid)
    : EstatsTableModel(parent, nl_client)
{
    estats_connection *conn;
    this->cid = cid;
/*
    estats::Check(estats_agent_find_connection_from_cid(&conn, agent, cid));
    estats::Check(estats_connection_get_connection_spec(&spec, conn));
    estats::Check(estats_snapshot_alloc(&newsnap, conn));
    estats::Check(estats_snapshot_alloc(&oldsnap, conn));
*/
    initialize();
}

Qt::ItemFlags VarTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QStandardItemModel::flags(index);
    if (index.isValid())
        theFlags = Qt::ItemIsSelectable|Qt::ItemIsEnabled;

    return theFlags;
}

void VarTableModel::initialize()
{
    setHorizontalHeaderLabels(QStringList() << tr("Name")
        << tr("Value") << tr("Delta"));

    estats_var* var_head;
    estats_var* var_pos;

    quint32 index = 0;
/*
    estats::Check(estats_agent_get_var_head(&var_head, agent));

    ESTATS_VAR_FOREACH(var_pos, var_head) {
        const char* name;
        
        estats::Check(estats_var_get_name(&name, var_pos));

        QList<QStandardItem*> items;

        items << new QStandardItem(name);
        items << new QStandardItem();
        items << new QStandardItem();

        varInfo[index++] = items;
    }

    QMapIterator<quint32, QList<QStandardItem*> > i(varInfo); 
    while (i.hasNext())
        appendRow(i.next().value());
*/
}

void VarTableModel::clear()
{
    QStandardItemModel::clear();
    initialize();
}

void VarTableModel::update()
{
    static int first_update = 1;
/*
    estats_var* var_head;
    estats_var* var_pos;
    estats_snapshot *tmp;

    quint32 index = 0;

    estats::Check(estats_take_snapshot(newsnap));

    estats::Check(estats_agent_get_var_head(&var_head, agent));

    ESTATS_VAR_FOREACH(var_pos, var_head) {
        ESTATS_TYPE type;
        estats_value *val = NULL;
        char* valstr;
        
        estats::Check(estats_snapshot_read_value(&val, newsnap, var_pos));
        estats::Check(estats_value_as_string(&valstr, val));

        QStandardItem* item = new QStandardItem(valstr);

        setItem(index, 1, item);

        estats_value_free(&val);
        free((void*)valstr);

        estats::Check(estats_var_get_type(&type, var_pos));

        if (!first_update && (type == ESTATS_TYPE_COUNTER32 || type == ESTATS_TYPE_COUNTER64)) {
            estats::Check(estats_snapshot_delta(&val, newsnap, oldsnap, var_pos));
            estats::Check(estats_value_as_string(&valstr, val));

            QStandardItem* item = new QStandardItem(valstr);

            setItem(index, 2, item);

            estats_value_free(&val);
            free((void*)valstr);
        }
        index++;
    }

    tmp = oldsnap;
    oldsnap = newsnap;
    newsnap = tmp;
*/
    if (first_update) first_update = 0;
}





