#include<iostream>
#include<string>
#include <cmath>
#include <fstream>
#include <unistd.h>

using namespace std;
struct Header 
{    
char  idLength;
char  colorMapType;
char  dataTypeCode;
short colorMapOrigin;
short colorMapLength;
char  colorMapDepth;
short xOrigin;
short yOrigin;
short width;    
short height;
char  bitsPerPixel;
char  imageDescriptor; 
};

struct Pixels 
{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
    
};
//Header headerObject,headerObject1;
		
class PicturesData
{
	private:
		int Size;
		unsigned char Red;
		unsigned char Green;
		unsigned char Blue;
		Header headerObject;
		ifstream file;
		
	public:
		//Reading the Header and then Pixels

		void OpenFile(string FileName)
		{
		//circles.tga
		//car.tga
		
		file.open(FileName.c_str(), ios::binary | ios::ate );//| ios::ate
	
			if(file.fail())
			{
		    	std::cout<<" could not be opened."<<std::endl;
			}	
		}
		
	void ReaderHeader()
	{
		//Header 
		
		file.seekg(0, ios::beg);
		file.read(&headerObject.idLength, 1);
		file.read(&headerObject.colorMapType, 1); 
		file.read(&headerObject.dataTypeCode, 1); 
		file.read((char *)&headerObject.colorMapOrigin, 2); 
		file.read((char *)&headerObject.colorMapLength, 2);
		file.read(&headerObject.colorMapDepth, 1);
		file.read((char *)&headerObject.xOrigin , 2);
		file.read((char *)&headerObject.yOrigin , 2);
		file.read((char *)&headerObject.width , 2);
		file.read((char *)&headerObject.height , 2);
		file.read(&headerObject.bitsPerPixel , 1);
		file.read(&headerObject.imageDescriptor , 1);
		
		
		
	}
	
	void GetPixel()
	{
		//RGB Blue, Green and then Red. That's how they are stored in Binary
		
		file.read((char *)&Blue , 1);	
		file.read((char *)&Green , 1);	
		file.read((char *)&Red, 1);
		
		if(file.eof())
		{
			file.close();
		}
		
	}
	
	void printerHeader()
	{
			
		cout<<"Here"<<endl;
		cout<<int(headerObject.idLength)<<endl;
		cout<<int(headerObject.colorMapType)<<endl;
		cout<<int(headerObject.dataTypeCode)<<endl;
		cout<<int(headerObject.colorMapOrigin)<<endl;
		cout<<int(headerObject.colorMapLength)<<endl;
		cout<<int(headerObject.colorMapDepth)<<endl;
		cout<<int(headerObject.xOrigin)<<endl;
		cout<<int(headerObject.yOrigin)<<endl;
		cout<<int(headerObject.width)<<endl;
		cout<<int(headerObject.height)<<endl;
		cout<<int(headerObject.bitsPerPixel)<<endl;
		cout<<int(headerObject.imageDescriptor)<<endl;
		cout<<"Ends";
		
	}
	
	int GetSize()
	{
		int Size=headerObject.width*headerObject.height;
		return Size;
	}
	struct Header getHeader()
	{
		return headerObject;
	}
	
	float getRedPixel()
	{
		return this->Red;
	}
	
	float getGreenPixel()
	{
		return this->Green;
	}
	
	float getBluePixel()
	{
		return this->Blue;
	}
};

class ResultantPicture
{
	private:
		int Size;
		unsigned char Red;
		unsigned char Green;
		unsigned char Blue;
		Header headerObject;
		ofstream file;
		
	public:
		
		void openFile(string FileName)
		{
			//circles.tga
			//car.tga
			file.open(FileName.c_str(), ios::binary | ios::out );//| ios::ate
		
			if(file.fail())
				{
			    	std::cout<<" could not be opened."<<std::endl;
				}	
				
		}
		
	void WriterHeader(struct Header myHeader)
	{
		Header ThisHeader=myHeader;
		
		file.write(&ThisHeader.idLength, 1);
		file.write(&ThisHeader.colorMapType, 1); 
		file.write(&ThisHeader.dataTypeCode, 1); 
		file.write((char *)&ThisHeader.colorMapOrigin, 2); 
		file.write((char *)&ThisHeader.colorMapLength, 2);
		file.write(&ThisHeader.colorMapDepth, 1);
		file.write((char *)&ThisHeader.xOrigin , 2);
		file.write((char *)&ThisHeader.yOrigin , 2);
		file.write((char *)&ThisHeader.width , 2);
		file.write((char *)&ThisHeader.height , 2);
		file.write(&ThisHeader.bitsPerPixel , 1);
		file.write(&ThisHeader.imageDescriptor , 1);
		
	}
	
	void CloseFile()
	{
		file.close();
	}
	
	void WritePixels(unsigned char Red,unsigned char Green,unsigned char Blue)
	{		
			//RGB
			file.write((char *)&Blue , 1);
			file.write((char *)&Green , 1);
			file.write((char *)&Red , 1);
	}
		
};


int clamp(float value)
{
	if(value<0)
	{
		value=0;
	}
	else if(value>255)
	{
		value=255;
	}
	return value;
}


float OverlayConditionOne(float UpperLayerValue, float LowerLayerValue )
{
	float ValueUnit = (255-LowerLayerValue)/127.5;

	float MinValue = LowerLayerValue - (255-LowerLayerValue);

	float Overlay = (UpperLayerValue * ValueUnit) + MinValue;
	
	return Overlay;
}
float OverlayConditionTwo(float UpperLayerValue, float LowerLayerValue )
{
	float ValueUnit=LowerLayerValue/127.5;

	float Overlay = UpperLayerValue * ValueUnit;
	
	return Overlay;
}



int main()
{
	//chdir("../");
	
	PicturesData Picture1,Picture2,Picture3;

	////////////////////////////////////Task 01	
	//Picture1 
	Picture1.OpenFile("input/layer1.tga");
	Picture1.ReaderHeader();
	//Picture1.printerHeader();
	
	//Picture2
	Picture2.OpenFile("input/pattern1.tga");
	Picture2.ReaderHeader();
	//Picture2.printerHeader();
	
	
	ResultantPicture ResPicture;
	ResPicture.openFile("output/part1.tga");
	ResPicture.WriterHeader(Picture1.getHeader());
	int Size=Picture1.GetSize();
	
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		Picture2.GetPixel();
		
		float Blue = ((Picture1.getBluePixel()*Picture2.getBluePixel())/255)+0.5f;
		float Green = ((Picture1.getGreenPixel()*Picture2.getGreenPixel())/255)+0.5f;
		float Red = ((Picture1.getRedPixel()*Picture2.getRedPixel())/255)+0.5f;
		
		
		Blue=trunc(Blue);
		Green=trunc(Green);
		Red=trunc(Red);
		
		ResPicture.WritePixels(Red,Green,Blue);
		
	}
	
	ResPicture.CloseFile();
	
	
	////////////////////////////////////Task 02	
	
	//Picture1 
	Picture1.OpenFile("input/layer2.tga");
	Picture1.ReaderHeader();
	//Picture1.printerHeader();
	
	//Picture2
	Picture2.OpenFile("input/car.tga");
	Picture2.ReaderHeader();
	//Picture2.printerHeader();
	
	
	ResultantPicture ResPicture1;
	ResPicture1.openFile("output/part2.tga");
	ResPicture1.WriterHeader(Picture1.getHeader());
	Size=Picture1.GetSize();
	
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		Picture2.GetPixel();
		int Blue = ((Picture2.getBluePixel()-Picture1.getBluePixel()));
		int Green = ((Picture2.getGreenPixel()-Picture1.getGreenPixel()));
		int Red = ((Picture2.getRedPixel()-Picture1.getRedPixel()));
		
		Blue=clamp(Blue);
		Green=clamp(Green);
		Red=clamp(Red);
		
		ResPicture1.WritePixels(Red,Green,Blue);
	}
	ResPicture1.CloseFile();
	
	
	////////////////////////////////////Task 03
	//Picture1 
	Picture1.OpenFile("input/layer1.tga");
	Picture1.ReaderHeader();
	//Picture1.printerHeader();
	
	//Picture2
	Picture2.OpenFile("input/pattern2.tga");
	Picture2.ReaderHeader();
	//Picture2.printerHeader();
	
	//Picture3
	Picture3.OpenFile("input/text.tga");
	Picture3.ReaderHeader();
	//Picture3.printerHeader();
	
	ResultantPicture ResPicture2;
	ResPicture2.openFile("output/part3.tga");
	ResPicture2.WriterHeader(Picture1.getHeader());
	Size=Picture1.GetSize();
	
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		Picture2.GetPixel();
		Picture3.GetPixel();
		
		//Multiply
	
		float Blue = ((Picture1.getBluePixel()*Picture2.getBluePixel())/255)+0.5f;
		float Green = ((Picture1.getGreenPixel()*Picture2.getGreenPixel())/255)+0.5f;
		float Red = ((Picture1.getRedPixel()*Picture2.getRedPixel())/255)+0.5f;
		
		Blue=trunc(Blue);
		Green=trunc(Green);
		Red=trunc(Red);

		//Screen
	
		
		Blue = (((255-Picture3.getBluePixel())*(255-Blue)))/255;
		Green = (((255-Picture3.getGreenPixel())*(255-Green)))/255;
		Red = (((255-Picture3.getRedPixel())*(255-Red)))/255;
		
		
		Blue=255-trunc(Blue+0.5f);
		Green=255-trunc(Green+0.5f);
		Red=255-trunc(Red+0.5f);

		ResPicture2.WritePixels(Red,Green,Blue);
		
	}
	
	ResPicture2.CloseFile();
	
	////////////////////////////////////Task 04
	//Picture1 
	Picture1.OpenFile("input/layer2.tga");
	Picture1.ReaderHeader();
	//Picture1.printerHeader();
	
	//Picture2
	Picture2.OpenFile("input/circles.tga");
	Picture2.ReaderHeader();
	//Picture2.printerHeader();
	
	//Picture3
	Picture3.OpenFile("input/pattern2.tga");
	Picture3.ReaderHeader();
	//Picture3.printerHeader();
	
	ResultantPicture ResPicture3;
	ResPicture3.openFile("output/part4.tga");
	ResPicture3.WriterHeader(Picture1.getHeader());
	Size=Picture1.GetSize();
	
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		Picture2.GetPixel();
		Picture3.GetPixel();
		
		//Multiply
	
		float Blue = ((Picture1.getBluePixel()*Picture2.getBluePixel())/255)+0.5f;
		float Green = ((Picture1.getGreenPixel()*Picture2.getGreenPixel())/255)+0.5f;
		float Red = ((Picture1.getRedPixel()*Picture2.getRedPixel())/255)+0.5f;
		
		Blue=trunc(Blue);
		Green=trunc(Green);
		Red=trunc(Red);

		//Substract
		Blue = ((Blue-Picture3.getBluePixel()));
		Green = ((Green-Picture3.getGreenPixel()));
		Red = ((Red-Picture3.getRedPixel()));
				
				
		Blue=clamp(Blue);
		Green=clamp(Green);
		Red=clamp(Red);

		ResPicture3.WritePixels(Red,Green,Blue);
		
	}
	
	ResPicture3.CloseFile();
	
	
	
	
	////////////////////////////////////Task 05
	//Picture1 
	Picture1.OpenFile("input/layer1.tga");
	Picture1.ReaderHeader();
	Picture2.OpenFile("input/pattern1.tga");
	Picture2.ReaderHeader();
	
	ResultantPicture ResPicture4;
	ResPicture4.openFile("output/part5.tga");
	ResPicture4.WriterHeader(Picture1.getHeader());
	Size=Picture1.GetSize();
	
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		Picture2.GetPixel();
		float Red,Green,Blue;
		if(Picture2.getRedPixel()>127.5)
		{
			Red=OverlayConditionOne(Picture1.getRedPixel(),Picture2.getRedPixel());
		}
		else
		{
			Red=OverlayConditionTwo(Picture1.getRedPixel(),Picture2.getRedPixel());
		}
		if(Picture2.getBluePixel()>127.5)
		{
			Blue=OverlayConditionOne(Picture1.getBluePixel(),Picture2.getBluePixel());
		}
		else
		{
			Blue=OverlayConditionTwo(Picture1.getBluePixel(),Picture2.getBluePixel());
		}
		if(Picture2.getGreenPixel()>127.5)
		{
			Green=OverlayConditionOne(Picture1.getGreenPixel(),Picture2.getGreenPixel());
		}
		else
		{
			Green=OverlayConditionTwo(Picture1.getGreenPixel(),Picture2.getGreenPixel());
		}
		
		Blue=trunc(Blue+0.5f);
		Green=trunc(Green+0.5f);
		Red=trunc(Red+0.5f);
		ResPicture4.WritePixels(Red,Green,Blue);
		
	}
	
	ResPicture4.CloseFile();	
	
	
	
	
	////////////////////////////////////Task 06
	//Picture1 
	Picture1.OpenFile("input/car.tga");
	Picture1.ReaderHeader();
	//Picture1.printerHeader();
	
	
	ResultantPicture ResPicture5;
	ResPicture5.openFile("output/part6.tga");
	ResPicture5.WriterHeader(Picture1.getHeader());
	Size=Picture1.GetSize();
	
	//Green + 200
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		Picture2.GetPixel();
		int Blue = (Picture1.getBluePixel());
		int Green = (Picture1.getGreenPixel()+200);
		int Red = (Picture1.getRedPixel());
		
		Green=clamp(Green);
		ResPicture5.WritePixels(Red,Green,Blue);
	}
	ResPicture5.CloseFile();
	
	
	////////////////////////////////////Task 07
	//Picture1 
	Picture1.OpenFile("input/car.tga");
	Picture1.ReaderHeader();
	//Picture1.printerHeader();
	
	
	ResultantPicture ResPicture6;
	ResPicture6.openFile("output/part7.tga");
	ResPicture6.WriterHeader(Picture1.getHeader());
	Size=Picture1.GetSize();
	
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		Picture2.GetPixel();
		
		int Blue = (Picture1.getBluePixel())*0;
		int Green = (Picture1.getGreenPixel());
		int Red = (Picture1.getRedPixel())*4;
		
		Blue=clamp(Blue);
		Red=clamp(Red);
		
		ResPicture6.WritePixels(Red,Green,Blue);
	}
	ResPicture6.CloseFile();





	////////////////////////////////////Task 08
	//Picture1 
	Picture1.OpenFile("input/car.tga");
	Picture1.ReaderHeader();
	
	ResultantPicture ResPicture7R,ResPicture7G,ResPicture7B;
	ResPicture7R.openFile("output/part8_r.tga");
	ResPicture7R.WriterHeader(Picture1.getHeader());
	ResPicture7G.openFile("output/part8_g.tga");
	ResPicture7G.WriterHeader(Picture1.getHeader());
	ResPicture7B.openFile("output/part8_b.tga");
	ResPicture7B.WriterHeader(Picture1.getHeader());
	
	Size=Picture1.GetSize();
	
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		
		float Red=Picture1.getRedPixel();
		float Green=Picture1.getRedPixel();
		float Blue=Picture1.getRedPixel();
		ResPicture7R.WritePixels(Red,Green,Blue);
		
		
		Red=Picture1.getGreenPixel();
		Green=Picture1.getGreenPixel();
		Blue=Picture1.getGreenPixel();
		ResPicture7G.WritePixels(Red,Green,Blue);
		
		
		Red=Picture1.getBluePixel();
		Green=Picture1.getBluePixel();
		Blue=Picture1.getBluePixel();
		ResPicture7B.WritePixels(Red,Green,Blue);
		
	}
	
	ResPicture7R.CloseFile();
	ResPicture7G.CloseFile();
	ResPicture7B.CloseFile();
	
	
	
	
	
	
	
	//Picture1 
	Picture1.OpenFile("input/layer_red.tga");
	Picture1.ReaderHeader();
	Picture2.OpenFile("input/layer_green.tga");
	Picture2.ReaderHeader();
	Picture3.OpenFile("input/layer_blue.tga");
	Picture3.ReaderHeader();
	
	cout<<"here";
	ResultantPicture ResPicture8;
	ResPicture8.openFile("output/part9.tga");
	ResPicture8.WriterHeader(Picture1.getHeader());
	Size=Picture1.GetSize();
	
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		Picture2.GetPixel();
		Picture3.GetPixel();
		
		float Red=Picture1.getRedPixel();
		float Green=Picture2.getGreenPixel();
		float Blue=Picture3.getBluePixel();
		
		
		ResPicture8.WritePixels(Red,Green,Blue);
		
	}
	
	ResPicture8.CloseFile();

	
	
	//////////////////////////Task10
	//Picture1 
	Picture1.OpenFile("input/text2.tga");
	Picture1.ReaderHeader();
	//Picture1.printerHeader();
	
	
	ResultantPicture ResPicture9;
	ResPicture9.openFile("output/part10.tga");
	ResPicture9.WriterHeader(Picture1.getHeader());
	Size=0;
	Size=Picture1.GetSize();
	
	float RedM[Size],BlueM[Size],GreenM[Size];
	for(int i=0;i<=Size;i++)
	{
		Picture1.GetPixel();
		
		RedM[i]=Picture1.getRedPixel();
		GreenM[i]=Picture1.getGreenPixel();
		BlueM[i]=Picture1.getBluePixel();
		
		
	}
	for(int i=1;i<Size;i++)
	{
		
		float Blue = BlueM[Size-i];
		float Green = GreenM[Size-i];
		float Red = RedM[Size-i];
		
		ResPicture9.WritePixels(Red,Green,Blue);
		
	}
	ResPicture9.CloseFile();
	
}
