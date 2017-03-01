#include "Mapping.h"
#include <fstream>
#include <iostream>
using namespace std;

void Mapping::mapping()
{
	ofstream outFile;

	outFile.open("map.txt");

	int k = 0;

	outFile << 32 << " " << 32 << endl;

	int x = 0, y = 0;

	for (y = 0; y < 32; y++)
	{
		for ( x = 0; x < 32; x++)
		{
			k = 0;
			if (y == 0 && (11 <= x && x <= 18))
				k = 1;
			if (y == 1 && ((x == 11) || (x == 18) || (21 <= x && x <= 24)))
				k = 1;
			if (y == 2 && ((x==18) || (x==24)) )
				k = 1;
			if (y == 3 && (x==24))
				k = 1;
			if (y == 4 && (x==11 || x==15 || x==24))
				k = 1;
			if (y == 5 && (x == 11 || x == 15 || x == 24))
				k = 1;
			if (y == 6 && ((0 <= x && x <= 19) || (22 <= x && x <= 24)) )
				k = 1;
			if (y == 7 && ((0 <= x && x <= 19) || (22 <= x && x <=31)) )
				k = 1;
			if ((8 <= y && y <= 10) && (x == 0))
				k = 1;
			if ((11 <= y && y <= 12) && (x == 0 || (3 <= x && x <= 18)) )
				k = 1;
			if ((y == 13) && (x == 0))
				k = 1;
			if ((14 <= y && y <= 15) && (25 <= x && x <= 31))
				k = 1;
			if ((y == 16) && (x == 0 || x == 25) )
				k = 1;
			if ((17 <= y && y <= 18) && ((0 <= x && x <= 4) || (8 <= x && x <= 19) || (x == 25)) )
				k = 1;
			if ((19 <= y && y <= 20) && ((x == 0) || (x==11) || (x==12) || (x==25)) )
				k = 1;
			if ((21 <= y && y <= 22) && ((x == 0) || (x == 11) || (x == 12) || (x == 25) || (30 <= x && x <= 31)))
				k = 1;
			if ((21 <= y && y <= 22) && ((x == 0) || (x == 11) || (x == 12) || (x == 25) || (30 <= x && x <= 31)))
				k = 1;
			if ((23 <= y && y <= 27) && ((x == 0)) )
				k = 1;
			if ((28 <= y && y <= 29) && ((x == 0) || (25 <= x && x <= 31)))
				k = 1;
			if ((30 <= y && y <= 31) && ((x == 0)) )
				k = 1;
			outFile << x << " " << y << " " << k << endl;
		}
	}

	outFile.close();

}


Mapping::Mapping()
{
}


Mapping::~Mapping()
{
}
