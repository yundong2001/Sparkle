#pragma once

#define BIT(X) (1<<(X))

#define BIT_OPERATE_AND(A,B) \
inline constexpr B operator&(A a,A b)\
{\
    return static_cast<B>(a) & static_cast<B>(b);\
}

#define BIT_OPERATE_OR(A,B) \
inline constexpr A operator|(A a,A b)\
{\
    return static_cast<A>(static_cast<B>(a) | static_cast<B>(b));\
}


#define BIT_OPERATE(A,B) \
BIT_OPERATE_AND(A,B)     \
BIT_OPERATE_OR(A,B)
