#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<sstream>
#include <filesystem>
#include<cstdio>
#include <conio.h>
#include <windows.h>

namespace fs = std::filesystem;

#include "Login.h"
#include "Staff.h"
#include"Course.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
using namespace std;

#define MaxStudent 50
const string file_inf_staff = "AceStaff\\inf_Staff.csv";
const string file_AccountStu = "Student\\UserAccount.csv";
const string file_AcademicYear = "AceStaff\\AcademicYear.csv";
const string file_FinalGrade_of_Courses = "Course\\FinalGrade _of_Courses";

const int maximum_pass = 15;

int move();
void gotoxy(int column, int line);
void print_Menu(string Menu[], int _numberOfItem);

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
};
struct Academic_staff {
	string staffID;
	string password;
	string Name;
	Date Birth;
	string Gender;
};
struct Semester {
	int semester;
	Date startDate, endDate;
};


struct Student {
	string StudentID;	
	string password;
	string Fname;
	string Lname;
	Date Birth;
	string Gender;
	string SocialID;
};
struct NodeStudent {
	Student sv;
	NodeStudent* next;
};
typedef NodeStudent* NodeS;
struct ListStudent {
	NodeS Head;
	NodeS Tail;
};

struct Course {
	string ID;
	string CourseName;
	string TeacherName;
	string ClassName;
	int credits;
	int maxStudent = MaxStudent;
	string dWeek;
	string session;
};
struct NodeCourse {
	Course data;
	NodeCourse* next;
};
typedef NodeCourse* NodeC;
struct ListCourse {
	NodeC head;
	NodeC tail;
};

struct score_of_student {
	string StudentID;
	string StuFullName;
	string TotalMark;
	string FinalMark;
	string MidtermMark;
	string OtherMark;
};
struct NodeScore {
	score_of_student data;
	NodeScore* next;
};
typedef NodeScore* NodeSC;
struct ListScore {
	NodeSC head;
	NodeSC tail;
};

void print_Menu(string Menu[], int _numberOfItem);
void gotoxy(int column, int line);
int move();
void erase_space(string& str);
stringstream export_filename(string str, int& n);
string Create_Folder(string nameNewFolder, string path);
bool copyfile(string source_file_path, string destination_directory_path);
void Create_trainingFolder(string path);
int count(string filename);
string seek_class(string ID);
stringstream save_folder_name(string path, int& n);

void loginsystem();
void Login(string& ID, string& Pass);
bool check_Login(string& ID, string& Pass, fstream& file, string filename);
bool find_posAccount(string ID, fstream& file, string filename);

string import_newPass(bool& isAcceptable);
void changePassword(fstream& file, string newPass);

void interface_Staff(Academic_staff& staff);
void rewrite_infStaff(fstream& file, Academic_staff& staff);
void r_inf_staff(fstream& file, Academic_staff& staff);
void export_AceStaff(Academic_staff& staff);

void interfaceStu(fstream& file, string filename, Student& S, string Class);
NodeS create_NodeS(Student infS);
ListStudent CreateInit_StuList();
Student importStu();
Student insert_1Stu_in_system(ofstream& fileout, string Class, string filename);
void AddTail(ListStudent& L, Student infS);
void DeleteList(ListStudent L);
void exportProfile_1_Stu(Student& S);
void interface_Mycourse(Student& S, string Class);
void seek_inf_accstu(fstream& file, Student& S);
Student r_inf_1stu(ifstream& filein);
void w_inf_1sv(ofstream& fileout, Student S);
void r_inf_class(ifstream& filein, ListStudent& L, string filename);
stringstream r_infCourse_of_Stu(string path, string CUR_YEAR, string SMT);
void print1Stu(Student& S);
void printStuList(ListStudent L);
void createAccount(string studentID, string Class);
void createListAccount(string Inf_file, string Class);
void createListCourse_of_a_student_in_the_class(string des_address);
void createListCourse_of_students_in_the_class(ListStudent L, string des_address);
bool createCourse_of_student_in_the_class(string StudentID, string CourseID, string ClassName);
void deleteCourse_of_student_in_the_class(string StudentID, string CourseID, string ClassName);

string type_of_training(string Class);

string interface_SELECT_ACADEMIC(stringstream& ss, int n);
Semester interfaceUpdateSemester();
void SEEK_AcademicYear(string& AcademicYear);
void update_AcademicYear(string& AcademicYear);
void r_cur_semester(Semester& Smt);
void print_cur_semester(Semester& Smt);
void updateSemester(Semester& NewSmt);
void Create_3Semester(string path);
string Select_Semester();

string interface_SELECT_CLASS(stringstream& ss, int n);
void interfacetypeoftraining(string& type);

void PrintDate(Date& D);
Date r_Date(string tmp);

void interface_list_course(string path);
void interface_AddCourse(string path);
bool interface_a_course(ListScore& LS, NodeC& C, string path, ListCourse& L_Course);
void input_identified_course(string& ID, string& name);
bool nameCourse(string codeCourse, string& name);
Course r_1_inf_course(ifstream& file_ListCourse);
void w_1_inf_course(ofstream& fileout, Course C);
void w_list_course(ofstream& fileout, ListCourse LC);
void printInfCourse(Course C);
void r_List_Course(ListCourse& L, string filename);
Course input_a_course();
void Create_fileListCourse(string path);
ListCourse Create_emptyListCourse();
NodeC CreateNodeC(Course& data);
void AddTail(ListCourse& L, Course& data);
void DeleteNode(ListCourse& LC, NodeC prev, NodeC cur);
void DeleteList(ListCourse LC);

void interface_updateScore(string path, ListScore LS, NodeC C);
void add1_Course_ofStu(Course C, stringstream& ss);
void add_1_Course_at_sstream(Course C, stringstream& ss);
void add_header_row(stringstream& ss);
void printInfCourse(Course C);
score_of_student r_1_stu_inCourse(ifstream& file);
NodeSC CreateNodeSC(score_of_student& data);
void AddTail(ListScore& L, score_of_student& data);
void DeleteNode(ListScore& LS, NodeSC prev, NodeSC cur);
void Create_ScoreBoardCourse(string path);
int cnt(ListScore LS);
bool Is_Full(ListScore tmpLSC, Course C);
bool Is_Exist(ListScore tmpLSC, string S);
ListScore r_ListScore(ifstream& file);
void w_1_stu_inCourse(ofstream& file, score_of_student SC);
void w_list_stu_inCourse(ListScore LS, ofstream& fileout);
void print_1_stu_inCourse(score_of_student SC);
void print_list_of_student_inCourse(ListScore LS);
void DeleteList(ListScore LS);

void interface_viewFinalMark(string StudentID, string Class);
void CourseName_Credit_Mark(string& mark, string& CourseName, string path, string StudentID);
void interface_viewFinalMark(string StudentID, string Class);
void update_FinalGrade_of_a_student(string filepath, score_of_student data);
void update_FinalGrade_of_student_list(string filepath, ListScore LS);
bool search_file_Course_FinalGrade(string folderPath, string& CourseID);
float cal_FinalGrade(score_of_student data);
void GPAtmp_GPAover(string StudentID, string& GPA_cur, string& GPAover);


