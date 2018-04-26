---
title: Binaural rendering (w Sofa)
permalink: /audiostack/ExtBinauralSamples/
---

Binaural extension provides effects for binaural spatialization.

Binaural extension doc is [here](../Binaural).

1. [Simple binaural spatialization](#binaural-spatialization-sample)
2. [Custom HRTF based on SOFA](#custom-hrtf-w-sofa)

## Binaural spatialization sample

This sample spatialize audio for one listener.

For multilistener samples, please see Asio Extension samples, since they enable multi-output rendering.

```cpp
{% include_relative samples/Binaural_1_Basics.cpp %}
```

## Custom HRTF w. SOFA

This sample loads a personalized HRTF file using SOFA and then renders binaural with your own HRTFs.


```cpp
{% include_relative extensions/ExtBinaural_2_SOFA.cpp %}
```
