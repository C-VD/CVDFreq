#include <math.h>
#include "CutOffFilter.h"
#pragma once
#define PI_4 3.1416
class FreqProcessor
{
public:	
	void setCutFreq(double pCutFreq);
	void setSampleRate(double pSampleRate);

	/* Filters */
	void highPass(double* inbuf, double* outbuf, int nSamples);
	void lowPass(double* inbuf, double* outbuf, int nSamples);
	void bandPass(double* inbuf, double* outbuf, int nSamples);
	CutOffFilter highCutOffFilter;
	CutOffFilter lowCutOffFilter;
private:
	int mSampleRate;
};
