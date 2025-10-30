#ifndef BASIS_CARTESIAN_HPP_
#define BASIS_CARTESIAN_HPP_

#include "basis_types.hpp"

namespace basis
{
	class Cartesian : public IBasis
	{
	public:
		virtual ~Cartesian() = default;

		Cartesian();
		Cartesian(Tag basisTag);

		Scalar Distance(const Vector& pt1, const Vector& pt2) const override;
		Scalar DistanceSquared(const Vector& pt1, const Vector& pt2) const override;
		Vector LocalToGlobal(const Vector& pt) const override;
		Vector LocalToGlobalVector(const Vector& vec) const override;
		Vector GlobalToLocal(const Vector& pt) const override;
		Vector GlobalToLocalVector(const Vector& vec) const override;
		
		const Matrix& GetBasis() const override;
		const Vector& GetOrigin() const override;
		Tag GetTag() const override;
		Dimension GetDim() const override;		
		Type GetType() const override;	
		
		void Offset(const Vector& delta) override;
		void Offset(const Axis& axis, Scalar delta) override;
		void Rotate(const Axis& axis, Scalar radians) override;
		
		void SetTag(Tag tag) override;

	protected:
		Tag tag_{ 0 };
		Vector origin_;
		Matrix basis_;

		const Dimension dim_{ 3 };
		const Type type_{basis_cartesian};
	};
	
} //namespace basis

#endif /* BASIS_CARTESIAN_HPP_ */