#pragma once

#include <exception>
#include <string>
#include <cerrno>
#include <cstring>
#include <clocale>
#include <cstdlib>
#include <iostream>
#include <cinttypes>

template<typename T = std::string>
struct Error: public std::exception {
	T error;
	Error(const T& e):error(e){}
	Error(int e):error(std::strerror(e)){}
	const char* what() const noexcept override { return (const char *)error; }
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