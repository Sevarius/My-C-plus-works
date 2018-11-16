#include"iostream"
#include<deque>
#include<string>

using namespace std;

class element{
	
public:
	bool index;
	double value;
	char sign;
	element() {
		index = NAN;
		value = NAN;
		sign = NAN;
	}
	element(char a) {
		index = 0;
		value = NAN;
		sign = a;
	}

	element(double a) {
		index = 1;
		value = a;
		sign = NAN;
	}

	friend ostream &operator<<(ostream &os, const element &el);

};
ostream &operator<<(ostream &os, const element &el)						//cout for my class
{  
	if (el.index == 1)
		os << el.value;
	else
		os << el.sign;
    return os;  
}   
ostream &operator<<(ostream &os, deque<element> &de)					//cout for the deque<my class>
{
	deque<element>::iterator it;
	for(it = de.begin();it != de.end(); it++)
		os << *it << " ";
	return os;
}

deque<element> ReadLine(string &line);										//string ---> deque
deque<element> Reform(deque<element> &MyDeque);								//deque ---> reverse polish annotation deque
double CountAnswer(deque<element> &MyDeque);								//reverse polish annotation deque ---> answer
int Prior(element a);														//function that returns the priority of operations

int main() {
	string line;
	getline(cin, line);
	deque<element> MyDeque;

	MyDeque = ReadLine(line);
	cout << MyDeque << "\n";

	MyDeque = Reform(MyDeque);
	cout << MyDeque << "\n";

	double Ans = CountAnswer(MyDeque);
	cout << Ans;
	
	cout << "\n";
	system("pause");
	return 0;
}
deque<element> ReadLine(string &line) {
	string LitLine;
	element el;
	deque<element> MainDeq;
	string::iterator it = line.begin();

	while (it != line.end()) {							//"reading" line
		if (*it == ' ')									//pass by free space
			it++;
		else if (*it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '%' || *it == '(' || *it == ')' || *it == '^' || *it == 'e') {		//stop "reading" number
			if (LitLine.size() != 0) {																												//putting number in the deque
				el.index = 1;
				el.value = atof(LitLine.c_str());
				el.sign = NAN;
				LitLine = "";
				MainDeq.push_back(el);
			}
			el.index = 0;								//putting sign in the deque
			el.value = NAN;
			el.sign = *it;
			MainDeq.push_back(el);
			it++;
		}
		else {											//continue to "read" number
			LitLine += *it;
			it++;
		}
	}
	if (LitLine.size() != 0) {							//put last number in the deque
		el.index = 1;
		el.value = atof(LitLine.c_str());
		el.sign = NAN;
		LitLine = "";
		MainDeq.push_back(el);
	}
	return MainDeq;
}

deque<element> Reform(deque<element> &MyDeque) {
	deque<element> AnsDeq, SignDeq;
	deque<element>::iterator ItMain = MyDeque.begin(), ItSign;

	while (ItMain != MyDeque.end()) {				//reading deque

		if ((*ItMain).index == 1)					//putting numbers in the deque
			AnsDeq.push_back(*ItMain);

		else if ((SignDeq.size() == 0 || (*ItMain).sign == '(' || SignDeq.back().sign == '(' || Prior(*ItMain) < Prior(SignDeq.back())) && (*ItMain).sign != ')')		//putting signs in the deque
			SignDeq.push_back(*ItMain);

		else if ((*ItMain).sign == ')') {			//moving signs to the deque with numbers because of ')' 
			ItSign = SignDeq.end() - 1;
			while ((*ItSign).sign != '(') {
				AnsDeq.push_back(*ItSign);
				SignDeq.erase(ItSign);
				ItSign = SignDeq.end() - 1;
			}
			SignDeq.erase(ItSign);
		}

		else if (Prior(*ItMain) >= Prior(SignDeq.back())) {			//moving signs to the deque with numbers because of their priority
			ItSign = SignDeq.end() - 1;
			while (Prior(*ItMain) >= Prior(SignDeq.back())) {
				AnsDeq.push_back(*ItSign);
				SignDeq.erase(ItSign);
				ItSign = SignDeq.end() - 1;
				if (SignDeq.size() == 0)
					break;
			}
			SignDeq.push_back(*ItMain);
		}

		ItMain++;
	}

	while (SignDeq.size() != 0) {				//moving remaining signs to the deque with numbers
		ItSign = SignDeq.end() - 1;
		AnsDeq.push_back(*ItSign);
		SignDeq.erase(ItSign);
	}

	return AnsDeq;
}

double CountAnswer(deque<element> &MyDeque) {			//counting answer
	deque<element>::iterator it;
	int i = 0;

	while (MyDeque.size() > 1) {
		if (MyDeque[i].index == 1)
			i++;
		else {
			element ans;
			ans.index = 1;
			ans.sign = NAN;
			switch (MyDeque[i].sign) {
			case '+':
				ans.value = MyDeque[i - 2].value + MyDeque[i - 1].value;
				break;
			case '-':
				ans.value = MyDeque[i - 2].value - MyDeque[i - 1].value;
				break;
			case '*':
				ans.value = MyDeque[i - 2].value * MyDeque[i - 1].value;
				break;
			case '/':
				ans.value = MyDeque[i - 2].value / MyDeque[i - 1].value;
				break;
			case '%':
				ans.value = double(int(MyDeque[i - 2].value) % int(MyDeque[i - 1].value));
				break;
			case '^':
				ans.value = pow(MyDeque[i - 2].value, MyDeque[i - 1].value);
				break;
			case 'e':
				ans.value = MyDeque[i - 2].value * pow(10.0, MyDeque[i - 1].value);
			}
			i -= 2;
			it = MyDeque.begin() + i;
			MyDeque.erase(it);
			it = MyDeque.begin() + i;
			MyDeque.erase(it);
			it = MyDeque.begin() + i;
			MyDeque.erase(it);
			it = MyDeque.begin() + i;
			MyDeque.insert(it, ans);
		}
	}

	return MyDeque[0].value;
}

int Prior(element a) {
	switch (a.sign) {
	case '+':
		return 6;
	case '-':
		return 6;
	case '*':
		return 5;
	case '/':
		return 5;
	case '%':
		return 5;
	case '^':
		return 4;
	case 'e':
		return 3;
	case '(':
		return 100;
	case ')':
		return 100;
	}
}