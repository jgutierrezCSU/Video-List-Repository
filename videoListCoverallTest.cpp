/**
  Unit Tests for Video List Repository
**/

#include <gtest/gtest.h>
#include "video.h"
#include "vlist.h"
 
class VideoListTest : public ::testing::Test
{
	protected:
		VideoListTest(){} //constructor runs before each test
		virtual ~videoListTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};
