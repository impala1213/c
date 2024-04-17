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
const int BLOCK_SIZE = 4096;
const int RECORD_SIZE = sizeof(Student);
const int BLOCKING_FACTOR = BLOCK_SIZE / RECORD_SIZE;



bool insert(char* name, unsigned ID, float score, char* dept) {
    Student student;
    strncpy(student.name, name, 20);
    student.ID = ID;
    student.score = score;
    strncpy(student.dept, dept, 10);

    // 파일이 존재여부 체크하기
    ifstream nfile("student.dat", ios::binary);
    if (!nfile.is_open()) {
        ofstream outfile("student.dat", ios::out | ios::binary);
        outfile.close();
        nfile.open("student.dat", ios::binary);
    }

    // 중복 ID 검사
    Student temp;
    fstream infile("student.dat", ios::in | ios::out | ios::binary);
    int blockcount = 1;
    while(infile.read((char*)&temp, RECORD_SIZE)) {
        if (temp.ID == ID) {
            //cout << "same id!" << endl;
            infile.close();
            return false;
        }
        if (infile.tellg() / RECORD_SIZE == BLOCKING_FACTOR - 1) {
            infile.seekp(blockcount * BLOCK_SIZE - (RECORD_SIZE - 1), ios::beg);
            blockcount += 1;
        }
    }
    // empty search
    fstream checkfile("student.dat", ios::in | ios::out | ios::binary);
    blockcount = 1;
    while(checkfile.read((char*)&temp, RECORD_SIZE)) {
        if (temp.ID == -1) {
            cout << "empty loc :" << checkfile.tellg() << endl;
            checkfile.seekp(checkfile.tellg() - RECORD_SIZE);
            checkfile.write((char*)&student, RECORD_SIZE);
            checkfile.close();
            return true;
        }
        if (checkfile.tellg() / RECORD_SIZE == BLOCKING_FACTOR - 1) {
            checkfile.seekp(blockcount * BLOCK_SIZE - (RECORD_SIZE - 1), ios::beg);
            blockcount += 1;
        }
    }

    infile.close();
    fstream file("student.dat", ios::in | ios::out | ios::binary | ios::ate);
    // blocking factor 이하인지 체크 초과시 새 블록 할당
    long currentSize = file.tellg();
    int currentRecords = currentSize / RECORD_SIZE;
    int currentBlock = currentRecords / BLOCKING_FACTOR;
    blockcount = 1;
    if (currentSize / RECORD_SIZE == BLOCKING_FACTOR - 1 ) {
        file.seekp(blockcount * BLOCK_SIZE - (RECORD_SIZE - 1), ios::beg);
        blockcount += 1;
    } else {
        file.seekp(0, ios::end);
    }
    file.write((char*)&student, RECORD_SIZE);
    cout << currentSize <<  " ID : " <<student.ID << endl;
    file.close();
    return true;
}


bool read(int n, char* name, unsigned* ID, float* score, char* dept) {
    ifstream file("student.dat", ios::binary);
    if(n > BLOCKING_FACTOR){
        file.seekg(BLOCK_SIZE *(n/BLOCKING_FACTOR) + RECORD_SIZE*(n%BLOCKING_FACTOR) + 1 ,ios::beg);
    }
    else{
        file.seekg(n * RECORD_SIZE, ios::beg);
    }
    Student student;
    if (!file.read((char*)&student, sizeof(Student))) {
            return false;
        }
    strcpy(name, student.name);
    *ID = student.ID;
    *score = student.score;
    strcpy(dept, student.dept);
    return true;
}

bool search(char* name, unsigned ID, float* score, char* dept) {
    ifstream file("student.dat", ios::binary);

    Student student;
    int blockcount = 1;
    while(file.read((char*)&student, RECORD_SIZE)) {
        long currentSize = file.tellg();
        int currentRecords = file.tellg() / RECORD_SIZE;
        int currentBlock = file.tellg() / RECORD_SIZE / BLOCKING_FACTOR;
        if (student.ID == ID) {
            strcpy(name, student.name);
            *score = student.score;
            strcpy(dept, student.dept);
            return true;
        }
        if (file.tellg() / RECORD_SIZE == BLOCKING_FACTOR - 1) {
            file.seekg(blockcount * BLOCK_SIZE - (RECORD_SIZE - 1), ios::beg);
            blockcount += 1;
        }
    }
    return false;
}

bool drop(char* name, unsigned ID, float *score, char* dept) {
    fstream file("student.dat", ios::in | ios::out | ios::binary);
    Student student;
    int blockcount = 1;
    while(file.read((char*)&student, RECORD_SIZE)) {
        long currentSize = file.tellg();
        int currentRecords = currentSize / RECORD_SIZE;
        int currentBlock = currentRecords / BLOCKING_FACTOR;
            cout << file.tellg();
            cout << " ID :" << student.ID << endl;
        if (student.ID == ID) {
            file.seekp(-40, ios::cur);
            cout << "drop : " << file.tellg() <<endl;
            student.ID = -1;
            file.write((char*)&student, RECORD_SIZE);
            break;
        }
        if (currentSize / RECORD_SIZE == BLOCKING_FACTOR - 1) {
            file.seekp(blockcount * BLOCK_SIZE - (RECORD_SIZE - 1), ios::beg);
            blockcount += 1;
        }
    }
    file.close();
    return true;
}



int main() {

    // 레코드 추가 테스트
    for (int i = 1; i <= 204; ++i) { // 충분한 수의 레코드를 추가하여 여러 블록을 채움
        char name[20], dept[10];
        sprintf(name, "Student%d", i);
        sprintf(dept, "Dept%d", i % 10);
        float score = 60.0 + (i % 40); // 점수는 60에서 99 사이로 설정
        unsigned ID = i; // ID는 순차적으로 증가

        if (insert(name, ID, score, dept)) {
            cout << "Insertion successful for ID " << ID << endl;
        } else {
            cout << "Insertion failed for ID " << ID << endl;
        }
    }
    for (int n = 90; n <= 104; ++n) { // 충분한 수의 레코드를 추가하여 여러 블록을 채움

        if (drop( "", n, 0,"" )) {
            cout << "drop successful for ID " << n << endl;
        } else {
            cout << "drop failed for ID " << endl;
        }
    }
    for (int m =90; m<=104; ++m){
        char name[20], dept[10];
        sprintf(name, "Student%d", m+100);
        sprintf(dept, "Dept%d", m % 10);
        float score = 60.0 + (m % 40); // 점수는 60에서 99 사이로 설정
        unsigned ID = m; // ID는 순차적으로 증가
        insert(name, ID, score, dept);


    }


    return 0;
}
