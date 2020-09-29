#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

namespace physics
{
	double scalar_product(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y);
	double cross_product(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y);
	double scalar_angle(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y);
}
