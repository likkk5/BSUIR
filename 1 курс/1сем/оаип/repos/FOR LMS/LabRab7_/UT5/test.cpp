#include "pch.h"
//UT5 - Task5

int Interesting(int nn);

TEST(TestInteresting, TestInteresting1) {
  EXPECT_EQ(Interesting(1), 0);
 }

TEST(TestInteresting, TestInteresting2) {
    EXPECT_EQ(Interesting(9), 1);
}

TEST(TestInteresting, TestInteresting3) {
    EXPECT_EQ(Interesting(10), 1);
}

TEST(TestInteresting, TestInteresting4) {
    EXPECT_EQ(Interesting(34), 3);
}

TEST(TestInteresting, TestInteresting5) {
    EXPECT_EQ(Interesting(880055535), 88005553);
}

TEST(TestInteresting, TestInteresting6) {
    EXPECT_EQ(Interesting(1000000000), 100000000);
}

int Interesting(int nn)
{
    return (nn + 1) / 10;
}