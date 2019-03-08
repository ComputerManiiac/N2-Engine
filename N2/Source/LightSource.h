#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

class LightSource
{
public:
	LightSource();

	~LightSource();
	
private:
	unsigned int id;
	static unsigned int count;
};

#endif