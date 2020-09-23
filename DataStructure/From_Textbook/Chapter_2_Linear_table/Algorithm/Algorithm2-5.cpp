#include"SqList.h"

//<< data structure >> (tsinghua university press, yan weimin/wu weimin)

int LocateElem(SqList L, ElemType e, Status (*compare)(ElemType, ElemType)){
    //Find the order of the first element that satisfies 'compare' with 'e'
    int i = 1; //i is initial order
    ElemType* p = L.elem;
    while(i <= L.length && !(*compare)(*p++, e)) ++i;
    if(i < L.length) return i; //fint it
    else return 0; //not found
}