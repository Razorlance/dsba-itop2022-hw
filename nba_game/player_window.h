#ifndef PLAYER_WINDOW_H
#define PLAYER_WINDOW_H

#include <QWidget>

namespace Ui
{
class player_window;
}

class player_window : public QWidget
{
    Q_OBJECT

   public:
    explicit player_window(QWidget *parent = nullptr);
    ~player_window();

   private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

   private:
    Ui::player_window *ui;
};

#endif  // PLAYER_WINDOW_H
