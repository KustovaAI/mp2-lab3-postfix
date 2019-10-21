#include <iostream>
#include <string>
#include "postfix.h"
#include <cstdlib>
using namespace std;

int main()
{
	string expression;
	
	double res;

	setlocale(LC_ALL, "Russian");
	cout << "Введите арифметическое выражение: ";
	getline(cin, expression);
	/*cout << expression << endl;
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;*/
	TPostfix postfix(expression);
	postfix.ToPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	res = postfix.Calculate();
	cout << res << endl;

	return 0;
}
