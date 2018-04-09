MarchingCubes Project by Bondarenko M. 26.12.2017

///////////////////////////////////////////////////////////////////////

To start the project you should to follow these instructions:
1) Install the OpenGL library
2) Configure the OpenGL library in your IDE
3) Configure the pratform on x64 and debug
4) Start

///////////////////////////////////////////////////////////////////////

Description of the files in my project

MarchingCubes.cpp
	This is the main application source file in my project

Sphere.cpp, Sphere.h
	These files are responsible for initializing objects and drawing these objects.

Tables.h 
	It keeps the lookup tables ( this tables are taken from "http://paulbourke.net/geometry/polygonise/").

Rotation.cpp, Rotation.h
	These files contain the functions for mouse control (object rotation, view slices along the axis OZ),
	left click for rotating and by clicking the right mouse button you can scan the slices along the axis OZ.

ReadDatacpp.cpp, ReadData.h
	These files are responsible for reading data from the files (hydrogen.dat, lobster.dat, 128.dat).

Algoritm.cpp, Algoritm.h
	These files implement the main algorithm (Marching Cubes algorithm), and also contain the calculation of interpolation and normals.

///////////////////////////////////////////////////////////////////////

The selection of the data for their processing is made by uncommenting the appropriate rows in the main function in MarchingCubes.cpp file.

To draw the object (hydrogen.dat, lobster.dat, 128.dat) you should uncomment row number 101 in the main function in MarchingCubes.cpp file.

///////////////////////////////////////////////////////////////////////