#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include <time.h>

using std::cout;		//работаем в пространстве имён std, но берём отттуда только функции cout и cin
using std::cin;

#define ARRAY_LENGTH 33		//определяем длину массива

int array[ARRAY_LENGTH];	//задаём глобальный массив, чтобы не перекидывать его между функциями
int SortFunction(int left_end, int right_end);		//определяем функцию

int main() {		//функция main
	
	srand(time(0));		//функция вызываемая для новой рандомизации чисел с каждым вызовом функции

	for (int counter = 0; counter < ARRAY_LENGTH; counter++)		//заполняем массив рандомными числами от 0 до 100
		array[counter] = rand() % 100;

	for (int counter = 0; counter < ARRAY_LENGTH; counter++) {		//выводим массив
		cout << array[counter];
		cout << ' ';
	}

	cout << '\n';		//отступ

	SortFunction(0, ARRAY_LENGTH);		//вызов основной действующей функции

	for (int counter = 0; counter < ARRAY_LENGTH; counter++) {		//вывод сортированного массива
		cout << array[counter];
		cout << ' ';
	}

	int just_for_luls;		//действия, нужные для того, чтобы консоль оставалась открытой и мы могли проверить результаты
	cin >> just_for_luls;
}


int SortFunction(int left_end, int right_end) {		//основная действующая функция
	
	if (right_end - left_end < 1)		//если передаваемый отрезок состоит из одного элемента, то считаем его уже сортированным
		return 0;
	
	int supporting_index = left_end;		//левый конец отрезка принимаем за опорный элемент
	int left_index = left_end, right_index = right_end;		//присваиваем индексам значения концов отрезков
	int additional_variable;		//переменная нужная при перестановке элементов
	
	while (left_index < right_index) {		//цикл действует до того момента, когда индексы движения от концов отрезка не станут равными

		if (array[left_index] <= array[supporting_index])		//сравниваем значение массива на левом индексе с опорным элементом
			left_index += 1;		//двигаем индекс левого конца на 1 вперёд
		else {
			if (array[right_index] >= array[supporting_index])// --//--
				right_index -= 1;		//двигаем индекс правого конца на 1 назад
			else {
				additional_variable = array[left_index];		//меняем местами два элемента
				array[left_index] = array[right_index];
				array[right_index] = additional_variable;
			}
		}
		
	}
	additional_variable = array[supporting_index];		//двигаем опорный элемент на место, где слева от него будут меньшие элементы, а справа - большие
	array[supporting_index] = array[right_index - 1];
	array[right_index - 1] = additional_variable;
	supporting_index = right_index - 1;		//меняем индес опорного элемента	

	if (right_end - left_end <= 2)		//в случае отрезка длиной 3 и меньше, данный отрезок уже считается отсортированным
		return 0;

	SortFunction(left_end, supporting_index);		//рекурсионно запускаем функцию на новые отрезки
	SortFunction(supporting_index + 1, right_end);
	
	return 0;
}
