#include <utility>
#include "BST.h"

BST::BST() {
    this->root = nullptr;
    this->treeSize = 0;
}
void BST::setDepartments(map<string, int> deps) {
    this->departments = std::move(deps);
}
void BST::printDepartments(){
    for (auto & department : departments) {
        cout << department.first <<" " << department.second << " Students\n" ;
    }
}

int BST::size() const {
    return treeSize;
}

bool BST:: found(int id) {
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

void BST::search(int id) {
    if (!found(id)) {
        cout << "Student is not found." << endl;
        return;
    }
    BSTNode *p = root;
    while (p != nullptr) {
        if (id == p->student.getId()) {
            cout << "Student is found.\n";
            p->student.printStudentInfo();
            return;
        } else if (id < p->student.getId()) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
}

void BST::insert(const Student &student) {
    if (found(student.getId())) {
        cout << "Student already exists" << endl;
        return;
    }

    treeSize++;
    auto *node = new BSTNode(student);
    departments[student.getDepartment()]++;

    if (root == nullptr) {
        root = node;
        return;
    }
    BSTNode *p = root, *prev = root;
    while (p != nullptr) {
        prev = p;
        if (student.getId() > p->student.getId())
            p = p->right;
        else
            p = p->left;
    }
    if (student.getId() > prev->student.getId()) {
        prev->right = node;
    } else
        prev->left = node;
}


void BST:: printInorder(BSTNode *node) {
    if (node == nullptr)
        return;

    printInorder(node->left);
    node->student.printStudentInfo();
    printInorder(node->right);
}

void BST:: print() {
    BSTNode *p = root;
    if (p == nullptr)
        return;
    printInorder(p);
}

void BST::remove(int id) {
    // Student doesn't exist
    if (!found(id)) {
        cout << "Value doesn't exist" << endl;
        return;
    }
    // Tree size = 1
    if (treeSize == 1) {
        departments[root->student.getDepartment()]--;
        delete root;
        root = nullptr;
        treeSize = 0;
        return;
    }
    auto *node = root, *prev = root;
    while (node->student.getId() != id) {
        prev = node;
        if (id > node->student.getId())
            node = node->right;
        else
            node = node->left;
    }
    // decrease all students
    treeSize--;
    // decrease the department students
    departments[node->student.getDepartment()]--;

    // Leaf Node (left = null & right null)
    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        // set prev node pointer null
        if (id > prev->student.getId())
            prev->right = nullptr;
        else
            prev->left = nullptr;
    }

        // Left != Null & Right = Null
    else if (node->left != nullptr && node->right == nullptr) {
        if (node == root)
            root = root->left;
        else if (id > prev->student.getId())
            prev->right = node->left;
        else
            prev->left = node->left;
        delete node;
    }

        // Left = Null & Right != Null
    else if (node->left == nullptr && node->right != nullptr) {
        if (node == root)
            root = root->right;
        else if (id > prev->student.getId())
            prev->right = node->right;
        else
            prev->left = node->right;
        delete node;
    } else if (node->left != nullptr && node->right != nullptr) {
        BSTNode *node2 = node, *prev2 = node;
        node2 = node2->right;
        while (node2->left != nullptr) {
            prev2 = node2;
            node2 = node2->left;
        }
        node->student = node2->student;
        delete node2;
        prev2->left = nullptr;
    }
}

bool BST::validID(int id){
    if (id < 0 || id > 100 || found(id)){
        return false;
    }else{
        return true;
    }
}
bool BST::validDep(string& dep){
    if (dep == "CS" ||dep == "IS" || dep == "DS"||dep == "AI" || dep == "IT"){
        return true;
    }else{
        return false;
    }
}
bool BST::validGPA(float gpa){
    if(gpa >= 0.0 && gpa <= 4.0)
        return true;
    return false;
}

void BST::displayMenu(){
    bool flag = true;
    while (flag) {
        cout << "\nChoose one of the following options:\n"
                "1. Add student\n"
                "2. Remove student\n"
                "3. Search student\n"
                "4. Print All (sorted by id)\n"
                "5. Return to main menu\n";
        int option; cin >> option;
        switch (option) {
            case 1: {
                int id;
                float gpa;
                string dep, name;
                cout << "id:";
                cin >> id;
                while (!validID(id)){
                    cout<<"Invalid ID, Please try again.\n";
                    cout<<"id:";
                    cin>>id;
                }
                cout << "Name:";
                cin.ignore();
                getline(cin,name);
                cout << "GPA:";
                cin >> gpa;
                while(!validGPA(gpa)){
                    cout << "Invalid GPA, Please try again.\n";
                    cout << "GPA: ";
                    cin >> gpa;
                }
                cout << "Department: [DS, CS, IS, AI]\n";
                cin >> dep;
                for (char & i : dep) {
                    i = toupper(i);
                }
                while (!validDep(dep)){
                    cout<<"Invalid Department, Please try again.\n";
                    cout<<"Department: [DS, CS, IS, AI, IT]\n";
                    cin>>dep;
                }
                Student new_student = *new Student(name, dep, gpa, id);
                insert(new_student);
                cout << "\nThe student is added.\n";
                break;
            }
            case 2:{
                int id;
                cout<<"Id: "; cin >> id;
                if (found(id)){
                    search(id);
                    remove(id);
                    cout << "Student is deleted.\n";
                }else{
                    cout << "Student is not found.\n";
                }
                break;
            }
            case 3:{
                int id;
                cout<<"Id: "; cin >> id;
                search(id);
                break;
            }
            case 4:{
                cout << "\nPrint " << treeSize << " Students.\n";
                print(); cout << "\n\nStudents per Departments:\n";
                printDepartments();
                break;
            }
            case 5:
                flag = false;
                break;
        }
    }
}

