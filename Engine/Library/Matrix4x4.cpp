#include "Matrix4x4.h"
#include "Rotator.h"
#include "Vector3.h"

namespace BE::Math
{
	Matrix4x4 Matrix4x4::FromScale(const Vector3& scale)
	{
		Matrix4x4 ret;
		ret.mat = Eigen::Scaling(scale[0], scale[1], scale[2]).toDenseMatrix();
		return ret;
	}

	Matrix4x4 Matrix4x4::FromPosition(const Vector3& pos)
	{
		Eigen::Affine3f transform{ Eigen::Translation3f{ pos[0], pos[1], pos[2] } };

		Matrix4x4 ret;
		ret.mat = transform.matrix();
		return ret;
	}


	/// @todo Implement this after build rotator.
	Matrix4x4 Matrix4x4::FromRotation(const Rotator& angle)
	{
		return Matrix4x4{ };
	}
}