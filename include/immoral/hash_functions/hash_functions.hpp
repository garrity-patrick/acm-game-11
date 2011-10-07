#ifndef _IMMORAL_HASH_FUNCTIONS_HPP_
#define _IMMORAL_HASH_FUNCTIONS_HPP_

/*!
 * \file hash_functions.hpp
 * \author Michael Taufen
 * 
 * Contains utility function to generate hash codes that help 
 * identify and rapidly compare strings.
 */

#include "immoral/types.hpp"

namespace immoral
{

	/*!
	 * Generate a 64-bit unsigned integer hash code from a string.
	 * This function is to be used at runtime. To convert strings to hashes
	 * during compilaion, see tools/macript.
	 * \param input_string The string to hash.
	 * \return An unsigned 64-bit integer (u64) containing a unique number identifying the string provided in arg1.
	 */
	u64 GetU64HashCode (string input_string)
	{
		u64 u64_hash_code = 5381;
		size_t i = 0;
		size_t string_size = input_string.size();
		int character;
	
		while ((i < string_size) && (character = input_string[i++]))
		{
			u64_hash_code = ((u64_hash_code << 5) + u64_hash_code) + character; 
			/* hash code * 32 + character */
		}
	
		return u64_hash_code;
	}

}