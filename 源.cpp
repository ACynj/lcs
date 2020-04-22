#include<stdio.h>
#include<stdlib.h>
typedef struct Snode* stack;
struct Snode {
	char data;
	stack Next;
};
stack creatStack() {
	stack s = (stack)malloc(sizeof(struct Snode));
	s->Next = NULL;
	return s;
}
void push(stack t,char x) {
	stack newNode = (stack)malloc(sizeof(struct Snode));
	newNode->data = x;
	newNode->Next = t->Next;
	t->Next = newNode;
}
char pop(stack s) {
	char x;
	if (s->Next == NULL)return -1;
	stack firstNode;
	firstNode = s->Next;
	x = firstNode->data;
	s->Next = firstNode->Next;
	free(firstNode);
	return x;
}
void Max(int c[100][100], int B[100][100], char x[], char y[], int xn, int yn) {
	//i表示数组x的下标，j表示数组y的下标
	//B[i][j] o表示删除x的末尾一位，1表示删除末尾一位，2表示删除x,y数组末尾两位
	int i, j;
	//temp1,temp2分别表示x，y数组的元素的下标
	char temp1, temp2;
	for (i = 1; i <= xn; i++) {
		for (j = 1; j <= yn; j++) {
			//如果x[i]=y[j]，那么c[i][j]=c[i-1][j-1]+1,B[i][j]=2
			//如果不相等，就为从max{c[i][j-1],c[i-1][j]},B为1/0
			if (x[i] == y[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				B[i][j] = 2;
			}
			else {
				if (c[i][j - 1] >= c[i - 1][j]) {
					c[i][j] = c[i][j - 1];
					B[i][j] = 1;
				}
				else {
					c[i][j] = c[i - 1][j];
					B[i][j] = 0;
				}
			}
		}
	}
	stack s = creatStack();
	temp1 = xn, temp2 = yn;
	//B[i][j]=0，x下标减一，=1，y数组下标减一，=2，x,y数组下标同时减1，并且将元素push到堆栈里
	while (temp1 > 0 && temp2 > 0) {
		if (B[temp1][temp2] == 2) {
			push(s, x[temp1]);
			temp1 -= 1;
			temp2 -= 1;
		}
		else if (B[temp1][temp2] == 1) {
			temp2 -= 1;
		}
		else {
			temp1 -= 1;
		}
	}
	
	for (i = 0; i <= xn; i++) {
		for (j = 0; j <= yn; j++) {
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}
	for (i = 1; i <= xn; i++) {
		for (j = 1; j <= yn; j++) {
			printf("%d ", B[i][j]);
		}
		printf("\n");
	}
//将最大子列从堆栈里pop出来
	for (int k= 0; k < c[xn][yn];k++) {
		if (k != c[xn][yn] - 1)
			printf("%c ", pop(s));
		else printf("%c\n", pop(s));
	}
	}

int main() {
	//创建两个数组保存子列大小与过程
	int c[100][100], B[100][100];
	//创建两个序列
	char x[100], y[100];
	//输入两个序列大小
	int xn, yn;
	scanf_s("%d %d", &xn, &yn);
	getchar();
	//输入两个序列
	for (int i = 1; i <= xn; i++)
		scanf_s("%c", &x[i]);
	for (int j = 0; j <= yn; j++) {
		scanf_s("%c", &y[j]);
	}
	//初始化c数组
	for (int i = 0; i <=xn; i++) {
		for (int j = 0; j <= yn; j++) {
			if (i == 0 || j == 0) {
				c[i][j] = 0;
			}
		}
	}
	//求最大子列和的长度数组
	Max(c, B, x, y,xn,yn);



}