#pragma once
#include "helpers.hpp"
#include <type_traits>
#include <exception>
#include <string>
#include <cerrno>
#include <cstring>
#include <clocale>
#include <cstdlib>
#include <iostream>
#include <cinttypes>


enum class DefaultErrorType {
	Unknown,
	NotImplementedYet
};

namespace std
{
	template<typename T>
	string to_string(const T& value);
	
	template<typename T=DefaultErrorType> 
	string to_string(const T& error){
		switch (error){
			return_case(DefaultErrorType::Unknown,"Unknown");
			return_case(DefaultErrorType::NotImplementedYet,"Not Implemented Yet");
			default:break;
		}
	}
} // namespace std





template<typename T>
struct Error: public std::exception {
	T error;	
	std::string error_str;

    Error():error_str("Unknown"){}
	Error(const T& e):error(e),error_str(std::is_integral<T>::value?std::strerror(e):std::to_string<T>(e)){}
	const char* what() const noexcept override { return error_str.c_str(); }
};

/**
 * prints an erro and exits the program
 * @param message message to be shown
*/
template<typename T = std::string>
inline void todo(const T& message){
	std::cerr<<message<<std::endl;
	std::exit(-1);
}

//some defines for TODO
#ifndef TODO_MESSAGE
#define TODO_MESSAGE "Not implemented yet"
#endif

#define CODE_FILE std::string(__FILE__)
#define CODE_LINE uint32_t(__LINE__)
#define CODE_POINT (std::string(__FILE__ ":")+std::to_string(__LINE__))

#define Todo todo<std::string>(CODE_POINT+std::string(" #" TODO_MESSAGE))
#define Todo_(X) todo<std::string>(CODE_POINT+std::string(" #")+std::to_string(X))

//just to confuse people with your code
#ifdef	RUST_LIKE_CPP
#define let auto
#endif