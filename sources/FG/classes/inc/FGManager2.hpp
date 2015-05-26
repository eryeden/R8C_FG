//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  Project : Function Generator
//  @ File Name : FGManager2.hpp
//  @ Date : 2015/05/25
//  @ Author : Kazuki Kikuchi
//
//


#if !defined(_FGMANAGER2_H)
#define _FGMANAGER2_H

#include "Wave.hpp"

class FGManager2 {
public:
	void button_down_mode();
	void button_down_up();
	void button_down_down();
	void button_down_select();
private:
	static const unsigned char POOL_SIZE_GENERATOR;
	unsigned char mode;
	unsigned char pool_output;
	Wave *pool_generator;
	unsigned char output_index_selected;
	unsigned char generator_index_selected;
	void move_generator(unsigned char idx);
	void clear_output(unsigned char idx);
	void clear_all_output();
	void set_output_gain(unsigned char idx, float gain);
	void set_output_frequency(unsigned char idx, unsigned int freq);
	void set_output_phase(unsigned char idx, float phase);
};

#endif  //_FGMANAGER2_H
