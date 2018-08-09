
#ifndef SGP4_DEFINES_H_
#define SGP4_DEFINES_H_

#include <qd/globals.h>
#include <cstdint>


#undef double
typedef double double_type;

#ifndef QD_INTEGRATION_ENABLED
#ifdef SGP4_ENABLE_QD_QD_INTEGRATION
namespace qd
{
    static inline qd_real to_real(int i) { return i; }
    static inline qd_real to_real(long i) { return int64_t(i); }
    static inline qd_real to_real(int64_t i) { return i; }
    static inline qd_real to_real(double d) { return d; }
}

#define QD_INTEGRATION_ENABLED 1

#elif defined(SGP4_ENABLE_QD_DD_INTEGRATION)
namespace qd
{
    static inline dd_real to_real(int i) { return i; }
    static inline dd_real to_real(long i) { return int64_t(i); }
    static inline dd_real to_real(int64_t i) { return i; }
    static inline dd_real to_real(double d) { return d; }
}

#define QD_INTEGRATION_ENABLED 1

#else

static inline int to_double(int i) { return i; }
static inline long to_double(long i) { return i; }
static inline int64_t to_double(int64_t i) { return i; }
static inline double to_double(double d) { return d; }

namespace qd
{
    static inline double to_real(int i) { return double(i); }
    static inline double to_real(long i) { return double(i); }
    static inline double to_real(int64_t i) { return double(i); }
    static inline double to_real(double d) { return d; }
}

#define QD_INTEGRATION_ENABLED 0

#endif

template <typename T>
static inline double_type as_double(T d) { return double_type(d); }

#endif

#ifndef SGP4_NAMESPACE_BEGIN
#define SGP4_NAMESPACE_BEGIN namespace sgp4 {
#endif

#ifndef SGP4_NAMESPACE_END
#define SGP4_NAMESPACE_END }
#endif

#include "SysDefine.h"

#endif
