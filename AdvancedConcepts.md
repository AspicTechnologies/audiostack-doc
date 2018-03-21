---
title: Advanced concepts
permalink: /audiostack/AdvancedConcepts/
---

In this section, we cover advanced concepts of Audisotack. If you haven't already, please read the [Introduction](../Index) and maybe discover [samples](../Samples).

## Channels and subchannels

A channel is an audio signal, which may contain many subchannels. For instance, reading a mono audio file on the disk will produce a channel with one subchannel. A binaural signal is a channel with 2 subchannels.

### Channels

A wide majority of effects work differently on each channel. For instance, the gain effect enable you to apply a different gain value to each channel (= source). Therefore, you can mute a source by setting the corresponding channel gain to 0.

In most case, channels are processed individually by effects. Therefore the number of input channels is the same as output channels.

This is not the case of **mixers** : they will get many channels as input, but will output only one channel. 

### Subchannels

Diagram elements can work on several **subchannels**. Only element working on the same number of subchannels can be connected together. (ex: A mono file reader can not be connected directly to a six speakers output, you have to use a spatializer to create the 6 subchannels stream). The number of subchannels handled by each bus input is the subchannel count of the first effect of this bus. The number of subchannels handled by each bus output is the subchannel count of the last effect of this bus.

All successive inputs/effects/outputs in a processing chain must follow this **subchannel equality** rule.

### Examples

Remind that channel and subchannels are different concepts. For example, a StereoMixer will take many stereo channel as input, and output on stereo channel. Channels are independant audio signals, Subchannel count holds the layout inside a channel.



The diagram below display hints about channel and subchannel layouts.
[![Alt text](../img/channels_1.png)](../img/channels_1.png)
In this diagram, all inputs provide mono signals. The 3D bus spatialize two mono signals to create two stereo (binaural) signals. The 2D bus apply a filter on two mono signals, then a signal splitter transforms these two mono signals into two stereo signals. Finally, buses outputs are plugged into a stereo output.

[![Alt text](../img/channels_2.png)](../img/channels_2.png)
This second diagram features a bi-listener 3D bus. This bus has 2 inputs and 2 outputs, enabling audio sources to be spatialized differently for each listener.

## Parameters

Inputs, Outputs and Effects may own parameters. Parameters enable you to tune audio processing. Typical parameters are buffer size, gain or 3D object positions. Parameters are defined by an address and a type (such as float, bool, vec3).

Addresses are strings of the form  `input/ID/file` or `effect/ID/gain`. 

### Runtime or instanciation?

We consider two types of parameters on IO and effects:
* Runtime parameters: you can modify them at anytime (ex: gain, position, rotation, ...)
* Instanciation parameters: you can modify/set them on an IO/effect only before ending the transaction that creates it.

### Multivaluation

Many parameters defined on effects may be multivalued. A gain effect, for instance, will declare a `gain` parameter holding N values, where N is the number of channels reaching this effect input. In this example, gain parameter addresses will be `effect/ID/gain/0`, `effect/ID/gain/1`, `effect/ID/gain/2`, etc.

Another example of multivalued parameter is the position of sources and listeners, usefull in spatialization effects. 

You will see below that parameter mapping helps you address parameters.

#### Mapping

In diagram with many effects, inputs and outputs, it may become complicated to modify parameter values.

To ease the modification of parameters, it is possible to **map** parameters together. This concept may be seen as creating references between addresses. For instance, you can map `input/ID/buffer_size` for all you inputs to `application/buffer_size`. Therefore, you only have to set `application/buffer_size` to modify all you input size at once. The string `application/buffer_size` is called a **pattern**.

Audiostack automatically maps a lot of parameters for you. Our previous example (buffer_size) is mapped on all inputs, effects and outputs to ease your life.

In most situtations, you won't have to map any parameter on your own. 

### Variables

Sometime, you will need to combine multivaluation and mapping, for instance when moving sources and listeners. If you spatialize 2 audio sources, spatialization effect will own the multivalued param called `effect/ID/source_position/`. It may then be difficult to properly address them combining the input ids and the channel id in the effect. 

To simplify this process, define a **variable** `src_id` on your inputs, then map the `source_position` parameter to use a **pattern**.

Example :
```cpp
setVariable(sourceA,"src_id",10);
setVariable(sourceB,"src_id",12);

setPattern(mySpatEffect, "source_position", "source/%src_id/position");
```

This will generate the parameters below and map old address to the new ones.
```console
effect/ID/source_position/0 => source/10/position
effect/ID/source_position/1 => source/12/position
```

This typical variables mapping job **is done by default** to simplify diagram building.

### Commands and callbacks

There exists an alternative to parameters to send and receive event to and from Inputs, Outputs and Effects. Commands are used to send events while callbacks are used to receive events from Inputs, Outputs and Effects.

Severals arguments can be sent to commands or received from callbacks. The available commands and callbacks, and the arguments are described in each Inputs, Outputs and Effects documentation.

Commands and callbacks are based on the same addressing mechanism described for parameters. They can be mapped with pattern the same way.

The input that is able to read an audio file is a typical example of the use of command and callbacks. You can in fact call the command ```play()```, ```stop()``` or ```seek(int _position)```. There also exists a callback named ```at_end``` that signals when the end of the file is reached.

## Life of diagram and transactions

When you create a Diagram, it is empty. You can modify the diagram, even after play() has been called. However, once the Diagram is playing, you have to use transactions to modify the diagram: begin a transaction, add/remove/connect anything you want, end the transaction. Your modifications will be applied with transaction's end. 

Please note that setting runtime parameters does not require transaction enclosing.

### Conclusion
 
Aspic Audisotack may handle tricky concepts, but most of them have default behavior to ease library use. We advise the reader to start with code [samples](../Samples) provided with this doc to quickly become operational.

