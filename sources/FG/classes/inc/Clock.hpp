//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : Clock.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_CLOCK_H)
#define _CLOCK_H

#define FIXED_POINT

//DTはここで計算するようにする

class Clock {
public:
	Clock();
	void SetFreq(unsigned int fin);
	void SetDt();
	void SetNop(unsigned int nopin);
	void SetPhase(float phain);
	void Set(unsigned int fin, unsigned int nopin, float phain);
	unsigned int GetFreq();
	float GetDt();
	unsigned int GetNop();
	unsigned int GetPhase();
	unsigned int Update();
private:


#ifdef FIXED_POINT

	unsigned char m_scale;
	unsigned int m_f;

	//unsigned int m_fp_nop;
	//unsigned int m_fp_pinv;
	//unsigned long m_fp_dt_us;
	//unsigned int m_fp_f;
	//unsigned int m_fp_k;
	//unsigned int m_fp_phase;
	//unsigned int m_fp_phase_shift_point;

	unsigned long m_fp_nop;
	unsigned long m_fp_pinv;
	unsigned long m_fp_dt_us;
	unsigned long m_fp_f;
	unsigned long m_fp_k;
	unsigned long m_fp_phase;
	unsigned long m_fp_phase_shift_point;

#else

	unsigned int m_nop;
	float m_dt;
	float m_pinv;
	unsigned int m_f;
	//unsigned int m_k;
	float m_k_f;
	float m_phase;
	unsigned int m_phase_shift_point;

#endif
	//unsigned int m_fp_nop;
	//unsigned int m_fp_pinv;
	//unsigned int m_fp_dt;
	//unsigned int m_fp_dt_us;
	//unsigned int m_fp_f;
	//unsigned int m_fp_k;
	//unsigned int m_fp_phase;
	//unsigned int m_fp_phase_shift_point;
	

};

#endif  //_CLOCK_H
