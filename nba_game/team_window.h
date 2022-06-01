#ifndef TEAM_WINDOW_H
#define TEAM_WINDOW_H

#include <QDialog>

namespace Ui {
class team_window;
}

class team_window : public QDialog
{
    Q_OBJECT

public:
    explicit team_window(QWidget *parent = nullptr);
    ~team_window();

private:
    Ui::team_window *ui;
};

#endif // TEAM_WINDOW_H
