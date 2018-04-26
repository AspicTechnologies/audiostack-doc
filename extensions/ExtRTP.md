---
title: RTP (audio streaming)
permalink: /audiostack/extensions/ExtRTP/
---

This extension uses RTP (Real-time Transport Protocol) to transfer audio streams over IP networks. It allows you to create applications with voice chat, or to compute audio server-side and stream it to clients.

It is possible to create P2P or client/server architectures. The extension also embeds compression alghorithms such as OPUS but may also transfer PCM audio if need be.

1. Inputs
	* [RTPInput](#rtp-input)
2. Outputs
	* [RTPOutput](#rtp-output)
3. Classes
	* [L16Codec](#l16-codec)
	* [OpusCodec](#opus-codec)
4. [Helper](#helpers)
5. [Samples](#code-samples)
















## Inputs

### RTP Input

This input listens one incoming audio stream. It also provides decoding before sending audio in Audiostack diagram.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`out`		|1						|1 (MONO)			|

#### Construction

- **codec (*const char\**)** : codec setup stored as string. Codecs provided in this API extension are able to automatically provide this parameter.

	Usage : 
	
```cpp
[...]	// instanciate a codec named myCodec
context.createInput(ID,RTPInput,myCodec.serialize());
```

#### Parameters

##### Instanciation

- **port (*unsigned int*) :** listening port on local machine.

	This parameter is mapped by default to `source/%src_id/port`.

	Usage : 
	
```cpp
context.setParameter("source/13/port",10400U);	// binds rtp input 13 to local port 10400
```
	
- **bufferization (*unsigned int*) :** stores *bufferization* samples before sending them to the rest of the application. Default value is 8192. Reducing this will reduce latency but could create small glitches if network lags. 

	This parameter is mapped by default to `source/%src_id/bufferization`.

	Usage : 
	
```cpp
context.setParameter("source/13/bufferization",8192U);
```

##### Runtime

ø

#### Callbacks
	
- **on_network_error:** this callback is called when network stacks encounters an error. For instance, if requested port is already occupied.

	This parameter is mapped by default to `source/%src_id/on_network_error`.

	Usage : 
```cpp
context.setCallback("source/ID/on_network_error",&onError); // onError is an argument-less function returning void.
``` 

See [samples](#code-samples) below for basic usage.

------

<br/>











## Outputs

### RTP Output

This output sends one audio channel to the network. It encodes packets before sending them.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|1						|1 (MONO)			|

#### Construction

- **codec (*const char\**)** : codec setup stored as string. Codecs provided in this API extension are able to automatically provide this parameter.

	Usage : 
	
```cpp
[...]	// instanciate a codec named myCodec
context.createOutput(ID,RTPOutput,myCodec.serialize());
```

#### Parameters

##### Instanciation

- **port (*unsigned int*) :** destination port on remote machine.

	This parameter is mapped by default to `listener/%list_id/port`.

	Usage : 
	
```cpp
context.setParameter("listener/15/port",10500U);	// sends audio packets of output 15 to remote port 10500
```
	
- **ip_address (*cosnt char\**) :** destination IP address.

	This parameter is mapped by default to `listener/%list_id/ip_address`.

	Usage : 
	
```cpp
context.setParameter("listener/15/ip_address","127.0.0.1");
```

##### Runtime

ø

#### Callbacks
	
- **on_network_error:** this callback is called when network stacks encounters an error. For instance, if requested port is already occupied.

	This parameter is mapped by default to `listener/%list_id/on_network_error`.

	Usage : 
```cpp
context.setCallback("listener/ID/on_network_error",&onError); // onError is an argument-less function returning void.
``` 


See [samples](#code-samples) below for basic usage.

------

<br/>














## Classes

### L16 Codec

This codec does not compress audio. Audio is encoded as PCM (Pulse Code Modulation) using 16 bits per sample at 44100 Hz. It is usefull to stream uncompress data but will consume bandwith. You can use it on local network.

#### Construction

```cpp 
L16Codec();
```
Creates a L16 Codec.

#### Methods

```cpp 
const char* serialize();
```

Constructs a descriptor of the codec, to be used by RTPInput and RTPOutput constructors.

No other methods are available since L16 Codec requires no tuning.

<br/>

```cpp 
[...]

L16Codec myCodec;

context.CreateInput(42, RtpInput, myCodec.serialize());

[...]
```

<br/>

### Opus Codec

OPUS allows compression for many types of audio signals, from voice to music. Using available parameters, you can adjust bandwith used by audio streams. We use this Codec for all our voice chat applications.

#### Construction

```cpp 
OpusCodec();
```
Creates the Codec.

#### Methods

```cpp 
void setSampleRate(unsigned int sampleRate);
```

Sets codec operating sample rate, available values are: 
* 16000
* 24000
* 48000

Automatic resampling will be achieved in RTPInput and RTPOutput to send/receive OPUS sample rate and convert it to your app samplerate.

<br/>

```cpp 
void setBitrate(unsigned int bitrate);
```

Sets codec operating bitrate, available values are: 
* 8000
* 16000
* 32000
* 64000
* 128000

<br/>

```cpp 
void setVOIP(bool isVOIP);
```

If *isVOIP* is true, then OPUS will perform further compression improvements knowing that audio streams will be voice. 

<br/>

```cpp 
const char* serialize();
```

Constructs a descriptor of the codec, to be used by RTPInput and RTPOutput constructors.

<br/>

Usage:

```cpp 
[...]

OpusCodec myCodec;
myCodec.setSampleRate(24000U);
myCodec.setBitrate(32000U);
myCodec.setVOIP(true);

context.CreateInput(42, RtpInput, myCodec.serialize());

[...]
```

<br/>

## Helpers

```cpp 
void initNetworkAPI();
```

On Windows, clean and recreate sockets context for the current application. If you app only uses Audiostack network features, you probably should call this function on launch. If your app embeds other network features, you don't want to use this.

Our piece of advice: don't use this method unless Audiostack is not able to open sockets.


```cpp 
void cleanNetworkAPI();
```

On Windows, clean sockets used by current application. If you app only uses Audiostack network features, you probably should call this function before exiting.

Our piece of advice: add this at exit if you notice that sockets remains locked after your app has ended.

<br/>

Usage:

```cpp 
int main(){
	RtpInterface::initNetworkAPI();

	[...]	// my application

	RtpInterface::cleanNetworkAPI();
	return 0;
}
```

------

<br/>









## Code samples

For more code samples, see [RTP samples](../ExtRTPSamples)


### C++ API Samples

#### Microphone stream/listen

The following code captures the microphone, sends it to localhost, reads it back and outputs final audio on the soundcard. With little modifications, it is possible to create collaborative audio application.

Please note this sample doesn't handle errors for code clarity.	

```cpp
{% include_relative ExtRTP_1_Basics.cpp %}
```

<br/>

For more code samples, see [RTP samples](../ExtRTPSamples)


