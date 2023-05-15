#include <iostream>
#include <fstream>
#include <map>
#include "BST.h"
#include "AVL.h"
#include "MinHeap.h"
#include "MaxHeap.h"
using namespace std;


int main() {
    // create a map on departments
    map<string,int> departments;

    // create tree
    auto bst = new BST();
    auto avl = new AVL();
    auto min = new MinHeap();
    auto max = new MaxHeap();

    // read file
    ifstream myFile(R"(D:\Study\Level 2\Data_Stuctures\Assignments\Assignment3\Data_Structures_A3\Students.txt)");
    int cnt = 0;
    string line;
    Student stud;
    while (getline(myFile, line)) {
        if (!cnt) {
            cnt++;
            continue;
        }
        switch (cnt % 4) {
            case 0:
                stud.setDepartment(line);
                departments[line]++;
                // insertion
                min->insert(stud);
                max->insert(stud);
                avl->insert(stud);
                bst->insert(stud);
                break;
            case 1:
                stud.setId(stoi(line));
                break;
            case 2:
                stud.setName(line);
                break;
            case 3:
                stud.setGpa(stof(line));
                break;
        }
        cnt++;
    }
    myFile.close();



    // main menu
    bool flag = true;
    while (flag){
        cout << "Choose Data Structure:\n"
                "1. BST\n"
                "2. AVL\n"
                "3. Min Heap\n"
                "4. Max Heap\n"
                "5. Exit Program\n";
        int option;
        cin >> option;
        switch (option) {
            case 1: {
                // first set departments
                // IMPORTANT FOR ALL CASES
                bst->setDepartments(departments);
                bst->displayMenu();
                break;
            }
            case 2:
                avl->setDepartments(departments);
                avl->displayMenu();
                break;
            case 3: {
                min->setDepartments(departments);
                min->displayMenu();
                break;
            }
            case 4:{
                max->setDepartments(departments);
                max->displayMenu();
                break;
            }
            case 5:
                flag = false;
                break;
        }
    }

}