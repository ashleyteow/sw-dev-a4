#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

/**
 * This test will look at Contructing objects and 
 * make sure all the constructors work properly
 */ 


/** Constructing Columns
 * These tests below will look at building all 
 * different column types
 */ 
void test_columns_empty() {
  IntColumn i;
  GT_EQUALS(i.size(), 0);
  StringColumn s;
  GT_EQUALS(s.size(), 0);
  FloatColumn f;
  GT_EQUALS(f.size(), 0);
  BoolColumn b;
  GT_EQUALS(b.size(), 0);
  exit(0);
}


TEST(a4, t1_1){ ASSERT_EXIT_ZERO(test_columns_empty); }



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
