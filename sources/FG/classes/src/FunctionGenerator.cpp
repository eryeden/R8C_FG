//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : FunctionGenerator.cpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#include "FunctionGenerator.hpp"
#include "AWave.hpp"
#include "BWave.hpp"
#include "Settings.hpp"


FunctionGenerator::FunctionGenerator() {

}



void FunctionGenerator::Update() {
	AUpdate();
	BUpdate();
}

void FunctionGenerator::InsertWave(unsigned char idx, AWave* w) {
	if (idx > Settings::FG_MAX_SLOT){return;}
	m_aslot[idx] = w;
}

void FunctionGenerator::InsertWave(unsigned char idx, BWave* w) {
	m_bslot = w;
}

void FunctionGenerator::InsertWaveFromPoolToSlotMasterIndex(unsigned char slot_idx, unsigned char pool_idx){
	if ((slot_idx) <= Settings::FG_MAX_SLOT){
		if (slot_idx == Settings::FG_MAX_SLOT){
			//m_bslot = ;
			if (m_pool_wave[pool_idx]->GetId() 
											== (Settings::WAVE_ID_BNONE 
												& Settings::WAVE_ID_BNONE
												& Settings::WAVE_ID_BPWM)
												)
			{
				m_bslot = (BWave *)m_pool_wave[pool_idx];
			} else{
				return;
			}
		}
		else{
			m_aslot[slot_idx] = (AWave *)m_pool_wave[pool_idx];
		}
	}
	else{
		return;
	}
}

void FunctionGenerator::DeleteWaveFromSlotMasterIndex(unsigned char idx) {
	if ((idx) <= Settings::FG_MAX_SLOT){
		if (idx == Settings::FG_MAX_SLOT){
			//m_bslot = ;
		}
		else{
			//m_aslot[idx] =;
		}
	}
	else{
		return;
	}
}

unsigned char FunctionGenerator::GetIdFromSlotMasterIndex(unsigned char idx) {
	if ((idx) <= Settings::FG_MAX_SLOT){
		if (idx == Settings::FG_MAX_SLOT){
			return m_bslot->GetId();
		} else{
			return m_aslot[idx]->GetId();
		}
	} else{
		return -1;
	}
}

Wave* FunctionGenerator::GetWaveFromSlotMasterIndex(unsigned char idx) {
	if ((idx) <= Settings::FG_MAX_SLOT){
		if (idx == Settings::FG_MAX_SLOT){
			return m_bslot;
		}
		else{
			return m_aslot[idx];
		}
	} else{
		return nullptr;
	}
}

unsigned char FunctionGenerator::GetAWaveSlotSize() {
	return Settings::FG_MAX_SLOT;
}

unsigned char FunctionGenerator::GetBWaveSlotSize() {
	return 1;
}

void FunctionGenerator::AUpdate() {
	char i;
	for (i = 0; i < Settings::FG_MAX_SLOT; i++){
		if (m_aslot[i]->GetId() != Settings::WAVE_ID_ANONE){
			m_dac.WriteVoltage(m_aslot[i]->GetValueNow());
		}
	}

}

void FunctionGenerator::BUpdate() {
	m_bslot->GetValueNow();
}
