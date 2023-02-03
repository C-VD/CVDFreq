#ifndef __CVDFREQ__
#define __CVDFREQ__

#include "IPlug_include_in_plug_hdr.h"
#include "FreqProcessor.h"


class CVDFreq : public IPlug
{
public:
  CVDFreq(IPlugInstanceInfo instanceInfo);
  ~CVDFreq();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mGain;
  FreqProcessor mFreqProcessorR;
  FreqProcessor mFreqProcessorL;
};

#endif
