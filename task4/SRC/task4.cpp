#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3) return -1;
	
	for (int i = 0, j = 0; i <= strlen(argv[1]) && j <= strlen(argv[2]); ++i, ++j)
	{
		if (argv[2][j] == '*')
		{
			//Skip '*' in argv[2]
			while (argv[2][j] == '*')
				j++;
			if (argv[2][j] == '\0')
			{
				cout << "OK" << endl;
				return 0;
			}
			while (argv[1][i] != argv[2][j])
			{
				i++;
				if(argv[1][i] == '\0')
				{
					cout<<"KO"<<endl;
					return -1;
				}
			}
		}
		if (argv[1][i] != argv[2][j])
		{
			cout << "KO" << endl;
			return -1;
		}
		if (argv[1][i] == '\0' && argv[2][j] == '\0')
		{
			cout << "OK" << endl;
			return 0;
		}
	}
	cout << "What??" << endl;
	return 0;
}
