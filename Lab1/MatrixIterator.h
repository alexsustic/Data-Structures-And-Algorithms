#pragma once
#include "Matrix.h"
class MatrixIterator {

	friend class Matrix;
private:
	const Matrix& matrix;
	MatrixIterator(const Matrix& m);
	int current_line;
	int current_column;
public:
	// get to the next line
	void next();
	// return all the non-NULL element from each line of the matrix through several iterations
	TElem iterator();

};
