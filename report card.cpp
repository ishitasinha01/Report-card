#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<iomanip>
using namespace std;
class Permission;
class Grade;
class Exams;
class Student;

class Student
{
public:

    int student_id;
    string student_name;
    int student_mobile;
    string student_email;
    string student_address;
    int student_year;
    string student_password;
    string student_username;
    int student_college_id;
    Grade *g;
    int p_marks,c_marks,m_marks,e_marks,cs_marks;
    float per;
    char grade;
    int std;
    friend class Grade;
    Student();

    Student(int student_id)
    {
        this->student_id=student_id;
    }

    void addStudent()
    {
        cout<<"Enter student details"<<endl;
        cout<<"Name::";
        fflush(stdin);
        getline(cin,student_name);
        cout<<"Student_id::";
        fflush(stdin);
        cin>>student_id;
        fflush(stdin);
        cout<<"Year::";
        fflush(stdin);
        cin>>student_year;
        cout<<"Mobile::";
        fflush(stdin);
        cin>>student_mobile;
        cout<<"Email::";
        fflush(stdin);
        getline(cin,student_email);
        cout<<"Address::";
        fflush(stdin);
        getline(cin,student_address);;
    }
    void showdata()
    {
        cout<<"\n\n\t***************\t\n";
        cout<<"\t|Name::"<<student_name<<endl;
        cout<<"\t|Student ID::"<<student_id<<endl;
        cout<<"\t|Year::"<<student_year<<endl;
        cout<<"\t|Mobile number::"<<student_mobile<<endl;
        cout<<"\t|Email::"<<student_email<<endl;
        cout<<"\t|Address::"<<student_address<<endl;
        cout<<"\t***************\t\n";
    }
    int getrollno()
    {
        return student_id;
    }
    void calculate()
    {
        per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
        if(per>=60)
            grade='A';
        else if(per>=50 && per<60)
            grade='B';
        else if(per>=33 && per<50)
            grade='C';
        else
            grade='F';
    }

    void addMarks()
    {
        showdata();

        cout<<"\nEnter The marks in Data Structure out of 100 : ";
        cin>>p_marks;
        cout<<"\nEnter The marks in Coa out of 100 : ";
        cin>>c_marks;
        cout<<"\nEnter The marks in Technical Communication out of 100 : ";
        cin>>m_marks;
        cout<<"\nEnter The marks in Electrical out of 100 : ";
        cin>>e_marks;
        cout<<"\nEnter The marks in Python  out of 100 : ";
        cin>>cs_marks;

        try{
            if(p_marks<0 || c_marks<0 || m_marks<0 || e_marks<0 || cs_marks<0){
                throw "-ve";
            }
            if(p_marks>100 || c_marks>100 || m_marks>100 || e_marks>100 || cs_marks>100){
                throw 100;
            }
            else{
                calculate();
            }
        }

        catch(const char *str){
            cout<<"Any of the marks cannot be negative.";
        }
        catch(int x){
            cout<<"Any of the marks must not exceed 100.";
        }

    }
    void showMarks()
    {
        showdata();

        cout<<"\n\n\t***************\t\n";
        cout<<"\n\t|Marks in Data Structure : "<<p_marks;
        cout<<"\n\t|Marks in Coa : "<<c_marks;
        cout<<"\n\t|Marks in Technical Communication : "<<m_marks;
        cout<<"\n\t|Marks in Electrical : "<<e_marks;
        cout<<"\n\t|Marks in  Python :"<<cs_marks;
        cout<<"\n\t|Percentage of student is  :"<<setprecision(2)<<per;
        cout<<"\n\t|Grade of student is :"<<grade;
        cout<<"\n\t***************\t\n";
    }
    void mark_sheet()
    {
        system("cls");
        cout<<"\n\t\t\t Galgotias College Of Engineering and Technology \n"<<endl;
        showMarks();
    }

};

Student :: Student(){
    p_marks=97;
    c_marks=89;
    m_marks=90;
    e_marks=92;
    cs_marks=100;
    grade='A';
    per=93.6;
}

Student st;
fstream record;
void write_student()
{
    record.open("student.txt",ios::out|ios::app);
    st.addStudent();
    record.write((char*)&st,sizeof(Student));
    record.close();
    cout<<"\n\nstudent record Has Been Created ";
    getch();
}
void display_all()
{
    system("cls");
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    record.open("student.txt",ios::in);
    while(record.read((char*)&st,sizeof(Student)))
    {
        st.showdata();
        cout<<"\n\n====================================\n";
        getch();
    }
    record.close();
    getch();
}


void modify_student()
{
    int no,found=0;
    system("cls");
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The roll number of student";
    cin>>no;
    record.open("student.txt",ios::in|ios::out);
    while(record.read((char*)&st,sizeof(Student)) && found==0)
    {
        if(st.getrollno()==no)
        {
            st.showdata();
            cout<<"\nPlease Enter The New Details of student"<<endl;
            st.addStudent();
            int pos=-1*sizeof(st);
            record.seekp(pos,ios::cur);
            record.write((char*)&st,sizeof(Student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    record.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}
void display_sp(int n)
{
    int flag=0;
    record.open("student.txt",ios::in);
    while(record.read((char*)&st,sizeof(Student)))
    {
        if(st.getrollno()==n)
        {
            system("cls");
            st.showdata();
            flag=1;
        }
    }
    record.close();
    if(flag==0)
        cout<<"\n\nrecord does not exist";
    getch();
}

void delete_Student()
{
    int no;
    system("cls");
    cout<<"\n\n\n\tDelete Record";
    record.open("student.txt",ios::in|ios::out);
    fstream fp3;
    fp3.open("Temp1.txt",ios::out);
    record.seekg(0,ios::beg);
    fp3.close();
    record.close();
    remove("student.txt");
    rename("Temp1.txt","student.txt");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
}

class Permission
{
public:
protected:
    string permission_id;
    string password;
public:

    Exams *ex;
    Grade *gd;
    Student *stud;
    int permission_status;


    Permission(string permission_id,string password)
    {
        this->permission_id=permission_id;
        this->password=password;
    }
    int checkPermission(string id,string password)
    {
        try
        {
            if(id==permission_id && password==this->password)
            {
                permission_status=1;
                return permission_status;
            }
            else
            {
                throw "Wrong ID or Password!";
                return 0;
            }
        }
        catch(const char*)
        {
            cout<<"Wrong ID or Password!"<<endl;
        }
        return 0;

    }
};

Permission p1("1234","ABCD");
fstream log1;
int admin_login(string id,string pass)
{
    if(p1.checkPermission(id,pass)==1)
    {
        return 1;
    }
    else
    {
        cout<<"Failed to login"<<endl;
        return 0;
    }
}

Permission p2("4321","PQRS");

int student_login(string id,string pass)
{
    if(p2.checkPermission(id,pass)==1)
    {
        return 1;
    }
    else
    {
        cout<<"Failed to login"<<endl;
        return 0;
    }
}

class Exam
{
public:
    int exam_id;
    string exam_type;
    string exam_name;
    string exam_date;
    int exam_student_id;

    void addExam()
    {
        cout<<"Exam Id::";
        fflush(stdin);
        cin>>exam_id;
        cout<<"Exam Type::";
        fflush(stdin);
        getline(cin,exam_type);
        cout<<"Exam name::";
        fflush(stdin);
        getline(cin,exam_name);
        cout<<"Exam Date::";
        fflush(stdin);
        getline(cin,exam_date);
    }
    void Examdetails()
    {
        cout<<"Exam Id::"<<exam_id<<endl;
        cout<<"Exam Type::"<<exam_type<<endl;
        cout<<"Exam Name::"<<exam_name<<endl;
        cout<<"Exam Date::"<<exam_date<<endl;
    }
    int getexamId()
    {
        return exam_id;

    }
};
Exam ex;
fstream exam;
void write_exam()
{
    exam.open("exam.txt",ios::out|ios::app);
    ex.addExam();
    exam.write((char*)&ex,sizeof(Exam));
    exam.close();
    cout<<"\n\nExam record Has Been Created ";
    getch();
}

void exam_details()
{
    system("cls");
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    exam.open("exam.txt",ios::in);
    while(exam.read((char*)&ex,sizeof(Exam)))
    {
        ex.Examdetails();
        cout<<"\n\n====================================\n";
        getch();
    }
    exam.close();
    getch();
}
void modify_exam()
{
    int no,found=0;
    system("cls");
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Id of exam::";
    cin>>no;
    exam.open("exam.txt",ios::in|ios::out);
    while(exam.read((char*)&ex,sizeof(Exam)) && found==0)
    {
        if(ex.getexamId()==no)
        {
            ex.Examdetails();
            cout<<"\nPlease Enter The New Details of Exams"<<endl;
            ex.addExam();
            int pos=-1*sizeof(ex);
            exam.seekp(pos,ios::cur);
            exam.write((char*)&ex,sizeof(Exam));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    exam.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}


class Grade:public Exam
{
public:
    int grade_id;
    string grade_name;
    string grade_description;
    string grade_type;
    int grade_student_id;
    Student *s[50];
    string subject[50];
    int no_of_subject;
    int subject_id[50];
    int marks[50];
    friend class Student;

    void addSubject()
    {
        cout<<"\t\tAdd subject"<<endl;

        cout<<"\tEnter number of subjects you wanted to add"<<endl;
        cin>>no_of_subject;
        for(int i=1; i<no_of_subject+1; i++)
        {
            cout<<"Enter Subject "<<i<<"::";
            cout<<"Subject Id:: ";

            cin>>subject_id[i];
            cout<<"Subject Name::";
            fflush(stdin);
            getline(cin,subject[i]);
        }
        cout<<endl;

    }
    void showSubject()
    {
        for(int i=1; i<no_of_subject+1; i++)
        {

            cout<<"#"<<subject[i]<<"\t\t"<<"["<<subject_id[i]<<"]"<<endl;
        }


    }
    int retSubId(int a)
    {
        return subject_id[a];
    }

    void addGrade()
    {

        int m;
        cout<<"Marks obtained"<<endl;
        showSubject();
        cout<<subject[1];
}
};
fstream sub;
Grade gd;

void write_subject()
{
    sub.open("subject.txt",ios::out|ios::app);
    gd.addSubject();
    sub.write((char*)&gd,sizeof(Grade));
    sub.close();
    cout<<"\n\nExam record Has Been Created ";
    getch();
}

void subject_details()
{
    system("cls");
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    sub.open("subject.txt",ios::in);
    int flag=0;


    while(sub.read((char*)&gd,sizeof(Grade)))
    {
        gd.showSubject();
        flag=1;
        cout<<"\n\n====================================\n";

    }
    if(flag==0)
    {
        cout<<"No record found"<<endl;
    }

    sub.close();
    getch();
}

void delete_subject()
{
    int no;
    system("cls");
    cout<<"\n\n\n\tDelete Record";
    sub.open("subject.txt",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.txt",ios::out);
    sub.seekg(0,ios::beg);
    fp2.close();
    sub.close();
    remove("subject.txt");
    rename("Temp.txt","subject.txt");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
}

fstream grade;

void write_Grade(int n)
{
    int flag=0;
    record.open("student.txt",ios::in);
    while(record.read((char*)&st,sizeof(Student)))
    {
        if(st.getrollno()==n)
        {
            system("cls");
            st.addMarks();
            st.mark_sheet();
            flag=1;
        }
    }
    record.close();
    if(flag==0)
        cout<<"\n\nrecord does not exist";

}

void modify_marks()
{
    int no,found=0;
    system("cls");
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Id of exam::";
    fflush(stdin);
    cin>>no;
    record.open("student.txt",ios::in|ios::out);
    while(record.read((char*)&st,sizeof(Student)) && found==0)
    {
        if(st.getrollno()==no)
        {
            st.showMarks();
            cout<<"\nPlease Enter The New Details of Exams"<<endl;
            st.addMarks();
            int pos=-1*sizeof(st);
            record.seekp(pos,ios::cur);
            record.write((char*)&st,sizeof(Student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    record.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}
void display_marks(int n)
{
    int flag=0;
    record.open("student.txt",ios::in);
    while(record.read((char*)&st,sizeof(Student)))
    {
        if(st.getrollno()==n)
        {
            system("cls");
            st.mark_sheet();
            flag=1;
        }
    }
    record.close();
    if(flag==0)
        cout<<"\n\nrecord does not exist";
    getch();
}
void reportcard(int n)
{
    record.open("student.txt",ios::in);
    while(record.read((char*)&st,sizeof(Student)))
    {
        if(st.getrollno()==n)
        {
            system("cls");
            st.showMarks();
        }

    }

}

void studentEntryMenu()
{

    cout<<"\t**************\t\n";
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORDS";
    cout<<"\n\n\t6.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-5)\n";
    cout<<"\t**************\t\n";
}
void examinationEntryMenu()
{
    cout<<"\t**************\t\n";
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.ADD EXAM DETAILS";
    cout<<"\n\n\t2.DISPLAY EXAMS";
    cout<<"\n\n\t3.MODIFY EXAM DETAILS";
    cout<<"\n\n\t4.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-4) ";
    cout<<"\t**************\t\n";
}
void subject()
{
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.ADD SUBJECT";
    cout<<"\n\n\t2.DISPLAY SUBJECT";
    cout<<"\n\n\t3.DELETE SUBJECTS";
    cout<<"\n\n\t4.BACK TO MAIN MENU";

}
void Generate_mark_sheet()
{
    cout<<"\t**************\t\n";
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\n\t1.GENERATE STUDENT DETAILS";
    cout<<"\n\n\n\t2.GENERATE MARKSHEET";

    cout<<"\n\n\t3.BACK TO MAIN MENU";
    cout<<"\t**************\t\n";
}
void intro(){
    system("cls");


cout<<"\n\n\t\t****************************\n\n";
cout<<"\t\t\t\tStudent Report Card Management system\n\n\n";
cout<<"\t\tStudent report card system project in C++ is a simple console application built\n"
        "\t\twithout the use of graphics. In this project, users can perform typical reportcard \n"
        "\t\trelated functions like adding a new student record and displaying, modifying,editing\n"
        "\t\tand deleting it. File handling has been effectively used to perform all these. \n"
        "\t\tThis project will teach you how to use file handling in C++, add, read, display,\n"
        "\t\tsearch, modify and delete record from file.";
    cout<<"\n\n\t\t****************************\n\n";
    cout<<"\t\t*******\n";
    cout<<"\t\tContributions:-\n";
    cout<<"\t\t1.Ishita Sinha\n";
    
  
    cout<<"\t\t*******\n";

}

void mainmenu();

void menu1(){
    int b;
    cout<<"\n\n\t\t******************\t\t"<<endl;
    cout<<"\t\t\t1.Manage Students\n\t\t\t2.Manage Examinations\n\t\t\t3.Manage Papers\n\t\t\t4.Manage Result\n\t\t\t5.Go Back"<<endl;
    cout<<"\t\t******************\t\t"<<endl;
    cout<<"\t\t\t";
    cin>>b;
    system("cls");
    switch(b)
    {
    case 1:
    {
        studentEntryMenu();
        int k;
        cin>>k;
        if(k==1)
        {
            write_student();
        }
        if(k==2)
        {
            display_all();
        }
        if(k==3)
        {
            int q;
            cout<<"Enter Student ID ::";
            cin>>q;

            display_sp(q);
        }
        if(k==4)
        {
            modify_student();
        }
        if(k==5)
        {
            delete_Student();
        }
        if(k==6)
        {
            menu1();
        }
        else{
            cout<<"Wrong Input";
            menu1();
        }
    }
    case 2:
    {
        examinationEntryMenu();
        int q;
        cin>>q;

        if(q==1)
        {
            write_exam();
        }
        if(q==2)
        {
            exam_details();
        }
        if(q==3)
        {
            modify_exam();
        }
        if(q==4)
        {
            menu1();
        }
        else{
            cout<<"Wrong Input";
            menu1();
        }

    }
    case 3:
    {
        subject();
        int m;
        cin>>m;
        if(m==1)
        {
            write_subject();
        }
        if(m==2)
        {
            subject_details();
        }
        if(m==3)
        {
            delete_subject();
        }
        if(m==4)
        {
            menu1();
        }
        else{
            cout<<"Wrong Input";
            menu1();
        }


    }
    case 4:
    {
        Generate_mark_sheet();
        int r;
        cin>>r;
        if(r==1)
        {
            int h;
            cout<<"Enter Student Id"<<endl;
            fflush(stdin);
            cin>>h;
            write_Grade(h);

        }
        if(r==2)
        {
            int h;
            cout<<"Enter Student Id"<<endl;
            fflush(stdin);
            cin>>h;
            display_marks(h);
            ;
        }
        if(r==3){
            menu1();
        }
        else{
            cout<<"Wrong Input";
            menu1();
        }


    }
    case 5:
    {
        mainmenu();
    }
}
}

void menu2(){
            cout<<"\n\n\n\t\t******************\t\t"<<endl;
            cout<<"\t\t\t1.Student details\n\t\t\t2.Generate report card\n\t\t\t3.Go Back"<<endl;
            cout<<"\t\t******************\t\t"<<endl;
            int q;
            cin>>q;
            switch (q)
            {
            case 1:
            {
                int ch;
                cout<<"Enter you Student id"<<endl;
                int j;
                cin>>j;
                display_sp(j);
                cout<<"\nPress 0 to go back ";
                cin>>ch;
                if(ch==0){
                    menu2();
                }
            }


            case 2:
            {
                int ch;
                cout<<"Enter your Student id"<<endl;
                int k;
                cin>>k;
                reportcard(k);
                cout<<"\nPress 0 to go back ";
                cin>>ch;
                if(ch==0){
                    menu2();
                }
            }

            case 3:
            {
                mainmenu();
            }
            }
        }


void mainmenu(){
    start:
    int a;
    cout<<"\t\t*******************\n"<<endl;
    cout<<"\t\t\tGalgotias College of Engineering and Technology\n"<<endl;
    cout<<"\t\t*******************\n\n\n"<<endl;
    cout<<"\t\t\tWelcome to Student Report Card generator\n\n"<<endl;
    cout<<"\t\t\tChoose from following\n\n"<<endl;
    cout<<"\t\t\t\t\t1.Admin login \n\n\t\t\t\t\t2.Student login \n\n\t\t\t\t\t3.About us\n"<<endl;
    cout<<"\t\t\t";
    cin>>a;

    if(a==1)
    {
        string m;
        string n;
        cout<<"\t\t**********\n";
        cout<<"\t\t\tId:";
        fflush(stdin);
        getline(cin,m);
        cout<<"\t\t\tPassword:";
        fflush(stdin);
        getline(cin,n);
        cout<<"\t\t**********\n";


        if(admin_login(m,n)==1)
        {
            cout<<"\t\tYou have successfully logged into the system"<<endl;
            system("cls");

            menu1();

        }
        else
        {
            cout<<"please try again"<<endl;
        }


    }
    else if(a==2)
    {
        string m;
        string n;
        cout<<"\t\t**********\n";
        cout<<"\t\t\tId:";
        fflush(stdin);
        getline(cin,m);
        cout<<"\t\t\tPassword:";
        fflush(stdin);
        getline(cin,n);
        cout<<"\t\t**********\n";


        if(student_login(m,n)==1)
        {

            cout<<"\t\tYou have successfully logged into the system\n"<<endl;
            system("cls");
            menu2();
        }
        else
        {
            cout<<"please try again"<<endl;
        }
    }
    else if(a==3)
    {
        intro();

    }
    else
    {
        cout<<"Wrong input! Please choose again"<<endl;
    }

    getch();
    system("cls");
    goto start;
}

int main()
{
    mainmenu();
}







