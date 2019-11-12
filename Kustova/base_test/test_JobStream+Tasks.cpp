#include "JobStream.h"
#include "JobStream.cpp"
#include "Tasks.h"
#include "Tasks.cpp"
#include <gtest.h>

TEST(TJobStream, can_create_object)
{
	ASSERT_NO_THROW(TJobStream p(10));
}

TEST(TJobStream, can_get_new_job)
{
	TJobStream pf(10);
	ASSERT_NO_THROW(pf.GetNewJob(50));
}

TEST(Tasks, can_create_object)
{
	ASSERT_NO_THROW(Tasks p());
}

TEST(Tasks, can_initializing_object)
{
	Tasks p;
	ASSERT_NO_THROW(p.Initializing(0.886, 5, 5));
}
TEST(Tasks, throw_when_cores_negative)
{
	Tasks p;
	ASSERT_ANY_THROW(p.Initializing(0.886, -5, 5));
}
TEST(Tasks, throw_when_tacts_negative)
{
	Tasks p;
	ASSERT_ANY_THROW(p.Initializing(0.886, 5, -5));
}
