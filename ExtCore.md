---
title: Core module
permalink: /audiostack/Core/
---

Aspic Audiostack Core module offers basic features. Here is a list:

1. Inputs
	* [HelloInput](#helloinput): basic synthetized input
	* [OpenALInput](#openalinput): standard cross-OS microphone
	* [Windows Core Audio Input](#windows-core-audio-input): low-latency, windows-only microphone capture
2. Outputs
	* [OpenALOutput](#openaloutput): standard cross-OS mono/stereo output
	* [Windows Core Audio Output](#windows-core-audio-output): low-latency, windows-only mono/stereo output
3. Effects
	* [SimpleGain (will be renamed 'Gain')](#simplegain)
	* [MultiChannelSimpleGain (will be renamed 'Splitter')](#multichannelsimplegain)
	* [MultiChannelMixer (will be renamed 'Mixer')](#multichannelmixer)
	* [Delay](#delay)
	* [R128Metering](#r128metering)
	* [MixFocus](#mixfocus)
	* [AttenuationEffect](#attenuation)
	* Under deprecation
		* [*Mixer (under deprecation, see MultiChannelMixer)*](#mixer)
		* [*StereoMixer (under deprecation, see MultiChannelMixer)*](#stereomixer)

		
		
		
		
		
		
		



## Inputs

### HelloInput

This is a simple input which automatically outputs the following generic sentence: "Aspic Audiostack says hello". 

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`out`		|1						|1 (MONO)			|


#### Construction

No arguments 

Usage : 
```cpp
context.createInput(ID,HelloInput);
```

#### Parameters

- **buffer_size (*unsigned int*)** : the length of audio buffers.

	This parameter is mapped by default to `application/buffer_size`.

	Usage with default vars and patterns: 
```cpp
context.setParameter("application/buffer_size",1024U)
```















### OpenALInput

This input uses OpenAL API to access computer microphones. If you have multiple input devices, this OpenAL wrapper will choose the default one.

On windows, you can change default microphone in the control panel, section Sound, tab recording.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`out`		|1						|1 (MONO)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createInput(ID,OpenALInput);
```

#### Parameters

##### Runtime

No runtime parameters.

##### Instanciation

- **buffer_size (*unsigned int*)** : the length of microphone audio buffers. Due to OpenAL drivers latency, values less than 2048 will create sound cracks. Recommanded value is 4096.

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",4096U)
```

	We strongly advise to set this parameter once before Audiostak play(). 

------




### Windows Core Audio Input

This input uses Windows APIs to access computer microphones. If you have multiple input devices, this wrapper will choose the default one.

On windows, you can change default microphone in the control panel, section Sound, tab recording.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`out`		|1						|1 (MONO)			|

#### Construction

- **hardware_id (*const char\**)** : the material identifier of the microphone you want to capture
	
	This parameter is optional. If left empty, Audiostack will chose default microphone.

Usage : 
```cpp
context.createInput(ID,WindowsCoreAudioInput);
// or 
context.createInput(ID,WindowsCoreAudioInput,"4d36e96c-e325-11ce-bfc1-08002be10318");
```

#### Parameters

##### Runtime

ø

##### Instanciation

- **buffer_size (*unsigned int*)** : the length of microphone audio buffers. 

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",512U)
```

	We strongly advise to set this parameter once before Audiostak play(). 

------











## Outputs

### OpenALOutput

Uses OpenAL API to output audio on speakers/headphone. Will use the default device if your computer have multiple outputs.

| I/O		| Channel count 		| Sub channel count	| |
:-|:-:|:-:|-
|`in`		|N						|1 or 2 (see construction)| |

#### Construction

- **stereo (*bool*)** : output will be stereo if value is set to TRUE or to mono if value is set to FALSE. When building a diagram, please ensure effects and outputs have compatible channel count : stereo effects may be plugged into stereo outputs.

	Usage : 
	
```cpp
context.createOutput(ID,OpenALOutput,true);		// creates a stereo output 
context.createOutput(ID,OpenALOutput,false);	// creates a mono output
```



#### Parameters

##### Runtime

- **master_gain (*float*)** : master gain of this output (amplitude).

	This parameter is mapped by default to `listener/%list_id/master_gain`.

	Usage : 
```cpp
context.setParameter("listener/2/master_gain",0.5f)
```

##### Instanciation 

- **buffer_size (*unsigned int*)** : the length of audio buffers. 

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",512U)
```

	We strongly advise to set this parameter once before Audiostak play(). 

- **buffer_count (*unsigned int*)** : the number of audio buffers in queue. Default value is 2, it means that audio is double-buffered.

	This parameter is mapped by default to `application/buffer_count`.

	Usage : 
```cpp
context.setParameter("application/buffer_count",3U)
```

#### Callbacks

- **triggered** : to be documented 

#### Android behavior

To be documented

























### Windows Core Audio Output

Uses Windows APIs to output audio on speakers/headphone. Will use the default device if your computer have multiple outputs.

| I/O		| Channel count 		| Sub channel count	| |
:-|:-:|:-:|-
|`in`		|N						|1 or 2 (see construction)| |

#### Construction

- **stereo (*bool*)** : output will be stereo if value is set to TRUE or to mono if value is set to FALSE. When building a diagram, please ensure effects and outputs have compatible channel count : stereo effects may be plugged into stereo outputs.

- **hardware_id (*const char\**)** : the material identifier of the microphone you want to capture
	
	This parameter is optional. If left empty, Audiostack will chose default microphone.

Usage : 
```cpp
context.createOutput(ID,WindowsCoreAudioOutput,false);		// creates a mono output
context.createOutput(ID,WindowsCoreAudioOutput,true);		// creates a stereo output 
context.createOutput(ID,WindowsCoreAudioOutput,true,"4d36e96c-e325-11ce-bfc1-08002be10318");
```


#### Parameters

##### Runtime

- **master_gain (*float*)** : master gain of this output (amplitude).

	This parameter is mapped by default to `listener/%list_id/master_gain`.

	Usage : 
```cpp
context.setParameter("listener/2/master_gain",0.5f)
```

##### Instanciation 

- **buffer_size (*unsigned int*)** : the length of audio buffers. 

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",512U)
```

	We strongly advise to set this parameter once before Audiostak play(). 


------
		







		
		
## Effects



### SimpleGain

May be used to apply a gain to specific audio channels. 

{% icon fa-exclamation-triangle  %} Will be renamed "Gain" 

| I/O		| Channel count 		| Sub channel count	| |
:-:|:-:|:-:|-
|`in`		|N						|1 (MONO)			| |
|`out`		|N						|1 (MONO)			| |

{% icon fa-exclamation-triangle  %} Will allow custom subchannel count in input/output, in order to become

#### Construction

No construction parameters.

Usage: 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, SimpleGain);
```

#### Parameters

##### Runtime

- **src_gain (*float, multivalued*) :** controls the gain applied to audio channels. Default value is `1.0f` for each channel. The higher the value, the loudest the sound will be. A value equal to `0.0f` mutes the signal.

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to ```source/%src_id/gain```

	Usage thanks to default vars and patterns:
	```cpp
context.setParameter("source/7/gain", 0.42f);	// set gain of input with objectId 7
	```

- **mute (*bool, multivalued*) :** if set to TRUE, mutes one audio channel. Default value is FALSE.

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.
	
	Parameter is mapped by default to ```source/%src_id/mute```
	
	Usage thanks to default vars and patterns:

	```cpp
context.setParameter("source/7/mute", true);
	```

##### Instanciation

No instanciation parameters.

------








### MultiChannelSimpleGain

This effect **splits** mono input channels into more sub channels. It is usefull to transform a mono signal in a stereo (or multichannel) output, for instance on a 2D bus before outputing to your stereo outputs.

Currenlty, also applies gain modification to channels. The gain applied to one signal is applied equally to each one of its sub channels. 

| I/O		| Channel count 		| Sub channel count	| |
:-:|:-:|:-:
|`in`		|N						|1 (MONO)			| |
|`out`		|N						|M (specified at construction) | |

#### Construction

- **nbSubChannel (*unsigned int*) :** set sub channel count of the output.

	Usage :
	```cpp
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelSimpleGain, 2U) // creates a stereo gain
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelSimpleGain, 8U) // creates a 7.1 master gain.
	```	
{% icon fa-exclamation-triangle  %} Will be renamed "Splitter"
	
#### Parameters

##### Runtime

{% icon fa-exclamation-triangle  %} Will lost gain and mute parameters (refer to [SimpleGain](#simplegain) )

- **src_gain (*float, multivalued*) :** controls the gain applied to audio channels. Default value is `1.0f` for each channel. The higher the value, the loudest the sound will be. A value equal to `0.0f` mutes the signal.

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to ```source/%src_id/gain```

	Usage thanks to default vars and patterns:
	```cpp
context.setParameter("source/7/gain", 0.42f);	// set gain of input with objectId 7
	```

- **mute (*bool, multivalued*) :** if set to TRUE, mutes one audio channel. Default value is FALSE.

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.
	
	Parameter is mapped by default to ```source/%src_id/mute```
	
	Usage thanks to default vars and patterns:
	```cpp
context.setParameter("source/7/mute", true);
	```

##### Instanciation

No instanciation parameters.

------









### MultiChannelMixer 

Mix down many channels into one channel. Mixers are usefull because they enable following effects to process fewer audio data. However, effects after a mixer cannot apply source-specific effects (like spatialization or attenuation), since sources are mixed.

It reduces the number of channels, but do not change the number of subchannels: mixing 2 stereo channels will produce 1 stereo channel.

{% icon fa-exclamation-triangle  %} Will be renamed "Mixer"

| I/O		| Channel count 		| Sub channel count	| |
:-|:-:|:-:|-
|`in`		|N						|M			| |
|`out`		|1						|M			| |

#### Construction

- **nbSubChannel (*unsigned int*) :** set sub channel count of input and output channels.

	Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelMixer, 2U) // creates a stereo mixer
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelMixer, 8U) // creates a 7.1 mixer
```
		
#### Parameters

##### Runtime 

- **volume (*float, multivalued*) :** controls amount of each input channel that goes to the output. Default value is `1.0f` and values must be between `0.0f` and `1.0f`

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/volume`

	Usage thanks to default vars and patterns:
	```cpp
context.setParameter("source/7/volume", 0.42f);
	```

##### Instanciation

No instanciation parameters.

------












### Delay

Applies delay on signal.

WORK IN PROGRESS

------








### R128Metering

Computes metering of your audio signals, using R128. Audio signal stays untouched.

| I/O		| Channel count 		| Sub channel count	| |
:-:|:-:|:-:|-
|`in`		|N						|M			| |
|`out`		|N						|M			| |

#### Construction

- **nbSubChannel (*unsigned int*) :** set sub channel count of input and output channels.

	Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, R128Metering, 2U) // creates a mono metering
context.createEffect(EFFECT_ID, BUS_ID, R128Metering, 9U) // creates a 2nd order ambisonics metering
```

#### Parameters

No runtime parameters.

No instanciation parameters.

#### Callbacks

- **peak:** this callback is called each time a peak value has been computed. It is called once per channel and subchannel. Therefore, having a 2 channels containing 1st order ambisonics will give you 8 calls.

TODO DEFAULT MAPPING

TODO USAGE

------









### MixFocus

Applies gain depending on whether a listener is looking towards a source.

| I/O		| Channel count 		| Sub channel count	| |
:-:|:-:|:-:|-
|`in`		|N						|1 (MONO)			| |
|`out`		|N						|1 (MONO)			| |

#### Construction

	No construction parameters.

	Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, MixFocus);
```

#### Parameters

##### Runtime

TODO src_position

TODO list_position

TODO list_rotation

TODO gain

TODO angle

##### Instanciation

No instanciation parameters.

------











### AttenuationEffect

{% icon fa-exclamation-triangle  %} Effect documentation under revision to match actual interface

This effects uses distance between sources and listeners to apply custom audio volume. It may be used to reproduce sound rollof over distance in real life.

Currently available attenuation profiles are linear and inverse.

Linear attenuation requires you to set a min and max distance. When distance between source and listener is below min, volume is set to 1.0f; when distance goes over max, volume is set to 0.0f.

Inverse attenuation requires a min distance and a decay coefficient. Audio volume is set to `1.0f` below min distance, and then follow a inverse law (1/distance). The decay coefficient enable a fine tuning of the strength of attenuation.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						| M 			|
|`out`		|N						| M 			|

#### Construction

- **attenuationType (*unsigned int*) :** choose between attenuation laws, use 0 for linear, use 1 for inverse.

- **nbSubChannel (*unsigned int*)** : set [subchannel](/#subchannels) count of input and output channels.

	Usage : 
	
```cpp
context.createEffect(EFFECT_ID, BUS_ID, AttenuationEffect, 0, 1) // creates linear attenuation effect for mono signals
context.createEffect(EFFECT_ID, BUS_ID, AttenuationEffect, 1, 2) // creates inverse attenuation effect for stereo signals
```
		
#### Parameters

- **src_position (*vec3, multivalued*) :** position of audio source

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/position`
	
- **listener_position (*vec3, multivalued*) :** position of audio listener

	This parameter will contain N values, with N equal to the number of buses output.

	Parameter is mapped by default to `listener/%list_id/position`
	
- **min_distance (*float*) :** available for linear and inverse attenuation. Default is `0.0f`.

- **max_distance (*float*) :** available for linear attenuation only. Default is `25.0f`.

- **sound_decay_coef (*float*) :** available for inverse attenuation only. Default is `1e-6`. Try to tune this value to makes attenuation more or less efficient.

-----


























## Deprecated effects

### Mixer 

{% icon fa-exclamation-triangle  %} Will be deprecated, see [MultiChannelMixer](#multichannelmixer) {% icon fa-exclamation-triangle  %}

Mix down many **mono** channels into one **mono** channel. Mixers are usefull because they enable following effects to process fewer audio data. However, effects after a mixer cannot apply source-specific effects (like spatialization or attenuation).

| I/O		| Channel count 		| Sub channel count	| |
:-|:-:|:-:|-
|`in`		|N						|1 (MONO)			| |
|`out`		|1						|1 (MONO)			| |

#### Construction

No arguments 

Usage : 

```cpp
context.createEffect(EFFECT_ID, BUS_ID, Mixer);
```

#### Parameters

##### Runtime 

- **volume (*float, multivalued*) :** controls amount of each input channel that goes to the output. Default value is `1.0f` and values must be between `0.0f` and `1.0f`

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/volume`

	Usage thanks to default vars and patterns:
	```cpp
context.setParameter("source/7/volume", 0.42f);
	```

##### Instanciation

ø

------

### StereoMixer 

{% icon fa-exclamation-triangle  %} Under deprecation, see MultiChannelMixer {% icon fa-exclamation-triangle  %}

Behaves like [Mixer](#mixer) but with **stereo** inputs and output.

| I/O		| Channel count 		| Sub channel count	| |
-|:-:|-:|-
|`in`		|N						|2 (STEREO)			| |
|`out`		|1						|2 (STEREO)			| |

#### Construction

No arguments 

Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, StereoMixer);
```

#### Parameters

Same as [Mixer](#mixer).

------






























## Code samples

For more code samples, see [Core samples](../ExtCoreSamples)

### C++ API Samples

#### OpenAL simple application

This sample connects microphone to computer output using OpenAL drivers.

Please note this sample doesn't handle errors, please go direclty to the next sample for error handling.

```cpp
{% include_relative samples/Core_1_OpenAL.cpp %}
```

##### Error handling

The previous sample doesn't catch any error, here is the sample application with error handling.

```cpp
{% include_relative samples/Core_1_OpenAL_Error.cpp %}
```

For more code samples, see [Core samples](../ExtCoreSamples)
	