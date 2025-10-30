#include "basis_cylindrical.hpp"
#include <cmath>

namespace basis
{
	CylindricalPtr CreateBasisCylindrical()
	{
		auto res = Cylindrical::Create();

		return res;
	}
	CylindricalPtr CreateBasisCylindrical(Tag basisTag)
	{
		auto res = Cylindrical::Create();

		res->SetTag(basisTag);

		return res;
	}
	Cylindrical::Cylindrical()
	{
		origin_ = Vector(dim_, 0.0);
		basis_ = Matrix(dim_, dim_, eilig::matrix_zeros);

		for (Index i = 0; i < dim_; ++i)
		{
			basis_(i, i) = 1.0;
		}
	}
	CylindricalPtr Cylindrical::Create()
	{
		class MakeSharedEnabler : public Cylindrical
		{
		};

		auto res = std::make_shared<MakeSharedEnabler>();

		return res;
	}
	CylindricalPtr Cylindrical::GetPtr()
	{
		return this->shared_from_this();
	}
	ConstCylindricalPtr Cylindrical::GetPtr() const
	{
		return const_cast<Cylindrical*>(this)->GetPtr();
	}
	Scalar Cylindrical::Distance(const Vector& pt1, const Vector& pt2) const
	{
		Vector dif = pt2 - pt1;
		Scalar res = pt1(0) * pt1(0) + pt2(0) * pt2(0) - 2.0 * pt1(0) * pt2(0) * cos(dif(1)) + dif(2) * dif(2);

		res = std::sqrt(res);

		return res;
	}
	Scalar Cylindrical::DistanceSquared(const Vector& pt1, const Vector& pt2) const
	{
		Vector dif = pt2 - pt1;
		Scalar res = pt1(0) * pt1(0) + pt2(0) * pt2(0) - 2.0 * pt1(0) * pt2(0) * cos(dif(1)) + dif(2) * dif(2);

		return res;
	}
	Vector Cylindrical::LocalToGlobal(const Vector& pt) const
	{
		Vector cartesian(dim_, 0.0);

		cartesian(0) = pt(0) * cos(pt(1));
		cartesian(1) = pt(0) * sin(pt(1));
		cartesian(2) = pt(2);

		return origin_ + basis_.Transpose() * cartesian;
	}
	Vector Cylindrical::LocalToGlobalVector(const Vector& vec) const
	{
		Vector cartesian(dim_, 0.0);

		cartesian(0) = vec(0) * cos(vec(1));
		cartesian(1) = vec(0) * sin(vec(1));
		cartesian(2) = vec(2);

		return basis_.Transpose() * cartesian;
	}
	Vector Cylindrical::GlobalToLocal(const Vector& pt) const
	{
		Vector local(dim_, 0.0);
		Scalar radius{ 0.0 };
		Scalar theta{ 0.0 };

		local = basis_ * (pt - origin_);
		radius = std::sqrt(local(0) * local(0) + local(1) * local(1));
		theta = std::atan2(local(1), local(0));
		local(0) = radius;
		local(1) = theta;

		return local;
	}
	Vector Cylindrical::GlobalToLocalVector(const Vector& vec) const
	{
		Vector local(dim_, 0.0);
		Scalar radius{ 0.0 };
		Scalar theta{ 0.0 };

		local = basis_ * vec;
		radius = std::sqrt(local(0) * local(0) + local(1) * local(1));
		theta = std::atan2(local(1), local(0));
		local(0) = radius;
		local(1) = theta;

		return local;
	}
	const Matrix& Cylindrical::GetBasis() const
	{
		return basis_;
	}
	const Vector& Cylindrical::GetOrigin() const
	{
		return origin_;
	}
	Tag Cylindrical::GetTag() const
	{
		return tag_;
	}
	Dimension Cylindrical::GetDim() const
	{
		return dim_;
	}
	Type Cylindrical::GetType() const
	{
		return type_;
	}
	void Cylindrical::Offset(const Vector& delta)
	{
		origin_ = origin_ + delta;
	}
	void Cylindrical::Offset(const Axis& axis, Scalar delta)
	{
		origin_(axis) = origin_(axis) + delta;
	}
	void Cylindrical::Rotate(const Axis& axis, Scalar radians)
	{
		Matrix rot(3, 3);
		Scalar cos = std::cos(radians);
		Scalar sin = std::sin(radians);

		if (axis == eilig::axis_x)
		{
			rot(0, 0) = 1.;
			rot(1, 0) = 0.;
			rot(2, 0) = 0.;

			rot(0, 1) = 0.;
			rot(1, 1) = cos;
			rot(2, 1) = sin;

			rot(0, 2) = 0.;
			rot(1, 2) = -sin;
			rot(2, 2) = cos;
		}
		else if (axis == eilig::axis_y)
		{
			rot(0, 0) = cos;
			rot(1, 0) = 0.;
			rot(2, 0) = -sin;

			rot(0, 1) = 0.;
			rot(1, 1) = 1.;
			rot(2, 1) = 0.;

			rot(0, 2) = sin;
			rot(1, 2) = 0.;
			rot(2, 2) = cos;
		}
		else if (axis == eilig::axis_z)
		{
			rot(0, 0) = cos;
			rot(1, 0) = sin;
			rot(2, 0) = 0.;

			rot(0, 1) = -sin;
			rot(1, 1) = cos;
			rot(2, 1) = 0.;

			rot(0, 2) = 0.;
			rot(1, 2) = 0.;
			rot(2, 2) = 1.;
		}

		basis_ = rot.Transpose() * basis_;
	}
	void Cylindrical::SetTag(Tag tag)
	{
		tag_ = tag;
	}
	
} //namespace basis