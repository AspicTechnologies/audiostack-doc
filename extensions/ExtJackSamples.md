---
title: JACK (virtual soundcard)
permalink: /audiostack/extensions/jack-samples/
---

JACK is a virtual sound card driver. It enables to interconnect programs audio IO together, and with real soundcards too.

You can use JACK extension and ASIO extension to address many hardware IO (eg, outputing signal to multiple listeners or array of speakers). JACK extension is only available for Unix systems.

JACK extension doc can be found [here](../jack).

1. [JACK bypass](#jack-bypass)
2. [Spatialization to JACK](#jack-spatialization)

## JACK bypass

This sample creates one mono input client and one mono output client. It is a sample bypass application.

```cpp
{% include_relative ExtJack_1_Basics.cpp %}
```

## JACK spatialization

This sample spatializes hello input for one listener. The output-jack-client must be connected to a hardware output and/or another program.

```cpp
{% include_relative ExtJack_3_Binaural.cpp %}
```