
#include "Matrix.h"

template<typename T>
void fillMatrix(Matrix<T> & m)
{
	int i,j;
	for(i=0;i<m.numRows();i++)
		m[i][0]=T();
	for(j=0;j<m.numCols();j++)
		m[0][j]=T();
	for(i=1;i<m.numRows();i++)
		for(j=1;j<m.numCols();j++)
			m[i][j]=T(i*j);
}

void test_int_matrix()
{
	Matrix<int> m(10,5);
	fillMatrix(m);
	Matrix<int> m2(m);
	cout<<"show the original matrix:"<<endl;
	cout<<m;
	cout<<"show the matrix constructed by copy constructor:"<<endl;
	cout<<m2;
}

void test_double_matrix()
{
	Matrix<double> m(8,10);
	fillMatrix(m);
	Matrix<double> m2(m);
	cout<<"show the original matrix:"<<endl;
	cout<<m;
	cout<<"show the matrix constructed by copy constructor:"<<endl;
	cout<<m2;
}

void generate_exception(Matrix<double>& M)throw(IndexOutOfBoundsException)
{
	for(int i=0;i<66666;++i)
	{
		M[i][i]=0;
	}
}
void test_double_matrix_exceptions()
{
	try
	{
    		cout << "Starting...\n";
    		Matrix < double > M(8,10);
    		fillMatrix( M );
    		cout << M;
    		generate_exception( M );
    		cout << "Done\n";
	}
	catch(IndexOutOfBoundsException & e)
	{
		cout<<"IndexOutOfBoundsException occured!"<<endl;
	}
}



int main()
{
	for (int i=0; i<3; ++i)
   	{
		test_int_matrix();
		test_double_matrix();
		test_double_matrix_exceptions();
	}
	return 0;
}

