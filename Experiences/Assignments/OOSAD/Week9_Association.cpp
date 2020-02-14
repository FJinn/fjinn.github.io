#include <iostream>
#include <ctime>
#include <string>
#include "windows.h"

using namespace std;

class Student;

class Department
{
	public:
		char* name;
		
		Department(char* n)
		{
			cout<<"Department: "<<endl;
			name = new char(sizeof(strlen(n)));
			name = n;
		}
		
		char* getName() const
		{
			return name;
		}
		
		~Department()
		{
			cout<<"Department: "<<endl;
			delete(name);
		}
};

class Student
{
	public:
		char* name;
		
		Student(char* n)
		{
			cout<<"Student: "<<endl;
			name = new char(sizeof(strlen(n)));
			name = n;
		}
		
		char* getName() const
		{
			return name;
		}
		
		~Student()
		{
			cout<<"Student: "<<endl;
			delete(name);
		}
};

class Course
{
	Student* std_p;
	Department* dept_p;
	char* courseName_p;
	
	static unsigned int index;
	static Course* courseList[4];
	
public:
	Course(char* cName, Student* student, Department* dept): courseName_p(0), std_p(student), dept_p(dept)
	{
		cout<<"Course: "<<endl;
		if(index<4)
		{
			courseName_p = new char(sizeof(strlen(cName)));
			courseName_p = cName;
			
			courseList[index] = this;
			++index;
		}
		else
		{
			cout<<"Cannot accomodate any more Course!"<<endl;
		}
	}
	~Course()
	{
		cout<<"Course: "<<endl;
		delete(courseName_p);
	}
	
	char* getStudentName() const
	{
		return std_p->getName();
	}
	
	char* getDepartmentName() const
	{
		return dept_p->getName();
	}
	
	char* getCourseName() const
	{
		return courseName_p;
	}
	
	static char* findStudent(char* cName, char* deptName)
	{
		for(int i=0; i<index; i++)
		{
			if(courseList[i]->getCourseName() == cName && courseList[i]->getDepartmentName() == deptName)
			{
				return courseList[i]->getStudentName();
			}
		}
	}
};

unsigned int Course::index = 0;
Course* Course::courseList[4] = {0,0,0,0};

int main()
{
	int i;
	cout<<"\nExample of Association class"<< endl;
	cout<<"=============================="<< endl;
	cout<<"We have 4 students"<<endl;
	Student* studentName[4] = {new Student("Javin"), new Student("Sean"),new Student("David"),new Student("Jonathan")};
	cout<<endl;
	cout<<"We got 2 Department"<<endl;
	Department* department[2] = {new Department("Game Development"), new Department("Computing")};
	
	cout<<endl;
	cout<<"Class Course Association student and department, with a course name..."<<endl;
	Course course1("FOP", studentName[0], department[1]);
	Course course2("OOP", studentName[1], department[0]);
	Course course3("DSA", studentName[2], department[1]);
	Course course4("OOSAD", studentName[3], department[0]);
	
	cout<<"Finding a student using course and department"<< endl;
	cout<<"Student who has taken OOSAD in Game Development department is: "<<endl;
	cout<<Course::findStudent("OOSAD", "Game Development")<<endl;
	
	cout<<endl;
	cout<<"Deletion of object"<<endl;
	for(int i=0; i<2; i++)
	{
		department[i] = NULL;
	}
	
	system("PAUSE");
	return 0;
}
