---
title: C++ API Documentation
permalink: /audiostack/AudiostackAPI/
---

Getting started
-----
During the installation process, several directories were created at the installation location.

- **include** : contains the C and C++ header files
- **lib** : dynamic libraries to build and ship your application (linux/windows)
- **helpers**: small tools, such as asio inspector or jack inspector
- **server**: audiostack server and libraries, usefull to enable client/server mode (see Doc)
- **cmake**: contains CMake scripts to help CMake find the library
- **depends**: contains third party installers
- **samples** : contains some ready to test code sample and cmake projects 

The C API is provided for cross-compiler compatibility and is not designed to be used directly.
The C++ API is then strongly recommended. The current API documentation will only focus on the C++ version.

### Requirements

* C++ compiler with C++11 support and correctly chosen architecture
* CMake to build given *samples*

### Building *samples*
To build all the samples, please execute the following commands. If not available on your system, there must exist close alternatives.

```console
cd samples/
mkdir build
cd build
cmake ..
make
```

### Helloworld using Audiostack and CMake
Create a new project directory

* CMakeLists.txt  

```cmake
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{AUDIOSTACK_CMAKE}")

project(helloworld)
add_executable(helloworld hello.cpp)

find_package (AspicAudiostack)
if (AspicAudiostack_FOUND)
  include_directories(${AspicAudiostack_INCLUDE_DIRS})
  target_link_libraries (helloworld ${AspicAudiostack_LIBRARIES})
endif (AspicAudiostack_FOUND)
```
* hello.cpp

```c++
#include <iostream>
#include "Audiostack.hpp"

int main(){
	AudiostackContext context;							
	context.setLicenseKeyFromFile("LICENSE_FILE.aslc");	
	
	int input=0
	int output=1;
	context.createInput(input,HelloInput);				
	context.createOutput(output,OpenALOutput,false);	
	
	context.connect(input,output);
	
	context.play();
	
	char c;
	do{
		std::cin>> c;
	}while(c!='q');
	
	context.stop();
	
	return 0;
}
```

<br/>
<br/>
<br/>

Before you read what's below
-----

The next chapter is a full API doc of Audiostack main class: *Context*. If you are new to Audiostack, it should maybe be a better idea to first discover samples. They will help you understand Audiostack architecture.

AudiostackContext
-----

*AudiostackContext* is the main class of *Aspic Audiostack*. 

### Construction/Destruction

```c++
AudiostackContext()
```
Construct an *AudiostackContext*.

<br/>

```c++
~AudiostackContext()
```
Destroy the *AudiostackContext*. While destroying, the diagram is totally cleared

<br/>

```c++
void clear()
```
Clear the diagram. All inputs, outputs, buses, effects and parameters are destroyed.

<br/>

```c++
void setLicenseKeyFromFile(const char* _keyFile);
```

Set a license file. A valid license file must be loaded to ensure diagram construction will work properly. License files holds information about the modules you have access to (Binaural, Asio, Vbap).

<br/>

```c++
void setLicenseKeyFromMemory(const char* _address, int _length);
```

Load license data from memory. License content must be stored in a char array.

<br/>

### Diagram edition

```c++
int createInput(int _objectId, int _inputType, Args...)
```	
					
Create an audio input of type *_inputType* with *_objectId* as **unique** identifier. Returns the identifier of the object if the operation is successful, -1 otherwise.

Please note that *_objectId* must be unique among all inputs, outputs, buses and effects.

See API Extensions to learn more about available inputs and their parameters.

<br/>

```c++
int createOutput(int _objectId, int _outputType, Args...)
```
Create an audio output of *_ouputType* with *_objectId* as unique identifier. Returns the identifier of the object if the operation is successful, -1 otherwise.

*_objectId* must be unique among all inputs, outputs, buses and effects.

See API Extensions sections to learn more about available outputs and their parameters.

<br/>		

```c++		
int createBus(int _objectId)
```

Create an audio bus with *_objectId* as identifier. Returns the identifier of the object if the operation is successful, -1 otherwise.

*_objectId* must be unique among all inputs, outputs, buses and effects.

<br/>

```c++		
void setLastEffectCount(int _busId, int _lastEffectCount)
```

{% icon fa-exclamation-triangle  %} This entry point requires revision

Set the number of instance of the last effect in the bus *_busId* to *_lastEffectCount*. Effects in the bus will be duplicated to enable differentiated processing, like independent spatialization and attenuation for multiple listeners. The bus will have multiple inputs and outputs (see [naming section](#naming)).

See our samples to go further.

<br/>

```c++
int createEffect(int _objectId, int _busId, int _effectType, Args...)
```

Create an audio effect of type *_effectType* at the back of bus *_busId* with *_objectId* as identifier. Returns the identifier of the object if the operation is successful, -1 otherwise.

*_objectId* must be unique among all inputs, outputs, buses and effects.

See API Extensions sections to learn more about available effects and their parameters.

<br/>

```c++
void removeInput(int _objectId)
``` 																

Remove audio input holding identifier *_objectId*.

<br/>

```c++
void removeOutput(int _objectId)
``` 																

Remove audio output holding identifier *_objectId*.

<br/>

```c++
void removeBus(int _objectId)
``` 																    

Remove audio bus holding identifier *_objectId* and all of its effects.

<br/>

```c++
void removeEffect(int _objectId)
``` 																

Remove audio effect holding identifier *_objectId*.

<br/>

```c++
void connect(int _outObjectId, int _inObjectId)
```

Connects object *_outObjectId* to object *_inObjectId*. This is the easiest way to connect inputs/buses/outputs.

However, some buses may have multiple inputs and outputs. In this ambiguous case, the method will raise an error (see Error handling section).

Therefore you'll have to use
```c++
void connect(int _outObjectId, const char* _outputName, int _inObjectId, const char* _inputName)
```													 

It connects the output *_outputName* of object *_outObjectId* to the input *_inputName* of object *_inObjectId*. 

* Audio inputs own a sole output called "out".

* Audio outputs own a sole input called "in".

* Buses may own many inputs/outputs. For instance, a spatialization bus effect for 2 listeners holds 2 outputs and inputs. Therefore, these inputs/outputs are named : `in_0`, `in_1`, `out_0`, `out_1`, etc.

<br/>

```c++
void disconnect(int _outObjectId, int _inObjectId)
```

Disconnect given objects.

```c++
void disconnect(int _outObjectId, const char* _outputName, int _inObjectId, const char* _inputName)
```

Disconnect specific IO of given objects.

<br/>

##### Transactions

Above are listed main operations to modify diagrams, ie IO/effects creation, deletion, connection.

You can use them before calling play() and you also can use them after play(). In this second case, you just have to enclose calls in a transaction:

```c++
void beginTransaction()
```

Starts a new transaction on the context. It allows you to modify the digram.

```c++
void endTransaction()
```

End transaction, and applies any modification you have asked for. If your modifications create an invalid state, the transaction will fail and raise an error.

```c++
void waitForTransaction()
```
	
Transactions are not applied synchroniously. If you wish, you can wait until it is done.

Sample:

```c++
[...]

context.beginTransaction();

context.createInput(IN_ID, TYPE, ARGS);				// create a new input (a source)
context.connect(IN_ID, ALREADY_EXISTING_BUS_ID);	// connect it to already existing parts of the digram

context.endTransaction();							// applies modifications
context.waitForTransaction();

[...]
```

### Parameters

Parameters are declared and owned by inputs, outputs or effects. The following function may prove useful to modify these parameters. Please refer to [Advanced Concepts](../AdvancedConcepts) to get a better grasp on parameters, and to API Extensions to learn more about available parameters.

At some point, please read [Advanced Concepts](../AdvancedConcepts) to learn about the difference between runtime parameters and instanciation parameters.

<br/>

```c++
void setParameter(const char* _param, T _value)
```

Apply the value *_value* to the parameter at address *_param*

Please use proper type for parameters (float, int, unsigned int, etc). Type mismatch will raise an error.

##### Samples

```c++

context.setParameter("application/buffer_size", 512U);

float sourcePos[] =   {0.0, 0.0, 0.0};
context.setParameter("source/SOURCE_ID/position", sourcePos);

```

<br/>

```c++
void sendCommand(const char* _param, Args...)
```

Send command *Args* to address *_param*. 

You can learn how and when to use commands using Extensions. For instance audio file use commands to trigger play/pause/stop.

<br/>

```c++
void setCallback(const char* _param, void(*_f)(Args...))
```

Set callback *_f* to address *_param*. 

You can learn how and when to use callbacks using Extensions. For instance, audio metering uses callbacks to provide you realtime metering.

<br/>

```c++
void setParameterPattern(int _objectId, const char* _param, const char* _pattern)
```

Apply the pattern *_pattern* to the parameter *_param* of object *_objectId*. If successful, the parameter will be mapped to the pattern.

<br/>
 			 
```c++
void setVariable(int _objectId, const char* _variable, T _value)
```

Set a variable named *_variable* of value *_value* on the object designated by id *_objectId*.

<br/>
		
		

### Play/Stop

```c++
void play()
```

Start audio processing. After this call, every operation on the diagram (IO creation or deletion, connections, modification of instanciation parameters) must be enclosed in a transaction (see below). However, runtime parameters can be set at any time without transaction.

<br/>

```c++
void stop()
```

Stop audio processing.

<br/>

### Error handling

AudiostackContext will not throw any exception. Instead, each method call may set an error flag that you have to check.

```c++
static int getError()
```

Return error status of the API. A value equal to 0 means there is no error. A value equal to 1 means an error has been raised.

Please note that calling this method will **reset the internal error flag** to 0.

<br/>

```c++
static const char* getLastErrorMessage()
```

Contains the description of the last error raised. You typically want to get this message right after a getError call returned

Since this method doesn't change any internal state, an empty error message doesn't mean there are no error.

<br/>

### Extensions

Audiostack API is divided into modules (also called Extensions). Each module offer specific features (such as Binaural rendering or Network streaming).

```c++
static void MyExtension::Load(Context* _context)
```

Load module/extension *MyExtension* in *_context*. If successful, the context will now enable the developer to access methods and inputs/outputs/effects of this module.

Given an extension called *MyExtension*, a sample program loading that extension may look like this :

```c++
#include "Audiostack.hpp"
#include "AudiostackExtension.h"

int main(){
	AudiostackContext context;
	context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

	MyExtentionInterface::Load(context.impl);
	
	MyExtensionObject object;
	object.someFunction()
	...
```

In the previous example, constructing a *MyExtensionObject* before the call *MyExtensionInterface::Load* would have caused a license error.

<br/>

## Disclaimer

Audiostack handles very complex concepts (patterns, variables, etc). Creating nice audio pipelines may prove very easy, but tuning specific features may prove harder.

In order to produce a clear documentation, in code samples and in extensions documentation, **we will use default patterns and variables**. 

This means that:
* each Input automatically declares a variable src_id equal to its objectId
* each Output automatically declares a variable list_id equal to its objectId
* each Input/Output/Effect create a convenient pattern to address its parameters

At some point, we will create a 'Power User' section to help you use custom patterns.

## What do I do now?

Have you checked code samples? Please do, they will help you create your first audio pipeline :)

