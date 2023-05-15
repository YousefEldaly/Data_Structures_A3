//
// Created by Omar on 5/15/2023.
//

#ifndef BINARY_SEARCH_TREE_MINHEAP_H
#define BINARY_SEARCH_TREE_MINHEAP_H
#include <iostream>
#include <vector>
#include <map>
#include "Student.h"
using namespace std;

class MinHeap {
private:
    std::vector<Student*> students;
    int TreeSize;
    std::map<std::string, int> departments;
public:
    MinHeap();
    void heapify(int size, int i);
    void buildHeap(int size);
    void heapSort();
    void printDepartments();
    void PrintAll(std::vector<Student*> students);
    void insert(const Student &newstudent);
    void setDepartments(std::map<std::string, int> deps);
    void displayMenu();
    bool validID(int id);
    static bool validDep(const string& dep);
    bool found(int id);
};


#endif //BINARY_SEARCH_TREE_MINHEAP_H
