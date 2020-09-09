#include<iostream>
#include<string>

using namespace std;

int main()
{
	string line = "";
	while (getline(cin, line))
	{
		if (line == "")
		{
			cout<<"Cin input over"<<endl;
			break;
		}
		cout << line << endl;
	}
  return 0;
}
