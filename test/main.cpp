#include <wrapper.hpp>



// Driver program to test above
int main()
{
	I32a a = -1;

	printf(" %d \n", a.unwrap());
	print_binary(a.unwrap());
	print_binary(a.data());

	return 0;
}

