#ifndef __FG__
#define __FG__



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
};

class ASine : public AWave{
private:

public:
	ASine(const unsigned int* stale, unsigned int nop, unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
};
class ATriangle : public AWave{

public:
	ATriangle(unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
};
class ASawtooth : public AWave{
public:
	ASawtooth(unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
};
class ANoise : public AWave{
public:
	ANoise(unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
};
class APWM : public AWave{
public:
	APWM(unsigned int freq, unsigned int phase, float gain);

	unsigned int get_val_now();
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
};
class BNoise : public BWave{
private:

public:
	unsigned int get_val_now();
};



class Functiongenerator{
private:

	static const unsigned char SLOT_SIZE_MAX = 5;
	Dac dac;
	Timer tim;
	Wave slot[SLOT_SIZE_MAX];
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

};


class LCD_Utils{};
class UI_Utils{};
class FGManeger{
private:

public:

};


#endif //__FG__
