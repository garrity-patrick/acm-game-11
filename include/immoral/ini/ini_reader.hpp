#ifndef _IMMORAL_INI_READER_HPP_
#define _IMMORAL_INI_READER_HPP_

/*!
 * \file ini_reader.hpp
 * \author Michael Taufen
 * 
 * Contains functions for parsing .ini files, as well as new types and structs to hold that data.
 * 
 */

 /*!
  * \par Required File Format for our .ini Config Files
  * A properly formatted file has:
  * - No whitespace around the equals sign
  * - All strings enclosed in double or single quotation marks
  * - Boolean values must be either true or false, exactly, all lowercase, and not enclosed in quotes
  * - Doubles should start with %d, as so: %d12.05
  * - Integers are just plain numbers, like: 150
  * - No whitespace at the ends of lines
  * - Comments begin with a semicolon, nothing on that line will be evaluated
  *
  * Failing to consider these reccomendations will result in errors.
  * \example test.ini
  * Here is an example of a properly formatted .ini file:
  */

//TODO: boolean values must be either true or false, all lowercase, do not add whitespace to the ends of the lines

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "immoral/types.hpp"

namespace immoral
{
	namespace config
	{
		/*!
		 * This struct holds a value read in from the .ini file.
		 * It is passed to iniMap as part of a key/value pair where the key is a string.
		 * This struct handles strings with the C++ std::string class.
		*/
		struct valStruct {
				int Int;
				double Double;
				bool Bool;
				std::string String;
			};
		/*!
		 * This type of map holds key/value pairs read in from the .ini file.
		 * It is constructed from key/value pairs where the first element is a std::string and the second an immoral::config::valStruct
		 */
		typedef std::map<std::string, valStruct> iniMap;

		/*!
		 * This struct holds a value read in from the .ini file.
		 * It is passed to hashedIniMap as part of a key/value pair where the key is a u64 hash code of the key in the .ini file.
		 * This struct handles strings as u64 hash codes.
		*/
		struct hashedValStruct {
				int Int;
				double Double;
				bool Bool;
				u64 String_hash;
			};	
		/*!
		 * This type of map holds key/value pairs read in from the .ini file.
		 * It is constructed from key/value pairs where the first element is a u64 hash code and the second an immoral::config::hashedValStruct
		 */
		typedef std::map<u64, hashedValStruct> hashedIniMap;

		/*!
		 * Reads a .ini file and returns a map containing all of the key-value pairs in that file.
		 * The pairs are not hashed, and can be accessed with a string, the name of the key.
		 * \param file_name The name of the file to open.
		 * \return A map of type immoral::config::iniMap containing all of the key-value pairs in that file in the form <std::String, immoral::config::valStruct>
		 */
		iniMap Parse (const char * file_name)
		{
			std::ifstream ini_file;
			std::string buffer;
			iniMap config;
			std::string key_name;
			std::string matched_value_string;
			ini_file.open(file_name);
			if (!ini_file.is_open())
			{
				std::cerr << "Unable to open ini file." << std::endl;
				return config; //note, config will be empty??? on return if the ini can't be opened
			}
			while (!ini_file.eof())
			{
				
				getline(ini_file, buffer);
				valStruct matched_value_struct;
				
				for (size_t i = 0; i < buffer.length(); ++i)
				{
					//comment test
					if (buffer[i] == ';')
						break;
					//equals sign test
					if (buffer[i] == '=')
					{
						 
						key_name = buffer.substr(0, i);
						//double test: '%d' before number (without quotes)
						if ((buffer[i + 1] == '%') && (buffer[i + 2] == 'd'))
						{
							matched_value_string = buffer.substr((i + 3), (buffer.length() - (i + 4)));
							std::istringstream matched_value_stream (matched_value_string);
							matched_value_stream >> matched_value_struct.Double;
							config.insert(std::pair<std::string, valStruct>(key_name, matched_value_struct));
							break;
						}
						//string test: enclosed in double or single parens					
						if ((buffer[i + 1] == '\'') || (buffer[i + 1] == '\"'))
						{
							matched_value_struct.String = buffer.substr((i + 2), (buffer.length() - (i + 4)));
							config.insert(std::pair<std::string, valStruct>(key_name, matched_value_struct));
							break;
						}
						//bool test: true or false, no parens
						matched_value_string = (buffer.substr((i + 1), (buffer.length() - (i + 2))));
						
						if (matched_value_string == "true")
						{
							matched_value_struct.Bool = true;
							config.insert(std::pair<std::string, valStruct>(key_name, matched_value_struct));
							break;
						}	
						else if (matched_value_string == "false")
						{
							matched_value_struct.Bool = false;
							config.insert(std::pair<std::string, valStruct>(key_name, matched_value_struct));
							break;
						}
						//int is any number with no prefix, basically whatever is left at this point
						else
						{
							std::istringstream matched_value_stream (matched_value_string);
							matched_value_stream >> matched_value_struct.Int;
							config.insert(std::pair<std::string, valStruct>(key_name, matched_value_struct));
						}
					}
				}
			}
			ini_file.close();
			return config;
		}

		/*!
		 * Reads a .ini file and returns a map containing all of the key-value pairs in that file, after hashing all of the strings.
		 * The pairs are hashed, and must be accessed with a the proper hash code resulting from the name of the key.
		 * This can be obtained like so: immoral::GetU64HashCode("name_of_key");
		 * \param file_name The name of the file to open.
		 * \return A map of type immoral::config::iniMap containing all of the key-value pairs in that file in the form <u64, immoral::config::hashedValStruct>
		 */
		hashedIniMap HashParse (const char * file_name) 
		{
			std::ifstream ini_file;
			std::string buffer;
			hashedIniMap config;
			std::string key_name;
			std::string matched_value_string;
			ini_file.open(file_name);
			if (!ini_file.is_open())
			{
				std::cerr << "Unable to open ini file." << std::endl;
				return config; //note, config will be empty??? on return if the ini can't be opened
			}
			while (!ini_file.eof())
			{
				//ini_file.getline();
				getline(ini_file, buffer);
				hashedValStruct matched_value_struct;
				//std::cout << buffer << std::endl;
				for (size_t i = 0; i < buffer.length(); ++i)
				{
					//comment test
					if (buffer[i] == ';')
						break;
					//equals sign test
					if (buffer[i] == '=')
					{
						
						key_name = buffer.substr(0, i); //rewrite this as making a new char array the length of the key name, and copying into it
						//double test: '%d' before number (without quotes)
						if ((buffer[i + 1] == '%') && (buffer[i + 2] == 'd'))
						{
							matched_value_string = buffer.substr((i + 3), (buffer.length() - (i + 4)));
							std::istringstream matched_value_stream (matched_value_string);
							matched_value_stream >> matched_value_struct.Double;
							config.insert(std::pair<u64, hashedValStruct>(GetU64HashCode(key_name), matched_value_struct));
							break;
						}
						//string test: enclosed in double or single parens					
						if ((buffer[i + 1] == '\'') || (buffer[i + 1] == '\"'))
						{
							matched_value_struct.String_hash = GetU64HashCode(buffer.substr((i + 2), (buffer.length() - (i + 4))));
							config.insert(std::pair<u64, hashedValStruct>(GetU64HashCode(key_name), matched_value_struct));
							break;
						}
						//bool test: true or false, no parens
						matched_value_string = (buffer.substr((i + 1), (buffer.length() - (i + 2))));
						
						if (matched_value_string == "true")
						{
							matched_value_struct.Bool = true;
							config.insert(std::pair<u64, hashedValStruct>(GetU64HashCode(key_name), matched_value_struct));
							break;
						}	
						else if (matched_value_string == "false")
						{
							matched_value_struct.Bool = false;
							config.insert(std::pair<u64, hashedValStruct>(GetU64HashCode(key_name), matched_value_struct));
							break;
						}
						//int is any number with no prefix, basically whatever is left at this point
						else
						{
							std::istringstream matched_value_stream (matched_value_string);
							matched_value_stream >> matched_value_struct.Int;
							config.insert(std::pair<u64, hashedValStruct>(GetU64HashCode(key_name), matched_value_struct));
						}
					}
				}
			}
			ini_file.close();
			return config;
		}

	}

}

#endif //_IMMORAL_INI_READER_HPP_