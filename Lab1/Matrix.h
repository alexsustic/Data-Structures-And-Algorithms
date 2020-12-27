#pragma once
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	int number_of_columns;
	int number_of_rows;
	int extra_space = 10;
	int lenght;
	int* row_index;
	int* column_index;
	TElem* values;

public:
	//allocates more space if needed (lenght=extra_space)
	void resize();

	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//destructor
	~Matrix();
};
