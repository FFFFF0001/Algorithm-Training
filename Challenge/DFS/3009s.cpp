#include<iostream>
#include<algorithm>
using namespace std;

int dir[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};
int endX,endY,startX,startY;
int map[25][25];
int col,row,steps,mini;
#define MAX 1e8
void dfs(int startX,int startY){
	int posX,posY;
	if(steps>=10)//����10��
		return;
	for(int i=0;i<4;i++){//4������
		posX = startX;
		posY = startY;
		while(1){
			posX += dir[i][0];//�ı�x����
			posY += dir[i][1];//�ı�y����
			if(posX<0||posX>row||posY<0||posY>col)//����Խ��
				break;
			if(posX==endX&&posY==endY){//�����յ�
				steps++;
				if(mini>steps)
					mini = steps;//�洢��С��������С����
				steps--;
				return;
			}
			else if(map[posX][posY]==1){//�����ϰ���
				if(posX-dir[i][0]!=startX||posY-dir[i][1]!=startY){//����������
					map[posX][posY] = 0;//�ϰ�����ʧ
					steps++;//����+1
					dfs(posX-dir[i][0],posY-dir[i][1]);//����dfs
					map[posX][posY] = 1;//�ϰ��︴ԭ
					steps--;//����-1
				}
				break;
			}
		}
	}
}
int main()
{
	//freopen("d.txt","r",stdin);
	int startX,startY;
	while(cin>>col>>row&&(col||row)){
		for(int i=1;i<=row;i++)
			for(int j=1;j<=col;j++){
				cin>>map[i][j];
				if(map[i][j]==2){//�����ʼ
					startX = i;
					startY = j;
				}
				if(map[i][j]==3){//����յ�
					endX = i;
					endY = j;
				}
			}
		mini = MAX;
		steps = 0;
		dfs(startX,startY);
		if(mini==MAX)//miniδ���ı�
			cout<<"-1"<<endl;
		else//miniֵ�ı�
			cout<<mini<<endl;
	}
	return 0;
}