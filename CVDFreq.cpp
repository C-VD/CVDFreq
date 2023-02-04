#include "CVDFreq.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kR,
  kCutFreq,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kGainX = 50,
  kGainY = 100,
  kRX = 45,
  kRY = 55,
  kCutFreqX = 120,
  kCutFreqY = 55,
  kKnobFrames = 60
};

CVDFreq::CVDFreq(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kGain)->InitDouble("Gain", 50., 0., 100.0, 0.01, "%");
  GetParam(kGain)->SetShape(2.);
  GetParam(kCutFreq)->InitDouble("Cutoff Frequency", 50., 30., 16000.0, 1.00, "Hz");
  GetParam(kCutFreq)->SetShape(2.);
  GetParam(kR)->InitDouble("R", 100., 0., 100.0, 1.00, "%");
  GetParam(kR)->SetShape(1.);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachBackground(BG_ID, BG_FN);

  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);

  //pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kRX, kRY, kR, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kCutFreqX, kCutFreqY, kCutFreq, &knob));

  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);

  mFreqProcessorL.setSampleRate(GetSampleRate());
  mFreqProcessorR.setSampleRate(GetSampleRate());
}

CVDFreq::~CVDFreq() {}

void CVDFreq::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.

  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];
  
  mFreqProcessorL.process(in1, out1, nFrames);
  mFreqProcessorR.process(in2, out2, nFrames);
  for (int s = 0; s < nFrames; ++s, ++out1, ++out2)
  {
    *out1 *= mGain;
    *out2 *= mGain;
  }

}

void CVDFreq::Reset()
{
  TRACE;
  IMutexLock lock(this);
}

void CVDFreq::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
    case kGain:
      mGain = GetParam(kGain)->Value() / 100.;
      break;

    case kCutFreq:
      mFreqProcessorL.setCutFreq(GetParam(kCutFreq)->Value());
      mFreqProcessorR.setCutFreq(GetParam(kCutFreq)->Value());
      break;
   case kR:
      break;

    default:
      break;
  }
}
