#include <iostream>
#include <iomanip>
#include <string>
using namespace std; 

class personType
{
private:
	int ID;
	string name;
	double grade;

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

	void setID(int newID)
	{
		ID = newID;
	}

	void setGrade(int newGrade)
	{
		grade = newGrade;
	}

	void print()
	{
		cout << name<< setw(10) << ID << setw(10) << grade << endl;
	}

	friend std::ostream& operator<< (std::ostream& o,  personType& person)
	{
		person.print();
		return o;
	}

	bool personType::operator==(const personType & person1) 
	{
		return name == person1.name;
	}

	bool personType::operator<(personType x)
	{
		return name<x.name;
	}

	bool personType::operator>(personType x)
	{
		return name>x.name;
	}

	bool personType::operator>=(personType x)
	{
		return name>=x.name;
	}

	bool personType::operator<=(personType x)
	{
		return name<=x.name;
	}
};