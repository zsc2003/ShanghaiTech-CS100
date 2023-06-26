#include <cstddef>
#include <cstdio>
#include <iostream>
using namespace std;
class Matrix {
public:
    typedef double Scalar;//作用域在class内 
    typedef std::size_t Index;

    explicit Matrix(Index rows, Index cols);
    Matrix(const Matrix &other);
    Matrix& operator=(const Matrix &other);
    ~Matrix();
    Index rows() const;//Index->size_t
    Index cols() const;
    Scalar& at(Index r, Index c);
    const Scalar& at(Index r, Index c) const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix transpose() const;
    Matrix block(Index r, Index c, Index p, Index q) const; // Block of size p x q, starting at (r,c)
    Scalar trace() const; // For square matrix
    Scalar determinant() const; // For square matrix
    void print(){for(Index i=0;i<row;++i){for(Index j=0;j<col;++j)printf("%.2f ",matrix[i][j]);cout<<'\n';}}
    Matrix slice(Index r,Index c) const;//the matrix delete row r and column c
	void debug(){matrix[0][0]=1,matrix[0][1]=2,matrix[0][2]=3,matrix[1][0]=4,matrix[1][1]=5,matrix[1][2]=6;}
private:
    // Define your private member variables and functions here
	int row,col;
	double **matrix;
};

Matrix::Matrix(Index rows, Index cols)
{
	row=rows,col=cols;
	matrix=new Scalar*[row];
	for(Index i=0;i<row;++i)
		matrix[i]=new Scalar[cols];
	for(Index i=0;i<row;++i)
		for(Index j=0;j<col;++j)
			matrix[i][j]=0.0;
}

Matrix::Matrix(const Matrix &other)
{
	row=other.row;
	col=other.col;
	matrix=new Scalar*[row];
	for(Index i=0;i<row;++i)
		matrix[i]=new Scalar[col];
	for(Index i=0;i<row;++i)
		for(Index j=0;j<col;++j)
			matrix[i][j]=other.matrix[i][j];
}


Matrix& Matrix::operator=(const Matrix &other)
{
	if(this==&other)
		return *this;

	for(int i=0;i<row;++i)
		delete [] matrix[i];
	delete [] matrix;
	row=other.row;
	col=other.col;
	matrix=new Scalar*[row];
	for(Index i=0;i<row;++i)
		matrix[i]=new Scalar[col];
	for(Index i=0;i<row;++i)
		for(Index j=0;j<col;++j)
			matrix[i][j]=other.matrix[i][j];
	return *this;
}

Matrix::~Matrix()
{
	for(int i=0;i<row;++i)
		delete [] matrix[i];
	delete [] matrix;
}

size_t Matrix::rows() const
{
	return row;
}

size_t Matrix::cols() const
{
	return col;
}

double& Matrix::at(Index r,Index c)
{
	return matrix[r][c];
}

const double& Matrix::at(Index r,Index c) const
{
	return matrix[r][c];
}

Matrix Matrix::operator+(const Matrix &other) const
{
	Matrix A(row,col);
	for(Index i=0;i<row;++i)
		for(Index j=0;j<col;++j)
			A.matrix[i][j]=matrix[i][j]+other.matrix[i][j];
	return A;
}

Matrix Matrix::operator-(const Matrix &other) const
{
	Matrix A(row,col);
	for(Index i=0;i<row;++i)
		for(Index j=0;j<col;++j)
			A.matrix[i][j]=matrix[i][j]-other.matrix[i][j];
	return A;
}

Matrix Matrix::operator*(const Matrix &other) const
{
	Matrix A(row,other.col);
	for(Index i=0;i<row;++i)
		for(Index j=0;j<other.col;++j)
			for(Index k=0;k<col;++k)
				A.matrix[i][j]+=matrix[i][k]*other.matrix[k][j];
	return A;
}

Matrix Matrix::transpose() const//转置矩阵 
{
	Matrix A(col,row);
	for(Index i=0;i<row;++i)
		for(Index j=0;j<col;++j)
			A.matrix[j][i]=matrix[i][j];
	return A;
}

Matrix Matrix::block(Index r,Index c,Index p,Index q) const//submatrix
{
	Matrix A(p,q);
	for(Index i=0;i<p;++i)
		for(Index j=0;j<q;++j)
			A.matrix[i][j]=matrix[r+i][c+j];
	return A;
}

double Matrix::trace() const
{
	Scalar ans=0.0;
	for(Index i=0;i<row;++i)
		ans+=matrix[i][i];
	return ans;
}

Matrix Matrix::slice(Index r,Index c) const
{
	Matrix A(row-1,col-1);
	Index rr=-1,cc=-1;
	for(Index i=0;i<row;++i)
	{
		if(i==r)continue;
		rr++;
		cc=-1;
		for(Index j=0;j<col;++j)
		{
			if(j==c)continue;
			cc++;
			A.matrix[rr][cc]=matrix[i][j];
		}
	}
	return A;
}
double Matrix::determinant() const
{
	if(row==1)
		return matrix[0][0];
	Scalar ans=0.0;
	for(Index i=0;i<col;++i)
	{
		Matrix A=this->slice(0,i);
		if(i&1)//i->odd
			ans-=matrix[0][i]*A.determinant();
		else
			ans+=matrix[0][i]*A.determinant();
	}
	return ans;
}
int main()
{
/*	Matrix A(2,3;
	A.debug();
	A.print();
	Matrix B=A.block(0,1,2,2);
	B.print();
	cout<<B.trace()<<' '<<B.determinant()<<'\n';*/
///	string s;
//	scanf("%s",s);
//	cout<<s;
	return 0;
}
