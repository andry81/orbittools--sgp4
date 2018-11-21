
#ifndef SGP4_DEFINES_H_
#define SGP4_DEFINES_H_

// disabled by default

#ifndef ENABLE_QD_INTEGRATION
#define ENABLE_QD_INTEGRATION 0
#endif

#ifndef ENABLE_QD_DD_INTEGRATION
#define ENABLE_QD_DD_INTEGRATION 0
#endif

#ifndef ENABLE_QD_QD_INTEGRATION
#define ENABLE_QD_QD_INTEGRATION 0
#endif

#if ENABLE_QD_INTEGRATION
#include <qd/globals.h>
#endif

#include <cstdint>


#undef double
typedef double double_type;

#ifndef TO_DOUBLE_DEFINED
#define TO_DOUBLE_DEFINED

inline int to_double(int i) { return i; }
inline long to_double(long i) { return i; }
inline int64_t to_double(int64_t i) { return i; }
inline double to_double(double d) { return d; }

#endif

#ifndef SGP4_NAMESPACE_BEGIN
#define SGP4_NAMESPACE_BEGIN namespace sgp4 {
#endif

#ifndef SGP4_NAMESPACE_END
#define SGP4_NAMESPACE_END }
#endif

#include "SysDefine.h"

#endif
