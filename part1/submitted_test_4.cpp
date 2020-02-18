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
 * Similar to test1, this test will map the Add2 rower to each row 
 * in a df and check to see if it worked
 */ 
void test_map() {
  Schema s("IIII");
  DataFrame d(s);
  Row r(s);
  
  r.set(0, 1);
  r.set(1, 3);
  r.set(2, 6543);
  r.set(3, 300);
  d.add_row(r);
    Add2_Rower add2;
  d.map(add2);
  GT_EQUALS(d.get_int(0, 0), 3);
  GT_EQUALS(d.get_int(1, 0), 5);
  GT_EQUALS(d.get_int(3, 0), 302);
  exit(0);
}

TEST(a4, t4_1){ ASSERT_EXIT_ZERO(test_map); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
