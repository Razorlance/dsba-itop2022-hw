#include "help_window.h"

#include "ui_help_window.h"

help_window::help_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::help_window)
{
    ui->setupUi(this);
}

help_window::~help_window() { delete ui; }

void help_window::paintEvent(QPaintEvent *event)
{
    QPainter painter(
        this);  // this - QPaintDevice; inheritance hierarchy: RomaWidget ->
                // (QWidget -> (QObject, QPaintDevice))

    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QRadialGradient radialGrad(QPointF(370, 270), 300);
    radialGrad.setColorAt(0, Qt::GlobalColor::white);
    radialGrad.setColorAt(1, QColor(0, 172, 238));  // (255, 192, 203)
    radialGrad.setColorAt(0.5, QColor(192, 192, 192));
    radialGrad.centerRadius();

    QBrush backgroundBrush(radialGrad);
    painter.setBrush(backgroundBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

    QTextDocument doc;
    doc.setTextWidth(width());
    doc.setHtml(
        "<center><font size=10 color=\"#196F3D\">Kak tebe takoe, Elon "
        "Musk?!?</font></center>");
    doc.drawContents(&painter, QRectF(0, 0, width() - 1, height() - 1));
    // painter.drawText()
    // painter.drawText(QRectF(0, 0, width() - 1, height() - 1), Qt::AlignCenter
    // | Qt::AlignTop, doc);
}
