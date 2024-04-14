#include <iostream>
#include <string>
using namespace std;

static int student_count = 0;

class Student {
public:
    unsigned ID;
    string name;

    Student() : ID(0), name("") {
        student_count++;
        cout << student_count << endl;
    }

    Student(unsigned id, string n) : ID(id), name(n) {
        student_count++;
        cout << student_count << endl;
    }

    Student(const Student &other) : ID(other.ID), name(other.name) {
        student_count++;
        cout << student_count << endl;
    }

    ~Student() {
        student_count--;
        cout << student_count << endl;
    }
};

class Lecture {
public:
    string prof;
    Student *students;
    int number;

    Lecture(int n) : prof(""), students(new Student[n]), number(n) {}

    ~Lecture() {
        delete[] students;
    }

    Lecture(const Lecture &other) : prof(other.prof), number(other.number) {
        students = new Student[number];
        for (int i = 0; i < number; i++) {
            students[i] = other.students[i];
        }
    }

    unsigned operator[](const string &name) {
        for (int i = 0; i < number; i++) {
            if (students[i].name == name) {
                return students[i].ID;
            }
        }
        return 0;
    }
};

int main() {
    int n;
    cin >> n;
    Lecture lecture(n); // make lecture with n students
    for (int i = 0; i < n; i++) {
        cin >> lecture.students[i].ID >> lecture.students[i].name;
    }
    string key_name;
    cin >> key_name;
    cout << lecture[key_name] << endl;

    return 0;
}
