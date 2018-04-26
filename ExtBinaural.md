---
title: Binaural (w Sofa support)
permalink: /audiostack/Binaural/
---


Aspic Audiostack Binaural module provides effects for binaural spatialization.

1. Effects
	* [Binaural Spatialization Aspic](#binaural-spatialization-aspic)
2. Helpers
	* [Loading custom HRTFs](#loading-custom-hrtf)
3. [Code samples](#code-samples)
		


## Effects

### Binaural Spatialization Aspic

Provides HRTF-based spatialization for binaural rendering. Also supports SOFA for individualized binaural rendering.

Each input channel is spatialized independently (no mixing), which enables you to add more "per-channel" effects after this spatialization.

| I/O		| Channel count 		| Sub channel count	| |
-|:-:|:-:|-
|`in`		|N						|1 (MONO)			| |
|`out`		|N						|2 (STEREO)			| |

#### Construction

No arguments 

Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, BinauralSpatializationAspic); 
```

#### Parameters

##### Instanciation

- **subject_name (*const char\**) :** name of HRTF to use

	If you have registered custom HRTF in the context, use this parameter to bind hrtfs to listeners

	Parameter is mapped by default to `listener/%list_id/subject_name`

	Usage with default vars and patterns:
	``` cpp
context.setParameter("listener/6/subject_name", "myHRTF");
	```

To load and register custom HRTF, see [HRTF loading](#loading-custom-hrtf) below.

##### Runtime

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
	

{% icon fa-exclamation-triangle  %} **Note :** coordinates in Aspic Audiostack are specified using right-hand axes (X right, Y up, Z backward).


{% icon fa-exclamation-triangle  %} We will add a convenient interface to help you transform various coordinates systems.

-----

<br/>

## Helpers

### Loading custom HRTF

In order to use custom HRTF, this extension allows you to laod .SOFA files.

First you have to register a new asset of type SofaAsset:

Usage:
```cpp
context.registerAsset("my_hrtf", 4 /* SofaAsset */);
```

The first parameter is the name you want to give to this asset; the second parameter identifies SofaAssets.

Then, you can load a file into this assets using:
```cpp
context.loadAssetFromFile("my_hrtf", "path/to/myHrtf.SOFA");
```

If your SOFA file is properly formated, the asset is successfully loaded, and you can bind these HRTFs to one listener. Please check [Binaural samples](../ExtBinauralSamples)!


-----

<br/>
<br/>


## Code samples

For more code samples, see [Binaural samples](../ExtBinauralSamples)

### Binaural spatialization sample

This sample spatialize audio for one listener.

For multilistener samples, please see Asio Extension samples, since they enable multi-output rendering.

```cpp
{% include_relative samples/Binaural_1_Basics.cpp %}
```

For more code samples, see [Binaural samples](../ExtBinauralSamples)
