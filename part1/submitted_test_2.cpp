#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


/***
 * These tests will test the Rower Visitor.
 */ 

/**
 * Adds 2 to to all the items in a Row
 */ 
class Add2_Rower : public Rower {
  public:
  //accept method for the rower object
  virtual bool accept(Row& r) {
    for(int i = 0; i < r.width(); i++) {
      switch (r.col_type(i)) {
        case 'I':
          r.set(i, (r.get_int(i) + 2));
          break;
        case 'F':
          r.set(i, static_cast<float>(r.get_float(i) + 2.0));
          break;
        default:
          break;
      }      
    }
  }
};

/**
 * Test visiting an entire row, and 
 * mapping Add2 to every item in the row
 */ 
void test1() {
  Schema s("IFII");
  Add2_Rower add2;

  Row r(s);
  r.set(0, 1);
  r.set(1, 3.141f);
  r.set(2, 6543);
  r.set(3, 300);
  add2.accept(r);
  r.get_int(0);
  GT_EQUALS(r.get_int(0), 2);
  GT_EQUALS(r.get_float(1), 5.141f);
  GT_EQUALS(r.get_int(3), 300);
  exit(0);
}

/**
 * Similar to test1, this test will map the Add2 rower to each row 
 * in a df and check to see if it worked
 */ 
void test_map() {
  Schema s("IFII");
  DataFrame d(s);
  Row r(s);
  d.add_row(r);
  d.set(0, 0, 1);
  d.set(1, 0, 3.141f);
  d.set(2, 0, 6543);
  d.set(3, 0, 300);
    Add2_Rower add2;
  d.map(add2);
  GT_EQUALS(d.get_int(0, 0), 2);
  GT_EQUALS(d.get_float(1, 0), 5.141f);
  GT_EQUALS(d.get_int(3, 0), 300);
  exit(0);
}

TEST(a4, t1){ ASSERT_EXIT_ZERO(test1); }
TEST(a4, t2){ ASSERT_EXIT_ZERO(test_map); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
