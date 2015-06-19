//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : Clock.cpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#include "Clock.hpp"
#include "Timer.hpp"

Clock::Clock()
{

#ifdef FIXED_POINT
	
	m_scale = 8;
	m_fp_nop = 0;
	m_fp_pinv = 0;
	m_fp_dt_us = 0;
	m_fp_f = 0;
	m_fp_k = 0;
	m_fp_phase = 0;
	m_fp_phase_shift_point = 0;

#else

	m_nop = 0;
	m_dt = 0;
	m_pinv = 0;
	m_phase = 0;
	m_f = 0;
	//	, m_k = 0
	m_phase_shift_point = 0;
	m_k_f = 0;

#endif	

	
}

/*

#ifdef FIXED_POINT

#else

#endif

*/

void Clock::SetFreq(unsigned int fin) {


#ifdef FIXED_POINT
	m_f = fin;
	m_fp_f = fin << m_scale;
	//m_fp_pinv = (((m_fp_f * m_fp_nop) >> m_scale) * m_fp_dt) >> m_scale;
	//m_fp_pinv = (((m_fp_f * m_fp_nop) >> m_scale) * m_fp_dt_us) >> m_scale / (1000000);
	m_fp_pinv = (unsigned long)((unsigned long)fin * (unsigned long)(m_fp_nop >> m_scale) * m_fp_dt_us / 1000000);
#else
	m_f = fin;
	m_pinv = (float) (m_f * m_nop) * m_dt;
#endif
	
}

void Clock::SetDt() {

#ifdef FIXED_POINT

	unsigned int tmp = 1;
	for (int i = 0; i < m_scale; i++){
		tmp *= 2;
	}
	m_fp_dt_us = (unsigned long) (Timer::SGetDt() * 1000000.0 * (float) tmp);

#else

	//m_dt = dtin;
	m_dt = Timer::SGetDt();

#endif



}

void Clock::SetNop(unsigned int nopin) {

#ifdef FIXED_POINT

	m_fp_nop = nopin << m_scale;

#else

	m_nop = nopin;

#endif


	
	
}

void Clock::SetPhase(float phain) {

#ifdef FIXED_POINT

	unsigned int tmp = 1;
	for (int i = 0; i < m_scale; i++){
		tmp *= 2;
	}
	//m_fp_phase_shift_point = (unsigned int) ((float) m_nop * phain * (float) tmp);// #TODO
	m_fp_phase_shift_point = (m_fp_nop * (unsigned long) (phain * (float)tmp)) >> m_scale;
	//m_fp_phase_shift_point = m_phase_shift_point << m_scale;

#else

	m_phase = phain;
	m_phase_shift_point = (unsigned int)((float)m_nop * m_phase);

#endif






}

void Clock::Set(unsigned int fin, unsigned int nopin, float phain){
	SetDt();
	SetNop(nopin);
	SetFreq(fin);
	SetPhase(phain);
}

unsigned int Clock::Update() {
	//m_k = (m_k + (unsigned int)m_pinv + m_phase_shift_point) % m_nop;


	//m_k = (unsigned int)m_k_f;

	//m_k = (m_k + (m_fp_pinv >> m_scale) + (m_fp_phase_shift_point >> m_scale)) % m_nop;
	//m_fp_k = (m_fp_k + m_fp_pinv + m_fp_phase_shift_point);
	//m_k = (m_fp_k >> m_scale) % m_nop;
	

#ifdef FIXED_POINT

	m_fp_k += m_fp_pinv + m_fp_phase_shift_point;
	if(m_fp_k > m_fp_nop){m_fp_k = 0;}
	return (unsigned int)(m_fp_k >> m_scale);

#else

	m_k_f += m_pinv + (float) m_phase_shift_point;
	if (m_k_f > m_nop){ m_k_f = 0; }
	return (unsigned int) m_k_f;

#endif

}

unsigned int Clock::GetFreq(){
	

#ifdef FIXED_POINT
	return m_f;
	//return (unsigned int)(m_fp_f >> m_scale);

#else

	return m_f;

#endif


};
float Clock::GetDt(){ 

#ifdef FIXED_POINT
	unsigned int tmp = 1;
	for (int i = 0; i < m_scale; i++){
		tmp *= 2;
	}
	return ((float)m_fp_dt_us / (float)tmp / 1000000.0);

#else

	return m_dt;

#endif

};
unsigned int Clock::GetNop(){ 

#ifdef FIXED_POINT

	return (m_fp_nop >> m_scale);

#else

	return m_nop;

#endif

};
unsigned int Clock::GetPhase(){ 

#ifdef FIXED_POINT
	unsigned int tmp = 1;
	for (int i = 0; i < m_scale; i++){
		tmp *= 2;
	}
	return ((float)m_fp_phase / (float)tmp);

#else

	return m_phase;	

#endif

};


