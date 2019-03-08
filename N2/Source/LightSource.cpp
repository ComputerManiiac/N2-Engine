#include "LightSource.h"


unsigned int LightSource::count = 0;

LightSource::LightSource()
{
	id = count++;
}


LightSource::~LightSource()
{
}
