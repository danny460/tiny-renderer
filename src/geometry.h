#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class t> struct Vec2 {
	t x, y;
	Vec2<t>() : x(t()), y(t()) {}
    Vec2<t>(t _x, t _y) : x(_x), y(_y) {}
    Vec2<t>(const Vec2<t> &v) : x(t()), y(t()) { *this = v; }
	inline t& 	   operator [](const int i){ if(i <= 0) return x; else return y;}
	inline Vec2<t> operator +(const Vec2<t> &V) const { return Vec2<t>(x+V.x, y+V.y); }
	inline Vec2<t> operator -(const Vec2<t> &V) const { return Vec2<t>(x-V.x, y-V.y); }
	inline Vec2<t> operator *(float f)          const { return Vec2<t>(x*f, y*f); }
	inline float dot(Vec2<t> &v){ return x * v.x + y * v.y; }
	inline float dot(Vec2<t> &v0, Vec2<t> &v1){ return v0.x * v1.x + v0.y * v1.y;}

	template <class > friend std::ostream& operator<<(std::ostream& s, Vec2<t>& v);
};

template <class t> struct Vec3 {
	t x,y,z;
	Vec3() : x(0), y(0), z(0) {}
	Vec3(t _x, t _y, t _z) : x(_x),y(_y),z(_z) {}
	inline t& 	   operator [](const int i){ if(i <= 0) return x; else if(i == 1) return y; else return z;}
	inline Vec3<t> operator ^(const Vec3<t> &v) const { return Vec3<t>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); } //cross product
	inline Vec3<t> operator +(const Vec3<t> &v) const { return Vec3<t>(x+v.x, y+v.y, z+v.z); }
	inline Vec3<t> operator -(const Vec3<t> &v) const { return Vec3<t>(x-v.x, y-v.y, z-v.z); }
	inline Vec3<t> operator *(float f)          const { return Vec3<t>(x*f, y*f, z*f); }
	inline t	   operator *(const Vec3<t> &v) const { return x*v.x + y*v.y + z*v.z; }
	inline float   dot(const Vec3<t> &v) 		const { return x*v.x + y*v.y + z*v.z; }
	inline Vec3<t> cross(const Vec3<t> &v) 		const { return Vec3<t>( y*v.z - z*v.y, z*v.x-x*v.z, x*v.y-y*v.x ); }

	float norm () const { return std::sqrt(x*x+y*y+z*z); }
	Vec3<t> & normalize(t l=1) { *this = (*this)*(l/norm()); return *this; }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vec3<t>& v);
};

typedef Vec2<float> Vec2f;
typedef Vec2<int>   Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;

template <class t> std::ostream& operator<<(std::ostream& s, Vec2<t>& v) {
	s << "(" << v.x << ", " << v.y << ")\n";
	return s;
}

template <class t> std::ostream& operator<<(std::ostream& s, Vec3<t>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}

const int DEFAULT_ALLOC = 4;

class Matrix {
	//
	std::vector<std::vector<float>> m;
	int rows, cols;

	public:
		Matrix(int r = DEFUALT_ALLOC, int c = DEFAULT_ALLOC);
		inline int nrows();
		inline int ncols();

		static Matrix indentity(int dimension);
		std::vector<float>& operator[](cosnt int i);
		Matrix operator*(const Matrix& a);
		Matrix transpose();
		Matrix inverse();

		friend std::ostream& operator<<(std::ostream& s, Matrix& m);
}

#endif //__GEOMETRY_H__
