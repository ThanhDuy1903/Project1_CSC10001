#include"Login.h"
string AcademicYear;
Semester CUR_SMT;

bool check_Login(string& ID, string& Pass, fstream& file, string filename)
{
	file.open(filename, ios::in | ios::out);
	if (!file.is_open()) return false;
	while (!file.eof())
	{
		string tmpID, tmpPass;
		getline(file, tmpID, ',');
		if (tmpID == ID)
		{
			getline(file, tmpPass, ',');
			erase_space(tmpPass);
			if (tmpPass == Pass)
				return true;
		}
		string tmp;
		getline(file, tmp);
	}
	return false;
}
bool find_posAccount(string ID, fstream& file, string filename)
{
	file.open(filename, ios::in | ios::out);
	while (!file.eof())
	{
		string tmp;
		getline(file, tmp, ',');
		if (tmp == ID) return true;
		getline(file, tmp);
	}
	return false;
}
void Login(string& ID, string& Pass)
{
	cout << "   ID: ";
	cin >> ID;
	cout << "   Password: ";
	cin >> Pass;
}
void loginsystem()
{
	system("cls");
	fstream file;
	string ID, Pass;
	SEEK_AcademicYear(AcademicYear);
	r_cur_semester(CUR_SMT);
	int line = 1; //Vị trí dòng của menu
	string LoginMenu[4];
	LoginMenu[0] = "----------------------------LOGIN PAGE----------------------------";
	LoginMenu[1] = "STUDENT";
	LoginMenu[2] = "ACADEMIC STAFF";
	LoginMenu[3] = "Out Program";
	print_Menu(LoginMenu, 4);
	gotoxy(0, line);
	cout << (char)4; //Vẽ con trỏ trỏ tới menu
	while (true) {
		if (kbhit()) {
			bool checkEnter = false;
			int x = move();
			gotoxy(0, line);
			cout << " "; //Xóa con trỏ ở vị trí cũ
			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= 4) line = 1;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 1) line = 3;
				break;
			}
			case 5:
			{
				checkEnter = true;
				if (line == 1)
				{
					system("cls");
					gotoxy(3, 0);
					cout << "----------------------------LOGIN PAGE----------------------------\n";
					cout << "   STUDENT\n";
					string filename, Class;
					string tmp_sub;
					Student S;
					Login(ID, Pass);
					filename = file_AccountStu;
					if (check_Login(ID, Pass, file, filename) == false)
					{
						cout << "\n   The Username or Password is Incorrect!";
						Sleep(2000);
						if (file.is_open()) file.close();
						loginsystem();
					}
					S.StudentID = ID, S.password = Pass;
					getline(file, Class);
					tmp_sub = Class.substr(0, 2);
					filename = "Student\\" + tmp_sub + "\\" + type_of_training(Class) + "\\" + Class + ".csv";
					if (file.is_open()) file.close();
					interfaceStu(file, filename, S, Class);
					break;
				}
				else if (line == 2)
				{
					system("cls");
					gotoxy(3, 0);
					cout << "----------------------------LOGIN PAGE----------------------------\n";
					cout << "   ACADEMIC\n";
					Academic_staff staff;
					Login(ID, Pass);
					if (check_Login(ID, Pass, file, file_inf_staff) == false)
					{
						cout << "\n   The Username or Password is Incorrect!";
						Sleep(2000);
						if (file.is_open()) file.close();
						loginsystem();
					}
					staff.staffID = ID; staff.password = Pass;
					r_inf_staff(file, staff);
					if (file.is_open()) file.close();
					interface_Staff(staff);
					break;
				}
				else return;
				break;
			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(LoginMenu, 4);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}