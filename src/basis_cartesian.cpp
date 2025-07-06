#include "basis_cartesian.hpp"
#include <cmath>

namespace basis
{
	CartesianPtr CreateBasisCartesian()
	{
		auto res = Cartesian::Create();

		return res;
	}
	CartesianPtr CreateBasisCartesian(Tag basisTag)
	{
		auto res = Cartesian::Create();

		res->SetTag(basisTag);

		return res;
	}
	Cartesian::Cartesian()
	{
		origin_ = Vector(dim_, 0.0);
		basis_ = Matrix(dim_, dim_, eilig::matrix_zeros);

		for (Index i = 0; i < dim_; ++i)
		{
			basis_(i, i) = 1.0;
		}
	}
	CartesianPtr Cartesian::Create()
	{
		class MakeSharedEnabler : public Cartesian
		{
		};

		auto res = std::make_shared<MakeSharedEnabler>();

		return res;
	}
	CartesianPtr Cartesian::GetPtr()
	{
		return this->shared_from_this();
	}
	ConstCartesianPtr Cartesian::GetPtr() const
	{
		return const_cast<Cartesian*>(this)->GetPtr();
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
	Vector Cartesian::LocalToGlobal(const Vector& pt) const
	{
		return origin_ + basis_.Transpose() * pt;
	}
	Vector Cartesian::LocalToGlobalVector(const Vector& vec) const
	{
		return basis_.Transpose() * vec;
	}
	Vector Cartesian::GlobalToLocal(const Vector& pt) const
	{
		return basis_ * (pt - origin_);
	}
	Vector Cartesian::GlobalToLocalVector(const Vector& vec) const
	{
		return basis_ * vec;
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
	Dimension Cartesian::GetDim() const
	{
		return dim_;
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
		basis_ = eilig::transform::RotationMatrix(axis, radians).Transpose() * basis_;
	}
	void Cartesian::SetTag(Tag tag)
	{
		tag_ = tag;
	}
	
} //namespace basis