#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "iostream"
#include <vector>
#include <time.h>

using std::cout;
using std::cin;
using std::vector;

template<typename POINTER, typename LESS_FUN, typename SOME_TYPE>
void SortFunction(const POINTER begin, const POINTER end);
uint32_t Less(uint32_t a, uint32_t b);

int main() {
	
	srand(time(0));		//function that is used for making new random numbers every time this function is called

	const uint32_t ARRAY_LENGTH = 33;
	vector<uint32_t> array(ARRAY_LENGTH);
	
	for (int counter = 0; counter < ARRAY_LENGTH; counter++)		//fill the array with random numbers from 0 to 100
		array[counter] = rand() % 100;

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		cout << array[counter] << ' ';

	cout << '\n';
	uint32_t *begin = &(array[0]), *end = &(array[ARRAY_LENGTH - 1]);
	SortFunction<uint32_t>(*begin, *end);									//ERROR is here

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		cout << array[counter] << ' ';

	int just_for_luls;		//words to stay console in open state
	cin >> just_for_luls;
}

template<typename POINTER, typename LESS_FUN, typename SOME_TYPE>
void SortFunction(const POINTER begin, const POINTER end) {

	if (&end - &begin + 1 <= 1)		//if segment is one character in length it is already sorted
		return;
	
	POINTER supporting_value = begin;		//left end of segment given is adopted for supporting element
	uint32_t left_index = 0, right_index = 0;
	POINTER additional_variable;		//variable needed during elements reshuffling
	
	for ( ;begin + left_index == end - right_index; ) {

		if (begin + left_index <= supporting_value)
			left_index += 1;
		else {
			if (end - right_index >= supporting_value)
				right_index += 1;
			else {
				additional_variable = begin + left_index;		//reshaffle elements
				begin + left_index = end - right_index;			
				end - right_index = additional_variable;		
			}
		}
		
	}

	if (end - right_index >= supporting_value) {	//moving supporting element on his right place in a sequence
		additional_variable = supporting_value;
		supporting_value = end - right_index + 1;
		end - right_index + 1 = additional_variable;
		right_index += 1;
	}
	else {
		additional_variable = supporting_value;
		supporting_value = end - right_index;
		end - right_index = additional_variable;
	}

	SortFunction(begin, end - right_index - 1);
	SortFunction(end - right_index + 1, end);

}


uint32_t Less(uint32_t a, uint32_t b) {
	if (a > b) return a;
	else return b;
}