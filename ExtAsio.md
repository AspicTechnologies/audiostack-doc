---
title: Asio module
permalink: /audiostack/Asio/
---

ASIO (Audio Stream Input/Output) is a computer sound card driver protocol. It enables to address inputs and outputs from many professional sound card.

You can use ASIO extension to address many hardware IO (eg, outputing signal to multiple listeners or array of speakers). ASIO is also a low latency procotol and maybe used to get the best audio experience.

{% icon fa-exclamation-triangle  %} Like in other audio softwares, only one ASIO driver can be used at a time. You can create many AsioInput and AsioOutput, but they will all access the same driver. 

1. Inputs
	* [AsioInput](#asioinput)
2. Outputs
	* [AsioOutput](#asiooutput)
3. Helpers
	* [AudioDriverList](#audiodriverlist)
	* [AudioDriver](#audiodriver)
	* AudioSlot

	
	
	
	
	
	
	
	
	
	
	
	
	
## Inputs

### AsioInput

Provides access to multiple inputs from a connected sound card with ASIO support.


| I/O		| Channel count 		| Sub channel count					|
-|:-:|-:
|`out`		|1						| M (see construction)	|



#### Construction

- **audioSlot (*const char* *)** : a string composed of the driver name and a list of input names. The input will have as many subchannels as input names in the list.

	Generic usage:
	```cpp
context.createInput(ID,AsioInput,"DRIVER_NAME:IN_1_NAME,IN_2_NAME");
	```
	
	Sample usage for a Focusrite sound card creating a two subchannels input:
	```cpp
context.createInput(ID,AsioInput,"Focusrite USB 2.0 Audio Driver:Input 3,Input 4");
	```

- **audioSlot (*AudioSlot&*)** : an AudioSlot object representing the driver and the list of inputs (see [AudioSlot](#AudioSlot)).
	{% icon fa-exclamation-triangle  %} Requires revision
	
#### Parameters

##### Instanciation

- **buffer_size (*unsigned int*)** : the length of inputs audio buffers.

	This parameter is mapped by default to `application/buffer_size`.

	Please note that this sets the length of audio buffer in application, not on the asio soundcard itself. For instance, your soundcard may use buffers of length 256 while your audiostack diagram processes buffer of size 512, or 256, or 4096, ...
	
	Usage : 
	```cpp
context.setParameter("application/buffer_size",256U);
	```

	
	
	
	
	
	
	
	
	
	
	
	
	
## Outputs

### AsioOutput

Provides access to multiple outputs from a connected sound card with ASIO support. 

It can be used to output multi-speaker output, or multiple headphones.

| I/O		| Channel count 		| Sub channel count					|
-|:-:|-:
|`in`		|N						| M (see construction)	|



#### Construction

- **audioSlot (*const char* *)**: a string composed of the driver name and a list of output names. The output will have as many subchannels as output names in the list.

	Generic usage:
	```cpp
context.createOutput(ID,AsioOutput,"DRIVER_NAME:OUT_1_NAME,OUT_2_NAME");
	```
	
	Usage for a Focusrite sound card creating a two subchannels output:
	```cpp
context.createOutput(ID,AsioOutput,"Focusrite USB 2.0 Audio Driver:Output 1,Output 2");
	```

- **audioSlot (*AudioSlot&*)** : an AudioSlot object representing the driver and the list of outputs (see [AudioSlot](#AudioSlot)).
	{% icon fa-exclamation-triangle  %} Requires revision
	
	
#### Parameters

##### Instanciation

- **buffer_size (*unsigned int*)** : the length of microphone audio buffers.

	This parameter is mapped by default to `application/buffer_size`.

	Please note that this sets the length of audio buffer in application, not on the asio soundcard itself. For instance, your soundcard may use buffers of length 256 while your audiostack diagram processes buffer of size 512, or 256, or 4096, ...
	
	Usage : 
	```cpp
context.setParameter("application/buffer_size",256U)
	```

	
	
	
	
	
	
	
## Classes


### AudioDriverList

#### Construction

```cpp 
AudioDriverList();
```
Creates a driver list.

#### Methods

```cpp 
unsigned int getNbDrivers()
```
Returns the number of asio drivers installed on your system.

```cpp 
const char* getDriverName(unsigned int _driverId)
```
Returns the name of the requested driver.

```cpp 
const char* getDefaultDriver() 
```
Returns the name of the first available ASIO driver on your system. If no driver is available, it returns nullptr.

Usage:
```cpp
AudioDriverList myList; 

const unsigned int nbDrivers = myList.getNbDrivers();
std::cout << nbDrivers << "available on your system.\n";

for(unsigned int i = 0; i < nbDrivers; ++i){
	std::cout << "Driver " << i <<", name: " << myList.getDriverName(i) << std::endl;
}

```	


### AudioDriver

#### Construction

```cpp 
AudioDriver(const char* _driverName)
```
Creates a driver, using the ASIO driver matching *_driverName*.
Please note that only one AudioDriver can be instanciated simultaneously.

```cpp 
bool isDriverLoaded()
```
Returns true if driver is properly created, false otherwise. You can also catch exceptions raised in constructor.

```cpp 
const char* getDriverName()
```
Returns the name of the represented ASIO driver (provided at construction).

```cpp 
unsigned int getNbInputs()
```
Returns the number of inputs available on the connected soundcard

```cpp
unsigned int getNbOutputs()
```
Returns the number of outputs available on the connected soundcard

```cpp
const char* getInputName(unsigned int _inputId)
```
Returns the name of the nth input

```cpp
const char* getOuputName(unsigned int _outputId)
```
Returns the name of the nth output

```cpp
void getAvailableBufferSize(unsigned int& _current, unsigned int& _min, unsigned int& _max, unsigned int& _preferred)
```
Provides buffer length available on connected soundcard. 

```cpp
float getSampleRate()
```
Returns operating samplerate of your soundcard.


```cpp
bool hasInput(const char* _inputName)
```
Returns true if *_inputName* is an available input 


```cpp
bool hasOuput(const char* _outputName)
```
Returns true if *_outputName* is an available output 

<br/>

Usage:
```cpp
AudioDriver myDriver("Dante Virtual Soundcard (x64)"); 

unsigned int nbInputs = myDriver.getNbInputs();
std::cout << "Current asio driver has " << nbInputs << " inputs."<<std::endl;
for(unsigned int inIdx = 0; inIdx < nbInputs; ++inIdx){
	std::cout << "\t" << inIdx << " - " << myDriver.getInputName(inIdx) <<std::endl;
}

```	

### AudioSlot

{% icon fa-exclamation-triangle  %} Requires revision



------


## Code samples


### C++ API Samples

> **Note:** Our Asio Inspector program, provided with Aspic Audiostack, enables you to get info about available asio drivers on your computer.

#### ASIO Basics

This sample spatialize hello input for one listener with 2 speakers on an asio device.

```cpp
{% include_relative samples/Asio_1_Basics.cpp %}
```

#### Multilistener using ASIO

This sample spatialize hello input for two listeners on the same host. Each listener gets individualized spatialization.

```cpp
{% include_relative samples/Asio_2_Multilistener.cpp %}
```


