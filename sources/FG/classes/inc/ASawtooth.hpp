//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : ASawtooth.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_ASAWTOOTH_H)
#define _ASAWTOOTH_H

#include "AWave.hpp"

class ASawtooth : public AWave {
public:
	ASawtooth(unsigned int freq, unsigned int phase, unsigned int gain);
	unsigned int GetValueNow();
	unsigned char GetId();
private:
	//float m_dv;

	unsigned long m_dv_fp;
	
};

#endif  //_ASAWTOOTH_H
