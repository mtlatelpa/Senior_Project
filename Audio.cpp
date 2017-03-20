#include "Audio.h"

Audio::Audio()
{

	//Loading in sound for Background Music
	if (!backgroundmusic1.openFromFile("Punks.wav"))
		std::cout << "Unable to load Music" << std::endl;
}

Audio::~Audio()
{
}