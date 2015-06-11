//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : ATriangle.cpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#include "ATriangle.hpp"
#include "Settings.hpp"

#define SCL_TR 10

ATriangle::ATriangle(unsigned int freq, float phase, unsigned int gain)
{

	SetGain(gain);
	m_clk.Set(freq, 64, phase);

	unsigned int tmp = 1;
	for (int i = 0; i < SCL_TR; i++){
		tmp *= 2;
	}

	m_dv_fp = (unsigned long) ((double) 0xFFF / ((double) m_clk.GetNop() / 2.0) * (double) tmp);

}

unsigned int ATriangle::GetValueNow() {
	unsigned int out = (unsigned int) ((((unsigned long) (m_clk.Update())) * m_dv_fp) >> SCL_TR);
	if (out < 0xFFF){
		return out;
	} else{
		return (unsigned int) (0x1FFF - out);
	}
}

unsigned char ATriangle::GetId() {
	return Settings::WAVE_ID_ATRIANGLE;
}


