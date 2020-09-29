#include "physics.h"

namespace physics
{
	double scalar_product(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y)
	{
		// ������ �������� ���� ����
		double dx1 = vec1_x - origin_x; double dy1 = vec1_y - origin_y;
		double dx2 = vec2_x - origin_x; double dy2 = vec2_y - origin_y;
		// ����
		double scalar = dx1 * dx2 + dy1 * dy2;

		return scalar;
	}

	double cross_product(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y)
	{
		// ������ �������� ���� ����
		double dx1 = vec1_x - origin_x; double dy1 = vec1_y - origin_y;
		double dx2 = vec2_x - origin_x; double dy2 = vec2_y - origin_y;
		// ����
		double cross = dx1 * dy2 - dy1 * dx2;

		return cross;
	}

	double scalar_angle(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y)
	{
		// ������ �������� ���� ����
		double dx1 = vec1_x - origin_x; double dy1 = vec1_y - origin_y;
		double dx2 = vec2_x - origin_x; double dy2 = vec2_y - origin_y;
		// �� ������ ũ��
		double d1 = sqrt(dx1 * dx1 + dy1 * dy1);
		double d2 = sqrt(dx2 * dx2 + dy2 * dy2);
		// ����
		double scalar_product_result = scalar_product(origin_x, origin_y, vec1_x, vec1_y, vec2_x, vec2_y);
		// �������κ��� angle ���
		double angle_result = acos(scalar_product_result / (d1 * d2));

		return angle_result;
	}
}