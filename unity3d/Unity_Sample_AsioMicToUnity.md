---
title: Get ASIO microphone into Unity
permalink: /audiostack/unity3d/samples/AsioToUnity/
---

In this sample, we will create a simple Audiostack setup in Unity, to acquire microhpone through ASIO soundcard, and send it into Unity audio engine, as a basic AudioSource.

The idea is to use ASIO latency capabilities and Unity AudioSource praticality (spectrum analysis, etc.).

## Prerequisties

* Unity3D 2017+
* Audiostack with the following extensions:
	* Core
	* ASIO / Low-latency
	* Memory
* A valid Audiostack licence

## Concept

A simple diagram of what we try to achieve

![Alt text](../../img/asioMicToUnity_6.PNG)

In Audiostack context, we handle ASIO soundcard and inject audio in Unity memory.

In Unity3D context, we inject audio stream in an Audio Source, to be processed by built-in audio features.

## Unity scene

Let's do it!

### Audiostack config

We create an empty game object and add a Audiostack Config (Add Component > Audiostack > Config).

![Alt text](../../img/asioMicToUnity_2.PNG)

We specify the path to our license key file. We also uncheck "Follow Unity Settings" to specify our own buffer length (512 in our case). 

Feel free to try other buffer length to handle ASIO latency. Also, don't forget to check your soundcard driver to adjust its latency.

###  ASIO microphone

We create a new empty game object, and add a Asio Input (Add Component > Audiostack > Inputs > Soundcards > ASIO)

We choose the driver corresponding to the soundcard we want to use, in my case "Focusrite USB 2.0 Audio Driver", specify that we want 1 input channel, and chose a hardware entry.

![Alt text](../../img/asioMicToUnity_3.PNG)

We are not able to send this input to our output yet, we will come back to it later.

### Memory output

We create a new empty game object, and add a Memory Output (Add Component > Audiostack > Outputs > Audiostack to Audio Clip)

We give a nice name to this output and don't change default parameters. You'll notice that it has automatically created an Audio Source without Audio Clip. Audiostack memory output will send its stream to this Audio Source.

![Alt text](../../img/asioMicToUnity_4.PNG)

### Connect IOs

We can connect our asio input to memory output:
- select our input game object
- in inspector, in component Asio Input, the last field "Send properties" displays a list of outputs.
- we check the output that will receive asio micrphone.

![Alt text](../../img/asioMicToUnity_7.PNG)

### Play!

We ensure there is a Audio Listener somewhere in the scene and hit play!

From this point, we hear whatever goes into our microphone in Unity audio output. The latency should be really nice but we can improve it:
* on our asio soundcard driver, we can reduce buffer length/latency,
* on Aspic Audiostack Config, we can reduce buffer length (512 ? 256 ? 128 ?),
* in Unity "Edit/Project Settings/Audio", we can ensure "DSP Buffer Size" is set to "Best Latency".

For further support, please contact us at dev[at]aspic[dot]tech!