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


#include "SolarPosition.h"

#include "Globals.h"
#include "Util.h"

#include "SysUndefine.h"

#include <cmath>

#include "SysDefine.h"


SGP4_NAMESPACE_BEGIN

Eci SolarPosition::FindPosition(const DateTime& dt)
{
    const double mjd = dt.ToJ2000();
    const double year = 1900 + mjd / double(365'25) * 1e2;
    const double T = (mjd + Delta_ET(year) / kSECONDS_PER_DAY) / 36525.0;
    const double M = Util::DegreesToRadians(Util::Wrap360(double(358'47583) / 1e5
                + Util::Wrap360(double(int64_t(35999'04975)) * T / 1e5)
                - (double(150) / 1e6 + double(33) * T / 1e7) * T * T));
    const double L = Util::DegreesToRadians(Util::Wrap360(double(279'69668) / 1e5
                + Util::Wrap360(double(int64_t(36000'76892)) * T / 1e5)
                + double(3025) * T * T / 1e7));
    const double e = double(1675104) / 1e8 - (double(418) / 1e7 + double(126) * T / 1e9) * T;
    const double C = Util::DegreesToRadians((double(1'919460) / 1e6
                - (double(4789) / 1e6 + double(14) * T / 1e6) * T) * std::sin(M)
                + (double(20094) / 1e6 - double(100) * T / 1e6) * std::sin(2 * M)
                + double(293) * std::sin(3 * M) / 1e6);
    const double O = Util::DegreesToRadians(
            Util::Wrap360(double(259'18) / 1e2 - double(1934'142) * T / 1e3));
    const double Lsa = Util::WrapTwoPI(L + C
            - Util::DegreesToRadians(double(569) / 1e5 - double(479) * std::sin(O) / 1e5));
    const double nu = Util::WrapTwoPI(M + C);
    double R = double(1'0000002) * (1 - e * e) / (1 + e * std::cos(nu)) / 1e7;
    const double eps = Util::DegreesToRadians(double(23'452294) / 1e6 - (double(130125) / 1e7
                + (double(164) / 1e8 - double(503) * T / 1e9) * T) * T + double(256) * std::cos(O) / 1e5);
    R = R * kAU;

    Vector solar_position(R * std::cos(Lsa),
            R * std::sin(Lsa) * std::cos(eps),
            R * std::sin(Lsa) * std::sin(eps),
            R);

    return Eci(dt, solar_position);
}

double SolarPosition::Delta_ET(double year) const
{
    return double(26'465) / 1e3 + double(747622) * (year - 1950) / 1e6 + double(1'886913)
        * std::sin(kTWOPI * (year - 1975) / 33) / 1e6;
}

SGP4_NAMESPACE_END
