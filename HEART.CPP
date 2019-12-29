#include<fstream>
using namespace std;
#include<windows.h>
#define MULTIPLIER 100
FILE*fin=fopen("color.txt","r");
struct
{
	char name[256];
	int r,g,b;
}color[256];
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
void heart(char file[],int map[15][15],int a,int b)
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
	sprintf(command,"bmp2png -E -D \"data\" \"%s\"",file);
	system(command);
}
void star(char file[],int map[15][15],int a,int b)
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
	sprintf(command,"bmp2png -E -D \"star\" \"%s\"",file);
	system(command);
}
void main()
{
	int i,j;
	char line[1024];
	while(1)
	{
		fgets(line,1024,fin);
		n++;
		sscanf(line,"%s #%2X%2X%2X",color[n].name,&color[n].r,&color[n].g,&color[n].b);
		if(feof(fin))break;
	}
	for(i=1;i<=n;++i)
	{
		for(j=1;j<=n;++j)
		{
			if(i==j||color[i].name[0]=='#'||color[j].name[0]=='#')continue;
			if(color[i].name[0]=='*'&&color[j].name[0]=='*')
			{
				sprintf(line,"%s star with %s background.bmp",color[i].name+1,color[j].name+1);
				star(line,map_star,i,j);
				continue;
			}
			sprintf(line,"%s filled with %s background.bmp",color[i].name,color[j].name);
			heart(line,map_fill,i,j);
			sprintf(line,"%s line with %s background.bmp",color[i].name,color[j].name);
			heart(line,map_line,i,j);
		}
	}
	return;
}