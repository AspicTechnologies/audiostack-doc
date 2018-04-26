---
title: Ambisonics (rendering, encoding)
permalink: /audiostack/extensions/ambisonics-samples/
---

This extension handles ambisoncis streams: encoding, decoding, conversions.

Extension doc can be found [here](/doc/audiostack/extensions/Ambisonics/).

1. [Ambisonics to Binaural](#ambisonics-to-binaural)
2. [Ambisonics encoding to ASIO streaming](#ambisonics-encoding-and-asio-streaming)

## Ambisonics to Binaural

This sample renders an ambisonics stream in binaural.

```cpp
{% include_relative ExtAmbisonics_1_HOAToBinaural.cpp %}
```

<br/>

## Ambisonics encoding and ASIO streaming

This sample encodes a hello input into ambisonics, and outputs this ambisonics to an ASIO driver (for instance to stream to an external decoding system).

```cpp
{% include_relative ExtAmbisonics_2_ObjectToAmbToAsio.cpp %}
```


