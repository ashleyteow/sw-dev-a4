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
 * reads in a CSV based on a column schema and generates a 
 * DataFrame object from it.
 * 
 * User will need to delete the DataFrame after it is returned.
 */ 
DataFrame* read_in_csv(char* file, char* col_schema) {
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Wrong file");
        return NULL;
    }
    size_t len;
    char* line;
    getline(&line, &len, fp);
    char *token;
    
    /* get the first token */
    token = strtok(line, ",");
    
    /* walk through other tokens */
    while( token != NULL ) {
        printf( " %s\n", token );
        token = strtok(NULL, ",");
    }


    // fscanf(fp, "%s", ret);
    // printf(ret);

    // fprintf(fp, "This is testing for fprintf...\n");
    // fputs("This is testing for fputs...\n", fp);
    fclose(fp);
    return 0;

}


int main () {
    read_in_csv("datafile.txt", "ISSISFFISFFISII");
}