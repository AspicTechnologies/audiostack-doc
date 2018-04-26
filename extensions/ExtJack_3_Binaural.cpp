[...]

enum:int{helloId = 0, outputId = 1, busId, spatId};

// Please launch your jack daemon before running audiostack.

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");

context.createInput(helloId, HelloInput);
context.createOutput(outputId, JackOutput, 2U);                 
// Output has 2 channel, because binaural effect produces a stereo output.

context.createBus(busId);                                       
context.createEffect(spatId,busId,BinauralSpatializationAspic);

context.connect(helloId,busId);
context.connect(busId,outputId);

context.play();


context.connect(0,1);

context.play();

char c;
do{
	std::cout<<"Feel free to connect jack ports (with program such as 'qjackctl').\n\tPress q to quit."<<std::endl;
	std::cin>>c;

	// Here, move source and listener!

}while(c!='q');

context.stop();

[...]
