/*
 * Copyright 2013 Daniel Warner <contact@danrw.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "Defines.h"

#include "SysUndefine.h"

#include <cmath>
#include <cfloat>
#include <limits> // can't use DBL_MAX in gcc, won't compile because of an error: `error: call of overloaded 'dd_real(long double)' is ambiguous`

#include "SysDefine.h"


SGP4_NAMESPACE_BEGIN

const double kAE = 1.0;
const double kQ0 = 120.0;
const double kS0 = 78.0;
const double kMU = double(398600'8) / 1e1;
const double kXKMPER = double(6378'1370) / 1e4; //6378.135;
const double kXJ2 = double(1'0826158) / 1e10; //1.082616e-3;
const double kXJ3 = double(-2'53881) / 1e11;
const double kXJ4 = double(-1'65597) / 1e11;

/*
 * alternative XKE
 * affects final results
 * aiaa-2006-6573
 * const double kXKE = 60.0 / sqrt(kXKMPER * kXKMPER * kXKMPER / kMU);
 * dundee
 * const double kXKE = 7.43669161331734132e-2;
 */
const double kXKE = 60.0 / std::sqrt(kXKMPER * kXKMPER * kXKMPER / kMU);
const double kCK2 = 0.5 * kXJ2 * kAE * kAE;
const double kCK4 = double(-375) * kXJ4 * kAE * kAE * kAE * kAE / 1000;

/*
 * alternative QOMS2T
 * affects final results
 * aiaa-2006-6573
 * #define QOMS2T   (std::pow(((Q0 - S0) / XKMPER), 4.0))
 * dundee
 * #define QOMS2T   (1.880279159015270643865e-9)
 */
const double kQOMS2T = std::pow(((kQ0 - kS0) / kXKMPER), 4.0);

const double kS = kAE * (1.0 + kS0 / kXKMPER);
#if ENABLE_QD_INTEGRATION
const double kPI = double::_pi();
const double kTWOPI = double::_2pi();
#else
const double kPI = 3.14159265358979323846264338327950288419716939937510582;
const double kTWOPI = 2.0 * kPI;
#endif
const double kTWOTHIRD = double(2.0) / 3.0;
const double kTHDT = double(4'37526908801129966) / 1e10 / 1e10;
/*
 * earth flattening
 */
const double kF = (double(6378'1370) - 6356'7523) / 6378'1370; //1.0 / 298.26;
/*
 * earth rotation per sideral day
 */
const double kOMEGA_E = double(1'00273790934) / 1e11;
const double kAU = double(149597870'691) / 1e3;

const double kSECONDS_PER_DAY = 86400.0;
const double kMINUTES_PER_DAY = 1440.0;
const double kHOURS_PER_DAY = 24.0;

const double kA3OVK2 = -kXJ3 / kCK2 * kAE * kAE * kAE;

// `double_type` instead `double` to bypass definition substitution
const double_type double_max = (std::numeric_limits<double_type>::max)();

// TO FIX triginometric range in acos/asin functions !!!

extern inline double truncate_float_to_minmax(double value, double min_value, double max_value)
{
    if (max_value < value) {
        return max_value;
    }

    if (value < min_value) {
        return min_value;
    }

    return value;
}

extern inline double fix_float_trigonometric_range_factor(double value)
{
    // avoid fix in special case
    if (std::isnormal(value) && value != double_max && value != -double_max) {
        return truncate_float_to_minmax(value, -1.0, +1.0);
    }

    return value;
}

SGP4_NAMESPACE_END

#include "SysUndefine.h"

#endif

