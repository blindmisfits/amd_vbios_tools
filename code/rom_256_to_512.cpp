#define _CRT_SECURE_NO_WARNINGS


#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;



#include <stdio.h>





int main(int argc, char *argv[])
{
	unsigned _int16 buf_big[262144]; // used "int" in case a check sum was needed
	char strSource[256], strDest[256];
	if (argc != 3)
	{
		puts("Usage <source_filename> <dest_filename>\nand the program concatenates 256kb");
		puts("of hex 0xff to first file and writes out as second file\n");
	}
	else
	{
		strcpy_s(strSource, argv[1]);
		strcpy_s(strDest, argv[2]);
		memset(buf_big, 0xff, sizeof(buf_big));
		ifstream fIN(strSource, ios::in | ios::binary);
		if (fIN.is_open())
		{
			fIN.read((char *)&buf_big, sizeof(buf_big)/2);
			fIN.close();
		}
		else
		{
			puts("Unable to open input file\n");
			exit(0);
		}
		ofstream fOUT(strDest, ios::out | ios::binary);
		if (fOUT.is_open())
		{
			fOUT.write((char *)&buf_big, sizeof(buf_big));
			fOUT.close();
		}
		else
		{
			puts("Unable to open output file\n");
		}
	}
}
