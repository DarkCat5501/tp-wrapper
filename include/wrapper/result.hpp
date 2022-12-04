#pragma once
#include "core.hpp"

template<typename E>
class VoidResult;

template<typename T,typename E = Error<DefaultErrorType> >
class Result{
	public:
		typedef typename std::conditional<std::is_enum<E>::value || std::is_integral<E>::value, Error<E>, E>::type ErrorType;

		inline bool ok() const { return m_ok; }
		inline E error() const { return m_error; }

		inline T& unwrap(){ 
			if(!m_ok)throw (ErrorType)m_error;
			return m_value;
		}

		static inline Result<T,E> Ok(const T& value){ return Result<T,E>(value); }
		static inline Result<T,E> Err(const E& e){ return Result<T,E>(e); }
		static inline Result<T,E> Err(){ return Result<void,E>(false); }

		Result(VoidResult<E>&& other):m_ok(other.ok()),m_error(other.error()){}

	protected:
		bool m_ok;
		T m_value;
		E m_error;

		Result(bool ok = false):m_ok(ok){}
		Result(const E& e):m_ok(false),m_error(e){}
		Result(const T& value):m_ok(true),m_value(value){}
};

template<typename E = Error<DefaultErrorType> >
class VoidResult{
	public:
		typedef typename std::conditional<std::is_enum<E>::value || std::is_integral<E>::value, Error<E>, E>::type ErrorType;

		inline bool ok() const { return m_ok; }
		inline E error() const { return m_error; }
		inline void unwrap(){ if(!m_ok)throw (ErrorType)m_error; }

		static inline VoidResult<E> Ok(){ return VoidResult<E>(true); }
		static inline VoidResult<E> Err(){ return VoidResult<E>(false); }
		static inline VoidResult<E> Err(const E& e){ return VoidResult<E>(e); }

		template<typename T>
		VoidResult(Result<T,E>&& other):m_ok(other.ok()),m_error(other.error()){}

	protected:
		bool m_ok;
		E m_error;

		VoidResult(bool ok = false):m_ok(ok){}
		VoidResult(const E& e):m_ok(false),m_error(e){}
};

template<typename E = Error<DefaultErrorType>>
static inline VoidResult<E> Ok(){ return VoidResult<E>::Ok(); }

template<typename E = Error<DefaultErrorType>>
static inline VoidResult<E> Err(const E& e){ return VoidResult<E>::Err(e); }

template<typename E = Error<DefaultErrorType>>
static inline VoidResult<E> Err(){ return VoidResult<E>::Err(); }

template<typename E = Error<DefaultErrorType>>
static inline VoidResult<E> Err(int e){ return VoidResult<E>::Err(e); }

template<typename T,typename E = Error<DefaultErrorType>>
static inline Result<T,E> Ok(const T& value){ return Result<T,E>::Ok(value); }

//just to confuse people with your code
#ifdef	RUST_LIKE_CPP
#define fn template<typename VariableType> Result<VariableType>
#define var VariableType
#endif
