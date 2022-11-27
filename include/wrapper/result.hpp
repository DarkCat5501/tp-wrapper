#pragma once
#include "core.hpp"

template<typename E, class ET>
class VoidResult;

template<typename T,typename E = uint32_t, class ET = Error<E>>
class Result{
	public:
		inline bool ok() const { return m_ok; }
		inline E error() const { return m_error; }

		inline T& unwrap(){ 
			if(!m_ok)throw ET(m_error);
			return m_value;
		}

		static inline Result<T,E,ET> Ok(const T& value){ return Result<T,E,ET>(value); }
		static inline Result<T,E,ET> Err(const E& e){ return Result<T,E,ET>(e); }
		static inline Result<T,E,ET> Err(){ return Result<void,E,ET>(false); }

		Result(VoidResult<E,ET>&& other):m_ok(other.ok()),m_error(other.error()){}

	protected:
		bool m_ok;
		T m_value;
		E m_error;

		Result(bool ok = false):m_ok(ok),m_error((E)0){}
		Result(const E& e):m_ok(false),m_error(e){}
		Result(const T& value):m_ok(true),m_value(value){}
};

template<typename E = uint32_t, class ET = Error<E>>
class VoidResult{
	public:
		inline bool ok() const { return m_ok; }
		inline E error() const { return m_error; }
		inline void unwrap(){ if(!m_ok)throw ET(m_error); }

		static inline VoidResult<E,ET> Ok(){ return VoidResult<E,ET>(true); }
		static inline VoidResult<E,ET> Err(){ return VoidResult<E,ET>(false); }
		static inline VoidResult<E,ET> Err(const E& e){ return VoidResult<E,ET>(e); }
		static inline VoidResult<E,ET> Err(int e){ return VoidResult<E,ET>(e); }

		template<typename T>
		VoidResult(Result<T,E,ET>&& other):m_ok(other.ok()),m_error(other.error()){}

	protected:
		bool m_ok;
		E m_error;

		VoidResult(bool ok = false):m_ok(ok),m_error((E)0){}	
		VoidResult(const E& e):m_ok(false),m_error(e){}
		VoidResult(int e):m_ok(false),m_error(e){}
};

template<typename E = uint32_t, class ET = Error<E>>
static inline VoidResult<E,ET> Ok(){ return VoidResult<E,ET>::Ok(); }

template<typename E = uint32_t, class ET = Error<E>>
static inline VoidResult<E,ET> Err(const E& e){ return VoidResult<E,ET>::Err(e); }

template<typename E = uint32_t, class ET = Error<E>>
static inline VoidResult<E,ET> Err(){ return VoidResult<E,ET>::Err(); }

template<typename E = uint32_t, class ET = Error<E>>
static inline VoidResult<E,ET> Err(int e){ return VoidResult<E,ET>::Err(e); }

template<typename T,typename E = uint32_t, class ET = Error<E>>
static inline Result<T,E,ET> Ok(const T& value){ return Result<T,E,ET>::Ok(value); }

template<typename T,typename E = uint32_t, class ET = Error<E>>
static inline Result<T,E,ET> Err(const E& e){ return Result<T,E,ET>::Err(e); }

template<typename T,typename E = uint32_t, class ET = Error<E>>
static inline Result<T,E,ET> Err(){ return Result<T,E,ET>::Err(); }


//just to confuse people with your code
#ifdef	RUST_LIKE_CPP
#define fn template<typename VariableType> Result<VariableType>
#define var VariableType
#endif