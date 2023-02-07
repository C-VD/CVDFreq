#include <math.h>
#include "CutOffFilter.h"
#pragma once
#define PI_4 3.1416
class FreqProcessor
{
public:	
	void setCutFreq(double pNc);
	void setSampleRate(double pSampleRate);
	void highPass(double* inbuf, double* outbuf, int nSamples);
	void lowPass(double* inbuf, double* outbuf, int nSamples);
	void bandPass(double* inbuf, double* outbuf, int nSamples);
	CutOffFilter highCutOffFilter;
	CutOffFilter lowCutOffFilter;
private:
	double mNc;
	double mC;
	int mSampleRate;
};
