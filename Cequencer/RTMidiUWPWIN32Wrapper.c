//// open midi out port 0
//

//result = gMidiOutPortOpenFunc(midiPtr, 0, &gMidiOutPort);
//if (result != WINRT_NO_ERROR)
//{
//	cout << "Unable to create Midi Out port" << endl;
//	goto cleanup;
//}
//
//// send a note on message to the midi out port
//unsigned char buffer[3] = { 144, 60 , 127 };
//cout << "Sending Note On to midi output port 0" << endl;
//gMidiOutPortSendFunc(gMidiOutPort, buffer, 3);
//
//Sleep(500);
//
//// send a note off message to the midi out port
//cout << "Sending Note Off to midi output port 0" << endl;
//buffer[0] = 128;
//gMidiOutPortSendFunc(gMidiOutPort, buffer, 3);