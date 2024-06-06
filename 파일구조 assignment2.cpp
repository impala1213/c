#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

struct Student {
    char name[20];
    unsigned ID;
    float score;
    char dept[10];
};

bool insert(char* name, unsigned* ID, float* score, char* dept);
bool read(int n, char* name, unsigned* ID, float* score, char* dept);
bool search(char* name, unsigned ID, float* score, char* dept);
bool drop(char* name, unsigned ID, float* score, char* dept);

bool insert(char* name, unsigned* ID, float* score, char* dept) {
    fstream file("student.dat", ios::in | ios::out | ios::binary | ios::app);
    if (!file) {
        file.open("student.dat", ios::out | ios::binary);
        file.close();
        file.open("student.dat", ios::in | ios::out | ios::binary | ios::app);
    }

    // Check for duplicate ID
    Student stud;
    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.ID == *ID) {
            file.close();
            return false;
        }
    }

    // Insert new record
    strncpy(stud.name, name, sizeof(stud.name) - 1);
    stud.name[sizeof(stud.name) - 1] = '\0';
    stud.ID = *ID;
    stud.score = *score;
    strncpy(stud.dept, dept, sizeof(stud.dept) - 1);
    stud.dept[sizeof(stud.dept) - 1] = '\0';

    file.clear();
    file.write(reinterpret_cast<char*>(&stud), sizeof(Student));
    file.close();
    return true;
}

bool read(int n, char* name, unsigned* ID, float* score, char* dept) {
    fstream file("student.dat", ios::in | ios::binary);
    if (!file) return false;

    file.seekg(n * sizeof(Student), ios::beg);
    Student stud;
    if (file.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        strncpy(name, stud.name, sizeof(stud.name));
        *ID = stud.ID;
        *score = stud.score;
        strncpy(dept, stud.dept, sizeof(stud.dept));
        file.close();
        return true;
    }
    file.close();
    return false;
}

bool search(char* name, unsigned ID, float* score, char* dept) {
    fstream file("student.dat", ios::in | ios::binary);
    if (!file) return false;

    Student stud;
    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.ID == ID) {
            strncpy(name, stud.name, sizeof(stud.name));
            *score = stud.score;
            strncpy(dept, stud.dept, sizeof(stud.dept));
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool drop(char* name, unsigned ID, float* score, char* dept) {
    fstream file("student.dat", ios::in | ios::out | ios::binary);
    if (!file) return false;

    vector<Student> students;
    Student stud;
    bool found = false;

    // Read all records into memory except the one to be deleted
    while (file.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.ID != ID) {
            students.push_back(stud);
        } else {
            strncpy(name, stud.name, sizeof(stud.name));
            *score = stud.score;
            strncpy(dept, stud.dept, sizeof(stud.dept));
            found = true;
        }
    }

    if (!found) {
        file.close();
        return false;
    }

    // Rewrite the file without the deleted record
    file.close();
    file.open("student.dat", ios::out | ios::binary | ios::trunc);
    for (const auto& s : students) {
        file.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }
    file.close();
    return true;
}

int main()
{


}
