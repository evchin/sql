#include "gtest/gtest.h"
#include "../../includes/sql/sql.h"

bool test_sample(bool debug = false)
{
  SQL sql;
  sql.batch("sample.txt");
  return true;
}

TEST(TEST_SQL, TestSample) {
  EXPECT_EQ(1, test_sample(false));
}

bool test_final21(bool debug = false)
{
  SQL sql;
  sql.batch("final21.txt");
  return true;
}

TEST(TEST_SQL, TestFinal21) {
  EXPECT_EQ(1, test_final21(false));
}

bool test_final19(bool debug = false)
{
  SQL sql;
  sql.batch("final19.txt");
  return true;
}

TEST(TEST_SQL, TestFinal19) {
  EXPECT_EQ(1, test_final19(false));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

