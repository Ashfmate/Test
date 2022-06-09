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
void Edit_Student_Data(string ID, int i);
void Delete_Student_Record(string ID);
void AddStudentData();
int StudentCounter();

//Classes

struct Student
{
	enum class StudentInputs
	{
		//ID,
		FName,
		LName,
		Age,
		University,
		Level
	};
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

void Edit_Student_Data(string ID, int i)
{
	string filename = "Database/" + ID + ".txt";
	ifstream GetDude(filename);
	Student s; //Takes all of our previous data for the student (RAM)

	GetDude >> s.ID >> s.First_Name >> s.Last_Name >> s.age >> s.University >> s.Level;
	//Loads all of the data to the RAM

	switch (Student::StudentInputs(i)) //jumps to the wanted data to change
	{/*
	case Student::StudentInputs::ID:
	{
		cout << "WARNING!!! changing the ID will change the name of the file\n";
		char check;
		cout << "Do you still want to continue and change the ID? press y, otherwise press anything else\n";
		cin >> check;
		if (check != 'y')
		{
			break;
		}
		string ID;
		cout << "Enter the new ID\n";
		cin >> ID;
		s.ID = ID;
	}*/
	break;
	case Student::StudentInputs::FName:
	{
		string FName;
		cin >> FName;
		s.First_Name = FName;
	}
	break;
	case Student::StudentInputs::LName:
	{
		string LName;
		cin >> LName;
		s.Last_Name = LName;
	}
	break;
	case Student::StudentInputs::Age:
	{
		int age;
		cin >> age;
		s.age = age;
	}
	break;
	case Student::StudentInputs::University:
	{
		string University;
		cin >> University;
		s.University = University;
	}
	break;
	case Student::StudentInputs::Level:
	{
		int Level;
		cin >> Level;
		s.Level = Level;
	}
	break;
	default:
		break;
	}
	ofstream SetDude(filename);
	SetDude << s.ID << " "
			<< s.First_Name << " " << s.Last_Name << " "
			<< s.age << " "
			<< s.University << " "
			<< s.Level;
	//Takes all the data from the RAM and stores in into the text file with the edited data

	//string oldname = "C:/Users/Ashfo/OneDrive/Desktop/Big project/Test/Test/Database/" + ID + ".txt";
	//string newname = "C:/Users/Ashfo/OneDrive/Desktop/Big project/Test/Test/Database/" + s.ID + ".txt";
	////Stores the names to be renamed
	//rename(oldname.c_str(), newname.c_str());
	////Renames the text file to fit the ID of the student if changed otherwise it will rename to the same name
}

void Delete_Student_Record(string ID)
{
	string filename = "Database/" + ID + ".txt";
	remove(filename.c_str());
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

		ThisDude << s.ID << " "
				 << s.First_Name << " " << s.Last_Name << " "
				 << s.age << " "
				 << s.University << " "
				 << s.Level;

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