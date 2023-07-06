#include"Global.h"
extern string AcademicYear;
extern Semester CUR_SMT;

void print_Menu(string Menu[], int _numberOfItem)
{
	for (int i = 0; i < _numberOfItem; i++) {

		gotoxy(3, i);
		cout << Menu[i];
	}
}
void gotoxy(int column, int line)

{

	COORD coord;

	coord.X = column;

	coord.Y = line;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
int move() {

	char c = getch();

	if ((int)c == -32) c = getch();

	switch ((int)c) {

	case 80:
		return 1; //cout << "Xuong";

	case 72:
		return 2; //cout << "Len";

	case 77:
		return 3; //cout << "Phai";       

	case 75:
		return 4; //cout << "Trai";

	case 27:
		return 8; //Nut ESC thoat

	case 13:
		return 5; //Nut Enter

	default:
		return 0; //cout << "Sai";

	}

}
void erase_space(string& str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
}
string import_newPass(bool &isAcceptable)
{
	string tmp;
	cin >> tmp; 
	if(tmp.length() <= maximum_pass) isAcceptable = true;
	return tmp;
}
void changePassword(fstream& file, string newPass)
{
	file.seekp(1, SEEK_CUR);
	file.seekp(-1, SEEK_CUR);
	file << newPass;
	for(int i = 1; i <= (maximum_pass - newPass.length()); i++)
		file << " ";
}
void SEEK_AcademicYear(string& AcademicYear)
{
	ifstream filein;
	filein.open(file_AcademicYear, ios::in);
	filein >> AcademicYear;
	filein.close();
}
void update_AcademicYear(string& AcademicYear)
{
	string space = "          ";
	stringstream ss(AcademicYear);
	int year;
	ss >> year;
	AcademicYear = to_string(year + 1) + "-" + to_string(year + 2);
	ofstream fileout;
	fileout.open(file_AcademicYear, ios::trunc | ios::out);
	fileout << AcademicYear<<endl;
	fileout << "Semester 1," << space << ',' << space << endl;
	fileout << "Semester 2," << space << ',' << space << endl;
	fileout << "Semester 3," << space << ',' << space;
	fileout.close();
}
void r_cur_semester(Semester& Smt)
{
	string space = "          ";
	ifstream filein;
	filein.open(file_AcademicYear, ios::in);
	string tmp;
	filein >> tmp;
	int x = 0;
	while (!filein.eof())
	{
		filein >> tmp >> x;
		filein.ignore();
		getline(filein, tmp, ',');
		if (tmp == space)
		{
			Smt.semester = x - 1;
			filein.close();
			return;
		}
		stringstream ss(tmp);
		ss >> Smt.startDate.day;
		ss.ignore();
		ss >> Smt.startDate.month;
		ss.ignore();
		ss >> Smt.startDate.year;
		getline(filein, tmp);
		ss.clear();
		ss.str("");
		ss << tmp;
		ss >> Smt.endDate.day;
		ss.ignore();
		ss >> Smt.endDate.month;
		ss.ignore();
		ss >> Smt.endDate.year;
	}
	filein.close();
	Smt.semester = 3;
}
void updateSemester(Semester& NewSmt)
{
	fstream file;
	file.open(file_AcademicYear, ios::out | ios::in);
	file.seekp(11, SEEK_SET);
	string tmp = "Semester " + to_string(NewSmt.semester);
	while (!file.eof())
	{
		string tmp1;
		getline(file, tmp1, ',');
		if (tmp1 == tmp)
		{
			file.seekp(-1, SEEK_CUR);
			file.seekp(1, SEEK_CUR);
			file << setw(2) << setfill('0') << right << NewSmt.startDate.day << '/';
			file << setw(2) << setfill('0') << right << NewSmt.startDate.month << '/';
			file << setw(4) << setfill('0') << right << NewSmt.startDate.year << ',';
			file << setw(2) << setfill('0') << right << NewSmt.endDate.day << '/';
			file << setw(2) << setfill('0') << right << NewSmt.endDate.month << '/';
			file << setw(4) << setfill('0') << right << NewSmt.endDate.year;
			return;
		}
		else getline(file, tmp1);
	}
	file.close();
}
void print_cur_semester(Semester& Smt)
{
	cout << "   Academic Year: " << AcademicYear << endl;
	cout << "   Semester: " << Smt.semester << endl;
	cout << "   Start Date: ";
	PrintDate(Smt.startDate);
	cout << endl;
	cout << "   End Date: ";
	PrintDate(Smt.endDate);
}

stringstream export_filename(string str, int& n)
{
	stringstream ss;
	// Đường dẫn đến thư mục cần đọc tên các tệp.
	fs::path directory_path(str);
	if (fs::is_empty(directory_path)) return ss;
	// Kiểm tra xem đường dẫn đến thư mục có tồn tại hay không.
	if (fs::is_directory(directory_path)) {
		// Duyệt qua tất cả các tệp trong thư mục và in ra tên của chúng.
		for (const auto& entry : fs::directory_iterator(directory_path)) {
			if (fs::is_regular_file(entry)) 
			{
				string str = entry.path().filename().string();
				ss << str.substr(0, str.length() - 4) << " ";
				n++;
			}
		}
	}
	return ss;
}
bool search_file_Course_FinalGrade(string folderPath, string& CourseID)
{
	fs::path directory_path(folderPath);
	if (fs::is_empty(directory_path)) return false;
	// Kiểm tra xem đường dẫn đến thư mục có tồn tại hay không.
	if (fs::is_directory(directory_path)) {
		for (const auto& entry : fs::directory_iterator(directory_path)) {
			string tmp = entry.path().filename().string();
			int index = int(tmp.find(CourseID));
			if (index != -1)
			{
				CourseID = tmp.substr(index);
				return true;
			}
		}
	}
	return false;
}
string Create_Folder(string nameNewFolder, string path)
{
	fs::create_directory(path + "\\" + nameNewFolder);
	return path + "\\" + nameNewFolder;
}
bool copyfile(string source_file_path, string destination_directory_path)
{
	ifstream filein(source_file_path, ios::binary);
	if (!filein.is_open()) return false;
	ofstream fileout(destination_directory_path, ios::binary);
	if (!fileout.is_open()) return false;
	char x;
	while (filein.read(&x, 1))
	{
		fileout.write(&x, 1);
	}
	filein.close();
	fileout.close();
	return true;
}

void PrintDate(Date& D)
{
	cout << setw(2) << right << setfill('0') << D.day << "/";
	cout << setw(2) << right << setfill('0') << D.month << "/";
	cout << setw(4) << right << setfill('0') << D.year;
}
Date r_Date(string tmp)
{
	Date D;
	stringstream ss(tmp);
	ss >> D.day;
	ss.ignore();
	ss >> D.month;
	ss.ignore();
	ss >> D.year;
	return D;
}

void Create_trainingFolder(string path)
{
	Create_Folder("APCS", path);
	Create_Folder("Courses for students have been summarized", path + "\\APCS");
	Create_Folder("VP", path);
	Create_Folder("Courses for students have been summarized", path +"\\VP");
	Create_Folder("CTT", path);
	Create_Folder("Courses for students have been summarized", path + "\\CTT");
	Create_Folder("CLC", path);
	Create_Folder("Courses for students have been summarized", path + "\\CLC");
}
void Create_3Semester(string path) {
	string str;
	str = Create_Folder("Semester 1", path);
	Create_fileListCourse(str);
	Create_Folder("ScoreboardCourses", str);
	str = Create_Folder("Semester 2", path);
	Create_fileListCourse(str);
	Create_Folder("ScoreboardCourses", str);
	str = Create_Folder("Semester 3", path);
	Create_fileListCourse(str);
	Create_Folder("ScoreboardCourses", str);
}
int count(string filename)
{
	ifstream filein(filename, ios::in);
	string tmp;
	getline(filein, tmp);
	int num = 0;
	while (!filein.eof())
	{
		getline(filein, tmp);
		num++;
	}
	filein.close();
	return num;
}
string seek_class(string ID)
{
	string tmp;
	ifstream filein(file_AccountStu, ios::in);
	while (filein.good())
	{
		getline(filein, tmp, ',');
		if (tmp == ID)
		{
			getline(filein, tmp, ',');
			break;
		}
		getline(filein, tmp);
	}
	if (filein.good()) getline(filein, tmp);
	filein.close();
	return tmp;
}
stringstream save_folder_name(string path, int &n)
{
	stringstream ss;
	if (fs::exists(path) && fs::is_directory(path)) {
		for (const auto& entry : fs::directory_iterator(path)) {
			if (fs::is_directory(entry)) {
				ss << entry.path().filename().string() << " ";
				n++;
			}
		}
	}
	return ss;
}