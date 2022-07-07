#pragma once
#include <iostream>

#define LOGMSG(x) std::cout << x ;
#define LOGMSGL(x) std::cout << x << std::endl;
#define ENDL std::cout << std::endl;

#define ASSERT(x,msg) if(x==0){ LOGMSGL(msg); __debugbreak(); }
#define ASSERTPTR(x,msg) if(x==nullptr){ LOGMSGL(msg); __debugbreak(); }
