#include "queue.h"
#include <gtest.h>

TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> st(5));
}

TEST(TQueue, cant_create_too_large_queue)
{
	ASSERT_ANY_THROW(TQueue<int> st(MaxQueueSize + 1));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(TQueue<int> st(-3));
}

TEST(TQueue, can_push_to_queue)
{
	TQueue<int> st(10);
	ASSERT_NO_THROW(st.Push(10));
}

TEST(TQueue, throw_when_push_to_full_queue)
{
	TQueue<int> st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);
	ASSERT_ANY_THROW(st.Push(4));
}

TEST(TQueue, can_get_from_queue)
{
	TQueue<int> st(5);
	st.Push(4);
	ASSERT_NO_THROW(st.Get());
}

TEST(TQueue, throw_when_get_from_empty_queue)
{
	TQueue<int> st(5);
	ASSERT_ANY_THROW(st.Get());
}

TEST(TQueue, can_get_first_of_queue)
{
	TQueue<int> st(5);
	st.Push(1);
	st.Push(2);
	EXPECT_EQ(1, st.GetFirst());
}

TEST(TQueue, throw_when_get_first_from_empty_queue)
{
	TQueue<int> st(5);
	ASSERT_ANY_THROW(st.GetFirst());
}

TEST(TQueue, can_check_Isempty)
{
	TQueue<int> st(3);
	EXPECT_EQ(true, st.IsEmpty());
	st.Push(1);
	EXPECT_EQ(false, st.IsEmpty());
}


TEST(TQueue, can_check_Isfull)
{
	TQueue<int> st(2);
	st.Push(1);
	EXPECT_EQ(false, st.IsFull());
	st.Push(2);
	EXPECT_EQ(true, st.IsFull());
}

TEST(TQueue, can_get_notion_by_index)
{
	TQueue<int> st(5);
	st.Push(1);
	st.Push(2);
	EXPECT_EQ(1, st.Get_notion_by_index(0));
}

TEST(TQueue, throw_when_get_notion_by_index_from_empty_queue)
{
	TQueue<int> st(5);
	ASSERT_ANY_THROW(st.Get_notion_by_index(1));
}