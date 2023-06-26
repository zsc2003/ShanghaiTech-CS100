#include <string>
#include <iostream>
#include <cstdio>
using namespace std;
// REMOVE THIS CLASS WHEN SUBMITTING!!!
class Point {
	double x{0}, y{0};
	std::string label;

public:
	Point(double x0, double y0, const std::string &l  = "")
		: x(x0), y(y0), label(l) {}
	Point() = default;
	double get_x() const {
		return x;
	}
	double get_y() const {
		return y;
	}
	std::string get_label() const {
		return label;
	}
	Point &set_x(double x0) {
		x = x0;
		return *this;
	}
	Point &set_y(double y0) {
		y = y0;
		return *this;
	}
	Point &set_label(const std::string &l) {
		label = l;
		return *this;
	}
};

class Point_counted {
	friend class Point_handle;//友元类 
	//Point_handle类可访问Point_counted类中private,protected的元素
	//若写成 friend class Point_handle::function()
	//则只能在 function访问private,protected变量 
	Point_counted(){}
	// All the members are private.
	Point p;
	unsigned cnt;
	// Define some helper member functions if you need.
};

class Point_handle {
	Point_counted *ptr;
	// Your code here.
public:
	Point_handle()
	{
		ptr=new Point_counted;
		ptr->cnt=1;
	}
	Point_handle(const Point &p){
		ptr=new Point_counted;
		ptr->p=p,ptr->cnt=1;
	}
	Point_handle(double x, double y,const string &l = ""){
		ptr=new Point_counted;
		ptr->p=Point(x,y,l),ptr->cnt=1;
	}
	Point_handle(const Point_handle &other)
	{//constructer 拷贝构造(copy-initialized) 
	//	cout<<"!111111"<<'\n';
		ptr=other.ptr;
		ptr->cnt++;
	}
	Point_handle &operator=(const Point_handle &other)
	{//拷贝赋值 (copy-assigned)
	//	cout<<"!2222222"<<'\n';
		if(this==&other)
			return *this;
		//cout<<ptr<<' '<<other.ptr<<'\n';
		if(ptr==other.ptr)
			return *this;
		ptr->cnt--;
		if(ptr->cnt==0){
			//cerr<<"deleting by copy "<<'\n'; 
			delete ptr;
		}
		ptr=other.ptr;
		ptr->cnt++;
		return *this;
	}
	~Point_handle()
	{
	//	cout<<"destructing"<<'\n'; 
		ptr->cnt--;
		if(ptr->cnt==0){
			//cerr<<"deleting by destructor "<<'\n'; 
			delete ptr;
		}
	}
	unsigned ref_count()const{return ptr->cnt;}
	double get_x()const{return ptr->p.get_x();}
	double get_y()const{return ptr->p.get_y();}
	string get_label()const{return ptr->p.get_label();}
	Point_handle &set_x(double x)
	{
		if(ptr->cnt==1)
		{
			ptr->p.set_x(x);
			return *this;	
		}
		ptr->cnt--;
		double new_x=x,new_y=ptr->p.get_y();
		string new_label=ptr->p.get_label();
		ptr=new Point_counted;
		ptr->p=Point(new_x,new_y,new_label);
		ptr->cnt=1;
		return *this;
	}
	Point_handle &set_y(double y)
	{
		if(ptr->cnt==1)
		{
			ptr->p.set_y(y);
			return *this;	
		}
		ptr->cnt--;
		double new_x=ptr->p.get_x(),new_y=y;
		string new_label=ptr->p.get_label();
		ptr=new Point_counted;
		ptr->p=Point(new_x,new_y,new_label);
		ptr->cnt=1;
		return *this;
	}
	Point_handle &set_label(string label)
	{
		if(ptr->cnt==1)
		{
			ptr->p.set_label(label);
			return *this;	
		}
		ptr->cnt--;
		double new_x=ptr->p.get_x(),new_y=ptr->p.get_y();
		string new_label=label;
		ptr=new Point_counted;
		ptr->p=Point(new_x,new_y,new_label);
		ptr->cnt=1;
		return *this;	
	}
};

int main()
{
/*	Point_handle p(3, 4, "A");
	cout << p.get_label()<<"("<< p.get_x()<<", "<< p.get_y()<<")"<<'\n';
	p.set_x(5).set_y(6);
	cout << p.get_label()<<"("<< p.get_x()<<", " <<p.get_y()<<")"<<'\n';
	cout<<p.ref_count()<<'\n';*/
//-------------------------------------------------------------------------------
/*	Point_handle ph1(5, 6, "A"),ph2 = ph1;
	cout << ph1.ref_count() << ", " << ph2.ref_count() << '\n';
	ph2.set_x(7);
	cout << ph1.get_label()<<"("<< ph1.get_x()<<", " <<ph1.get_y()<<")"<<'\n';
	cout << ph2.get_label()<<"("<< ph2.get_x()<<", " <<ph2.get_y()<<")"<<'\n';
	cout << ph1.ref_count() << ", " << ph2.ref_count() << '\n';*/
//-------------------------------------------------------------------------------
/*	Point_handle ph1(3, 4, "A"), ph2 (5, 6, "A");
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<'\n';
	ph1=ph1;
	cout<<ph1.ref_count()<<'\n';
	ph1 = ph2;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<'\n';
	ph2 = ph1;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<'\n';
	ph1=ph1;
	cout<<ph1.ref_count()<<'\n';*/
//-------------------------------------------------------------------------------
/*	Point_handle ph1(3, 4, "A"), ph2 (5, 6, "A"),ph3(7,8,"b");
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph1=ph2;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph1=ph3;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph2=ph3;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph1.set_x(1);
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph1.set_y(1).set_x(1);
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph2.set_y(1).set_x(1);
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';*/
//-------------------------------------------------------------------------------
/*	Point_handle ph1,ph2(1,1,"1");
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<'\n';
	ph1=ph2;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<'\n';*/
//-------------------------------------------------------------------------------
/*	Point_handle ph1(1,2,"A"),ph2=ph1,ph3=ph2;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph1.set_x(1);
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph1.set_y(1).set_label("A").set_x(1).set_x(1).set_x(1);
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph1=ph2;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';
	ph1=ph2;
	cout<<ph1.ref_count()<<' '<<ph2.ref_count()<<' '<<ph3.ref_count()<<'\n';*/
	return 0;
}
