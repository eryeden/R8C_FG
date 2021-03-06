//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : Dac.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_DAC_H)
#define _DAC_H

#include "SSUbus.hpp"

class Dac {
public:
	Dac();
	void WriteVoltageA(unsigned int vol);
	void WriteVoltageB(unsigned int vol);

	static void SInitialize();
	static void SWriteVoltageA(unsigned int vol);
	static void SWriteVoltageB(unsigned int vol);

	//static unsigned int sm_send;

private:
	SSUbus m_ssu;

	//struct m_dac_bit_def{
	//	unsigned char dac_select : 1;
	//	unsigned char input_buffer_control : 1;
	//	unsigned char gain_select : 1;
	//	unsigned char power_down_control : 1;
	//	unsigned int dac_data : 12;
	//};

	//union m_dac_data_def{
	//	struct m_dac_bit_def bit;
	//	unsigned int word;
	//};

	////unsigned int m_data_outs;
	//union m_dac_data_def m_data_outs; //実際に送られるデータ

	//unsigned int m_send;

	//unsigned char m_dac_select;
	//unsigned char m_input_buffer_control;
	//unsigned char m_gain_select;
	//unsigned char m_power_down_control;

	static const unsigned char DAC_SELECT_B = 0x01;
	static const unsigned char DAC_SELECT_A = 0x00;

	static const unsigned char DAC_INPUT_BUFFER_CONTROL_BUFFERED = 0x01;
	static const unsigned char DAC_INPUT_BUFFER_CONTROL_UNBUFFERED =  0x00;
	
	static const unsigned char DAC_GAIN_1X = 0x01;
	static const unsigned char DAC_GAIN_2X = 0x00;

	static const unsigned char DAC_SHUTDOWN_POWER_ON = 0x01;
	static const unsigned char DAC_SHUTDOWN_POWER_OFF = 0x00;

};


#endif  //_DAC_H
