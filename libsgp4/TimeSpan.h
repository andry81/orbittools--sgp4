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


#ifndef TIMESPAN_H_
#define TIMESPAN_H_

#include "Defines.h"

#include "SysUndefine.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdint.h>

#include "SysDefine.h"


SGP4_NAMESPACE_BEGIN

const int64_t TicksPerDay =  86400000000LL;
const int64_t TicksPerHour =  3600000000LL;
const int64_t TicksPerMinute =  60000000LL;
const int64_t TicksPerSecond =   1000000LL;
const int64_t TicksPerMillisecond = 1000LL;
const int64_t TicksPerMicrosecond =    1LL;

const int64_t UnixEpoch = 62135596800000000LL;

const int64_t MaxValueTicks = 315537897599999999LL;

// 1582-Oct-15
const int64_t GregorianStart = 49916304000000000LL;

/**
 * @brief Represents a time interval.
 *
 * Represents a time interval (duration/elapsed) that is measured as a positive
 * or negative number of days, hours, minutes, seconds, and fractions
 * of a second.
 */
class TimeSpan
{
public:
#if QD_INTEGRATION_ENABLED
    TimeSpan(double ticks)
        : m_ticks(ticks)
    {
    }
#else
    TimeSpan(int64_t ticks)
        : m_ticks(ticks)
    {
    }
#endif

    TimeSpan(int hours, int minutes, int seconds)
    {
        CalculateTicks(0, hours, minutes, seconds, 0);
    }

    TimeSpan(int days, int hours, int minutes, int seconds)
    {
        CalculateTicks(days, hours, minutes, seconds, 0);
    }

    TimeSpan(int days, int hours, int minutes, int seconds, int microseconds)
    {
        CalculateTicks(days, hours, minutes, seconds, microseconds);
    }

    TimeSpan Add(const TimeSpan& ts) const
    {
        return TimeSpan(m_ticks + ts.m_ticks);
    }
    
    TimeSpan Subtract(const TimeSpan& ts) const
    {
        return TimeSpan(m_ticks - ts.m_ticks);
    }

    int Compare(const TimeSpan& ts) const
    {
        int ret = 0;

        if (m_ticks < ts.m_ticks)
        {
            ret = -1;
        }
        if (m_ticks > ts.m_ticks)
        {
            ret = 1;
        }
        return ret;
    }

    bool Equals(const TimeSpan& ts) const
    {
        return m_ticks == ts.m_ticks;
    }

    int Days() const
    {
#if QD_INTEGRATION_ENABLED
        return static_cast<int>(to_double(m_ticks / TicksPerDay));
#else
        return static_cast<int>(m_ticks / TicksPerDay);
#endif
    }

    int Hours() const
    {
#if QD_INTEGRATION_ENABLED
        return static_cast<int>(to_double(std::fmod(m_ticks, TicksPerDay) / TicksPerHour));
#else
        return static_cast<int>((m_ticks % TicksPerDay) / TicksPerHour);
#endif
    }

    int Minutes() const
    {
#if QD_INTEGRATION_ENABLED
        return static_cast<int>(to_double(std::fmod(m_ticks, TicksPerHour) / TicksPerMinute));
#else
        return static_cast<int>((m_ticks % TicksPerHour) / TicksPerMinute);
#endif
    }

    int Seconds() const
    {
#if QD_INTEGRATION_ENABLED
        return static_cast<int>(to_double(std::fmod(m_ticks, TicksPerMinute) / TicksPerSecond));
#else
        return static_cast<int>((m_ticks % TicksPerMinute) / TicksPerSecond);
#endif
    }

    int Milliseconds() const
    {
#if QD_INTEGRATION_ENABLED
        return static_cast<int>(to_double(std::fmod(m_ticks, TicksPerSecond) / TicksPerMillisecond));
#else
        return static_cast<int>((m_ticks % TicksPerSecond) / TicksPerMillisecond);
#endif
    }
    
    int Microseconds() const
    {
#if QD_INTEGRATION_ENABLED
        return static_cast<int>(to_double(std::fmod(m_ticks, TicksPerSecond) / TicksPerMicrosecond));
#else
        return static_cast<int>((m_ticks % TicksPerSecond) / TicksPerMicrosecond);
#endif
    }

#if QD_INTEGRATION_ENABLED
    double Ticks() const
    {
        return m_ticks;
    }
#else
    int64_t Ticks() const
    {
        return m_ticks;
    }
#endif

    double TotalDays() const
    {
        return static_cast<double>(m_ticks) / TicksPerDay;
    }

    double TotalHours() const
    {
        return static_cast<double>(m_ticks) / TicksPerHour;
    }

    double TotalMinutes() const
    {
        return static_cast<double>(m_ticks) / TicksPerMinute;
    }

    double TotalSeconds() const
    {
        return static_cast<double>(m_ticks) / TicksPerSecond;
    }
    
    double TotalMilliseconds() const
    {
        return static_cast<double>(m_ticks) / TicksPerMillisecond;
    }
    
    double TotalMicroseconds() const
    {
        return static_cast<double>(m_ticks) / TicksPerMicrosecond;
    }

    std::string ToString() const
    {
        std::stringstream ss;

        ss << std::right << std::setfill('0');
        
        if (m_ticks < 0)
        {
            ss << '-';
        }

        if (Days() != 0)
        {
            ss << std::setw(2) << std::abs(Days()) << '.';
        }

        ss << std::setw(2) << std::abs(Hours()) << ':';
        ss << std::setw(2) << std::abs(Minutes()) << ':';
        ss << std::setw(2) << std::abs(Seconds());

        if (Microseconds() != 0)
        {
            ss << '.' << std::setw(6) << std::abs(Microseconds());
        }

        return ss.str();
    }

private:
#if QD_INTEGRATION_ENABLED
    typedef double ticks_type;
#else
    typedef int64_t ticks_type;
#endif

    ticks_type m_ticks;

    void CalculateTicks(int days,
            int hours,
            int minutes,
            int seconds,
            int microseconds)
    {
        m_ticks = days * TicksPerDay +
            (hours * 3600LL + minutes * 60LL + seconds) * TicksPerSecond + 
            microseconds * TicksPerMicrosecond;
    }
};

inline std::ostream& operator<<(std::ostream& strm, const TimeSpan& t)
{
    return strm << t.ToString();
}

inline TimeSpan operator+(const TimeSpan& ts1, const TimeSpan& ts2)
{
    return ts1.Add(ts2);
}

inline TimeSpan operator-(const TimeSpan& ts1, const TimeSpan& ts2)
{
    return ts1.Subtract(ts2);
}

inline bool operator==(const TimeSpan& ts1, TimeSpan& ts2)
{
    return ts1.Equals(ts2);
}

inline bool operator>(const TimeSpan& ts1, const TimeSpan& ts2)
{
    return (ts1.Compare(ts2) > 0);
}

inline bool operator>=(const TimeSpan& ts1, const TimeSpan& ts2)
{
    return (ts1.Compare(ts2) >= 0);
}

inline bool operator!=(const TimeSpan& ts1, const TimeSpan& ts2)
{
    return !ts1.Equals(ts2);
}

inline bool operator<(const TimeSpan& ts1, const TimeSpan& ts2)
{
    return (ts1.Compare(ts2) < 0);
}

inline bool operator<=(const TimeSpan& ts1, const TimeSpan& ts2)
{
    return (ts1.Compare(ts2) <= 0);
}

SGP4_NAMESPACE_END

#include "SysUndefine.h"

#endif
