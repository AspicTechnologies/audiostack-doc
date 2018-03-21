---
title: Multi listener binaural rendering in Unity
permalink: /audiostack/unity3d/samples/MultiListenerUnityAsio/
---

In this sample, we will use Audiostack Unity plugin to provide binaural rendering for two different listeners.

The idea:
- exploit multi-output feature of Audiostack,
- use ASIO soundcard to get multiple outputs (two pairs in our case).

## Prerequisties

* Unity3D 2017+
* Audiostack with the following extensions:
	* Core
	* Binaural
	* ASIO / Low-latency
* A valid Audiostack licence

## Concept

A simple diagram of what we try to achieve

![Alt text](../../img/multilistener_asio_unity_1.png)

Each listener will be mapped to 2 hardware outputs (left+right). 

In current Audiostack Unity plugin version, buses have are not exposing multilple outputs (although the C++ API does). Therefore, we will create 2 spatization bus, one for each listener.

## Unity scene

Let's do it!

### Audiostack config

We create an empty game object and add a Audiostack Config (Add Component > Audiostack > Config).

![Alt text](../../img/multilistener_asio_unity_2.png)

We specify the path to our license key file. We also uncheck "Follow Unity Settings" to specify our own buffer length (512 in our case). 

### Listeners

Lets create two game objects representing our listeners. On each listener, we add an Asio Output (Add Component > Audiostack > Outputs > Soundcards > ASIO).

We choose the driver corresponding to the soundcard we want to use, in my case "Focusrite USB 2.0 Audio Driver", we ask for 2 output channels, and finally choose hardware channels.

Since we will produce binaural output, we need 2 channels per listener.

Finally, we give a different name to each Asio Output, for instance "listener1" and "listener2".

![Alt text](../../img/multilistener_asio_unity_3.png)


### Binaural renderer

On new game objects, lets create two buses.

For each bus:
* name it (name must be unique)
* connect it to one listener
* add a gain effect (Add Component > Audiostack > Effects > Gain)
* add a binaural effect (Add Component > Audiostack > Effects > Binaural spatialization)

![Alt text](../../img/multilistener_asio_unity_4.png)

### Audio source

Finally, we add a basic Audiostack audio source: the "Hello input". This input welcomes you into Audiostack :)

Don't forget to connect this source to both our buses.

![Alt text](../../img/multilistener_asio_unity_5.png)


### Play!

Hit play! If your outputs are connected to headphones, you will now hear spatialized audio.

If you move listeners and source, you will notice that each listener is getting a different rendering depending on positions and rotations.

For further support, please contact us at dev[at]aspic[dot]tech!