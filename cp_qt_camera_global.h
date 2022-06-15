#ifndef CP_QT_CAMERA_GLOBAL_H
#define CP_QT_CAMERA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CP_QT_CAMERA_LIBRARY)
#  define CP_QT_CAMERA_EXPORT Q_DECL_EXPORT
#else
#  define CP_QT_CAMERA_EXPORT Q_DECL_IMPORT
#endif

#endif // CP_QT_CAMERA_GLOBAL_H
