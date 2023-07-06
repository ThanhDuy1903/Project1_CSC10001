#include"Course.h"
extern string AcademicYear;
extern Semester CUR_SMT;

ListCourse Create_emptyListCourse()
{
	ListCourse L;
	L.head = L.tail = nullptr;
	return L;
}
NodeC CreateNodeC(Course& data)
{
	NodeC tmp = new NodeCourse;
	tmp->data = data;
	tmp->next = nullptr;
	return tmp;
}
void AddTail(ListCourse& L, Course& data)
{
	NodeC tmp = CreateNodeC(data);
	if (L.head == nullptr) { L.head = L.tail = tmp; return; }
	L.tail->next = tmp;
	L.tail = tmp;
}

void DeleteNode(ListScore& LS, NodeSC prev, NodeSC cur)
{
	if (prev == nullptr)
	{
		NodeSC tmp = LS.head->next;
		delete LS.head;
		LS.head = tmp;
		return;
	}
	if (cur == LS.tail)
	{
		delete LS.tail;
		prev->next = nullptr;
		LS.tail = prev;
		return;
	}
	prev->next = cur->next;
	delete cur;
}
ListScore Create_emptyListScore()
{
	ListScore L;
	L.head = L.tail = nullptr;
	return L;
}
score_of_student InputSCstu(ListScore LS)
{
	system("cls");
	cout << "   ------------------------ Input Information Student ------------------------\n\n";
	string StuID, FullName;
	while (true)
	{
		fstream file;
		cout << "   Input student ID: ";
		getline(cin, StuID);
		if (Is_Exist(LS, StuID)) cout << "   The student registered for this course. Again!";
		else if (find_posAccount(StuID, file, file_AccountStu) == false)
		{
			cout << "   The student ID isn't exist. Again!";
			file.close();
		}
		else break;
		cout << endl;
	}
	cout << "\n   Input Full Name: ";
	getline(cin, FullName);
	score_of_student tmp;
	tmp.StudentID = StuID;
	tmp.StuFullName = FullName;
	tmp.FinalMark = tmp.MidtermMark = tmp.OtherMark = tmp.TotalMark = "    ";
	return tmp;
}
NodeSC CreateNodeSC(score_of_student& data)
{
	NodeSC tmp = new NodeScore;
	tmp->data = data;
	tmp->next = nullptr;
	return tmp;
}
int cnt(ListScore LS)
{
	int cnt = 0;
	while (LS.head != nullptr)
	{
		cnt++;
		LS.head = LS.head->next;
	}
	return cnt;
}
void AddTail(ListScore& L, score_of_student& data)
{
	NodeSC tmp = CreateNodeSC(data);
	if (L.head == nullptr) { L.head = L.tail = tmp; return; }
	L.tail->next = tmp;
	L.tail = tmp;
}

float cal_FinalGrade(score_of_student data)
{
	float tmp_Other = stof(data.OtherMark);
	float tmp_Final = stof(data.FinalMark);
	float tmp_Midterm = stof(data.MidtermMark);
	float tmp_Total = stof(data.TotalMark);
	float FinalGrade = float(tmp_Other + tmp_Final * 0.5 + tmp_Midterm * 0.3 + tmp_Total * 0.2);
	if (FinalGrade >= 10) return 10.0;
	return round(FinalGrade * 10) / 10;
}
void update_FinalGrade_of_a_student(string filepath, score_of_student data)
{
	fstream file(filepath);
	string tmp;
	float mark = cal_FinalGrade(data);
	getline(file, tmp);
	getline(file, tmp);
	while (!file.eof())
	{
		getline(file, tmp, ',');
		if (tmp == data.StudentID)
		{
			file.seekp(-1, ios::cur);
			file.seekp(1, ios::cur);
			if (mark == 10) file << "10.0";
			else file << fixed << setprecision(2) << mark;
			return;
		}
		getline(file, tmp);
	}
	file.clear();
	file.seekp(0, ios::end);
	file << endl << data.StudentID << ",";
	if (mark == 10) file << "10.0";
	else file << fixed << setprecision(2) << mark;
	file.close();
}
void update_FinalGrade_of_student_list(string filepath, ListScore LS)
{
	while (LS.head != nullptr)
	{
		update_FinalGrade_of_a_student(filepath, LS.head->data);
		LS.head = LS.head->next;
	}
}
bool Is_Full(ListScore tmpLSC, Course C)
{
	return cnt(tmpLSC) == C.maxStudent;
}
bool Is_Exist(ListScore tmpLSC, string S)
{
	while (tmpLSC.head != nullptr)
	{
		if (tmpLSC.head->data.StudentID == S) return true;
		tmpLSC.head = tmpLSC.head->next;
	}
	return false;
}
void DeleteNode(ListCourse& LC, NodeC prev, NodeC cur)
{
	if (prev == nullptr)
	{
		NodeC tmp = LC.head->next;
		delete LC.head;
		LC.head = tmp;
		return;
	}
	if (cur == LC.tail)
	{
		delete LC.tail;
		prev->next = nullptr;
		LC.tail = prev;
		return;
	}
	prev->next = cur->next;
	delete cur;
}
void DeleteList(ListCourse LC)
{
	while (LC.head != nullptr)
	{
		NodeC tmp = LC.head->next;
		delete LC.head;
		LC.head = tmp;
	}
}
void DeleteList(ListScore LS)
{
	while (LS.head != nullptr)
	{
		NodeSC tmp = LS.head->next;
		delete LS.head;
		LS.head = tmp;
	}
}

bool nameCourse(string codeCourse, string& name)
{
	if (codeCourse == "CSC10001") { name = "Nhap mon lap trinh"; return true; }
	if (codeCourse == "CSC10002") { name = "Ky thuat lap trinh"; return true; }
	if (codeCourse == "CSC10003") { name = "Phuong phap lap trinh huong doi tuong";  return true; }
	if (codeCourse == "CSC10004") { name = "Cau truc du lieu va giai thuat"; return true; }
	if (codeCourse == "CSC10006") { name = "Co so du lieu"; return true; }
	if (codeCourse == "CSC10007") { name = "He dieu hanh"; return true; }
	if (codeCourse == "CSC10008") { name = "Mang may tinh"; return true; }
	if (codeCourse == "CSC10009") { name = "He thong may tinh"; return true; }
	if (codeCourse == "CSC13002") { name = "Nhap mon cong nghe phan mem"; return true; }
	if (codeCourse == "CSC14003") { name = "Co so tri tue nhan tao"; return true; }
	if (codeCourse == "CSC11004") { name = "Mang may tinh nang cao"; return true; }
	if (codeCourse == "CSC15001") { name = "An ninh may tinh"; return true; }
	if (codeCourse == "BAA00001") { name = "Anh van 1"; return true; }
	if (codeCourse == "BAA00002") { name = "Anh van 2"; return true; }
	if (codeCourse == "BAA00003") { name = "Anh van 3"; return true; }
	if (codeCourse == "BAA00004") { name = "Anh van 4"; return true; }
	if (codeCourse == "BAA00007") { name = "Phuong phap luan sang tao"; return true; }
	if (codeCourse == "MTH00003") { name = "Vi tich phan 1B"; return true; }
	if (codeCourse == "MTH00004") { name = "Vi tich phan 2B"; return true; }
	if (codeCourse == "MTH00030") { name = "Dai so tuyen tinh"; return true; }
	if (codeCourse == "MTH00040") { name = "Xac xuat thong ke"; return true; }
	if (codeCourse == "MTH00041") { name = "Toan roi rac"; return true; }
	if (codeCourse == "MTH00050") { name = "Toan hoc to hop"; return true; }
	if (codeCourse == "PHY00001") { name = "Vat li dai cuong 1"; return true; }
	if (codeCourse == "PHY00002") { name = "Vat li dai cuong 2"; return true; }
	if (codeCourse == "PHY00081") { name = "Thuc hanh vat li dai cuong"; return true; }
	return false;
}
void Create_fileListCourse(string path)
{
	ofstream fileout(path + "\\ListCourse.csv");
	fileout << "ID,Course Name,Class Name,Teacher Name,Credits,Maximum Number of Students,Day Week,Session";
	fileout.close();
}
Course r_1_inf_course(ifstream& file_ListCourse)
{
	Course C;
	getline(file_ListCourse, C.ID, ',');
	getline(file_ListCourse, C.CourseName, ',');
	getline(file_ListCourse, C.ClassName, ',');
	getline(file_ListCourse, C.TeacherName, ',');
	file_ListCourse >> C.credits;
	file_ListCourse.ignore();
	file_ListCourse >> C.maxStudent;
	file_ListCourse.ignore();
	getline(file_ListCourse, C.dWeek, ',');
	getline(file_ListCourse, C.session);
	return C;
}
void r_List_Course(ListCourse& L, string filename)
{
	ifstream filein(filename, ios::in);
	if (!filein.is_open()) return;
	string tmp;
	getline(filein, tmp);
	while (!filein.eof())
	{
		Course C_tmp = r_1_inf_course(filein);
		AddTail(L, C_tmp);
	}
	filein.close();
}
Course input_a_course()
{
	Course C;
	while (true)
	{
		cout << "   Course ID: ";
		getline(cin, C.ID);
		if (C.ID.length() == 8) break;
		cout << "   Course ID have to have key. Again!.\n";
	}
	cout << "   Course Name: "; getline(cin, C.CourseName);
	cout << "   Class Name: ";  getline(cin, C.ClassName);
	cout << "   Teacher Name: "; getline(cin, C.TeacherName);
	cout << "   Credits number: ";  cin >> C.credits;
	cout << "   Maximum student: "; cin >> C.maxStudent;
	cin.ignore();
	cout << "   Day of the week((MON / TUE / WED / THU / FRI / SAT): ";  getline(cin, C.dWeek);
	cout << "   The session(S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): "; getline(cin, C.session);
	return C;
}
void w_1_inf_course(ofstream& fileout, Course C)
{
	fileout << C.ID << ',' << C.CourseName << ',' << C.ClassName << ',' << C.TeacherName << ',' << C.credits;
	fileout << ',' << C.maxStudent << ',' << C.dWeek << ',' << C.session;
}
void w_list_course(ofstream& fileout, ListCourse LC)
{
	fileout << "ID,Course Name,Class Name,Teacher Name,Credits,Maximum Number of Students,Day Week,Session";
	while (LC.head != nullptr)
	{
		fileout << endl;
		w_1_inf_course(fileout, LC.head->data);
		LC.head = LC.head->next;
	}
}
void printInfCourse(Course C)
{
	system("cls");
	cout << "   ---------------- INFORMATION OF THIS COURSE ----------------\n\n";
	cout << "   ID: " << C.ID << endl;
	cout << "   Name Course: " << C.CourseName << endl;
	cout << "   Class Course: " << C.ClassName << endl;
	cout << "   Teacher: " << C.TeacherName << endl;
	cout << "   Number Credits: " << C.credits << endl;
	cout << "   Maximum number of Student: " << C.maxStudent << endl;
	cout << "   Schedule: " << C.dWeek << "-" << C.session;
}
void add1_Course_ofStu(Course C, stringstream& ss)
{
	ss << setw(15) << setfill(' ') << left << C.ID;
	ss << setw(45) << setfill(' ') << left << C.CourseName;
	ss << setw(20) << setfill(' ') << left << C.ClassName;
	ss << setw(10) << setfill(' ') << left << C.credits;
	ss << C.dWeek << "-" << C.session;
}
void add_1_Course_at_sstream(Course C, stringstream& ss)
{
	ss << setw(15) << setfill(' ') << left << C.ID;
	ss << setw(45) << setfill(' ') << left << C.CourseName;
	ss << C.ClassName;
}
void add_header_row(stringstream& ss)
{
	ss << setw(15) << setfill(' ') << left << "Course ID";
	ss << setw(45) << setfill(' ') << left << "Course Name";
	ss << "Class Name";
}
void Create_ScoreBoardCourse(string path)
{
	ofstream fileout(path);
	fileout << "NO,Student ID,Student Full Name,Total Mark,Final Mark,Midterm Mark,Other Mark";
	fileout.close();
}
void input_identified_course(string& ID, string& name)
{
	cout << "   Input Course ID: ";
	getline(cin, ID);
	cout << "   Input Class Name: ";
	getline(cin, name);
}
score_of_student r_1_stu_inCourse(ifstream& file)
{
	score_of_student SC;
	string tmp;
	getline(file, tmp, ',');
	getline(file, SC.StudentID, ',');
	getline(file, SC.StuFullName, ',');
	getline(file, SC.TotalMark, ',');
	getline(file, SC.FinalMark, ',');
	getline(file, SC.MidtermMark, ',');
	getline(file, SC.OtherMark);
	return SC;
}
ListScore r_ListScore(ifstream& file)
{
	ListScore L_SC = Create_emptyListScore();
	string tmp;
	getline(file, tmp);
	while (!file.eof())
	{
		score_of_student S = r_1_stu_inCourse(file);
		AddTail(L_SC, S);
	}
	return L_SC;
}
void w_1_stu_inCourse(ofstream& file, score_of_student SC)
{
	file << SC.StudentID << ',' << SC.StuFullName << ',' << SC.TotalMark << ',' << SC.FinalMark << ',' << SC.MidtermMark;
	file << ',' << SC.OtherMark;
}
void w_list_stu_inCourse(ListScore LS, ofstream& fileout)
{
	fileout << "No, Student ID, Student Full Name, Total Mark, Final Mark, Midterm Mark, Other Mark";
	int cnt = 0;
	while (LS.head != nullptr)
	{
		fileout << endl << ++cnt << ',';
		w_1_stu_inCourse(fileout, LS.head->data);
		LS.head = LS.head->next;
	}
}
void print_1_stu_inCourse(score_of_student SC)
{
	cout << setw(17) << setfill(' ') << left << SC.StudentID << setw(25) << setfill(' ') << left << SC.StuFullName;
	cout << setw(15) << setfill(' ') << SC.TotalMark << setw(15) << setfill(' ') << SC.FinalMark;
	cout << setw(15) << setfill(' ') << SC.MidtermMark << SC.OtherMark;
}
void print_list_of_student_inCourse(ListScore LS)
{
	system("cls");
	cout << "   ---------------- LIST OF STUDENTS OF THIS COURSE ----------------\n\n";
	int cnt = 0;
	cout << "   " << setw(5) << setfill(' ') << left << "No" << setw(17) << setfill(' ') << left << "Student ID" << setw(25) << setfill(' ') << left << "Student Full Name";
	cout << setw(15) << setfill(' ') << "Total Mark" << setw(15) << setfill(' ') << "Final Mark";
	cout << setw(15) << setfill(' ') << "Midterm Mark" << "Other Mark";
	while (LS.head != nullptr)
	{
		cout << endl << "   " << setw(5) << setfill(' ') << left << ++cnt;
		print_1_stu_inCourse(LS.head->data);
		LS.head = LS.head->next;
	}
}

void interface_updateScore(string path, ListScore LS, NodeC C)
{
	system("cls");
	int line = 1; //Vị trí dòng của menu
	string UPDATE_SCORE[4];
	UPDATE_SCORE[0] = "----------------------- UPDATE SCORE -----------------------";
	UPDATE_SCORE[1] = "Import the scoreboard of the course";
	UPDATE_SCORE[2] = "A student";
	UPDATE_SCORE[3] = "Back";
	print_Menu(UPDATE_SCORE, 4);
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
				switch (line)
				{
				case 2:
				{
					system("cls");
					cout << "   ----------------------- UPDATE SCORE OF A STUDENT -----------------------\n\n";
					ListScore hold_on = LS;
					string tmpID = "";
					cout << "   Input Student ID: ";
					cin >> tmpID;
					while (LS.head != nullptr)
					{
						if (LS.head->data.StudentID == tmpID) break;
						LS.head = LS.head->next;
					}
					if (LS.head == nullptr)
					{
						cout << "   The Student ID haven't the course.\n";
						
						;
						break;
					}
					cout << "   CONFIRM: Press ESC to cancel or ENTER to update the scoreboard!";
					bool checkUpdate = false;
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) { checkUpdate = false; break; }
						if (c == 13) { checkUpdate = true; break; }
					}
					if (checkUpdate == false) break;
					system("cls");
					cout << "\n   *Input Mark:\n\n";
					cout << "   Total Mark: ";
					cin >> LS.head->data.TotalMark;
					cout << "   Midterm Mark: ";
					cin >> LS.head->data.MidtermMark;
					cout << "   Final Mark: ";
					cin >> LS.head->data.FinalMark;
					cout << "   Other Mark: ";
					cin >> LS.head->data.OtherMark;
					cin.ignore();
					ofstream fileout(path + "\\ScoreboardCourses" + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv", ios::out);
					w_list_stu_inCourse(hold_on, fileout);
					string tmp = C->data.ID;
					if (search_file_Course_FinalGrade(file_FinalGrade_of_Courses, tmp) == true)
						update_FinalGrade_of_a_student(file_FinalGrade_of_Courses + "\\" + tmp, LS.head->data);
					fileout.close();
					cout << "\n   SUCCESSFULLY!";
					Sleep(2000);
					break;
				}
				case 1:
				{
					system("cls");
					cout << "   ----------------------- UPDATE SCOREBOARD -----------------------\n\n";
					string tmp;
					cout << "   Input source file: ";
					getline(cin, tmp);
					cout << "   CONFIRM: Press ESC to cancel or ENTER to update scoreboard!";
					bool checkUPDATE = false;
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) { checkUPDATE = false; break; }
						if (c == 13) { checkUPDATE = true; break; }
					}
					if (checkUPDATE == false) break;
					if (copyfile(tmp, path + "\\ScoreboardCourses" + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv") == false)
					{
						cout << "\n   Updating is failed!";
					}
					else
					{
						ifstream file(path + "\\ScoreboardCourses" + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv", ios::in | ios::out);
						DeleteList(LS);
						LS = r_ListScore(file);
						file.close();
						string tmp1 = C->data.ID;
						if (search_file_Course_FinalGrade(file_FinalGrade_of_Courses, tmp1) == true)
							update_FinalGrade_of_student_list(file_FinalGrade_of_Courses + "\\" + tmp1, LS);
						cout << "\n   Sucessfully!";
					}
					Sleep(2000);
					break;
				}
				case 3: return;
				}
				break;
			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(UPDATE_SCORE, 4);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}
void interface_AddCourse(string path)
{
	system("cls");
	int line = 1; //Vị trí dòng của menu
	string Staff[4];
	Staff[0] = "----------------------- ADD COURSE -----------------------";
	Staff[1] = "1. Add by file csv";
	Staff[2] = "2. Input by keyboard";
	Staff[3] = "3. Back";
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
				switch (line)
				{
				case 1:
				{
					system("cls");
					cout << "   ----------------------- ADD COURSE BY FILE CSV -----------------------\n\n";
					string tmp;
					cout << "   Input path of file csv: ";
					getline(cin, tmp);
					cout << "   CONFIRM: Press ESC to cancel or ENTER to continue";
					bool checkRemove = false;
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) { checkRemove = false; break; }
						if (c == 13) { checkRemove = true; break; }
					}
					if (copyfile(tmp, path + "\\ListCourse.csv") == false)
					{
						cout << "\n   ADDING COURSES IS FAILED!";
					}
					ListCourse LC = Create_emptyListCourse();
					r_List_Course(LC, path + "\\ListCourse.csv");
					while (LC.head != nullptr)
					{
						Create_ScoreBoardCourse(path + "\\ScoreboardCourses\\" + LC.head->data.ID + "-" + LC.head->data.ClassName + ".csv");
						LC.head = LC.head->next;
					}
					cout << "   Sucessfully!";
					DeleteList(LC);
					Sleep(2000);
					break;
				}
				case 2:
				{
					system("cls");
					cout << "   ----------------------- ADD A COURSE BY KEYBOARD -----------------------\n\n";
					Course C = input_a_course();
					cout << "   CONFIRM: Press ESC to cancel or ENTER to continue";
					bool checkRemove = false;
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) { checkRemove = false; break; }
						if (c == 13) { checkRemove = true; break; }
					}
					ofstream fileout(path + "\\ListCourse.csv", ios::app);
					fileout << endl;
					w_1_inf_course(fileout, C);
					fileout.close();
					Create_ScoreBoardCourse(path + "\\ScoreboardCourses\\" + C.ID + "-" + C.ClassName + ".csv");
					cout << "   Successfully!";
					Sleep(2000);
					break;
				}
				case 3: return;
				}
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
bool interface_a_course(ListScore& LS, NodeC& C, string path, ListCourse& L_Course)
{
	system("cls");
	int line = 1; //Vị trí dòng của menu
	string A_Course[11];
	A_Course[0] = "----------------------- COURSE -----------------------";
	A_Course[1] = "Upload a CSV file, containing a list of students enrolled in the course";
	A_Course[2] = "View the list of students in the course";
	A_Course[3] = "Information of the course";
	A_Course[4] = "Update information of the course";
	A_Course[5] = "Add a student to the course";
	A_Course[6] = "Remove a student from the course";
	A_Course[7] = "Delete the course";
	A_Course[8] = "Export a list of students in a course to a CSV file";
	A_Course[9] = "Update score board";
	A_Course[10] = "Back";
	print_Menu(A_Course, 11);
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
				if (line >= 11) line = 1;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 1) line = 10;
				break;
			}
			case 5:
			{
				checkEnter = true;
				switch (line)
				{
				case 1:
				{
					DeleteList(LS);
					system("cls");
					cout << "   ---------------- UPLOAD A LIST OF STUDNETS ENROLLED IN THE COURSE ----------------\n\n";
					string source;
					cout << "   Input source file: ";
					getline(cin, source);
					cout << "   CONFIRM: Press ESC to cancel or ENTER to upload!";
					bool checkUPDATE = false;
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) { checkUPDATE = false; break; }
						if (c == 13) { checkUPDATE = true; break; }
					}
					if (checkUPDATE == false) break;
					ifstream filein(source);
					string str;
					getline(filein, str);
					while (filein.good())
					{
						score_of_student S;
						getline(filein, str, ',');
						getline(filein, S.StudentID, ',');
						getline(filein, S.StuFullName);
						S.FinalMark = S.MidtermMark = S.OtherMark = S.TotalMark = "    ";
						AddTail(LS, S);
						createCourse_of_student_in_the_class(S.StudentID, C->data.ID, C->data.ClassName);
					}
					filein.close();
					ofstream fileout(path + "\\ScoreboardCourses" + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv", ios::out);
					w_list_stu_inCourse(LS, fileout);
					break;
				}
				case 2:
					print_list_of_student_inCourse(LS);
					cout << "\n\n   Press the ESC to go back!";
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) break;
					}
					break;
				case 3:
					printInfCourse(C->data);
					cout << "\n\n   Press the ESC to go back!";
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) break;
					}
					break;
				case 4:
				{
					system("cls");
					cout << "   ---------------- UPDATE COURSE INFORMATION ----------------\n\n";
					NodeC tmp = new NodeCourse;
					tmp->data.ClassName = C->data.ClassName;
					tmp->data.ID = C->data.ID;
					tmp->data.CourseName = C->data.CourseName;
					cout << "   Teacher Name: "; getline(cin, tmp->data.TeacherName);
					cout << "   Credits number: ";  cin >> tmp->data.credits;
					cout << "   Maximum student: "; cin >> tmp->data.maxStudent;
					cin.ignore();
					cout << "   Day of the week((MON / TUE / WED / THU / FRI / SAT): ";  getline(cin, tmp->data.dWeek);
					cout << "   The session( S1(07:30), S2(09:30), S3(13:30) and S4(15:30) ): "; getline(cin, tmp->data.session);
					cout << "\n\n    Press ENTER to update or ESC to cancel!";
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27)
						{
							delete tmp;
							break;
						}
						if (c == 13)
						{
							NodeC prev = nullptr, cur = L_Course.head;
							while (true)
							{
								if (cur == C) break;
								prev = cur;
								cur = cur->next;
							}
							if (prev != nullptr) prev->next = tmp;
							else L_Course.head = tmp;
							tmp->next = C->next;
							delete C;
							C = tmp;
							ofstream fileout(path + "\\ListCourse.csv", ios::out);
							w_list_course(fileout, L_Course);
							fileout.close();
							break;
						}
					}
					break;
				}
				case 5:
				{
					system("cls");
					cout << "   ------------------------ ADD A STUDENT TO THE COURSE ------------------------\n\n";
					if (Is_Full(LS, C->data)) cout << "Class is full!\n";
					else
					{
						score_of_student S = InputSCstu(LS);
						cout << "\n   CONFIRM: Press ESC to cancel or ENTER to add the student!";
						bool checkAdd = false;
						while (true)
						{
							char c = getch();
							if ((int)c == -32) c = getch();
							if (c == 27) { checkAdd = false; break; }
							if (c == 13) { checkAdd = true; break; }
						}
						if (checkAdd == false) break;
						AddTail(LS, S);
						ofstream fileout(path + "\\ScoreboardCourses" + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv", ios::out);
						w_list_stu_inCourse(LS, fileout);
						if (createCourse_of_student_in_the_class(S.StudentID, C->data.ID, C->data.ClassName) == false)
							cout << "\n   Students have reached the maximum number of registered subjects in the current semester(13 subjects)!";
						else cout << "\n   Adding the student to the course is successfull!";
						fileout.close();
					}
					Sleep(2000);
					break;
				}
				case 6:
				{
					system("cls");
					cout << "   ------------------------ REMOVE A STUDENT FROM THE COURSE ------------------------\n\n";
					string tmp;
					cout << "   Input Student ID: ";
					getline(cin, tmp);
					NodeSC prev = nullptr, cur = LS.head;
					while (cur != nullptr)
					{
						if (cur->data.StudentID == tmp)
						{
							DeleteNode(LS, prev, cur);
							break;
						}
						prev = cur;
						cur = cur->next;
					}
					if (cur == nullptr) {
						cout << "\n   The Student ID haven't the course!";
						Sleep(2000);
						break;
					}
					cout << "\n   CONFIRM: Press ESC to cancel or ENTER to remove";
					bool checkRemove = false;
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) { checkRemove = false; break; }
						if (c == 13) { checkRemove = true; break; }
					}
					if (checkRemove == false) break;
					ofstream fileout(path + "\\ScoreboardCourses" + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv", ios::out);
					w_list_stu_inCourse(LS, fileout);
					deleteCourse_of_student_in_the_class(tmp, C->data.ID, C->data.ClassName);
					fileout.close();
					cout << "\n   Successfully removed the student from the course!";
					Sleep(2000);
					break;
				}
				case 7:
				{
					system("cls");
					cout << "   ------------------------ DELETE THE COURSE ------------------------\n\n";
					cout << "   CONFIRM: Press ESC to cancel or ENTER to delete";
					bool checkDelete = false;
					while (true)
					{
						char c = getch();
						if ((int)c == -32) c = getch();
						if (c == 27) { checkDelete = false; break; }
						if (c == 13) { checkDelete = true; break; }
					}
					if (checkDelete == false) break;
					NodeSC tmp1 = LS.head;
					while (tmp1 != nullptr)
					{
						deleteCourse_of_student_in_the_class(tmp1->data.StudentID, C->data.ID, C->data.ClassName);
						tmp1 = tmp1->next;
					}
					string filename = path + "\\ScoreboardCourses" + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv";
					if (remove(filename.c_str()) != 0)
						cout << "Error.\n";
					NodeC prev = nullptr, cur = L_Course.head;
					while (cur != nullptr)
					{
						if (cur->data.ClassName == C->data.ClassName && cur->data.ID == C->data.ID)
						{
							DeleteNode(L_Course, prev, cur);
							ofstream fileout(path + "\\ListCourse.csv", ios::out);
							w_list_course(fileout, L_Course);
							fileout.close();
							break;
						}
						prev = cur;
						cur = cur->next;
					}
					cout << "\n   Successfully deleted the course!";
					Sleep(2000);
					return true;
				}
				case 8:
				{
					system("cls");
					cout << "   ----------------------- Export a list of students in the course to a CSV file -----------------------\n\n";
					string tmp;
					cout << "\n   Input folder: ";
					getline(cin, tmp);
					if (copyfile(path + "\\ScoreboardCourses" + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv", tmp + "\\" + C->data.ID + "-" + C->data.ClassName + ".csv") == false)
					{
						cout << "\n   Updating is failed!";
					}
					else cout << "\n   Sucessfully!";
					break;
				}
				case 9:
					interface_updateScore(path, LS, C);
					break;
				case 10: return false;
				}
			}
			break;
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(A_Course, 11);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
	return false;
}
void interface_list_course(string path)
{
	system("cls");
	ListCourse L_Course = Create_emptyListCourse();
	r_List_Course(L_Course, path + "\\ListCourse.csv");
	NodeC tmp_Course = L_Course.head;
	string arr_str[102], arr_Name[102][2];
	arr_str[0] = "----------------------- LIST COURSE -----------------------";
	stringstream ss;
	add_header_row(ss);
	getline(ss, arr_str[1]);
	int i = 2;
	while (tmp_Course != nullptr)
	{
		ss.clear();
		arr_Name[i][0] = tmp_Course->data.ID;
		arr_Name[i][1] = tmp_Course->data.ClassName;
		add_1_Course_at_sstream(tmp_Course->data, ss);
		getline(ss, arr_str[i++]);
		tmp_Course = tmp_Course->next;
	}
	int line = 2;
	print_Menu(arr_str, i);
	cout << "\n   Press the ESC to go back";
	gotoxy(0, line);
	cout << (char)4;
	while (true) {
		if (kbhit()) {
			bool checkEnter = false;
			bool checkDelete = false;
			int x = move();
			gotoxy(0, line);
			cout << " "; //Xóa con trỏ ở vị trí cũ
			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= i) line = 2;
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
				ifstream file(path + "\\ScoreboardCourses" + "\\" + arr_Name[line][0] + "-" + arr_Name[line][1] + ".csv", ios::in | ios::out);
				ListScore LS = r_ListScore(file);
				file.close();
				NodeC tmp1 = L_Course.head;
				while (tmp1 != nullptr)
				{
					if (tmp1->data.ID == arr_Name[line][0] && tmp1->data.ClassName == arr_Name[line][1])
					{
						break;
					}
					tmp1 = tmp1->next;
				}
				checkDelete = interface_a_course(LS, tmp1, path, L_Course);
				DeleteList(LS);
				break;
			}
			case 8: DeleteList(L_Course); return;
			}
			if (checkEnter == true)
			{
				if (checkDelete == false)
				{
					system("cls");
					print_Menu(arr_str, i);
					cout << "\n   Press the ESC to go back";
				}
				else if (checkDelete == true)
				{
					i = 2;
					tmp_Course = L_Course.head;
					while (tmp_Course != nullptr)
					{
						ss.clear();
						arr_Name[i][0] = tmp_Course->data.ID;
						arr_Name[i][1] = tmp_Course->data.ClassName;
						add_1_Course_at_sstream(tmp_Course->data, ss);
						getline(ss, arr_str[i++]);
						tmp_Course = tmp_Course->next;
					}
					line = 2;
					system("cls");
					print_Menu(arr_str, i);
					cout << "\n   Press the ESC to go back";
				}
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
	DeleteList(L_Course);
}
string Select_Semester()
{
	int option;
	cout << "   Semester(1,2,3): ";
	cin >> option;
	cin.ignore();
	if (option == 1) return "Semester 1";
	else if (option == 2) return "Semester 2";
	return "Semester 3";
}
void interfaceManageCourses()
{
	system("cls");
	int n = 0, n1 = 0;
	stringstream ss = save_folder_name("Student", n);
	string ACADEMIC_YEAR = interface_SELECT_ACADEMIC(ss, n);
	if (ACADEMIC_YEAR == "Back") return;
	string str = "Course\\" + ACADEMIC_YEAR.substr(2, 2);
	cout << endl << endl << endl << endl;
	string path = str + "\\" + Select_Semester();
	system("cls");
	int line = 1; //Vị trí dòng của menu
	string Course[4];
	Course[0] = "----------------------- COURSE -----------------------";
	Course[1] = "List of courses";
	Course[2] = "Add course to current semester";
	Course[3] = "Back";
	print_Menu(Course, 4);
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
				if (line < 1) line = 4 - 1;
				break;
			}
			case 5:
			{
				checkEnter = true;
				switch (line)
				{
				case 1:
				{
					interface_list_course(path);
					break;
				}
				case 2:
				{
					interface_AddCourse(path);
					break;
				}
				default: return;
				}
				break;
			}
			}
			if (checkEnter == true)
			{
				system("cls");
				print_Menu(Course, 4);
			}
			gotoxy(0, line);
			cout << (char)4;
		}
	}
}
void CourseName_Credit_Mark(string& mark, string& CourseName, string path, string StudentID)
{
	ifstream filein(path);
	getline(filein, CourseName);
	string tmp;
	getline(filein, tmp);
	while (filein.good())
	{
		getline(filein, tmp, ',');
		if (tmp == StudentID)
		{
			getline(filein, mark);
			break;
		}
		getline(filein, tmp);
	}
	filein.close();
}
void GPAtmp_GPAover(string StudentID, string& GPA_cur, string& GPAover)
{
	int over_credits_sum = 0, tmp_credits_sum = 0;
	float GPAcur_tmp = 0.0, GPAover_tmp = 0.0;
	bool check1 = false;
	bool check2 = false;
	bool check3 = false;
	string Class = seek_class(StudentID);
	for (int i = 0; i < 4; i++)
	{
		int year = 2000 + stoi(Class.substr(0, 2));
		string year_str = to_string(year + i) + "-" + to_string(year + i + 1);
		for (int j = 1; j <= 3; j++)
		{
			string SMT = "Semester " + to_string(j);
			stringstream ss1 = r_infCourse_of_Stu("Student/" + Class.substr(0, 2) + "/" + type_of_training(Class) + "/Courses for students have been summarized/" + Class + "/" + StudentID + ".csv", year_str, SMT);
			string tmp;
			if ((year_str == AcademicYear) && ("Semester " + to_string(CUR_SMT.semester) == SMT)) check1 = true;
			while (getline(ss1, tmp, '-'))
			{
				search_file_Course_FinalGrade("Course/FinalGrade _of_Courses", tmp);
				string mark = "", CourseName = "";
				int Credit = stoi(tmp.substr(tmp.length() - 5, 1));
				CourseName_Credit_Mark(mark, CourseName, "Course/FinalGrade _of_Courses/" + tmp, StudentID);
				if (mark == "")
				{
					getline(ss1, tmp, ',');
					continue;
				}
				else check2 = true;
				if (check1 == true)
				{
					tmp_credits_sum += Credit;
					GPAcur_tmp += stof(mark) * Credit;
					check3 = true;
				}
				over_credits_sum += Credit;
				GPAover_tmp += stof(mark) * Credit;
				getline(ss1, tmp, ',');
			}
			check1 = false;
		}
		if (check2 == false) return;
	}
	GPAover_tmp = float(round(GPAover_tmp * 10.0 / over_credits_sum) / 10);
	GPAover = to_string(GPAover_tmp).substr(0, 4);
	if (check3 == true)
	{
		GPAcur_tmp = float(round(GPAcur_tmp * 10.0 / tmp_credits_sum) / 10);
		GPA_cur = to_string(GPAcur_tmp).substr(0, 4);
	}
}
