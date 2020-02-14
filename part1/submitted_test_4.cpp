#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

  /***
 * 
 *               | Grades (int) | Letter Grade (s) |       Major (s)    | Pass/Fail (b)
 * ----------    | --------------------------------------------------------------------
 * James Corden  |      97      |         A        | Computer Science       |    False
 * Marty Jane    |      85      |         B        | Computer Engineering   |    False
 * Bobbi Brown   |      92      |         A        | Biology                |    False
 * Justin Torre  |      70      |         C        | Health Science         |    False
 * Amanda Bynes  |      40      |         F        | Computer Science       |    False
 * 
 */ 


// adding data via rows
void testExample1() {
  IntColumn * grades = new IntColumn();
  StringColumn * letter_grades = new StringColumn();
  StringColumn * major = new StringColumn();
  BoolColumn * pass_fail = new BoolColumn();

  Schema * ex_schema = new Schema("ISSB");
  Row * r1 = new Row(e*x_schema);
  r1->set(0, 97);



  // FloatColumn tax_rate(4, 0.0625, 0.0400, 0.0625, 0.0850);
  // BoolColumn east_coast(4, false, false, true, true);
  // String * team1 = new String("Null");
  // String * team2 = new String("Patriots");
  // String * team3 = new String("Giants");
  // String * team4 = new String("49ers");
  // StringColumn football_team(4, team1, team2, team3, team4);

  // Schema * example_schema = new Schema("IFSB");
  // DataFrame * example_df = new DataFrame(*example_schema);
  // GT_TRUE(example_df->get_schema().equals(new Schema("IFSB")));

  // example_df->add_column(&population, new String("Population"));
  // example_df->add_column(&tax_rate, new String("Tax Rate"));
  // example_df->add_column(&football_team, new String("Football Team"));
  // example_df->add_column(&east_coast, new String("East Coast"));
  // GT_TRUE(example_df->ncols == 4);
  // GT_TRUE(example_df->nrows == 4);

  exit(0);
}
TEST(a4, t1){ ASSERT_EXIT_ZERO(testExample1); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
