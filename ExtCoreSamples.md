---
title: Core samples
permalink: /audiostack/ExtCoreSamples/
---


## Hello world

Our favorite test, it probably is the simplest test with Audiostack and should be used to test if the SDK is working properly.

```cpp
{% include_relative samples/Core_0_Hello.cpp %}
```


## OpenAL (mic and output)

This sample connects microphone to computer output using OpenAL drivers.

Please note this sample doesn't handle errors, please go direclty to the next sample for error handling.

```cpp
{% include_relative samples/Core_1_OpenAL.cpp %}
```

## OpenAL (mic and output) with Error handling

The previous sample doesn't catch any error, here is the sample application with error handling.


```cpp
{% include_relative samples/Core_1_OpenAL_Error.cpp %}
```

## Gain

```cpp
{% include_relative samples/Core_2_Bus2D_Gain.cpp %}
```

## Sound rolloff over distance

The following samples uses AttenuationEffect and introduces source and listener position modification.


```cpp
{% include_relative samples/Core_3_Attenuation.cpp %}
```