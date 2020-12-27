#include "MatrixIterator.h"
#include "Matrix.h"
using namespace std;

///initialize the current_line and current_column with 0
/// complexity if theta(1)
MatrixIterator::MatrixIterator(const Matrix& m):matrix(m)
{
	current_line = 0;
	current_column = 0;
}



///the current_line increases with 1
///complexity is theta(1)
void MatrixIterator::next() {
	this->current_line = this->current_line + 1;
}




///for each new iteration, we are returning the non-null elements from all columns of the same line
/// and then we prepare for the next iteration increasing the current_line with 1
/// complexity is theta(nr_of_columns- current_column)
TElem MatrixIterator::iterator() {
	int nr_of_columns = matrix.nrColumns();
	if (this->current_column == nr_of_columns)
		this->current_column = 0;
	for (int index = current_column; index < nr_of_columns; index++)
	{
		if (matrix.element(this->current_line, index) != NULL_TELEM)
			return matrix.element(this->current_line, index);
		this->current_column += 1;
	}
	next();

}