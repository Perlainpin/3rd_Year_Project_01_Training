#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>


int main()
{
	if (fopen("color_modif.bmp", "rb") != NULL)
	{
		remove("color_modif.bmp");
	}
	if (fopen("BMP_modif.bmp", "rb") != NULL)
	{
		remove("BMP_modif.bmp");
	}	

	//FILE* pFile = LoadFile("color.bmp");

	FILE* pFile =  fopen("color.bmp", "rb");

	if (pFile == NULL)
	{
		std::cout << "file not loaded\n";
		fclose(pFile);
		return 0;
	}

	long lSize;
	byte* buffer;
	size_t result;

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	buffer = new byte[lSize];
	if (buffer == NULL)
	{
		std::cout << "Memory error\n";
		fclose(pFile);
		free(buffer);
		return 0;
	}

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		std::cout << "Reading error\n";
		fclose(pFile);
		free(buffer);
		return 0;
	}

	fclose(pFile);

	//std::cout << "buffer :" << buffer << "\n";

	tagBITMAPFILEHEADER fileHeader;
	memcpy(&fileHeader, buffer, sizeof(tagBITMAPFILEHEADER));

	tagBITMAPINFOHEADER infoHeader;
	memcpy(&infoHeader, buffer + sizeof(tagBITMAPFILEHEADER), sizeof(tagBITMAPINFOHEADER));
	infoHeader.biSizeImage = infoHeader.biWidth * abs(infoHeader.biHeight) * 3;

	//std::cout << "size :" << infoheader.biWidth << " X " << infoheader.biHeight << "\n";

	byte* bgr = buffer + sizeof(tagBITMAPFILEHEADER) + sizeof(tagBITMAPINFOHEADER);

	/*
	for (int i = 0; i < lSize; ++i) {

		std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)(unsigned char)bgr[i] << " ";

		if ( (i+1 ) % 3 == 0) {
			std::cout << " | ";
		}
		if ((i + 1) % 48 == 0) {
			std::cout <<  std::endl;
		}

	}
	*/

	
	// Modifier certains pixels(exemple : passer au negatif de l'image)
	for (int y = 0; y < infoHeader.biHeight; ++y) {
		for (int x = 0; x < infoHeader.biWidth; ++x) {
			int pixelIndex = (y * infoHeader.biWidth + x) * 3; // 3 car on a 3 octets par pixel (BGR)

			bgr[pixelIndex] = 255 - bgr[pixelIndex];
			bgr[pixelIndex + 1] = 255 - bgr[pixelIndex + 1];
			bgr[pixelIndex + 2] = 255 - bgr[pixelIndex + 2];
				
		}
	}

	FILE* pNewFile;

	std::string modifiedFilename = "modified_" + std::string("color.bmp");
	const char* newFilename = modifiedFilename.c_str();

	pNewFile = fopen(newFilename, "wb");
	if (pNewFile == NULL)
	{
		std::cout << "file not created\n";
		fclose(pNewFile);
	}

	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pNewFile);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pNewFile);

	fwrite(bgr, 1, infoHeader.biSizeImage, pNewFile);

	free(buffer);
	return 0;
}
/*
FILE* LoadFile(const char* Filename)
{
	return fopen(Filename, "rb");
}

void SaveFile(const char* Filename, byte* buffer)
{
	FILE* pNewFile;

	std::string modifiedFilename = "modified_" + std::string(Filename);
	const char* newFilename = modifiedFilename.c_str();

	pNewFile = fopen(newFilename, "wb");
	if (pNewFile == NULL)
	{
		std::cout << "file not created\n";
		fclose(pNewFile);
	}
}

void WriteFile(FILE* File, tagBITMAPFILEHEADER fileHeader, tagBITMAPINFOHEADER infoHeader, byte* bgr)
{
	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, File);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, File);

	fwrite(bgr, 1, infoHeader.biSizeImage, File);
}

void ReadFile()
{
	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	buffer = new byte[lSize];
	if (buffer == NULL)
	{
		std::cout << "Memory error\n";
		fclose(pFile);
		free(buffer);
		return 0;
	}

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		std::cout << "Reading error\n";
		fclose(pFile);
		free(buffer);
		return 0;
	}

	fclose(pFile);
}
*/