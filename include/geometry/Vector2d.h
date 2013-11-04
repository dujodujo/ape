#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#include <iosfwd>
#include <limits>

class Vector2d {
	double x;
	double y;

	Vector2d():x(0.0),y(0.0) {}
	Vector2d(double a, double b):x(a),y(b) {}

	//sets x and y to zero
	void zero() {x=0.0; y=0.0;}

	//returns true if both x and y are zero
	bool is_zero() const {return (x*x + y*y) < min_double;}

	//returns the length of the vector
	inline double length() const;

	//returns the squared length of the vector (thereby avoiding the sqrt)
	inline double length_sq() const;

	inline void normalize();

	inline double dot(const Vector2d& v2) const;

	//returns positive if v2 is clockwise of this vector,
	//negative if anticlockwise (assuming the Y axis is pointing down,
	//X axis to right like a Window app)
	inline int sign(const Vector2D& v2) const;

	//returns the vector that is perpendicular to this one.
	inline Vector2D perp() const;

	//adjusts x and y so that the length of the vector does not exceed max
	inline void truncate(double max);

	//returns the distance between this vector and th one passed as a parameter
	inline double distance(const Vector2d &v2) const;

	//squared version of above.
	inline double distance_sq(const Vector2d &v2) const;

	inline void reflect(const Vector2d& norm);

	//returns the vector that is the reverse of this vector
	inline Vector2d get_reverse() const;

	//we need some overloaded operators
	const Vector2d& operator+=(const Vector2d &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	const Vector2d& operator-=(const Vector2d &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	const Vector2D& operator*=(const double& rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	const Vector2d& operator/=(const double& rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	bool operator==(const Vector2d& rhs) const {
		return (is_equal(x, rhs.x) && is_equal(y,rhs.y) );
	}

	bool operator!=(const Vector2d& rhs) const {
		return (x != rhs.x) || (y != rhs.y);
	}
};

//-----------------------------------------------------------------------some more operator overloads
inline Vector2d operator*(const Vector2d &lhs, double rhs);
inline Vector2d operator*(double lhs, const Vector2d &rhs);
inline Vector2d operator-(const Vector2d &lhs, const Vector2d &rhs);
inline Vector2d operator+(const Vector2d &lhs, const Vector2d &rhs);
inline Vector2d operator/(const Vector2d &lhs, double val);
std::ostream& operator<<(std::ostream& os, const Vector2d& rhs);
std::ifstream& operator>>(std::ifstream& is, Vector2d& lhs);


//------------------------------------------------------------------------member functions

//------------------------- Length ---------------------------------------
//
//  returns the length of a 2D vector
//------------------------------------------------------------------------
inline double Vector2d::length() const {
	return sqrt(x*x + y*y);
}


//------------------------- LengthSq -------------------------------------
//
//  returns the squared length of a 2D vector
//------------------------------------------------------------------------
inline double Vector2d::length_sq() const {
	return (x*x + y*y);
}


//------------------------- Vec2DDot -------------------------------------
//
//  calculates the dot product
//------------------------------------------------------------------------
inline double Vector2d::dot(const Vector2d &v2) const {
	return x*v2.x + y*v2.y;
}

//------------------------ Sign ------------------------------------------
//
//  returns positive if v2 is clockwise of this vector,
//  minus if anticlockwise (Y axis pointing down, X axis to right)
//------------------------------------------------------------------------
enum {clockwise = 1, anticlockwise = -1};

inline int Vector2d::sign(const Vector2d& v2) const {
	if (y*v2.x > x*v2.y) { 
		return anticlockwise;
	} else  {
		return clockwise;
	}
}

//------------------------------ Perp ------------------------------------
//
//  Returns a vector perpendicular to this vector
//------------------------------------------------------------------------
inline Vector2d Vector2d::perp() const {
	return Vector2d(-y, x);
}

//------------------------------ Distance --------------------------------
//
//  calculates the euclidean distance between two vectors
//------------------------------------------------------------------------
inline double Vector2d::distance(const Vector2d &v2)const {
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;
	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

//------------------------------ DistanceSq ------------------------------
//
//  calculates the euclidean distance squared between two vectors 
//------------------------------------------------------------------------
inline double Vector2d::distance_sq(const Vector2d &v2) const {
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;
	return ySeparation*ySeparation + xSeparation*xSeparation;
}

//----------------------------- Truncate ---------------------------------
//
//  truncates a vector so that its length does not exceed max
//------------------------------------------------------------------------
inline void Vector2d::truncate(double max) {
	if (this->length() > max) {
		this->normalize();
		*this *= max;
	} 
}

//--------------------------- Reflect ------------------------------------
//
//  given a normalized vector this method reflects the vector it
//  is operating upon. (like the path of a ball bouncing off a wall)
//------------------------------------------------------------------------
inline void Vector2d::reflect(const Vector2d& norm) {
	*this += 2.0 * this->dot(norm) * norm.get_reverse();
}

//----------------------- GetReverse ----------------------------------------
//
//  returns the vector that is the reverse of this vector
//------------------------------------------------------------------------
inline Vector2d Vector2d::get_reverse()const {
	return Vector2d(-this->x, -this->y);
}


//------------------------- Normalize ------------------------------------
//
//  normalizes a 2D Vector
//------------------------------------------------------------------------
inline void Vector2d::normalize() { 
	double vector_length = this->length();

	if(vector_length > std::numeric_limits<double>::epsilon()) {
		this->x /= vector_length;
		this->y /= vector_length;
	}
}


//------------------------------------------------------------------------non member functions

inline Vector2d Vec2d_normalize(const Vector2d &v) {
	Vector2d vec = v;
	double vector_length = vec.length();

	if (vector_length > std::numeric_limits<double>::epsilon()) {
		vec.x /= vector_length;
		vec.y /= vector_length;
	}
	return vec;
}


inline double Vec2d_distance(const Vector2d &v1, const Vector2d &v2) {
	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;
	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

inline double Vec2d_distance_sq(const Vector2d &v1, const Vector2d &v2) {
	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;
	return ySeparation*ySeparation + xSeparation*xSeparation;
}

inline double Vec2d_length(const Vector2d& v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

inline double Vec2d_length_sq(const Vector2d& v) {
	return (v.x*v.x + v.y*v.y);
}

inline Vector2d POINTS_to_vector(const POINTS& p) {
	return Vector2d(p.x, p.y);
}

inline Vector2d POINT_to_vector(const POINT& p) {
	return Vector2d((double)p.x, (double)p.y);
}

inline POINTS cector_to_POINTS(const Vector2d& v) {
	POINTS p;
	p.x = (short)v.x;
	p.y = (short)v.y;

	return p;
}

inline POINT vector_to_POINT(const Vector2d& v) {
	POINT p;
	p.x = (long)v.x;
	p.y = (long)v.y;

	return p;
}



//------------------------------------------------------------------------operator overloads
inline Vector2d operator*(const Vector2d &lhs, double rhs) {
	Vector2d result(lhs);
	result *= rhs;
	return result;
}

inline Vector2d operator*(double lhs, const Vector2d &rhs) {
	Vector2d result(rhs);
	result *= lhs;
	return result;
}

//overload the - operator
inline Vector2d operator-(const Vector2d &lhs, const Vector2d &rhs) {
	Vector2d result(lhs);
	result.x -= rhs.x;
	result.y -= rhs.y;
	return result;
}

//overload the + operator
inline Vector2d operator+(const Vector2d &lhs, const Vector2d &rhs) {
	Vector2d result(lhs);
	result.x += rhs.x;
	result.y += rhs.y;
	return result;
}

//overload the / operator
inline Vector2d operator/(const Vector2d &lhs, double val) {
	Vector2d result(lhs);
	result.x /= val;
	result.y /= val;
	return result;
}

#endif