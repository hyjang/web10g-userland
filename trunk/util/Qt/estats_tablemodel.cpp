#include "estats_tablemodel.hpp"

EstatsTableModel::EstatsTableModel(QObject *parent, estats_agent *agent)
    : QStandardItemModel(parent)
{
    this->agent = agent;
}

