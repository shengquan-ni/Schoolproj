#ifndef MATRIX_H
#define MATRIX_H
#include "Array.h"

template<class Element>
class Matrix
{
private:
	int rows,cols;
	Array<Array<Element>*> m;
public:
	Matrix<Element>(int newRows, int newCols):rows(newRows),cols(newCols),m(rows)
	{
		for(int i=0;i<rows;++i)
			m[i]=new Array<Element>(cols);
	}

	Matrix<Element>(Matrix<Element>& matrix):rows(matrix.rows),cols(matrix.cols),m(matrix.rows)
	{
		for(int i=0;i<rows;++i)
			m[i]=new Array<Element>(cols);
		for(int i=0;i<rows;++i)
		for(int j=0;j<cols;++j)
			(*m[i])[j]=matrix[i][j];
	}
	int numRows()
	{
		return rows;
	}

	int numCols()
	{
		return cols;
	}

	Array<Element> & operator [](int row)
	{
		return *m[row];
	}
	
	void print(ostream & out)
	{
		for(int i=0;i<rows;++i)
			cout<<m[i]<<endl;
	}
	friend ostream & operator <<(ostream & out, Matrix<Element>& m)
	{
		m.print(out);
		return out;
	}
	~Matrix<Element>()
	{
		for(int i=0;i<rows;++i)
			delete m[i];
	}

};
#endif
