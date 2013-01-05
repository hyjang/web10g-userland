#ifndef ESTATSTABLEMODEL_HPP
#define ESTATSTABLEMODEL_HPP

#include "EstatsView.hpp"
#include <QStandardItemModel>

class EstatsTableModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit EstatsTableModel(QObject *parent=0, estats_agent *agent=NULL);

protected:
    estats_agent *agent;

private:

};

#endif // ESTATSTABLEMODEL_HPP
