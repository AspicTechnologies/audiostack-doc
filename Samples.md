---
title: Code samples
permalink: /audiostack/Samples/
---

Here is our simplest Hello world sample

```cpp
{% include_relative samples/Core_0_Hello_v2.cpp %}
```

### Extension specific samples

Each API Extension section contains samples, however, you can also use this list to direclty jump to specific samples:

- [Core samples](../ExtCoreSamples)
- [Audio file samples](../ExtAudioFileSamples)
- [Binaural samples](../ExtBinauralSamples)
- [Nahimic samples](../ExtNahimicSamples)
- [ASIO samples](../extensions/ExtAsioSamples)
- [VBAP samples](../ExtVBAPSamples)
- *[OSC samples](../ExtOSCSamples)*

### Error handling

A wide majority of code samples in this documentation does not include any error handling, for readability.

The following sample detects context errors and provides exceptions.

```cpp
{% include_relative samples/Error.cpp %}
```