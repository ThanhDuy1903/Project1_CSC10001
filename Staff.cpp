#include"Staff.h"
extern string AcademicYear;
extern Semester CUR_SMT;

void rewrite_infStaff(fstream& file, Academic_staff& staff)
{
	file.seekg(0, SEEK_CUR);
	file << "," << staff.Name << "," << setw(2) << right << setfill('0') << staff.Birth.day << "/";
	file << setw(2) << setfill('0') << staff.Birth.month << "/" << staff.Birth.year << "," << staff.Gender;
}
void r_inf_staff(fstream& file, Academic_staff& staff)
{
	file.seekg(0, SEEK_CUR);
	getline(file, staff.Name, ',');
	file >> staff.Birth.day;
	file.seekg(1, SEEK_CUR);
	file >> staff.Birth.month;
	file.seekg(1, SEEK_CUR);
	file >> staff.Birth.year;
	file.seekg(1, SEEK_CUR);
	getline(file, staff.Gender);
}
void export_AceStaff(Academic_staff& staff)
{
	cout << "   ID: " << staff.staffID << endl;
	cout << "   Name: " << staff.Name << endl;
	cout << "   Birth: " << setw(2) << right << setfill('0') << staff.Birth.day << "/";
	cout << setw(2) << setfill('0') << staff.Birth.month << "/" << staff.Birth.year << endl;
	cout << "   Gender: " << staff.Gender << endl;
	cout << "   Password: " << staff.password << endl;
}
Semester interfaceUpdateSemester()
{
	system("cls");
	Semester NewSmt;
	cout << "   -----------------------Update Semester-----------------------\n";
	cout << "   Current Academic: " << AcademicYear << "     Semester: " << CUR_SMT.semester << "\n\n";
	cout << "   Semester(1/2/3): ";
	cin >> NewSmt.semester;
	cout << "   Start Date(dd/mm/yyyy): ";
	string tmp;
	cin.ignore();
	getline(cin, tmp);
	NewSmt.startDate = r_Date(tmp);
	cout << "   End Date(dd/mm/yyyy): ";
	getline(cin, tmp);
	NewSmt.endDate = r_Date(tmp);
	return NewSmt;
}
string interface_SELECT_ACADEMIC(stringstream& ss, int n)
{
	system("cls");
	string s = "Back";
	int line = 1;
	string* Academic = new string[n + 2];
	if (Academic == nullptr) return "Back";
	Academic[0] = "---------------------- SELECT ACADEMIC YEAR ----------------------";
	Academic[n + 1] = "Back";
	for (int i = 1; i < n + 1; i++)
	{
		int x;
		ss >> x;
		Academic[i] = to_string(2000 + x) + "-" + to_string(2000 + x + 1);
	}
	print_Menu(Academic, n + 2);
	gotoxy(0, line);
	cout << (char)4;
	while (true) {
		if (kbhit()) {
			bool checkOut = false;
			int x = move();
			gotoxy(0, line);
			cout << " "; //Xóa con trỏ ở vị trí cũ
			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= n + 2) line = 1;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 1) line = n + 1;
				break;
			}
			case 5:
			{
				if (line >= n + 1) { checkOut = true; break; }
				else {
					s = Academic[line];
					delete[] Academic;
					return s;
				}
			}
			}
			if (checkOut == true) break;
			gotoxy(0, line);
			cout << (char)4;
		}
	}
	delete[] Academic;
	return s;
}
string interface_SELECT_CLASS(stringstream& ss, int n) {
	system("cls");
	string s = "";
	int line = 1;
	string* CLASS = new string[n + 2];
	if (CLASS == nullptr) return "Back";
	CLASS[0] = "---------------------- SELECT CLASS ----------------------";
	CLASS[n + 1] = "Back";
	for (int i = 1; i < n + 1; i++)
	{
		ss >> CLASS[i];
	}
	print_Menu(CLASS, n + 2);
	gotoxy(0, line);
	cout << (char)4;
	while (true) {
		if (kbhit()) {
			bool checkOut = false;
			int x = move();
			gotoxy(0, line);
			cout << " "; //Xóa con trỏ ở vị trí cũ
			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= n + 2) line = 1;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 1) line = n + 1;
				break;
			}
			case 5:
			{
				if (line == n + 1) { checkOut = true; break; }
				s = CLASS[line];
				delete[] CLASS;
				return s;
			}
			}
			if (checkOut == true) break;
			gotoxy(0, line);
			cout << (char)4;
		}
	}
	delete[] CLASS;
	return s;
}
void interfacetypeoftraining(string& type)
{
	system("cls");
	int line = 1;
	string TRANING[6];
	TRANING[0] = "---------------------- SELECT TYPE OF TRAINING ----------------------";
	TRANING[1] = "1. APCS";
	TRANING[2] = "2. CLC";
	TRANING[3] = "3. CTT";
	TRANING[4] = "4. VP";
	TRANING[5] = "Back";
	print_Menu(TRANING, 6);
	gotoxy(0, line);
	cout << (char)4; //Vẽ con trỏ trỏ tới menu
	while (true) {
		if (kbhit()) {
			int x = move();
			gotoxy(0, line);
			cout << " "; //Xóa con trỏ ở vị trí cũ
			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= 6) line = 1;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 1) line = 5;
				break;
			}
			case 5:
			{
				switch (line)
				{
				case 1: type = "APCS"; return;
				case 2: type = "CLC"; return;
				case 3: type = "CTT"; return;
				case 4: type = "VP"; return;
				case 5: type = "Back"; return;
				}
				break;
			}
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}

void interface_Staff(Academic_staff& staff)
{
	system("cls");
	string tmp;
	fstream file;
	int line = 1; //Vị trí dòng của menu
	string Staff[7];
	Staff[0] = "-----------------------ACEDEMIC STAFF-----------------------";
	Staff[1] = "Change password";
	Staff[2] = "Profile";
	Staff[3] = "Manage student";
	Staff[4] = "Manage course";
	Staff[5] = "Academic Year";
	Staff[6] = "Log out";
	print_Menu(Staff, 7);
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
				if (line >= 7) line = 1;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 1) line = 7 - 1;
				break;
			}
			case 5:
			{
				checkEnter = true;
				switch (line)
				{
				case 1:
				{
					system("cls");
					gotoxy(3, 0);
					cout << "----------------------------CHANGE PASSWORD----------------------------\n\n";
					while (true)
					{
						bool isAcceptable = false;
						cout << "   New pasword(maximum 15 key): ";
						tmp = import_newPass(isAcceptable);
						if (isAcceptable == true) break;
						cout << "   Password length limit exceeded!\n";
					}
					cout << "   CONFIRM: Press ESC to cancel or ENTER to change password!";
					bool checkChange = false;
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) { checkChange = false; break; }
						if (c == 13) { checkChange = true; break; }
					}
					if (checkChange == false) break;
					staff.password = tmp;
					find_posAccount(staff.staffID, file, file_inf_staff);
					changePassword(file, tmp);
					rewrite_infStaff(file, staff);
					if (file.is_open()) file.close();
					cout << "\n   Your password is successfully changed!";
					Sleep(2000);
					break;
				}
				case 2:
					system("cls");
					cout << "   ----------------------------PROFILE----------------------------\n\n";
					export_AceStaff(staff);
					cout << "\n   Press the ESC to go back";
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) break;
					}
					break;
				case 3:
					interfaceManageStu();
					break;
				case 4:
					interfaceManageCourses();
					break;
				case 5:
					interfaceAcademicYear();
					break;
				case 6: return;
				}
				break;

			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(Staff, 7);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}
void interfaceListClasses()
{
	system("cls");
	ListStudent L = CreateInit_StuList();
	ifstream filein;
	int n = 0, n1 = 0;
	stringstream ss = save_folder_name("Student", n);
	string ACADEMIC_YEAR = interface_SELECT_ACADEMIC(ss, n);
	if (ACADEMIC_YEAR == "Back") return;
	string str = "Student\\" + ACADEMIC_YEAR.substr(2, 2);
	string type = "";
	interfacetypeoftraining(type);
	if (type == "Back") return;
	str += "\\" + type;
	stringstream ss1 = export_filename(str, n1);
	string CLASS = interface_SELECT_CLASS(ss1, n1);
	str += "\\" + CLASS + ".csv";
	r_inf_class(filein, L, str);
	system("cls");
	int line = 1; //Vị trí dòng của menu
	string type_inf_stu_of_class[4];
	type_inf_stu_of_class[0] = "-----------------------VIEW INFORMATION OF ALL STUDENTS IN THE CLASS-----------------------";
	type_inf_stu_of_class[1] = "View the personal information";
	type_inf_stu_of_class[2] = "View the GPA in current semester and the over GPA";
	type_inf_stu_of_class[3] = "Back";
	print_Menu(type_inf_stu_of_class, 4);
	gotoxy(0, line);
	cout << (char)4; //Vẽ con trỏ trỏ tới menu
	while (true)
	{
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
				switch (line)
				{
				case 1:
					printStuList(L);
					cout << "\n\n   Press the ESC to go back!";
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) break;
					}
					break;
				case 2:
				{
					system("cls");
					cout << "   ----------------------- GPA OF STUDENTS  -----------------------\n";
					int No = 0;
					cout << "   " << setw(5) << setfill(' ') << left << "No" << setw(15) << setfill(' ') << left << "Student ID";
					cout << setw(30) << setfill(' ') << left << "Full Name" << setw(15) << setfill(' ') << left << "CUR_SMT_GPA";
					cout << "Over GPA";
					ListStudent L_tmp = L;
					while (L_tmp.Head != nullptr)
					{
						string GPAtmp = "", GPAover = "";
						GPAtmp_GPAover(L_tmp.Head->sv.StudentID, GPAtmp, GPAover);
						cout << endl << "   " << setw(5) << setfill(' ') << left << ++No;
						cout << setw(15) << setfill(' ') << left << L_tmp.Head->sv.StudentID;
						string str = L_tmp.Head->sv.Lname + " " + L_tmp.Head->sv.Fname;
						cout << setw(30) << setfill(' ') << left << str;
						cout << setw(15) << setfill(' ') << left << GPAtmp << GPAover;
						L_tmp.Head = L_tmp.Head->next;
					}
					cout << "\n\n   Press the ESC to go back!";
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) break;
					}
					break;
				}
				default: DeleteList(L); return;
				}
			}
			break;
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(type_inf_stu_of_class, 4);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
	DeleteList(L);
}
void interfaceAcademicYear()
{
	system("cls");
	int line = 2;
	string Staff[5];
	Staff[0] = "-----------------------Information Academic Year-----------------------";
	Staff[1] = "\t\t\t\tAcademic Year: " + AcademicYear + "   Semester : " + to_string(CUR_SMT.semester);
	Staff[2] = "Create New Academic Year";
	Staff[3] = "Information Academic Year";
	Staff[4] = "Back";
	print_Menu(Staff, 5);
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
				if (line >= 5) line = 2;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 2) line = 4;
				break;
			}
			case 5:
			{
				checkEnter = true;
				switch (line)
				{
				case 2:
				{
					system("cls");
					stringstream ss(AcademicYear);
					int F;
					ss >> F;
					string str = Create_Folder(to_string(F - 2000 + 1), "Student");
					Create_trainingFolder(str);
					update_AcademicYear(AcademicYear);
					ss.clear();
					ss.str("");
					ss << AcademicYear;
					ss >> F;
					str = Create_Folder(to_string(F - 2000), "Course");
					Create_3Semester(str);
					cout << "\n\n    The new academic year has just been created";
					SEEK_AcademicYear(AcademicYear);
					r_cur_semester(CUR_SMT);
					Date D;
					CUR_SMT.startDate = D;
					CUR_SMT.endDate = D;
					Staff[1] = "\t\t\t\tAcademic Year: " + AcademicYear + "   Semester : " + to_string(CUR_SMT.semester);
					Sleep(2000);
					break;
				}
				case 3:
					interfaceSemester();
					break;
				case 4:
					return;
				default: break;
				}
				break;
			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(Staff, 5);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}
void interfaceCreateClass()
{
	stringstream ss(AcademicYear);
	int F;
	ss >> F;
	string str = to_string(F - 2000);
	system("cls");
	int line = 1; //Vị trí dòng của menu
	string Create_Class[4];
	Create_Class[0] = "-----------------------Information Academic Year-----------------------";
	Create_Class[1] = "Create class by file CSV";
	Create_Class[2] = "Add a student from keyboard";
	Create_Class[3] = "Back";
	print_Menu(Create_Class, 4);
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
				string type = "";
				string Class = "";
				if (line == 1 || line == 2)
				{
					interfacetypeoftraining(type);
					system("cls");
					cout << "   ------------------- Create Class -------------------\n";
					cout << "\n   Input CLass ID: ";
					cin >> Class;
				}
				ListStudent L = CreateInit_StuList();
				ifstream filein;
				if (line == 1)
				{
					string Inf_file;
					cout << "   Input source file .csv: ";
					cin.ignore();
					getline(cin, Inf_file);
					if (copyfile(Inf_file, "Student\\" + str + "\\" + type + "\\" + Class + ".csv") == false)
					{
						cout << "\n   Creating Class is failed!";
					}
					else {
						createListAccount("Student\\" + str + "\\" + type + "\\" + Class + ".csv", Class);
						r_inf_class(filein, L, "Student\\" + str + "\\" + type + "\\" + Class + ".csv");
						string path = Create_Folder(Class, "Student/" + str + "/" + type + "/Courses for students have been summarized");
						createListCourse_of_students_in_the_class(L, path);
						cout << "   Creating the classe for 1st-year students is succesfull!";
					}
					Sleep(2000);
				}
				else if (line == 2)
				{
					ofstream fileout;
					fileout.open("Student\\" + str + "\\" + type + "\\" + Class + ".csv", ios::app | ios::ate);
					if (fileout.tellp() == 0)
					{
						fileout << "No, Student ID, Full Name, Last Name, First Name, Birth, Gender, Social ID";
						string path = Create_Folder(Class, "Student/" + str + "/" + type + "/Courses for students have been summarized");
					}
					cout << endl;
					cin.ignore();
					Student S = insert_1Stu_in_system(fileout, Class, "Student\\" + str + "\\" + type + "\\" + Class + ".csv");
					fileout.close();
					createListCourse_of_a_student_in_the_class("Student/" + str + "/" + type + "/Courses for students have been summarized/" + Class + "/" + S.StudentID + ".csv");
					cout << "   Add the student is succefull!";
					Sleep(2000);
				}
				if (filein.is_open()) filein.close();
				DeleteList(L);
				if (line == 3) return;
				break;
			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(Create_Class, 4);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}

void interfaceManageStu()
{
	system("cls");
	int line = 2;
	string Staff[5];
	Staff[0] = "-----------------------MANAGE STUDENT-----------------------";
	Staff[1] = "\t\t\t\t\t" + AcademicYear;
	Staff[2] = "Create Class";
	Staff[3] = "List of Classes";
	Staff[4] = "Back";
	print_Menu(Staff, 5);
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
				if (line >= 5) line = 2;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 2) line = 4;
				break;
			}
			case 5:
			{
				checkEnter = true;
				switch (line)
				{
				case 2:
					interfaceCreateClass();
					break;
				case 3:
					interfaceListClasses();
					break;
				case 4: return;
				default: break;
				}
				break;
			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(Staff, 5);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}
void interfaceSemester()
{
	system("cls");
	int line = 1; //Vị trí dòng của menu
	string Staff[4];
	Staff[0] = "-----------------------Setting Semester-----------------------";
	Staff[1] = "Current Semester Details";
	Staff[2] = "Update Semester";
	Staff[3] = "Back";
	print_Menu(Staff, 4);
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
					cout << "   ----------------------------CURRENT SEMESTER----------------------------\n\n";
					print_cur_semester(CUR_SMT);
					cout << "\n\n   Press the ESC to go back";
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) break;
					}
				}
				else if (line == 2)
				{
					Semester NewSmt = interfaceUpdateSemester();
					CUR_SMT = NewSmt;
					updateSemester(NewSmt);
				}
				else if (line == 3) return;
				break;
			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(Staff, 4);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}

}