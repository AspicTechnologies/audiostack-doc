[...]

enum:int{hello=0,asioOut1=1,asioOut2=2,bus,spatEffect);

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");
AsioInterface::Load(context->impl);

context.createInput(hello,HelloInput);
context.createOutput(asioOut1,AsioOutput,"DRIVER_NAME:OUT1_NAME,OUT2_NAME");
context.createOutput(asioOut2,AsioOutput,"DRIVER_NAME:OUT3_NAME,OUT4_NAME");
// Use Asio Inspector provided with our installer to get the name of your asio driver and outputs

context.createBus(bus);
context.createEffect(spatEffect,bus,BinauralSpatializationAspic);
context.setLastEffectCount(bus,2);
// We force this bus to output 2 separate outputs. Each output is stereo (thanks to binaural spat).

context.connect(hello, "out",bus,"in_0");
context.connect(hello, "out",bus,"in_1");
context.connect(bus,"out_0",asioOut1,"in");
context.connect(bus,"out_1",asioOut2,"in");
// Since our bus holds 2 outputs and inputs, connection may use explicit naming

context.setParameter("application/buffer_size",512U);

context.play();

// Audio source starts between the two listeners. They are both looking toward the source.
float pos[] = {0.0,0.0,0.0};
float listPos[] = {-10.0,0.0,0.0};
float listRot[] = {0.0,90.0,0.0};
context.setParameter("source/0/position",pos);
context.setParameter("listener/1/position",listPos);
context.setParameter("listener/1/rotation",listRot);
listPos[0] = 10.0f;
listRot[1] = 270.0f;
context.setParameter("listener/2/position",listPos);
context.setParameter("listener/2/rotation",listRot);

char c;
do{
	std::cout<<"Press f or b to move the source. The source starts between the listeners and can be moved. Press q to exit"<<std::endl;
	std::cout<<"Current source position: "<<pos[2]<<std::endl;
	std::cin>>c;

	switch(c){
	case 'f':
		pos[2]-=1.0;
		context.setParameter("source/0/position",pos);
		break;
	case 'b':
		pos[2]+=1.0;
		context.setParameter("source/0/position",pos);
		break;
	}
}while(c!='q');

context.stop();

[...]