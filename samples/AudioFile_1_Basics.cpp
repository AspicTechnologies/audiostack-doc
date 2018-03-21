[...]


enum:int{fileId = 0,outputId};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");
CoreAudioFileExtension::Load(context->impl);	// Load extension, allows to use inputs/outputs and helpers contained in the extension

context.createInput(fileId,AudioFileReader,"FILE.wav");
// file is a mono, 48kHz/16bits wav file located on disk
// OR context.createInput(0,AudioFileReader,"KEY") if in server
context.createOutput(outputId,OpenALOutput,false);
// Output is mono, in order to accept mono file.

context.setParameter("source/0/loop",true);             // file will play in loop
context.setParameter("source/0/start_on_awake",true);   // start file reading automatically

context.connect(fileId,outputId);

context.play();

char c;
do{
	std::cout<<"Press r to play, p to pause and s to stop. Press q to quit."<<std::endl;
	std::cin>>c;

	switch(c){
	case 'r':
		context.sendCommand("source/0/play");
		break;

	case 'p':
		context.sendCommand("source/0/pause");
		break;

	case 's':
		context.sendCommand("source/0/stop");
		break;
	}
}while(c!='q');

context.stop();

[...]