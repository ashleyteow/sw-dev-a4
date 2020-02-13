#pragma once

#include "column.h"
#include "string.h"

/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * value.
 */
class StringColumn : public Column {
 public:
  StringColumn() {

  }

  /**
   * ... is a list of string pointers
   */ 
  StringColumn(int n, ...) {
    va_list vl;
    va_start(vl,n);
    String* largest=va_arg(vl, String*);

    for (int i=1;i<n;i++)
    {
      String* val=va_arg(vl,String*);
      largest=(largest>val)?largest:val;
    }
    va_end(vl);
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