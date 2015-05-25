//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : FunctionGenerator.hpp
//  @ Date : 2015/05/25
//  @ Author : 
//
//


#if !defined(_FUNCTIONGENERATOR_H)
#define _FUNCTIONGENERATOR_H

#include "AWave.hpp"
#include "BWave.hpp"
#include "Dac.hpp"
#include "Timer.hpp"

class FunctionGenerator {
public:
	void Update();
	void InsertWave(unsigned char idx, AWave w);
	void InsertWave(unsigned char idx, BWave w);
	void DeleteWaveFromSlotMasterIndex(unsigned char idx);
	unsigned char GetIdFromSlotMasterIndex(unsigned char idx);
	Wave* GetWaveFromSlotMasterIndex(unsigned char idx);
	unsigned char GetAWaveSlotSize();
	unsigned char GetBWaveSlotSize();
private:
	static const unsigned char m_AWAVE_SLOT_SIZE_MAX;
	static const unsigned char m_BWAVE_SLOT_SIZE_MAX;
	Dac m_dac;
	Timer m_tim;
	AWave* m_aslot;
	BWave* *m_bslot;
	Wave* m_pool_awave;
	void AUpdate();
	void BUpdate();
	FunctionGenerator();
};

#endif  //_FUNCTIONGENERATOR_H