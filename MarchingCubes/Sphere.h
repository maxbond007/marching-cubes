#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "stdafx.h"

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;


class DrawObject {
public:

	void Object(int sx, int sy, int sz, string name);
	void Sphere(int x0, int y0, int z0, int r);
	void transformObject(int xnew, int ynew, int znew);
	vector<vector<vector<int>>> XYZ;

private:

};

#endif
