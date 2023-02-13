#pragma once
class CutOffFilter
{
public:
	/* Setting the all-pass filter coefficients */
	inline void setC(double pC) { mC = pC; }

	/* Basic cut-off filters */
	void hpass(double *in, double *out);
	void lpass(double *in, double *out);
private:
	double mC;
	/* All-pass filter function */
	double apf(double in);
	double zStack[3]{ 0, 0, 0 };
};
