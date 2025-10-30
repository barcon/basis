#ifndef BASIS_TYPES_HPP_
#define BASIS_TYPES_HPP_

#include "eilig.hpp"
#include <memory>

namespace basis
{
	using Axis = eilig::Axis;
	using Scalar = eilig::Scalar;
	using Vector = eilig::Vector;
	using Matrix = eilig::Matrix;

	using Dimension = std::size_t;
	using Tag = std::size_t;
	using Type = std::size_t;
	using Index = std::size_t;

	class IBasis;
	using IBasisPtr = std::shared_ptr<IBasis>;
	using ConstIBasisPtr = std::shared_ptr<const IBasis>;

	static const Type basis_cartesian = 1;
	static const Type basis_cylindrical = 2;

	class IBasis
	{
	public:
		virtual ~IBasis() = default;

		virtual Scalar Distance(const Vector& pt1, const Vector& pt2) const = 0;
		virtual Scalar DistanceSquared(const Vector& pt1, const Vector& pt2) const = 0;
		virtual Vector LocalToGlobal(const Vector& pt) const = 0;
		virtual Vector LocalToGlobalVector(const Vector& vec) const = 0;
		virtual Vector GlobalToLocal(const Vector& pt) const = 0;
		virtual Vector GlobalToLocalVector(const Vector& vec) const = 0;

		virtual const Matrix& GetBasis() const = 0;
		virtual const Vector& GetOrigin() const = 0;
		virtual Tag GetTag() const = 0;
		virtual Dimension GetDim() const = 0;
		virtual Type GetType() const = 0;
		
		virtual void Offset(const Vector& delta) = 0;
		virtual void Offset(const Axis& axis, Scalar delta) = 0;
		virtual void Rotate(const Axis& axis, Scalar radians) = 0;

		virtual void SetTag(Tag tag) = 0;
	};
} //namespace basis

#endif /* BASIS_TYPE_HPP_ */