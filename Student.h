#include "iostream"
using namespace std;

class Student {

private:
    int id;
    string name;
    string department;
    float gpa;
public:
    Student(string name,string dep,float gpa,int id);
    Student();
    int getId() const;
    void setId(int student_id);
    const string &getName() const;
    void setName(const string &student_name);
    const string &getDepartment() const;
    void setDepartment(const string &student_department);
    float getGpa() const;
    void setGpa(float student_gpa);
    void printStudentInfo();

};


