#ifndef _VRANDOM_
#define _VRANDOM_

#include "mtrand.h"

class VRandom : public MTRand_int32 {
public :
	VRandom(unsigned long seed) : MTRand_int32(seed) {}
	int range(int a, int b) { return a + (*this)()%(b-a); }
	int rand() { return (*this)(); }
};

#endif


