#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include <time.h>

using std::cout;		//working in namespace std, but only take cout è cin functions out of there
using std::cin;

#define ARRAY_LENGTH 33		//define the length of array

int array[ARRAY_LENGTH];	//make the global array, for not throwing it between functions
int SortFunction(int left_end, int right_end);		//define working function

int main() {		//main function
	
	srand(time(0));		//function that is used for making new random numbers every time this function is called

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)		//fill the array with random numbers from 0 to 100
		array[counter] = rand() % 100;

	for (int counter = 0; counter < ARRAY_LENGTH; counter++) {		//printing array
		cout << array[counter];
		cout << ' ';
	}

	cout << '\n';		//indentation

	SortFunction(0, ARRAY_LENGTH);		//calling main working function

	for (int counter = 0; counter < ARRAY_LENGTH; counter++) {		//printing sorted array
		cout << array[counter];
		cout << ' ';
	}

	int just_for_luls;		//words to stay console in open state
	cin >> just_for_luls;
}


int SortFunction(int left_end, int right_end) {		//main working function
	
	if (right_end - left_end < 1)		//if segment is one character in length
		return 0;
	
	int supporting_index = left_end;		//left end of segment given is adopted for supporting element
	int left_index = left_end, right_index = right_end;		//indices are given the value of the ends of segment
	int additional_variable;		//variable needed during elements reshuffling
	
	while (left_index < right_index) {		//cycle is working until we go through all elements in the segment

		if (array[left_index] <= array[supporting_index])
			left_index += 1;
		else {
			if (array[right_index] >= array[supporting_index])
				right_index -= 1;
			else {
				additional_variable = array[left_index];		//reshaffle elements
				array[left_index] = array[right_index];			
				array[right_index] = additional_variable;		
			}
		}
		
	}
	additional_variable = array[supporting_index];		//moving supporting element on his right place in a sequence
	array[supporting_index] = array[right_index - 1];
	array[right_index - 1] = additional_variable;
	supporting_index = right_index - 1;		//changing supporting element index	

	if (right_end - left_end <= 2)		//if segment is 3 elements in length, it's already sorted
		return 0;

	SortFunction(left_end, supporting_index);		//call next stage (recursion)
	SortFunction(supporting_index + 1, right_end);
	
	return 0;
}
