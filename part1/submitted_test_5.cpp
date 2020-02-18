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



/**
 * Test constructing dataframe, schema and row
 */ 
void test_others() {
  Schema s_empty;
  GT_EQUALS(s_empty.width(), 0);
  GT_EQUALS(s_empty.length(), 0);
  Schema s("BIFSSFIB");
  GT_EQUALS(s.width(), 8);
  GT_EQUALS(s.length(), 0);

  DataFrame d(s);
  GT_TRUE(d.get_schema().equals(&s));
  GT_EQUALS(d.ncols(), 8);  
  exit(0);
}

TEST(a4, t5_1){ ASSERT_EXIT_ZERO(test_others); }


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    test_others();
    return RUN_ALL_TESTS();
}
