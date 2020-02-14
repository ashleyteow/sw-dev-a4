#include <gtest/gtest.h>
#include "dataframe.h" 
#include "string.h"

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

/***
 * 
 *            | Population (int) | Tax rate (f) | Football team (s) | East Coast (b)
 * ---------- | --------------------------------------------------------------------
 * Chicago    | 2700000          | .0625        | Null              | False
 * New York   | 8600000          | .0400        | Patriots          | False
 * Boston     | 0685000          | .0625        | Giants            | True
 * San Fran   | 0884000          | .0850        | 49ers             | True
 * 
 */ 


// adding data via columns
void testExample1() {
  IntColumn population(4, 27000000, 8600000, 350000, 20000);
  FloatColumn tax_rate(4, 0.0625, 0.0400, 0.0625, 0.0850);
  BoolColumn east_coast(4, false, false, true, true);
  String * team1 = new String("Null");
  String * team2 = new String("Patriots");
  String * team3 = new String("Giants");
  String * team4 = new String("49ers");
  StringColumn football_team(4, team1, team2, team3, team4);

  Schema * example_schema = new Schema("IFSB");
  DataFrame * example_df = new DataFrame(*example_schema);
  GT_TRUE(example_df->get_schema().equals(new Schema("IFSB")));

  example_df->add_column(&population, new String("Population"));
  example_df->add_column(&tax_rate, new String("Tax Rate"));
  example_df->add_column(&football_team, new String("Football Team"));
  example_df->add_column(&east_coast, new String("East Coast"));
<<<<<<< HEAD
  GT_TRUE(example_df->get_schema().equals(new Schema("IFSB")));
=======
  GT_TRUE(example_df->ncols == 4);
  GT_TRUE(example_df->nrows == 4);
>>>>>>> 890bebcc9ef9bbb89dbcce0622fed0b5cbce77b5

  exit(0);
}


TEST(a4, t1){ ASSERT_EXIT_ZERO(testExample1); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
