#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-3));
}

TEST(TStack, can_push_to_stack)
{
	TStack<int> st(10);
	ASSERT_NO_THROW(st.Push(10));
}

TEST(TStack, throw_when_push_to_full_stack)
{
	TStack<int> st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);
	ASSERT_ANY_THROW(st.Push(4));
}

TEST(TStack, can_pop_from_stack)
{
	TStack<int> st(5);
	st.Push(4);
	ASSERT_NO_THROW(st.Pop());
}

TEST(TStack, throw_when_pop_from_empty_stack)
{
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_get_top_of_stack)
{
	TStack<int> st(5);
	st.Push(1);

	EXPECT_EQ(1, st.GetTopElement());
}

TEST(TStack, throw_when_get_top_from_empty_stack)
{
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.GetTopElement());
}

TEST(TVector, can_check_Isempty)
{
	TStack<int> st(3);
	EXPECT_EQ(true, st.IsEmpty());
	st.Push(1);
	EXPECT_EQ(false, st.IsEmpty());
}


TEST(TVector, can_check_Isfull)
{
	TStack<int> st(2);
	st.Push(1);
	EXPECT_EQ(false, st.IsFull());
	st.Push(2);
	EXPECT_EQ(true, st.IsFull());
}
