---
title: Ambisonics
permalink: /audiostack/extensions/Ambisonics/
---

This extension handles ambisoncis streams: encoding, decoding, conversions.

1. Effects
	* [AmbisonicsToBinaural](#ambisonics-to-binaural)
	* [AmbisonicsEncoder](#ambisonics-encoder)
	* [AmbisonicsOrderManipulation](#ambisonics-order-manipulation)
2. [Code samples](#code-samples)






	
	
## Effects

### Ambisonics To Binaural

Renders ambisonics streams as binaural.

| I/O		| Channel count 		| Sub channel count	| |
:-:|:-:|:-:|-
|`in`		| N						| M			| |
|`out`		| N						| 2 (BINAURAL) 		| |


#### Construction

- **ambFormat (*const char*) :** Use this parameter to specify the kind of Ambisonics stream you will be sending to the effect. Available values are: ACN_SN3D_ORDER1, ACN_SN3D_ORDER2 and ACN_SN3D_ORDER3. Streams must be normalized and order using ACN SN3D convention.

Usage: 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, AmbisonicsToBinaural, "AMBISONICS_THIRD_ORDER");
```


#### Parameters

##### Runtime
	
- **listener_rotation (*vec3, multivalued*) :** rotation of audio listener

	This parameter will contain N values, with N equal to the number of listeners.

	Parameter is mapped by default to `listener/%list_id/rotation`
	
	Usage with default vars and patterns: 
``` cpp
float playerRot[] = {1.0, 2.0, 3.0};
context.setParameter("listener/1/rotation", playerRot);
```
	


<br/>

<br/>








### Ambisonics Encoder

Encodes mono sources to ambisonics.

| I/O		| Channel count 		| Sub channel count	| |
:-:|:-:|:-:|-
|`in`		| N						| 1			| |
|`out`		| N						| M 		| |


#### Construction

- **ambFormat (*const char*) :** Use this parameter to specify the kind of Ambisonics stream you want as effect output. Available values are: ACN_SN3D_ORDER1, ACN_SN3D_ORDER2, ACN_SN3D_ORDER3, TBE.

Usage: 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, AmbisonicsEncoder, "TBE");
```


#### Parameters

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




<br/>

<br/>




### Ambisonics Order Manipulation

Converts ambisonics to different ambisonics ordering/normalization.

| I/O		| Channel count 		| Sub channel count	| |
:-:|:-:|:-:|-
|`in`		| N						| M			| |
|`out`		| N						| O 		| |


#### Construction

- **inAmbFormat (*const char*) :** Input ambisonics type. Available values are: ACN_SN3D_ORDER1, ACN_SN3D_ORDER2, ACN_SN3D_ORDER3, TBE.

- **outAmbFormat (*const char*) :** Output ambisonics type. Available values are: ACN_SN3D_ORDER1, ACN_SN3D_ORDER2, ACN_SN3D_ORDER3, TBE.

Usage: 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, AmbisonicsOrderManipulation, "ACN_SN3D_ORDER3", "TBE");
```

-----

<br/>
<br/>

## Code samples

For more code samples, see [Ambisonics samples](../ambisonics-samples)

### Ambisonics to Binaural

This sample renders an ambisonics stream in binaural.

```cpp
{% include_relative extensions/ExtAmbisonics_1_HOAToBinaural.cpp %}
```


For more code samples, see [Ambisonics samples](../ambisonics-samples)

