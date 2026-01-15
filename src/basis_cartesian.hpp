#ifndef BASIS_CARTESIAN_HPP_
#define BASIS_CARTESIAN_HPP_

#include "basis_types.hpp"

namespace basis
{
	class Cartesian;
	using CartesianPtr = std::shared_ptr<Cartesian>;
	using ConstCartesianPtr = std::shared_ptr<const Cartesian>;	

	CartesianPtr CreateBasisCartesian();
	CartesianPtr CreateBasisCartesian(Tag basisTag);
	
	class Cartesian : public IBasis, virtual public std::enable_shared_from_this<Cartesian>
	{
	public:
		virtual ~Cartesian() = default;

		static CartesianPtr Create();
		CartesianPtr GetPtr();
		ConstCartesianPtr GetPtr() const;

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
		void Offset(const Axis& axis, Scalar delta) override;
		void Rotate(const Axis& axis, Scalar radians) override;
		
		void SetOrigin(const Vector& origin) override;
		void SetTag(Tag tag) override;

	protected:
		Cartesian();

		Tag tag_{ 0 };			
		Vector origin_;
		Matrix basis_;

		const Dimension dim_{ 3 };
		const Type type_{basis_cartesian};
	};
	
} //namespace basis

#endif /* BASIS_CARTESIAN_HPP_ */