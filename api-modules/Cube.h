#pragma once
class Cube
{
public:
	Cube();
	~Cube();
	char* Alias;

	void setAlias(char*);
	char* getAlias();
	void SimplePrint(char*);
	void setBGColor(char*);
};

