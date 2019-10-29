#include "postfix.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <locale>
#include <algorithm>
#include <vector>
TPostfix::TPostfix(string _c)
{
	infix = _c;
}
TPostfix::TPostfix()
{
	infix = "";
}
bool TPostfix::Is_Operator(char c)
{
	const string operators = "+-*/()";
	if (operators.find(c) == string::npos)
		return 0;
	return 1;
}

bool TPostfix::Is_Operand(char c)
{
	const string operand = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";;
	if (operand.find(c) == string::npos)
		return 0;
	return 1;
}

int TPostfix::Priority(string c)
{
	int res = -1;
	if (c == "(")
		res = 1;
	if ((c == "-") || (c == "+"))
		res = 2;
	if ((c == "*") || (c == "/"))
		res = 3;
	if ((c == "++") || (c == "--"))
		res = 4;
	if ((c == "sin") || (c == "cos") || (c == "tg") || (c == "ctg") || (c == "ln"))
		res = 5;
	return res;
}

void TPostfix::Delete_Space()
{
	string c1 = "";
	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] != ' ')
			c1 += infix[i];
	}
	infix = c1;
}

void TPostfix::To_normal()
{
	TPostfix f;
	string str = "";
	string tmp;
	const string numbers = "0123456789";
	for (int i = 0; i < infix.length(); i++)
	{
		tmp = Is_Unary_operation(i);
		if (tmp != "")
		{
			str += tmp;
			continue;
		}
		str += infix[i];
		if ((f.Is_Operand(infix[i])) && (f.Is_Operand(infix[i + 1])))
			str += "*";
		if ((f.Is_Operand(infix[i])) && (numbers.find(infix[i+1]) != string::npos))
			str += "*";
		if ( (numbers.find(infix[i]) != string::npos) && (f.Is_Operand(infix[i+1])))
			str += "*";
		if ((infix[i] == ')') && (infix[i + 1] == '('))
			str += "*";
		if ((infix[i] == ')') && (f.Is_Operand(infix[i + 1])))
			str += "*";
		if ((f.Is_Operand(infix[i + 1])) && (infix[i + 1] == '('))
			str += "*";
	}
	infix = str;
}

int TPostfix::Check_Parentheses(const string & c) const
{
	int open = 0;
	int close = 0;
	for (int i = 0; i < c.length();i++)
	{
		if (c[i] == '(')
			open++;
		if (c[i] == ')')
			close++;
	}
	if (open != close) return 0;
	else return 1;

}

int TPostfix::Check_Str()
{
	if (infix.length() == 0)
		return 0;
	TPostfix p;
	if ((infix.length() == 1) && (p.Is_Operator(infix[0])))
		return 0;
	if ((infix[0] == '*') || (infix[0] == '/'))
		return 0;
	if ((infix[infix.length() - 1] == '*') || (infix[infix.length() - 1] == '/') || (infix[infix.length() - 1] == '-') || (infix[infix.length() - 1] == '+'))
		return 0;
	
	for (int i = 0; i < infix.length() - 1; i++)
	{
		int j = i + 1;
		if (Is_Unary_operation(i) != "")
		{
			if ((i+1 == infix.length() ) ||(infix[i+1] == ')') || (infix[i+1] == '*') || (infix[i+1] == '/') || (infix[i+1] == '+') || (infix[i+1] == '-'))
				return 0;
			continue;
		}
		if ((infix[i] == '(') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '*') || (infix[i + 1] == '/') || (infix[i + 1] == '-')))
			return 0;

		if ((infix[i + 1] == ')') && ((infix[i] == '-') || (infix[i] == '+') || (infix[i] == '*') || (infix[i] == '/')))
			return 0;

		if ((infix[i] == '(') && (infix[i + 1] == ')'))
			return 0;
		
		if ((infix[i] == '+') && (Is_Unary_operation(j) == "")&&((infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '/') || (infix[i + 1] == ')') || (infix[i + 1] == '*')))
			return 0;
		if ((infix[i] == '-') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '/') || (infix[i + 1] == ')') || (infix[i + 1] == '*')))
			return 0;
		if ((infix[i] == '*') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '/') || (infix[i + 1] == ')') || (infix[i + 1] == '*')))
			return 0;
		if ((infix[i] == '/') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '/') || (infix[i + 1] == ')') || (infix[i + 1] == '*')))
			return 0;
	}
	return 1;
}
string TPostfix::Is_Unary_operation(int &i)
{
	string tmp = "";
	if ((i < infix.length() - 1) && (((infix[i] == 's') && (infix[i + 1] == 'i') && (infix[i + 2] == 'n'))
		|| ((infix[i] == 'c') && (infix[i + 1] == 'o') && (infix[i + 2] == 's'))
		|| ((infix[i] == 'c') && (infix[i + 1] == 't') && (infix[i + 2] == 'g'))))
	{
		tmp += infix[i];
		tmp += infix[i + 1];
		tmp += infix[i + 2];
		i += 2;
	}
	else if ((i < infix.length() - 2) && (((infix[i] == 't') && (infix[i + 1] == 'g'))
		|| ((infix[i] == 'l') && (infix[i + 1] == 'n'))
		|| ((infix[i] == '+') && (infix[i + 1] == '+'))
		|| ((infix[i] == '-') && (infix[i + 1] == '-'))))
	{
		tmp += infix[i];
		tmp += infix[i + 1];
		i += 1;
	}
	return tmp;
}
void TPostfix::ToPostfix()
{
	if (infix.length() == 0) throw "negative";
	Delete_Space();
	To_normal();
	if ((Check_Str() == 0) || (Check_Parentheses(infix) == 0)) throw "negative";

	const string numbers = "0123456789";
	TStack<string> op(30);
	TStack<string> res(30);
	string tmp;
	int j;
	string Invert_res_Str = "";
	int len = infix.length();
	for (int i = 0; i < len; i++)
	{

		tmp = "";
		j = i;
		while (((numbers.find(infix[j]) != string::npos)) && (j < infix.length()))
		{
			tmp += infix[j];
			j++;
		}
		if (tmp.length() > 1)
		{
			res.Push(tmp);
			i = j - 1;
			continue;
		}
		tmp = Is_Unary_operation(i);
		
		if (tmp.length() > 0)
		{
			if ((!op.IsEmpty()) && (Priority(tmp) <= Priority(op.GetTopElement())))
				while ((!op.IsEmpty()) && (Priority(tmp) <= Priority(op.GetTopElement())))
					res.Push(op.Pop());
			op.Push(tmp);
			continue;
		}
		string str = "";
		str += infix[i];

		if ((Is_Operator(infix[i])) && (infix[i] != ')'))
		{

			if ((!op.IsEmpty()) && (Priority(str) <= Priority(op.GetTopElement())) && (infix[i] != '('))
				while ((!op.IsEmpty()) && (Priority(str) <= Priority(op.GetTopElement())))
					res.Push(op.Pop());
			op.Push(str);
		}

		else if ((Is_Operand(infix[i]) == 1) || (infix[i] >= '0') && (infix[i] <= '9'))
			res.Push(str);


		else if (str == ")")
		{
			string r = "";
			while ((!op.IsEmpty()) && (r != "("))
			{
				r = op.Pop();
				res.Push(r);
			}
			if (r == "(")
				res.Pop();
		}
		else throw ("negative");
	}

	while (!op.IsEmpty())
		res.Push(op.Pop());
	while (!res.IsEmpty())
	{
		string s;
		s = res.Pop();
		Invert_res_Str += ' ';
		for (int i = s.length() - 1; i >= 0; i--)
			Invert_res_Str += s[i];

	}
	for (int j = Invert_res_Str.length() - 1; j > 0; j--)
	{
		postfix += Invert_res_Str[j];
	}

}

double TPostfix::Calculate()
{
	if (postfix == "")
		throw "String is empy";
	TStack <double> res(30);
	string tmp = "";
	const string numbers = "0123456789";
	const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int j;
	int f = 0;
	double str;
	double left_op;
	double right_op;
	double arr2[10];
	int arr2_count = 0;
	string str1 = "";
	for (int i = 0; i < postfix.length(); i++)
	{
		tmp = "";
		j = i;
		while ((postfix[j] != ' ') && (j < postfix.length()))
		{
			tmp += postfix[j];
			j++;
		}
		if (numbers.find(tmp[0]) != string::npos)
		{
			res.Push(To_Int(tmp));
			i = j;
			continue;
		}
		else if (tmp.length() != 1)
		{
			right_op = res.Pop();
			if (tmp == "sin") res.Push(sin(right_op));
			if (tmp == "cos") res.Push(cos(right_op));
			if (tmp == "tg") res.Push(tan(right_op));
			if (tmp == "ctg") res.Push(1/tan(right_op));
			if (tmp == "ln")
			{
				if (right_op <= 0) throw "negative";
				res.Push(log(right_op));
			}
			if (tmp == "++") res.Push(right_op + 1);
			if (tmp == "--") res.Push(right_op - 1);
			i = j;

			continue;
		}
		else
		{
			tmp = postfix[i];
			if (alphabet.find(tmp) != string::npos)
			{
				f = -1;
				for (int k = 0; k < str1.length(); k++)
					if (postfix[i] == str1[k]) f = k;	//проверка на повторный ввод одной и той же переменной

				if (f == -1)
				{
					cout << "Enter the " << tmp << ": ";
					cin >> str;
					str1 += postfix[i];
					arr2[arr2_count] = str;
					arr2_count++;
					res.Push(str);
				}
				else
					res.Push(arr2[f]);
				i++;
				continue;
			}
		}
		right_op = res.Pop();
		if ((res.IsEmpty()) && (tmp == "-"))
		{
			res.Push(-right_op);
			i++;
			continue;
		}

		if ((res.IsEmpty()) && (tmp == "+"))
		{
			res.Push(right_op);
			i++;
			continue;
		}
		left_op = res.Pop();
		if (tmp == "+") res.Push(left_op + right_op);
		if (tmp == "-") res.Push(left_op - right_op);
		if (tmp == "*") res.Push(left_op * right_op);
		if (tmp == "/")
		{
			if (right_op == 0) throw "Division by zero";
			res.Push(left_op / right_op);
		}
		i++;

	}
	return res.Pop();
}
int To_Int(string c)
{
	int res = 0;
	for (int i = 0; i < c.length(); i++)
	{
		res = res * 10 + c[i] - '0';
	}
	return res;
}
