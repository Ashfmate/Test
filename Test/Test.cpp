//Standard library files

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>

using namespace std;

//Function prototyping

void Add_ID_To_Database(string ID);
bool Check_If_Present(string ID);
void AddStudentData();
int StudentCounter();

//Classes

struct Student
{
	string ID;
	string First_Name;
	string Last_Name;
	int age;
	string University;
	int Level;
};

class Teacher
{

};

//Main function

int main()
{
	AddStudentData();
}

//Additional functions other than main

void Add_ID_To_Database(string ID)
{
	ofstream IDs;
	IDs.open("Database/Student ID List.txt", ios::app);
	IDs << ID << endl;
}

bool Check_If_Present(string ID)
{
	ifstream IDs("Database/Student ID List.txt");
	while (IDs)
	{
		string curID;
		IDs >> curID;
		if (ID == curID)
		{
			return true;
		}
	}
	return false;
}

void AddStudentData()
{
	Student s;
	cout << "Enter The ID: ";
	cin >> s.ID;

	cout << "Enter The First name: ";
	cin >> s.First_Name;

	cout << "Enter The Last name: ";
	cin >> s.Last_Name;

	cout << "Enter The age: ";
	cin >> s.age;

	cout << "Enter The University you go to: ";
	cin >> s.University;

	cout << "Enter The level: ";
	cin >> s.Level;

	if (!Check_If_Present(s.ID))
	{
		ofstream ThisDude;
		ThisDude.open("Database/" + s.ID + ".txt");

		ThisDude << "ID: " << s.ID << endl
				 << "Name: " << s.First_Name << " " << s.Last_Name << endl
				 << "Age: " << s.age << endl
				 << "University: " << s.University << endl
				 << "Level: " << s.Level;

		Add_ID_To_Database(s.ID);
	}
}

int StudentCounter()
{
	ifstream Students("Database/Student ID List.txt");
	int counter = 0;
	while (Students)
	{
		char c = Students.get();
		if (c == 10)
		{
			++counter;
		}
	}
	return counter;
}