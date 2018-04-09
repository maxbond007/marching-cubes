#include "stdafx.h"
#include "ReadData.h"


readData::readData(string fileName, int sx, int sy, int sz) {
	this->fileName = fileName;
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	totalSize = sx * sy * sz;
	data = new unsigned char[totalSize];
	//data.resize(totalSize);
	readFile();
}


void readData::readFile() {
	ifstream ifs(fileName, ios::binary);
	ifs.seekg(0, ifs.beg);
	ifs.read((char*)&data[0], totalSize);
	ifs.close();
}

