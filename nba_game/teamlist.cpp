#include "teamlist.h"

#include <QDebug>

#include "ui_teamlist.h"

TeamList::TeamList(PlayersList* players, TeamsTable* teamsTableModel,
                   QMenu* menu, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::TeamList),
      _players(players),
      _menu(menu),
      _teamsTableModel(teamsTableModel),
      _teamsListModel(new QStringListModel()),
      _teamsMenu(new QMenu)

{
    ui->setupUi(this);
    ui->teamlist->setModel(_teamsListModel);
    ui->playersTable->setModel(_teamsTableModel);
    _teamsListModel->setStringList(players->getTeamList());
    QAction* addTeam = new QAction("Create new team", this);
    connect(addTeam, SIGNAL(triggered()), this, SLOT(newTeam()));
    _teamsMenu->addAction(addTeam);
    connect(ui->teamlist, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(on_teamlist_customContextMenuRequested(QPoint)));
}

TeamList::~TeamList() { delete ui; }

void TeamList::newTeam()
{
    bool ok;
    QString text =
        QInputDialog::getText(this, tr("Add new team"), tr("Team name:"),
                              QLineEdit::Normal, "New team", &ok);
    if (ok && !text.isEmpty())
    {
        _teamsListModel->layoutAboutToBeChanged();
        _players->appendTeam(text);
        _teamsListModel->setStringList(_players->getTeamList());
        _teamsListModel->layoutChanged();
        //        QAction* teamAction = new QAction("Add to " + text, this);
        //        _menu->addAction(teamAction);
        //        connect(teamAction, SIGNAL(triggered()), parent(),
        //        SLOT(AddToTeam()));
    }
}

void TeamList::on_okButton_clicked() { this->close(); }

void TeamList::on_teamlist_customContextMenuRequested(const QPoint& pos)
{
    _teamsMenu->popup(ui->teamlist->viewport()->mapToGlobal(pos));
}

void TeamList::on_teamlist_clicked(const QModelIndex& index)
{
    //    size_t index =
    //    ui->teamlist->selectionModel()->selectedRows().at(0).row(); size_t
    //    index =
    //        ui->_teamsListModel->selectionModel()->selectedRows().at(0).row();

    QString teamName = ui->teamlist->model()->data(index).toString();
    //               ui->table->model()->data(ui->table->model()->index(index,
    //        0)).toInt();
    _teamsTableModel->layoutAboutToBeChanged();
    _teamsTableModel->setSelectedTeam(teamName);
    _players->setTeamName(teamName);
    _teamsTableModel->layoutChanged();
}

void TeamList::on_saveButton_clicked()
{
    QFileDialog objFlDlg(this);
    objFlDlg.setOption(QFileDialog::ShowDirsOnly, true);
    objFlDlg.setAcceptMode(QFileDialog::AcceptSave);
    objFlDlg.selectFile("Team");
    QList<QLineEdit*> lst = objFlDlg.findChildren<QLineEdit*>();
    qDebug() << lst.count();
    if (lst.count() == 1)
    {
        lst.at(0)->setReadOnly(true);
    }
    if (objFlDlg.exec())
    {
        QFile file(objFlDlg.selectedFiles().at(0) + ".csv");
        if (file.open(QIODevice::Append))
        {
            QTextStream stream(&file);
            for (QString& k : _players->getTeamList())
            {
                stream << k << ";";
                for (const Player& p : _players->getSelectedTeam(k))
                {
                    stream << p.id << " " << p.name << ",";
                }
                stream << "\n";
            }
        }
        file.close();
    }
}

void TeamList::on_tournamentButton_clicked() {}
