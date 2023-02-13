#include "CVDFreq.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kMode,
  kCutFreq,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kModeX = 60,
  kModeY = 50,
  kCutFreqX = 245,
  kCutFreqY = 50,
  kKnobFrames = 60
};

CVDFreq::CVDFreq(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mCutFreq(0.25)
{
  TRACE;

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kCutFreq)->InitDouble("Cutoff Frequency", 50., 30., 16000.0, 1.00, "Hz");
  GetParam(kCutFreq)->SetShape(2.);
  GetParam(kMode)->InitDouble("Mode", 2., 1., 3.0, 1.00, "");
  GetParam(kMode)->SetShape(1.);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachBackground(BG_ID, BG_FN);

  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);

  //pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kModeX, kModeY, kMode, &knob));
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
  
  mFreqProcessorL.bandPass(in1, out1, nFrames);
  mFreqProcessorR.bandPass(in2, out2, nFrames);
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
    case kCutFreq:
      mFreqProcessorL.setCutFreq(GetParam(kCutFreq)->Value());
      mFreqProcessorR.setCutFreq(GetParam(kCutFreq)->Value());
      break;
    case kMode:
        break;
    default:
      break;
  }
}
