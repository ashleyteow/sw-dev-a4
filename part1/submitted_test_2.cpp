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
  Schema s("III");
  Add2_Rower add2;

  Row r(s);
  r.set(0, 1);
  r.set(1, 6543);
  r.set(2, 300);
  add2.accept(r);
  r.get_int(0);
  GT_EQUALS(r.get_int(0), 3);
  GT_EQUALS(r.get_int(1), 6545);
  GT_EQUALS(r.get_int(2), 302);
  exit(0);
}

TEST(a4, t2_1){ ASSERT_EXIT_ZERO(test1); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    // test1();
    return RUN_ALL_TESTS();
}
