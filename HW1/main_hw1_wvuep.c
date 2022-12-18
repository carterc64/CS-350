/**
 * @file main_hw1_wvuep.c
 * @brief File with main function for CS 350 Homework #1: WVU Enrollment Problem
 * @author Brian Powell
 */

 // CS 350 Homework #1: WVU Enrollment Problem
 // Place this file in the same directory as your own source code and add it to your project.
 // DO NOT MODIFY THE CONTENTS OF THIS FILE.

 // Include header files
#include "hw1_wvuep.h"
#include <stdio.h>

/**
 * @brief Program entry point
 * @return Status code
*/
int main(void)
{
	// Initial enrollment
	const int initial_enrollment = 29107;

	// Year of initial enrollment
	const int initial_year = 2020;

	// Year for target enrollment
	const int target_year = 2035;

	// Prompt user for target enrollment
	int target_enrollment = prompt_target_enrollment(target_year);

	// Calculate target growth rate
	double growth_rate = calculate_growth_rate(initial_enrollment, target_enrollment, initial_year, target_year);

	// Print growth rate and descrition;
	print_growth_rate(growth_rate);

	// Print enrollment estimates for years initial_year through initial_year + 50
	print_enrollment_estimates(initial_enrollment, growth_rate, initial_year, initial_year + 50);

	// Print name of programmer
	printf("Code written by %s\n", get_programmer_name());

	return 0;

}