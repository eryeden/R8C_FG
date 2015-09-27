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
#include "Wave.hpp"
#include "AWave.hpp"
#include "BWave.hpp"
#include "Settings.hpp"

#include "ASawtooth.hpp"
#include "ASine.hpp"
#include "ATriangle.hpp"
#include "APWM.hpp"
#include "ANoise.hpp"
#include "ANone.hpp"

//static ANone m_anone;
//static ASawtooth m_asawtooth(100, 0, 50);
//static ASine m_asine(100, 0, 50);
//static ATriangle m_atriangle(200, 0, 10);
//static APWM m_apwm(100, 0, 50);
//static ANoise m_anoise(100, 0, 10);

//ANone m_anone;
//ASawtooth m_asawtooth(100, 0, 50);
//ASine m_asine(100, 0, 50);
//ATriangle m_atriangle(200, 0, 10);
//APWM m_apwm(100, 0, 50);
//ANoise m_anoise(100, 0, 10);

FunctionGenerator::FunctionGenerator()
	: m_dac()
	, m_anone()
	, m_asawtooth(100, 0, 50)
	, m_asine(100, 0, 50)
	, m_atriangle(100, 0, 50)
	, m_apwm(100, 0, 50)
	, m_anoise(100, 0, 50)

{

	

	m_apwm.SetDuty(0.5);

	m_pool_wave[0] = &m_anone;
	//m_pool_wave[1] = &m_anone;
	//m_pool_wave[2] = &m_anone;
	//m_pool_wave[3] = &m_anone;
	//m_pool_wave[4] = &m_anone;
	//m_pool_wave[5] = &m_anone;

	m_pool_wave[1] = &m_asawtooth;
	m_pool_wave[2] = &m_asine;
	m_pool_wave[3] = &m_atriangle;
	m_pool_wave[4] = &m_apwm;
	m_pool_wave[5] = &m_anoise;

	ss = &m_atriangle;

	//m_aslot[0] = (AWave *) m_pool_wave[1];
	//m_aslot[1] = (AWave *) m_pool_wave[2];
	//m_aslot[2] = (AWave *) m_pool_wave[3];
	//m_aslot[3] = (AWave *) m_pool_wave[3];
	//m_aslot[4] = (AWave *) m_pool_wave[4];

	//m_aslot[0] = &m_anone;
	//m_aslot[1] = &m_asawtooth;
	//m_aslot[2] = &m_atriangle;
	//m_aslot[3] = &m_asine;
	//m_aslot[4] = &m_apwm;

	m_aslot[0] = &m_anone;
	m_aslot[1] = &m_anone;
	m_aslot[2] = &m_anone;
	m_aslot[3] = &m_anone;
	m_aslot[4] = &m_anone;

	for (int i = 0; i < Settings::FG_MAX_POOL; ++i){
		m_pool_wave[i]->Enable();
	}



}



void FunctionGenerator::Update() {
	AUpdate();
	//BUpdate();
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

unsigned char FunctionGenerator::GetIdFromPoolMasterIndex(unsigned char idx) {
	if ((idx) <= Settings::FG_MAX_POOL) {
		return m_pool_wave[idx]->GetId();
	}else {
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
		
		return m_aslot[0];
	}
}

Wave* FunctionGenerator::GetWaveFromPoolMasterIndex(unsigned char idx) {
	//if ((idx) <= Settings::FG_MAX_POOL){
	//	if (idx == Settings::FG_MAX_POOL){
	//		return m_pool_wave[Settings::FG_MAX_POOL - 1];
	//	}
	//	else{
	//		return m_pool_wave[idx];
	//	}
	//}
	//else{
	//	return 0;
	//}
	return m_pool_wave[idx];
}

unsigned char FunctionGenerator::GetAWaveSlotSize() {
	return Settings::FG_MAX_SLOT;
}

unsigned char FunctionGenerator::GetBWaveSlotSize() {
	return 1;
}

#define MIX_SCL 15
void FunctionGenerator::AUpdate() {
	char i;
	unsigned long out = 0;
	//unsigned char now = 0;
	for (i = 0; i < Settings::FG_MAX_SLOT; i++){
		if (m_aslot[i]->GetId() != Settings::WAVE_ID_ANONE){
			//m_dac.WriteVoltageA(m_aslot[i]->GetValueNow());
			out += (unsigned int)(m_aslot[i]->Out());
			//now++;
		}
	}

	//out << MIX_SCL;
	//out /= now;
	//m_dac.WriteVoltageA((unsigned int)(out >> MIX_SCL));
	
	out = (out > 0xFFF) ? 0xFFF : out;
	
	m_dac.WriteVoltageA((unsigned int)out);

}

void FunctionGenerator::BUpdate() {
	m_bslot->GetValueNow();
}

//ANONE以外の有効な波の数
unsigned char FunctionGenerator::GetNoW(){
	unsigned char tmp = 0;
	for (int i = 0; i < Settings::FG_MAX_SLOT; i++){
		if (m_aslot[i]->GetId() != Settings::WAVE_ID_ANONE){
			tmp++;
		}
	}
	return tmp;
}



