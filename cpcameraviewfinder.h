#ifndef CPCAMERAVIEWFINDER_H
#define CPCAMERAVIEWFINDER_H

#include <QCameraViewfinder>
#include <QPainter>
#include "cp_qt_camera_global.h"

class CP_QT_CAMERA_EXPORT CPCameraViewfinder : public QCameraViewfinder {
    Q_OBJECT
public:
    CPCameraViewfinder(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // CPCAMERAVIEWFINDER_H
