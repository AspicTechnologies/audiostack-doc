[...]

enum:int{helloId = 0, outputId = 1, busId, gainId};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(helloId, HelloInput);
context.createOutput(outputId, WindowsCoreAudioOutput,true);					
// We use a stereo output

context.createBus(busId);										

context.createEffect(gainId, busId, MultiChannelSimpleGain,(unsigned int)2);	
// We add a gain with the ability to split the signal in 2 subchannels

context.connect(helloId,busId);									
context.connect(busId,outputId);								
// Connections are matching, because subchannel equality rule is observed

context.play();

context.setParameter("source/0/gain",0.5f);
context.setParameter("source/0/mute",true);

[...]