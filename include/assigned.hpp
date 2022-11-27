#pragma once
#include "core.hpp"
#include "option.hpp"

#define L_BIT(X) (0x80 << 8*(sizeof(X)-1) )
#define R_BIT(X) (0x1)
#define I_ASSIGN_BIT(X) (0x80 << 8*(sizeof(X)-1) )
#define F_ASSIGN_BIT(X) (0x1)
#define A_SIGN_BIT(X) (0x40 << 8*(sizeof(X)-1) )
#define I_ASSIGN_SIGN_BITS(X) (0xC0 << 8*(sizeof(X)-1) )
#define FULL_MASK(X) ((X)~0x0)

template<typename T>
T assigned_to_value(T a){
	if(std::is_signed<T>::value){
		T b = a&(I_ASSIGN_SIGN_BITS(T)^FULL_MASK(T));
		return (a&A_SIGN_BIT(T))?-b:b;
	}
	return a&(I_ASSIGN_BIT(T)^FULL_MASK(T));
};

template<typename T>
T value_to_assigned(T a,bool assigned){
	T b = a<0 ? (-a) | A_SIGN_BIT(T) :a;	
	return b | (assigned ? I_ASSIGN_BIT(T) : 0x0);
};

template<typename T>
T floating_to_assigned(T a, bool assigned){
	uint64_t value = mutate(uint64_t, a);
	if(assigned) value |= 0x1;
	else value &= ~0x1;
	return mutate(T, value);
}

template<typename T>
T assigned_to_floating(T a){
	uint64_t value = mutate(uint64_t, a);
	value &= ~0x1;
	return mutate(T, value);
}

template<typename T>
T reverse_bits(T n){
	uint64_t value = mutate(uint64_t,n);
	uint64_t rev = 0;
	for(size_t bit=0;bit<sizeof(T)*8;bit++){
		rev <<= 1;
		rev ^= (value >> bit & 0x1);
	}
	return mutate(T,rev);
}

template<typename T>
void print_binary(T data){
	uint64_t dt = mutate(uint64_t, data);
	for(int bit = sizeof(T)*8 -1; bit>=0;--bit)
		putc((dt >> bit) & 0x1 ? '1':'0',stdout );
	printf("\n");
}


/**
 * packed assignment checked type
 * A S Data..
 * 0 0 0 0 0 0 ... 0 
 * where A is the assigned bit
 * and S is the sign bit
 * */ 
template<typename T>
class Asg {
	private:
		T m_value;
	public:
		Asg():m_value(0x0){}
		Asg(const T& value):m_value(value_to_assigned(value,true)){}
		Asg(const Asg<T>&& other):m_value(other.m_value){}
		
		
		inline bool assigned() const { return m_value & I_ASSIGN_BIT(T); }
		inline T unwrap() const { return assigned_to_value<T>(m_value); }
		inline const T data() const { return m_value; }

		inline Asg<T>& operator=(const Asg<T>& other){ m_value = other.m_value; return *this; }
		inline Asg<T>& operator=(const T& other){ m_value = value_to_assigned(other,true); return *this; }


		inline bool operator==(const Asg<T>& other) const { return assigned() == other.assigned() && other.m_value == m_value; }
		inline bool operator==(const T& other) const { return assigned() && other == unwrap(); }
		inline bool operator==(const NoneOption& other) const { return !assigned(); }
		inline bool operator==(const Option<T>& other) const { return other.assigned() == assigned() && other.unwrap() == unwrap(); }
};

template<typename T>
class AsgF {
	private:
		T m_value;
	public:
		AsgF():m_value(0x0){}
		AsgF(const T& value):m_value(floating_to_assigned(value,true)){}
		AsgF(const Asg<T>&& other):m_value(other.value){}
		
		
		inline bool assigned() const { return mutate(uint64_t,m_value) & F_ASSIGN_BIT(T); }
		inline T unwrap() const { return assigned_to_floating<T>(m_value); }
		inline const T data() const { return m_value; }

		inline Asg<T>& operator=(const Asg<T>& other){ m_value = other.m_value; return *this; }
		inline Asg<T>& operator=(const T& other){ m_value = floating_to_assigned(other,true); return *this; }


		inline bool operator==(const Asg<T>& other) const { return assigned() == other.assigned() && other.m_value == m_value; }
		inline bool operator==(const T& other) const { return assigned() && other == unwrap(); }
		inline bool operator==(const NoneOption& other) const { return !assigned(); }
		inline bool operator==(const Option<T>& other) const { return other.assigned() == assigned() && other.unwrap() == unwrap(); }
};

using I8a = Asg<int8_t>;
using U8a = Asg<uint8_t>;
using I16a = Asg<int16_t>;
using U16a = Asg<uint16_t>;
using I32a = Asg<int32_t>;
using U32a = Asg<uint32_t>;
using I64a = Asg<int64_t>;
using U64a = Asg<uint64_t>;
using F32a = AsgF<float>;
using F64a = AsgF<double>;