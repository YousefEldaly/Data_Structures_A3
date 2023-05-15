#include "BST.h"

BST::BST() {
    this->root = nullptr;
    this->treeSize = 0;
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
        cout << "Student doesn't exist" << endl;
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
    treeSize--;
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