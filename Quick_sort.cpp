#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "iostream"
#include <vector>
#include <time.h>

using std::cout;
using std::cin;
using std::vector;

template<typename SOME_TYPE>
int SortFunction(uint32_t left_end, uint32_t right_end, vector<SOME_TYPE> &ARRAY);

int main() {
	
	srand(time(0));		//function that is used for making new random numbers every time this function is called

	const uint32_t ARRAY_LENGTH = 33;
	vector<uint32_t> array(ARRAY_LENGTH);
	
	for (int counter = 0; counter < ARRAY_LENGTH; counter++)		//fill the array with random numbers from 0 to 100
		array[counter] = rand() % 100;

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		cout << array[counter] << ' ';

	cout << '\n';

	SortFunction<uint32_t>(0, ARRAY_LENGTH - 1, array);

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		cout << array[counter] << ' ';

	int just_for_luls;		//words to stay console in open state
	cin >> just_for_luls;
}

template<typename SOME_TYPE>
int SortFunction(uint32_t left_end, uint32_t right_end, vector<SOME_TYPE> &ARRAY) {

	if (right_end - left_end + 1 <= 1)		//if segment is one character in length it is already sorted
		return 0;
	
	uint32_t supporting_index = left_end;		//left end of segment given is adopted for supporting element
	uint32_t left_index = left_end, right_index = right_end;
	SOME_TYPE additional_variable;		//variable needed during elements reshuffling
	
	for ( ;left_index < right_index; ) {

		if (ARRAY[left_index] <= ARRAY[supporting_index])
			left_index += 1;
		else {
			if (ARRAY[right_index] >= ARRAY[supporting_index])
				right_index -= 1;
			else {
				additional_variable = ARRAY[left_index];		//reshaffle elements
				ARRAY[left_index] = ARRAY[right_index];			
				ARRAY[right_index] = additional_variable;		
			}
		}
		
	}

	if (ARRAY[right_index] >= ARRAY[supporting_index]) {	//moving supporting element on his right place in a sequence
		additional_variable = ARRAY[supporting_index];
		ARRAY[supporting_index] = ARRAY[right_index - 1];
		ARRAY[right_index - 1] = additional_variable;
		supporting_index = right_index - 1;
	}
	else {
		additional_variable = ARRAY[supporting_index];
		ARRAY[supporting_index] = ARRAY[right_index];
		ARRAY[right_index] = additional_variable;
		supporting_index = right_index;
	}

	SortFunction(left_end, supporting_index - 1, ARRAY);
	SortFunction(supporting_index + 1, right_end, ARRAY);
	
	return 0;
}
