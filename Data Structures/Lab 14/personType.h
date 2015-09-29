#include <iostream>
#include <iomanip>
#include <string>
using namespace std; 

class personType
{
private:
	int *ID;
	string name;
	double *grade;

public:
	personType()
	{
		grade = 0;
		ID = 0;
	}

	personType(string newName)
	{
		name = newName;
		grade = 0;
		ID = 0;
	}

	void setID(int * newID)
	{
		ID = newID;
	}

	void setGrade(double * newGrade)
	{
		grade = newGrade;
	}

	string returnName()
	{
		return name;
	}
	void print()
	{
		cout << name<< "     " << ID << "     " << grade << endl;
	}

	friend std::ostream& operator<< (ostream& o, const personType& person) 
	{
		cout << person.name<< "     " << person.ID << "     " << person.grade << endl;
		return o;
	}

	bool personType::operator==(const personType & person1) const
	{
		return name == person1.name;
	}

	bool personType::operator<(personType x)const
	{
		return name<x.name;
	}

	bool personType::operator>(personType x)const
	{
		return name>x.name;
	}

	bool personType::operator>=(personType x)const
	{
		return name>=x.name;
	}

	bool personType::operator<=(personType x)const
	{
		return name<=x.name;
	}
};