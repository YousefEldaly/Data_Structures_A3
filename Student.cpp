#include "Student.h"


int Student::getId() const {
    return id;
}

void Student::setId(int id) {
    Student::id = id;
}

const string &Student::getName() const {
    return name;
}

void Student::setName(const string &name) {
    Student::name = name;
}

const string &Student::getDepartment() const {
    return department;
}

void Student::setDepartment(const string &department) {
    Student::department = department;
}

float Student::getGpa() const {
    return gpa;
}

void Student::setGpa(float gpa) {
    Student::gpa = gpa;
}
