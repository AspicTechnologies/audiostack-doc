---
title: VBAP (multi speaker spatialization)
permalink: /audiostack/extensions/vbap-samples/
---

VBAP extension provides effects for spatialization over multiple speaker. The effects of this module will apply the appropriate gain on all speakers to perceive sound from the correct direction. This extension also handles delay and frequency corrections to ensure a smooth rendering.

VBAP extension doc can be found [here](../../VBAP).

1. [VBAP spatialization](#vbap-spatialization-sample)

## VBAP spatialization sample

This sample spatialize hello input for one listener with 4 speakers. Audio output is achieved with jack but could rely on ASIO with a slightly different code. 

```cpp
{% include_relative ExtVBAP_1_Basics.cpp %}
```
