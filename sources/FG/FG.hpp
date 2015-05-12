#ifndef __FG__
#define __FG__

#define SLOT_SIZE_MAX 5

class TIMER{
private:

public:
  void set_frequency(unsigned int fin);
  void Enable();
  void Disable();
};



class SSU{

public:
  void write_byte(unsigned char data);
  void write(unsigned char * data, unsigned char bytes);
};

class ADC{
private:
  SSU ssu;
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
  float A;
  Clock clk;
public:
  
  void set_gain(float gain);
  float get_gain();
  
  void set_frequency(unsigned int fin);
  unsigned int get_frequency();
  
  void set_phase(float phain);
  float set_phase();

  virtual unsigned int get_val_now();
  unsigned int Out();
  
  void Enable();
  void Disable();
  
  +virtual unsigned char get_id();
  
};


class ANone : public Wave{

public:
  ANone(unsigned int freq, unsigned int phase, float gain);

  unsigned int get_val_now();
};

class ASine : public Wave{
private:
  
public:
  ASine(const unsigned int* stale, unsigned int nop, unsigned int freq, unsigned int phase, float gain);

  unsigned int get_val_now();
};
class ATriangle : public Wave{

public:
  ATriangle(unsigned int freq, unsigned int phase, float gain);

  unsigned int get_val_now();
};
class ASawtooth : public Wave{
public:
  ASawtooth(unsigned int freq, unsigned int phase, float gain);

  unsigned int get_val_now();
};
class ANoise : public Wave{
public:
  ANoise(unsigned int freq, unsigned int phase, float gain);

  unsigned int get_val_now();
};
class APWM : public Wave{
public:
  APWM(unsigned int freq, unsigned int phase, float gain);

  unsigned int get_val_now();
};


class BWave{
  
public:
  void set_frequency(unsigned int fin);
  void set_duty(unsigned int duty);
  virtual unsigned int Out();

};

class BPWM : public BWave{
private:
  //TIMER tim;
public:
  unsigned int Out();
};
class BNoise : public BWave{
private:
  //TIMER tim;
public:
  unsigned int Out();
};

class FG{
private:
  ADC adc;
  TIMER tim;
  Wave slot[SLOT_SIZE_MAX];
  BWave *bslot;
  unsigned int nos;
  void AUpdate();
  void BUpdate(); 
public:
  FG();
  void clear();
  volatile void Update();
  
  FG& operator+=(Wave& w);
  
  void insertwave(unsigned char idx, Wave& w);
  void insertwave(unsigned char idx, BWave& w);
  void deletewave(unsigned char idx);
  
}; 




#endif //__FG__ 
