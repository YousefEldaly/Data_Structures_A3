#include "AVL.h"

int AVL::height(AvlNode *node) const {
    return node == nullptr ? -1 : node->height;
}

void AVL::insert(const Student &student) {
    insert(student, root);
}

void AVL::insert(const Student &student, AvlNode *&node) {
    if(node == nullptr){
        treeSize++;
        departments[student.getDepartment()]++;
        node = new AvlNode{student, nullptr, nullptr};
    }
    /*else if (found(student.getId()))
        return;
    else if (found(node->student.getId())){
        balance(node);
        return;}*/
    else if(student.getId() < node->student.getId())
        insert(student, node->left);
    else if(node->student.getId() < student.getId())
        insert(student, node->right);

    balance(node);
}

void AVL::balance(AvlNode *&node) {
    if(node == nullptr)
        return;
    if(height(node->left) - height(node->right) > ALLOWED_IMBALANCE)
        if(height(node->left->left) >= height(node->left->right))
            rotateWithLeftChild(node);
        else
            doubleWithLeftChild(node);
    else
        if(height(node->right) - height(node->left) > ALLOWED_IMBALANCE)
            if(height(node->right->right) >= height(node->right->left))
                rotateWithRightChild(node);
            else
                doubleWithRightChild(node);


    node->height = max(height(node->left), height(node->right)) + 1;
}

void AVL::rotateWithLeftChild(AvlNode *&node2) {
    AvlNode *node1 = node2->left;
    node2->left = node1->right;
    node1->right = node2;
    node2->height = max(height(node2->left), height(node2->right)) + 1;
    node1->height = max(height(node1->left), node2->height) + 1;
    node2 = node1;
}

void AVL::rotateWithRightChild(AvlNode *&node2) {

    AvlNode *node1 = node2->right;
    node2->right = node1->left;
    node1->left = node2;
    node2->height = max(height(node2->left), height(node2->right)) + 1;
    node1->height = max(height(node1->right), node2->height) + 1;
    node2 = node1;

}

void AVL::doubleWithLeftChild(AvlNode *&node3) {
    rotateWithRightChild(node3->left);
    rotateWithLeftChild(node3->left);

}
void AVL::doubleWithRightChild(AvlNode *&node3) {
    rotateWithLeftChild(node3->right);
    rotateWithRightChild(node3);
}

void AVL::remove(const int student_id) {
    remove(student_id, root);
}
void AVL::remove(const int student_id, AvlNode *&node) {
    if(node == nullptr)
        return;

    if(student_id < node->student.getId())
        remove(student_id, node->left);
    else if(node->student.getId() < student_id)
        remove(student_id, node->right);
    else if(node->left != nullptr && node->right != nullptr){
        node->student = findMin(node->right)->student;
        remove(node->student.getId(), node->right);
    }
    else{
        departments[node->student.getDepartment()]--;
        AvlNode *oldNode = node;
        node = (node->left != nullptr) ? node->left : node->right;
        delete oldNode;
        treeSize--;
    }

}

AvlNode* AVL::findMin(AvlNode *node) {
    if(node == nullptr)
        return nullptr;
    if(node->left == nullptr)
        return node;

    return findMin(node->left);
}

void AVL::printInOrder(AvlNode *node) {
    if (node == nullptr)
        return;

    printInOrder(node->left);
    node->student.printStudentInfo();
    printInOrder(node->right);
}

void AVL::print() {
    AvlNode *node = root;
    if (node == nullptr)
        return;
    printInOrder(node);
}

bool AVL::found(int id) {
    AvlNode *node = root;
    while (node != nullptr) {
        if (id == node->student.getId())
            return true;
        else if (id < node->student.getId()) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return false;

}

void AVL::setDepartments(map<string, int> deps) {
    this->departments = std::move(deps);
}


void AVL::displayMenu(){
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
                cout << "id: ";
                cin >> id;
                while (!validID(id)){
                    cout<<"Invalid ID, Please try again.\n";
                    cout<<"id: ";
                    cin>>id;
                }
                cout << "Name:";
                cin.ignore();
                getline(cin,name);
                cout << "GPA: ";
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
                    //search(id);
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

bool AVL::validID(int id){
    if (id < 0 || id > 100 || found(id)){
        return false;
    }else{
        return true;
    }
}

bool AVL::validDep(string& dep){
    if (dep == "CS" ||dep == "IS" || dep == "DS"||dep == "AI" || dep == "IT")
        return true;
    return false;
}

void AVL::search(int id) {
    if (!found(id)) {
        cout << "Student is not found." << endl;
        return;
    }
    AvlNode *node = root;
    while (node != nullptr) {
        if (id == node->student.getId()) {
            cout << "Student is found.\n";
            node->student.printStudentInfo();
            return;
        } else if (id < node->student.getId()) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
}

void AVL::printDepartments(){
    for (auto & department : departments) {
        cout << department.first <<" " << department.second << " Students\n" ;
    }
}

bool AVL::validGPA(float gpa){
    if(gpa >= 0.0 && gpa <= 4.0)
        return true;
    return false;
}


