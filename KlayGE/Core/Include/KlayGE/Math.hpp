// Math.hpp
// KlayGE 数学函数库 头文件
// Ver 2.1.1
// 版权所有(C) 龚敏敏, 2003-2004
// Homepage: http://klayge.sourceforge.net
//
// 2.1.1
// 修改了自定义类型 (2004.4.22)
// 增加了网格函数 (2004.5.18)
//
// 2.0.4
// 修改了Random的接口 (2004.3.29)
//
// 2.0.0
// 初次建立 (2003.9.18)
//
// 修改记录
///////////////////////////////////////////////////////////////////////////////

#ifndef _MATH_HPP
#define _MATH_HPP

#include <KlayGE/PreDeclare.hpp>

#include <limits>
#include <cstdlib>

#include <boost/static_assert.hpp>

#pragma comment(lib, "KlayGE_Core.lib")

namespace KlayGE
{
	// 常量定义
	/////////////////////////////////////////////////////////////////////////////////
	const float PI		= 3.141592f;			// PI
	const float PI2		= 6.283185f;			// PI * 2
	const float PIdiv2	= 1.570796f;			// PI / 2

	const float DEG90	= 1.570796f;			// 90 度
	const float DEG270	= -1.570796f;			// 270 度
	const float DEG45	= 0.7853981f;			// 45 度
	const float DEG5	= 0.0872664f;			// 5 度
	const float DEG10	= 0.1745329f;			// 10 度
	const float DEG20	= 0.3490658f;			// 20 度 
	const float DEG30	= 0.5235987f;			// 30 度
	const float DEG60	= 1.047197f;			// 60 度
	const float DEG120	= 2.094395f;			// 120 度

	const float DEG40	= 0.6981317f;			// 40 度
	const float DEG80	= 1.396263f;			// 80 度
	const float DEG140	= 2.443460f;			// 140 度
	const float DEG160	= 2.792526f;			// 160 度

	const float SQRT2	= 1.414213f;			// 根2
	const float SQRT_2	= 0.7071068f;			// 1 / SQRT2
	const float SQRT3	= 1.732050f;			// 根3

	const float DEG2RAD	= 0.01745329f;			// 角度化弧度因数
	const float RAD2DEG	= 57.29577f;			// 弧度化角度因数

	namespace MathLib
	{
		// 求绝对值
		template <typename T>
		inline T
		Abs(const T& x)
		{
			return x < T(0) ? -x : x;
		}

		// 取符号
		template <typename T>
		inline T
		Sgn(const T& x)
		{
			return x < T(0) ? T(-1) : (x > T(0) ? T(1) : T(0));
		}
		
		// 平方
		template <typename T>
		inline T
		Sqr(const T& x)
		{
			return x * x;
		}
		// 立方
		template <typename T>
		inline T
		Cube(const T& x)
		{
			return Sqr(x) * x;
		}

		// 角度化弧度
		template <typename T>
		inline T
		Deg2Rad(const T& x)
		{
			return static_cast<T>(x * DEG2RAD);
		}
		// 弧度化角度
		template <typename T>
		inline T
		Rad2Deg(const T& x)
		{
			return static_cast<T>(x * RAD2DEG);
		}

		// 四舍五入
		template <typename T>
		inline T
		Round(const T& x)
		{
			return (x > 0) ? static_cast<T>(static_cast<int>(0.5f + x)) :
					-static_cast<T>(static_cast<int>(0.5f - x));
		}
		// 取整
		template <typename T>
		inline T
		Trunc(const T& x)
		{
			return static_cast<T>(static_cast<int>(x));
		}

		// 取三个中小的
		template <typename T>
		inline const T&
		Min3(const T& a, const T& b, const T& c)
		{
			return std::min(std::min(a, b), c);
		}
		// 取三个中大的
		template <typename T>
		inline const T&
		Max3(const T& a, const T& b, const T& c)
		{
			return std::max(std::max(a, b), c);
		}

		// 余数
		template <typename T>
		inline T
		Mod(const T& x, const T& y)
		{
			return x % y;
		}
		// 浮点版本
		inline float
		Mod(const float& x, const float& y)
		{
			return std::fmodf(x, y);
		}
		inline double
		Mod(const double& x, const double& y)
		{
			return std::fmod(x, y);
		}

		// 求和
		template <typename InputIterator, typename T>
		inline T
		Sum(InputIterator first, InputIterator last)
		{
			T sum(0);
			for (InputIterator i = first; i != last; ++ i)
			{
				sum += (*i);
			}
			return sum;
		}

		// 平均数
		template <typename InputIterator, typename T>
		inline T
		Avg(InputIterator first, InputIterator last)
		{
			return MathLib::Sum(first, last) / (last - first);
		}

		// 限制 val 在 low 和 high 之间
		template <typename T>
		inline const T&
		Limit(const T& val, const T& low, const T& high)
		{
			return std::max(low, std::min(high, val));
		}

		// 环绕处理
		template <typename T>
		inline T
		Surround(const T& val, const T& low, const T& high)
		{
			T ret(val);
			T rang(high - low);

			while (ret >= high)
			{
				ret -= rang;
			}
			while (ret < low)
			{
				ret += rang;
			}

			return ret;
		}

		// 奇数则返回true
		template <typename T>
		inline bool
		IsOdd(const T& x)
		{
			return MathLib::Mod(x, 2) != 0;
		}
		// 偶数则返回true
		template <typename T>
		inline bool
		IsEven(const T& x)
		{
			return !MathLib::IsOdd(x);
		}

		// 判断 val 是否在 low 和 high 之间
		template <typename T>
		inline bool
		InBound(const T& val, const T& low, const T& high)
		{
			return ((val >= low) && (val <= high));
		}
		
		// 判断两个数是否相等
		template <typename T>
		inline bool
		Eq(const T& lhs, const T& rhs)
		{
			return (lhs == rhs);
		}
		// 浮点版本
		inline bool
		Eq(float lhs, float rhs)
		{
			return (MathLib::Abs<float>(lhs - rhs)
				<= std::numeric_limits<float>::epsilon());
		}
		inline bool
		Eq(double lhs, double rhs)
		{
			return (MathLib::Abs<double>(lhs - rhs)
				<= std::numeric_limits<double>::epsilon());
		}


		// 基本数学运算
		///////////////////////////////////////////////////////////////////////////////
		inline float
		Abs(float x)
		{
			return std::fabsf(x);
		}
		inline float
		Sqrt(float x)
		{
			return std::sqrtf(x);
		}
		inline float
		RecipSqrt(float x)
		{
			float xhalf = 0.5f * x;
			int n = *reinterpret_cast<int*>(&x);	// get bits for floating value
			n = 0x5f3759df - (n >> 1);				// gives initial guess y0
			x = *reinterpret_cast<float*>(&n);		// convert bits back to float
			x = x * (1.5f - xhalf * x * x);			// Newton step, repeating increases accuracy

			return x;
		}

		inline float
		Pow(float x, float y)
		{
			return std::powf(x, y);
		}
		inline float
		Exp(float x)
		{
			return std::expf(x);
		}

		inline float
		Log(float x)
		{
			return std::logf(x);
		}
		inline float
		Log10(float x)
		{
			return std::log10f(x);
		}

		inline float
		Sin(float x)
		{
			return std::sinf(x);
		}
		inline float
		Cos(float x)
		{
			return Sin(x + PI / 2);
		}
		inline void
		SinCos(float x, float& s, float& c)
		{
			s = Sin(x);
			c = Cos(x);
		}
		inline float
		Tan(float x)
		{
			return std::tanf(x);
		}

		inline float
		ASin(float x)
		{
			return std::asinf(x);
		}
		inline float
		ACos(float x)
		{
			return std::acosf(x);
		}
		inline float
		ATan(float x)
		{
			return std::atanf(x);
		}

		inline float
		Sinh(float x)
		{
			return std::sinhf(x);
		}
		inline float
		Cosh(float x)
		{
			return std::coshf(x);
		}
		inline float
		Tanh(float x)
		{
			return std::tanhf(x);
		}


		template <typename T, int N>
		struct DotHelper
		{
			static T Do(const T* lhs, const T* rhs)
			{
				return lhs[0] * rhs[0] + DotHelper<T, N - 1>::Do(lhs + 1, rhs + 1);
			}
		};
		template <typename T>
		struct DotHelper<T, 1>
		{
			static T Do(const T* lhs, const T* rhs)
			{
				return lhs[0] * rhs[0];
			}
		};

		// 几种类型的Dot
		template <typename T>
		inline typename T::value_type
		Dot(const T& lhs, const T& rhs)
		{
			return DotHelper<T::value_type, T::elem_num>::Do(&lhs[0], &rhs[0]);
		}

		// 几种类型的LengthSq
		template <typename T>
		inline typename T::value_type
		LengthSq(const T& rhs)
		{
			return MathLib::Dot(rhs, rhs);
		}

		// 几种类型的Length
		template <typename T>
		inline typename T::value_type
		Length(const T& rhs)
		{
			return MathLib::Sqrt(MathLib::LengthSq(rhs));
		}

		// 几种类型的Lerp
		template <typename T>
		inline T&
		Lerp(T& out, const T& lhs, const T& rhs, float s)
		{
			out = lhs + (rhs - lhs) * s;
			return out;
		}

		template <typename T, int N>
		struct MaxMinimizeHelper
		{
			static void DoMax(T out[N], const T lhs[N], const T rhs[N])
			{
				out[0] = std::max(lhs[0], rhs[0]);
				MaxMinimizeHelper<T, N - 1>::DoMax(out + 1, lhs + 1, rhs + 1);
			}

			static void DoMin(T out[N], const T lhs[N], const T rhs[N])
			{
				out[0] = std::min(lhs[0], rhs[0]);
				MaxMinimizeHelper<T, N - 1>::DoMin(out + 1, lhs + 1, rhs + 1);
			}
		};
		template <typename T>
		struct MaxMinimizeHelper<T, 1>
		{
			static void DoMax(T out[1], const T lhs[1], const T rhs[1])
			{
				out[0] = std::max(lhs[0], rhs[0]);
			}

			static void DoMin(T out[1], const T lhs[1], const T rhs[1])
			{
				out[0] = std::min(lhs[0], rhs[0]);
			}
		};

		template <typename T, int N>
		inline Vector_T<T, N>&
		Maximize(Vector_T<T, N>& out,
			const Vector_T<T, N>& lhs, const Vector_T<T, N>& rhs)
		{
			MaxMinimizeHelper<T, N>::DoMax(&out[0], &lhs[0], &rhs[0]);
			return out;
		}

		template <typename T, int N>
		inline Vector_T<T, N>&
		Minimize(Vector_T<T, N>& out,
			const Vector_T<T, N>& lhs, const Vector_T<T, N>& rhs)
		{
			MaxMinimizeHelper<T, N>::DoMin(&out[0], &lhs[0], &rhs[0]);
			return out;
		}

		template <typename T, int N>
		struct TransformHelper
		{
			static void Do(Vector_T<T, 4>& out, const Vector_T<T, N>& v, const Matrix4& mat);
		};
		template <typename T>
		struct TransformHelper<T, 4>
		{
			static void Do(Vector_T<T, 4>& out, const Vector_T<T, 4>& v, const Matrix4& mat)
			{
				out = Vector_T<T, 4>(v.x() * mat(0, 0) + v.y() * mat(1, 0) + v.z() * mat(2, 0) + v.w() * mat(3, 0),
					v.x() * mat(0, 1) + v.y() * mat(1, 1) + v.z() * mat(2, 1) + v.w() * mat(3, 1),
					v.x() * mat(0, 2) + v.y() * mat(1, 2) + v.z() * mat(2, 2) + v.w() * mat(3, 2),
					v.x() * mat(0, 3) + v.y() * mat(1, 3) + v.z() * mat(2, 3) + v.w() * mat(3, 3));
			}
		};
		template <typename T>
		struct TransformHelper<T, 3>
		{
			static void Do(Vector_T<T, 4>& out, const Vector_T<T, 3>& v, const Matrix4& mat)
			{
				out = Vector_T<T, 4>(v.x() * mat(0, 0) + v.y() * mat(1, 0) + v.z() * mat(2, 0) + mat(3, 0),
					v.x() * mat(0, 1) + v.y() * mat(1, 1) + v.z() * mat(2, 1) + mat(3, 1),
					v.x() * mat(0, 2) + v.y() * mat(1, 2) + v.z() * mat(2, 2) + mat(3, 2),
					v.x() * mat(0, 3) + v.y() * mat(1, 3) + v.z() * mat(2, 3) + mat(3, 3));
			}
		};
		template <typename T>
		struct TransformHelper<T, 2>
		{
			static void Do(Vector_T<T, 4>& out, const Vector_T<T, 2>& v, const Matrix4& mat)
			{
				out = Vector_T<T, 4>(v.x() * mat(0, 0) + v.y() * mat(1, 0) + mat(3, 0),
					v.x() * mat(0, 1) + v.y() * mat(1, 1) + mat(3, 1),
					v.x() * mat(0, 2) + v.y() * mat(1, 2) + mat(3, 2),
					v.x() * mat(0, 3) + v.y() * mat(1, 3) + mat(3, 3));
			}
		};

		template <typename T, int N>
		inline Vector_T<T, 4>&
		Transform(Vector_T<T, 4>& out, const Vector_T<T, N>& v, const Matrix4& mat)
		{
			TransformHelper<T, N>::Do(out, v, mat);
			return out;
		}

		template <typename T, int N>
		inline Vector_T<T, N>&
		TransformCoord(Vector_T<T, N>& out, const Vector_T<T, N>& v, const Matrix4& mat)
		{
			BOOST_STATIC_ASSERT(N < 4);

			Vector_T<T, 4> temp;
			TransformHelper<T, N>::Do(temp, v, mat);
			out = Vector_T<T, N>(&temp[0]);
			if (Eq(temp.w(), T(0)))
			{
				out = Vector_T<T, N>::Zero();
			}
			else
			{
				out /= temp.w();
			}
			return out;
		}


		template <typename T, int N>
		struct TransformNormalHelper
		{
			static void Do(Vector_T<T, N>& out, const Vector_T<T, N>& v, const Matrix4& mat);
		};
		template <typename T>
		struct TransformNormalHelper<T, 3>
		{
			static void Do(Vector_T<T, 3>& out, const Vector_T<T, 3>& v, const Matrix4& mat)
			{
				Vector_T<T, 4> temp(v.x(), v.y(), v.z(), T(0));
				TransformHelper<T, 4>::Do(temp, temp, mat);
				out = Vector_T<T, 3>(&temp[0]);
			}
		};
		template <typename T>
		struct TransformNormalHelper<T, 2>
		{
			static void Do(Vector_T<T, 2>& out, const Vector_T<T, 2>& v, const Matrix4& mat)
			{
				Vector_T<T, 3> temp(v.x(), v.y(), T(0));
				TransformNormalHelper<T, 3>::Do(temp, temp, mat);
				out = Vector_T<T, 2>(&temp[0]);
			}
		};

		template <typename T, int N>
		inline Vector_T<T, N>&
		TransformNormal(Vector_T<T, N>& out, const Vector_T<T, N>& v, const Matrix4& mat)
		{
			BOOST_STATIC_ASSERT(N < 4);

			TransformNormalHelper<T, N>::Do(out, v, mat);
			return out;
		}

		template <typename T, int N>
		inline Vector_T<T, N>&
		BaryCentric(Vector_T<T, N>& out,
			const Vector_T<T, N>& v1, const Vector_T<T, N>& v2, const Vector_T<T, N>& v3,
			const T& f, const T& g)
		{
			out = v1 + f * (v2 - v1) + g * (v3 - v1);
			return out;
		}

		template <typename T>
		inline T&
		Normalize(T& out, const T& rhs)
		{
			out = rhs * RecipSqrt(LengthSq(rhs));
			return out;
		}


		// 2D 向量
		///////////////////////////////////////////////////////////////////////////////
		template <typename T>
		inline T
		CCW(const Vector_T<T, 2>& lhs, const Vector_T<T, 2>& rhs)
		{
			return lhs.x() * rhs.y() - lhs.y() * rhs.x();
		}


		// 3D 向量
		///////////////////////////////////////////////////////////////////////////////
		template <typename T>
		inline T
		Angle(const Vector_T<T, 3>& lhs, const Vector_T<T, 3>& rhs)
		{
			return ACos(Dot(lhs, rhs) / (Length(lhs) * Length(rhs)));
		}

		template <typename T>
		inline Vector_T<T, 3>&
		Cross(Vector_T<T, 3>& out, const Vector_T<T, 3>& lhs, const Vector_T<T, 3>& rhs)
		{
			out = Vector_T<T, 3>(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
				lhs.z() * rhs.x() - lhs.x() * rhs.z(),
				lhs.x() * rhs.y() - lhs.y() * rhs.x());
			return out;
		}

		template <typename T>
		inline Vector_T<T, 3>&
		TransQuat(Vector_T<T, 3>& out, const Vector_T<T, 3>& v, const Quaternion_T<T>& quat)
		{
			// result = av + bq + c(q.v CROSS v)
			// where
			//  a = q.w()^2 - (q.v DOT q.v)
			//  b = 2 * (q.v DOT v)
			//  c = 2q.w()
			const T a(quat.w() * quat.w() - Dot(quat.v(), quat.v()));
			const T b(2 * Dot(quat.v(), v));
			const T c(quat.w() + quat.w());

			// Must store this, because result may alias v
			Vector_T<T, 3> cross;
			Cross(cross, quat.v(), v);		// q.v CROSS v

			out = Vector_T<T, 3>(a * v.x() + b * quat.x() + c * cross.x(),
				a * v.y() + b * quat.y() + c * cross.y(),
				a * v.z() + b * quat.z() + c * cross.z());
			return out;
		}

		template <typename T>
		inline Vector_T<T, 3>&
		Project(Vector_T<T, 3>& out, const Vector_T<T, 3>& vec,
			const Matrix4_T<T>& world, const Matrix4_T<T>& view, const Matrix4_T<T>& proj,
			const int viewport[4], const T& nearPlane, const T& farPlane)
		{
			Vector_T<T, 4> temp;
			Transform(temp, objVec, world);
			Transform(temp, temp, view);
			Transform(temp, temp, proj);
			temp /= temp.w();

			out.x() = (temp.x() + 1) * viewport[2] / 2 + viewport[0];
			out.y() = (-temp.y() + 1) * viewport[3] / 2 + viewport[1];
			out.z() = (temp.z() + 1) * (farPlane - nearPlane) / 2 + nearPlane;
			return out;
		}

		template <typename T>
		inline Vector_T<T, 3>&
		UnProject(Vector_T<T, 3>& out, const Vector_T<T, 3>& winVec, const T& clipW,
			const Matrix4_T<T>& world, const Matrix4_T<T>& view, const Matrix4_T<T>& proj,
			const int viewport[4], const T& nearPlane, const T& farPlane)
		{
			Vector_T<T, 4> temp;
			temp.x() = 2 * (winVec.x() - viewport[0]) / viewport[2] - 1;
			temp.y() = -(2 * (winVec.y() - viewport[1]) / viewport[3] - 1);
			temp.z() = 2 * (winVec.z() - nearPlane) / (farPlane - nearPlane) - 1;
			temp.w() = clipW;

			Matrix4_T<T> mat;
			Inverse(mat, world * view * proj);
			Transform(temp, temp, mat);
			out = Vector_T<T, 3>(temp.x(), temp.y(), temp.z());
			out /= temp.w();
			return out;
		}


		// 4D 向量
		///////////////////////////////////////////////////////////////////////////////
		template <typename T>
		inline Vector_T<T, 4>&
		Cross(Vector_T<T, 4>& out, const Vector_T<T, 4>& v1, const Vector_T<T, 4>& v2, const Vector_T<T, 4>& v3)
		{
			const T A = (v2.x() * v3.y()) - (v2.y() * v3.x());
			const T B = (v2.x() * v3.z()) - (v2.z() * v3.x());
			const T C = (v2.x() * v3.w()) - (v2.w() * v3.x());
			const T D = (v2.y() * v3.z()) - (v2.z() * v3.y());
			const T E = (v2.y() * v3.w()) - (v2.w() * v3.y());
			const T F = (v2.z() * v3.w()) - (v2.w() * v3.z());

			out = Vector_T<T, 4>((v1.y() * F) - (v1.z() * E) + (v1.w() * D),
				-(v1.x() * F) + (v1.z() * C) - (v1.w() * B),
				(v1.x() * E) - (v1.y() * C) + (v1.w() * A),
				-(v1.x() * D) + (v1.y() * B) - (v1.z() * A));
			return out;
		}


		// 4D 矩阵
		///////////////////////////////////////////////////////////////////////////////
		template <typename T>
		inline Matrix4_T<T>&
		Multiply(Matrix4_T<T>& out, const Matrix4_T<T>& lhs, const Matrix4_T<T>& rhs)
		{
			out = Matrix4_T<T>(
				lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0),
				lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1),
				lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2),
				lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3) + lhs(0, 3) * rhs(3, 3),

				lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0),
				lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1),
				lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2),
				lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3) + lhs(1, 3) * rhs(3, 3),

				lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0),
				lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1),
				lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2),
				lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3) + lhs(2, 2) * rhs(2, 3) + lhs(2, 3) * rhs(3, 3),

				lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0) + lhs(3, 2) * rhs(2, 0) + lhs(3, 3) * rhs(3, 0),
				lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1) + lhs(3, 3) * rhs(3, 1),
				lhs(3, 0) * rhs(0, 2) + lhs(3, 1) * rhs(1, 2) + lhs(3, 2) * rhs(2, 2) + lhs(3, 3) * rhs(3, 2),
				lhs(3, 0) * rhs(0, 3) + lhs(3, 1) * rhs(1, 3) + lhs(3, 2) * rhs(2, 3) + lhs(3, 3) * rhs(3, 3));
			return out;
		}

		template <typename T>
		inline T
		Determinant(const Matrix4_T<T>& rhs)
		{
			const T _3142_3241(rhs(2, 0) * rhs(3, 1) - rhs(2, 1) * rhs(3, 0));
			const T _3143_3341(rhs(2, 0) * rhs(3, 2) - rhs(2, 2) * rhs(3, 0));
			const T _3144_3441(rhs(2, 0) * rhs(3, 3) - rhs(2, 3) * rhs(3, 0));
			const T _3243_3342(rhs(2, 1) * rhs(3, 2) - rhs(2, 2) * rhs(3, 1));
			const T _3244_3442(rhs(2, 1) * rhs(3, 3) - rhs(2, 3) * rhs(3, 1));
			const T _3344_3443(rhs(2, 2) * rhs(3, 3) - rhs(2, 3) * rhs(3, 2));

			return rhs(0, 0) * (rhs(1, 1) * _3344_3443 - rhs(1, 2) * _3244_3442 + rhs(1, 3) * _3243_3342)
				- rhs(0, 1) * (rhs(1, 0) * _3344_3443 - rhs(1, 2) * _3144_3441 + rhs(1, 3) * _3143_3341)
				+ rhs(0, 2) * (rhs(1, 0) * _3244_3442 - rhs(1, 1) * _3144_3441 + rhs(1, 3) * _3142_3241)
				- rhs(0, 3) * (rhs(1, 0) * _3243_3342 - rhs(1, 1) * _3143_3341 + rhs(1, 2) * _3142_3241);
		}

		template <typename T>
		inline T
		Inverse(Matrix4_T<T>& out, const Matrix4_T<T>& rhs)
		{
			const T _2132_2231(rhs(1, 0) * rhs(2, 1) - rhs(1, 1) * rhs(2, 0));
			const T _2133_2331(rhs(1, 0) * rhs(2, 2) - rhs(1, 2) * rhs(2, 0));
			const T _2134_2431(rhs(1, 0) * rhs(2, 3) - rhs(1, 3) * rhs(2, 0));
			const T _2142_2241(rhs(1, 0) * rhs(3, 1) - rhs(1, 1) * rhs(3, 0));
			const T _2143_2341(rhs(1, 0) * rhs(3, 2) - rhs(1, 2) * rhs(3, 0));
			const T _2144_2441(rhs(1, 0) * rhs(3, 3) - rhs(1, 3) * rhs(3, 0));
			const T _2233_2332(rhs(1, 1) * rhs(2, 2) - rhs(1, 2) * rhs(2, 1));
			const T _2234_2432(rhs(1, 1) * rhs(2, 3) - rhs(1, 3) * rhs(2, 1));
			const T _2243_2342(rhs(1, 1) * rhs(3, 2) - rhs(1, 2) * rhs(3, 1));
			const T _2244_2442(rhs(1, 1) * rhs(3, 3) - rhs(1, 3) * rhs(3, 1));
			const T _2334_2433(rhs(1, 2) * rhs(2, 3) - rhs(1, 3) * rhs(2, 2));
			const T _2344_2443(rhs(1, 2) * rhs(3, 3) - rhs(1, 3) * rhs(3, 2));
			const T _3142_3241(rhs(2, 0) * rhs(3, 1) - rhs(2, 1) * rhs(3, 0));
			const T _3143_3341(rhs(2, 0) * rhs(3, 2) - rhs(2, 2) * rhs(3, 0));
			const T _3144_3441(rhs(2, 0) * rhs(3, 3) - rhs(2, 3) * rhs(3, 0));
			const T _3243_3342(rhs(2, 1) * rhs(3, 2) - rhs(2, 2) * rhs(3, 1));
			const T _3244_3442(rhs(2, 1) * rhs(3, 3) - rhs(2, 3) * rhs(3, 1));
			const T _3344_3443(rhs(2, 2) * rhs(3, 3) - rhs(2, 3) * rhs(3, 2));

			// 行列式的值
			const T det(Determinant(rhs));
			if (!Eq(det, 0.0f))
			{
				T invDet(1.0f / det);

				out = Matrix4(
					+invDet * (rhs(1, 1) * _3344_3443 - rhs(1, 2) * _3244_3442 + rhs(1, 3) * _3243_3342),
					-invDet * (rhs(0, 1) * _3344_3443 - rhs(0, 2) * _3244_3442 + rhs(0, 3) * _3243_3342),
					+invDet * (rhs(0, 1) * _2344_2443 - rhs(0, 2) * _2244_2442 + rhs(0, 3) * _2243_2342),
					-invDet * (rhs(0, 1) * _2334_2433 - rhs(0, 2) * _2234_2432 + rhs(0, 3) * _2233_2332),

					-invDet * (rhs(1, 0) * _3344_3443 - rhs(1, 2) * _3144_3441 + rhs(1, 3) * _3143_3341),
					+invDet * (rhs(0, 0) * _3344_3443 - rhs(0, 2) * _3144_3441 + rhs(0, 3) * _3143_3341),
					-invDet * (rhs(0, 0) * _2344_2443 - rhs(0, 2) * _2144_2441 + rhs(0, 3) * _2143_2341),
					+invDet * (rhs(0, 0) * _2334_2433 - rhs(0, 2) * _2134_2431 + rhs(0, 3) * _2133_2331),

					+invDet * (rhs(1, 0) * _3244_3442 - rhs(1, 1) * _3144_3441 + rhs(1, 3) * _3142_3241),
					-invDet * (rhs(0, 0) * _3244_3442 - rhs(0, 1) * _3144_3441 + rhs(0, 3) * _3142_3241),
					+invDet * (rhs(0, 0) * _2244_2442 - rhs(0, 1) * _2144_2441 + rhs(0, 3) * _2142_2241),
					-invDet * (rhs(0, 0) * _2234_2432 - rhs(0, 1) * _2134_2431 + rhs(0, 3) * _2132_2231),

					-invDet * (rhs(1, 0) * _3243_3342 - rhs(1, 1) * _3143_3341 + rhs(1, 2) * _3142_3241),
					+invDet * (rhs(0, 0) * _3243_3342 - rhs(0, 1) * _3143_3341 + rhs(0, 2) * _3142_3241),
					-invDet * (rhs(0, 0) * _2243_2342 - rhs(0, 1) * _2143_2341 + rhs(0, 2) * _2142_2241),
					+invDet * (rhs(0, 0) * _2233_2332 - rhs(0, 1) * _2133_2331 + rhs(0, 2) * _2132_2231));
			}
			else
			{
				out = rhs;
			}

			return det;
		}

		template <typename T>
		inline Matrix4_T<T>&
		LookAtLH(Matrix4_T<T>& out, const Vector_T<T, 3>& vEye, const Vector_T<T, 3>& vAt,
			const Vector_T<T, 3>& vUp = Vector_T<T, 3>(0, 1, 0))
		{
			Vector_T<T, 3> zAxis;
			Normalize(zAxis, vAt - vEye);
			Vector_T<T, 3> xAxis;
			Cross(xAxis, vUp, zAxis);
			Normalize(xAxis, xAxis);
			Vector_T<T, 3> yAxis;
			Cross(yAxis, zAxis, xAxis);

			out = Matrix4_T<T>(
				xAxis.x(),			yAxis.x(),			zAxis.x(),			0,
				xAxis.y(),			yAxis.y(),			zAxis.y(),			0,
				xAxis.z(),			yAxis.z(),			zAxis.z(),			0,
				-Dot(xAxis, vEye),	-Dot(yAxis, vEye),	-Dot(zAxis, vEye),	1);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		LookAtRH(Matrix4_T<T>& out, const Vector_T<T, 3>& vEye, const Vector_T<T, 3>& vAt,
			const Vector_T<T, 3>& vUp = Vector_T<T, 3>(0, 1, 0))
		{
			Vector_T<T, 3> zAxis;
			Normalize(zAxis, vEye - vAt);
			Vector_T<T, 3> xAxis;
			Cross(xAxis, vUp, zAxis);
			Normalize(xAxis, xAxis);
			Vector_T<T, 3> yAxis;
			Cross(yAxis, zAxis, xAxis);

			out = Matrix4_T<T>(
				xAxis.x(),			yAxis.x(),			zAxis.x(),			0,
				xAxis.y(),			yAxis.y(),			zAxis.y(),			0,
				xAxis.z(),			yAxis.z(),			zAxis.z(),			0,
				-Dot(xAxis, vEye),	-Dot(yAxis, vEye),	-Dot(zAxis, vEye),	1);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		OrthoLH(Matrix4_T<T>& out, const T& w, const T& h, const T& nearPlane, const T& farPlane)
		{
			const T w_2(w / 2);
			const T h_2(h / 2);
			return OrthoOffCenterLH(out, -w_2, w_2, -h_2, h_2, nearPlane, farPlane);
		}
		template <typename T>
		inline Matrix4_T<T>&
		OrthoOffCenterLH(Matrix4_T<T>& out, const T& left, const T& right, const T& bottom, const T& top,
			const T& nearPlane, const T& farPlane)
		{
			const T q(T(1) / (farPlane - nearPlane));
			const T invWidth(T(1) / (right - left));
			const T invHeight(T(1) / (top - bottom));

			out = Matrix4_T<T>(
				invWidth + invWidth,		0,								0,					0,
				0,							invHeight + invHeight,			0,					0,
				0,							0,								q,					0,
				-(left + right) * invWidth,	-(top + bottom) * invHeight,	-nearPlane * q,		1);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		PerspectiveLH(Matrix4_T<T>& out, const T& width, const T& height, const T& nearPlane, const T& farPlane)
		{
			const T q(farPlane / (farPlane - nearPlane));
			const T near2(nearPlane + nearPlane);

			out = Matrix4_T<T>(
				near2 / width,	0,				0,				0,
				0,				near2 / height,	0,				0,
				0,				0,				q,				1,
				0,				0,				-nearPlane * q, 0);
			return out;
		}
		template <typename T>
		inline Matrix4_T<T>&
		PerspectiveFovLH(Matrix4_T<T>& out, const T& fov, const T& aspect, const T& nearPlane, const T& farPlane)
		{
			const T h(T(1) / Tan(fov / 2));
			const T w(h / aspect);
			const T q(farPlane / (farPlane - nearPlane));

			out = Matrix4_T<T>(
				w,		0,		0,				0,
				0,		h,		0,				0,
				0,		0,		q,				1,
				0,		0,		-nearPlane * q, 0);
			return out;
		}
		template <typename T>
		inline Matrix4_T<T>&
		PerspectiveOffCenterLH(Matrix4_T<T>& out, const T& left, const T& right, const T& bottom, const T& top,
			const T& nearPlane, const T& farPlane)
		{
			const T q(farPlane / (farPlane - nearPlane));
			const T near2(nearPlane + nearPlane);
			const T invWidth(T(1) / (right - left));
			const T invHeight(T(1) / (top - bottom));

			out = Matrix4_T<T>(
				near2 * invWidth,			0,								0,				0,
				0,							near2 * invHeight,				0,				0,
				-(left + right)* invWidth,	-(top + bottom) * invHeight,	q,				1,
				0,							0,								-nearPlane * q, 0);
			return out;
		}
		template <typename T>
		inline Matrix4_T<T>&
		Reflect(Matrix4_T<T>& out, const Plane_T<T>& p)
		{
			Plane_T<T> P;
			Normalize(P, p);
			const T aa2(-2 * P.a() * P.a()), ab2(-2 * P.a() * P.b()), ac2(-2 * P.a() * P.c()), ad2(-2 * P.a() * P.d());
			const T bb2(-2 * P.b() * P.b()), bc2(-2 * P.b() * P.c()), bd2(-2 * P.a() * P.c());
			const T cc2(-2 * P.c() * P.c()), cd2(-2 * P.c() * P.d());

			out = Matrix4_T<T>(
				aa2 + 1,	ab2,		ac2,		0,
				ab2,		bb2 + 1,	bc2,		0,
				ac2,		bc2,		cc2 + 1,	0,
				ad2,		bd2,		cd2,		1);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		RotationX(Matrix4_T<T>& out, const T& x)
		{
			float sx, cx;
			SinCos(x, sx, cx);

			out = Matrix4_T<T>(
				1,	0,		0,		0,
				0,	cx,		sx,		0,
				0,	-sx,	cx,		0,
				0,	0,		0,		1);
			return out;
		}
		template <typename T>
		inline Matrix4_T<T>&
		RotationY(Matrix4_T<T>& out, const T& y)
		{
			float sy, cy;
			SinCos(y, sy, cy);

			out = Matrix4_T<T>(
				cy,		0,		-sy,	0,
				0,		1,		0,		0,
				sy,		0,		cy,		0,
				0,		0,		0,		1);
			return out;
		}
		template <typename T>
		inline Matrix4_T<T>&
		RotationZ(Matrix4_T<T>& out, const T& z)
		{
			float sz, cz;
			SinCos(z, sz, cz);

			out = Matrix4_T<T>(
				cz,		sz,		0,		0,
				-sz,	cz,		0,		0,
				0,		0,		1,		0,
				0,		0,		0,		1);
			return out;
		}
		template <typename T>
		inline Matrix4_T<T>&
		Rotation(Matrix4_T<T>& out, const T& angle, const T& x, const T& y, const T& z)
		{
			Quaternion_T<T> quat;
			RotationAxis(quat, Vector_T<T, 3>(x, y, z), angle);
			return ToMatrix(out, quat);
		}

		template <typename T>
		inline Matrix4_T<T>&
		Scaling(Matrix4_T<T>& out, const T& x, const T& y, const T& z)
		{
			out = Matrix4(
				sx,	0,	0,	0,
				0,	sy,	0,	0,
				0,	0,	sz,	0,
				0,	0,	0,	1);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		Shadow(Matrix4_T<T>& out, const Vector_T<T, 4>& v, const Plane_T<T>& p)
		{
			const Vector_T<T, 4> v(-L);
			Plane_T<T> P;
			Normalize(P, p);
			const T d(-Dot(P, v));

			out = Matrix4_T<T>(
				P.a() * v.x() + d,	P.a() * v.y(),		P.a() * v.z(),		P.a() * v.w(),
				P.b() * v.x(),		P.b() * v.y() + d,	P.b() * v.z(),		P.b() * v.w(),
				P.c() * v.x(),		P.c() * v.y(),		P.c() * v.z() + d,	P.c() * v.w(),
				P.d() * v.x(),		P.d() * v.y(),		P.d() * v.z(),		P.d() * v.w() + d);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		ToMatrix(Matrix4_T<T>& out, const Quaternion_T<T>& quat)
		{
			// calculate coefficients
			const T x2(quat.x() + quat.x());
			const T y2(quat.y() + quat.y());
			const T z2(quat.z() + quat.z());

			const T xx2(quat.x() * x2), xy2(quat.x() * y2), xz2(quat.x() * z2);
			const T yy2(quat.y() * y2), yz2(quat.y() * z2), zz2(quat.z() * z2);
			const T wx2(quat.w() * x2), wy2(quat.w() * y2), wz2(quat.w() * z2);

			out = Matrix4_T<T>(
				1 - yy2 - zz2,	xy2 + wz2,		xz2 - wy2,		0,
				xy2 - wz2,		1 - xx2 - zz2,	yz2 + wx2,		0,
				xz2 + wy2,		yz2 - wx2,		1 - xx2 - yy2,	0,
				0,				0,				0,				1);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		Translation(Matrix4_T<T>& out, const T& x, const T& y, const T& z)
		{
			out = Matrix4_T<T>(
				1,	0,	0,	0,
				0,	1,	0,	0,
				0,	0,	1,	0,
				x,	y,	z,	1);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		Transpose(Matrix4_T<T>& out, const Matrix4_T<T>& rhs)
		{
			out = Matrix4_T<T>(
				rhs(0, 0), rhs(1, 0), rhs(2, 0), rhs(3, 0),
				rhs(0, 1), rhs(1, 1), rhs(2, 1), rhs(3, 1),
				rhs(0, 2), rhs(1, 2), rhs(2, 2), rhs(3, 2),
				rhs(0, 3), rhs(1, 3), rhs(2, 3), rhs(3, 3));
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		LHToRH(Matrix4_T<T>& out, const Matrix4_T<T>& rhs)
		{
			out = rhs;
			out(2, 0) = -out(2, 0);
			out(2, 1) = -out(2, 1);
			out(2, 2) = -out(2, 2);
			out(2, 3) = -out(2, 3);
			return out;
		}

		template <typename T>
		inline Matrix4_T<T>&
		Scaling(Matrix4_T<T>& out, const Vector_T<T, 3>& vPos)
		{
			return Scaling(out, vPos.x(), vPos.y(), vPos.z());
		}
		template <typename T>
		inline Matrix4_T<T>&
		Translation(Matrix4_T<T>& out, const Vector_T<T, 3>& vPos)
		{
			return Translation(out, vPos.x(), vPos.y(), vPos.z());
		}
		template <typename T>
		inline Matrix4_T<T>&
		OrthoRH(Matrix4_T<T>& out, const T& width, const T& height, const T& nearPlane, const T& farPlane)
		{
			OrthoLH(out, w, h, nearPlane, farPlane);
			return LHToRH(out, out);
		}
		template <typename T>
		inline Matrix4_T<T>&
		OrthoOffCenterRH(Matrix4_T<T>& out, const T& left, const T& right, const T& bottom, const T& top, 
			const T& nearPlane, const T& farPlane)
		{
			OrthoOffCenterLH(out, left, right, bottom, top, nearPlane, farPlane);
			return LHToRH(out, out);
		}
		template <typename T>
		inline Matrix4_T<T>&
		PerspectiveRH(Matrix4_T<T>& out, const T& width, const T& height,
			const T& nearPlane, const T& farPlane)
		{
			PerspectiveLH(out, w, h, nearPlane, farPlane);
			return LHToRH(out, out);
		}
		template <typename T>
		inline Matrix4_T<T>&
		PerspectiveFovRH(Matrix4_T<T>& out, const T& fov, const T& aspect,
			const T& nearPlane, const T& farPlane)
		{
			PerspectiveFovLH(out, fov, aspect, nearPlane, farPlane);
			return LHToRH(out, out);
		}
		template <typename T>
		inline Matrix4_T<T>&
		PerspectiveOffCenterRH(Matrix4_T<T>& out, const T& left, const T& right, const T& bottom, const T& top, 
			const T& nearPlane, const T& farPlane)
		{
			PerspectiveOffCenterLH(out, left, right, bottom, top, nearPlane, farPlane);
			return LHToRH(out, out);
		}

		template <typename T>
		inline Matrix4_T<T>&
		RHToLH(Matrix4_T<T>& out, const Matrix4_T<T>& rhs)
		{
			return LHToRH(out, rhs);
		}


		// 四元数
		///////////////////////////////////////////////////////////////////////////////
		template <typename T>
		inline Quaternion_T<T>&
		Conjugate(Quaternion_T<T>& out, const Quaternion_T<T>& rhs)
		{
			out = Quaternion_T<T>(-rhs.x(), -rhs.y(), -rhs.z(), rhs.w());
			return out;
		}

		template <typename T>
		inline Quaternion_T<T>&
		AxisToAxis(Quaternion_T<T>& out, const Vector_T<T, 3>& from, const Vector_T<T, 3>& to)
		{
			Vector_T<T, 3> a;
			Normalize(a, from);
			Vector_T<T, 3> b;
			Normalize(b, to);
			Vector_T<T, 3> half;
			Normalize(half, a + b);

			out = UnitAxisToUnitAxis(out, a, half);
			return out;
		}
		template <typename T>
		inline Quaternion_T<T>&
		UnitAxisToUnitAxis(Quaternion_T<T>& out, const Vector_T<T, 3>& from, const Vector_T<T, 3>& to)
		{
			Vector_T<T, 3> axis;
			Cross(axis, from, to);

			out = Quaternion_T<T>(axis, Dot(from, to));
			return out;
		}

		template <typename T>
		inline Quaternion_T<T>&
		BaryCentric(Quaternion_T<T>& out, const Quaternion_T<T>& q1, const Quaternion_T<T>& q2,
			const Quaternion_T<T>& q3, const T& f, const T& g)
		{
			const T temp(f + g);

			Quaternion_T<T> qT1;
			Slerp(qT1, q1, q2, temp);
			Quaternion_T<T> qT2;
			Slerp(qT2, q1, q3, temp);

			out = Slerp(out, qT1, qT2, g / temp);
			return out;
		}

		template <typename T>
		inline Quaternion_T<T>&
		Exp(Quaternion_T<T>& out, const Quaternion_T<T>& rhs)
		{
			const T theta(Length(rhs.v()));

			Vector_T<T, 3> vec;
			Normalize(vec, rhs.v());

			out = Quaternion_T<T>(vec * Sin(theta), Cos(theta));
			return out;
		}
		template <typename T>
		inline Quaternion_T<T>&
		Ln(Quaternion_T<T>& out, const Quaternion_T<T>& rhs)
		{
			const T theta_2(ACos(rhs.w()));

			Vector_T<T, 3> vec;
			Normalize(vec, rhs.v() * (theta_2 + theta_2));

			out = Quaternion_T<T>(vec, 0);
			return out;
		}

		template <typename T>
		inline Quaternion_T<T>&
		Inverse(Quaternion_T<T>& out, const Quaternion_T<T>& q)
		{
			const T inv(T(1) / Length(rhs));
			out = Quaternion(-rhs.x() * inv, -rhs.y() * inv, -rhs.z() * inv, rhs.w() * inv);
			return out;
		}

		template <typename T>
		inline Quaternion_T<T>&
		Multiply(Quaternion_T<T>& out, const Quaternion_T<T>& lhs, const Quaternion_T<T>& rhs)
		{
			out = Quaternion_T<T>(
				lhs.x() * rhs.w() - lhs.y() * rhs.z() + lhs.z() * rhs.y() + lhs.w() * rhs.x(),
				lhs.x() * rhs.z() + lhs.y() * rhs.w() - lhs.z() * rhs.x() + lhs.w() * rhs.y(),
				lhs.y() * rhs.x() - lhs.x() * rhs.y() + lhs.z() * rhs.w() + lhs.w() * rhs.z(),
				lhs.w() * rhs.w() - lhs.x() * rhs.x() - lhs.y() * rhs.y() - lhs.z() * rhs.z());
			return out;
		}

		template <typename T>
		inline Quaternion_T<T>&
		RotationYawPitchRoll(Quaternion_T<T>& out, const T& yaw, const T& pitch, const T& roll)
		{
			const T angX(pitch / 2), angY(yaw / 2), angZ(roll / 2);
			T sx, sy, sz;
			T cx, cy, cz;
			SinCos(angX, sx, cx);
			SinCos(angY, sy, cy);
			SinCos(angZ, sz, cz);

			out = Quaternion_T<T>(
				sx * cy * cz + cx * sy * sz,
				cx * sy * cz - sx * cy * sz,
				cx * cy * sz - sx * sy * cz,
				sx * sy * sz + cx * cy * cz);
			return out;
		}

		template <typename T>
		inline void
		ToAxisAngle(Vector_T<T, 3>& vec, T& ang, const Quaternion_T<T>& quat)
		{
			const T tw(ACos(quat.w()));
			const T scale(T(1) / Sin(tw));

			ang = tw + tw;
			vec.x() = quat.x() * scale, 
				vec.y() = quat.y() * scale;
			vec.z() = quat.z() * scale;
		}

		template <typename T>
		inline Quaternion_T<T>&
		ToQuaternion(Quaternion_T<T>& out, const Matrix4_T<T>& mat)
		{
			Quaternion_T<T> quat;
			T s;
			const T tr(mat(0, 0) + mat(1, 1) + mat(2, 2));

			// check the diagonal
			if (tr > 0)
			{
				s = Sqrt(tr + 1);
				quat.w() = s * 0.5f;
				s = 0.5f / s;
				quat.x() = (mat(1, 2) - mat(2, 1)) * s;
				quat.y() = (mat(2, 0) - mat(0, 2)) * s;
				quat.z() = (mat(0, 1) - mat(1, 0)) * s;
			}
			else
			{
				if ((mat(1, 1) > mat(0, 0)) && (mat(2, 2) <= mat(1, 1)))
				{
					s = Sqrt((mat(1, 1) - (mat(2, 2) + mat(0, 0))) + 1);

					quat.y() = s * 0.5f;

					if (!Eq(s, 0.0f))
					{
						s = 0.5f / s;
					}

					quat.w() = (mat(2, 0) - mat(0, 2)) * s;
					quat.z() = (mat(2, 1) + mat(1, 2)) * s;
					quat.x() = (mat(0, 1) + mat(1, 0)) * s;
				}
				else
				{
					if ((mat(1, 1) <= mat(0, 0) && mat(2, 2) > mat(0, 0)) || (mat(2, 2) > mat(1, 1)))
					{
						s = Sqrt((mat(2, 2) - (mat(0, 0) + mat(1, 1))) + 1);

						quat.z() = s * 0.5f;

						if (!Eq(s, 0.0f))
						{
							s = 0.5f / s;
						}

						quat.w() = (mat(0, 1) - mat(1, 0)) * s;
						quat.x() = (mat(0, 2) + mat(2, 0)) * s;
						quat.y() = (mat(1, 2) + mat(2, 1)) * s;
					}
					else
					{
						s = Sqrt((mat(0, 0) - (mat(1, 1) + mat(2, 2))) + 1);

						quat.x() = s * 0.5f;

						if (!Eq(s, 0.0f))
						{
							s = 0.5f / s;
						}

						quat.w() = (mat(1, 2) - mat(2, 1)) * s;
						quat.y() = (mat(1, 0) + mat(0, 1)) * s;
						quat.z() = (mat(2, 0) + mat(0, 2)) * s;
					}
				}
			}

			out = quat;
			return out;
		}

		template <typename T>
        inline Quaternion_T<T>&
		RotationAxis(Quaternion_T<T>& out, const Vector_T<T, 3>& v, const T& angle)
		{
			const T ang(angle * 0.5f);
			T sa, ca;
			SinCos(ang, sa, ca);

			Vector_T<T, 3> vec;
			Normalize(vec, v);

			out = Quaternion_T<T>(sa * vec, ca);
			return out;
		}

		template <typename T>
        inline Quaternion_T<T>&
		Slerp(Quaternion_T<T>& out, const Quaternion_T<T>& lhs, const Quaternion_T<T>& rhs, const T& slerp)
		{
			T scale0, scale1;
			Quaternion_T<T> q2;

			// DOT the quats to get the cosine of the angle between them
			const T cosom(Dot(lhs, rhs));

			// Two special cases:
			// Quats are exactly opposite, within DELTA?
			if (cosom > std::numeric_limits<T>::epsilon() - T(1))
			{
				// make sure they are different enough to avoid a divide by 0
				if (cosom < T(1) - std::numeric_limits<T>::epsilon())
				{
					// SLERP away
					const T omega(ACos(cosom));
					const T isinom(T(1) / Sin(omega));
					scale0 = Sin((1 - slerp) * omega) * isinom;
					scale1 = Sin(slerp * omega) * isinom;
				}
				else
				{
					// LERP is good enough at this distance
					scale0 = 1 - slerp;
					scale1 = slerp;
				}

				q2 = rhs * scale1;
			}
			else
			{
				// SLERP towards a perpendicular quat
				// Set slerp parameters
				scale0 = Sin((1 - slerp) * PIdiv2);
				scale1 = Sin(slerp * PIdiv2);

				q2.x() = -rhs.y() * scale1;
				q2.y() = +rhs.x() * scale1;
				q2.z() = -rhs.w() * scale1;
				q2.w() = +rhs.z() * scale1;
			}

			// Compute the result
			out = scale0 * lhs + q2;
			return out;
		}

		template <typename T>
        inline Quaternion_T<T>&
		RotationYawPitchRoll(Quaternion_T<T>& out, const Vector_T<T, 3>& ang)
		{
			return RotationYawPitchRoll(out, ang.x(), ang.y(), ang.z());
		}


		// 平面
		///////////////////////////////////////////////////////////////////////////////
		template <typename T>
		inline T
		Dot(const Plane_T<T>& lhs, const Vector_T<T, 4>& rhs)
		{
			return lhs.a() * rhs.x() + lhs.b() * rhs.y() + lhs.c() * rhs.z() + lhs.d() * rhs.w();
		}
		template <typename T>
		inline T
		DotCoord(const Plane_T<T>& lhs, const Vector_T<T, 3>& rhs)
		{
			return lhs.a() * rhs.x() + lhs.b() * rhs.y() + lhs.c() * rhs.z() + lhs.d();
		}
		template <typename T>
		inline T
		DotNormal(const Plane_T<T>& lhs, const Vector_T<T, 3>& rhs)
		{
			return lhs.a() * rhs.x() + lhs.b() * rhs.y() + lhs.c() * rhs.z();
		}

		template <typename T>
		inline Plane_T<T>&
		Normalize(Plane_T<T>& out, const Plane_T<T>& rhs)
		{
			const T inv(T(1) / Length(rhs));
			out = Plane(rhs.a() * inv, rhs.b() * inv, rhs.c() * inv, rhs.d() * inv);
			return out;
		}
		template <typename T>
		inline Plane_T<T>&
		FromPointNormal(Plane_T<T>& out, const Vector_T<T, 3>& point, const Vector_T<T, 3>& normal)
		{
			out = Plane(normal.x(), normal.y(), normal.z(), -Dot(point, normal));
			return out;
		}
		template <typename T>
		inline Plane_T<T>&
		FromPoints(Plane_T<T>& out, const Vector_T<T, 3>& v0, const Vector_T<T, 3>& v1, const Vector_T<T, 3>& v2)
		{
			Vector_T<T, 3> vec;
			Cross(vec, v1 - v0, v1 - v2);
			Normalize(vec, vec);
			return FromPointNormal(out, v0, vec);
		}
		template <typename T>
		inline Plane_T<T>&
		Transform(Plane_T<T>& out, const Plane_T<T>& p, const Matrix4_T<T>& mat)
		{
			out = Plane_T<T>(
				p.a() * mat(0, 0) + p.b() * mat(1, 0) + p.c() * mat(2, 0) + p.d() * mat(3, 0),
				p.a() * mat(0, 1) + p.b() * mat(1, 1) + p.c() * mat(2, 1) + p.d() * mat(3, 1),
				p.a() * mat(0, 2) + p.b() * mat(1, 2) + p.c() * mat(2, 2) + p.d() * mat(3, 2),
				p.a() * mat(0, 3) + p.b() * mat(1, 3) + p.c() * mat(2, 3) + p.d() * mat(3, 3));
			return out;
		}
		
		// 求直线和平面的交点，直线orig + t * dir，t的取值范围[0, 1]
		template <typename T>
		inline bool
		IntersectLine(Vector_T<T, 3>& out, const Plane_T<T>& p,
			const Vector_T<T, 3>& orig, const Vector_T<T, 3>& dir)
		{
			Vector_T<T, 3> vP(0, 0, 0);

			if (!Eq(p.a(), T(0)))
			{
				vP.x() = -p.d() / p.a();
			}
			else
			{
				if (!Eq(p.b(), T(0)))
				{
					vP.y() = -p.d() / p.b();
				}
				else
				{
					if (!Eq(p.c(), T(0)))
					{
						vP.z() = -p.d() / p.c();
					}
				}
			}

			const T deno(Dot(dir, p.Normal()));
			if (!Eq(deno, T(0)))
			{
				return false;
			}

			const T t(Dot(vP - orig, p.Normal()) / deno);

			out = orig + t * dir;

			return true;
		}


		// 颜色
		///////////////////////////////////////////////////////////////////////////////
		Color& Negative(Color& out, const Color& rhs);
		Color& Modulate(Color& out, const Color& lhs, const Color& rhs);


		// 范围
		///////////////////////////////////////////////////////////////////////////////
		bool VecInSphere(const Sphere& sphere, const Vector3& v);
		bool BoundProbe(const Sphere& sphere, const Vector3& pos, const Vector3& dir);
		bool VecInBox(const Box& box, const Vector3& v);
		bool BoundProbe(const Box& box, const Vector3& orig, const Vector3& dir);


		// 网格
		///////////////////////////////////////////////////////////////////////////////

		// 计算像素光照需要的TBN
		template <typename TangentIterator, typename BinormIterator,
			typename IndexIterator, typename PositionIterator, typename TexCoordIterator>
		void ComputeTangent(TangentIterator targentBegin, BinormIterator binormBegin,
								IndexIterator indicesBegin, IndexIterator indicesEnd,
								PositionIterator xyzsBegin, PositionIterator xyzsEnd,
								TexCoordIterator texsBegin)
		{
			for (int i = 0; i < xyzsEnd - xyzsBegin; ++ i)
			{
				*(targentBegin + i) = Vector3::Zero();
				*(binormBegin + i) = Vector3::Zero();
			}

			for (IndexIterator iter = indicesBegin; iter != indicesEnd; iter += 3)
			{
				const U16 previousIndex = *(iter + 0);
				const U16 currentIndex = *(iter + 1);
				const U16 nextIndex = *(iter + 2);

				const Vector3& currentXYZ(*(xyzsBegin + currentIndex));
				const Vector3& previousXYZ(*(xyzsBegin + previousIndex));
				const Vector3& nextXYZ(*(xyzsBegin + nextIndex));

				Vector3 v1v0 = nextXYZ - currentXYZ;
				Vector3 v2v0 = previousXYZ - currentXYZ;

				const Vector2& nextTex(*(texsBegin + nextIndex));
				const Vector2& currentTex(*(texsBegin + currentIndex));
				const Vector2& previousTex(*(texsBegin + previousIndex));

				float s1 = nextTex.x() - currentTex.x();
				float t1 = nextTex.y() - currentTex.y();

				float s2 = previousTex.x() - currentTex.x();
				float t2 = previousTex.y() - currentTex.y();

				float denominator = s1 * t2 - s2 * t1;
				Vector3 T, B;
				if (denominator < 0.0001f)
				{
					T = Vector3(1, 0, 0);
					B = Vector3(0, 1, 0);
				}
				else
				{
					T = (t2 * v1v0 - t1 * v2v0) / denominator;
					B = (s1 * v2v0 - s2 * v1v0) / denominator;
				}
				*(targentBegin + previousIndex) += T;
				*(binormBegin + previousIndex) += B;

				*(targentBegin + currentIndex) += T;
				*(binormBegin + currentIndex) += B;

				*(targentBegin + nextIndex) += T;
				*(binormBegin + nextIndex) += B;
			}

			for (int i = 0; i < xyzsEnd - xyzsBegin; ++ i)
			{
				MathLib::Normalize(*(targentBegin + i), *(targentBegin + i));
				MathLib::Normalize(*(binormBegin + i), *(binormBegin + i));
			}
		}

		template <typename NormalIterator, typename IndexIterator, typename PositionIterator>
		void ComputeNormal(NormalIterator normalBegin,
								IndexIterator indicesBegin, IndexIterator indicesEnd,
								PositionIterator xyzsBegin, PositionIterator xyzsEnd)
		{
			for (int i = 0; i < xyzsEnd - xyzsBegin; ++ i)
			{
				*(normalBegin + i) = Vector3::Zero();
			}

			for (IndexIterator iter = indicesBegin; iter != indicesEnd; iter += 3)
			{
				const U16 v0Index = *(iter + 0);
				const U16 v1Index = *(iter + 1);
				const U16 v2Index = *(iter + 2);

				const Vector3& v0(*(xyzsBegin + v0Index));
				const Vector3& v1(*(xyzsBegin + v1Index));
				const Vector3& v2(*(xyzsBegin + v2Index));

				Vector3 vec;
				MathLib::Cross(vec, v1 - v0, v2 - v0);	

				*(normalBegin + v0Index) += vec;
				*(normalBegin + v1Index) += vec;
				*(normalBegin + v2Index) += vec;
			}

			for (int i = 0; i < xyzsEnd - xyzsBegin; ++ i)
			{
				MathLib::Normalize(*(normalBegin + i), *(normalBegin + i));
			}
		}		
	};


	class Random
	{
	public:
		static Random& Instance();

		// 任意随机数
		int Next() const;

		// 小于x的随机数
		template <typename T>
		T Next(const T& x)
			{ return MathLib::Mod<T>(static_cast<T>(Random::Instance().Next()), x); }

		// 在min和max之间的随机数
		template <typename T>
		T Next(const T& minv, const T& maxv)
			{ return minv + Random::Instance().Next(maxv - minv); }

	private:
		Random();
	};
}

#include <KlayGE/Vector.hpp>
#include <KlayGE/Rect.hpp>
#include <KlayGE/Size.hpp>
#include <KlayGE/Matrix.hpp>
#include <KlayGE/Quaternion.hpp>
#include <KlayGE/Plane.hpp>
#include <KlayGE/Color.hpp>
#include <KlayGE/Bound.hpp>
#include <KlayGE/Sphere.hpp>
#include <KlayGE/Box.hpp>

#endif		// _MATH_HPP
