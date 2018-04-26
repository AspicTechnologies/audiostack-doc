---
title: User documentation
permalink: /audiostack/Index/
---

Introduction
-----
*Aspic Audiostack* is a software toolkit providing features to easily create rich audio applications. The toolkit is composed of core features and extensions.

Several plugins and wrappers easing software integration are available.

The benefits of *Aspic Audiostack* is its effective way to declare audio inputs, outputs and effects and route audio signal in-between.

{% icon fa-exclamation-triangle  %} We are currently working on Audiostack doc. Some sections may be incomplete. {% icon fa-exclamation-triangle  %}

Basic concepts
-----

Lets meet one major concept of *Audiostack*: diagrams. Diagrams are a representation of the application sound routing process.

### Input, output and bus

Sound signals are produced by **inputs** and travel along links through the diagram to reach one or more **outputs**. Inputs and outputs can be of various types (audio files, audio over IP, professionnal and mainstream sound cards, ...).

A **bus** is the representation of a collection of effects. All elements connected to a bus input are processed by the effects of this bus (from left to right). 

A sample diagram is displayed below:
[![Alt text](../img/diagram.png)](../img/diagram.png)


Next step
-----
What now? 

We advise you to jump to sections matching your use of Audiostack, such as:
* [C/C++ API Guide](../AudiostackAPI)
* Plugins

However, at some point you will have to understand deeper concepts, such as channels/subchannels, variables, mapping, ... If you want to read it now, go to [Advanced concepts section](../AdvancedConcepts).

