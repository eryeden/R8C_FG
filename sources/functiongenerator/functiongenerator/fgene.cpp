/***********************************************************************/
/*                                                                     */
/*  FILE        :functiongenerator.cpp                                 */
/*  DATE        :Fri, May 08, 2015                                     */
/*  DESCRIPTION :main program file.                                    */
/*  CPU GROUP   :29                                                    */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.19).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/***********************************************************************/

#include "sfr_r829.h"
#include "LCDUtils.hpp"
#include "Dac.hpp"
#include "ClockSettings.hpp"
#include "SSUbus.hpp"
#include "Timer.hpp"
#include "ASawtooth.hpp"
#include "ASine.hpp"
#include "ATriangle.hpp"
#include "APWM.hpp"
#include "ANoise.hpp"
#include "FunctionGenerator.hpp"

//#include "Clock.hpp"

void main(void);

//class INTRtest : public INTRbase{
//public:
//	unsigned int j;
//	Dac dac;
//	INTRtest(){
//		j = 0;
//	}
//	void intr1(){
//		p1_0 = !p1_0;
//		j = (j > (0x0FFF - 1)) ? 0 : j + 100;
//		dac.WriteVoltageA(j);
//	}
//	void op(){
//		intr1();
//	}
//};

//class INTRsawave : public ASawtooth, public INTRbase{
//public:
//	INTRsawave(unsigned int freq, unsigned int phase, float gain)
//		: ASawtooth(freq, phase, gain){};
//	unsigned int j;
//	Dac dac;
//	void op(){
//		//j = Out();
//		j = GetValueNow();
//		dac.WriteVoltageA(j);
//	}
//};
//
//class INTRsinewave : public ASine, public INTRbase{
//public:
//	INTRsinewave(unsigned int freq, unsigned int phase, float gain)
//		: ASine(freq, phase, gain){};
//	unsigned int j;
//	Dac dac;
//	void op(){
//		j = Out();
//		//j = GetValueNow();
//		dac.WriteVoltageA(j);
//	}
//};
//
//class INTRtriwave : public ATriangle, public INTRbase{
//public:
//	INTRtriwave(unsigned int freq, unsigned int phase, float gain)
//		: ATriangle(freq, phase, gain){};
//	unsigned int j;
//	Dac dac;
//	void op(){
//		//j = Out();
//		j = GetValueNow();
//		dac.WriteVoltageA(j);
//	}
//};
//
//class INTRpwmwave : public APWM, public INTRbase{
//public:
//	INTRpwmwave(unsigned int freq, unsigned int phase, float gain)
//		: APWM(freq, phase, gain){};
//	unsigned int j;
//	Dac dac;
//	void op(){
//		//j = Out();
//		j = GetValueNow();
//		dac.WriteVoltageA(j);
//	}
//};
//
//class INTRnoisewave : public ANoise, public INTRbase{
//public:
//	INTRnoisewave(unsigned int freq, unsigned int phase, float gain)
//		: ANoise(freq, phase, gain){};
//	unsigned int j;
//	Dac dac;
//	void op(){
//		j = Out();
//		//j = GetValueNow();
//		dac.WriteVoltageA(j);
//	}
//};

//class INTRfg : public FunctionGenerator, public INTRbase{
//public:
//	INTRfg(): FunctionGenerator(){};
//
//	void op(){
//		Update();
//		//p1_0 = !p1_0;
//	}
//};


void main(void)
{
	
	ClockSettings clkstg;
	clkstg.Initialize();

	//static Dac dac;
	//Dac::SInitialize();
	//Dac dac;

	//INTRtest intr;


	//pd1_1 = 1;
	//p1drr1 = 1;
	//p1_1 = 0;

	//pd1_0 = 1;
	//p1_0 = 0;

	LCDUtils lcd;
	lcd.Initialize();

	lcd.Clear();

	lcd.WriteLineUp("KIKUTI1111111111");
	lcd.WriteLineDown("KIKUTI2222");

	//lcd.Test();

	//Timer tim;
	//tim.SetDt(300);

	//INTRsawave intsawave(200, 0, 1);
	//intsawave.Enable();

	//INTRsinewave swave(100, 0, 50);
	//swave.Enable();

	//INTRtriwave trwave(100, 0, 1);
	//trwave.Enable();

	//INTRpwmwave pwmwave(100, 0, 1);
	//pwmwave.SetDuty(0.3);
	//pwmwave.Enable();

	//INTRnoisewave nwave(100, 0, 10);
	//nwave.Enable();


	//ASawtooth m_asawtooth(100, 0, 10);
	//ASine m_asine(100, 0, 10);



	//static INTRfg fg;

	//tim.SetClassInterrupter(&swave);
	//tim.SetClassInterrupter(&intr);
	//tim.SetClassInterrupter(&fg);
	//tim.Enable();

	//fg.InsertWaveFromPoolToSlotMasterIndex(0, 2);
	//fg.InsertWaveFromPoolToSlotMasterIndex(1, 5);



	//Clock clk;
	//clk.Set(500, 100, 0);
	unsigned char _j = 0;

	char tmpp[16];
	

	while(1){
		for(unsigned long i = 0; i < 100000; ++i);
			//p1_1 = !p1_1;
		for (int i = 0; i < 16; ++i){
			tmpp[i] = _j;
		}
		_j++;
		
		lcd.WriteLineDown(tmpp);
		//	clk.Update();
		//	fg.op();
	}
	
}
