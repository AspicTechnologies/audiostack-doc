---
title: Audio file
permalink: /audiostack/AudioFile/
---

Audio file module enables applications to read and write audio files. Supported formats are .wav, .ogg. More extension will be supported soon. Please contact us for more details.

1. Inputs
	* AudioFileReader
	* SyncAudioFileReader
2. Outputs
	* AudioFileWriter
	* SyncAudioFileWriter

	
	
	
	
	
	
	
	
	
## Inputs

### AudioFileReader

This input read a file on your drive and outputs its audio content. It provides commands to pause or resume reading.

> **WAV Files**: must be monophonic and encoded at 48kHz/16bits.

> **OGG files**: must be  encoded at 48kHz. If not, consider changing "application/sample_rate".

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`out`		|1						|1 (MONO)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createInput(ID,AudioFileReader);
```

#### Parameters

##### Instanciation

- **filename (*const char* *) :** path (with filename and extension) to the audio file to read. May be an absolute path or a relative path (relative to the executable location).

	This parameter is mapped by default to `source/%src_id/file`.

	Usage : 
	
```cpp
context.setParameter("source/7/filename","./hello.wav");	// using relative path
context.setParameter("source/7/filename","C:/path/to/hello.wav");	// using absolute path
```
	
- **buffer_size (*unsigned int*) :** the length of audio buffers read by this input.

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
	
```cpp
context.setParameter("application/buffer_size",1024U);
```


- **start_on_awake (*bool*) :** if set to TRUE, file is played when application starts, which is usefull for background sounds. Default value is FALSE (usefull for event sounds).

	This parameter is mapped by default to `source/%src_id/start_on_awake`.

	Usage : 
	
```cpp
context.setParameter("source/5/start_on_awake",true);
```

##### Runtime

- **loop (*bool*) :** if set to TRUE, audiofile will be played in loops, which may prove usefull for background sounds. Default is FALSE.

	This parameter is mapped by default to `source/%src_id/loop`.

	Usage with default vars and patterns: 
```cpp
context.setParameter("source/8/loop",true);
```


#### Commands

- **play :** resume file reading.

	This parameter is mapped by default to `source/%src_id/play`.

	Usage : 
	
```cpp
context.sendCommand("source/10/play");
```

- **pause :** pause file reading. Reader head remains at its current position.

	This parameter is mapped by default to `source/%src_id/pause`.

	Usage : 
	
```cpp
context.sendCommand("source/11/pause");
```
	
- **stop :** stop file reading and place reader head to the beginning of the file.

	This parameter is mapped by default to `source/%src_id/stop`.

	Usage : 
```cpp
context.sendCommand("source/5/stop");
```
	
- **seek (*int*) :** move the header head N samples afer begin. *Seek* doesn't start or stop file reading.

	This parameter is mapped by default to `source/%src_id/seek`.

	TODO requires revision
	
	Usage : 
```cpp
context.sendCommand("source/3/seek",4800);
```
	
#### Callbacks
	
- **at_end :** this callback is called when file reading reaches the end of the file. You can use it to notify your application and trigger an event.

	This parameter is mapped by default to `source/%src_id/at_end`.

	Usage : 
```cpp
context.setCallback("source/ID/at_end",&atEndCallback); // atEndCallback is an argument-less function returning void.
``` 



TODO add AudioFileWriter

TODO add SyncAudioFileReader/Writer

<br/>	
	
## Classes


### AudioClipLibrary

AudioClipLibrary helps you manage audio files and get useful information such as length, samplerate, etc.

#### Construction

```cpp 
AudioClipLibrary();
```
Creates an empty audio clip library.

#### Methods


```cpp 
void registerClip(const char* _id, const char* _filename)
```
Register the audio file located at *_filename* under the identifier *_id*. Will set an error on the context if the audio file could not be opened.

	Usage:
```cpp 
AudioClipLibrary myLibrary;
myLibrary.registerClip("hello","/path/to/hello.wav")
```



```cpp 
float getSampleRate(const char* _id)
```
Returns the samplerate of the clip with identifier *_id*

```cpp 
int getLengthInSample(const char* _id)
```
Returns the length, in samples, of the clip with identifier *_id*

```cpp 
float getLengthInSeconds(const char* _id)
```
Returns the length, in seconds, of the clip with identifier *_id*

```cpp 
int getChannelCount(const char* _id)
```
Returns the number of channels of the clip with identifier *_id*

```cpp 
bool hasClip(const char* _id)
```
Returns true is the library contains a clip with id *_id*

<br/>

Usage:

```cpp 
AudioClipLibrary myLibrary;
myLibrary.registerClip("hello","/path/to/hello.wav");

if(myLibrary.hasClip("hello")){
	std::cout << "Clip duration is " << myLibrary.getLengthInSeconds("hello") << " seconds." << std::endl;
}else{
	// It could be a good idea to check error on Context
}
```

------

## Code samples

For more code samples, see [Audio File samples](../ExtAudioFileSamples)


### C++ API Samples

#### AudioFile simple application

This sample connects an audio file reader to computer output using OpenAL drivers.

Please note this sample doesn't handle errors for code clarity.

```cpp
{% include_relative samples/AudioFile_1_Basics.cpp %}
```

#### AudioFile callbacks

This sample provides hints to use callbacks on file reader.

In this use case, the application stops once the file reading reaches end of file.

```cpp
{% include_relative samples/AudioFile_2_Callback.cpp %}
```

For more code samples, see [Audio File samples](../ExtAudioFileSamples)


