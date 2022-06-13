#ifndef HELP_WINDOW_H
#define HELP_WINDOW_H

#include <QPainter>
#include <QTextDocument>
#include <QWidget>

#include "qdialog.h"
namespace Ui
{
class help_window;
}

class help_window : public QDialog
{
    Q_OBJECT

   public:
    explicit help_window(QWidget *parent = nullptr);
    ~help_window();

   protected:
    void paintEvent(QPaintEvent *event);

   private:
    Ui::help_window *ui;
};

#endif  // HELP_WINDOW_H