//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : UIUtils.cpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#include "UIUtils.hpp"
#include "Settings.hpp"

unsigned char GetScale(unsigned int in){
	unsigned int scl = 1;
	unsigned int tmp = in;
	while (1){
		tmp /= 10;
		if (in != 0) scl++;
		else break;
	}
	return scl;
}

UIUtils::UIUtils()
	: WAVE_TEXT_ANONE("NONE")
	, WAVE_TEXT_ASINE("SINE")
	, WAVE_TEXT_ATRIANGLE("TRIA")
	, WAVE_TEXT_ASAWTOOTH("SAWT")
	, WAVE_TEXT_APWM("PWM ")
	, WAVE_TEXT_ANOISE("NOIS")
	, WAVE_TEXT_GAIN("GAIN")
	, WAVE_TEXT_FREQ("FREQ")
	, WAVE_TEXT_POOL("POOL")
	, WAVE_TEXT_SLOT("SLOT")
	, WAVE_TEXT_SET("SET")
{
	lcd.Initialize();

}




void UIUtils::Output(UIView * ui){

	//VIEWモードで出力
	lcd.SetCursor(0, 0);

	//スロット番号の表示
	//lcd.WriteString("S");
	lcd.WriteNumber(ui->GetSlotNumber());
	lcd.WriteString(" ");

	//波名表示
	lcd.WriteString(GetTextFromID(ui->GetWave()->GetId()));

	//ゲイン表示
	lcd.SetCursor(11, 0);
	lcd.WriteString("G:");
	lcd.WriteNumber(ui->GetWave()->GetGain());

	//周波数表示
	lcd.SetCursor(0, 1);
	lcd.WriteString("F:");
	unsigned int ff = ui->GetWave()->GetFrequency();
	//WriteFrequency(ui->GetWave()->GetFrequency());
	WriteFrequency(ff);
}

void UIUtils::Output(UISet * ui){
	//設定sモードで出力
	lcd.SetCursor(0, 0);

	//スロット番号の表示
	//lcd.WriteString("S");
	lcd.WriteNumber(ui->GetSlotNumber());
	lcd.WriteString(" ");

	//波名表示
	lcd.WriteString(GetTextFromID(ui->GetWave()->GetId()));

	lcd.SetCursor(0, 1);

	switch (ui->GetMode())
	{
	case UI_MODE_GAIN:
		//ゲイン表示
		lcd.WriteString("G:");
		lcd.WriteNumber(ui->GetWave()->GetGain());
		break;
	case UI_MODE_FREQUENCY:
		//周波数表示
		lcd.WriteString("F:");
		WriteFrequency(ui->GetWave()->GetFrequency());
		break;
	case UI_MODE_INSERTION:
		break;
	case UI_MODE_UNDEFINED:
		break;
	default:
		break;
	}
}

void UIUtils::Output(UIInsertion * ui){
	//POOL表示
	lcd.SetCursor(0, 0);
	lcd.Write(0xFF);
	lcd.WriteString(" ");
	lcd.WriteString(GetTextFromID(ui->GetWaveSelected()->GetId()));
	lcd.WriteString(" ");
	lcd.SetCursor(15, 0);
	lcd.Write(0xFF);

	lcd.SetCursor(0, 1);
	lcd.WriteString("  ");
	lcd.WriteString(GetTextFromID(ui->GetWave()->GetId()));
}

const char * UIUtils::GetTextFromID(unsigned char ID){
	switch (ID)
	{
	case Settings::WAVE_ID_ANOISE:
		return WAVE_TEXT_ANOISE;
		break;
	case Settings::WAVE_ID_ANONE:
		return WAVE_TEXT_ANONE;
		break;
	case Settings::WAVE_ID_APWM:
		return WAVE_TEXT_APWM;
		break;
	case Settings::WAVE_ID_ASAWTOOTH:
		return WAVE_TEXT_ASAWTOOTH;
		break;
	case Settings::WAVE_ID_ASINE:
		return WAVE_TEXT_ASINE;
		break;
	case Settings::WAVE_ID_ATRIANGLE:
		return WAVE_TEXT_ATRIANGLE;
		break;
	default:
		return WAVE_TEXT_ANONE;
		break;
	}
}


void UIUtils::WriteFrequency(unsigned int f){
	if (f < 1000){
		lcd.WriteNumber(f); lcd.WriteString("Hz");
		return;
	}
	else if (f < 1000000){
		lcd.WriteNumber(f / 1000);
		lcd.WriteString(".");
		lcd.WriteNumber((f - ((f / 1000) * 1000)));
		lcd.WriteString("kHz");
		return;
	}
	else if (f < 1000000000){
		lcd.WriteNumber(f / 1000000); lcd.WriteString("MHz");
		return;
	}
	else{
		lcd.WriteString("UND");
		return;
	}
}

/*
	 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
	 000,000

	 */

void UIUtils::WriteFrequency2(unsigned int f, unsigned char scale){
	unsigned char scl = 0;

	lcd.SetCursor(7,1);

	if (scale > (5)){
		scl = 5;
	} else{
		scl = scale;
	}

	lcd.WriteNumber6(f);
	lcd.WriteString("Hz");
	if (scl > 2){
		//コンマの分も考慮する
		scl++;
	}
	else{
		//コンマ以右のカーソル
		;
	}
	//ディスプレイON、カーソルON、ブリンクONにする
	lcd.EnableCursor(true);
	lcd.SetCursor((15 - 2) - scl, 1);

	//if (scale > (GetScale(f) - 1)){
	//	scl = GetScale(f) - 1;
	//} else{
	//	scl = scale;
	//}
	//
	//if (f < 1000){
	//	lcd.WriteNumber(f); lcd.WriteString("Hz");
	//	lcd.SetCursor((15 - 2) - scl, 1);
	//} else{
	//	lcd.WriteNumber(f / 1000);
	//	lcd.WriteString(",");
	//	lcd.WriteNumber((f - ((f / 1000) * 1000)));
	//	lcd.WriteString("Hz");

	//	if (scl > 3){
	//		//コンマの分も考慮する
	//		scl++;
	//	} else{
	//		//コンマ以右のカーソル
	//		;
	//	}
	//	lcd.SetCursor((15 - 2) - scl, 1);
	//}

}

void UIUtils::WriteWaveNameFromID(const unsigned char ID){
	lcd.WriteString(GetTextFromID(ID));
	return;
}

void UIUtils::WriteWaveNameFromSelectedID(const unsigned char ID){
	lcd.Write('#');
	lcd.WriteString(GetTextFromID(ID));
	lcd.Write('#');
	return;
}

LCDUtils * UIUtils::GetHundleLCD(){
	return &lcd;
}

void UIUtils::WriteGain2(unsigned int gain, unsigned char scale){

}

void UIView::Set(Wave *w, unsigned char slotnum){
	m_awave = w; m_slotnum = slotnum;
}

unsigned char UIView::GetSlotNumber(){
	return m_slotnum;
}

Wave * UIView::GetWave(){
	return m_awave;
}


void UISet::Set(Wave *w, unsigned char slotnum, unsigned char ui_mode){
	m_awave = w; m_slotnum = slotnum; m_ui_mode = ui_mode;
	m_scale = 0;
}

void UISet::Set(Wave *w, unsigned char slotnum, unsigned char ui_mode, unsigned char scl){
	m_awave = w; m_slotnum = slotnum; m_ui_mode = ui_mode;
	m_scale = scl;
}

unsigned char UISet::GetSlotNumber(){
	return m_slotnum;
}

unsigned char UISet::GetMode(){
	return m_ui_mode;
}

Wave * UISet::GetWave(){
	return m_awave;
}

void UIInsertion::Set(Wave *w_selected, Wave *w){
	m_w_selected = w_selected;
	m_w = w;
}

Wave * UIInsertion::GetWave(){
	return m_w;
}

Wave * UIInsertion::GetWaveSelected(){
	return m_w_selected;
}



