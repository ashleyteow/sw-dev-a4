#pragma once
#include "object.h"
#include "Schema.h"
#include "Fielder.h"
#include "primitive_types_cwc.h"

/*************************************************************************
 * Row::
 *
 * This class represents a single row of data constructed according to a
 * dataframe's schema. The purpose of this class is to make it easier to add
 * read/write complete rows. Internally a dataframe hold data in columns.
 * Rows have pointer equality.
 */
class Row : public Object {
 public:
  Schema* scm;
  Array* items;
  int index;
  /** Build a row following a schema. */
  Row(Schema& scm) {
    this->index = -1;
    this->scm = new Schema(scm);
    this->items = new Array();
    for (int i = 0; i < this->scm->width(); i++) {
      this->items->push(new Object());
    }
  }

  ~Row() {
    for (int i = 0; i < this->items->length(); i++) {
      delete this->items->get(i);
    }
    delete this->scm;
    delete this->items;
  }

 
  /** Setters: set the given column with the given value. Setting a column with
    * a value of the wrong type is undefined. */
  void set(size_t col, int val) {
    delete this->items->get(col);
    this->items->set(new IntCWC(val), col);
  }

  void set(size_t col, float val) {    
    delete this->items->get(col);
    this->items->set(new FloatCWC(val), col);
  }

  void set(size_t col, bool val) {
    delete this->items->get(col);
    this->items->set(new BoolCWC(val), col);
  }

  /** Acquire ownership of the string. */
  void set(size_t col, String* val) {
    this->items->set(val, col);
  }

 
  /** Set/get the index of this row (ie. its position in the dataframe. This is
   *  only used for informational purposes, unused otherwise */
  void set_idx(size_t idx) {
    this->index = idx;
  }

  size_t get_idx() {
    return this->index;
  }

 
  /** Getters: get the value at the given column. If the column is not
    * of the requested type, the result is undefined. */
  int get_int(size_t col) {
      return dynamic_cast<IntCWC*>(this->items->get(col))->i;
  }

  bool get_bool(size_t col) {
      return dynamic_cast<BoolCWC*>(this->items->get(col))->b;
  }

  float get_float(size_t col) {
      return dynamic_cast<FloatCWC*>(this->items->get(col))->f;
  }

  String* get_string(size_t col) {
      return dynamic_cast<String*>(this->items->get(col));
  }

 
  /** Number of fields in the row. */
  size_t width() {
      return this->scm->width();
  }
 
   /** Type of the field at the given position. An idx >= width is  undefined. */
  char col_type(size_t idx) {
    return this->scm->col_type(idx);
  }
 
  /** Given a Fielder, visit every field of this row. The first argument is
    * index of the row in the dataframe.
    * Calling this method before the row's fields have been set is undefined. */
  void visit(size_t idx, Fielder& f) {
    f.start(idx);
    for(int i = 0; i < this->width(); i++) {
      switch (this->col_type(i)) {
        case 'I':
          f.accept(this->get_int(i));
          break;
        case 'F':
          f.accept(this->get_float(i));
          break;
        case 'B':
          f.accept(this->get_bool(i));
          break;
        case 'S':
          f.accept(this->get_string(i));
          break;
        default:
          break;
      } 
    }
    f.done();
  }
 
};