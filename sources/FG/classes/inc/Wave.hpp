//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : Wave.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_WAVE_H)
#define _WAVE_H


class Wave {
public:
	Wave();
	unsigned char m_is_inserted;
	virtual void SetFrequency(unsigned int fin) = 0;
	virtual unsigned int GetFrequency() = 0;
	virtual unsigned int GetValueNow() = 0;
	virtual unsigned char GetId() = 0;
	virtual unsigned int Out();
	void Enable();
	void Disable();
	
protected:
	bool m_is_enabled;

};

#endif  //_WAVE_H
