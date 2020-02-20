#pragma once
#include "object.h"
#include "string.h"
#include "array.h"


/*************************************************************************
 * Schema::
 * A schema is a description of the contents of a data frame, the schema
 * knows the number of columns and number of rows, the type of each column,
 * optionally columns and rows can be named by strings.
 * The valid types are represented by the chars 'S', 'B', 'I' and 'F'.
 */
class Schema : public Object {
 public:
  Array* header_strings;
  Array* row_strings;
  char* types;


  /** Copying constructor */
  Schema(Schema& from) {
    header_strings = new Array();
    row_strings = new Array();
    this->types = strdup(from.types);
    for (int i = 0; i < strlen(types); i++) {
      header_strings->push(new String(from.header_strings->get(i)->c_str()));
    }
    for (int i = 0; i < from.length(); i++) {
      row_strings->push(new String(from.row_strings->get(i)->c_str()));
    }


  }
 
  /** Create an empty schema **/
  Schema() {
    header_strings = new Array();
    row_strings = new Array();

  }

    /** Create an empty schema **/
  ~Schema() {
    for (int i = 0; i < this->width(); i++) {
      delete header_strings->get(i);
    }
    for (int i = 0; i < this->length(); i++) {
      delete row_strings->get(i);
    }
    delete header_strings;
    delete row_strings;
  }
 
  /** Create a schema from a string of types. A string that contains
    * characters other than those identifying the four type results in
    * undefined behavior. The argument is external, a nullptr argument is
    * undefined. **/
  Schema(const char* types) {
    this->types = strdup(types);
    header_strings = new Array();
    row_strings = new Array();
    for (int i = 0; i < strlen(types); i++) {
      header_strings->push(new String(""));
    }
    
  }
 
  /** Add a column of the given type and name (can be nullptr), name
    * is external. Names are expectd to be unique, duplicates result
    * in undefined behavior. */
  void add_column(char typ, String* name) {
    strncat(this->types, &typ, 1);
    this->header_strings->push(name);
  }
 
  /** Add a row with a name (possibly nullptr), name is external.  Names are
   *  expectd to be unique, duplicates result in undefined behavior. */
  void add_row(String* name) {
    this->row_strings->push(name);

  }
 
  /** Return name of row at idx; nullptr indicates no name. An idx >= width
    * is undefined. */
  String* row_name(size_t idx) {
    if (this->row_strings->get(idx) == nullptr) {
      return new String("");
    } else {
      return dynamic_cast<String*>(this->row_strings->get(idx));
    }
  }
 
  /** Return name of column at idx; nullptr indicates no name given.
    *  An idx >= width is undefined.*/
  String* col_name(size_t idx) {
    if (this->header_strings->get(idx) == nullptr) {
      return new String("");
    } else {
      return dynamic_cast<String*>(this->header_strings->get(idx));
    }
  }
 
  /** Return type of column at idx. An idx >= width is undefined. */
  char col_type(size_t idx) {
    return types[idx];
  }
 
  /** Given a column name return its index, or -1. */
  int col_idx(const char* name) {
    for (int i = 0; i < this->width(); i++) {
      if (strcmp(this->header_strings->c_str(), name) == 0) {
        return i;
      }
    }
    return -1;
  }
 
  /** Given a row name return its index, or -1. */
  int row_idx(const char* name) {
    for (int i = 0; i < this->width(); i++) {
      if (strcmp(this->row_strings->c_str(), name) == 0) {
        return i;
      }
    }
    return -1;
  }
 
  /** The number of columns */
  size_t width() {
    return this->header_strings->length();
  }
 
  /** The number of rows */
  size_t length() {
    return this->row_strings->length();
  }
};