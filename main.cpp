#include <iostream>
#include <fstream>
#include "BST.cpp"
using namespace std;


int main() {
    // create tree
    auto bst= new BST();


    // read file
    ifstream myFile("E:\\Desktop\\Assests\\Data_Structures_A3\\Students.txt");
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

    //test bst
    bst->print();


}