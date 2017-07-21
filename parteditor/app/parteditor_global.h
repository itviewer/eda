#ifndef PARTEDITOR_GLOBAL_H
#define PARTEDITOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PARTEDITOR_LIBRARY)
#  define PARTEDITORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PARTEDITORSHARED_EXPORT Q_DECL_IMPORT
#endif


#endif // PARTEDITOR_GLOBAL_H
