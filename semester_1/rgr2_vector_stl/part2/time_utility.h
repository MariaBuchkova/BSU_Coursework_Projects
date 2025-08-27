#pragma once

#include <ctime>
#include <random>

namespace time_utility {


const size_t MAX_HOUR_NUMBER_PER_DAY = 23;
const size_t MAX_MINUTE_NUMBER_PER_HOUR = 59;


/**
 * Set specific values for an hour and a minute of the current day time.
 *
 * @param hours: amount of hours
 * @param minutes: amount of  minutes
 * @return time representation as `std::time_t`.
 * 
 * @throws std::out_of_range thrown if `hours` > 23 or `minutes` > 59
 */
std::time_t SetTime(size_t hours, size_t minutes);


/**
 * Set random generated values for an hour and a minute of the current day time.
 *
 * @param generator: generator which used to create random hours and minutes.
 * @return random generatred time as `std::time_t`.
 */
std::time_t GenerateRandomTime(std::mt19937& generator);


/**
 * Print time in format `Www Mmm dd hh:mm:ss yyyy\n`.
 * 
 * see `std::asctime` function:
 * 
 * https://en.cppreference.com/w/cpp/chrono/c/asctime
 * 
 * @param time_to_print: time which has to be printed.
 */
void PrintTime(const std::time_t& time_to_print);


}  // namespace time_utility
