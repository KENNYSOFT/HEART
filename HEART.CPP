#include<fstream>
using namespace std;
#define MULTIPLIER 100
typedef u_int16_t WORD;
typedef u_int32_t DWORD;
typedef int32_t LONG;
#define BI_RGB 0x0000
#pragma pack(push)
#pragma pack(1)
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;
typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biplanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)
FILE*fin=fopen("color.txt","r");
struct
{
	char name[256];
	int r,g,b;
}color[256],color_opsv[10]={{},{"white",0xFF,0xFF,0xFF},{"logoblue",0x23,0x96,0xFF},{"logoyellow",0xFF,0xDC,0x50},{"logogreen",0x79,0xD6,0x5B},{"logofont",0x41,0x41,0x41}};
int n;
int map_fill[15][15]={
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,0,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int map_line[15][15]={
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,0,0,1,0,1,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int map_star[15][15]={
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,1,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int remainder(int p)
{
	if(p%4)return 4-(p%4);
	else return 0;
}
void draw(const char *dst,char file[],int map[15][15],int a,int b)
{
	int i,j;
	char command[1024];
	FILE*fp=fopen(file,"w");
	BITMAPFILEHEADER bitmapfileheader={19778,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+MULTIPLIER*15*(MULTIPLIER*15*3+remainder(MULTIPLIER*15*3)),0,0,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)};
	BITMAPINFOHEADER bitmapinfoheader={sizeof(BITMAPINFOHEADER),MULTIPLIER*15,MULTIPLIER*15,1,24,BI_RGB,0,0,0,0,0};
	fwrite(&bitmapfileheader,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&bitmapinfoheader,sizeof(BITMAPINFOHEADER),1,fp);
	for(i=MULTIPLIER*15-1;i>=0;--i)
	{
		for(j=0;j<MULTIPLIER*15;++j)
		{
			if(map[i/MULTIPLIER][j/MULTIPLIER])
			{
				fputc(color[a].b,fp);
				fputc(color[a].g,fp);
				fputc(color[a].r,fp);
			}
			else
			{
				fputc(color[b].b,fp);
				fputc(color[b].g,fp);
				fputc(color[b].r,fp);
			}
		}
		for(j=1;j<=remainder(MULTIPLIER*15*3);++j)fputc(0,fp);
	}
	fclose(fp);
	sprintf(command,"./BMP2PNG.EXE -E -D \"%s\" \"%s\"",dst,file);
	system(command);
}
void draw_opsv(const char *dst,char file[],int map[15][15])
{
	int i,j;
	char command[1024];
	FILE*fp=fopen(file,"w");
	BITMAPFILEHEADER bitmapfileheader={19778,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+MULTIPLIER*15*(MULTIPLIER*15*3+remainder(MULTIPLIER*15*3)),0,0,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)};
	BITMAPINFOHEADER bitmapinfoheader={sizeof(BITMAPINFOHEADER),MULTIPLIER*15,MULTIPLIER*15,1,24,BI_RGB,0,0,0,0,0};
	fwrite(&bitmapfileheader,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&bitmapinfoheader,sizeof(BITMAPINFOHEADER),1,fp);
	for(i=MULTIPLIER*15-1;i>=0;--i)
	{
		for(j=0;j<MULTIPLIER*15;++j)
		{
			if(map[i/MULTIPLIER][j/MULTIPLIER])
			{
				int cl;
				if(i>=MULTIPLIER*15/2&&j>=MULTIPLIER*15/2)cl=5;
				else if(j>=MULTIPLIER*15/2)cl=4;
				else if(i<=j)cl=3;
				else cl=2;
				fputc(color_opsv[cl].b,fp);
				fputc(color_opsv[cl].g,fp);
				fputc(color_opsv[cl].r,fp);
			}
			else
			{
				fputc(color_opsv[1].b,fp);
				fputc(color_opsv[1].g,fp);
				fputc(color_opsv[1].r,fp);
			}
		}
		for(j=1;j<=remainder(MULTIPLIER*15*3);++j)fputc(0,fp);
	}
	fclose(fp);
	sprintf(command,"./BMP2PNG.EXE -E -D \"%s\" \"%s\"",dst,file);
	system(command);
}
int main()
{
	int i,j;
	char line[1024];
	while(1)
	{
		fgets(line,1024,fin);
		if(feof(fin))break;
		n++;
		sscanf(line,"%s #%2X%2X%2X",color[n].name,&color[n].r,&color[n].g,&color[n].b);
	}
	for(i=1;i<=n;++i)
	{
		for(j=1;j<=n;++j)
		{
			if(i==j||color[i].name[0]=='#'||color[j].name[0]=='#')continue;
			if(color[i].name[0]=='*'&&color[j].name[0]=='*')
			{
				sprintf(line,"%s star with %s background.bmp",color[i].name+1,color[j].name+1);
				draw("star",line,map_star,i,j);
				continue;
			}
			else if(color[i].name[0]=='*'||color[j].name[0]=='*')continue;
			sprintf(line,"%s filled with %s background.bmp",color[i].name,color[j].name);
			draw("data",line,map_fill,i,j);
			sprintf(line,"%s line with %s background.bmp",color[i].name,color[j].name);
			draw("data",line,map_line,i,j);
		}
	}
	sprintf(line,"opsv filled with %s background.bmp",color_opsv[1].name);
	draw_opsv("opsv",line,map_fill);
	sprintf(line,"opsv line with %s background.bmp",color_opsv[1].name);
	draw_opsv("opsv",line,map_line);
	return 0;
}
