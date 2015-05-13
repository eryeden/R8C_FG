#ifndef __FG__
#define __FG__

class Settings{
private:
public:
	static const unsigned char SLOT_SIZE_MAX = 5;

	static const unsigned char WAVE_ID_ANONE = 0x01;
	static const unsigned char WAVE_ID_ASINE = 0x02;
	static const unsigned char WAVE_ID_ATRIANGLE = 0x03;
	static const unsigned char WAVE_ID_ASAWTOOTH = 0x04;
	static const unsigned char WAVE_ID_ANONE = 0x05;
	static const unsigned char WAVE_ID_ANONE = 0x06;


};


class Timer{
private:

public:
	void set_frequency(unsigned int fin);
	void Enable();
	void Disable();
};



class SSUbus{

public:
	void write_byte(unsigned char data);
	void write(unsigned char * data, unsigned char bytes);
};

class Dac{
private:
	SSUbus ssu;
public:
	void write(unsigned int vol);
};

class Clock{
private:
	unsigned int nop;
	float dt;
	float pinv;
	unsigned int f;
	unsigned int k;
	float pha;

public:
	void set_freq(unsigned int fin);
	void set_dt(float dtin);
	void set_nop(unsigned int nopin);
	void set_phase(unsigned int phain);

	unsigned int update();

};

class Wave{
private:


public:
	void set_frequency(unsigned int fin);
	unsigned int get_frequency();

	virtual unsigned int get_val_now();
	unsigned int Out();

	void Enable();
	void Disable();

	virtual unsigned char get_id();

};

class AWave : public Wave{
private:
	float m_A;
protected:
	Clock m_clk;
public:

	void set_frequency(unsigned int fin);
	unsigned int get_frequency();

	void set_gain(float gain);
	float get_gain();

	void set_phase(float phain);
	float set_phase();
};

class ANone : public AWave{

public:
	unsigned int get_val_now();
	unsigned char get_id();
};

class ASine : public AWave{
private:

public:
	ASine(const unsigned int* stale, unsigned int nop, unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
	unsigned char get_id();
};
class ATriangle : public AWave{

public:
	ATriangle(unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
	unsigned char get_id();
};
class ASawtooth : public AWave{
public:
	ASawtooth(unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
	unsigned char get_id();
};
class ANoise : public AWave{
public:
	ANoise(unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
	unsigned char get_id();
};
class APWM : public AWave{
public:
	APWM(unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
	unsigned char get_id();
};


class BWave : public Wave{
public:

public:
	void set_frequency(unsigned int fin);
	void set_duty(unsigned int duty);
};

class BPWM : public BWave{
private:

public:
	unsigned int get_val_now();
	unsigned char get_id();
};
class BNoise : public BWave{
private:

public:
	unsigned int get_val_now();
	unsigned char get_id();
};



class Functiongenerator{
private:
	static const unsigned char SLOT_SIZE_MAX = 5;


	Dac dac;
	Timer tim;
	Wave slot[Settings::SLOT_SIZE_MAX];
	BWave *bslot;
	void AUpdate();
	void BUpdate();



public:
	Functiongenerator(); //ここですべてのスロットにANone, BNoneを入れておく。
	
	
	void clear();
	void Update();

	void insertwave(unsigned char idx, AWave& w);
	void insertwave(unsigned char idx, BWave& w);
	void deletewave(unsigned char idx);

	const unsigned char get_id_index(unsigned char idx);

	const unsigned char get_slotsize();

};


class LCDUtils{
private:


public:
	void initialize();
	void write(unsigned char in);

	void clear();
};
class UIUtils{
private:

public:
	void show(FGManeger * fgm);

};
class FGManeger{
private:

	static const unsigned char POOL_SIZE_GENERATOR = 5;
	unsigned char mode;
	unsigned char pool_output[Settings::SLOT_SIZE_MAX];
	Wave * pool_generator[POOL_SIZE_GENERATOR];

	unsigned char output_index_selected;
	unsigned char generator_index_selected;

	void move_generator(unsigned char idx);
	void clear_output(unsigned char idx);
	void clear_all_output();
	void set_output_gain(unsigned char idx, float gain);
	void set_output_frequency(unsigned char idx, unsigned int freq);
	void set_output_phase(unsigned char idx, float phase);

public:

	void button_down_mode();
	void button_down_up();
	void button_down_down();
	void button_down_select();

	
};


#endif //__FG__
