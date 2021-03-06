// MarchingCubes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sphere.h"
#include "Rotation.h"
#include "stdio.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

	//The selection of the data for processing is made by uncommenting the appropriate rows

	//CT :
	/*string name = "128.dat";
	int sx = 128;
	int sy = 128;
	int sz = 114;*/

	//Lobster :
	/*string name = "lobster.dat";
	int sx = 120;
	int sy = 120;
	int sz = 34;*/

	//hydrogen :
	string name = "hydrogen.dat";
	int sx = 64;
	int sy = 64;
	int sz = 64;

	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = 2;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;

	int x0 = 0, y0 = 0, z0 = 0, r = 10; // parameters of the sphere

	int xweight = sx;
	int yweight = sy;
	int zweight = sz;

	DrawObject object; // Draws objects

	Mouse m; // Function for mouse control (object rotation, view slices along the axis Z)

	sf::Window App(sf::VideoMode(800, 800), "Marching Cubes", sf::Style::Resize | sf::Style::Close, contextSettings);

	while (App.isOpen()) {
		sf::Event Event;
		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				App.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (Event.type == sf::Event::MouseButtonPressed) {
					m.setState(Mouse::Left);
					m.setXx(sf::Mouse::getPosition(App).x);
					m.setYy(sf::Mouse::getPosition(App).y);
				}
				m.onLeftButton(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (Event.type == sf::Event::MouseButtonPressed) {
					m.setState(Mouse::Right);
					m.setZz(sf::Mouse::getPosition(App).y);
				}
				m.onRightButton(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
			}

			if (Event.type == sf::Event::MouseButtonReleased) {
				if (m.getState() == Mouse::Left) {
					m.setXold(m.getXnew());
					m.setYold(m.getYnew());
				}
				else if (m.getState() == Mouse::Right) {
					m.setZold(m.getZnew());
				}
				m.setState(Mouse::None);
			}
		}

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		
		glLoadIdentity();
		glOrtho(-xweight, xweight, -yweight, yweight, -zweight, zweight);

		object.transformObject(m.getXnew(), m.getYnew(), m.getZnew());

		object.Sphere(x0, y0, z0, r); // the Sphere drawing
		//object.Object(sx, sy, sz, name); // the objects drawing
		App.display();
		//system("pause");
	}
}
