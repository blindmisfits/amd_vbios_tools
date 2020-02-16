#define _CRT_SECURE_NO_WARNINGS


#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;



#include <stdio.h>
const int wanted_size = 524288;
const int have_size = 262144;

bool DoImages = false;
// if 4th arg supplied then create bios images

int main(int argc, char *argv[])
{
	char buf_big[wanted_size]; // used "int" in case a check sum was needed
	char strSource[256], strDest[256];
	if (argc == 4)
	{
		DoImages = true;
		argc--;
	}
	if (argc != 3)
	{
		puts("Usage <source_filename> <dest_filename>\nand the program concatenates 256kb");
		puts("of hex 0xff to first file and writes out as second file");
		puts("if optional 3rd argument then create machine code bios image(s)");
	}
	else
	{
		strcpy_s(strSource, argv[1]);
		strcpy_s(strDest, argv[2]);
		memset(buf_big, 0xff, wanted_size);
		ifstream fIN(strSource, ios::in | ios::binary);
		if (fIN.is_open())
		{
			fIN.read(buf_big, have_size);
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
			fOUT.write(buf_big, wanted_size);
			fOUT.close();
		}
		else
		{
			puts("Unable to open output file\n");
		}
		if (DoImages)
		{
			int nImages = 0;
			int iPtr = 0;
			while (1)
			{
				unsigned int iVal;
				int iSize;	// size of image
				int iSig = 0xaa55;
				int jSig = 0;
				char *ch = (char *)&jSig;
				*ch = buf_big[iPtr];
				ch++;
				*ch = buf_big[iPtr + 1];
				if (jSig == iSig)
				{
					iSig = (unsigned int)buf_big[iPtr + 2];
					iSize = iSig * 512;
					iVal = buf_big[iPtr + 3] & 0xff;
					if (iVal != 0xe9)
					{
						puts("Opcode E9 not found, looking for a 0 to signal new code image\n");
						if(iVal != 0)exit(0);
					}
					ch = (char *)&jSig;
					*ch = (unsigned int)buf_big[iPtr + 4] & 0xff;
					ch++;
					*ch = (unsigned int)buf_big[iPtr + 5] & 0xff;
					jSig += 2; // opcode is 3 bytes "55 aa 74  e9 02 a1" reserved space of 1 byte so next instructon is +1 +1 or +2
					printf("Image:%d size:%d  entry point%04x\n", nImages, iSize, jSig);
					sprintf(strDest, "machine_code_image%d.hex", nImages);
					ofstream fOUT(strDest, ios::out | ios::binary);
					if (fOUT.is_open())
					{
						fOUT.write(&buf_big[iPtr], iSize); // includes null or 0xff or text as code is smaller than image
						fOUT.close();
					}
					else
					{
						puts("Unable to open output file\n");
					}
				}
				else
				{
					if (nImages == 0)
						puts("error: cannot find a bios signature\n");
					else exit(0);
				}
				nImages++;
				iPtr+= iSize; // is 
			}
		}
	}
}
