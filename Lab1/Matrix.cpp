#include "Matrix.h"
#include <stdio.h>
#include <iostream>
#include <exception>
using namespace std;

void Matrix::resize() {
	///everytime time the lenght of the matrix will get equal with the current extra space
	///then the current extra space will extend with 10
	this->extra_space += 10;

	///the column_index will also extend with 10 in lenght
	int* new_column_index = new int[this->extra_space];
	for (int index = 0; index < this->lenght; index++)
		new_column_index[index] = this->column_index[index];
	delete[] this->column_index;
	this->column_index = new_column_index;

	/// and the values will also extend with 10 in lenght
	TElem* new_values = new TElem[this->extra_space];
	for (int index = 0; index < this->lenght; index++)
		new_values[index] = this->values[index];
	delete[] this->values;
	this->values = new_values;
}




Matrix::Matrix(int nrLines, int nrCols) {

	this->number_of_columns = nrCols;
	this->number_of_rows = nrLines;
	this->lenght = 0;
	this->extra_space = 10;

	///we allocate space for the row_index, column_index and values
	///we initialize the row_index with 0

	this->row_index = new int[number_of_rows + 1];
	for (int index = 0; index <= number_of_rows; index++)
		this->row_index[index] = 0;
	this->column_index = new int[this->extra_space];
	this->values = new TElem[this->extra_space];
}


int Matrix::nrLines() const {
	return this->number_of_rows;
}


int Matrix::nrColumns() const {
	return this->number_of_columns;
}


TElem Matrix::element(int i, int j) const {
	///we check if the position is valid
	if (i < 0 || i >= this->number_of_rows || j < 0 || j >= this->number_of_columns)
		throw runtime_error("Invalid position!");
	///we check if we have non-zero elements in the matrix
	if (this->lenght == 0)
		return NULL_TELEM;
	/// from where the elements from the first row starts to where the first row ends, we check if 
	/// there is an element equal with the column of the searched element and return its value
	for (int index = row_index[i]; index < row_index[i + 1]; index++)
		if (this->column_index[index] == j)
			return this->values[index];
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {

	///We first check if the position is valid
	///Then we check in which of this 4 cases we are:
 ///   1)current value = 0 and new value = 0  => do nothing
 ///   2)current value = 0 and new value =! 0  => insert in the data structure
 ///   3)current value =! 0 and new value = 0  => remove from the data structure
 ///   4)current value =! 0 and new value =! 0  => just change the value in the data structure


	if (i < 0 || i >= this->number_of_rows || j<0 || j>this->number_of_columns)
		throw runtime_error("Invalid position!");
	else
	{

		TElem current_value = element(i, j);

		if (current_value == NULL_TELEM && e == NULL_TELEM)
		{
			///first case
			return NULL_TELEM;
		}
		else if (current_value == NULL_TELEM && e != NULL_TELEM)
		{
			///second case
			if (this->lenght == this->extra_space)
				resize();
			int position = row_index[i + 1];
			for (int index = this->lenght; index > position; index--)
			{
				column_index[index] = column_index[index-1];
				values[index] = values[index-1];
			}
			column_index[position] = j;
			values[position] = e;
			for (int index = i + 1; index <= this->number_of_rows; index++)
				this->row_index[index] += 1;
			this->lenght += 1;
			return current_value;

		}
		else if (current_value != NULL_TELEM && e == NULL_TELEM)
		{
			///third case
			int element_column_position;
			for (int index = row_index[i]; index < row_index[i + 1]; index++)
				if (column_index[index] == j)
				{
					element_column_position = index;
					break;
				}

			for (int index = element_column_position; index < this->lenght; index++)
			{
				column_index[index] = column_index[index + 1];
				values[index] = values[index + 1];
			}
			for (int index = i + 1; index <= this->number_of_rows; index++)
				this->row_index[index] -= 1;
			this->lenght-=1;
			return current_value;

		}
		else if (current_value != NULL_TELEM && e != NULL_TELEM)
		{
			///fourth case
			int element_column_position;
			for (int index = row_index[i]; index < row_index[i + 1]; index++)
				if (column_index[index] == j)
				{
					element_column_position = index;
					break;
				}
			values[element_column_position] = e;
			return current_value;
		}
	}
	return NULL_TELEM;
}


Matrix::~Matrix() {
	/// destructor
	delete[] this->row_index;
	delete[] this->column_index;
	delete[] this->values;
}
