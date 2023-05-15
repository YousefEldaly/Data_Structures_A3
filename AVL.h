//
// Created by Yusuf Aldaly on 5/15/2023.
//

#ifndef TREES_AVL_H
#define TREES_AVL_H
#include "Student.h"
using namespace std;

// : student{student}, left{LeftTree}, right{RightTree}, height{height} { }
// : student{student}, left{LeftTree}, right{RightTree}, height{height} { }
class AvlNode{
public:
    Student student;
    AvlNode *left, *right;
    int height;

    AvlNode(const Student &student, AvlNode *left_node, AvlNode *right_node, int height = 0)
            : student{student}, left{left_node}, right{right_node}, height{height} { }
    explicit AvlNode()=default;
};


class AVL {
    /*struct AvlNode
    {
        Student student;
        AvlNode *left, *right;
        int height;

        AvlNode(const Student &student, AvlNode *left_node, AvlNode *right_node, int height = 0)
                : student{student}, left{left_node}, right{right_node}, height{height} { }
        AvlNode(){
            left = nullptr;
            right = nullptr;
        }


        AvlNode(Student &&student, AvlNode *left_node, AvlNode *right_node, int height = 0)
                : student{student}, left{left_node}, right{right_node}, height{height} { }

    };*/
    AvlNode *root;
    int treeSize;
    map<string,int> departments;
    static const int ALLOWED_IMBALANCE = 1;

    int height(AvlNode *node) const;
    void insert(const Student &student, AvlNode *&node);
    void balance(AvlNode *&node);
    void rotateWithLeftChild(AvlNode *&node2);
    void rotateWithRightChild(AvlNode *&node2);
    void doubleWithLeftChild(AvlNode *&node3);
    void doubleWithRightChild(AvlNode *&node3);
    void remove(const int student_id, AvlNode *&node);
    void printInOrder(AvlNode *node);
    AvlNode* findMin(AvlNode *node);
    bool found(int id);
    bool validID(int id);
    bool validDep(string& dep);
    bool validGPA(float gpa);
    void search(int id);
    void printDepartments();

public:
    void insert(const Student &student);
    void remove(const int student_id);
    void print();
    void setDepartments(map<string, int> deps);
    void displayMenu();




};


#endif //TREES_AVL_H
