//
// Created by Omar on 5/15/2023.
//

#include <algorithm>
#include "MinHeap.h"

MinHeap::MinHeap() {
    TreeSize = 0;
}
void MinHeap::setDepartments(map<string, int> deps) {
    this->departments = std::move(deps);
}

void MinHeap::heapify(int size, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int min = i;
    if (left < size && students[left]->getGpa() < students[min]->getGpa()) {
        min = left;
    }
    if (right < size && students[right]->getGpa() < students[min]->getGpa()) {
        min = right;
    }
    if (min != i) {
        std::swap(students[i], students[min]);
        heapify(size, min);
    }
}

void MinHeap::buildHeap(int size) {
    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapify(size, i);
    }
}

void MinHeap::heapSort() {
    buildHeap(students.size());

    for (int i = students.size() - 1; i > 0; i--) {
        std::swap(students[0], students[i]);
        heapify(i, 0);
    }

}

void MinHeap::printDepartments() {
    for (const auto& department : departments) {
        cout << department.first << " " << department.second << " Students\n";
    }
}

void MinHeap::PrintAll(std::vector<Student*> students) {
    cout << "print " << TreeSize << " students" << endl;
    std::reverse(students.begin(), students.end());
    for (int i = 0; i < students.size(); i++) {
        std::cout << "[" << students[i]->getId() << "," << students[i]->getName() << "," << students[i]->getGpa() << ","
                  << students[i]->getDepartment() << "]" << std::endl;
    }
}

void MinHeap::insert(const Student& new_student) {
    students.push_back(new Student(new_student));  // Add the new student to the vector
    TreeSize++;  // Increase the size of the heap
    departments[new_student.getDepartment()]++; // increase the number of students per department

    int i = TreeSize - 1;
    while (i != 0 && students[(i - 1) / 2]->getGpa() > students[i]->getGpa()) {
        std::swap(students[i], students[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    buildHeap(students.size());
}
void MinHeap::displayMenu() {
    bool flag = true;
    while (flag) {

        int choice;
        std::cout << "Choose one of the following options: " << std::endl <<
                  "1. Add Student" << endl <<
                  "2. Print All (sorted by gpa)" << endl <<
                  "3. Back to main menu" << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                int id;
                float gpa;
                string dep, name;
                cout << "Enter the student details:" << endl;
                cout << "ID: ";
                cin >> id;
                while (!validID(id)) {
                    cout << "Invalid ID, please try again: ";
                    cin >> id;
                }
                cout << "Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "GPA: ";
                cin >> gpa;
                cout << "Department: [DS, CS, IS, AI]" << endl;
                cin >> dep;
                while (!validDep(dep)) {
                    cout << "Invalid Department, please try again: ";
                    cin >> dep;
                }
                Student new_student = *new Student(name, dep, gpa, id);
                insert(new_student);
                break;
            }
            case 2: {
                heapSort();
                PrintAll(students);
                printDepartments();
                break;
            }
            case 3: {
                flag = false;
                break;
            }
        }
    }
}
bool MinHeap::validID(int id) {
    if (id < 0 || id > 100 || found(id)) {
        return false;
    } else {
        return true;
    }
}

bool MinHeap::validDep(const string& dep) {
    if (dep == "CS" || dep == "IS" || dep == "DS" || dep == "AI") {
        return true;
    } else {
        return false;
    }
}

bool MinHeap::found(int id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->getId() == id)
            return true;
    }
    return false;
}

