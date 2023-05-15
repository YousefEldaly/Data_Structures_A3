#ifndef BINARY_SEARCH_TREE_MAXHEAP_H
#define BINARY_SEARCH_TREE_MAXHEAP_H

#include <iostream>
#include <vector>
#include <map>
#include "Student.h"
using namespace std;

class MaxHeap {
private:
    std::vector<Student*> students;
    int TreeSize;
    std::map<std::string, int> departments;

public:
    MaxHeap();

    void heapify(int size, int i);
    void buildHeap(int size);
    void heapSort();
    void printDepartments();
    void PrintAll(std::vector<Student*> students);
    void insert(const Student &newstudent);
    void setDepartments(std::map<std::string, int> deps);
    void displayMenu();
    bool validID(int id);
    bool validGPA(float gpa);
    static bool validDep(const string& dep);
    bool found(int id);
};

#endif

