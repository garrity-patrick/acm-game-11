#ifndef _IMMORAL_FLOAT_HPP_
#define _IMMORAL_FLOAT_HPP_

/*!
 * \file float.hpp
 * \author Patrick Garrity
 * 
 * Contains utility functions to handle floating-point calculations. These are 
 * meant to help deal with floating-point error and related problems.
 */

namespace immoral
{
	/*!
	 * The epsilon value to use for floating-point comparisions.
	 */
	const float FLOAT_EPSILON = 0.00001f;
	
	/*!
	 * Determine the equality of two floating-point numbers.
	 * This calculation uses the FLOAT_EPSILON value.
	 * \param x The first number.
	 * \param y The second number.
	 * \return Whether or not the two numbers are equal.
	 */
	inline bool feq(float x, float y)
	{
		return ((y >= (x - FLOAT_EPSILON))
			&& (y <= (x + FLOAT_EPSILON)));
	}
	
	/*!
	 * Determine the inequality of two floating-point numbers.
	 * This calculation uses the FLOAT_EPSILON value.
	 * \param x The first number.
	 * \param y The second number.
	 * \return Whether or not the two numbers are not equal.
	 */
	inline bool fneq(float x, float y)
	{
		return ((y < (x - FLOAT_EPSILON))
			|| (y > (x + FLOAT_EPSILON)));
	}
	
	/*!
	 * Determine whether one floating-point number is less than another.
	 * This calculation uses the FLOAT_EPSILON value.
	 * \param x The first number.
	 * \param y The second number.
	 * \return The boolean result of (x < y).
	 */
	inline bool flt(float x, float y)
	{
		return (x < (y - FLOAT_EPSILON));
	}
	
	/*!
	 * Determine whether one floating-point number is less than or equal to another.
	 * This calculation uses the FLOAT_EPSILON value.
	 * \param x The first number.
	 * \param y The second number.
	 * \return The boolean result of (x <= y).
	 */
	inline bool flte(float x, float y)
	{
		return (x <= (y - FLOAT_EPSILON));
	}
	
	/*!
	 * Determine whether one floating-point number is greater than another.
	 * This calculation uses the FLOAT_EPSILON value.
	 * \param x The first number.
	 * \param y The second number.
	 * \return The boolean result of (x > y).
	 */
	inline bool fgt(float x, float y)
	{
		return (x > (y + FLOAT_EPSILON));
	}
	
	/*!
	 * Determine whether one floating-point number is greater than or equal to another.
	 * This calculation uses the FLOAT_EPSILON value.
	 * \param x The first number.
	 * \param y The second number.
	 * \return The boolean result of (x >= y).
	 */
	inline bool fgte(float x, float y)
	{
		return (x >= (y + FLOAT_EPSILON));
	}
	
	/*!
	 * Clamp a floating-point value to a range.
	 * \param x The number to clamp.
	 * \param low The lower bound of the range.
	 * \param high The upper bound of the range.
	 * \return The clamped value.
	 */
	inline float clamp(float x, float low, float high)
	{
		if (x > high) return high;
		if (x < low)  return low;
		return x;
	}
}

#endif
