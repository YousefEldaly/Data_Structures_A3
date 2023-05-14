#include <utility>
#include "iostream"
#include "Student.h"
using namespace std;

class BSTNode{
public:
    Student student;
    BSTNode* left, *right;
    explicit BSTNode(Student student){
        this->student = std::move(student);
        left = right = nullptr;
    }

};

class BST{
private:
    BSTNode *root;
    int treeSize{};
public:
    BST(){
        this->root = nullptr;
        this->treeSize = 0;
    }

    int size() const{
        return treeSize;
    }


    bool found(int id) {
        BSTNode *p = root;
        while (p != nullptr) {
            if (id == p->student.getId())
                return true;
            else if (id < p->student.getId()) {
                p = p->left;
            } else {
                p = p->right;
            }
        }
        return false;
    }




    void insert(const Student& student){
        if(found(student.getId())){
            cout<<"Student already exists"<<endl;
            return;
        }
        treeSize++;
        auto *node = new BSTNode(student);
        if(root == nullptr){
            root = node;
            return;
        }
        BSTNode *p = root, *prev = root;
        while(p != nullptr){
            prev = p;
            if(student.getId() > p->student.getId())
                p = p->right;
            else
                p = p->left;
        }
        if (student.getId() > prev->student.getId()) {
            prev->right = node;
        } else
            prev->left = node;
    }


    void printInorder(BSTNode* node)
    {
        if (node == nullptr)
            return;

        printInorder(node->left);

        cout << "[" << node->student.getId() <<"," <<
        node->student.getName() <<"," <<
        node->student.getDepartment() <<"," <<
        node->student.getGpa() <<"]\n";

        printInorder(node->right);
    }

    void print(){
        BSTNode* p = root;
        if (p == nullptr)
            return;
        printInorder(p);
    }


};

