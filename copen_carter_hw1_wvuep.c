/**
* Carter Copen
* 9/28/22
* Computer Science 350 Section 001
* Homework #1: WVU Enrollment Problem
* Visual Studio 2022
* Linux-type project
*/

#include "hw1_wvuep.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

//Get user input for target inrollment
int prompt_target_enrollment(int target_year) {
	char enrollment_target[15];
	int numeric_check = 0;
	size_t length;

	//First user input
	printf("Enter enrollment target for %d: \n", target_year);
	scanf("%14s", &enrollment_target);

	//get length of input
	length = strlen(enrollment_target);

	//inital check to see if input is a number
	for (size_t i = 0; i < length; i++) {
		
		if (!isdigit(enrollment_target[i])) {
			numeric_check = 0;
			break;
		}
		numeric_check = 1;
	}

	//while its not a number, or if its a number below 0
	while (numeric_check == 0 || enrollment_target <= 0) {
		
		//says its wrong and prompt another input
		printf("\nInvalid target \n");
		printf("Enter enrollment target for %d: \n", target_year);
		scanf("%s", &enrollment_target);

		//numeric check input
		for (int i = 0; i < length; i++) {
			if (!isdigit(enrollment_target[i])) {
				numeric_check = 0;
				break;
			}
			numeric_check = 1;
		}
	}

	//input is now a number above 0 change to int and return 
	return atoi(enrollment_target);

}


//calculate the growth rate
double calculate_growth_rate(int initial_enrollment, int target_enrollment, int initial_year, int target_year) {

	//gets the first half of the equation
	double target_enroll_over_initial = (double)target_enrollment / (double)initial_enrollment;
	
	//gets the second hald or the part that will be the power
	double target_year_over_initial = (1/ ((double)target_year - (double)initial_year));

	//calculate the two halfs and subtract 1
	double growth_rate = pow(target_enroll_over_initial, target_year_over_initial)-1;

	//check to see if the rate is in range of -1 <= growth_rate <= 1
	if (growth_rate < -1 || growth_rate > 1) {
		puts("Growth Rate Out of Range Error");
		return -1;
	}
	
	//retrn the double
	return growth_rate;

}

//get the description of the growth rate
const char* get_growth_rate_description(double growth_rate) {

	//initilizer 
	const char* growth_rate_description;

	//checks to see which description matches the growth_rate then assigns the correct description
	if (growth_rate >= 0.04) {
		growth_rate_description = "unreasonable";

	}else if (growth_rate >= 0.02) {
		growth_rate_description = "high";

	}else if (growth_rate >= 0.01) {
		growth_rate_description = "ambitious";

	}else if (growth_rate >= 0) {
		growth_rate_description = "resonable";

	}else {
		growth_rate_description = "negative";
	}

	//returns the const char*
	return growth_rate_description;
}

//display the growth_rate and matching decription
void print_growth_rate(double growth_rate) {

	//gets the descritption 
	const char* growth_rate_description = get_growth_rate_description(growth_rate);

	//prints the growth_rate*100 with only 1 decimal to match % format, then the descritption
	printf("Required annual rate of growth, %.1f%, is %s\n", growth_rate*100, growth_rate_description);

}

//calculates the estimated enrollment based of the new year and growth_rate
int calculate_enrollment_estimate(int initial_enrollment, double growth_rate, int initial_year, int estimate_year) {
	
	//get the power part of the equation
	double power = (double)estimate_year - (double)initial_year;

	//completes the equation
	double enrollment_estimate_double = (double)initial_enrollment * (pow(1 + (double)growth_rate, power));

	//rounds the double to turn into an int 
	int enrollment_estimate = round(enrollment_estimate_double);
	
	//return the rounded int
	return enrollment_estimate;

}

//prints the calculate_enrollment_estimate for each year from the inital_year to the end_year
void print_enrollment_estimates(int initial_enrollment, double growth_rate, int initial_year, int end_year) {

	//loop for the initial_year to the end_year
	for (int i = 0; i <= end_year-initial_year; i++) {

		//prints the year along with that years enrollment estimate
		printf("%d enrollement estimate: %d\n", initial_year+i,
			calculate_enrollment_estimate(initial_enrollment, growth_rate, initial_year, initial_year+i));

	}

}

//displays my name
const char* get_programmer_name(void) {

	const char* name = "Carter Copen";
	return name;

}