#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

class Expr_node {
public:
	Expr_node() = default;
	virtual double eval() const = 0;//虚函数后加const和=0表示只读,父类无用,全用在子类(纯虚函数)
	virtual std::string to_string() const = 0;//纯虚函数子类必须实现 
	//eval  returns the value of the expression
	//to_string returns a fully parenthesized representation of the expression
	virtual ~Expr_node() = default;
	Expr_node(const Expr_node &) = delete;//禁用 
	Expr_node &operator=(const Expr_node &) = delete;
};

class Number_node : public Expr_node {
	friend Number_node *make_number(double);
	double value;
	Number_node(double val) : value(val) {}//:value(val)相当于在函数里面写value=val 
	virtual double eval() const override{return value;}
	virtual std::string to_string() const override;
};
inline Number_node *make_number(double value){
	return new Number_node(value);
}
string Number_node::to_string() const
{
	stringstream s;//创建字符流
	s<<value; //把数字输入字符流
	if(value<0)
		return "("+s.str()+")";
	return s.str();
/*	if(value<0)
		return "("+(std::to_string(value))+")";
	return std::to_string(value);*/
}

class Negation_node : public Expr_node {
	friend Negation_node *make_negation(Expr_node *);
	Expr_node* operand;
	Negation_node(Expr_node* son) : operand(son) {}
	~Negation_node() throw()
	{
		delete operand;
	}
	virtual double eval() const override{return (-1.00)*operand->eval();}
	virtual string to_string() const override{return "(-"+operand->to_string()+")";}
};	

inline Negation_node *make_negation(Expr_node *value) {
	return new Negation_node(value);
}

class Binary_node : public Expr_node{
public:
	Expr_node *lhs,*rhs;
	Binary_node(Expr_node *lson,Expr_node *rson) : lhs(lson),rhs(rson) {}
	~Binary_node() throw()
	{
		delete lhs;
		delete rhs;
	}
};

class Plus_node : public Binary_node{
	using Binary_node::Binary_node;//子类继承父类构造方法
	virtual double eval() const override{return lhs->eval()+rhs->eval();}
	virtual string to_string() const override{return "("+lhs->to_string()+" + "+rhs->to_string()+")";	}
};
inline Plus_node *make_plus(Expr_node *value1,Expr_node *value2)
{
	return new Plus_node(value1,value2);
}

class Minus_node : public Binary_node{
	using Binary_node::Binary_node;
	virtual double eval() const{return lhs->eval()-rhs->eval();}
	virtual string to_string() const{return "("+lhs->to_string()+" - "+rhs->to_string()+")";}
};
inline Minus_node *make_minus(Expr_node *value1,Expr_node *value2)
{
	return new Minus_node(value1,value2);
}

class Multiply_node : public Binary_node{
	using Binary_node::Binary_node;//子类继承父类构造方法
	virtual double eval() const{return lhs->eval()*rhs->eval();}
	virtual string to_string() const{return "("+lhs->to_string()+" * "+rhs->to_string()+")";}
};
inline Multiply_node *make_multiply(Expr_node *value1,Expr_node *value2)
{
	return new Multiply_node(value1,value2);
}

class Divide_node : public Binary_node{
	using Binary_node::Binary_node;//子类继承父类构造方法
	virtual double eval() const{return lhs->eval()/rhs->eval();}
	virtual string to_string() const{return "("+lhs->to_string()+" / "+rhs->to_string()+")";}
};
inline Divide_node *make_divide(Expr_node *value1,Expr_node *value2)
{
	return new Divide_node(value1,value2);
}

//---------------------part B----------------------
class math_node : public Expr_node{
public:
	Expr_node *operand;
	math_node(Expr_node *value) : operand(value) {}
	~math_node() throw()
	{
		delete operand;
	}
};

class sin_node : public math_node{
	using math_node::math_node;//子类继承父类构造方法
	virtual double eval() const{return sin(operand->eval());}
	virtual string to_string() const
	{
		string s=operand->to_string();
		if(s[0]=='(')return "sin"+s;
		return "sin("+s+")";
	}
};
inline sin_node *make_sin(Expr_node *value)
{
	return new sin_node(value);
}

class cos_node : public math_node{
	using math_node::math_node;//子类继承父类构造方法
	virtual double eval() const{return cos(operand->eval());}
	virtual string to_string() const
	{
		string s=operand->to_string();
		if(s[0]=='(')return "cos"+s;
		return "cos("+s+")";	
	}
};
inline cos_node *make_cos(Expr_node *value)
{
	return new cos_node(value);
}

class tan_node : public math_node{
	using math_node::math_node;//子类继承父类构造方法
	virtual double eval() const{return tan(operand->eval());}
	virtual string to_string() const
	{
		string s=operand->to_string();
		if(s[0]=='(')return "tan"+s;
		return "tan("+s+")";	
	}
};
inline tan_node *make_tan(Expr_node *value)
{
	return new tan_node(value);
}

class log_node : public math_node{
	using math_node::math_node;//子类继承父类构造方法
	virtual double eval() const{return log(operand->eval());}
	virtual string to_string() const
	{
		string s=operand->to_string();
		if(s[0]=='(')return "log"+s;
		return "log("+s+")";	
	}
};
inline log_node *make_log(Expr_node *value)
{
	return new log_node(value);
}

class exp_node : public math_node{
	using math_node::math_node;//子类继承父类构造方法
	virtual double eval() const{return exp(operand->eval());}
	virtual string to_string() const
	{
		string s=operand->to_string();
		if(s[0]=='(')return "exp"+s;
		return "exp("+s+")";	
	}
};
inline exp_node *make_exp(Expr_node *value)
{
	return new exp_node(value);
}

int main() {
/*	Expr_node *expr_tree = make_divide(
				make_plus(make_number(3), make_multiply(make_number(4), make_number(5))),
				make_number(6));
	cout << expr_tree->eval() << '\n';
	cout << expr_tree->to_string() << '\n';
	delete expr_tree;
	
	Expr_node *expr_tree2 = make_multiply(
				make_negation(make_number(-5)),make_plus(make_number(3),make_number(4)));
	cout << expr_tree2->eval() << '\n';
	cout << expr_tree2->to_string() << '\n';
	delete expr_tree2;
	
	Expr_node *expr_tree3 = make_negation(
				make_plus(make_number(3),make_number(4)));
	cout << expr_tree3->eval() << '\n';
	cout << expr_tree3->to_string() << '\n';
	delete expr_tree3;
	
	Expr_node *expr_tree4 = make_negation(make_number(1.00465));
				//make_minus(make_number(3),make_number(4));
	cout << expr_tree4->eval() << '\n';
	cout << expr_tree4->to_string() << '\n';
	delete expr_tree4;
	
	Expr_node *expr_tree5 = make_negation(make_plus(make_number(3.0000),make_number(5.00000)));
	cout << expr_tree5->eval() << '\n';
	cout << expr_tree5->to_string() << '\n';
	delete expr_tree5;
	
	Expr_node *expr_tree6 = make_number(0.1);
	cout << expr_tree6->eval() << '\n';
	cout << expr_tree6->to_string() << '\n';
	delete expr_tree6;
	
	Expr_node *expr_tree7 = make_minus(make_plus(make_number(3.0000000),make_number(5.00000)),make_negation(make_number(-4.0000)));
	cout << expr_tree7->eval() << '\n';
	cout << expr_tree7->to_string() << '\n';
	delete expr_tree7;
	
	Expr_node *expr_tree8 = make_multiply(make_negation(make_divide(make_number(5),make_number(6))),make_plus(make_number(3),make_number(4)));
	cout << expr_tree8->eval() << '\n';
	cout << expr_tree8->to_string() << '\n';
	delete expr_tree8;*/
//-----------------part II-------------------------------- 
/*	Expr_node *bonus_tree =
		make_plus(make_exp(make_sin(make_number(3))), make_number(1));
	cout << bonus_tree->eval() << '\n';
	cout << bonus_tree->to_string() << '\n';
	delete bonus_tree;
	
	Expr_node *bonus_tree2 = make_sin(make_number(3));
	cout << bonus_tree2->eval() << '\n';
	cout << bonus_tree2->to_string() << '\n';
	delete bonus_tree2;	
	
	Expr_node *bonus_tree3 = make_sin(make_plus(make_number(3),make_number(5)));
	cout << bonus_tree3->eval() << '\n';
	cout << bonus_tree3->to_string() << '\n';
	delete bonus_tree3;*/
	
	Expr_node *bonus_tree4 = make_plus(make_cos(make_number(-3)),make_sin(make_plus(make_number(3),make_number(4))));
	cout << bonus_tree4->eval() << '\n';
	cout << bonus_tree4->to_string() << '\n';
	delete bonus_tree4;
	return 0;
}
