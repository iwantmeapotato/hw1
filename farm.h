#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class farm {
private:
  int tRipe, tRot, size;
  string in, out;
  ifstream ifs;
  ofstream ofs;
  int **field;
public:
  farm(string in, string out): in(in), out(out) {
    int curr;
    ifs.open(in);
    ifs >> size;
    int **field = new int* [size];
      for (int i = 0; i < size; i++) {
        field[i] = new int[size];
        for (int j = 0; j < size; j++) {
          ifs >> curr;
          field[i][j] = curr;
        }
    }

    ifs.close();
  }

  int squeeze(int row) {
    int ripe = 0;
    for (int i = 0; i < size; i++) {
      if (field[row][i] >= 6 && field[row][i] <= 8) {
        ripe++;
      }
    }
    return ripe;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        cout << field[i][j] << " ";
      }
      cout << '\n';
    }
  }

  void write() {
    ofs.open(out);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        ofs << field[i][j] << " ";
      }
      ofs << '\n';
    }
    ofs.close();
  }




};
