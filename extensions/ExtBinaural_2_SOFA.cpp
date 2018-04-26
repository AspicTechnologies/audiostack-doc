[...]

enum:int{helloIn=0, audioOut=1, bus, effect};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");
BinauralExtension::Load(context->impl);

// Register and load HRTFs in context
char hrtfFilename[] = "path/to/myHRTFs.sofa";
context.registerAsset("my_hrtf", 4 /* SofaAsset */);
context.loadAssetFromFile("my_hrtf", hrtfFilename);

context.createInput(helloIn, HelloInput);

context.createBus(bus);
context.createEffect(effect, bus, BinauralSpatializationAspic);

context.createOutput(audioOut, WindowsCoreAudioOutput, true);	
context.setParameter("listener/1/subject_name", "my_hrtf");	// Bind registered hrtf to this listener rendering

context.connect(helloIn, bus);
context.connect(bus, audioOut);

context.play();

char c;

do {
	std::cin >> c;
	// Move source and listener

} while(c!='q');

context.stop();

[...]