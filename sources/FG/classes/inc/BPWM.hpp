//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : BPWM.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_BPWM_H)
#define _BPWM_H

#include "BWave.hpp"

class BPWM : public BWave {
public:
	unsigned int GetValueNow();
	unsigned char GetId();
	unsigned int GetFrequency();

};

#endif  //_BPWM_H
