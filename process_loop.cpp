#include <iostream>
#include <fstream>
#include <string>
//-------------------------------
using namespace std;
//-------------------------------
const int LOOP_NO = 2;
const int QUERY_NO = 8;
//-------------------------------
int main(int argc, char *argv[])
{
	string str1, str2;
	string step;
	
	string::size_type sz;
	int loop_rec[QUERY_NO + 1][LOOP_NO];

	if (argv[1] == NULL)
	{
		cout << "need input file name prefix, end with _" << endl;
		return 0;
	}
	if (argv[2] == NULL)
	{
		cout << "need output file name prefix, end with _" << endl;
		return 0;
	}
	
	ifstream in;
	ofstream out;
	int i, j, k, l;
	int pos;
	int lineno;
	//int i_step;
	
	for (i = 0; i < LOOP_NO; ++i)
		for (j = 0; j <= QUERY_NO; ++j)
			loop_rec[j][i] = -1;
			
	for (i = 0; i < LOOP_NO; ++i)
	{
		string postfix = std::to_string(i);
		in.open((string(argv[1]) + postfix + ".txt").c_str());
		if (!in)
		{
			cout << "open file error!" << endl;
			//return 0;
			continue;
		}
		
		j = 1;
		str1 = "";
		while (in)
		{
			str2 = str1;	//last str
			getline(in, str1);	//new str
			lineno++;
			
			if (str1.find("rc = 101") != string::npos)
			{
				if (str2.find("rc = 0") != string::npos)
				{
					pos = str2.find("scanstatus = ");
					step = str2.substr(pos + 13);
					loop_rec[j][i] = std::stoi(step, &sz);
				}
				++j;
			}
		}
		in.close();
	}
	
	out.open((string(argv[2]) + "loops_summary.txt").c_str());
	for (j = 1; j <= QUERY_NO; ++j)
	{
		out << j << ": " << endl;
		for (i = 0; i < LOOP_NO; ++i)
		{
			if (loop_rec[j][i] != -1)
			{
				out << i << ":\t" << loop_rec[j][i] << endl;
			}
		}
		out << endl;
	}
	out.close();
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
