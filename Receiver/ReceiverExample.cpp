#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
	string line = "";
	while (getline(cin, line))
	{
		if (line == "")
			break;
		cout << line << endl;
	}
  return 0;
}
