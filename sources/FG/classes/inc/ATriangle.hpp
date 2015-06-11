//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : ATriangle.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_ATRIANGLE_H)
#define _ATRIANGLE_H

#include "AWave.hpp"

class ATriangle : public AWave {
public:
	ATriangle(unsigned int freq, float phase, unsigned int gain);
	unsigned int GetValueNow();
	unsigned char GetId();
private:
	unsigned long m_dv_fp;
};

#endif  //_ATRIANGLE_H
