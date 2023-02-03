#include "FreqProcessor.h"

void FreqProcessor::setSampleRate(double pSampleRate) {
	mSampleRate = pSampleRate;
}

void FreqProcessor::setCutFreq(double pCutFreq) {
	mNc = (pCutFreq / mSampleRate);
	mC = (tan(PI_4 * mNc) - 1) / (tan(PI_4 * mNc) + 1);
}

void FreqProcessor::process(double* inbuf, double* outbuf, int pNumSamples) {
	for (int s = 0; s < pNumSamples; s++, inbuf++, outbuf++) {
		*outbuf = *inbuf - apf(*inbuf);
	}
}
double FreqProcessor::apf(double in){
 	zStack[0] = in * mC + zStack[1] + zStack[2] * -mC;
	zStack[2] = zStack[0];
	zStack[1] = in;
	return zStack[0];
  }