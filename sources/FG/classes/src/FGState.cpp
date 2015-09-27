//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : FGState.hpp
//  @ Date : 2015/09/24
//  @ Author : 
//
//

#include "FGState.hpp"
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

FGState::FGState() {
	;
}

void FGState::SetIndexSelected(unsigned char idx) {
	idx_selected = idx;
}

void FGState::SetFunctionGenerator(FunctionGenerator * _fg) {
	fg = _fg;
}

void FGState::SetUIUtils(UIUtils *uiu) {
	ui_utils = uiu;
}
//###########SLOTS################################
StateSlots::StateSlots() : FGState() {
	idx_show1 = 0;
	idx_show2 = 1;
	idx_selected = 0;
}
void StateSlots::Initialize() {
	no_slots_max = fg->GetAWaveSlotSize();
}
void StateSlots::Up() {
	if (idx_selected == idx_show1) {
		if (idx_show1 == 0) {
			idx_show1 = 0;
		}
		else {
			idx_show1--;
		}
		if (idx_show2 == 1) {
			idx_show2 = 1;
		}
		else {
			idx_show2--;
		}
		idx_selected = idx_show1;
	}
	else {
		idx_selected = idx_show1;
	}
	Output();
}
void StateSlots::Down() {
	if (idx_selected == idx_show2) {
		if (idx_show1 == (no_slots_max - 2)) {
			idx_show1 = (no_slots_max - 2);
		}
		else {
			idx_show1++;
		}
		if (idx_show2 == (no_slots_max - 1)) {
			idx_show2 = (no_slots_max - 1);
		}
		else {
			idx_show2++;
		}
		idx_selected = idx_show2;
	}
	else {
		idx_selected = idx_show2;
	}

	Output();
}
void StateSlots::Select() {
	;
}

void StateSlots::Mode() {
	//ui_utils->GetHundleLCD()->Clear();
	Output();
}

unsigned char StateSlots::GetIndexSelected() {
	return idx_selected;
}

unsigned char StateSlots::GetIndexShow1() {
	return idx_show1;
}
unsigned char StateSlots::GetIndexShow2() {
	return idx_show2;
}

void StateSlots::Output() {

	ui_utils->GetHundleLCD()->Clear();

	if (idx_selected == idx_show1) {
		ui_utils->GetHundleLCD()->SetCursor(0, 0);
		ui_utils->WriteWaveNameFromSelectedID(fg->GetIdFromSlotMasterIndex(idx_show1));

		ui_utils->GetHundleLCD()->SetCursor(0, 1);
		ui_utils->WriteWaveNameFromID(fg->GetIdFromSlotMasterIndex(idx_show2));

	}
	else {
		ui_utils->GetHundleLCD()->SetCursor(0, 0);
		ui_utils->WriteWaveNameFromID(fg->GetIdFromSlotMasterIndex(idx_show1));

		ui_utils->GetHundleLCD()->SetCursor(0, 1);
		ui_utils->WriteWaveNameFromSelectedID(fg->GetIdFromSlotMasterIndex(idx_show2));
	}
}
//###########SLOTS################################

//###########FREQUENCY################################
StateFrequency::StateFrequency()
	:FGState() 
{
	scale = 0;
}

void StateFrequency::Up() {
	//選択されている桁の値を一つ増やす桁上がりも
	long f = (long)fg->GetWaveFromSlotMasterIndex(idx_selected)->GetFrequency();
	unsigned int pm = 1;
	for (int i = 0; i < scale; i++) {
		pm *= 10;
	}

	f += pm;
	if (f <= 30000) {
	   fg->GetWaveFromSlotMasterIndex(idx_selected)->SetFrequency((unsigned int)f); 
	   Output();
	}
	
	
}
void StateFrequency::Down() {
	//選択されている桁の値を一つ減らす桁下がりも許可アンダーフローに注意
	//freq = fg->GetWaveFromSlotMasterIndex(idx_selected)->GetFrequency();
	long f = (long)fg->GetWaveFromSlotMasterIndex(idx_selected)->GetFrequency();
	unsigned int pm = 1;
	for (int i = 0; i < scale; i++) {
		pm *= 10;
	}

	f -= pm;
	if (f >= 0) {
		  fg->GetWaveFromSlotMasterIndex(idx_selected)->SetFrequency((unsigned int)f);
		  Output();
	}
	
}
void StateFrequency::Select() {
	//選択されている桁を一つ右にずらす。一番右だったら一番左にずらす
	if (scale == 0) {
		scale = 5;
	}
	scale--;

	Output();
}
void StateFrequency::Mode() {
	Output();
}

void StateFrequency::Output() {	   
	unsigned int f = fg->GetWaveFromSlotMasterIndex(idx_selected)->GetFrequency();
	ui_utils->GetHundleLCD()->Clear();
	ui_utils->GetHundleLCD()->WriteLineUp("F:");
	ui_utils->WriteWaveNameFromID(fg->GetIdFromSlotMasterIndex(idx_selected));
	ui_utils->WriteFrequency2(f, scale);
}

//###########FREQUENCY################################

//###########PHASE################################
void StatePhase::Up() {
	//選択されている桁の値を一つ増やす桁上がりも許可

}
void StatePhase::Down() {
	//選択されている桁の値を一つ減らす桁下がりも許可アンダーフローに注意
}
void StatePhase::Select() {
	//選択されている桁を一つ右にずらす。一番右だったら一番左にずらす
}
void StatePhase::Mode() {
	Output();
}

void StatePhase::Output() {
	ui_utils->GetHundleLCD()->Clear();
	ui_utils->GetHundleLCD()->WriteLineUp("P:");
	ui_utils->WriteWaveNameFromID(fg->GetIdFromSlotMasterIndex(idx_selected));
}

//###########PHASE################################

//###########GAIN################################
StateGain::StateGain()
	:FGState()
{
	scale = 0;
}
void StateGain::Up() {
	//選択されている桁の値を一つ増やす桁上がりも
	int g = gain; 
	int pm = 1;
	for (int i = 0; i < scale; i++) {
		pm *= 10;
	}

	g += pm;
	if (g <= 100) {
		fg->GetWaveFromSlotMasterIndex(idx_selected)->SetGain((unsigned int)g);
		gain = g;
		Output();
	}


}
void StateGain::Down() {
	int g = gain;
	int pm = 1;
	for (int i = 0; i < scale; i++) {
		pm *= 10;
	}

	g -= pm;
	if (g >= 0) {
		fg->GetWaveFromSlotMasterIndex(idx_selected)->SetGain((unsigned int)g);
		gain = g;
		Output();
	}

}
void StateGain::Select() {
	//選択されている桁を一つ右にずらす。一番右だったら一番左にずらす
	if (scale == 0) {
		scale = 2;
	}
	scale--;

	Output();
}
void StateGain::Mode() {
	gain = (int)fg->GetWaveFromSlotMasterIndex(idx_selected)->GetGain();
	Output();
}

void StateGain::Output() {
	unsigned int g = (unsigned int)gain;
	ui_utils->GetHundleLCD()->Clear();
	ui_utils->GetHundleLCD()->WriteLineUp("G:");
	ui_utils->WriteWaveNameFromID(fg->GetIdFromSlotMasterIndex(idx_selected)); 
	ui_utils->WriteFrequency2(g, scale);
}

//###########GAIN################################

//###########DUTYRATIO################################
void StateDutyRatio::Up() {

}
void StateDutyRatio::Down() {

}
void StateDutyRatio::Select() {

}
void StateDutyRatio::Mode() {
	Output();
}

void StateDutyRatio::Output() {
	ui_utils->GetHundleLCD()->Clear();
	ui_utils->GetHundleLCD()->WriteLineUp("DR:");
	ui_utils->WriteWaveNameFromID(fg->GetIdFromSlotMasterIndex(idx_selected));
}

//###########DUTYRATIO################################

//###########INSERTION################################
StateInsertion::StateInsertion()
	:FGState()
{
	iidx_show1 = 0;
	iidx_show2 = 1;
	idx_insert = 0;
}

void StateInsertion::Initialize() {
	no_slots_max = Settings::FG_MAX_POOL;
}

void StateInsertion::Up() {
	if (idx_insert == iidx_show1) {
		if (iidx_show1 == 0) {
			iidx_show1 = 0;
		}
		else {
			iidx_show1--;
		}
		if (iidx_show2 == 1) {
			iidx_show2 = 1;
		}
		else {
			iidx_show2--;
		}
		idx_insert = iidx_show1;
	}
	else {
		idx_insert = iidx_show1;
	}
	Output();
}
void StateInsertion::Down() {
	if (idx_insert == iidx_show2) {
		if (iidx_show1 == (no_slots_max - 2)) {
			iidx_show1 = (no_slots_max - 2);
		}
		else {
			iidx_show1++;
		}
		if (iidx_show2 == (no_slots_max - 1)) {
			iidx_show2 = (no_slots_max - 1);
		}
		else {
			iidx_show2++;
		}
		idx_insert = iidx_show2;
	}
	else {
		idx_insert = iidx_show2;
	}
	Output();
}
void StateInsertion::Select() {
	//Insert
	fg->InsertWaveFromPoolToSlotMasterIndex(idx_selected, idx_insert);
}
void StateInsertion::Mode() {
	Output();
}

void StateInsertion::Output() {
	ui_utils->GetHundleLCD()->Clear();
					  
	if (idx_insert == iidx_show1) {
		ui_utils->GetHundleLCD()->SetCursor(0, 0);
		ui_utils->GetHundleLCD()->Write('<');
		ui_utils->WriteWaveNameFromSelectedID(fg->GetIdFromPoolMasterIndex(iidx_show1));

		ui_utils->GetHundleLCD()->SetCursor(0, 1);
		ui_utils->GetHundleLCD()->Write('<');
		ui_utils->WriteWaveNameFromID(fg->GetIdFromPoolMasterIndex(iidx_show2));
	}
	else {
		ui_utils->GetHundleLCD()->SetCursor(0, 0);
		ui_utils->GetHundleLCD()->Write('<');
		ui_utils->WriteWaveNameFromID(fg->GetIdFromPoolMasterIndex(iidx_show1));

		ui_utils->GetHundleLCD()->SetCursor(0, 1);
		ui_utils->GetHundleLCD()->Write('<');
		ui_utils->WriteWaveNameFromSelectedID(fg->GetIdFromPoolMasterIndex(iidx_show2));
	}
}

//###########INSERTION################################

unsigned char StateSlots::GetID() {
	return ID_STATE_SLOTS;
}

unsigned char StateFrequency::GetID() {
	return ID_STATE_FREQ;
}

unsigned char StatePhase::GetID() {
	return ID_STATE_PHASE;
}

unsigned char StateGain::GetID() {
	return ID_STATE_GAIN;
}

unsigned char StateDutyRatio::GetID() {
	return ID_STATE_DUTYRATIO;
}

unsigned char StateInsertion::GetID() {
	return ID_STATE_INSERTION;
}





