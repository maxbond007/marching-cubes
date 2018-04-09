#pragma once
#ifndef DATAREAD_READDATA_H
#define DATAREAD_READDATA_H

#include <fstream>
#include <vector>
#include <iostream>
#include "stdio.h"
using namespace std;

class readData {
public:
	readData(string fileName, int sx, int sy, int sz);
	inline unsigned char get(int x, int y, int z) {
		return data[z * (sx * sy) + y * sx + x];
	}
	inline void put(int x, int y, int z, unsigned char value) {
		data[z * (sx * sy) + y * sx + x] = value;
	}

private:

	void readFile();
	string fileName;
	//vector<unsigned char> data;
	unsigned char* data;
	int totalSize;
	int sx, sy, sz;
};


#endif //DATAREAD_READDATA_H
