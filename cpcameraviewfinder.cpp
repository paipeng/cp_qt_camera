#include "cpcameraviewfinder.h"

#include <QDebug>

CPCameraViewfinder::CPCameraViewfinder(QWidget *parent) :
    QCameraViewfinder(parent), painter(this), rect(0, 0, parent->size().width()-4, parent->size().height()-4), text("Overlay"), pen(Qt::green, 4), brush(Qt::green, Qt::SolidPattern)
{


}

void CPCameraViewfinder::paintEvent(QPaintEvent* event) {
    qDebug() << "paintEvent widget size: " << this->width() << "-" << this->height();
    // Default rendered -> call base class
    QCameraViewfinder::paintEvent(event);
    // draw some text
    QPainter painter(this);
    painter.setPen(pen);
    //QBrush brush(Qt::green, Qt::SolidPattern);
    //painter.setBrush(brush);
    painter.drawText(12, 12, this->text);
    //QRect rect( 10, 10, 200, 200);
    //painter.drawRect(rect);
    if (points.size() > 0) {
        painter.drawPoints(points);

        for (int i = 0; i < points.size()-1; i++) {
            painter.drawLine(points.at(i), points.at(i+1));
        }
        painter.drawLine(points.at(points.size()-1), points.at(0));
    }
}

void CPCameraViewfinder::setText(const QString& text) {
    this->text = text;
}
void CPCameraViewfinder::setRect(const QRect& rect) {
    this->rect = rect;
}


void CPCameraViewfinder::setPoints(const QVector<QPoint>& points) {
    this->points = points;
}

const QSize CPCameraViewfinder::getSize() {
    return this->size();
}
