#include "FreqProcessor.h"

void FreqProcessor::setSampleRate(double pSampleRate) {
	mSampleRate = pSampleRate;
}

void FreqProcessor::setCutFreq(double pCutFreq) {
	mNc = (pCutFreq / mSampleRate);
	lowCutOffFilter.setNc(mNc);
	highCutOffFilter.setNc(mNc);
	mC = (tan(PI_4 * mNc) - 1) / (tan(PI_4 * mNc) + 1);
	lowCutOffFilter.setC(mC);
	highCutOffFilter.setC(mC);
}

void FreqProcessor::lowPass(double* inbuf, double* outbuf, int nSamples) {
	for (int s = 0; s < nSamples; s++) {
		highCutOffFilter.lpass(inbuf, outbuf);
		++inbuf;
		++outbuf;
	}
}

void FreqProcessor::highPass(double* inbuf, double* outbuf, int nSamples) {
	for (int s = 0; s < nSamples; s++) {
		lowCutOffFilter.hpass(inbuf, outbuf);
		++inbuf;
		++outbuf;
	}
}
void FreqProcessor::bandPass(double* inbuf, double* outbuf, int nSamples) {
	for (int s = 0; s < nSamples; s++) {
		lowCutOffFilter.hpass(inbuf, outbuf);
		highCutOffFilter.lpass(outbuf, outbuf);
		++inbuf;
		++outbuf;
	}

}
