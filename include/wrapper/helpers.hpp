#pragma once
///functions and helper definitions
#define L_BIT(X) (0x80 << 8*(sizeof(X)-1) )
#define R_BIT(X) (0x1)
#define FULL_MASK(X) ((X)~0x0)

#define mutate(X,Y) (*(X*)&Y)
#define return_case(X,Y) case X: return Y
#define return_if(X,Y) if(X) return Y


