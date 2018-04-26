---
title: JACK (virtual soundcard)
permalink: /audiostack/extensions/jack/
---

JACK is a virtual sound card driver. It enables to interconnect programs audio IO together, and with real soundcards too.

You can use JACK extension and ASIO extension to address many hardware IO (eg, outputing signal to multiple listeners or array of speakers). JACK extension is only available for Unix systems.

1. Inputs
	* [JackInput](#jack-input)
2. Outputs
	* [JackOutput](#jack-output)
3. [Samples](#code-samples)

	
	
	
	
	
	
	
	
	
	
	
	
	
## Inputs

### Jack Input

Creates a jack client with multiple input ports. Allows you to send audio from other programs or soundcards to Audiostack diagram.

| I/O		| Channel count 		| Sub channel count					|
-|:-:|-:
|`out`		|1						| M (see construction)	|


#### Construction

- **subChannelCount (*unsigned int*)** : The number of input ports to create on a new jack client.

Sample usage to send 4 channel to this input (for instance for FOA acquisition):
```cpp
context.createInput(ID,JackInput,4U);
```


#### Parameters

ø

> [Global parameters](../applicationparameters) used by this IO :
> - application/buffer_size


------

<br/>

	
	
	
	
	
	
	
	
	
	
## Outputs

### Jack Output

Creates a jack client with multiple output ports. Allows you to send audio from Audiostack to other programs or soundcards.

It can be used to output multi-speaker output, or multiple headphones.

| I/O		| Channel count 		| Sub channel count					|
-|:-:|-:
|`in`		|N						| M (see construction)	|



#### Construction

- **subChannelCount (*unsigned int*)** : The number of input ports to create on a new jack client.

Sample usage to expose a 8 channel output on jack (for instance in combination with 8 speaker spatialization):
```cpp
context.createInput(ID,JackOutput,8U);
```
	

#### Parameters

##### Runtime

- **master_gain (*float*)** : master gain of this output (amplitude).

	This parameter is mapped by default to `listener/%list_id/master_gain`.

	Usage : 
```cpp
context.setParameter("listener/2/master_gain",0.5f)
```

> [Global parameters](../applicationparameters) used by this IO :
> - application/buffer_size




------

<br/>
<br/>

## Code samples

For more code samples, see [JACK samples](../jack-samples)

## JACK spatialization

This sample spatializes hello input for one listener. The output-jack-client must be connected to a hardware output and/or another program.

```cpp
{% include_relative ExtJack_3_Binaural.cpp %}
```

For more code samples, see [JACK samples](../jack-samples)

