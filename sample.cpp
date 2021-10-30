#include "AIController.h"
#include <utility>
#include <bits/stdc++.h>
#define se second
#define fi first
extern int ai_side;
std::string ai_name = "HanHan_Killer";
const int fx[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
int cz[11][3],ans[3];//bu cz
int la0[2],la1[2],q[101][2],f[11][11],sg,nsg,w0,w1,a[11][11]={0};
//la 上次位置
//sg 最短路估价(ta-wo)
//a 障碍物数组 
//w 木板放次数 
void init()
{
	la0[0]=8;la0[1]=4;
	la1[0]=0;la1[1]=4;
	sg=w0=w1=0;
}
bool pd(int x,int y,int i)
{
	if(i==0){
		if(a[x-1][y-1]!=2&&a[x-1][y]!=2)return 1;
	}else if(i==1){
		if(a[x-1][y-1]!=1&&a[x][y-1]!=1)return 1;
	}else if(i==2){
		if(a[x][y-1]!=2&&a[x][y]!=2)return 1;
	}else if(i==3){
		if(a[x-1][y]!=1&&a[x][y]!=1)return 1;
	}
	return 0;
}
int get_win0(int stx,int sty)
{
	if(stx==0)return 0;memset(f,0,sizeof f);
	int h=1,t=1;q[1][0]=stx;q[1][1]=sty;f[stx][sty]=1;
	while(h<=t){
		int x=q[h][0],y=q[h][1];
		for(int i=0;i<4;i++)if(pd(x,y,i)){
			int xx=x+fx[i][0],yy=y+fx[i][1];
			if(xx>=0&&xx<9&&yy>=0&&yy<9&&f[xx][yy]==0){
			f[xx][yy]=f[x][y]+1,q[++t][0]=xx,q[t][1]=yy;
			if(xx==0)return f[xx][yy]-1;}
		}
		++h;
	}
	return -1;
}
int get_win1(int stx,int sty)
{
	if(stx==8)return 0;memset(f,0,sizeof f);
	int h=1,t=1;q[1][0]=stx;q[1][1]=sty;f[stx][sty]=1;
	while(h<=t){
		int x=q[h][0],y=q[h][1];
		for(int i=0;i<4;i++)if(pd(x,y,i)){
			int xx=x+fx[i][0],yy=y+fx[i][1];
			if(xx>=0&&xx<9&&yy>=0&&yy<9&&f[xx][yy]==0){
			f[xx][yy]=f[x][y]+1,q[++t][0]=xx,q[t][1]=yy;
			if(xx==8)return f[xx][yy]-1;}
		}
		++h;
	}
	return -1;
}
/*void serach1(int x0,int y0,int x1,int y1,int t,int sg1)
{
	if(!sg1>=sg-(4-t))return;
	if(!sg1>=nsg-(4-t))return;
	//zou
	for(int i=0;i<4;i++)if(pd(x0,y0,i)){
		int xx=x0+fx[i][0],yy=y0+fx[i][1];
		if(xx!=x1||yy!=y1){
			int sg2=get_win1(xx,yy)-get_win0(x1,y1);
			if(sg2<=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
		}
		else{
			if(pd(xx,yy,i)){
				xx=xx+fx[i][0],yy=yy+fx[i][1];
				int sg2=get_win1(xx,yy)-get_win0(x1,y1);
				if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
			}else{
				for(int i=0;i<4;i++)if(pd(xx,yy,i)){
					xx=xx+fx[i][0],yy=yy+fx[i][1];
					if(xx!=x0||yy!=y0){
						int sg2=get_win1(xx,yy)-get_win0(x1,y1);
						if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
					}
					xx=xx-fx[i][0],yy=yy-fx[i][1];
				}
			}
		}
	}
	//ban
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)if(!a[i][j]){
			a[i][j]=1;
			int w1,w2;
			if((w1=get_win1(xx,yy))>=0&&(w2=get_win0(x1,y1))>=0){
				int sg2=get_win1(xx,yy)-get_win0(x1,y1);
				if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
			}
			a[i][j]=2;
			if((w1=get_win1(xx,yy))>=0&&(w2=get_win0(x1,y1))>=0){
				int sg2=get_win1(xx,yy)-get_win0(x1,y1);
				if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
			}
			a[i][j]=0;
		}
}
void serach0(int x0,int y0,int x1,int y1,int t,int sg1)//t:how many times?
{
	if(!sg1>=sg-2*(4-t))return;
	if(!sg1>=nsg-2*(4-t))return;
	if(t>4){
		if(sg1>nsg){
			nsg=sg1;
			ans[0]=cz[1][0];
			ans[1]=cz[1][1];
			ans[2]=cz[1][2];
		}
		return;
	}
	//zou
	for(int i=0;i<4;i++)if(pd(x0,y0,i)){
		int xx=x0+fx[i][0],yy=y0+fx[i][1];
		if(xx!=x1||yy!=y1){
			int sg2=get_win1(xx,yy)-get_win0(x1,y1);
			if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
		}
		else{
			if(pd(xx,yy,i)){
				xx=xx+fx[i][0],yy=yy+fx[i][1];
				int sg2=get_win1(xx,yy)-get_win0(x1,y1);
				if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
			}else{
				for(int i=0;i<4;i++)if(pd(xx,yy,i)){
					xx=xx+fx[i][0],yy=yy+fx[i][1];
					if(xx!=x0||yy!=y0){
						int sg2=get_win1(xx,yy)-get_win0(x1,y1);
						if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
					}
					xx=xx-fx[i][0],yy=yy-fx[i][1];
				}
			}
		}
	}
	//ban
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)if(!a[i][j]){
			a[i][j]=1;
			int w1,w2;
			if((w1=get_win1(xx,yy))>=0&&(w2=get_win0(x1,y1))>=0){
				int sg2=get_win1(xx,yy)-get_win0(x1,y1);
				if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
			}
			a[i][j]=2;
			if((w1=get_win1(xx,yy))>=0&&(w2=get_win0(x1,y1))>=0){
				int sg2=get_win1(xx,yy)-get_win0(x1,y1);
				if(sg2>=sg1-(4-t))serach1(xx,yy,x1,y1,t+1,sg2);
			}
			a[i][j]=0;
		}
}*/
void now_best(int x0,int y0,int x1,int y1)
{
	for(int i=0;i<4;i++)if(pd(x0,y0,i)){
		int xx=x0+fx[i][0],yy=y0+fx[i][1];
		if(xx<0||yy<0||xx>8||yy>8)continue;
		if(xx!=x1||yy!=y1){
			int sg2=get_win1(x1,y1)-get_win0(xx,yy);
			if(sg2>nsg){
				nsg=sg2;
				ans[0]=0;
				ans[1]=xx;
				ans[2]=yy;
			}
		}
		else{
			if(pd(xx,yy,i)){
				xx=xx+fx[i][0],yy=yy+fx[i][1];
				if(xx<0||yy<0||xx>8||yy>8)continue;
				int sg2=get_win1(x1,y1)-get_win0(xx,yy);
				if(sg2>nsg){
					nsg=sg2;
					ans[0]=0;
					ans[1]=xx;
					ans[2]=yy;
				}
			}else{
				for(int i=0;i<4;i++)if(pd(xx,yy,i)){
					xx=xx+fx[i][0],yy=yy+fx[i][1];
					if(xx<0||yy<0||xx>8||yy>8){xx=xx-fx[i][0],yy=yy-fx[i][1];continue;}
					if(xx!=x0||yy!=y0){
						int sg2=get_win1(x1,y1)-get_win0(xx,yy);
						if(sg2>nsg){
							ans[0]=0;
							ans[1]=xx;
							ans[2]=yy;
						}
					}
					xx=xx-fx[i][0],yy=yy-fx[i][1];
				}
			}
		}
	}
	if(w0<10)
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)if(!a[i][j]){
			a[i][j]=1;
			int w1,w2;
			if(a[i-1][j]!=1&&a[i+1][j]!=1)if((w1=get_win0(x0,y0))>=0&&(w2=get_win1(x1,y1))>=0){
				int sg2=get_win1(x1,y1)-get_win0(x0,y0);
					if(sg2>=nsg){
						nsg=sg2;
						ans[0]=1;
						ans[1]=i;
						ans[2]=j;
					}
			}
			a[i][j]=2;
			if(a[i][j-1]<2&&a[i][j+1]<2)if((w1=get_win0(x0,y0))>=0&&(w2=get_win1(x1,y1))>=0){
				int sg2=get_win1(x1,y1)-get_win0(x0,y0);
					if(sg2>=nsg){
						nsg=sg2;
						ans[0]=2;
						ans[1]=i;
						ans[2]=j;
					}
			}
			a[i][j]=0;
		}
}
void now_best2(int x0,int y0,int x1,int y1)
{
	for(int i=0;i<4;i++)if(pd(x1,y1,i)){
		int xx=x1+fx[i][0],yy=y1+fx[i][1];
		if(xx<0||yy<0||xx>8||yy>8)continue;
		if(xx!=x0||yy!=y0){
			int sg2=get_win0(x0,y0)-get_win1(xx,yy);
			if(sg2>nsg){
				nsg=sg2;
				ans[0]=0;
				ans[1]=xx;
				ans[2]=yy;
			}
		}
		else{
			if(pd(xx,yy,i)){
				xx=xx+fx[i][0],yy=yy+fx[i][1];
				if(xx<0||yy<0||xx>8||yy>8)continue;
				int sg2=get_win0(x0,y0)-get_win1(xx,yy);
				if(sg2>nsg){
					nsg=sg2;
					ans[0]=0;
					ans[1]=xx;
					ans[2]=yy;
				}
			}else{
				for(int i=0;i<4;i++)if(pd(xx,yy,i)){
					xx=xx+fx[i][0],yy=yy+fx[i][1];
					if(xx<0||yy<0||xx>8||yy>8){xx=xx-fx[i][0],yy=yy-fx[i][1];continue;}
					if(xx!=x1||yy!=y1){
						int sg2=get_win0(x0,y0)-get_win1(xx,yy);
						if(sg2>nsg){
							ans[0]=0;
							ans[1]=xx;
							ans[2]=yy;
						}
					}
					xx=xx-fx[i][0],yy=yy-fx[i][1];
				}
			}
		}
	}
	if(w1<10)
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)if(!a[i][j]){
			a[i][j]=1;
			int w1,w2;
			if(a[i-1][j]!=1&&a[i+1][j]!=1)if((w1=get_win0(x0,y0))>=0&&(w2=get_win1(x1,y1))>=0){
				int sg2=get_win0(x0,y0)-get_win1(x1,y1);
					if(sg2>=nsg){
						nsg=sg2;
						ans[0]=1;
						ans[1]=i;
						ans[2]=j;
					}
			}
			a[i][j]=2;
			if(a[i][j-1]<2&&a[i][j+1]<2)if((w1=get_win0(x0,y0))>=0&&(w2=get_win1(x1,y1))>=0){
				int sg2=get_win0(x0,y0)-get_win1(x1,y1);
					if(sg2>=nsg){
						nsg=sg2;
						ans[0]=2;
						ans[1]=i;
						ans[2]=j;
					}
			}
			a[i][j]=0;
		}
}
std::pair<int, std::pair<int, int> > action(std::pair<int, std::pair<int, int> > loc)
{
	int fl=loc.fi,nx=loc.se.fi,ny=loc.se.se,cs=0;
	//0 first (8,4) , 1 second 
	if (ai_side == 0){
		if(fl==-1){la0[0]=7;la0[1]=4;return std::make_pair(0,std::make_pair(7,4));}
		else{
			if(fl==0)la1[0]=nx,la1[1]=ny;
			else w1++,a[nx][ny]=fl;
			nsg=-100;
			now_best(la0[0],la0[1],la1[0],la1[1]);
			/*sg=get_win1(la1[0],la1[1])-get_win0(la0[0],la0[1]);
			search0(la0[0],la0[1],la1[0],la1[1],1,sg);*/
			if(ans[0]==0){
				la0[0]=ans[1];
				la0[1]=ans[2];
			}else if(ans[0]==1){
				a[ans[1]][ans[2]]=1;w0++;
			}else a[ans[1]][ans[2]]=2,w0++;
			return std::make_pair(ans[0],std::make_pair(ans[1],ans[2]));
		}
	}
	else{
		if(fl==0)la0[0]=nx,la0[1]=ny;
			else w0++,a[nx][ny]=fl;
		//if(!cs){la1[0]=1;la1[1]=4;cs++;return std::make_pair(0,std::make_pair(1,4));}
		//else{
			nsg=-100;
			now_best2(la0[0],la0[1],la1[0],la1[1]);
			/*sg=get_win1(la1[0],la1[1])-get_win0(la0[0],la0[1]);
			search0(la0[0],la0[1],la1[0],la1[1],1,sg);*/
			if(ans[0]==0){
				la1[0]=ans[1];
				la1[1]=ans[2];
			}else if(ans[0]==1){
				a[ans[1]][ans[2]]=1;w1++;
			}else a[ans[1]][ans[2]]=2,w1++;
			return std::make_pair(ans[0],std::make_pair(ans[1],ans[2]));
		//}
	}	
}
