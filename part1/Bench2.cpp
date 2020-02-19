#include <stdio.h>
#include "dataframe.h"
#include "string.h"
#include "Rower.h"


const char* DATA_FILE = "datafile.txt";

// rounds floats to the nearest whole number
// changes birthyear to age 
// adds 1 to each char for string columns
class ComplicatedTaskRower : public Rower {
  public:
  //accept method for the rower object
  virtual bool accept(Row& r) {
    for(int i = 0; i < r.width(); i++) {
      switch (r.col_type(i)) {
        case 'I': {
          // if column is birthyear, set its value to be the user's age
          if (i == 13) {
            r.set(i, 2020 - r.get_int(i));
          }
          if (i == 0) {
            r.set(i, r.get_int(i) / 60);
          }
          break;
        }
        case 'F': {
          // we round floats to the nearest whole number
          int floor = static_cast<int>(r.get_float(i));
          r.set(i, r.get_float(i) - static_cast<float>(floor) >= 0.5 ? floor + 1 : floor);
          break;
        }
        case 'S': {
          for (int col = 0; col < r.get_string(i)->size(); col++) {
            r.get_string(i)->cstr_[col] += 1;
          }
        break;
        }
        default:
          break;
      }      
    }
  }
};

// rounds the lat long's in the dataset to the nearest whole number
class SimpleTaskRower : public Rower {
  public:
  //accept method for the rower object
  virtual bool accept(Row& r) {
    for(int i = 0; i < r.width(); i++) {
      switch (r.col_type(i)) {
        case 'F': {
          // we round floats to the nearest whole number
          int floor = static_cast<int>(r.get_float(i));
          r.set(i, r.get_float(i) - static_cast<float>(floor) >= 0.5 ? floor + 1 : floor);
          break;
        }
        default:
          break;
      }      
    }
  }
};

/**
 * Generates a data frame based on a header_line in csv format and a column schema
 */ 
DataFrame* create_data_frame(char* header_line, char* col_schema) {
    Schema s("");
    DataFrame* df = new DataFrame(s);

    char *token;
    int col = 0;
    /* get the first token */
    token = strtok(header_line, ",");
    
    /* walk through other tokens */
    while( token != NULL ) {
        char curr_t = col_schema[col];
        if (curr_t == 'I') {
            df->add_column(new IntColumn(), new String(token));
        } else if (curr_t == 'B') {
            df->add_column(new BoolColumn(), new String(token));
        } else if (curr_t == 'F') {
            df->add_column(new FloatColumn(), new String(token));
        } else if (curr_t == 'S') {
            df->add_column(new StringColumn(), new String(token));
        }
        token = strtok(NULL, ",");
        col++;
    }


}

/**
 * reads in a CSV based on a column schema and generates a 
 * DataFrame object from it.
 * 
 * User will need to delete the DataFrame after it is returned.
 */ 
DataFrame* read_in_csv(char* file, char* col_schema) {
    FILE *fp;
    debug_printf("file = %s\n",file);
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Wrong file");
        return NULL;
    }
    size_t len;
    char* line;
    // debug_printf(" = \n",line);

    getline(&line, &len, fp);
        debug_printf("data = %s\n",line);

    // DataFrame* df = create_data_frame(line, col_schema);

    // while (line != NULL) {
    //     Row temp_row(df->get_schema());
    //     char* token = strtok(line, ",");
    //     int i= 0;
    //     while( token != NULL ) {
    //         if (col_schema[i] == 'I') {
    //             temp_row.set(i, atoi(token));
    //         } else if (col_schema[i] == 'F') {
    //             temp_row.set(i, static_cast<float>(atof(token)));
    //         } else if (col_schema[i] == 'S') {
    //             temp_row.set(i, new String(token));
    //         } else if (col_schema[i] == 'B') {
    //             temp_row.set(i, atoi(token) > 0);
    //         }
    //         token = strtok(NULL, ",");
    //         i++;
    //     }
    // }
    // fclose(fp);
    // free(line);

}


int main () {
    read_in_csv("datafile.txt", "ISSISFFISFFISII");
    return 0;
}