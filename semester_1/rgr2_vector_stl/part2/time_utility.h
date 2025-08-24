#pragma once

#include <ctime>
#include <random>

namespace time_utility {


const size_t MAX_HOUR_NUMBER_PER_DAY = 23;
const size_t MAX_MINUTE_NUMBER_PER_HOUR = 59;


/**
 * Set specific values for HH and MM of the current day.
 *
 * @param hours: amount of hours
 * @param minutes: amount of  minutes
 * @return time representation as 'std::time_t'.
 * 
 * @throws std::out_of_range thrown if 'hours' > 23 or 'minutes' > 59
 */
std::time_t SetTime(size_t hours, size_t minutes);


/**
 * Set random generated values for an hour and a minute of the current day.
 *
 * @param generator: generator which used to create random hours and minutes.
 * @return random generatred time as 'std::time_t'.
 */
std::time_t GenerateRandomTime(std::mt19937& generator);


/**
 * Compare two times according to the following rules:
 * 
 * HH1:MM1 < HH2:MM2 if (HH1 < HH2) or ((HH1 == HH2) && (MM1 < MM2)).
 * 
 * @param first_time The first time to compare (HH1, MM1).
 * @param second_time The second time to compare (HH2, MM2).
 * @return true if 'first_time' < 'second_time', otherwise \a false.
 */
bool CompareTimes(const std::time_t& first_time, const std::time_t& second_time);


/**
 * Print time in format "HH:MM".
 *
 * @param time_to_print: time which has to be printed.
 */
void PrintTime(const std::time_t& time_to_print);


}  // namespace time_utility
