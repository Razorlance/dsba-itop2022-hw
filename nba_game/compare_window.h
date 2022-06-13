#ifndef COMPARE_WINDOW_H
#define COMPARE_WINDOW_H

#include <players_list.h>

#include <QDialog>
namespace Ui
{
class compare_window;
}

class compare_window : public QDialog
{
    Q_OBJECT

   public:
    explicit compare_window(players_list *players, size_t id1, size_t id2,
                            QWidget *parent = nullptr);
    ~compare_window();

   private slots:
    void on_close_button_clicked();

   private:
    Ui::compare_window *ui;
};

#endif  // COMPARE_WINDOW_H
