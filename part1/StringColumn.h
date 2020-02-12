#pragma once

#include "column.h"

/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * value.
 */
class StringColumn : public Column {
 public:
  StringColumn() {

  }

  StringColumn(int n, ...) {

  }

  StringColumn* as_string() {

  }

  /** Returns the string at idx; undefined on invalid idx.*/
  String* get(size_t idx) {
    return new String("");
  }

  /** Out of bound idx is undefined. */
  void set(size_t idx, String* val) {

  }

  size_t size() {
    return 0;
  }
  
};