//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : BNoise.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_BNOISE_H)
#define _BNOISE_H

#include "BWave.hpp"

class BNoise : public BWave {
public:
	unsigned int GetValueNow();
	unsigned char GetId();
	unsigned int GetFrequency();
	unsigned int GetValueNow();
	unsigned char GetId();
};

#endif  //_BNOISE_H
