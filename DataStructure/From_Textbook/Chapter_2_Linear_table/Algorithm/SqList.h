#include"header.h"

#define LIST_INIT_SIZE 100 //initial size
#define LISTINCREMENT 10 //evety time increase

typedef struct {

	ElemType* elem; //list body
	int length; // number of elements
	int listsize; // capacity

}SqList;

Status InitList_Sq(SqList& L) {
	//create a new empty list
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW); // fail to alloc memory
	L.length = 0; // empty length is 0
	L.listsize = LIST_INIT_SIZE; // initial capacity
	return OK;
} //InitList_Sq

int ListLength(SqList L) { return L.length; }

int ListEmpty(SqList L) { return L.length == 0; }

Status GetElem(SqList L, int i, ElemType& e) {
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	return OK;
}

Status PriorElem(SqList& L, ElemType* cur_e, ElemType& pre_e) {
	if (!L.elem || (cur_e == L.elem)) return ERROR;
	pre_e = *(cur_e - 1);
	return OK;
}

Status NextElem(SqList& L, ElemType* cur_e, ElemType& next_e) {
	if (!L.elem || cur_e >= L.elem + L.length - 1) return ERROR;
	next_e = *(++cur_e); 
	return OK;
}

Status DestoryList(SqList& L) {
	free(L.elem);
	L.length = 0;
	L.listsize = 0;
	return OK;
}

Status ClearList(SqList& L) {
	L.length = 0;
	return OK;
}

Status Traverse(SqList L, void (*visit)(ElemType*)) {
	ElemType* e = L.elem;
	int n = L.length;
	while (n--)
		(*visit)(e++);
	return OK;
}

// ----------- Test ----------------------

void Print(SqList L) {
	printf("List : ");
	for (int i = 0; i < L.length; i++)
		printf("%d ", L.elem[i]);
}

void print(ElemType* e) { printf("%d ", *e); }


int main() {
	SqList L;
	InitList_Sq(L);
	for (int i = 0; i < 12; i++, L.length += 1) L.elem[i] = i;

	printf("ListInit:"); Print(L);

	printf("\nListLength: %d\n", ListLength(L));

	printf("ListEmpty: %d\n", ListEmpty(L));

	ElemType e = 0;
	GetElem(L, 8, e);
	printf("GetElem(L, 8, e) : %d\n", e);

	ElemType  pre = 0,  next = 0;
	ElemType* p = L.elem;
	ElemType* q = L.elem + L.length - 1;

	printf("p = L.elem;q = L.elem + L.length - 1;\n");
	
	if(PriorElem(L, p, pre)) printf("PriorElem(L, p, pre) : %d\n", pre);
	if (PriorElem(L, q, pre)) printf("PriorElem(L, q, pre) : %d\n", pre);
	if (NextElem(L, p, next)) printf("PriorElem(L, p, next) : %d\n", next);
	if (NextElem(L, q, next)) printf("PriorElem(L, q, next) : %d\n", next);
	
	printf("traverse:");
	Traverse(L, print);
	DestoryList(L);
	
	return 0;
}