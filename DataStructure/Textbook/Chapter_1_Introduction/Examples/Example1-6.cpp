#include"header.h"

typedef ElemType* Triplet;

Status InitTriplet(Triplet& T, ElemType v1, ElemType v2, ElemType v3);

Status DestoryTriplet(Triplet& T);

Status Get(Triplet T, int i, ElemType& e);

Status Put(Triplet& T, int i, ElemType e);

bool IsAscending(Triplet T);

bool IsDescending(Triplet T);

ElemType Max(Triplet T, ElemType& e);

ElemType Min(Triplet T, ElemType& e);