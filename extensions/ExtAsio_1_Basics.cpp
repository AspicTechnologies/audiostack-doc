[...]

enm:int{hello=0,asioOut=1,bus,spatEffect};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");
AsioInterface::Load(context->impl);

context.createInput(hello,HelloInput);
context.createOutput(asioOut,AsioOutput,"DRIVER_NAME:OUT1_NAME,OUT2_NAME");
// Use Asio Inspector provided with our installer to get the name of your asio driver and outputs

context.createBus(bus);
context.createEffect(spatEffect,bus,BinauralSpatializationAspic);

context.connect(hello, bus);
context.connect(bus,asioOut);

context.setParameter("application/buffer_size",512U);

context.play();

float sourcePos[]   =   {0.0, 0.0, -1.0};
float listenerPos[] =   {0.0, 0.0, 1.0};
float listenerRot[] =   {0.0, 0.0, 0.0};
context.setParameter("listener/1/position",listenerPos);
context.setParameter("source/0/position",sourcePos);

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