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
	//i��ʾ����x���±꣬j��ʾ����y���±�
	//B[i][j] o��ʾɾ��x��ĩβһλ��1��ʾɾ��ĩβһλ��2��ʾɾ��x,y����ĩβ��λ
	int i, j;
	//temp1,temp2�ֱ��ʾx��y�����Ԫ�ص��±�
	char temp1, temp2;
	for (i = 1; i <= xn; i++) {
		for (j = 1; j <= yn; j++) {
			//���x[i]=y[j]����ôc[i][j]=c[i-1][j-1]+1,B[i][j]=2
			//�������ȣ���Ϊ��max{c[i][j-1],c[i-1][j]},BΪ1/0
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
	//B[i][j]=0��x�±��һ��=1��y�����±��һ��=2��x,y�����±�ͬʱ��1�����ҽ�Ԫ��push����ջ��
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
//��������дӶ�ջ��pop����
	for (int k= 0; k < c[xn][yn];k++) {
		if (k != c[xn][yn] - 1)
			printf("%c ", pop(s));
		else printf("%c\n", pop(s));
	}
	}

int main() {
	//�����������鱣�����д�С�����
	int c[100][100], B[100][100];
	//������������
	char x[100], y[100];
	//�����������д�С
	int xn, yn;
	scanf_s("%d %d", &xn, &yn);
	getchar();
	//������������
	for (int i = 1; i <= xn; i++)
		scanf_s("%c", &x[i]);
	for (int j = 0; j <= yn; j++) {
		scanf_s("%c", &y[j]);
	}
	//��ʼ��c����
	for (int i = 0; i <=xn; i++) {
		for (int j = 0; j <= yn; j++) {
			if (i == 0 || j == 0) {
				c[i][j] = 0;
			}
		}
	}
	//��������к͵ĳ�������
	Max(c, B, x, y,xn,yn);



}