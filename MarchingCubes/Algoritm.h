#pragma once
#ifndef ALGORITM_H
#define ALGORITM_H

#include "stdafx.h"

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

struct XYZ
{
	double x, y, z;
};

struct GridCell
{
	XYZ p[8];
	double val[8];
};

struct Triangle
{
	XYZ p[3];
};

class MarchingCubes {

public:

	Triangle triangles;
	XYZ vertlist[12];

	void AlgMarCub(vector<vector<vector<int>>>& object, int sx, int sy, int sz);

private:
	XYZ Interp(double isolevel, XYZ p1, XYZ p2, double valp1, double valp2);
	vector<float> MarchingCubes::Normals();
	void MarchingCubes::Drawing(int cubeindex);

	double param;
	XYZ p;
	int i, j, k;
	float x1, y1, y2, x2, z1, z2;
	float nx, ny, nz, nn;

	GLfloat materialAmbient[4] = { 0.5f, 0.5f, 0.5f, 0.0f };
	GLfloat materialDiffuse[4] = { 0.8f, 0.4f, 0.4f, 0.0f };
	GLfloat materialShine[4] = { 0.8f, 0.4f, 0.4f, 0.0f };
	GLfloat materialShineFactor[1] = { 30.0f };
	GLfloat poziceSvetla[4] = { 1.0f, 1.0f, 1.0f, 0.0f };

};
#endif
