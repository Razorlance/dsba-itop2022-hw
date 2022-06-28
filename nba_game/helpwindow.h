#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QPainter>

#include "qdialog.h"
namespace Ui
{
class HelpWindow;
}

class HelpWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit HelpWindow(QWidget *parent = nullptr);
    ~HelpWindow();

   protected:
    void paintEvent(QPaintEvent *event);

   private:
    Ui::HelpWindow *ui;
};

#endif  // HELPWINDOW_H
