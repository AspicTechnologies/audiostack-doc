---
title: Unity introduction
permalink: /audiostack/Unity/
---

Audiostack is packaged with a plugin for Unity3D. The concepts of Audiostack remain identical to the SDK: you connect inputs/effects/outputs together to build custom audio pipelines.

If you are not familiar with Audiostack diagrams, please [read the very first page of this documentation](../Index) to understand what are diagrams, inputs, buses, effects and outputs. Also, if you are in the mood, discover [channels and subchannels](../AdvancedConcepts#channels-and-subchannels).

1. [Install](#install)
2. [New features](#specific-concepts-for-unity)
3. [Your first sample](#setup-the-plugin)

<br/>

## Install

Audiostack plugin for Unity is shipped as a .unitypackage file. You can import it in a project by double-clicking this file, or using ```Assets/Import package/Custom package``` in Unity Editor.

Please import all files contained in the package:
- Audiostack: all scripts wrapping Audiostack SDK
- Editor: UI of Audiostack in Unity
- Plugins: native libraries for your system (ex: Win64, Android).

------

<br/>

## Specific concepts for Unity

Most of the features of Audiostack are working the same, whether you are using the SDK or the plugin. However, there is two new things to learn: "Config" and how Connections work.

### Config node

In every Unity scene using Audiostack, the *first* thing you will do is add one Audiostack Config component on one gameobject.

- Select a gameobject (or create a new one), for convenience, you could name it "Audio root"
- Add a component using ```Aspic Audiostack/Config```
- Drag and drop your license key file in the field "License file"

{% icon fa-exclamation-triangle  %} If your license is invalid, Unity console will remind it to you and Audiostack won't work at all.

_Adding Config process_
![img CinematicVR Panner]({{site.baseurl}}/audiostack/unity3d/img/addConfig.jpg)

_Config component looks like this_
![img CinematicVR Panner]({{site.baseurl}}/audiostack/unity3d/img/configNode.jpg)

If you uncheck "Follow Unity Settings", you will be able to tune global parameters of Audiostack (buffer length, sample rate). We advise that you try to reduce buffer length whenever you can (512 is a nice value) but don't touch buffering and sample rate is not necessary.

If "Follow Unity Settings" is checked, Audiostack will in the exact same configuration than Unity audio engine (usually longer buffers with more buffering, causing higher latencies).

### Connections

When using the C++ SDK, you connect inputs, buses and outputs using instructions such as:

```context.connect(INPUT, OUTPUT);```

In our Unity plugin:
- every bus and output has a name
- every input and bus has a list of "Sends" (this list contains the name of available bus/output to connect to)

Lets see how this looks:

Here is my output, named "listener":
![img CinematicVR Panner]({{site.baseurl}}/audiostack/unity3d/img/linksOutput.jpg)

Here is my input. Its Sends list contains listener. I just have to check the box to connect them together. 
![img CinematicVR Panner]({{site.baseurl}}/audiostack/unity3d/img/linksInput.jpg)

This is all you have to know about it. Please [visit samples](../unity3d/samples-list) to learn more!

------

<br/>

## Setup the plugin

In order to test that the plugin is working, let's create a basic "Hello sample"! If you have read the SDK documentation, you know it already: we will create a Hello Input (synthetized voice) and send it to a Windows Core Audio Output (or any other simple output available for your OS).

### 1. Config

- Create a new gameobject
- Name it "Audio config"
- Add a component: ```Aspic Audiostak/Config```
- Drag and drop your license file in the License file field

You can leave other parameters as they are.s

![img CinematicVR Panner]({{site.baseurl}}/audiostack/unity3d/img/sampleOne_COnfig.jpg)

### 2. Output

- Create a new gameobject
- Name it "Listener"
- Add a Windows Core Audio output component: ```Aspic Audiostak/Outputs/Soundcards/Windows Core Audio```
- In the field "Output key", type "listener"
- Uncheck the "Stereo" attribute

![img CinematicVR Panner]({{site.baseurl}}/audiostack/unity3d/img/sampleOne_In.jpg)

### 3. Input

- Create a new gameobject
- Name it "Source"
- Add a Hello Input component: ```Aspic Audiostak/Inputs/Hello```
- Under "Send properties", check the bow besides "listener" output

![img CinematicVR Panner]({{site.baseurl}}/audiostack/unity3d/img/sampleOne_Out.jpg)

### 4. Play

- Save your scene
- Play!

If you have followed these steps and if your license is valid, you should hear a welcome message :)

If black magic has broken your Audiostack, please contact us.


------

<br/>

## Next steps

You may know [discover samples](../unity3d/samples-list) or read more advanced doc about the plugin.

At any time, feel free to ask support by [contacting us](https://www.aspictechnologies.com/contact).
