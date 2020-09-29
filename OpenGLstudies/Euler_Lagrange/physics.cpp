#include "physics.h"

namespace physics
{
	double* two_vector(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y) // 2���� �� ���͸� �����ϴ� ���� 4�� �迭
	{
		double vec[4];
		// ������ �������� ���� ����
		vec[0] = vec1_x - origin_x; vec[1] = vec1_y - origin_y;
		vec[2] = vec2_x - origin_x; vec[3] = vec2_y - origin_y;

		return vec;
	}
	
	double scalar_product(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y) // ��Į�� ��
	{
		// ������ �������� ���� ����
		double* vec = two_vector(origin_x, origin_y, vec1_x, vec1_y, vec2_x, vec2_y);
		double dx1 = vec[0]; double dy1 = vec[1];
		double dx2 = vec[2]; double dy2 = vec[3];
		// ����
		double scalar = dx1 * dx2 + dy1 * dy2;

		return scalar;
	}
	
	double cross_product(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y) // ���� ��
	{
		// ������ �������� ���� ����
		double* vec = two_vector(origin_x, origin_y, vec1_x, vec1_y, vec2_x, vec2_y);
		double dx1 = vec[0]; double dy1 = vec[1];
		double dx2 = vec[2]; double dy2 = vec[3];
		// ����
		double cross = dx1 * dy2 - dy1 * dx2;

		return cross;
	}
	
	double scalar_angle(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y) // �� ���� ���� ����
	{
		//// ������ �������� ���� ����
		//double dx1 = vec1_x - origin_x; double dy1 = vec1_y - origin_y;
		//double dx2 = vec2_x - origin_x; double dy2 = vec2_y - origin_y;
		double* vec = two_vector(origin_x, origin_y, vec1_x, vec1_y, vec2_x, vec2_y);
		double dx1 = vec[0]; double dy1 = vec[1];
		double dx2 = vec[2]; double dy2 = vec[3];
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