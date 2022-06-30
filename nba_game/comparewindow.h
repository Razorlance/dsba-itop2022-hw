#ifndef COMPAREWINDOW_H
#define COMPAREWINDOW_H

#include <playerslist.h>

#include <QDialog>
namespace Ui
{
class CompareWindow;
}

class CompareWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit CompareWindow(PlayersList *players, size_t id1, size_t id2,
                           QWidget *parent = nullptr);
    ~CompareWindow();

   private slots:
    void on_close_button_clicked();
    void compareFields();

   private:
    Ui::CompareWindow *ui;
};

#endif  // COMPAREWINDOW_H
