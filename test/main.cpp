#include <wrapper.hpp>



Result<F32a> sum(const F32a& a,const F32a& b){
	return Ok<F32a>(a.unwrap() + b.unwrap());
}

// Driver program to test above
int main()
{
	F32a a = sum(10.001,10.001).unwrap();
	printf(" %f \n", a.unwrap());

	return 0;
}

