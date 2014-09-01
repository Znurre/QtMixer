#include <QtCore/QtGlobal>

#if defined QTMIXER_LIBRARY
#define QTMIXER_EXPORT Q_DECL_EXPORT
#else
#define QTMIXER_EXPORT Q_DECL_IMPORT
#endif
