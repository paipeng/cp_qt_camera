#ifndef CPCAMERA_INTERFACE_H
#define CPCAMERA_INTERFACE_H


#include <QPixmap>

class CPCameraInterface {
public:
    virtual ~CPCameraInterface() {}
    virtual void cameraState(int cameraId, int state) = 0;
    virtual void processCapturedImage(int cameraId, const QImage& img) = 0;
    virtual void cameraReadyForCapture(int cameraId, bool ready) = 0;
};


#endif // CPCAMERA_INTERFACE_H
