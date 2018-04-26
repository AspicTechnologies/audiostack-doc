[...]

enm:int{hoaFileIn=0,audioOut=1,bus,hoaDecoderEffect};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(hoaFileIn,SyncAudioFileReader,0,0,16);	// 16 channel -> 3rd order ambisonics
context.setParameter("sync_source/0/file", "path/to/hoa3.wav");
context.setParameter("sync_source/0/loop", true);
context.setParameter("sync_source/0/start_on_awake", true);
context.setParameter("sync_source/0/nb_channel",16);

context.createBus(bus);
context.createEffect(hoaDecoderEffect, bus, AmbisonicsToBinaural,"ACN_SN3D_ORDER3");

context.createOutput(audioOut,WindowsCoreAudioOutput,true);

context.connect(hoaFileIn, bus);
context.connect(bus, audioOut);

context.play();

float listRot[3];
listRot[0] = 0.0f;
listRot[1] = 0.0f;
listRot[2] = 0.0f;

char c;
do {
	std::cout<<"Press q or d to rotate listener."<<std::endl;
	std::cout<<"Press x to exit."<<std::endl;
	std::cin >> c;
	switch(c){
	case 'q':
		listRot[1] -= 5.0f;
		break;
	case 'd':
		listRot[1] += 5.0f;
		break;
	}
	context.setParameter("listener/1/rotation",listRot);

}while(c != 'x');

context.stop();

[...]