#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


/***
 * This Test file grabs an exmaple dataframe from `test_examples.h` that looks like...
 * 
 *            | Population (int) | Tax rate (f) | Football team (s) | East Coast (b)
 * ---------- | --------------------------------------------------------------------
 * Chicago    | 2700000          | .0625        | Null              | False
 * New York   | 8600000          | .0400        | Patriots          | False
 * Boston     | 0685000          | .0625        | Giants            | True
 * San Fran   | 0884000          | .0850        | 49ers             | True
 * 
 * 
 * Main things this submitted test will test for:
 * 1. Dataframe with all column types
 * 2. Copying a dataframe
 * 
 * 
 * 
 */ 



/**
 * This test will check to make sure that if we mutate the scheme of an empty
 * dataframe that we can then append to it.
 * 
 */ 
void test1() {
  Schema s;
  DataFrame df(s);
  String cities("Cities");
  String countries("Countries");
  String tr("Tax rate");
  String br("Birth rate");
  GT_EQUALS(df.get_col(cities), -1);
  GT_EQUALS(df.get_row(countries), -1);


  exit(0);
}

TEST(a4, t1){ ASSERT_EXIT_ZERO(test1); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
