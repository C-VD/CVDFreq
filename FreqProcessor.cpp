#include "FreqProcessor.h"

void FreqProcessor::setSampleRate(double pSampleRate) {
	mSampleRate = pSampleRate;
}

void FreqProcessor::setCutFreq(double pCutFreq) {
	/* Converting frequancy to relative frequancy */
	double nc = (pCutFreq / mSampleRate);
	/* Setting the all-pass filter coefficiennt */
	double c = (tan(PI_4 * nc) - 1) / (tan(PI_4 * nc) + 1);
	lowCutOffFilter.setC(c);
	highCutOffFilter.setC(c);
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
