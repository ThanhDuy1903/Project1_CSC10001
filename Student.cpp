#include"Global.h"
extern string AcademicYear;
extern Semester CUR_SMT;


void interfaceStu(fstream& file, string filename, Student& S, string Class)
{
	system("cls");
	int line = 1; //Vị trí dòng của menu
	string STUDENT[6];
	STUDENT[0] = "----------------------- STUDENT -----------------------";
	STUDENT[1] = "1. Change password";
	STUDENT[2] = "2. Profile";
	STUDENT[3] = "3. View of my courses";
	STUDENT[4] = "4. View grade final mark";
	STUDENT[5] = "5. Log out";
	print_Menu(STUDENT, 6);
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
				checkEnter = true;
				string tmp;
				switch (line)
				{
				case 1:
				{
					while (true)
					{
						system("cls");
						gotoxy(3, 0);
						cout << "----------------------------CHANGE PASSWORD----------------------------\n\n";
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
					S.password = tmp;
					find_posAccount(S.StudentID, file, file_AccountStu);
					changePassword(file, tmp);
					file << "," << Class;
					if (file.is_open()) file.close();
					cout << "\n   Your password is successfully changed!";
					Sleep(2000);
					break;
				}
				case 2:
					file.open(filename, ios::in | ios::out);
					seek_inf_accstu(file, S);
					exportProfile_1_Stu(S);
					cout << "\n   Press ESC to back!";
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) break;
					}
					file.close();
					break;
				case 3:
				{
					interface_Mycourse(S, Class);
					break;
				}
				case 4: 
					interface_viewFinalMark(S.StudentID, Class);
					break;
				case 5: return;
				}
				break;
			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(STUDENT, 6);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}
void interface_Mycourse(Student& S, string Class)
{
	system("cls");
	stringstream ss1;
	string arr_str[102], arr_Name[102][2];
	arr_str[0] = "----------------------- MY COURSES -----------------------";
	ss1 << "   Academic Year: " << AcademicYear << "          " << "Semester " << CUR_SMT.semester;
	getline(ss1, arr_str[1]);
	ss1.clear();
	ss1 << setw(15) << setfill(' ') << left << "Course ID";
	ss1 << setw(45) << setfill(' ') << left << "Course Name";
	ss1 << setw(20) << setfill(' ') << left << "Class Name";
	ss1 << setw(10) << setfill(' ') << left << "Credit";
	ss1 << "Schedule";
	getline(ss1, arr_str[2]);
	string path = "Course\\" + AcademicYear.substr(2, 2) + "\\Semester " + to_string(CUR_SMT.semester);
	ListCourse L_Course = Create_emptyListCourse();
	r_List_Course(L_Course, path + "\\ListCourse.csv");
	path = "Student\\" + Class.substr(0, 2) + "\\" + type_of_training(Class) + "\\Courses for students have been summarized\\" + Class + "\\" + S.StudentID + ".csv";
	stringstream ss = r_infCourse_of_Stu(path, AcademicYear, "Semester " + to_string(CUR_SMT.semester));
	string tmp;
	int i = 3;
	while (getline(ss, tmp, ','))
	{
		NodeC tmp2 = L_Course.head;
		while (tmp2 != nullptr)
		{
			if (tmp.find(tmp2->data.ID + "-" + tmp2->data.ClassName) != -1)
			{
				arr_Name[i][0] = tmp2->data.ID;
				arr_Name[i][1] = tmp2->data.ClassName;
				ss1.clear();
				add1_Course_ofStu(tmp2->data, ss1);
				getline(ss1, arr_str[i++]);
			}
			tmp2 = tmp2->next;
		}
	}
	int line = 3;
	print_Menu(arr_str, i);
	cout << "\n   Press the ESC to go back";
	gotoxy(0, line);
	cout << (char)4;
	while (true) {
		if (kbhit())
		{
			bool checkEnter = false;
			int x = move();
			gotoxy(0, line);
			cout << " "; //Xóa con trỏ ở vị trí cũ
			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= i) line = 3;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 2) line = i - 1;
				break;
			}
			case 5:
			{
				checkEnter = true;
				string path = "Course\\" + AcademicYear.substr(2, 2) + "\\Semester " + to_string(CUR_SMT.semester);
				ifstream file(path + "\\ScoreboardCourses" + "\\" + arr_Name[line][0] + "-" + arr_Name[line][1] + ".csv", ios::in | ios::out);
				ListScore LS = r_ListScore(file);
				print_list_of_student_inCourse(LS);
				cout << "\n\n   Press the ESC to go back!";
				while (true)
				{
					char c = getch();
					if ((int)c == -32) c = getch();
					if (c == 27) break;
				}
				file.close();
				break;
			}
			case 8: DeleteList(L_Course); return;
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(arr_str, i);
				cout << "\n   Press the ESC to go back";
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
	DeleteList(L_Course);
}
void interface_viewFinalMark(string StudentID, string Class)
{
	stringstream ss;
	int x = stoi(Class.substr(0, 2));
	for (int i = 0; i < 4; i++)
	{
		ss << x + i;
		if (i < 3) ss << " ";
	}
	string ACADEMIC_YEAR = interface_SELECT_ACADEMIC(ss, 4);
	if (ACADEMIC_YEAR == "Back") return;
	cout << endl << endl << endl << endl << endl;
	string op_SMT = Select_Semester();
	stringstream ss1 = r_infCourse_of_Stu("Student/" + Class.substr(0, 2) + "/" + type_of_training(Class) + "/Courses for students have been summarized/" + Class + "/" + StudentID + ".csv", ACADEMIC_YEAR, op_SMT);
	string tmp;
	system("cls");
	cout << "\n   ----------------------- VIEW GRADE FINAL MARK -----------------------\n\n";
	cout << "   " << setw(15) << setfill(' ') << left << "Course ID";
	cout << setw(45) << setfill(' ') << left << "Course Name";
	cout << setw(10) << setfill(' ') << left << "Credits";
	cout << "Final Grade\n";
	while (getline(ss1, tmp, '-'))
	{
		search_file_Course_FinalGrade("Course/FinalGrade _of_Courses", tmp);
		string mark = "", CourseName = "";
		int Credit = stoi(tmp.substr(tmp.length() - 5, 1));
		CourseName_Credit_Mark(mark, CourseName, "Course/FinalGrade _of_Courses/" + tmp, StudentID);
		cout << "   " << setw(15) << setfill(' ') << left << tmp.substr(0, tmp.length() - 6);
		cout << setw(45) << setfill(' ') << left << CourseName;
		cout << setw(10) << setfill(' ') << left << Credit << mark;
		getline(ss1, tmp, ',');
		cout << endl;
	}
	cout << "\n\n   Press the ESC to go back!";
	while (true)
	{
		char c = getch();
		if ((int)c == -32) c = getch();
		if (c == 27) break;
	}
}
string type_of_training(string Class)
{
	if (Class.find("CLC") != string::npos) return "CLC";
	else if (Class.find("CTT") != string::npos) return "CTT";
	else if (Class.find("VP") != string::npos) return "VP";
	return "APCS";
}
void exportProfile_1_Stu(Student& S)
{
	system("cls");
	cout << "   --------------------- Student Profile ---------------------\n\n";
	cout << "   Student ID: " << S.StudentID << endl;
	cout << "   Last Name: " << S.Lname << endl;
	cout << "   First Name: " << S.Fname << endl;
	cout << "   Birth: " << setw(2) << right << setfill('0') << S.Birth.day << "/";
	cout << setw(2) << setfill('0') << S.Birth.month << "/" << S.Birth.year << endl;
	cout << "   Gender: " << S.Gender << endl;
	cout << "   Social ID: " << S.SocialID << endl;
	cout << "   Password: " << S.password << endl;
}
void seek_inf_accstu(fstream& file, Student& S)
{
	string tmpID, tmp;
	int No = 0;
	getline(file, tmp);
	while (!file.eof())
	{
		file >> No;
		file.ignore();
		getline(file, tmpID, ',');
		if (tmpID == S.StudentID)
		{
			getline(file, tmp, ',');
			getline(file, S.Lname, ',');
			getline(file, S.Fname, ',');
			file >> S.Birth.day;
			file.seekg(1, SEEK_CUR);
			file >> S.Birth.month;
			file.seekg(1, SEEK_CUR);
			file >> S.Birth.year;
			file.seekg(1, SEEK_CUR);
			getline(file, S.Gender, ',');
			file >> S.SocialID;
			return;
		}
		getline(file, tmp);
	}
}

Student r_inf_1stu(ifstream& filein)
{
	Student S;
	string tmp;
	getline(filein, tmp, ',');
	getline(filein, S.StudentID, ',');
	getline(filein, tmp, ',');
	getline(filein, S.Lname, ',');
	getline(filein, S.Fname, ',');
	filein >> S.Birth.day;
	filein.seekg(1, SEEK_CUR);
	filein >> S.Birth.month;
	filein.seekg(1, SEEK_CUR);
	filein >> S.Birth.year;
	filein.seekg(1, SEEK_CUR);
	getline(filein, S.Gender, ',');
	filein >> S.SocialID;
	return S;
}
void w_inf_1sv(ofstream& fileout, Student S)
{
	fileout << S.StudentID << ',';
	fileout << S.Lname << " " << S.Fname << ',';
	fileout << S.Lname << ',' << S.Fname << ',';
	fileout << setw(2) << setfill('0') << right << S.Birth.day << '/';
	fileout << setw(2) << setfill('0') << right << S.Birth.month << '/';
	fileout << setw(4) << setfill('0') << right << S.Birth.year << ',';
	fileout << S.Gender << ',';
	fileout << S.SocialID;
}
void r_inf_class(ifstream& filein, ListStudent& L, string filename)
{
	filein.open(filename, ios::in);
	if (!filein.is_open()) return;
	string tmp;
	getline(filein, tmp);
	while (filein.good())
		AddTail(L, r_inf_1stu(filein));
	filein.close();
}
stringstream r_infCourse_of_Stu(string path, string CUR_YEAR, string SMT)
{
	stringstream ss;
	ifstream filein(path);
	while (filein.good())
	{
		string tmp;
		getline(filein, tmp);
		if (tmp == CUR_YEAR)
		{
			for (int i = 0; i < 3; i++)
			{
				getline(filein, tmp, ',');
				if (tmp == SMT)
				{
					getline(filein, tmp);
					int x = int(tmp.find("                    "));
					if (x == 0) return ss;
					tmp = tmp.substr(0, x);
					ss << tmp;
					filein.close();
					return ss;
				}
				if (!filein.seekg(274, ios::cur)) return ss;
			}
		}
		if (!filein.seekg(855, ios::cur)) return ss;
	}
	return ss;
}
void print1Stu(Student& S)
{
	cout << setw(15) << setfill(' ') << left << S.StudentID << setw(10) << setfill(' ') << left << S.Lname;
	cout << setw(20) << setfill(' ') << left << S.Fname << "   " << setw(2) << setfill('0') << right << S.Birth.day << "/";
	cout << setw(2) << setfill('0') << right << S.Birth.month << "/" << setw(4) << setfill('0') << right << S.Birth.year << "   ";
	cout << setw(7) << setfill(' ') << left << S.Gender << setw(20) << setfill(' ') << left << S.SocialID;
}
void printStuList(ListStudent L)
{
	system("cls");
	cout << "   ----------------------- PERSONAL INFORMATION OF STUDENTS  -----------------------\n";
	int No = 0;
	cout << "   " << setw(5) << setfill(' ') << left << "No" << setw(15) << setfill(' ') << left << "Student ID";
	cout << setw(10) << setfill(' ') << left << "Last Name" << setw(20) << setfill(' ') << left << "First Name";
	cout << "   " << setw(13) << setfill(' ') << left << "Birth" << setw(7) << setfill(' ') << left << "Gender" << setw(20) << setfill(' ') << left << "Social ID" << endl;
	while (L.Head != nullptr)
	{
		cout << "   " << setw(5) << setfill(' ') << left << ++No;
		print1Stu(L.Head->sv);
		L.Head = L.Head->next;
		cout << endl;
	}
}
void createAccount(string studentID, string Class)
{
	fstream file;
	file.open(file_AccountStu, ios::out | ios::app);
	file.seekp(0, SEEK_END);
	file << endl << studentID << ',';
	changePassword(file, "1111");
	file << ',' << Class;
	file.close();
}
void createListAccount(string Inf_file, string Class)
{
	ifstream filein;
	filein.open(Inf_file, ios::in);
	string tmp;
	getline(filein, tmp);
	while (!filein.eof())
	{
		Student S = r_inf_1stu(filein);
		createAccount(S.StudentID, Class);
	}
	filein.close();
}
bool createCourse_of_student_in_the_class(string StudentID, string CourseID, string ClassName)
{
	string Class = seek_class(StudentID);
	string tmp_sub = Class.substr(0, 2);
	fstream file("Student\\" + tmp_sub + "\\" + type_of_training(Class) + "\\Courses for students have been summarized\\" + Class + "\\" + StudentID + ".csv");
	string tmp;
	while (file.good())
	{
		getline(file, tmp);
		if (tmp == AcademicYear)
		{
			string tmp1 = "Semester " + to_string(CUR_SMT.semester);
			while (true)
			{
				getline(file, tmp, ',');
				if (tmp == tmp1) break;
				file.seekg(274, ios::cur);
			}
			break;
		}
		file.seekg(855, ios::cur);
	}
	for (int i = 1; i <= 13; i++)
	{
		getline(file, tmp, ',');
		if (tmp == "                    ")
		{
			file.seekp(-21, ios::cur);
			tmp = CourseID + "-" + ClassName;
			file << setw(20) << setfill(' ') << left << tmp << ',';
			return true;
		}
	}
	file.close();
	return false;
}
void deleteCourse_of_student_in_the_class(string StudentID, string CourseID, string ClassName)
{
	string Class = seek_class(StudentID);
	string tmp_sub = Class.substr(0, 2);
	fstream file("Student\\" + tmp_sub + "\\" + type_of_training(Class) + "\\Courses for students have been summarized\\" + Class + "\\" + StudentID + ".csv");
	string tmp = "";
	string tmp1 = CourseID + "-" + ClassName;
	while (file.good())
	{
		getline(file, tmp);
		if (tmp == AcademicYear)
		{
			string tmp1 = "Semester " + to_string(CUR_SMT.semester);
			while (true)
			{
				getline(file, tmp, ',');
				if (tmp == tmp1) break;
				file.seekg(274, ios::cur);
			}
			break;
		}
		file.seekg(855, ios::cur);
	}
	for (int i = 1; i <= 13; i++)
	{
		getline(file, tmp, ',');
		if (tmp.find(tmp1) != -1)
		{
			file.seekp(-21, ios::cur);
			file << "                    ";
			return;
		}
	}
	getline(file, tmp);
	file.close();
}
void createListCourse_of_a_student_in_the_class(string des_address)
{
	stringstream ss(AcademicYear);
	string year;
	getline(ss, year, '-');
	int num = stoi(year);
	ofstream fileout(des_address);
	for (int i = 0; i < 4; i++)
	{
		fileout << num + i << '-' << num + i + 1 << endl;
		for (int x = 1; x <= 3; x++)
		{
			fileout << "Semester " + to_string(x);
			for (int j = 0; j < 13; j++)
				fileout << ",                    ";
			if (x < 3) fileout << endl;
		}
		if (i < 3) fileout << endl;
	}
}
void createListCourse_of_students_in_the_class(ListStudent L, string des_address)
{
	while (L.Head != nullptr)
	{
		createListCourse_of_a_student_in_the_class(des_address + "/" + L.Head->sv.StudentID + ".csv");
		L.Head = L.Head->next;
	}
}

NodeS create_NodeS(Student infS)
{
	NodeS S = new NodeStudent;
	S->sv = infS;
	S->next = nullptr;
	return S;
}
ListStudent CreateInit_StuList()
{
	ListStudent L;
	L.Head = L.Tail = nullptr;
	return L;
}
Student importStu()
{
	Student S;
	cout << "   Student ID: ";  getline(cin, S.StudentID);
	cout << "   Last Name: "; getline(cin, S.Lname);
	cout << "   First Name: ";  getline(cin, S.Fname);
	string tmp;
	cout << "   Birth Day(dd/mm/yyyy): ";  getline(cin, tmp);
	stringstream ss(tmp);
	ss >> S.Birth.day;
	ss.ignore();
	ss >> S.Birth.month;
	ss.ignore();
	ss >> S.Birth.year;
	cout << "   Gender: ";  getline(cin, S.Gender);
	cout << "   Social ID: ";  getline(cin, S.SocialID);
	return S;
}
Student insert_1Stu_in_system(ofstream& fileout, string Class, string filename)
{
	Student S = importStu();
	int num = count(filename);
	fileout << endl << ++num;
	fileout << ',';
	w_inf_1sv(fileout, S);
	createAccount(S.StudentID, Class);
	return S;
}
void AddTail(ListStudent& L, Student infS)
{
	NodeS tmp = create_NodeS(infS);
	if (L.Head == nullptr) { L.Head = L.Tail = tmp; return; }
	L.Tail->next = tmp;
	L.Tail = tmp;
}
void DeleteList(ListStudent L)
{
	while (L.Head != nullptr)
	{
		NodeS tmp = L.Head->next;
		delete L.Head;
		L.Head = tmp;
	}
}

