#ifndef _IMMORAL_FLOAT_HPP_
#define _IMMORAL_FLOAT_HPP_

/*!
 * \file f32.hpp
 * \author Patrick Garrity
 * 
 * Contains utility functions to handle floating-point calculations. These are 
 * meant to help deal with floating-point error and related problems.
 */

#include "immoral/types.hpp"

namespace immoral
{
	/*!
	 * The epsilon value to use for floating-point comparisions.
	 */
	const f32 FLOAT_EPSILON = 0.00001f;
	
	/*!
	 * Determine the equality of two floating-point numbers.
	 * This calculation uses the FLOAT_EPSILON value.
	 * \param x The first number.
	 * \param y The second number.
	 * \return Whether or not the two numbers are equal.
	 */
	inline bool feq(f32 x, f32 y)
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
	inline bool fneq(f32 x, f32 y)
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
	inline bool flt(f32 x, f32 y)
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
	inline bool flte(f32 x, f32 y)
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
	inline bool fgt(f32 x, f32 y)
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
	inline bool fgte(f32 x, f32 y)
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
	inline f32 clamp(f32 x, f32 low, f32 high)
	{
		if (x > high) return high;
		if (x < low)  return low;
		return x;
	}
}

#endif
