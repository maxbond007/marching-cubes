#include "stdafx.h"
#include "Rotation.h"

void Mouse::onLeftButton(int x, int y) {
	ynew = yold + y - yy;
	xnew = xold + x - xx;
}

void Mouse::onRightButton(int x, int y) {
	znew = zold + y - zz;
}



void Mouse::setXx(int xx) {
	Mouse::xx = xx;
}


void Mouse::setXold(int xold) {
	Mouse::xold = xold;
}


void Mouse::setYy(int yy) {
	Mouse::yy = yy;
}


void Mouse::setYold(int yold) {
	Mouse::yold = yold;
}


void Mouse::setZz(int zz) {
	Mouse::zz = zz;
}


void Mouse::setZold(int zold) {
	Mouse::zold = zold;
}


void Mouse::setState(Mouse::State state) {
	Mouse::state = state;
}

int Mouse::getXnew() const {
	return xnew;
}

int Mouse::getYnew() const {
	return ynew;
}

int Mouse::getZnew() const {
	return znew;
}

Mouse::State Mouse::getState() const {
	return state;
}