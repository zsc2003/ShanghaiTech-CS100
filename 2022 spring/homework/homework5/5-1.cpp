
// DO NOT MODIFY THE CODE BELOW
#include <cstddef>
#include<iostream>

using namespace std;

class Array {
public:
	Array();
	explicit Array(std::size_t n);
	explicit Array(int *begin, int *end);
	Array(const Array &other);
	Array &operator=(const Array &other);
	~Array();
	int &at(std::size_t n);
	const int &at(std::size_t n) const;//函数后加const表示只读 
	std::size_t size() const;
	bool empty() const;
	void clear();
	Array slice(std::size_t l, std::size_t r, std::size_t s = 1) const;
	
	void print();
	
private:
	std::size_t m_size;//size_t用法和int一样,范围取决于平台 
	int *m_data;
};

// YOUR CODE STARTS HERE
Array::Array()
{
	m_size=0; 
}

Array::Array(std::size_t n)
{
//	cout<<"in the constructor (size_t n)\n";
	if(n<0)n=0;
	m_size=n;
	if(n>0)
		m_data=new int[n];
	for(int i=0;i<n;++i)
		m_data[i]=0;
}

Array::Array(int *begin, int *end)
{
//	cout<<"in the constructor (int *begin, int *end)\n";
	int n=end-begin;
	if(n<0)n=0;
//	cout<<"n="<<n<<'\n';
	m_size=n;
	if(n>0)
		m_data=new int[n];
	for(int i=0;i<n;++i)
		m_data[i]=*(begin+i);
}

Array::Array(const Array &other)
{
//	cout<<"in the copy constructor\n";
	m_size=other.m_size;
	if(m_size>0)
		m_data=new int[m_size];
	for(int i=0;i<m_size;++i)
		m_data[i]=other.m_data[i];
}

Array &Array::operator=(const Array &a)
{
	if(this==&a)//self-assignment
		return *this;
	if(m_size!=0)
		delete [] m_data;
	m_size=a.m_size;
	if(m_size>0)
		m_data=new int[m_size];
	for(int i=0;i<m_size;++i)
		m_data[i]=a.m_data[i];
	return *this;
}

Array::~Array()
{
	if(m_size!=0)
		delete [] m_data;
	m_size=0;
}

int &Array::at(std::size_t n)
{
	return *(m_data+n);
}

const int &Array::at(std::size_t n) const
{
//	const int x=*(m_data+n)
//	return x;
	return *(m_data+n);
}

std::size_t Array::size() const
{
	return m_size;
}

void Array::clear()
{
	if(m_size!=0)
		delete [] m_data;
	m_size=0;
}

Array Array::slice(std::size_t l, std::size_t r, std::size_t s ) const
{
	if(r>m_size)
		r=m_size;
	int n=0;
	if(s<=0||l<0||r<0)n=0;
	else
	{
		for(int i=l;i<r;i+=s)
			++n;
	}
	Array a(n);
	int pos=l;
	for(int i=0;i<n;++i)
	{
		a.m_data[i]=m_data[pos];
		pos+=s;
	}
	return a;
}

void Array::print()
{
	cout<<"m_size="<<m_size<<'\n';
	for(int i=0;i<this->m_size;++i)
		cout<<m_data[i]<<' ';
	cout<<'\n';
}

bool Array::empty() const
{
	if(m_size==0)
		return true;
	return false;
}
// YOUR CODE ENDS HERE

int main() {
	// You can test your implementation here, but we will replace the main function on OJ.
	/*size_t m_size;
	m_size=5;
	cout<<m_size;
	int *a=new int[10];
	for(int i=0;i<10;++i)a[i]=i;
	delete [] a;*/
	
	Array a1;
	a1.print();
/*	
	int arr[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
//	cout<<"ar="<<ar<<'\n';
	Array a2(arr, arr + 10 );
	a2.print();
	
	Array a3(a2);
	a3.print();
	
	Array a4(0);
	a4.print();
	a4=a3;
	a4.print();
	//cout<<arr.m_data[i];
	
	a4.at(1)=11111;
	a4.print();*/
/*	const int xxxx=1;
	cout<<"pos1="<<pos1<<'\n';
	const int pos2=a4.at(xxxx);
	cout<<"const int overload::"<<pos2<<'\n';*/
	
/*	cout<<a4.size()<<'\n';
	a3.clear();
	cout<<a3.size()<<' '<<a4.size()<<'\n';
	Array a5=a2.slice(5,8,2);
	a5.print();
	int arr[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
	Array a2(arr, arr + 10);
	a2.print();
	Array a3;
	a3.print();
	a3=a2;
	a3.print();*/
	return 0;
}
