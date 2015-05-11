#ifndef __FG__
#define __FG__

#define SLOT_SIZE_MAX 5


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
class Wave : public Clock{
private:
  float A;
public:
  
  void set_gain(float gain);
  float get_gain();

  virtual unsigned int get_val_now();
  unsigned int Out();
  
  void Enable();
  void Disable();
  
};

class ASine : public Wave{
private:
  
public:
  ASine(const unsigned int* stale, unsigned int nop, unsigned int freq, unsigned int phase, float gain);

  unsigned int Out();
};
class ATriangle : public Wave{

public:
  ATriangle(unsigned int freq, unsigned int phase, float gain);

  unsigned int Out();
};
class ASawtooth : public Wave{
public:
  ASawtooth(unsigned int freq, unsigned int phase, float gain);

  unsigned int Out();
};
class ANoise : public Wave{
public:
  ANoise(unsigned int freq, unsigned int phase, float gain);

  unsigned int Out();
};
class APWM : public Wave{
public:
  APWM(unsigned int freq, unsigned int phase, float gain);

  unsigned int Out();
};

class DPWM{
  
};
class DNoise{
  
};

class TIMER{
  
};

class SSU{
  
};
class ADC: public SSU{
  
};

class FG : public ADC ,public TIMER{
private:
  Wave slot[SLOT_SIZE_MAX];
  unsigned int nos;
public:
  FG();
  
  volatile void Update();
  
  FG& operator+=(Wave& w);
  
}; 




#endif //__FG__ 
