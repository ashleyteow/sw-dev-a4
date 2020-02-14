# Part 1 ReadMe
## Introduction to our Implementation
* DataFrame
In dataframe.h, there are two class fields, one for this dataframe's schema and the other is an array that holds our various typed columns. 
We decided to use our previous array implementation from Assignment 2 to store this data.

* Column
In column.h, there are two fields as well: one to store the type of the column (represented with its char type) as well as an array to store the column data. We add to this array using the various push_back methods that all Column objects implement.


## Overview of the Design Choices 


## Use cases 
* (the "examples" step from the design recipe) of things one can do with your data frame.
You can create a dataframe in 2 ways, either by populating the column first or populating the rows. 