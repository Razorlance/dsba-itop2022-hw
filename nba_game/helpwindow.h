#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QPainter>

#include "qdialog.h"
namespace Ui
{
class helpWindow;
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
    Ui::helpWindow *ui;
};

#endif  // HELPWINDOW_H
