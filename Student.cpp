#include "Student.h"

#include <utility>

Student::Student(string name, string dep, float gpa, int id) {
    this->id = id;
    this->name = std::move(name);
    this->department = std::move(dep);
    this->gpa = gpa;
}

Student::Student() {
    id = 0;
    name ="";
    department="";
    gpa=0.0;
}

void Student::printStudentInfo(){
    cout << "[" << id << "," << name << "," << department << ","<<gpa << "]\n" ;
}

int Student::getId() const {
    return id;
}

void Student::setId(int student_id) {
    Student::id = student_id;
}

const string &Student::getName() const {
    return name;
}

void Student::setName(const string &student_name) {
    Student::name = student_name;
}

const string &Student::getDepartment() const {
    return department;
}

void Student::setDepartment(const string &student_department) {
    Student::department = student_department;
}

float Student::getGpa() const {
    return gpa;
}

void Student::setGpa(float student_gpa) {
    Student::gpa = student_gpa;
}