[...]

enum:int{helloId = 0, outputId = 1, busId, attenuationId};

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(helloId, HelloInput);
context.createOutput(outputId, WindowsCoreAudioOutput,false);
// We use a mono output

context.createBus(busId);                                       
context.createEffect(attenuationId,busId,AttenuationEffect,0U,1U);
// Effect apply a linear attenuation on mono channels.

context.connect(helloId,busId);                                   
context.connect(busId,outputId);        

float sourcePos[] = {0.0, 0.0, -1.0};
context.setParameter("source/0/position",sourcePos);
// The variable %src_id on our Input is automatically set, therefore we can use it in patterns on connected effects

float listenerPos[] = {0.0, 0.0, 0.0};
context.setParameter("listener/1/position",listenerPos);
// The variable %list_id on our Output is automatically set, therefore we can use it in patterns on connected effects

context.play();

char c;
do{
	std::cout<<"Press f or b to move the source forward/backward. Press q to quit."<<std::endl;
	std::cin>>c;

	switch(c){
	case 'f':
		sourcePos[2]-=1.0;
		context.setParameter("source/0/position",sourcePos);
		break;
	case 'b':
		sourcePos[2]+=1.0;
		context.setParameter("source/0/position",sourcePos);
		break;
	}
}while(c!='q');

context.stop();
		
[...]