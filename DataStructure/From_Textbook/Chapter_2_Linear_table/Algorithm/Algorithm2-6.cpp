#include"SqList.h"

//<< data structure >> (tsinghua university press, yan weimin/wu weimin)

void MergeList_Sq(SqList& La, SqList& Lb, SqList& Lc)
{
	//elements in the linear table La Lb are arranged in non-decreasing order
	//Merge La and Lb to obtain a new sequential linear table
    //and the elements of Lc are also arranged in non-decreasing order
	ElemType* pa = La.elem;
	ElemType* pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	ElemType* pc = Lc.elem = (ElemType*)malloc(Lc.length * sizeof(ElemType));
	if (!Lc.elem) exit(OVERFLOW); //fail to malloc
	ElemType* pa_last = La.elem + La.length - 1;
	ElemType* pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last){//merge
		if (*pa < *pb)
            *pc++ = *pa++;
		else 
            *pa++ = *pb++;
	}
	while(pa < pa_last)  *pc++ = *pa++; // insert rest elem
	while(pb < pb_last) *pc++ = *pb++; // insert rest elem
} //MergeLisst_Sq


//------------------------------test


void Print(SqList L) {
	printf("List : ");
	for (int i = 0; i < L.length; i++)
		printf("%d ", L.elem[i]);
}

int main() {
	SqList L1;
	SqList L2;
	SqList L3;
	InitList_Sq(L1);
	InitList_Sq(L2);
	InitList_Sq(L3);
	for (int i = 0; i < 6; i++, L1.length += 1) L1.elem[i] = i;
	for (int i = 0; i < 6; i++, L2.length += 1) L2.elem[i] = i + 3;
	printf("Init : \n");
	Print(L1); 
	printf("\n");
	Print(L2);
	printf("\n");
	MergeList_Sq(L1, L2, L3);
	printf("L3 : ");
	Print(L3);
	return 0;
}
