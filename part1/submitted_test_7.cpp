#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

/**
 * Example
 * 
 *                        | Author (string)    | Price_usd (int) 
 * ---------------------- | -------------------------------------
 * Brave New World        | Aldous Huxley      | 12              
 * Tale of Two Cities     | Charles Dickons    | 10              
 * Linear Algebra V10     | N/A                | 55              
 * How To Design Programs | Matthias Felleisen | 95      
 * 
 */    



void testExample1() {
  String * author1 = new String("Aldous Huxley");
  String * author2 = new String("Charles Dickons");
  String * author4 = new String("Matthias Felleisen");
  StringColumn authors(4, author1, author2, nullptr, author4);
  IntColumn price(4, 12, 10, 55, 95);

  Schema example_schema("SI");
  DataFrame * example_df = new DataFrame(example_schema);
   
  example_df->add_column(&authors, new String("Author"));
  example_df->add_column(&price, new String("Price_usd"));
  GT_TRUE(example_df->get_schema().equals(new Schema("IS")));

  GT_EQUALS(example_df->get_col(*(new String("Author"))), 0);

  exit(0);
}
TEST(a4, t7_1){ ASSERT_EXIT_ZERO(testExample1); }



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testExample1();
    return RUN_ALL_TESTS();
}
