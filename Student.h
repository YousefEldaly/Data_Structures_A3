#include "iostream"
using namespace std;

class Student {

private:
    int id;
    string name;
    string department;
    float gpa;
public:
    int getId() const;
    void setId(int id);
    const string &getName() const;
    void setName(const string &name);
    const string &getDepartment() const;
    void setDepartment(const string &department);
    float getGpa() const;
    void setGpa(float gpa);


};


