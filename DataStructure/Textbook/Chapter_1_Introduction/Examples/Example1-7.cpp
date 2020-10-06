#include"header.h"

typedef ElemType* Triplet;

Status InitTriplet(Triplet& T, ElemType v1, ElemType v2, ElemType v3){
    T = (ElemType *)malloc(3 * sizeof(ElemType));
    if(!T) exit(OVERFLOW); //not have enough memory
    T[0] = v1;
    T[1] = v2;
    T[2] = v3;
    return OK;
}

Status DestoryTriplet(Triplet& T){
    //if(!T) return 
    free(T);
    T = NULL;
    return OK;
}

Status Get(Triplet T, int i, ElemType& e){
    if(i < 1 || i >= 3) return ERROR;
    e = T[i - 1];
    return OK;
}

Status Put(Triplet& T, int i, ElemType e){
    if(i < 1 || i >= 3) return ERROR;
    T[i] = e;
    return OK;
}

bool IsAscending(Triplet T){
    return ((T[0] < T[1]) && (T[1] < T[2]));
}

bool IsDescending(Triplet T){
    return ((T[0] > T[1]) && (T[1] > T[2]));
}

ElemType Max(Triplet T, ElemType& e){
/*
    Line 45 is copied from our textbook, but I don't know why there is something wrong with it...
    
    e = ((T[0] >= T[1]) ? ((T[0] >= T[2]) ? T[0] : T[2]) : ((T[1] >= T[2]) ? T[1] : T[2]));
*/
    e = T[0] > T[1] ? T[0] : T[1];
    e = e > T[2] ? e : T[2];
    return OK;
}

ElemType Min(Triplet T, ElemType& e){
/*
    Line 45 is copied from our textbook, but I don't know why there is something wrong with it...
    
    e = ((T[0] <= T[1]) ? ((T[0] <= T[2]) ? T[0] : T[2]) : ((T[1] <= T[2]) ? T[1] : T[2]));
*/   
    e = T[0] < T[1] ? T[0] : T[1];
    e = e < T[2] ? e : T[2];
    return OK;
}

//--------------------hava a test

int main(){
    Triplet T;

    InitTriplet(T, 7, 8, 9);
    printf("InitTriplet : %d %d %d\n", T[0], T[1], T[2]);
    ElemType e = 0;

    Get(T, 2, e);
    printf("GET 2 : %d\n", e);
    printf("PET 2 : %d\n", Put(T, 2, e));
    printf("PET 3 : %d\n", Put(T, 3, e));
    printf("T[0] = %d T[1] = %d T[2] = %d\n", T[0], T[1], T[2]);
    printf("IsAscending : %d\n", IsAscending(T));
    printf("IsDescending : %d\n", IsDescending(T));

    Max(T, e);
    printf("Max : %d\n", e);
    Min(T, e);
    printf("Min : %d\n", e);

    return 0;
}