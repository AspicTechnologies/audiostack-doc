[...]

enum:int{helloId = 0,outputId = 1, busId = 2, spatId = 3};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");
NahimicExtension::Load(context->impl);	// Load extension, allows to use inputs/outputs/effects contained in the extension

context.createInput(helloId, HelloInput);
context.createOutput(outputId, OpenALOutput,true);                 
// Output is stereo, because binaural effect produces a stereo output.

context.createBus(busId);                                       
context.createEffect(spatId,busId,NahimicBinauralSpatialization);

context.connect(helloId,busId);
context.connect(busId,outputId);

float sourcePos[]   =   {0.0, 0.0, -1.0};
float listenerPos[] =   {0.0, 0.0, 1.0};
float listenerRot[] =   {0.0, 0.0, 0.0};

context.setParameter("listener/1/position",listenerPos);
context.setParameter("source/0/position",sourcePos);

context.play();

char c;
do{
	std::cout<<"Press r or l to rotate the listener, press q to exit"<<std::endl;
	std::cin>>c;
	switch(c){
	case 'l':
		listenerRot[1]-=10;
		context.setParameter("listener/1/rotation",listenerRot);
		break;
	case 'r':
		listenerRot[1]+=10;
		context.setParameter("listener/1/rotation",listenerRot);
		break;
	}
}while(c!='q');

context.stop();

[...]