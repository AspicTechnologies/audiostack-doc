---
title: Nahimic (third party binaural)
permalink: /audiostack/Nahimic/
---

Audiostack Nahimic&trade; Binaural module provides binaural spatialization algorithms developed by A-Volute&trade;.

1. Effects
	* [Nahimic Binaural Spatialization](#nahimic-binaural-spatialization)









## Effects

### Nahimic Binaural Spatialization

Provides Nahimic&trade; binaural spatialization. 

Due to optimized signal processing, spatializated audio is mixed in one output channel.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 (MONO)			|
|`out`		|1						|2 (BINAURAL)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, NahimicBinauralSpatialization);
```

#### Parameters

ø

> [Global parameters](../applicationparameters) used by this IO :
> - application/buffer_size
> - application/sample_rate

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

	


------

<br/>


## Code samples

For more code samples, see [Nahimic samples](../extensions/ExtNahimicSamples)

### Nahimic spatialization sample

This sample spatialize audio for one listener.

For multilistener samples, please see [Asio Extension samples](../extensions/ExtAsioSamples).

```cpp
{% include_relative samples/Nahimic_1_Basics.cpp%}
```

