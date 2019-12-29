#include<fstream>
using namespace std;
#include<windows.h>
int MULTIPLIER,FR,FG,FB,BR,BG,BB;
FILE*fin=fopen("PREFERENCE.TXT","r");
FILE*fout=fopen("HEART.BMP","wb");
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
int map[15][15];
int remainder(int p)
{
	if(p%4)return 4-(p%4);
	else return 0;
}
void main()
{
	int i,j;
	char ct[10];
	fscanf(fin,"%d\n%s\n%d\n%d\n%d\n%d\n%d\n%d",&MULTIPLIER,ct,&FR,&FG,&FB,&BR,&BG,&BB);
	if(!strcmp(ct,"FILL"))memcpy(map,map_fill,15*15*sizeof(int));
	if(!strcmp(ct,"LINE"))memcpy(map,map_line,15*15*sizeof(int));
	BITMAPFILEHEADER bitmapfileheader={19778,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+MULTIPLIER*15*(MULTIPLIER*15*3+remainder(MULTIPLIER*15*3)),0,0,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)};
	BITMAPINFOHEADER bitmapinfoheader={sizeof(BITMAPINFOHEADER),MULTIPLIER*15,MULTIPLIER*15,1,24,BI_RGB,0,0,0,0,0};
	fwrite(&bitmapfileheader,sizeof(BITMAPFILEHEADER),1,fout);
	fwrite(&bitmapinfoheader,sizeof(BITMAPINFOHEADER),1,fout);
	for(i=MULTIPLIER*15-1;i>=0;--i)
	{
		for(j=0;j<MULTIPLIER*15;++j)
		{
			if(map[i/MULTIPLIER][j/MULTIPLIER])
			{
				fputc(FR,fout);
				fputc(FB,fout);
				fputc(FG,fout);
			}
			else
			{
				fputc(BR,fout);
				fputc(BG,fout);
				fputc(BB,fout);
			}
		}
		for(j=1;j<=remainder(MULTIPLIER*15*3);++j)fputc(0,fout);
	}
	return;
}