#include "ArgumentManager.h"
#include <fstream>
#include <iostream>
using namespace std;

void print(int **field, int size, int ripe, int rotten);
void write(int **field, int size, string out, int ripe, int rotten);
void harvest(int *row, int size);
int *squeeze(int *row, int size);
void tomorrow(int **field, int size, bool *status);

int main(int argc, char *argv[]) {
  // if (argc < 1 || (argc != 3 && argc != 2)) {
  //   cout << "Invalid arguments" << endl;
  //   return 1;
  // }
  ArgumentManager am(argc, argv);
  const string in = am.get("input");
  const string out = am.get("output");

  int size, curr, ripe = 0, rotten = 0;

  // ifstream ifs(in); // online
  // string outF = out;

  ifstream ifs("input3.txt"); // offline
  string outF = "output.txt";

  ifs >> size;

  // make arrays
  int **field = new int *[size];
  for (int i = 0; i < size; i++) {
    field[i] = new int[size];
  }
  bool *squished = new bool[size];
  for (int i = 0; i < size; i++) {
    squished[i] = false;
  }

  // initialize
  int *p = *field;
  for (int i = 0; i < size; i++) {
    p = new int[size];
    int *q = p;
    for (int j = 0; j < size; j++) {
      ifs >> curr;
      *q = curr;
      // field[i][j] = curr;
      q++;
    }
    p++;
  }
  cout << string(25, '\n');

  for (int day = 0; day < 8; day++) { //////
    cout << "\nDay " << day << "\n";
    for (int row = 0; row < size; row++) {
      int *squish = squeeze(field[row], size);

      if ((*(squish) + *(squish + 1)) >= size / 2) {
        harvest(field[row], size);
        ripe += *squish;
        rotten += *(squish + 1);
        squished[row] = true;
      }
    }
    print(field, size, ripe, rotten);
    cout << '\n';
    if (day != 7) {
      tomorrow(field, size, squished);
    }
  }

  cout << "\nending ";
  print(field, size, ripe, rotten);
  write(field, size, outF, ripe, rotten);

  return 0;
}

void print(int **field, int size, int ripe, int rotten) {
  cout << "field: \n";
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << field[i][j] << " ";
    }
    cout << '\n';
  }
  cout << "Harvested kiwis: " << ripe << "\nRotten kiwis: " << rotten;
}

int *squeeze(int *row, int size) {
  static int data[2] = {0};
  data[0] = 0; // data is static
  data[1] = 0;
  for (int i = 0; i < size; i++) {
    if (row[i] >= 6 && row[i] <= 8) {
      data[0]++;
    }
    if (row[i] >= 9) {
      data[1]++;
    }
  }
  return data;
}

void harvest(int *row, int size) {
  for (int i = 0; i < size; i++) {
    row[i] = 0;
  }
}

void write(int **field, int size, string out, int ripe, int rotten) {
  ofstream ofs(out);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ofs << field[i][j] << " ";
    }
    ofs << '\n';
  }
  ofs << "\nHarvested kiwis: " << ripe << "\nRotten kiwis: " << rotten;
  ofs.close();
}

void tomorrow(int **field, int size, bool *status) {
  for (int row = 0; row < size; row++) {
    if (!status[row]) {
      for (int kiwi = 0; kiwi < size; kiwi++) {
        field[row][kiwi]++;
      }
    }
    status[row] = false;
  }
}
