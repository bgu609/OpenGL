#include "physics.h"

namespace physics
{
	double* two_vector(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y) // 2차원 두 벡터를 정의하는 길이 4의 배열
	{
		double vec[4];
		// 원점을 기준으로 벡터 정의
		vec[0] = vec1_x - origin_x; vec[1] = vec1_y - origin_y;
		vec[2] = vec2_x - origin_x; vec[3] = vec2_y - origin_y;

		return vec;
	}
	
	double scalar_product(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y) // 스칼라 곱
	{
		// 원점을 기준으로 벡터 정의
		double* vec = two_vector(origin_x, origin_y, vec1_x, vec1_y, vec2_x, vec2_y);
		double dx1 = vec[0]; double dy1 = vec[1];
		double dx2 = vec[2]; double dy2 = vec[3];
		// 내적
		double scalar = dx1 * dx2 + dy1 * dy2;

		return scalar;
	}
	
	double cross_product(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y) // 벡터 곱
	{
		// 원점을 기준으로 벡터 정의
		double* vec = two_vector(origin_x, origin_y, vec1_x, vec1_y, vec2_x, vec2_y);
		double dx1 = vec[0]; double dy1 = vec[1];
		double dx2 = vec[2]; double dy2 = vec[3];
		// 외적
		double cross = dx1 * dy2 - dy1 * dx2;

		return cross;
	}
	
	double scalar_angle(double origin_x, double origin_y, double vec1_x, double vec1_y, double vec2_x, double vec2_y) // 두 벡터 사이 각도
	{
		//// 원점을 기준으로 벡터 정의
		//double dx1 = vec1_x - origin_x; double dy1 = vec1_y - origin_y;
		//double dx2 = vec2_x - origin_x; double dy2 = vec2_y - origin_y;
		double* vec = two_vector(origin_x, origin_y, vec1_x, vec1_y, vec2_x, vec2_y);
		double dx1 = vec[0]; double dy1 = vec[1];
		double dx2 = vec[2]; double dy2 = vec[3];
		// 두 벡터의 크기
		double d1 = sqrt(dx1 * dx1 + dy1 * dy1);
		double d2 = sqrt(dx2 * dx2 + dy2 * dy2);
		// 내적
		double scalar_product_result = scalar_product(origin_x, origin_y, vec1_x, vec1_y, vec2_x, vec2_y);
		// 내적으로부터 angle 계산
		double angle_result = acos(scalar_product_result / (d1 * d2));

		return angle_result;
	}
}