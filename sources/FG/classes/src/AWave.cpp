//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : AWave.cpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#include "AWave.hpp"
#define GAIN_SCL 8

AWave::AWave()
	: m_A(100)

{
	;
}

AWave::AWave(unsigned char id)
	: m_A(100), ID(id)

{
	;
}


// 0 ~ 100
void AWave::SetGain(unsigned char gain) {
	if (gain > 100){
		m_A = 1 << GAIN_SCL;
	} else{
		m_A = (gain << GAIN_SCL) / 100;
	}
}

unsigned int AWave::GetGain() {
	return ((m_A * 100) >> GAIN_SCL);
}

void AWave::SetPhase(float phain) {
	m_clk.SetPhase(phain);
}

float AWave::GetPhase() {
	return m_clk.GetPhase();
}

void AWave::SetFrequency(unsigned int fin) {
	m_clk.SetFreq(fin);
}

unsigned int AWave::GetFrequency() {
	return m_clk.GetFreq();
}

unsigned int AWave::Out() {
	return (m_is_enabled) ? 
		(((unsigned long)GetValueNow() * (unsigned long)m_A) >> GAIN_SCL)
		: 0;
}