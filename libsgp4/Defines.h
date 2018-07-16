
#ifndef SGP4_DEFINES_H_
#define SGP4_DEFINES_H_

#ifndef QD_INTEGRATION_ENABLED
#ifdef SGP4_ENABLE_QD_QD_INTEGRATION
#include <qd/qd_real.h>

static inline qd_real from_double(double d) { return d; }

#define QD_INTEGRATION_ENABLED 1

#elif defined(SGP4_ENABLE_QD_DD_INTEGRATION)
#include <qd/dd_real.h>

static inline dd_real from_double(double d) { return d; }

#define QD_INTEGRATION_ENABLED 1

#else
static inline double to_double(double d) { return d; }
static inline double from_double(double d) { return 0; }

#define QD_INTEGRATION_ENABLED 0

#endif
#endif

#ifndef SGP4_NAMESPACE_BEGIN
#define SGP4_NAMESPACE_BEGIN namespace sgp4 {
#endif

#ifndef SGP4_NAMESPACE_END
#define SGP4_NAMESPACE_END }
#endif

#include "SysDefine.h"

#endif
