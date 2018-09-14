#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include <time.h>

using std::cout;
using std::cin;

#define ARRAY_LENGTH 33

int array[ARRAY_LENGTH];
int SortFunction(int left_end, int right_end);

int main() {
	
	srand(time(0));

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		array[counter] = rand() % 100;

	for (int counter = 0; counter < ARRAY_LENGTH; counter++) {
		cout << array[counter];
		cout << ' ';
	}

	cout << '\n';
	SortFunction(0, ARRAY_LENGTH);

	for (int counter = 0; counter < ARRAY_LENGTH; counter++) {
		cout << array[counter];
		cout << ' ';
	}

	int just_for_luls;
	cin >> just_for_luls;
}


int SortFunction(int left_end, int right_end) {
	
	if (right_end - left_end < 1)
		return 0;
	
	int supporting_index = left_end;
	int left_index = left_end, right_index = right_end;
	int additional_variable;
	
	while (left_index < right_index) {

		if (array[left_index] <= array[supporting_index])
			left_index += 1;
		else {
			if (array[right_index] >= array[supporting_index])
				right_index -= 1;
			else {
				additional_variable = array[left_index];
				array[left_index] = array[right_index];
				array[right_index] = additional_variable;
			}
		}
		
	}
	additional_variable = array[supporting_index];
	array[supporting_index] = array[right_index - 1];
	array[right_index - 1] = additional_variable;
	supporting_index = right_index - 1;

	if (right_end - left_end <= 2)
		return 0;

	SortFunction(left_end, supporting_index);
	SortFunction(supporting_index + 1, right_end);
	
	return 0;
}
