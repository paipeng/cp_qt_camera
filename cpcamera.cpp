#include "cpcamera.h"


CPCamera::CPCamera(int cameraId, CPCameraInterface* cameraInterface): cameraId(cameraId) {
    this->cameraInterface = cameraInterface;
}

CPCamera::~CPCamera() {

}

void CPCamera::setCamera(const QCameraInfo &cameraInfo, QCameraViewfinder *surface) {
    qDebug() << "setCamera: " << cameraInfo.description();
    m_camera.reset(new QCamera(cameraInfo));

    connect(m_camera.data(), &QCamera::stateChanged, this, &CPCamera::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &CPCamera::displayCameraError);

    qDebug() << "1";
    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &CPCamera::updateRecorderState);

    qDebug() << "2";
    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &CPCamera::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &CPCamera::displayRecorderError);

    qDebug() << "3";
    m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

    qDebug() << "4";
    m_camera->setViewfinder(surface);

    qDebug() << "5";
    updateCameraState(m_camera->state());
    updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
    updateRecorderState(m_mediaRecorder->state());

    qDebug() << "6";
    connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &CPCamera::readyForCapture);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &CPCamera::processCapturedImage);
    //connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &CPCamera::imageSaved);
    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
            this, &CPCamera::displayCaptureError);

    connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
            this, &CPCamera::updateLockStatus);

    //ui->captureWidget->setTabEnabled(0, true);
    //ui->captureWidget->setTabEnabled(1, true);

    qDebug() << "7";
    updateCaptureMode();
}

const QList<QCameraInfo> CPCamera::getAvailableCamersInfos() {
    return QCameraInfo::availableCameras();
}



void CPCamera::takeImage() {
    m_imageCapture->capture();

}

void CPCamera::startCamera() {
    qDebug("startCamera: %d", m_isCameraStart);
    if (m_isCameraStart) {
        qDebug() << "stop";
        m_camera->stop();

        displayCapturedImage();
    } else {
        qDebug() << "start";
        m_camera->start();

        displayViewfinder();
    }
    m_isCameraStart = !m_isCameraStart;
    qDebug("startCamera end: %d", m_isCameraStart);
}

void CPCamera::stopCamera() {
    qDebug() << "stopCamera camera state: " << m_camera->status();
    m_camera->stop();
}

void CPCamera::updateCaptureMode() {
    //int tabIndex = ui->captureWidget->currentIndex();
    //QCamera::CaptureModes captureMode = tabIndex == 0 ? QCamera::CaptureStillImage : QCamera::CaptureVideo;

    if (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage))
        m_camera->setCaptureMode(QCamera::CaptureStillImage);
}

void CPCamera::updateCameraState(QCamera::State state) {

    qDebug() << "updateCameraState: " << state;
    switch (state) {
    case QCamera::ActiveState:

        break;
    case QCamera::UnloadedState:
    case QCamera::LoadedState:
        break;
    }
    cameraInterface->cameraState(cameraId, state);
}

void CPCamera::updateRecorderState(QMediaRecorder::State state) {

}

void CPCamera::setExposureCompensation(int index) {
    m_camera->exposure()->setExposureCompensation(index*0.5);
}

void CPCamera::displayRecorderError() {
    //QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void CPCamera::displayCameraError() {
    //QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void CPCamera::updateCameraDevice(QAction *action) {
    //setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void CPCamera::displayViewfinder() {
}

void CPCamera::displayCapturedImage() {
}

void CPCamera::readyForCapture(bool ready) {
    //qDebug("readyForCapture: %d", ready);
    if (ready) {
        m_isCapturingImage = true;
        //m_imageCapture->capture();
    } else {
        m_isCapturingImage = false;
    }
    this->cameraInterface->cameraReadyForCapture(this->cameraId, ready);
}

void CPCamera::imageSaved(int id, const QString &fileName) {
    Q_UNUSED(id);
    qDebug("imageSaved: %s", (const char*)(fileName.data()));
    m_isCapturingImage = false;
}


void CPCamera::processCapturedImage(int requestId, const QImage& img) {
    Q_UNUSED(requestId);
    //qDebug("processCapturedImage imageFormat: %d", img.format());
    this->cameraInterface->processCapturedImage(this->cameraId, img);
}


void CPCamera::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason) {
    QColor indicationColor = Qt::black;

    switch (status) {
    case QCamera::Searching:
        indicationColor = Qt::yellow;
        //ui->statusbar->showMessage(tr("Focusing..."));
        break;
    case QCamera::Locked:
        indicationColor = Qt::darkGreen;
        //ui->statusbar->showMessage(tr("Focused"), 2000);
        break;
    case QCamera::Unlocked:
        indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
        //if (reason == QCamera::LockFailed)
        //    ui->statusbar->showMessage(tr("Focus Failed"), 2000);
        break;
    }
}


void CPCamera::updateRecordTime() {
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
    //ui->statusbar->showMessage(str);
}


void CPCamera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString) {
    Q_UNUSED(id);
    Q_UNUSED(error);
    //QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    //m_isCapturingImage = false;
}

