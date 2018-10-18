#include <iostream>
#include <vector>
#include <time.h>

using std::cout;
using std::cin;
using std::vector;
using std::swap;

template<typename POINTER, typename LESS_FUN>
void SortFunction(const POINTER begin, const POINTER end, LESS_FUN More);

bool more(uint32_t a, uint32_t b) {
	return a >= b;
}

int main() {
	
	srand(time(0));		//function that is used for making new random numbers every time this function is called

	const uint32_t ARRAY_LENGTH = 33;
	vector<uint32_t> array(ARRAY_LENGTH);
	
	for (int counter = 0; counter < ARRAY_LENGTH; counter++)		//fill the array with random numbers from 0 to 100
		array[counter] = rand() % 200 + 1;

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		cout << array[counter] << ' ';

	cout << '\n';
	SortFunction(array.begin(), array.end() - 1, more);

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		cout << array[counter] << ' ';

	cout << "\n";
	system("pause");
	return 0;
}

template<typename POINTER, typename LESS_FUN>
void SortFunction(const POINTER begin, const POINTER end, LESS_FUN More) {

	if (end == begin)		//if segment is one character in length it is already sorted
		return;

	//left end of segment given is adopted for supporting element
	uint32_t left_index = 0, right_index = 0;

	while (begin + left_index != end - right_index) {

		if (More(*begin, *(begin + left_index)))
			left_index += 1;
		else if (More(*(end - right_index), *begin))
			right_index += 1;
		else swap(*(begin + left_index), *(end - right_index));

	}

	if (More(*(end - right_index), *begin)) {	//moving supporting element on his right place in a sequence
		right_index += 1;
		swap(*begin, *(end - right_index));
	}
	else swap(*begin, *(end - right_index));

	if(begin != end - right_index) SortFunction(begin, end - right_index - 1, More);
	if(end - right_index != end) SortFunction(end - right_index + 1, end, More);
}