#include "basis_cartesian.hpp"
#include <cmath>

namespace basis
{
	CartesianPtr CreateBasisCartesian(Tag basisTag)
	{
		auto res = Cartesian::Create();

		res->SetTag(basisTag);

		return res;
	}
	Cartesian::Cartesian()
	{
		origin_ = Vector(numberCoordinates_, 0.0);
		basis_ = Matrix(numberCoordinates_, numberCoordinates_, eilig::matrix_diagonal);
	}
	Scalar Cartesian::Distance(const Vector& pt1, const Vector& pt2) const
	{
		Vector dif = pt2 - pt1;
		Scalar res = eilig::Dot(dif, dif);

		res = std::sqrt(res);

		return res;
	}
	Scalar Cartesian::DistanceSquared(const Vector& pt1, const Vector& pt2) const
	{
		Vector dif = pt2 - pt1;
		Scalar res = eilig::Dot(dif, dif);

		return res;
	}
	Vector Cartesian::LocalToGlobalPoint(const Vector& pt) const
	{
		return origin_ + basis_ * pt;
	}
	Vector Cartesian::LocalToGlobalVector(const Vector& vec) const
	{
		return basis_ * vec;
	}
	Vector Cartesian::GlobalToLocalPoint(const Vector& pt) const
	{
		return basis_.Transpose() * (pt - origin_);
	}
	Vector Cartesian::GlobalToLocalVector(const Vector& vec) const
	{
		return basis_.Transpose() * vec;
	}
	const Matrix& Cartesian::GetBasis() const
	{
		return basis_;
	}
	const Vector& Cartesian::GetOrigin() const
	{
		return origin_;
	}
	Tag Cartesian::GetTag() const
	{
		return tag_;
	}
	NumberCoordinates Cartesian::GetNumberCoordinates() const
	{
		return numberCoordinates_;
	}
	Type Cartesian::GetType() const
	{
		return type_;
	}
	void Cartesian::Offset(const Vector& delta)
	{
		origin_ = origin_ + delta;
	}
	void Cartesian::Offset(const Axis& axis, Scalar delta)
	{
		origin_(axis) = origin_(axis) + delta;
	}
	void Cartesian::Rotate(const Axis& axis, Scalar radians)
	{
		basis_ = eilig::transform::RotationMatrix(axis, radians) * basis_;
	}
	void Cartesian::SetOrigin(const Vector& origin)
	{
		origin_ = origin;
	}
	void Cartesian::SetTag(Tag tag)
	{
		tag_ = tag;
	}
	
} //namespace basis