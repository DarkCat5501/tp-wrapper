#pragma once
#include "core.hpp"

class NoneOption;
class AnyOption;
template<typename T>
class Option{
	public:
		inline bool assigned() const { return m_assigned; }
		inline T& unwrap(){  return m_value; }

		inline T& unwrap_or_default(){ 
			if(!m_assigned) m_value = T();
			return m_value;
		}

		static inline Option<T> Some(const T& value){ return Option<T>(value); }
		static inline Option<T> None(){ return Option<T>(); }

		Option(NoneOption&&):m_assigned(false){}
		Option(AnyOption&&) = delete;

		inline constexpr bool operator==(const NoneOption& other){return !m_assigned;}
		inline constexpr bool operator==(const AnyOption& other){return m_assigned;}

		template<typename P>
		inline constexpr bool operator==(const Option<P>& other){ 
			if(!other.m_assigned || !m_assigned) return m_assigned == other.m_assigned;
			return m_value == other.m_value;
		}

	protected:
		bool m_assigned;
		T m_value;

		Option():m_assigned(false){}
		Option(const T& value):m_assigned(true),m_value(value){}
};

class NoneOption{
	public:
		NoneOption(){}
		template<typename T>
		NoneOption(Option<T>&& other){}

		inline constexpr bool operator==(const NoneOption&) const { return true; }
		inline constexpr bool operator==(const AnyOption&) const { return false; }

		template<typename T>
		inline constexpr bool operator==(const Option<T>& other){ return !other.assigned(); }
};

class AnyOption{
	public:
		AnyOption(){}
		template<typename T>
		AnyOption(Option<T>&& other){}

		inline constexpr bool operator==(const AnyOption&) const { return true; }
		inline constexpr bool operator==(const NoneOption&) const { return false; }

		template<typename T>
		inline constexpr bool operator==(const Option<T>& other){ return other.assigned(); }
};

template<typename T>
static inline Option<T> Some(const T& value){ return Option<T>::Some(value); }

template<typename T>
static inline Option<T> None(){ return Option<T>::Some(); }

static inline NoneOption None(){ return NoneOption(); }
static inline AnyOption Any(){ return AnyOption(); }


#define __match_var __13_match41623
#define match(X) __match_var = X
#define if_match(Y) if(__match_var == Y)
#define elif_match(Y) else if(__match_var == Y)
