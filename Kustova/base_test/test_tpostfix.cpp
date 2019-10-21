#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_from_string)
{
	string p = "a +m";
	ASSERT_NO_THROW(TPostfix pf(p));
}

TEST(TPostfix, check_when_after_open_parentheses_goes_operator)
{
	TPostfix p;
	string s = "J- (-";
	EXPECT_EQ(false, p.Check_Str());
}

TEST(TPostfix, check_when_before_close_parentheses_goes_operator)
{
	TPostfix p;
	string s = "J-(b -)";
	EXPECT_EQ(false, p.Check_Str());
}

TEST(TPostfix, check_there_are_two_operator_in_a_row)
{
	TPostfix p;
	string s = "a+-b";
	EXPECT_EQ(false, p.Check_Str());
}
TEST(TPostfix, check_when_the_first_symbol_is_operator_multiplication_or_division)
{
	TPostfix p;
	string s = "*g-k";
	EXPECT_EQ(false, p.Check_Str());
}
TEST(TPostfix, check_when_the_last_symbol_is_operator)
{
	TPostfix p;
	string s = "g-k+";
	EXPECT_EQ(false, p.Check_Str());
}
TEST(TPostfix, check_when_after_unary_operation_goes_operator)
{
	TPostfix p;
	string s = "a+sin+";
	EXPECT_EQ(false, p.Check_Str());
}
TEST(TPostfix, check_when_the_last_symbol_is_unary_operator)
{
	TPostfix p;
	string s = "5+ln";
	EXPECT_EQ(false, p.Check_Str());
}
TEST(TPostfix, throw_infix_is_empty)
{
	TPostfix p;
	EXPECT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, check_when_different_count_of_open_and_close_parentheses)
{
	TPostfix p;
	string s = "(h-9))";
	EXPECT_EQ(false, p.Check_Parentheses(s));
}

TEST(TPostfix, can_delete_space)
{
	string s = "a +  b";
	TPostfix p(s);
	p.Delete_Space();
	EXPECT_EQ("a+b", p.GetInfix());
}

TEST(TPostfix, is_unary_operation)
{
	string s = "a+lnx";
	TPostfix p(s);
	int i = 2;
	int j = 1;
	EXPECT_EQ("ln", p.Is_Unary_operation(i));
	EXPECT_EQ("", p.Is_Unary_operation(j));
}

TEST(TPostfix, can_to_postfix_some_values)
{
	string s = "a + b - c";
	TPostfix p(s);
	p.ToPostfix();
	EXPECT_EQ("a b + c -", p.GetPostfix());
}

TEST(TPostfix, can_to_postfix_expression_with_parentheses)
{
	string s = "(a +n)*m";
	TPostfix p(s);
	p.ToPostfix();
	EXPECT_EQ("a n + m *", p.GetPostfix());
}

TEST(TPostfix, can_to_postfix_expression_with_constant)
{
	string s = "a + b -21";
	TPostfix p(s);
	p.ToPostfix();
	EXPECT_EQ("a b + 21 -", p.GetPostfix());
}
TEST(TPostfix, can_to_postfix_expression_with_unary_operation)
{
	string s = "a + b -sin(++x)";
	TPostfix p(s);
	p.ToPostfix();
	EXPECT_EQ("a b + x ++ sin -", p.GetPostfix());
}

TEST(TPostfix, can_convert_expression_to_normal_view)
{
	string s1 = "ab + c";
	string s2 = "(a+n)(b-n)";
	TPostfix p1(s1), p2(s2);
	p1.To_normal();
	p2.To_normal();
	EXPECT_EQ("a*b + c", p1.GetInfix());
	EXPECT_EQ("(a+n)*(b-n)", p2.GetInfix());
}

TEST(TPostfix, can_get_priority)
{
	string s1 = "(";
	string s2 = "+";
	string s3 = "*";
	string s4 = "++";
	string s5 = "sin";
	TPostfix p(s1);
	EXPECT_EQ(1, p.Priority(s1));
	EXPECT_EQ(2, p.Priority(s2));
	EXPECT_EQ(3, p.Priority(s3));
	EXPECT_EQ(4, p.Priority(s4));
	EXPECT_EQ(5, p.Priority(s5));
}

TEST(TPostfix, check_is_operator)
{
	TPostfix p;
	EXPECT_EQ(true, p.Is_Operator('+'));
	EXPECT_EQ(false, p.Is_Operator('a'));
}

TEST(TPostfix, check_is_operand)
{
	TPostfix p;
	EXPECT_EQ(true, p.Is_Operand('a'));
	EXPECT_EQ(false, p.Is_Operand('+'));
}

TEST(TPostfix, can_calculate_two_const)
{
	string s = "2+2";
	TPostfix p(s);
	p.ToPostfix();
	EXPECT_DOUBLE_EQ(4., p.Calculate());
}

TEST(TPostfix, throw_divide_by_zero)
{
	string s = "4/0";
	TPostfix p(s);
	p.ToPostfix();
	ASSERT_ANY_THROW(p.Calculate());
}
TEST(TPostfix, throw_lg_from_no_positive_number)
{
	string s = "ln0";
	TPostfix p(s);
	p.ToPostfix();
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, can_calculate_hard_expression)
{
	string s = "(((10-20) + 44)/2 -9)*8";
	TPostfix p(s);
	p.ToPostfix();
	EXPECT_DOUBLE_EQ(64., p.Calculate());
}
