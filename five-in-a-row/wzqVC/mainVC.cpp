#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

#define ESC 0x1b
#define space 0x20

#define E_KEY 0X65
#define D_KEY 0x64
#define S_KEY 0x73
#define F_KEY 0x66
#define LEFT 0x4b					/*�����*/
#define RIGHT 0x4d					/*���Ҽ�*/
#define DOWN 0x50					/*���¼�*/
#define UP 0x48						/*���ϼ�*/
#define ESC 0x1b					/*��ESC���˳���*/
#define SPACE 0x20					/*��space���ո��*/

#define GRAY 0x808000

struct GRID{
    int x,y;
    long color;
};

void SetGridValue(struct GRID grid[15][15]);
void DrawChessboard(struct GRID grid[15][15]);
void DrawChessman(int c1,int c2,int x,int y);
int getKey();
void play(char c);
int judge(int x,int y);

struct GRID grid[15][15];
int hx=7,hy=7;
int hc=0,cc=15;
int flag = 0;

/*
 * ������ 
 */
int main() {
	
    //int gdriver=DETECT,gmode;
    //initgraph(&gdriver,&gmode,"");//ͼ�ν����ʼ��
	initgraph(640, 480);   // ����� TC ��������
    setbkcolor(WHITE);
    cleardevice();//����
	//DrawChessman(RED, BLUE, 100, 100);
	SetGridValue(grid);
	DrawChessboard(grid);
	
	
	int c;
	setcolor(WHITE);
    rectangle(grid[hx][hy].x-14,grid[hx][hy].y-14,grid[hx][hy].x+14,grid[hx][hy].y+14);
    rectangle(96,23,530,457);
	while(1) {
		c = getKey();
		printf("$#%x#$\n",c);
		
		play(c);
	}
	/*
	int c;
	while(1) {
		c = getKey();
		printf("$#%x#$\n",c);
	}*/
	system("pause");
	return 0;
}
// �ı����ӵ���ɫ 
void changeColor(int flag, int &hc, int &cc)
{
	if(flag==1) {
		hc = WHITE; cc = BLACK;
	} else {
		hc = BLACK; cc = WHITE;
	}
}
/*
 * ��Ϸ���ƹ���
 * �������������ƶ������ӷ��ú��˳���Ϸ�� 
 */ 
void play(char c)
{
	if(c==SPACE) {
		if(grid[hx][hy].color == -1) {
			changeColor(flag,hc,cc);
			DrawChessman(cc,hc,hx,hy);
			grid[hx][hy].color = flag;
			if(judge(hx,hy)) {
				setcolor(4);
				//settextstyle( GOTHIC_FONT, HORIZ_DIR,4 );
				setfont(32, 0,"����");
    			//settextjustify( CENTER_TEXT, CENTER_TEXT );
    			if(flag == 0) {					
					outtextxy( grid[7][7].x, grid[7][7].y, "Player 1 Win!" );
				} else {
					outtextxy( grid[7][7].x, grid[7][7].y, "Player 2 Win!" );
				}
			}
			flag = 1 - flag;
		}
	} else 	if(c=='e'||c=='d'||c=='s'||c=='f'||c=='E'||c=='D'||c=='S'||c=='F'){
        setcolor(GRAY);
        rectangle(grid[hx][hy].x-14,grid[hx][hy].y-14,grid[hx][hy].x+14,grid[hx][hy].y+14);
        putpixel(grid[hx][hy].x-14,grid[hx][hy].y,0);
        putpixel(grid[hx][hy].x,grid[hx][hy].y-14,0);
        putpixel(grid[hx][hy].x,grid[hx][hy].y+14,0);
        putpixel(grid[hx][hy].x+14,grid[hx][hy].y,0);

        switch(c){
            case 'e':
            case 'E':
                if(hy==0) hy=14;
                else hy-=1;
                break;
            case 'd':
            case 'D':
                if(hy==14) hy=0;
                else hy+=1;
                break;
            case 's':
            case 'S':
                if(hx==0) hx=14;
                else hx-=1;
                break;
            case 'f':
            case 'F':
                if(hx==14) hx=0;
                else hx+=1;
                break;
        }
        setcolor(WHITE);
        rectangle(grid[hx][hy].x-14,grid[hx][hy].y-14,grid[hx][hy].x+14,grid[hx][hy].y+14);
        //rectangle(96,23,530,457);
    }
}
/*
 *�ж�������ɫ�����ڲ�ͬ����ĸ����Ƿ񵽴�5��
 */
int judge(int x,int y)	
{
    int j,k,n1,n2 ; 
    while(1)
    {

        /*���Ϸ�*/
        n1=0 ;
        n2=0 ;
        for(j=x,k=y;j>=0&&k>=0;j--,k--)
        {
            if(grid[j][k].color==flag)
                n1++;								/*�ۼ����Ϸ���������*/
            else
                break ;
        }

        /*���·�*/
        for(j=x,k=y;j<=14&&k<=14;j++,k++)
        {
            if(grid[j][k].color==flag)
                n2++;								/*�ۼ����·���������*/
            else
                break ;
        }
        if(n1+n2-1>=5)								/*���Ϸ������·��������ۼӴ��ڵ���5*/
            return(1);									/*����1*/
        
        /*���Ϸ�*/
        n1=0 ;
        n2=0 ;
        for(j=x,k=y;j<=19&&k>=0;j++,k--)
        {
            if(grid[j][k].color==flag)
                n1++;								/*�ۼ����Ϸ���������*/
            else
                break ;
        }
        /*���·�*/
        for(j=x,k=y;j>=0&&k<=14;j--,k++)
        {
            if(grid[j][k].color==flag)
                n2++;								/*�ۼ����·���������*/
            else
                break ;
        }
        if(n1+n2-1>=5)								/*���·������Ϸ��������ۼӴ��ڵ���5*/
            return(1);									/*����1*/
        n1=0 ;
        n2=0 ;

        /*ˮƽ����*/
        for(j=x,k=y;j>=0;j--)
        {
            if(grid[j][k].color==flag)
                n1++;								/*�ۼ�ˮƽ���������*/
            else
                break ;
        }

        /*ˮƽ����*/
        for(j=x,k=y;j<=14;j++)
        {
            if(grid[j][k].color==flag)
                n2++;								/*�ۼ�ˮƽ�ҵ�������*/
            else
                break ;
        }
        if(n1+n2-1>=5)								/*ˮƽ���ˮƽ�ҵ������ۼӴ��ڵ���5*/
            return(1);									/*����1*/
        
        /*��ֱ����*/
        n1=0 ;
        n2=0 ;
        for(j=x,k=y;k>=0;k--)
        {
            if(grid[j][k].color==flag)
                n1++;								/*�ۼӴ�ֱ���ϵ�������*/
            else
                break ;
        }

        /*��ֱ����*/
        for(j=x,k=y;k<=14;k++)
        {
            if(grid[j][k].color==flag)
                n2++;								/*�ۼӴ�ֱ���µ�������*/
            else
                break ;
        }
        if(n1+n2-1>=5)								/*��ֱ������ۼӺʹ��ڵ���5*/
            return(1);									/*����1*/
        return(0);
    }
}
/*
 * ��ü������� 
 */
int getKey()
{
	int key = getch();
	if(key == ESC) return ESC;
	if(key == 0xe0) {
		key = getch();
		if(key == UP) return 'e';
		if(key == DOWN) return 'd';
		if(key == LEFT) return 's';
		if(key == RIGHT) return 'f';
	}
	return key;
}
/*
 * �ڣ�x,y��λ�û���c1,c2����ɫ������
 * ��x,y��Ϊ���ӵ�λ��
 * c1 Ϊ��Ե����ɫ
 * c2 ΪԲ�����ڲ���ɫ 
 */
void DrawChessman(int c1,int c2,int x,int y){
    setcolor(c1);
    setfillstyle(c1, SOLID_FILL); // tc��vc��һ��
    //pieslice(grid[x][y].x,grid[x][y].y,0,360,13);
	pie(grid[x][y].x-14,grid[x][y].y-14,grid[x][y].x+14,grid[x][y].y+14,0,3.14*2);
    //setcolor(c2);
    //circle(grid[x][y].x,grid[x][y].y,13);
}
/*
 * �������̵�λ�� 
 */ 
void SetGridValue(struct GRID grid[15][15]){
    int x,y;
    int i,j;
    x=110;
    for(i=0;i<=14;i++){
        y=37;
        for(j=0;j<=14;j++){
            grid[i][j].x=x;
            grid[i][j].y=y;
            grid[i][j].color=-1;
            y+=29;
        }
        x+=29;
    }
}
/*
 * ���̻������� 
 */ 
void DrawChessboard(struct GRID grid[15][15]){
    int i,j;
    setfillstyle(GRAY,SOLID_FILL);//�������ģʽ ��ʵ��� ��ɫΪ6  vc��tc ��һ��
    bar(96,23,530,457);//��һ�������� 
    setcolor(GRAY);//������ɫΪ����ɫ 
    rectangle(96,23,530,457);
    setcolor(0);//������ɫΪ��ɫ 
    // �������� 
    for(i=0;i<=13;i++) {
        for(j=0;j<=13;j++){
            rectangle(grid[i][j].x,grid[i][j].y,grid[i+1][j+1].x,grid[i+1][j+1].y);
        }
	}
	// ���ĸ��ڵ� 
    setcolor(0);
    setfillstyle(0,SOLID_FILL);//vc��tc ��һ��
    //pieslice(grid[3][3].x,grid[3][3].y,0,360,4);
    //pieslice(grid[3][11].x,grid[3][11].y,0,360,4);
    //pieslice(grid[11][3].x,grid[11][3].y,0,360,4);
    //pieslice(grid[11][11].x,grid[11][11].y,0,360,4);
	int x,y;
	x=3;y=3;pie(grid[x][y].x-4,grid[x][y].y-4,grid[x][y].x+4,grid[x][y].y+4,0,3.14*2);//vc��tc ��һ��
	x=3;y=11;pie(grid[x][y].x-4,grid[x][y].y-4,grid[x][y].x+4,grid[x][y].y+4,0,3.14*2);
	x=11;y=3;pie(grid[x][y].x-4,grid[x][y].y-4,grid[x][y].x+4,grid[x][y].y+4,0,3.14*2);
	x=11;y=11;pie(grid[x][y].x-4,grid[x][y].y-4,grid[x][y].x+4,grid[x][y].y+4,0,3.14*2);
}



