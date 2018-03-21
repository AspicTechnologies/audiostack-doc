---
title: Audio file samples
permalink: /audiostack/ExtAudioFileSamples/
---



## AudioFile simple application

This sample connects an audio file reader to computer output using OpenAL drivers.

Please note this sample doesn't handle errors for code clarity.

```cpp
{% include_relative samples/AudioFile_1_Basics.cpp %}
```

## AudioFile callbacks

This sample provides hints to use callbacks on file reader.

In this use case, the application stops once the file reading reaches end of file.

```cpp
{% include_relative samples/AudioFile_2_Callback.cpp %}
```
