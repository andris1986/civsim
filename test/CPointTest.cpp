#define private public
#define protected public
#include "../src/CPoint.h"
#undef private
#undef protected

#include <gtest/gtest.h>

class CPointTest : public testing::Test {

};


TEST_F(CPointTest, constructorTest) {
	CPoint p1(1.0, 2.0);
	ASSERT_EQ(1.0, p1.m_x);
	ASSERT_EQ(2.0, p1.m_y);

	CPoint p2;
	ASSERT_EQ(0.0, p2.m_x);
	ASSERT_EQ(0.0, p2.m_y);
}

