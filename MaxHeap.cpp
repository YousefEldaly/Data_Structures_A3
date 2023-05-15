#include "MaxHeap.h"

MaxHeap::MaxHeap() {
    TreeSize = 0;
}
void MaxHeap::heapify(int size, int i) {
    int left = 2*i + 1;
    int right = 2*i +2;
    int max = i;
    if (left < size && students[left]->getGpa() > students[max]->getGpa()) {
        max = left;
    }
    if (right < size && students[right]->getGpa() > students[max]->getGpa()) {
        max = right;
    }
    if (max != i) {
        std::swap(students[i], students[max]);
        heapify(size, max);
    }
}

void MaxHeap::buildHeap(int size) {
    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapify(size, i);
    }
}
void MaxHeap::heapSort() {
    buildHeap(students.size());

    for (int i = students.size() - 1; i > 0; i--) {
        std::swap(students[0], students[i]);
        heapify(i, 0);
    }
}
void MaxHeap::printDepartments(){
    for (auto & department : departments) {
        cout << department.first <<" " << department.second << " Students\n" ;
    }
}
void MaxHeap::PrintAll(std::vector<Student*> students) {
    cout << "print " << TreeSize << " students" << endl;
    for (int i = students.size()-1; i >= 0; i--) {
        std::cout << "[" << students[i]->getId() << "," << students[i]->getName() << "," << students[i]->getGpa() << ","
                  << students[i]->getDepartment() << "]" << std::endl;
    }
    //cout << std::endl;
}
void MaxHeap::insert(const Student& new_student) {
    students.push_back(new Student(new_student));  // Add the new student to the vector
    TreeSize++;  // Increase the size of the heap
    departments[new_student.getDepartment()]++;

    int i = TreeSize - 1;
    while (i != 0 && students[(i - 1) / 2]->getGpa() < students[i]->getGpa()) {
        std::swap(students[i], students[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    buildHeap(students.size());
}

void MaxHeap::setDepartments(std::map<std::string, int> deps) {
    this->departments = std::move(deps);
}

void MaxHeap::displayMenu() {
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
                cout << "id:";
                cin >> id;
                while (!validID(id)) {
                    cout << "Invalid ID, Please try again.\n";
                    cout << "id:";
                    cin >> id;
                }
                cout << "Name:";
                cin.ignore();
                getline(cin, name);
                cout << "GPA:";
                cin >> gpa;
                while(!validGPA(gpa)){
                    cout << "Invalid GPA, Please try again.\n";
                    cout << "GPA: ";
                    cin >> gpa;
                }
                cout << "Department: [DS, CS, IS, AI]\n";
                cin >> dep;
                while (!validDep(dep)) {
                    cout << "Invalid Department, Please try again.\n";
                    cout << "Department: [DS, CS, IS, AI]\n";
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
bool MaxHeap::validID(int id){
    if (id < 0 || id > 100 || found(id)){
        return false;
    }else{
        return true;
    }
}
bool MaxHeap::validDep(const string& dep){
    if (dep == "CS" ||dep == "IS" || dep == "DS"||dep == "AI"){
        return true;
    }else{
        return false;
    }
}

bool MaxHeap::validGPA(float gpa){
    if(gpa >= 0.0 && gpa <= 4.0)
        return true;
    return false;
}

bool MaxHeap::found(int id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->getId() == id)
            return true;
    }
    return false;
}


