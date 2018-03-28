---
title: Plugin API (custom algorithms)
permalink: /audiostack/extensions/PluginAPISamples/
---




## HOA to binaural

In this sample, we will create a user effect that takes third order ambisonics and outputs binaural. 

For clarity, the effect implementation will only be a blueprint. You have learned above that we will process in two steps:
- first, create a plugin: a small dynamic library containing your effect(s)
- then, create an Audiostack app that will load this plugin and access its effect(s)

### Create a plugin

- inherit from aspic::audiostack::AudiostackEffect
- specify in and out channel counts using *getSubchannelLayout*
- declare parameters (listener rotation)
- implement your decoding algorithm in *processAudio* 
- create a plugin that contains your effect

```cpp
{% include_relative PluginAPI_2_Hoa3Blueprint.cpp %}
```

### Create your Audiostack app

```cpp
{% include_relative PluginAPI_2_Hoa3Main.cpp %}
```

### Build

- Create a dynamic library with your plugin
- Install this new library in Audiostack execution folder

