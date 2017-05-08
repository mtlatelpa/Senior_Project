#pragma once
#include "Projectile.h"

class Tower : public projectile
{
public:
	Tower();
	~Tower();

	int active1 = 0;
	int active2 = 0;
	int active3 = 0;

	int tower1bullets = 4;
	int tower2bullets = 10;
	int tower3bullets = 15;

private:

};