#pragma once
#include "object.h"
#include "string.h"


class BoolColumn;
class IntColumn;
class FloatColumn;
class StringColumn;
/**
 * Column ::
 * Represents one column of a data frame which holds values of a single type.
 * This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality. */
class Column : public Object {
 public:
 
  /** Type converters: Return same column under its actual type, or
   *  nullptr if of the wrong type.  */
  virtual IntColumn* as_int() {
    return 0;
  }

  virtual BoolColumn*  as_bool() {
    return 0;
  }

  virtual FloatColumn* as_float() {
    return 0;
  }

  virtual StringColumn* as_string() {
    return 0;
  }

 
  /** Type appropriate push_back methods. Calling the wrong method is
    * undefined behavior. **/
  virtual void push_back(int val) {

  }

  virtual void push_back(bool val) {

  }

  virtual void push_back(float val) {

  }

  virtual void push_back(String* val) {

  }

 
 /** Returns the number of elements in the column. */
  virtual size_t size() {
    return 0;
  }

 
  /** Return the type of this column as a char: 'S', 'B', 'I' and 'F'. */
  char get_type() {

  }

};


#include "IntColumn.h"
#include "BoolColumn.h"
#include "FloatColumn.h"
#include "StringColumn.h"