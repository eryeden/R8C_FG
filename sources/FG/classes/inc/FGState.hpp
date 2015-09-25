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


#if !defined(_FGSTATE_H)
#define _FGSTATE_H

#include "FunctionGenerator.hpp"
#include "UIUtils.hpp"

static const unsigned char ID_STATE_SLOTS = 0x01;
static const unsigned char ID_STATE_FREQ = 0x02;
static const unsigned char ID_STATE_PHASE = 0x03;
static const unsigned char ID_STATE_GAIN = 0x04;
static const unsigned char ID_STATE_DUTYRATIO = 0x05;
static const unsigned char ID_STATE_INSERTION = 0x06;


class FGState {
public:
	FGState();
	virtual void Up() = 0;
	virtual void Down() = 0;
	virtual void Select() = 0;
	virtual void Mode() = 0;
	virtual unsigned char GetID() = 0;
	void SetIndexSelected(unsigned char idx);
	void SetFunctionGenerator(FunctionGenerator * fg);
	void SetUIUtils(UIUtils * uiu);
private:
protected:
	unsigned char idx_selected;
	FunctionGenerator* fg;
	UIUtils * ui_utils;
};

class StateSlots : public FGState{
public:
	StateSlots();

	void Up();
	void Down();
	void Select();
	void Mode();

	unsigned char GetIndexShow1();
	unsigned char GetIndexShow2();
	unsigned char GetIndexSelected();

	void Initialize();


	unsigned char GetID();

private:

	unsigned char idx_show1;
	unsigned char idx_show2;
	unsigned char no_slots_max;

	void Output();

};

class StateFrequency : public FGState{
public:
	StateFrequency() :FGState(){;}
	void Up();
	void Down();
	void Select();
	void Mode();

	unsigned char GetID();

private:

};

class StatePhase : public FGState{
public:
	StatePhase() : FGState(){;}
	void Up();
	void Down();
	void Select();
	void Mode();

	unsigned char GetID();

private:


};

class StateGain : public FGState{
public:
	StateGain() : FGState(){;}
	void Up();
	void Down();
	void Select();
	void Mode();

	unsigned char GetID();

private:


};

class StateDutyRatio : public FGState{
public:
	StateDutyRatio() : FGState(){;}
	void Up();
	void Down();
	void Select();
	void Mode();

	unsigned char GetID();

private:


};

class StateInsertion : public FGState{
public:
	StateInsertion() : FGState(){;}
	void Up();
	void Down();
	void Select();
	void Mode();

	unsigned char GetID();

private:

	unsigned char idx_inserion_show_1;
	unsigned char idx_inserion_show_2;

};

#endif  //_FGSTATE_H
