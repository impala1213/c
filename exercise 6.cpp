#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
    int n, k, i;
    int id, height;
    float weight, score;

    ofstream outfile("test.bin", ios::binary);

    cin >> n >> k;

    for (i = 0; i < n; i++) {
        cin >> id >> weight >> height >> score;
        outfile.write((char*)&score, sizeof(float));
        outfile.write((char*)&id, sizeof(int));
        outfile.write((char*)&weight, sizeof(float));
        outfile.write((char*)&height, sizeof(int));
    }

    outfile.close();

    ifstream inFile("test.bin", ios::binary);

    int recordSize = sizeof(float) + sizeof(int) + sizeof(float) + sizeof(int);
    inFile.seekg(k, ios::beg);
    inFile.read((char*)&score, sizeof(float));
    inFile.read((char*)&id, sizeof(int));
    inFile.read((char*)&weight, sizeof(float));
    inFile.read((char*)&height, sizeof(int));

    cout << score << " " << id << " " << weight << " " << height << endl;

    inFile.close();
    return 0;
}
