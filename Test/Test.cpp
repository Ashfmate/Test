//Standard library files

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>

using namespace std;

//Function prototyping

void Add_ID_To_Database(string ID); //Adds a new ID to a database of IDs
bool Check_If_Present(string ID); //Returns a boolean depending on the presence of the ID entered in the parameter
void Edit_Student_Data(string ID, int i); //Edits student data based on the integer entered in (handled in the front end)
void Delete_Student_Record(string ID); //Removes an entire text file of the student as well as all reference to that student
void AddStudentData(); //Makes a text file for the student and add the ID to the ID database
int StudentCounter(); //Counts the amount of students in the ID database
int PasswordsCounter(); //Counts the amount of student with Passwords (pretty useless but there if needed)
void MakePassword(); //Makes a password for the student
bool Check_Password(string ID, string password); //Checks the validity of the password

//Classes

struct Student
{
	enum class StudentInputs
	{
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
	/*
		All that is needed is the front end.
		The Edit function has an integer to pass into it which decides the thing we want to edit.
		So when you want to use it have it be decided with an integer that goes up and down with the arrows.
		Oh yeah, the way the user will choose which to edit is by a pointer (not c++ pointer).
		This pointer will point towards the thing we want to edit and an integer will be changing depending on the pointer.
		Don't mind the password functions, they were annoying to make in the first place.
		And please please please make the front end, you don't have to make the program all over again or in your way.
		If you have any problem just ask me.
		I am tired
	*/
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
	{
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
}

void Delete_Student_Record(string ID)
{
	string filename = "Database/" + ID + ".txt";
	remove(filename.c_str());
	{
		ifstream file("Database/Student ID List.txt");
		vector<string> FileData;
		FileData.resize(StudentCounter());
		for (string& FD : FileData)
		{
			file >> FD;
		}
		ofstream IDs("Database/Student ID List.txt");
		IDs.clear();
		for (unsigned int i = 0; i < FileData.size(); ++i)
		{
			if (FileData.at(i) != ID)
			{
				IDs << FileData.at(i) << "\n";
			}
		}
	}
	{
		ifstream file("Database/Student Passwords.txt");
		vector<string> FileData;
		FileData.resize(PasswordsCounter() * 2);
		for (string& FD : FileData)
		{
			file >> FD;
		}
		ofstream IDs("Database/Student Passwords.txt");
		IDs.clear();
		IDs << "\n";
		for (unsigned int i = 0; i < FileData.size(); i += 2)
		{
			if (FileData.at(i) != ID)
			{
				IDs << FileData.at(i) << " " << FileData.at(i + 1) << "\n";
			}
		}
	}
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

int PasswordsCounter()
{
	ifstream Passwords("Database/Student Passwords.txt");
	int counter = 0;
	while (Passwords)
	{
		char c = Passwords.get();
		if (c == 10)
		{
			++counter;
		}
	}
	return (counter - 1);
}

void MakePassword()
{
	label:
	cout << "Enter your ID: ";
	string ID;
	cin >> ID;
	string password;
	if (Check_If_Present(ID))
	{
		cout << "Enter the password: ";
		cin >> password;
		cout << "Don't forget this password, you cannot get it back and there is no way to retrieve your credentials so memorize\n";
		ofstream Passes("Database/Student Passwords.txt", ios::app);
		Passes << ID << " " << password << "/n";
	}
	else
	{
		cout << "The student does not exist, try again";
		goto label;
	}
}

bool Check_Password(string ID, string password)
{
	ifstream Pass("Database/Student Passwords.txt");
	if (Check_If_Present(ID))
	{
		while (Pass)
		{
			char c = Pass.get();
			if (c == 10)
			{
				string IDs;
				Pass >> IDs;
				if (ID == IDs)
				{
					string codeword;
					Pass >> codeword;
					if (password == codeword)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	return false;
}
