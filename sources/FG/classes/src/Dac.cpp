//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : Dac.cpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//



/*
	DACのラッチはLOWにしとけばいい
	A,Bのシンクロが必要なときだけ使う
*/


#include "Dac.hpp"
#include "sfr_r829.h"

//とりあえず4線モードを使ってみる そうするとチップセレクト処理が必要なくなる
Dac::Dac()
	: m_ssu()
{
	m_ssu.InitializeSynchronizedClockMode(); // SSU初期化


	m_data_outs.bit.dac_select = DAC_SELECT_A;
	m_data_outs.bit.input_buffer_control = DAC_INPUT_BUFFER_CONTROL_BUFFERED;
	m_data_outs.bit.gain_select = DAC_GAIN_1X;
	m_data_outs.bit.power_down_control = DAC_SHUTDOWN_POWER_ON;
	m_data_outs.bit.dac_data = 0;

	m_send = 0;
	m_send |= (DAC_SELECT_A << 15);
	m_send |= (DAC_INPUT_BUFFER_CONTROL_BUFFERED << 14);
	m_send |= (DAC_GAIN_1X << 13);
	m_send |= (DAC_SHUTDOWN_POWER_ON << 12);

}

void Dac::WriteVoltageA(unsigned int vol) {
	m_send |= (DAC_SELECT_A << 15);
	m_send &= 0xF000;
	m_send |= (vol & 0x0FFF);

	m_ssu.WriteSync(m_send);

}

void Dac::WriteVoltageB(unsigned int vol) {
	m_send |= (DAC_SELECT_B << 15);
	m_send &= 0xF000;
	m_send |= (vol & 0x0FFF);

	m_ssu.WriteSync(m_send);

}


void Dac::SInitialize(){
	//sm_send = 0x7000;
	SSUbus::SInitializeSynchronizedClockMode();
}

void Dac::SWriteVoltageA(unsigned int vol) {
	unsigned int tmp_send = 0x7000;
	tmp_send |= (vol & 0x0FFF);
	SSUbus::SWriteSync(tmp_send);

}

void Dac::SWriteVoltageB(unsigned int vol) {
	unsigned int tmp_send = 0xF000;
	tmp_send |= (vol & 0x0FFF);
	SSUbus::SWriteSync(tmp_send);
}



