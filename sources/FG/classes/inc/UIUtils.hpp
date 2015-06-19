//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : UIUtils.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_UIUTILS_H)
#define _UIUTILS_H

#include "FGManager.hpp"
#include "LCDUtils.hpp"
#include "AWave.hpp"

class UIView{
public:
	void Set(AWave *w, unsigned char slotnum);
	AWave * GetWave();
	unsigned char GetSlotNumber();
private:
	AWave *m_awave;
	unsigned char m_slotnum;
};

class UISet{
public:
	void Set(AWave *w, unsigned char slotnum, unsigned char ui_mode);
	AWave * GetWave();
	unsigned char GetSlotNumber();
	unsigned char GetMode();
private:
	AWave *m_awave;
	unsigned char m_slotnum;
	unsigned char m_ui_mode;
};

class UIInsertion{
public:
	void Set(AWave *w_selected, AWave *w);
	AWave * GetWaveSelected();
	AWave * GetWave();
private:
	AWave *m_w_selected, *m_w;
};


class UIUtils {
public:
	UIUtils();
	void Show(FGManager fgm);

	void Output(UIView * ui);
	void Output(UISet * ui);
	void Output(UIInsertion * ui);

	static const unsigned char UI_MODE_UNDEFINED = 0x00;
	static const unsigned char UI_MODE_VIEW = 0x01;
	static const unsigned char UI_MODE_FREQUENCY = 0x02;
	static const unsigned char UI_MODE_GAIN = 0x03;
	static const unsigned char UI_MODE_INSERTION = 0x04;

private:

	LCDUtils lcd;
	//8�����܂�
	const char * WAVE_TEXT_ANONE;
	const char * WAVE_TEXT_ASINE;
	const char * WAVE_TEXT_ATRIANGLE;
	const char * WAVE_TEXT_ASAWTOOTH;
	const char * WAVE_TEXT_APWM;
	const char * WAVE_TEXT_ANOISE;
	const char * WAVE_TEXT_GAIN;
	const char * WAVE_TEXT_FREQ;
	const char * WAVE_TEXT_POOL;
	const char * WAVE_TEXT_SLOT;
	const char * WAVE_TEXT_SET;

	const char * GetTextFromID(unsigned char ID);

	void WriteFrequency(unsigned int f);

};




#endif  //_UIUTILS_H
