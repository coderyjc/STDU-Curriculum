#include"SqList.h"

//<< data structure >> (tsinghua university press, yan weimin/wu weimin)

Status ListDelete_Sq(SqList& L, int i, ElemType& e){
    //delete the i elem and return its value
    // leagel 1 ~ ListLength(L)

    if((i < 1) || (i > ListLength(L))) return ERROR; //i is illeagel
    ElemType* p = &(L.elem[i - 1]);
    e = *p; //value
    ElemType* q = L.elem + L.length - 1; // tail
    for(++p; p <= q; ++p) *(p - 1) = *p; //cover element
    --L.length;
    return OK;
} //ListDelete_Sq



//----------------------test----------------------------




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
	ElemType e;
	ListDelete_Sq(L, 3, e);

	printf("\nAfterDelete: ");
	Print(L);
	printf("\ne  =  %d", e);
	DestoryList(L);

	return 0;
}
