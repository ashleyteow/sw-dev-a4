#include "object.h"
#include "string.h"

/*************************************************************************
 * Schema::
 * A schema is a description of the contents of a data frame, the schema
 * knows the number of columns and number of rows, the type of each column,
 * optionally columns and rows can be named by strings.
 * The valid types are represented by the chars 'S', 'B', 'I' and 'F'.
 */
class Schema : public Object {
 public:
 
  /** Copying constructor */
  Schema(Schema& from) {

  }
 
  /** Create an empty schema **/
  Schema() {

  }
 
  /** Create a schema from a string of types. A string that contains
    * characters other than those identifying the four type results in
    * undefined behavior. The argument is external, a nullptr argument is
    * undefined. **/
  Schema(const char* types) {

  }
 
  /** Add a column of the given type and name (can be nullptr), name
    * is external. Names are expectd to be unique, duplicates result
    * in undefined behavior. */
  void add_column(char typ, String* name) {

  }
 
  /** Add a row with a name (possibly nullptr), name is external.  Names are
   *  expectd to be unique, duplicates result in undefined behavior. */
  void add_row(String* name) {

  }
 
  /** Return name of row at idx; nullptr indicates no name. An idx >= width
    * is undefined. */
  String* row_name(size_t idx) {
    return new String("");
  }
 
  /** Return name of column at idx; nullptr indicates no name given.
    *  An idx >= width is undefined.*/
  String* col_name(size_t idx) {
    return new String("");
  }
 
  /** Return type of column at idx. An idx >= width is undefined. */
  char col_type(size_t idx) {
    return 'c';
  }
 
  /** Given a column name return its index, or -1. */
  int col_idx(const char* name) {
    return 0;
  }
 
  /** Given a row name return its index, or -1. */
  int row_idx(const char* name) {
    return 0;
  }
 
  /** The number of columns */
  size_t width() {
    return 0;
  }
 
  /** The number of rows */
  size_t length() {
    return 0;
  }
};