---
title: VBAP multispeaker spatialization
permalink: /audiostack/VBAP/
---

VBAP extension provides effects for spatialization over multiple speaker. The effects of this module will apply the appropriate gain on all speakers to perceive sound from the correct direction. This extension also handles delay and frequency corrections to ensure a smooth rendering.

> **Note :** To address multiple harware outputs see [Asio](../ASIO) or [Jack](../Jack).

1. Effects
	-	[Multi Channel Spatialization](#multi-channel-spatialization)
2. Helpers
	- [Calibration](#calibration)
3. [Code samples](#code-samples)

## Effects

### Multi Channel Spatialization

Provides VBAP-based spatialization for rendering over speakers. 

Each input channel is spatialized independently (no mixing), which enables you to add more "per-channel" effects after this spatialization.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 (MONO)				|
|`out`		|N						| M (nb speakers)			|


#### Construction

- **nbSubChannel (*unsigned int*) :** count of output subchannels.
	
	Warning: nbSubChannel must equals the installation speaker count

- **defaultSpeakerPositions (*float*)** : array of default speaker positions. This float[] must have a length equal to 3x nbSubChannel

Usage : 
```cpp
float[] speakerPos{-1,0,1, 1,0,1, 1,0,-1, -1,0,-1};
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelSpatialization, 4, speakerPos);
```

Example for a 3 speakers positions array :

|0|1|2|3|4|5|6|7|8|
|-|-|-|-|-|-|-|-|-|
| S1.x | S1.y |S1.z|S2.x|S2.y|S2.z|S3.x|S3.y|S3.z|

> **Note :** coordinates in Aspic Audiostack are specified using right-hand axes (X right, Y up, Z backward).

#### Parameters

- **src_position (*vec3, multivalued*) :** position of audio source

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/position`

	Usage with default vars and patterns:
	``` cpp
float sourcePos[] = {1.0, 2.0, 3.0};
context.setParameter("source/9/position", sourcePos);
	```

- **listener_position (*vec3, multivalued*) :** position of audio listener

	This parameter will contain N values, with N equal to the number of listeners.

	Parameter is mapped by default to `listener/%list_id/position`
	
	Usage with default vars and patterns:
	``` cpp
float playerPos[] = {1.0, 2.0, 3.0};
context.setParameter("listener/1/position", playerPos);
	```
	
- **listener_rotation (*vec3, multivalued*) :** rotation of audio listener

	This parameter will contain N values, with N equal to the number of listeners.

	Parameter is mapped by default to `listener/%list_id/rotation`
	
	Usage with default vars and patterns: 
``` cpp
float playerRot[] = {1.0, 2.0, 3.0};
context.setParameter("listener/1/rotation", playerRot);
```

- **hardware_position(*vec3, multivalued*) :** position of each speaker
	
	This parameter will contain N values, with N equal to the number of speakers/subchannels.

	Parameter is mapped by default to `hardware/%speaker_id/position`

	Usage with default vars and patterns: 
``` cpp
float oneSpeakerPos[] = {1.0, 2.0, 3.0};
context.setParameter("hardware/4/position", oneSpeakerPos);	// move 5th speaker position
```
	
> **Note :** coordinates in Aspic Audiostack are specified using right-hand axes (X right, Y up, Z backward).

------

<br/>

## Helpers

### Calibration

VBAP extension offers methods to calibrate your speaker setup. Using sine sweeps and offline processing, it computes gain, delay, and filters to ensure your setup will provide homogeneous renderings.

These helpers are being documented, if you have specific questions, please contact us.

------

<br/>
<br/>

## Code samples

For more code samples, see [VBAP samples](../extensions/vbap-samples)

Please note that our VBAP samples use ASIO or JACK outputs, in order to provide multiple speakers capabilities.

### VBAP spatialization sample

This sample spatialize hello input for one listener with 4 speakers. Audio output is achieved with jack but could rely on ASIO with a slightly different code. 

```cpp
{% include_relative extensions/ExtVBAP_1_Basics.cpp %}
```

For more code samples, see [VBAP samples](../extensions/vbap-samples)
