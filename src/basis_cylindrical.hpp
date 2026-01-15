#ifndef BASIS_CYLINDRICAL_HPP_
#define BASIS_CYLINDRICAL_HPP_

#include "basis_types.hpp"

namespace basis
{
	class Cylindrical;
	using CylindricalPtr = std::shared_ptr<Cylindrical>;
	using ConstCylindricalPtr = std::shared_ptr<const Cylindrical>;	

	CylindricalPtr CreateBasisCylindrical();
	CylindricalPtr CreateBasisCylindrical(Tag basisTag);
	
	class Cylindrical : public IBasis, virtual public std::enable_shared_from_this<Cylindrical>
	{
	public:
		virtual ~Cylindrical() = default;

		static CylindricalPtr Create();
		CylindricalPtr GetPtr();
		ConstCylindricalPtr GetPtr() const;

		Scalar Distance(const Vector& pt1, const Vector& pt2) const override;
		Scalar DistanceSquared(const Vector& pt1, const Vector& pt2) const override;
		Vector LocalToGlobalPoint(const Vector& pt) const override;
		Vector LocalToGlobalVector(const Vector& vec) const override;
		Vector GlobalToLocalPoint(const Vector& pt) const override;
		Vector GlobalToLocalVector(const Vector& vec) const override;
		
		const Matrix& GetBasis() const override;
		const Vector& GetOrigin() const override;
		Tag GetTag() const override;
		Dimension GetDim() const override;		
		Type GetType() const override;	
		
		void Offset(const Vector& delta) override;
		void Offset(const Axis& axis, Scalar value) override;
		void Rotate(const Axis& axis, Scalar radians) override;
		
		void SetOrigin(const Vector& origin) override;
		void SetTag(Tag tag) override;

	protected:
		Cylindrical();

		Tag tag_{ 0 };			
		Vector origin_;
		Matrix basis_;

		const Dimension dim_{ 3 };
		const Type type_{basis_cylindrical};
	};
	
} //namespace basis

#endif /* BASIS_CYLINDRICAL_HPP_ */