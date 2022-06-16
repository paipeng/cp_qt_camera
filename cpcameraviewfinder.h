#ifndef CPCAMERAVIEWFINDER_H
#define CPCAMERAVIEWFINDER_H

#include <QCameraViewfinder>
#include <QPainter>
#include "cp_qt_camera_global.h"

class CP_QT_CAMERA_EXPORT CPCameraViewfinder : public QCameraViewfinder {
    Q_OBJECT
public:
    CPCameraViewfinder(QWidget *parent = nullptr);
    void setText(const QString& text);
    void setRect(const QRect& rect);
    void setPoints(const QVector<QPoint>& points);
    const QSize getSize();
protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPainter painter;
    QRect rect;
    QString text;
    QPen pen;
    QBrush brush;
    QVector<QPoint> points;
};

#endif // CPCAMERAVIEWFINDER_H
