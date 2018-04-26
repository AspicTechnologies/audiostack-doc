---
title: ASIO (mutli-listener, low-latency & pro soundcards)
permalink: /audiostack/extensions/ExtAsioSamples/
---

ASIO extension provides access to ASIO soundcard (physical and virtual). You can use this extension to access better latencies, output audio on many listeners, multiple speakers, send audio to network audio drivers such as Dante or AES67.

ASIO extension doc can be found [here](/doc/audiostack/Asio/).

1. [ASIO Basics](#asio-basics)
2. [Multilistener using ASIO](#multilistener-using-asio)

## ASIO Basics

This sample spatialize hello input for one listener with 2 speakers on an asio device.

```cpp
{% include_relative ExtAsio_1_Basics.cpp %}
```

<br/>

## Multilistener using ASIO

This sample spatialize hello input for two listeners on the same host. Each listener gets individualized spatialization.

```cpp
{% include_relative ExtAsio_2_Multilistener.cpp %}
```


