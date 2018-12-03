#include <iostream>
#include <vector>
#include <time.h>

using std::cout;
using std::cin;
using std::vector;
using std::swap;

template<typename POINTER, typename MORE_FUN>
void SortFunction(const POINTER begin, const POINTER end, MORE_FUN More);

template<typename POINTER, typename MORE_FUN>
int MedianFunction(const POINTER begin, const POINTER end, MORE_FUN More);

bool More(uint32_t a, uint32_t b) {
	return a >= b;
}

int main() {
	
	srand(time(0));		//function that is used for making new random numbers every time this function is called

	const uint32_t ARRAY_LENGTH = 10;
	vector<uint32_t> array(ARRAY_LENGTH);
	
	for (int counter = 0; counter < ARRAY_LENGTH; counter++)		//fill the array with random numbers from 0 to 100
		array[counter] = rand() % 200 + 1;

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		cout << array[counter] << ' ';
	
	cout << '\n';
	SortFunction(array.begin(), array.end() - 1, More);

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)
		cout << array[counter] << ' ';

	cout << "\n";
	system("pause");
	return 0;
}

template<typename POINTER, typename MORE_FUN>
void SortFunction(const POINTER begin, const POINTER end, MORE_FUN More) {

	if (end == begin)		//if segment is one character in length it is already sorted
		return;

	//left end of segment given is adopted for supporting element
	uint32_t left_index = 0, right_index = 0;

	const int index = MedianFunction(begin, end, More);			//Function that finds the median of three elements (start, end, middle)
	const POINTER supporting_element = begin + index;

	while (begin + left_index != end - right_index) {

		if (More(*supporting_element, *(begin + left_index)))
			left_index += 1;
		else if (More(*(end - right_index), *supporting_element))
			right_index += 1;
		else swap(*(begin + left_index), *(end - right_index));

	}

	if (More(*(end - right_index), *supporting_element)) {	//moving supporting element on his right place in a sequence
		if(index >= left_index)
			swap(*supporting_element, *(end - right_index));
		else {
			right_index += 1;
			swap(*supporting_element, *(end - right_index));
		}
	}
	else swap(*supporting_element, *(end - right_index));

	if(begin != end - right_index) SortFunction(begin, end - right_index - 1, More);
	if(end - right_index != end) SortFunction(end - right_index + 1, end, More);
}

template<typename POINTER, typename MORE_FUN>
int MedianFunction(const POINTER begin, const POINTER end, MORE_FUN More) {		//function returns index that must be added to the beginning to find median element
	uint32_t index = 0;
	bool index_2 = 0;		//index to see if the length of section is even or not
	while ((begin + index != end - index) && (begin + index != end - index + 1))
		index += 1;
	if (begin + index == end - index) index_2 = 0;
	else index_2 = 1;
	if (More(*begin, *(begin + index)))
		if (More(*(begin + index), *end))
			return index;
		else
			if (More(*end, *begin))
				return 0;
			else
				return (index - index_2) * 2 + index_2;
	else
		if (More(*begin, *end))
			return 0;
		else
			if (More(*end, *(begin + index)))
				return index;
			else
				return (index - index_2) * 2 + index_2;
}