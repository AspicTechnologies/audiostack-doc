[...]

enum{file, bus, ambToBinaural, coreOut};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");

// Read a HOA3 file (16 sub-channels)
context.createInput(file,SyncAudioFileReader,0,0,16);
context.setParameter("sync_source/0/file", "path/to/hoa3_file.wav");
context.setParameter("sync_source/0/loop", true);
context.setParameter("sync_source/0/start_on_awake", true);
context.setParameter("sync_source/0/nb_channel",16);

context.createBus(bus);

// Load plugin interface features
PluginInterface::Load(context.impl);

// Load your plugin and create an effect it contains
AudiostackPlugin plugin(context,"AmbisonicsSkeletonPlugin.dll");
context.createEffect(ambToBinaural,bus, UserEffect, plugin.impl,0);

context.createOutput(coreOut,WindowsCoreAudioOutput,true);

context.connect(file, bus);
context.connect(bus, coreOut);

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
	context.setParameter("listener/3/rotation",listRot);

}while(c != 'x');

context.stop();

[...]