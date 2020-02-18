#pragma once
#include "column.h"
#include "Schema.h"
#include "Rower.h"
#include "array.h"
#include "object.h"
#include <thread>


/****************************************************************************
 * DataFrame::
 *
 * A DataFrame is table composed of columns of equal length. Each column
 * holds values of the same type (I, S, B, F). A dataframe has a schema that
 * describes it.
 */
class DataFrame : public Object {
 public:
  Schema* schema;
  Array* arr_col;
 
  /** Create a data frame with the same columns as the given df but with no rows or rownmaes */
  DataFrame(DataFrame& df) {
    schema = new Schema(df.get_schema());
    arr_col = new Array();
    for(int i = 0; i < df.nrows(); i++) {

      Row* temp_row = new Row(*this->schema);
      // Build temp_row based on our arr_col
      for(int row_i = 0; row_i < temp_row->width(); row_i++) {
        char t = temp_row->col_type(row_i);
        if (t == 'B') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(df.arr_col->get(i))->as_bool()->get(row_i));
        } else if (t == 'I') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(df.arr_col->get(i))->as_int()->get(row_i));
        } else if (t == 'F') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(df.arr_col->get(i))->as_float()->get(row_i));
        } else if (t == 'S') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(df.arr_col->get(i))->as_string()->get(row_i));
        }
      }
      this->add_row(*temp_row);
    }
  }
 
  /** Create a data frame from a schema and columns. All columns are created
    * empty. */
  DataFrame(Schema& schema) {
    this->schema = new Schema(schema);
    this->arr_col = new Array();
  }
 
  /** Returns the dataframe's schema. Modifying the schema after a dataframe
    * has been created in undefined. */
  Schema& get_schema() {
    return *this->schema;
  }
 
  /** Adds a column this dataframe, updates the schema, the new column
    * is external, and appears as the last column of the dataframe, the
    * name is optional and external. A nullptr colum is undefined. */
  void add_column(Column* col, String* name) {
    this->schema->add_column(col->get_type(), name);
    arr_col->push(col);
  }
 
  /** Return the value at the given column and row. Accessing rows or
   *  columns out of bounds, or request the wrong type is undefined.*/
  int get_int(size_t col, size_t row) {
    return dynamic_cast<Column*>(arr_col->get(col))->as_int()->get(row);
  }

  bool get_bool(size_t col, size_t row) {
    return dynamic_cast<Column*>(arr_col->get(col))->as_bool()->get(row);
  }

  float get_float(size_t col, size_t row) {
    return dynamic_cast<Column*>(arr_col->get(col))->as_float()->get(row);
  }

  String* get_string(size_t col, size_t row) {
    return dynamic_cast<Column*>(arr_col->get(col))->as_string()->get(row);
  }
 
  /** Return the offset of the given column name or -1 if no such col. */
  int get_col(String& col) {
    return schema->col_idx(col.c_str());
  }
 
  /** Return the offset of the given row name or -1 if no such row. */
  int get_row(String& col) {
      return schema->row_idx(col.c_str());
  }
 
  /** Set the value at the given column and row to the given value.
    * If the column is not  of the right type or the indices are out of
    * bound, the result is undefined. */
  void set(size_t col, size_t row, int val) {
    dynamic_cast<Column*>(arr_col->get(col))->as_int()->set(row, val);
  }

  void set(size_t col, size_t row, bool val) {
    dynamic_cast<Column*>(arr_col->get(col))->as_bool()->set(row, val);
  }

  void set(size_t col, size_t row, float val) {
    dynamic_cast<Column*>(arr_col->get(col))->as_float()->set(row, val);
  }

  void set(size_t col, size_t row, String* val) {
   dynamic_cast<Column*>(arr_col->get(col))->as_string()->set(row, val);
  }
 
  /** Set the fields of the given row object with values from the columns at
    * the given offset.  If the row is not form the same schema as the
    * dataframe, results are undefined.
    */
  void fill_row(size_t idx, Row& row) {
    for(int i = 0; this->schema->width(); i++) {
      char t = row.col_type(i);
      if (t == 'B') {
        dynamic_cast<Column*>(arr_col->get(i))->as_bool()->set(idx, row.get_bool(i));
      } else if (t == 'I') {
        dynamic_cast<Column*>(arr_col->get(i))->as_int()->set(idx, row.get_int(i));
      } else if (t == 'F') {
        dynamic_cast<Column*>(arr_col->get(i))->as_float()->set(idx, row.get_float(i));
      } else if (t == 'S') {
        dynamic_cast<Column*>(arr_col->get(i))->as_string()->set(idx, row.get_string(i));
      }
    }
  }
 
  /** Add a row at the end of this dataframe. The row is expected to have
   *  the right schema and be filled with values, otherwise undedined.  */
  void add_row(Row& row) {
    for(int i = 0; i < arr_col->length(); i++) {
      char t = row.col_type(i);
      if (t == 'B') {
        dynamic_cast<Column*>(arr_col->get(i))->push_back(row.get_bool(i));
      } else if (t == 'I') {
        dynamic_cast<Column*>(arr_col->get(i))->push_back(row.get_int(i));
      } else if (t == 'F') {
        dynamic_cast<Column*>(arr_col->get(i))->push_back(row.get_float(i));
      } else if (t == 'S') {
        dynamic_cast<Column*>(arr_col->get(i))->push_back(row.get_string(i));
      }
    }
    schema->add_row(new String(""));
  }
 
  /** The number of rows in the dataframe. */
  size_t nrows() {
    return this->schema->length();
  }
 
  /** The number of columns in the dataframe.*/
  size_t ncols() {
    return this->schema->width();
  }
 
  /** Visit rows in order */
  void pmap(Rower& r) {
    std::thread* threads[this->nrows()];
    Row* temp_rows[this->nrows()];

    for (int row = 0; row < this->nrows(); row++) {
      Row* temp_row = new Row(*this->schema);
      temp_rows[row] = temp_row;

      // Build temp_row based on our arr_col
      for(int row_i = 0; row_i < temp_row->width(); row_i++) {
        char t = temp_row->col_type(row_i);
        if (t == 'B') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_bool()->get(row_i));
        } else if (t == 'I') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_int()->get(row_i));
        } else if (t == 'F') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_float()->get(row_i));
        } else if (t == 'S') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_string()->get(row_i));
        }
      }
      std::thread* temp_thread = new std::thread([&r, temp_row] { (&r)->accept(*temp_row); });
      threads[row] = temp_thread;
      
      delete temp_row;
    }
    for(int i = 0; i < this->nrows(); i++) {
      threads[i]->join();
      this->fill_row(i, *temp_rows[i]);
    }
    
  }
 
  /** Create a new dataframe, constructed from rows for which the given Rower
    * returned true from its accept method. */
  DataFrame* filter(Rower& r) {
    DataFrame* copy = new DataFrame(*this->schema);
    for (int row = 0; row < this->nrows(); row++) {
      Row* temp_row = new Row(*this->schema);
      // Build temp_row based on our arr_col
      for(int row_i = 0; row_i < temp_row->width(); row_i++) {
        char t = temp_row->col_type(row_i);
        if (t == 'B') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_bool()->get(row_i));
        } else if (t == 'I') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_int()->get(row_i));
        } else if (t == 'F') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_float()->get(row_i));
        } else if (t == 'S') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_string()->get(row_i));
        }
      }
      if(r.accept(*temp_row)) {
        copy->add_row(*temp_row);
      }
    }
    return copy;
  }
 
  /** Print the dataframe in SoR format to standard output. */
  void print() {
    for(int j = 0; this->schema->length(); j++) {
      for(int i = 0; this->schema->width(); i++) {
        char t = this->schema->col_type(i);
        std::cout << '<';
        if (t == 'B') {
          std::cout << dynamic_cast<Column*>(arr_col->get(i))->as_bool()->get(j);
        } else if (t == 'I') {
          std::cout << dynamic_cast<Column*>(arr_col->get(i))->as_int()->get(j);
        } else if (t == 'F') {
          std::cout << dynamic_cast<Column*>(arr_col->get(i))->as_float()->get(j);
        } else if (t == 'S') {
          std::cout << '"' << dynamic_cast<Column*>(arr_col->get(i))->as_string()->get(j) << '"';
        }
        std::cout << '>';
      }
      std::cout << std::endl;
    }
  }
};