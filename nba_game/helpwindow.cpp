#include "helpwindow.h"

#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::helpWindow)
{
    ui->setupUi(this);
}

HelpWindow::~HelpWindow() { delete ui; }

void HelpWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::white, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QRadialGradient radialGrad(QPointF(240, 320), 200);
    QBrush backBrush(radialGrad);
    QFont font = painter.font();

    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing,
                           true);

    radialGrad.setColorAt(0.2, QColor(53, 21, 176));
    radialGrad.setColorAt(0.4, Qt::GlobalColor::white);
    radialGrad.setColorAt(0.8, QColor(255, 0, 0));

    painter.setBrush(backBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

    painter.setPen(pen);
    painter.drawEllipse(QPointF(240, 320), 190, 190);
    painter.drawEllipse(QPointF(240, 320), 120, 120);

    font.setPixelSize(40);
    painter.setFont(font);
    painter.drawText(QPointF(180, 335), "SPORT");
}
