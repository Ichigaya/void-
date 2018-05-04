#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct PS
{
	int tu, mau;
};

struct Node
{
	void *key;
	Node *next;
};

Node *getNode(void *x, int size)
{
	Node *p = (Node*)malloc(sizeof(Node));
	if (p == NULL)
	{
		printf("Khong du bo nho!\n");
		return NULL;
	}
	p->key = (PS*)malloc(sizeof(PS));
	p->next = NULL;
	if (p->key == NULL)
	{
		printf("Khong du bo nho!\n");
		free(p);
		return NULL;
	}
	memcpy(p->key, x, size);
	return p;
}

void addFirst(Node *&head, Node *&tail, void *x, int size)
{
	if (x == NULL)
		return;
	Node *p = getNode(x, size);
	if (head == NULL)
	{
		head = p;
		tail = p;
		return;
	}
	if (p != NULL);
	{
		p->next = head;
		head = p;
	}
}

void addLast(Node *&head, Node *&tail, void *x, int size)
{
	if (x == NULL)
		return;
	Node *p = getNode(x, size);
	if (tail == NULL)
	{
		head = p;
		tail = p;
		return;
	}
	if (p != NULL);
	{
		tail->next = p;
		tail = p;
	}
}

int Count(Node *head, Node *tail)
{
	if (head == NULL)
		return 0;
	int result = 0;
	Node *p = head;
	while (p != NULL)
	{
		result++;
		p = p->next;
	}
	return result;
}

void addMiddle(Node *&head, Node *&tail, void *x, int size, int pos)
{
	if (x == NULL) return;
	if (pos == 0) addFirst(head, tail, x, size);
	else
	{
		int t = Count(head, tail);
		if (pos > t) 
		{
			addLast(head, tail, x, size);
			return;
		}
		;
		int i;
		Node *p, *pre;
		p = getNode(x, size);
		if (p == NULL)
		{
			printf("Khong du bo nho!");
			return;
		}
		for (i = 0, pre = head; i < pos - 1; i++, pre = pre->next);
		p->next = pre->next;
		pre->next = p;
	}
}

void deleteFirst(Node *&head, Node *&tail)
{
	if (head == NULL)
	{
		printf("Danh sach rong!");
		return;
	}
	Node *p = head;
	head = head->next;
	free(p);
}

void deleteEnd(Node *&head, Node *&tail)
{
	if (head == NULL)
	{
		printf("Danh sach rong");
		return;
	}
	Node *p = head;
	while (p->next->next != NULL) p = p->next;
	p->next = NULL;
	free(tail);
	tail = p;
}

void deleteMiddle(Node *&head, Node *&tail, int pos)
{
	if (head == NULL)
	{
		printf("Danh sach rong!");
		return;
	}
	if (pos == 0)
	{
		deleteFirst(head, tail);
		return;
	}
	int t = Count(head, tail);
	if (pos >= t)
	{
		deleteEnd(head, tail);
		return;
	}
	else
	{
		int i;
		Node *pre;
		for (i = 0, pre = head; i < pos - 1; i++, pre = pre->next);
		Node *p = pre->next;
		pre->next = p->next;
		free(p);
	}
}

bool fracCmp(void *a, void *b)
{
	PS *r = (PS*)a, *s = (PS*)b;
	int s1 = r->tu*s->mau;
	int s2 = r->mau*s->tu;
	return (s1 == s2);
}

Node* scanList(Node *&head, void *k)
{
	Node *p = head;
	while (p != NULL)
	{
		if (fracCmp(k,p->key)) return p;
		p = p->next;
	}
	return NULL;
}

void destroyList(Node *&head)
{
	Node *p;
	while (head)
	{
		p = head;
		head = head->next;
		free(p);
	}
	printf("Da huy danh sach!\n");
}

void printList(Node *head, Node *tail)
{
	if (head == NULL)
	{
		printf("Danh sach rong!\n");
		return;
	}
	Node *p = head;
	PS *u;
	while (p)
	{
		u = (PS*)p->key;
		printf("%d/%d ", u->tu, u->mau);
		p = p->next;
	}
	printf("\n");
}

void main()
{
	Node *head = NULL, *tail = NULL;
	PS x;
	int pos;
	printf("Nhap cac phan so (nhap 'x' de dung):\n");
	while (scanf("%d %d", &x.tu, &x.mau))
	{
		if (x.mau != 0)
			addLast(head, tail, &x, sizeof(PS));
		else
			printf("Nhap khong hop le! (Mau so khac 0)\n");
	}
	printList(head, tail);
	printf("So luong phan tu: %d\n", Count(head, tail));
	fflush(stdin);
	printf("Nhap vao phan tu can chen:\n");
	scanf("%d %d", &x.tu, &x.mau);
	printf("Nhap vao vi tri can chen:\n");
	scanf("%d", &pos);
	addMiddle(head, tail, &x, sizeof(PS), pos);
	printList(head, tail);
	deleteFirst(head, tail);
	printf("Da xoa phan tu dau! Nhan enter de tiep tuc...\n");
	printList(head, tail);
	getch();
	deleteEnd(head, tail);
	printf("Da xoa phan tu cuoi! Nhan enter de tiep tuc...\n");
	printList(head, tail);
	getch();
	printf("Nhap vao vi tri phan so can xoa:\n");
	scanf("%d", &pos);
	deleteMiddle(head, tail, pos);
	printList(head, tail);
	printf("Nhan enter de huy danh sach...\n");
	getch();
	destroyList(head);
	system("pause");
}