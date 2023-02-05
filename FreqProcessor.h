#include <math.h>
#pragma once
#define PI_4 3.1416
class FreqProcessor
{
public:	
	void highPass(double* inbuf, double* outbuf, int pNumSamples);
	void lowPass(double* inbuf, double* outbuf, int pNumSamples);
	void setCutFreq(double pNc);
	void setSampleRate(double pSampleRate);
private:
	double zStack[3] { 0, 0, 0 };
	double mNc;
	int mSampleRate;
	double mC;
	double apf(double in);
};

