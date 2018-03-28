#include "AspicAudiostackPluginAPI.h"

using namespace aspic::audiostack;

// This is a blueprint, the audio processing method mutes output
class HOA3ToBinauralEffect : public AudiostackEffect{
public:
	HOA3ToBinauralEffect()
	{

	}

	// Implement your hoa3 to binaural decoding in this method
	virtual void processAudio(const float** _in, float** _out, int _bufferLength, float _sampleRate){
		// Debug received param
		std::cout<<"rot : "<<headRot.x<<", "<<headRot.y<<", "<<headRot.z<<std::endl;
		
		// Mute output
		for(int i =0; i<_bufferLength;++i){
			_out[0][i] = 0.0f;
			_out[1][i] = 0.0f;
		}
	}

	// Ask for 16 inputs (Hoa3) and 2 outputs (binaural)
	virtual void getSubchannelLayout(int &_inCount, int &_outCount) const{
		_inCount = 16;
		_outCount = 2;
	}
protected:
	// You want -at least- listener rotation. You could also ask for more parameters, dependeing on your algorithms
	virtual void declareParameters(){
		registerListenerParam("rotation",headRot);
	}
private:
	Vector3 headRot;
};

// Create a plugin that contains HOA3ToBinauralEffect. You could add more effects in this plugin.
class AmbisonicsSkeletonPlugin : public AudiostackPlugin{
public:
	AmbisonicsSkeletonPlugin(){
		registerEffect<HOA3ToBinauralEffect>(0);
	}
};

AUDIOSTACK_PLUGIN(AmbisonicsSkeletonPlugin)
