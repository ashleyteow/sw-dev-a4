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
    this->type = 'S';
    this->col_data = new Array();

  }

  /**
   * ... is a list of string pointers
   */ 
  StringColumn(int n, ...) {
    this->col_data = new Array();

    this->type = 'S';
    va_list vl;
    va_start(vl,n);
    for (int i=0;i<n;i++)
    {
      String* read_vl = va_arg(vl, String*);
      String* s;
      if (read_vl == nullptr) {
        s = new String("");
      }
      else {
        s = new String(read_vl->c_str());
      }
      // printf("%s\n", s->c_str());
      col_data->push(s);

      // printf("pushed");
    }
    va_end(vl);
  }

  StringColumn* as_string() {
    return this;
  }

  /** Returns the string at idx; undefined on invalid idx.*/
  String* get(size_t idx) {
    return dynamic_cast<String*>(this->col_data->get(idx));
  }

  /** Out of bound idx is undefined. */
  void set(size_t idx, String* val) {
    delete dynamic_cast<String*>(this->col_data->get(idx));
    col_data->set(val, idx);
  }

  size_t size() {
    return this->col_data->length();
  }

  virtual void push_back(String* val) {
    this->col_data->push(new String(val->c_str()));
  }
  
};