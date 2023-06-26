#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std; 
// This class is quite simple with only some getters and setters.
// Finish the definitions of these functions first.
class Grade {
public:
	// This constructor initializes the members with the parameters.
	Grade(const std::string &name, int number, double grade) : m_name(name),m_number(number),m_grade(grade) {};
	std::string getName() const {return m_name;}
	void setName(const std::string &name) {m_name=name;}
	int getNumber() const {return m_number;}
	void setNumber(int number) {m_number=number;}
	double getGrade() const {return m_grade;}
	void setGrade(double grade) {m_grade=grade;}
	
private:
	std::string m_name;
	int m_number;//student number
	double m_grade;
};

struct NameComparator {
	bool operator()(const Grade &a, const Grade &b) const
	{
		return a.getName() < b.getName();
	}
};
	
struct NumberComparator {
	bool operator()(const Grade &a, const Grade &b) const
	{
		return a.getNumber() < b.getNumber();
	}
};
	
struct GradeComparator {
	bool operator()(const Grade &a, const Grade &b) const
	{
		return a.getGrade() > b.getGrade();
	}
};
	
class Gradesheet {
	friend std::ostream &operator<<(std::ostream &os, const Gradesheet &sheet)
	{
		os<<"/------------------------------\\"<<'\n';
		os<<"|Name      Number    Grade     |"<<'\n';
		os<<"|------------------------------|"<<'\n';
		int l=sheet.m_grades.size();
		for(int i=0;i<l;++i)
		{
			os<<'|';
			os<<std::left<<setw(10)<<sheet.m_grades[i].getName();
			os<<std::left<<setw(10)<<sheet.m_grades[i].getNumber();
			os.precision(3);
			os<<std::left<<setw(10)<<sheet.m_grades[i].getGrade();
			os<<'|'<<'\n';
		}
		os<<"\\------------------------------/"<<'\n';
		return os;//一定要return 达到链式的作用
	}
	
public:
	Gradesheet(){m_grades.clear();}
	~Gradesheet(){m_grades.clear();}
	
	std::size_t size() const {return m_grades.size();}
	double average() const;
	bool addGrade(const Grade &grade);
	double findByName(const std::string &name) const;
	double findByNumber(int number) const;
	Grade &operator[](std::size_t i) {return m_grades[i];}
	const Grade &operator[](std::size_t i) const {return m_grades[i];}
	void sortByName() {sort(m_grades.begin(),m_grades.end(),NameComparator());}
	void sortByNumber() {sort(m_grades.begin(),m_grades.end(),NumberComparator());}
	void sortByGrade() {sort(m_grades.begin(),m_grades.end(),GradeComparator());}
	
private:
	std::vector<Grade> m_grades;
};

double Gradesheet::average() const
{
	int l=m_grades.size();
	double ans=0.0;
	for(int i=0;i<l;++i)
		ans+=m_grades[i].getGrade();
	return ans/(double)l;
}
bool Gradesheet::addGrade(const Grade &grade)
{
	int l=m_grades.size();
	for(int i=0;i<l;++i)
		if((m_grades[i].getName()==grade.getName())||(m_grades[i].getNumber()==grade.getNumber()))
			return 0;
	m_grades.push_back(grade);
	return 1;
}
double Gradesheet::findByName(const std::string &name) const
{
	int l=m_grades.size();
	for(int i=0;i<l;++i)
		if(m_grades[i].getName()==name)
			return m_grades[i].getGrade();
	return -1;
}
double Gradesheet::findByNumber(int number) const
{
	int l=m_grades.size();
	for(int i=0;i<l;++i)
		if(m_grades[i].getNumber()==number)
			return m_grades[i].getGrade();
	return -1;
}

int main() {
	Gradesheet sheet;
	sheet.addGrade(Grade("Bob", 1, 95));
	sheet.addGrade(Grade("Carl", 2, 100));
	sheet.addGrade(Grade("Alex", 3, 90));
	sheet.sortByGrade();
	std::cout << "size == " << sheet.size() << "\n" << sheet;
	return 0;
}
