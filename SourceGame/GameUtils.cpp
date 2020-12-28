#include<fstream>
#include<string>
using namespace std;
void ignoreLineIfstream(ifstream& fs, int lineCount)
{
	string s;
	for (int i = 0; i < lineCount; i++)
	{
		std::getline(fs, s);
	}
}

int readLineCount(const char* filename)
{
	int numLines = 0;
	ifstream in(filename);
	//while ( ! in.eof() )
	while (in.good())
	{
		std::string line;
		std::getline(in, line);
		++numLines;
	}

	return numLines;
}
