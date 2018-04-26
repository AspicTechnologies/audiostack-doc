[...]

enm:int{helloIn=0,asioOut=1,bus,hoaEncoderEffect};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(helloIn,HelloInput);

context.createBus(bus);
context.createEffect(hoaEncoderEffect, bus, AmbisonicsEncoder,"ACN_SN3D_ORDER3");

context.createOutput(asioOut,AsioOutput,"DRIVERNAME:OUT 1,OUT 2,OUT 3,[...]");	// 16 channel output to stream HOA

context.connect(helloIn, bus);
context.connect(bus, asioOut);

context.play();

do {
	std::cin >> c;
	switch(c){
		// move source and listener with patterns "source/0/position" and "listener/1/position"
	}

}while(c != 'x');

context.stop();

[...]