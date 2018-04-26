---
title: RTP (streaming & collaboration)
permalink: /audiostack/extensions/ExtRTPSamples/
---

RTP extension contains inputs and outputs to send/receive audio to/from the network. You can use it to create collaborative VR app (spatialized voice chat), or stream audio from server to clients.

RTP extension doc can be found [here](../ExtRTP).

1. [Stream and listen to microphone](#microphone-stream-and-listen)

## Microphone stream and listen

The following code captures the microphone, sends it to localhost, reads it back and outputs final audio on the soundcard. With little modifications, it is possible to create collaborative audio application.

Please note this sample doesn't handle errors for code clarity.

```cpp
{% include_relative ExtRTP_1_Basics.cpp %}
```

