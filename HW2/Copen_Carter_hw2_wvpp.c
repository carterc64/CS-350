/**
	Carter Copen
	Copen_Carter_hw2_wvpp.c
	This is the source code file for hw2
	Using Visual Studio 2022 and a Linux-type Project
	
*/

#include "hw2_wvpp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS

// Struct for node
typedef struct node{
	const char* countyName;
	const char* fipsCode;
	const char* seat;
	int population;
	int area;
	struct node* nextPtr;
};

//Creates listPtr
list* create_list() {
	struct list* listPtr = malloc(sizeof(struct list));
	if (listPtr == NULL) {
		puts("Could Not Allocate Memory");
		exit(1);
	}
	struct node* headPtr = NULL;
	listPtr->headPtr = headPtr;
	return listPtr;
}

//Returns current head node of a list pointer
struct node* get_head_node(list* listPtr) {
	struct node* headPtr = listPtr->headPtr;
	return headPtr;
}

//Adds the county into the sorted list in the right position
void add_sorted_county(list* listPtr, const char* county_name, const char* fips_code, const char* seat, int population, int area) {
	
	//creates node to be added
	struct node* nodePtr = malloc(sizeof(struct node));
	if (nodePtr == NULL) {
		puts("Could Not Allocate Memory");
		exit(1);
	}
	nodePtr->area = area;
	nodePtr->countyName = county_name;
	nodePtr->fipsCode = fips_code;
	nodePtr->population = population;
	nodePtr->seat = seat;
	nodePtr->nextPtr = NULL;
	
	//gets current head
	struct node* headPtr = get_head_node(listPtr);
	//checks if a head is present
	if (headPtr != NULL) {
		//calculate both densities
		struct node* curPtr = headPtr;
		int densityNew = get_population_density(nodePtr);
		int densityCurrent = get_population_density(curPtr);

		//if new node is more dense then current head make new node the new head
		if (densityNew > densityCurrent) {

			nodePtr->nextPtr = curPtr;
			listPtr->headPtr = nodePtr;
			return;
		}

		//if it is smaller than head find location it fits
		while (curPtr->nextPtr != NULL) {
			
			densityCurrent = get_population_density(curPtr->nextPtr);
			if (densityNew > densityCurrent) {
				nodePtr->nextPtr = curPtr->nextPtr;
				curPtr->nextPtr = nodePtr;
				return;
			}
			curPtr = get_next_node(curPtr);
		}

		//went threw all nodes and no suitable location so add it to the end
		curPtr->nextPtr = nodePtr;

	}
	else {
		//if head isnt present make the new node the new head
		listPtr->headPtr = nodePtr;
	}

}

//Finds the node with the specified countyName or returns 1
int delete_by_county_name(list* listPtr, const char* county_name) {
	//gets head node
	struct node* headPtr = get_head_node(listPtr);

	//checks if exsits
	if (headPtr != NULL) {

		//checks to see if the head node is the one with the ocunty name
		if (strcmp(get_county_name(headPtr), county_name) == 0) {
			//removes the matching headnode
			struct node* tempPtr = headPtr;
			listPtr->headPtr = tempPtr->nextPtr;
			free(tempPtr);
			return 0;
		
		}

		struct node* curPtr = headPtr;
		//head node wasnt a match now check other
		while (curPtr->nextPtr != NULL) {
			//compares to check for match of county name
			if (strcmp(get_county_name(curPtr->nextPtr), county_name) == 0) {
				//removes the matching node
				struct node* tempPtr = curPtr->nextPtr;
				curPtr->nextPtr = tempPtr->nextPtr;
				free(tempPtr);
				return 0;
			}
			//traverses list
			curPtr = get_next_node(curPtr);
		}
		
		//no matching node
		return 1;
	}
	else {
		//head node doesnt exist
		return 1;
	}
}

//Returns county name from specified node
const char* get_county_name(struct node* nodePtr) {
	return nodePtr->countyName;
}

//Returns fipsCode from specified node
const char* get_fips_code(struct node* nodePtr) {
	return nodePtr->fipsCode;
}

//Returns seat from specified node
const char* get_seat(struct node* nodePtr) {
	return nodePtr->seat;
}

//Returns population from specified node
int get_population(struct node* nodePtr){
	return nodePtr->population;
}

//Returns area from spceified node
int get_area(struct node* nodePtr) {
	return nodePtr->area;
}

//Calculates the population density of a specidied node
double get_population_density(struct node* nodePtr) {
	double result = get_population(nodePtr) / (double)get_area(nodePtr);
	return result;
}

//Looks for the next node of a specified node
struct node* get_next_node(struct node* nodePtr) {
	if (nodePtr->nextPtr == NULL) {
		return NULL;
	}
	else {
		return nodePtr->nextPtr;
	}
}

//Loads the counties from a file into the list
void load_counties(list* listPtr, const char* filename) {
	
	//opens the file to read
	FILE* filePtr = NULL;
	filePtr = fopen(filename, "r");
	if (filePtr == NULL) {
		puts("Could Not Open File");
		exit(1);
	}

	//gets rid of first line
	char junk[80];
	fgets(junk, 80, filePtr);

	//string for the rest of the files
	char fileLine[80];
	//while there is a line in the file do
	while (fgets(fileLine, 80, filePtr) != NULL) {

		//declares and copies countyName
		const char* countyName = malloc(sizeof(countyName));
		if (countyName == NULL) {
			puts("Could Not Allocate Memory");
			exit(1);
		}
		strcpy(countyName, rtrim(substring(fileLine, 0, 15)));

		//declares and copies the fipsCode
		const char* fipsCode = malloc(sizeof(fipsCode));
		if (fipsCode == NULL) {
			puts("Could Not Allocate Memory");
			exit(1);
		}
		strcpy(fipsCode, rtrim(substring(fileLine, 16, 27)));

		//declares and copies the seat 
		const char* seat = malloc(sizeof(seat));
		if (seat == NULL) {
			puts("Could Not Allocate Memory");
			exit(1);
		}
		strcpy(seat, rtrim(substring(fileLine, 27, 48)));

		//gets the population
		int population = atoi(substring(fileLine, 48, 60));
		
		//gets the area
		int area = atoi(substring(fileLine, 60, 63));
		
		//calls the new node to be added to list based off read in variables
		add_sorted_county(listPtr, countyName, fipsCode, seat, population, area);
	}
	//closes the file
	fclose(filePtr);
	filePtr = NULL;
}

//Writes the current list into a new file
void save_counties(list* listPtr, const char* filename) {

	//opens the file for read and write
	FILE* filePtr = NULL;
	filePtr = fopen(filename, "w+");
	if (filePtr == NULL) {
		puts("Could Not Open File");
		exit(1);
	}

	//puts the header line
	fputs("County Name,FIPS Code,Seat,Population,Area,Population Density", filePtr);

	//gets the head node
	struct node* headPtr = get_head_node(listPtr);
	//checks it exists
	if (headPtr != NULL) {

		//writes in the headPtr
		struct node* curPtr = headPtr;
		
		//while there are nodes left in the list
		while (get_next_node(curPtr) != NULL) {

			//write to the file
			fprintf(filePtr, "\n%s,%s,%s,%d,%d,%0.2f", 
				get_county_name(curPtr), get_fips_code(curPtr), get_seat(curPtr), get_population(curPtr)
				, get_area(curPtr), get_population_density(curPtr));
			
			//transition node
			curPtr = get_next_node(curPtr);
		}
		//writes in the last county
		fprintf(filePtr, "\n%s,%s,%s,%d,%d,%0.2f",
			get_county_name(curPtr), get_fips_code(curPtr), get_seat(curPtr), get_population(curPtr)
			, get_area(curPtr), get_population_density(curPtr));
	}

	//close the file
	fclose(filePtr);
	filePtr = NULL;
}


//Creates substring from larger string
const char* substring(const char* string, int start, int end){

	// Get length of substring
	int strlen = end - start;

	// Allocate enough memory for substring
	char* substringPtr = malloc((strlen + 1) * sizeof(char));
	if (substringPtr == NULL)
	{
		puts("Could not allocate memory for string.");
		exit(1);
	}

	// Initialize new substring to null terminators
	memset(substringPtr, 0, strlen + 1);

	// Copy substring
	strncpy(substringPtr, string + start, strlen);

	return substringPtr;
}

//Trims whitespace
const char* rtrim(const char* string){
	
	// Create new array large enough to handle string + null terminator
	char* strippedPtr = malloc((strlen(string) + 1) * sizeof(char));
	if (strippedPtr == NULL)
	{
		puts("Could not allocate memory for string.");
		exit(1);
	}

	// Null terminate new array
	memset(strippedPtr, 0, strlen(string) + 1);

	// Copy existing string into new array
	strncpy(strippedPtr, string, strlen(string));

	// Loop over string, start at end, to strip whitespace
	size_t position = strlen(string) - 1;
	while ((position >= 0) && isspace(strippedPtr[position]))
	{
		// Set char to null terminator
		strippedPtr[position] = '\0';

		// Advance one position to left
		position--;
	}

	return strippedPtr;
}

//Returns my name
const char* get_programmer_name(void) {
	const char* name = "Carter Copen";
	return name;
}
