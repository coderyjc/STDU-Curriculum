#include"SqList.h"

//<< data structure >> (tsinghua university press, yan weimin/wu weimin)

Status ListInsert_Sq(SqList& L, int i, ElemType e)
{
	// insert e after elem i in the list
	if (i < 1 || i > L.length + 1) return ERROR; //i illeagel
	if (L.length >= L.listsize) { //increade memory
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.length + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW); //faile to realloc
		L.elem = newbase; 
		L.listsize += LISTINCREMENT; //add capacity
	}
	ElemType* q = &(L.elem[i - 1]); //q insert position
	for (ElemType* p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p; // to right
	*q = e; // insert e
	++L.length;
	return OK;
} //ListInsert_Sq


//--------------------test--------------------------

void Print(SqList L) {
	printf("List : ");
	for (int i = 0; i < L.length; i++)
		printf("%d ", L.elem[i]);
}


int main() {
	SqList L;
	InitList_Sq(L);
	for (int i = 0; i < 12; i++, L.length += 1) L.elem[i] = i;
	printf("Init : ");
	Print(L);

	ListInsert_Sq(L, 1, 0);

	printf("\nAfterInsert: ");
	Print(L);

	DestoryList(L);

	return 0;
}