

#include "stdafx.h"
#include "Algoritm.h"
#include "Tables.h"

#include <iostream>

using namespace std;

// Marching cubes algorihtm
void MarchingCubes::AlgMarCub(vector<vector<vector<int>>>& object, int sx, int sy, int sz) {
	
	GridCell grid;
	double isolevel = 1;

	for (int x = 0; x < sx - 1; x++) {
		
		for (int y = 0; y < sy - 1; y++) {

			for (int z = 0; z < sz - 1; z++) {

				int cubeindex = 0;

				//The indexing convention for vertices and edges used in the algorithm are shown below

				//                 p7_______e6_____________p6
				//                  /|                    /|
				//                 / |                   / |
				//              e7/  |                e5/  |
				//               /___|______e4_________/   |
				//            p4|    |                 |p5 |e10
				//              |    |                 |   |
				//              |    |e11              |e9 |
				//            e8|    |                 |   |
				//              |    |_________________|___|
				//              |   / p3      e2       |   /p2
				//              |  /                   |  /
				//              | /e3                  | /e1
				//              |/_____________________|/
				//              p0         e0          p1

				grid.val[0] = object[x][y][z];
				grid.val[1] = object[x + 1][y][z];
				grid.val[2] = object[x + 1][y][z + 1];
				grid.val[3] = object[x][y][z + 1];
				grid.val[4] = object[x][y + 1][z];
				grid.val[5] = object[x + 1][y + 1][z];
				grid.val[6] = object[x + 1][y + 1][z + 1];
				grid.val[7] = object[x][y + 1][z + 1];

				// Write down the coordinates of each squares points
				grid.p[0].x = x;			
				grid.p[0].y = y;				
				grid.p[0].z = z;				

				grid.p[1].x = x + 1;
				grid.p[1].y = y;
				grid.p[1].z = z;

				grid.p[2].x = x + 1;
				grid.p[2].y = y;
				grid.p[2].z = z + 1;

				grid.p[3].x = x;				
				grid.p[3].y = y;			
				grid.p[3].z = z + 1;			

				grid.p[4].x = x;
				grid.p[4].y = y + 1;
				grid.p[4].z = z;

				grid.p[5].x = x + 1;
				grid.p[5].y = y + 1;
				grid.p[5].z = z;

				grid.p[6].x = x + 1;	
				grid.p[6].y = y + 1;	
				grid.p[6].z = z + 1;	

				grid.p[7].x = x;
				grid.p[7].y = y + 1;
				grid.p[7].z = z + 1;

				// Determine the index into the edge table which tells us which vertices are inside of the surface
				if (grid.val[0] < isolevel) cubeindex |= 1;
				if (grid.val[1] < isolevel) cubeindex |= 2; 
				if (grid.val[2] < isolevel) cubeindex |= 4;
				if (grid.val[3] < isolevel) cubeindex |= 8; 
				if (grid.val[4] < isolevel) cubeindex |= 16; 
				if (grid.val[5] < isolevel) cubeindex |= 32; 
				if (grid.val[6] < isolevel) cubeindex |= 64;
				if (grid.val[7] < isolevel) cubeindex |= 128; 


				if (edgeTable[cubeindex] == 0) {
					//
				}else {
					// Cube is entirely in/out of the surface
					if (edgeTable[cubeindex] & 1)
						vertlist[0] = Interp(isolevel, grid.p[0], grid.p[1], grid.val[0], grid.val[1]);
					if (edgeTable[cubeindex] & 2)
						vertlist[1] = Interp(isolevel, grid.p[1], grid.p[2], grid.val[1], grid.val[2]);
					if (edgeTable[cubeindex] & 4)
						vertlist[2] = Interp(isolevel, grid.p[2], grid.p[3], grid.val[2], grid.val[3]);
					if (edgeTable[cubeindex] & 8)
						vertlist[3] = Interp(isolevel, grid.p[3], grid.p[0], grid.val[3], grid.val[0]);
					if (edgeTable[cubeindex] & 16)
						vertlist[4] = Interp(isolevel, grid.p[4], grid.p[5], grid.val[4], grid.val[5]);
					if (edgeTable[cubeindex] & 32)
						vertlist[5] = Interp(isolevel, grid.p[5], grid.p[6], grid.val[5], grid.val[6]);
					if (edgeTable[cubeindex] & 64)
						vertlist[6] = Interp(isolevel, grid.p[6], grid.p[7], grid.val[6], grid.val[7]);
					if (edgeTable[cubeindex] & 128)
						vertlist[7] = Interp(isolevel, grid.p[7], grid.p[4], grid.val[7], grid.val[4]);
					if (edgeTable[cubeindex] & 256)
						vertlist[8] = Interp(isolevel, grid.p[0], grid.p[4], grid.val[0], grid.val[4]);
					if (edgeTable[cubeindex] & 512)
						vertlist[9] = Interp(isolevel, grid.p[1], grid.p[5], grid.val[1], grid.val[5]);
					if (edgeTable[cubeindex] & 1024)
						vertlist[10] = Interp(isolevel, grid.p[2], grid.p[6], grid.val[2], grid.val[6]);
					if (edgeTable[cubeindex] & 2048)
						vertlist[11] = Interp(isolevel, grid.p[3], grid.p[7], grid.val[3], grid.val[7]);
		
					Drawing(cubeindex);

					
				}
			}
		}
	}
}

// the linearly interpolation
XYZ MarchingCubes::Interp(double isolevel, XYZ p1, XYZ p2, double valp1, double valp2) {

	param = (isolevel - valp1) / (valp2 - valp1);
	p.x = p1.x + param * (p2.x - p1.x);
	p.y = p1.y + param * (p2.y - p1.y);
	p.z = p1.z + param * (p2.z - p1.z);

	return(p);
}

// the triangles drawing function
void MarchingCubes::Drawing(int cubeindex) {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialShine);
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShineFactor);
	glLightfv(GL_LIGHT0, GL_POSITION, poziceSvetla);

	glBegin(GL_TRIANGLES);
	for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {

		triangles.p[0] = vertlist[triTable[cubeindex][i]];
		triangles.p[1] = vertlist[triTable[cubeindex][i + 1]];
		triangles.p[2] = vertlist[triTable[cubeindex][i + 2]];

		vector<float> normal = Normals();
		
		glNormal3f(normal[0], normal[1], normal[2]);

		glVertex3f(triangles.p[0].x, triangles.p[0].y, triangles.p[0].z);
		glVertex3f(triangles.p[1].x, triangles.p[1].y, triangles.p[1].z);
		glVertex3f(triangles.p[2].x, triangles.p[2].y, triangles.p[2].z);
	}
	glEnd();
	glFlush();
}

// the function of calculating the normal to each triangle
vector<float> MarchingCubes::Normals() {

	vector<float> normal(3);

	x1 = triangles.p[1].x - triangles.p[0].x;
	y1 = triangles.p[1].y - triangles.p[0].y;
	z1 = triangles.p[1].z - triangles.p[0].z;
	x2 = triangles.p[2].x - triangles.p[0].x;
	y2 = triangles.p[2].y - triangles.p[0].y;
	z2 = triangles.p[2].z - triangles.p[0].z;

	nx = y1 * z2 - y2 * z1;
	ny = z1 * x2 - x1 * z2;
	nz = x1 * y2 - y1 * x2;

	nn = sqrt(nx*nx + ny*ny + nz*nz);

	normal[0] = nx / nn;
	normal[1] = ny / nn;
	normal[2] = nz / nn;

	return(normal);
}