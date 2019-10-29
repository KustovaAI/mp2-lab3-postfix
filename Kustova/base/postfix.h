#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
	
	string infix;
	string postfix;
public:
	TPostfix(string _c);
	TPostfix();
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	void ToPostfix();
	void Delete_Space();
	void To_normal();
	int Check_Parentheses(const string& c)const;
	int Check_Str();
	string Is_Unary_operation(int &i);
	bool Is_Operator(char c);
	bool Is_Operand(char c);
	int Priority(string c);
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};
int To_Int(string c);
#endif
