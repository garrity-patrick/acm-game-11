#ifndef _IMMORAL_VECTOR2_HPP_
#define _IMMORAL_VECTOR2_HPP_

/*!
 * \file vector2.hpp
 * \author Patrick Garrity
 * 
 * Contains the definition of a 2-dimensional vector.
 */

namespace immoral
{
	/*!
	 * \class vector2
	 * 
	 * A 2-dimensional vector. Uses single-precision floating-point numbers.
	 */
	class vector2
	{
	private:
		/*!
		 * The x- and y-components of the vector.
		 * These are stored in an array to guarantee they are (1) contiguous
		 * and (2) easy to pass to OpenGL functions.
		 */
		float m_xy[2];
	
	public:
		/*!
		 * Constructor.
		 */
		vector2(void);
		
		/*!
		 * Copy constructor.
		 * \param other The vector2 to copy.
		 */
		vector2(const vector2 & other);
		
		/*!
		 * Constructor.
		 * \param x The x-component of the vector.
		 * \param y The y-component of the vector.
		 */
		vector2(float x, float y);
		
		/*!
		 * Destructor.
		 */
		~vector2(void);
		
		/*!
		 * Get the x-component of this vector2.
		 * \return The x-component (rvalue).
		 */
		const float & x(void) const { return m_xy[0]; }
		
		/*!
		 * Get the x-component of this vector2.
		 * \return The x-component (lvalue).
		 */
		float & x(void) { return m_xy[0]; }
		
		/*!
		 * Get the y-component of this vector2.
		 * \return The y-component (rvalue).
		 */
		const float & y(void) const { return m_xy[1]; }
		
		/*!
		 * Get the y-component of this vector2.
		 * \return The y-component (lvalue).
		 */
		float & y(void) { return m_xy[1]; }
		
		/*!
		 * Set the components of this vector2.
		 * \param x The new x-component.
		 * \param y The new y-component.
		 */
		void set(float x, float y) { m_xy[0] = x; m_xy[1] = y; }
		
		/*!
		 * Get the components of this vector.
		 * \return The components array.
		 */
		const float * components(void) const { return m_xy; }
		
		/*!
		 * Overloaded assignment operator.
		 * \param other The vector2 to copy.
		 * \return A reference to this vector2.
		 */
		vector2 & operator=(const vector2 & other);
		
		/*!
		 * Overloaded equality operator.
		 * Compares two vector2 objects for equality.
		 * (x1, y1) == (x2, y2) <==> x1 == x2 && y1 == y2
		 * \param v The vector2 to compare against.
		 * \return Whether or not the two vectors are equal.
		 */
		bool operator==(const vector2 & v) const;
		
		/*!
		 * Overloaded inequality operator.
		 * Compares two vector2 objects for inequality.
		 * (x1, y1) != (x2, y2) <==> x1 != x2 || y1 != y2
		 * \param v The vector2 to compare against.
		 * \return Whether or not the two vectors are equal.
		 */
		bool operator!=(const vector2 & v) const;
		
		/*!
		 * Overloaded plus operator.
		 * Adds two vectors.
		 * (x1, y1) + (x2, y2) = (x1 + x2, y1 + y2)
		 * \param v The vector2 to add.
		 * \return The sum of the two vectors.
		 */
		vector2 operator+(const vector2 & v) const;
		
		/*!
		 * Overloaded minus operator.
		 * Calculates the difference between vectors.
		 * (x1, y1) - (x2, y2) = (x1 - x2, y1 - y2)
		 * \param v The vector2 to subtract.
		 * \return The difference between the vectors.
		 */
		vector2 operator-(const vector2 & v) const;
		
		/*!
		 * Overloaded times operator.
		 * Scales a vector2.
		 * (x1, y1) * s = (x1*s, y1*s)
		 * \param scalar The value to scale by.
		 * \return The scaled vector.
		 */
		vector2 operator*(float scalar) const;
		
		/*!
		 * Overloaded times operator.
		 * Calculates the dot product of two vector2.
		 * dot(v1, v2) = (x1 * x2) + (y1 * y2)
		 * \param v The vector to dot with.
		 * \return The dot product of the two vectors.
		 */
		float operator*(const vector2 & v) const;
		
		/*!
		 * Overloaded plus-equals operator.
		 * \param v The vector2 to add.
		 * \return A reference to this vector2.
		 */
		vector2 & operator+=(const vector2 & v);
		
		/*!
		 * Overloaded minus-equals operator.
		 * \param v The vector2 to subtract.
		 * \return A reference to this vector2.
		 */
		vector2 & operator-=(const vector2 & v);
		
		/*!
		 * Overloaded times-equals operator.
		 * \param scalar The value to scale by.
		 * \return A reference to this vector2.
		 */
		vector2 & operator*(float scalar);
		
		/*!
		 * Add a vector2.
		 * \param v The vector2 to add.
		 */
		void add(const vector2 & v);
		
		/*!
		 * Subtract a vector2.
		 * \param v The vector2 to subtract.
		 */
		void subtract(const vector2 & v);
		
		/*!
		 * Scale this vector2.
		 * \param scalar The value to scale by.
		 */
		void scale(float scalar);
		
		/*!
		 * Calculate the dot product of two vectors.
		 * \param v The vector2 to dot with.
		 * \return The dot product.
		 */
		float dot(const vector2 & v);
		
		/*!
		 * Calculate the magnitude of this vector2.
		 * \return The magnitude of this vector.
		 */
		float mag(void) const;
		
		/*!
		 * Calculate the squared magnitude of this vector2.
		 * \return The squared magnitude of this vector.
		 */
		float mag2(void) const;
		
		/*!
		 * Calculate the distance between two vector2.
		 * \param v The vector2 to find the distance to.
		 * \return The distance between the vectors.
		 */
		float distance(const vector2 & v) const;
		
		/*!
		 * Calculate the squared distance between two vector2.
		 * \param v The vector2 to find the distance to.
		 * \return The distance between the vectors squared.
		 */
		float distance2(const vector2 & v) const;
		
		/*!
		 * Normalize this vector.
		 * norm(v1) = v1*(1.0/mag(v1))
		 */
		void normalize(void);
		
		/*!
		 * Calculate the normal of this vector.
		 * \return The normal form of this vector.
		 */
		vector2 normal(void) const;
		
		/*!
		 * Make this vector2 a unit vector in the x-direction.
		 */
		void unit_x(void) { m_xy[0] = 1.0f; m_xy[1] = 0.0f; }
		
		/*!
		 * Make this vector2 a unit vector in the y-direction.
		 */
		void unit_y(void) { m_xy[0] = 0.0f; m_xy[1] = 1.0f; }
		
		/*!
		 * Make this vector2 the zero vector.
		 */
		void zero(void)   { m_xy[0] = 0.0f; m_xy[1] = 0.0f; }
	};
}

#endif
