#ifndef BASIS_TYPES_HPP_
#define BASIS_TYPES_HPP_

#include "eilig.hpp"
#include <memory>

namespace basis
{
	using namespace eilig;
	using NumberCoordinates = Number;

	class IBasis;
	using IBasisPtr = std::shared_ptr<IBasis>;
	using ConstIBasisPtr = std::shared_ptr<const IBasis>;

	enum class BasisType
	{
		cartesian = 0,
		cylindrical = 1
	};

	class IBasis
	{
	public:
		virtual ~IBasis() = default;

		virtual Scalar Distance(const Vector& pt1, const Vector& pt2) const = 0;
		virtual Scalar DistanceSquared(const Vector& pt1, const Vector& pt2) const = 0;
		virtual Vector LocalToGlobalPoint(const Vector& pt) const = 0;
		virtual Vector LocalToGlobalVector(const Vector& vec) const = 0;
		virtual Vector GlobalToLocalPoint(const Vector& pt) const = 0;
		virtual Vector GlobalToLocalVector(const Vector& vec) const = 0;

		virtual const Matrix& GetBasis() const = 0;
		virtual const Vector& GetOrigin() const = 0;
		virtual NumberCoordinates GetNumberCoordinates() const = 0;
		virtual BasisType GetType() const = 0;
		virtual Tag GetTag() const = 0;
		
		virtual void Offset(const Vector& delta) = 0;
		virtual void Offset(const Axis& axis, Scalar delta) = 0;
		virtual void Rotate(const Axis& axis, Scalar radians) = 0;

		virtual void SetOrigin(const Vector& origin) = 0;
		virtual void SetTag(Tag tag) = 0;
	};
} //namespace basis

#endif /* BASIS_TYPE_HPP_ */