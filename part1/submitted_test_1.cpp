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


void test_columns_items() {
  IntColumn i(4, 1, 2, 3, 4);
  GT_EQUALS(i.size(), 5);
  GT_EQUALS(i.get(0), 0);
  GT_EQUALS(i.get(3), 3);

  String* s1 = new String("Hi");
  String* s2 = new String("world! ");
  String* s3 = new String("I");
  String* s4 = new String("am");
  String* s5 = new String("a");
  String* s6 = new String("StringColumn");
  StringColumn s(6, s1, s2, s3, s4, s5, s6);
  GT_TRUE(s.get(0)->equals(s1));
  GT_EQUALS(s.size(), 6);
  FloatColumn f(1.2, 63.34, 8.0, 1.111, 0.00);
  GT_TRUE(f.get(0) == 1.2);
  GT_EQUALS(s.size(), 6);
  
  GT_EQUALS(f.size(), 0);
  BoolColumn b(4, false, true, true, false);
  GT_EQUALS(b.get(0), false);
  GT_EQUALS(b.size(), 4);
  exit(0);
}

/**
 * Test constructing dataframe, schema and row
 */ 
void test_others() {
  Schema s_empty;
  GT_EQUALS(s_empty.width(), 0);
  GT_EQUALS(s_empty.length(), 0);
  Schema s("BIFSSFIB");
  GT_EQUALS(s_empty.width(), 8);
  GT_EQUALS(s_empty.length(), 0);

  DataFrame d(s);
  GT_TRUE(d.get_schema().equals(&s));
  GT_EQUALS(d.ncols(), 8);  
  exit(0);
}


TEST(a4, t1){ ASSERT_EXIT_ZERO(test_columns_empty); }

TEST(a4, t2){ ASSERT_EXIT_ZERO(test_columns_items); }

TEST(a4, t3){ ASSERT_EXIT_ZERO(test_others); }


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
