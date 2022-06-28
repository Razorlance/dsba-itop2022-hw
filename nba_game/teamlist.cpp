#include "teamlist.h"

#include <QDebug>

#include "ui_teamlist.h"

TeamList::TeamList(PlayersList* players, QMenu* menu, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::TeamList),
      _players(players),
      _menu(menu),
      teamsListModel(new QStringListModel()),
      _teamsMenu(new QMenu)

{
    ui->setupUi(this);
    ui->teamlist->setModel(teamsListModel);
    teamsListModel->setStringList(players->getTeamList());
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
        teamsListModel->layoutAboutToBeChanged();
        _players->appendTeam(text);
        teamsListModel->setStringList(_players->getTeamList());
        teamsListModel->layoutChanged();
        QAction* teamAction = new QAction("Add to " + text, this);
        _menu->addAction(teamAction);
        connect(teamAction, SIGNAL(triggered()), parent(), SLOT(AddToTeam()));
    }
}

void TeamList::on_okButton_clicked() { this->close(); }

void TeamList::on_teamlist_customContextMenuRequested(const QPoint& pos)
{
    _teamsMenu->popup(ui->teamlist->viewport()->mapToGlobal(pos));
}
