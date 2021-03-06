//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : Timer.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


//割り込み間隔は5usが最小だった
//8bitカウンタだと12.8usが最大

#if !defined(_TIMER_H)
#define _TIMER_H

#include "Dac.hpp"


class INTRbase{
public:
	virtual void op() = 0;
};

class Timer {
public:
	Timer();
	
	void Enable();
	void Disable();
	void SetDt(float dt_ms);
	float GetDt();
	static float SGetDt();

	//volatile void IntrTB();
	void SetInterrupter(void (*op)());
	void SetClassInterrupter(INTRbase * pib);

private:
	//Dac m_dac;

	unsigned int m_tmp;

	unsigned int m_tmp_count;
	unsigned char m_tmp_pr;
	unsigned char m_tmp_pre;

};


#endif  //_TIMER_H
