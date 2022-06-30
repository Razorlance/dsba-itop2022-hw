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
      _teamsMenu(new QMenu),
      _tableMenu(new QMenu),
      _tournamentWindow(new TournamentWindow(_players, "", "", this))

{
    ui->setupUi(this);
    ui->teamlist->setModel(_teamsListModel);
    ui->playersTable->setModel(_teamsTableModel);
    _teamsListModel->setStringList(players->getTeamList());
    QAction* addTeam = new QAction("Create new team", this);
    QAction* deleteTeam = new QAction("Delete team", this);
    connect(addTeam, SIGNAL(triggered()), this, SLOT(newTeam()));
    connect(deleteTeam, SIGNAL(triggered()), this, SLOT(deleteTeam()));
    QAction* deleteFromTeam = new QAction("Delete from team", this);
    _tableMenu->addAction(deleteFromTeam);
    _teamsMenu->addAction(addTeam);
    _teamsMenu->addAction(deleteTeam);
    connect(deleteFromTeam, SIGNAL(triggered()), this, SLOT(deleteFromTeam()));
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
        _players->appendTeam(text);
        _teamsListModel->layoutAboutToBeChanged();

        _teamsListModel->setStringList(_players->getTeamList());
        _teamsListModel->layoutChanged();
        //        QAction* teamAction = new QAction("Add to " + text, this);
        //        _menu->addAction(teamAction);
        //        connect(teamAction, SIGNAL(triggered()), parent(),
        //        SLOT(AddToTeam()));
    }
}

void TeamList::deleteTeam()
{
    size_t index = ui->teamlist->selectionModel()->selectedRows().at(0).row();
    QString teamName = ui->teamlist->model()
                           ->data(ui->teamlist->model()->index(index, 0))
                           .toString();

    if (_players->getTeamList().size() > 1 &&
        ui->teamlist->selectionModel()->selectedRows().size() > 0)
    {
        _players->deleteSelectedTeam(teamName);
        _teamsListModel->setStringList(_players->getTeamList());
    }
}

void TeamList::deleteFromTeam()
{
    size_t index = ui->teamlist->selectionModel()->selectedRows().at(0).row();
    QString teamName = ui->teamlist->model()
                           ->data(ui->teamlist->model()->index(index, 0))
                           .toString();
    size_t tableIndex =
        ui->playersTable->selectionModel()->selectedRows().at(0).row();
    size_t id = ui->playersTable->model()
                    ->data(ui->playersTable->model()->index(tableIndex, 0))
                    .toInt();
    _teamsTableModel->layoutAboutToBeChanged();
    _players->deleteFromSelectedTeam(teamName, id);
    _teamsTableModel->layoutChanged();
}

void TeamList::on_okButton_clicked() { this->close(); }

void TeamList::on_teamlist_customContextMenuRequested(const QPoint& pos)
{
    if (ui->teamlist->selectionModel()->selectedRows().size() > 0)
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

void TeamList::on_tournamentButton_clicked()
{
    if (ui->teamlist->selectionModel()->selectedRows().size() <= 1)
        return;
    size_t index1 = ui->teamlist->selectionModel()->selectedRows().at(0).row();
    QString teamName1 = ui->teamlist->model()
                            ->data(ui->teamlist->model()->index(index1, 0))
                            .toString();
    size_t index2 = ui->teamlist->selectionModel()->selectedRows().at(1).row();
    QString teamName2 = ui->teamlist->model()
                            ->data(ui->teamlist->model()->index(index2, 0))
                            .toString();
    _tournamentWindow->setTeam1(teamName1);
    _tournamentWindow->setTeam2(teamName2);
    _tournamentWindow->update();
    _tournamentWindow->show();
}

void TeamList::on_playersTable_customContextMenuRequested(const QPoint& pos)
{
    _tableMenu->popup(ui->playersTable->viewport()->mapToGlobal(pos));
}
