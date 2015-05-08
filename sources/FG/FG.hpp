#ifndef __FG__
#define __FG__


class FG : public ADC{
  
  
  
  
}; 

class ASine : public Wave{};
class ATriangle : public Wave{};
class ASawtooth : public Wave{};
class ANoise : public Wave{};
class APWM : public Wave{};

class DPWM{};
class DNoise{};

class Wave : public Clock{};

class Clock{};

class ADC: public SSU{};
class SSU{};


#endif //__FG__ 
