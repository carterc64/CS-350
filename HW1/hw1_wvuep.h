/**
 * @file hw1_wvuep.h
 * @brief Header file for CS 350 Homework #1: WVU Enrollment Problem
 * @author Brian Powell
 */

 // Place this file in the same directory as your own source code and add it to your project.
 // DO NOT MODIFY THE CONTENTS OF THIS FILE.

#pragma once

/**
 * @brief Prompts the user to enter their enrollment target for the specified year
 * @param target_year Year to prompt for target enrollment
 * @return User-specified value
 */
int prompt_target_enrollment(int target_year);

/**
 * @brief Calculate annual growth rate using the formula ((target_enrollment/initial_enrollment)^(1/years) - 1)
 * @param initial_enrollment Enrollment in initial_year
 * @param target_enrollment Target enrollment for end_year
 * @param initial_year Year for initial enrollment
 * @param target_year Year for target enrollment
 * @return Growth rate
 */
double calculate_growth_rate(int initial_enrollment, int target_enrollment, int initial_year, int target_year);

/**
 * @brief Get description of growth rate likelihood of occurring.
 * @param growth_rate Required annual growth rate
 * @return String describing the growth rate
*/
const char* get_growth_rate_description(double growth_rate);

/**
 * @brief Print growth rate and a description of the rate
 * @param growth_rate Required growth rate
 */
void print_growth_rate(double growth_rate);

/**
 * @brief Calculate the estimated enrollment in estimate_year
 * @param initial_enrollment Enrollment in initial_year
 * @param growth_rate Required annual growth rate
 * @param initial_year Year for initial enrollment
 * @param estimate_year Year for which to calculate enrollment estimate
 */
int calculate_enrollment_estimate(int initial_enrollment, double growth_rate, int initial_year, int estimate_year);

/**
 * @brief Print the estimated enrollment for each year between initial_year and end_year
 * @param initial_enrollment Enrollment in initial_year
 * @param growth_rate Required annual growth rate
 * @param initial_year Year for initial enrollment
 * @param end_year Last year for printing enrollment
 */
void print_enrollment_estimates(int initial_enrollment, double growth_rate, int initial_year, int end_year);

/**
 * @brief Function to get the name of the programmer
 * @return String with the name of the programmer
 */
const char* get_programmer_name(void);
