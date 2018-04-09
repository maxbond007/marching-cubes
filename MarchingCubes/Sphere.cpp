

#include "stdafx.h"
#include "Sphere.h"
#include "Algoritm.h"
#include "ReadData.h"

#include <iostream>
#include <vector>


using namespace std;

MarchingCubes algorithm;


void DrawObject::transformObject(int xnew, int ynew, int znew) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0, 0.0, -50.0f);
	glTranslatef(0.0, 0.0, znew);
	glRotatef(ynew, 1.0, 0.0, 0.0);
	glRotatef(xnew, 0.0, 1.0, 0.0);
}

// the Sphere drawing function
void DrawObject::Sphere(int x0, int y0, int z0, int r) {

	XYZ.clear();
	glEnable(GL_POINT_SMOOTH); // Сглаживание точек
	glPointSize(5);
	glBegin(GL_POINTS);
		for (float x = -r; x <= r; x++) {
			vector<vector<int>> XY;
			for (float y = -r; y <= r; y++) {
				vector<int> Z;
				for (float z = -r; z <= r; z++) {
			
					if ((x - x0)*(x - x0) + (y - y0)*(y - y0) + (z - z0)*(z - z0) <= r*r) {

						Z.push_back(0);
						glColor3f(1, 1, 1);
						glVertex3i(x + r, y + r, z + r);
					}
					else {
						Z.push_back(1);
					}
				}XY.push_back(Z);
			}XYZ.push_back(XY);
		}
	glEnd();
	algorithm.AlgMarCub(XYZ, XYZ.size(), XYZ.size(), XYZ.size());
	glFlush();
}

// the objects drawing function
void DrawObject::Object(int sx, int sy, int sz, string name) {

	readData D(name, sx, sy, sz); // Zavolanie tohto príkazu automaticky načíta dáta

	XYZ.clear();
	glEnable(GL_POINT_SMOOTH); // Сглаживание точек
	glPointSize(5);
	glBegin(GL_POINTS);
	for (float x = 0; x < sx; x++) {
		vector<vector<int>> XY;
		for (float y = 0; y < sy; y++) {
			vector<int> Z;
			for (float z = 0; z < sz; z++){

				if (int(D.get(x, y, z)) != 0) {

					Z.push_back(0);
					glColor3f(1, 1, 1);
					glVertex3i(x, y, z);

				}
				else {
					Z.push_back(1);
				}
			} XY.push_back(Z);
		} XYZ.push_back(XY);
	}
	glEnd();
	//glFlush();
	algorithm.AlgMarCub(XYZ, sx, sy, sz);
	std::cout << "All ready\n";
	glFlush();
}