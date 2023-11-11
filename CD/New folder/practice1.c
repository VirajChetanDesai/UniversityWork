#include<stdio.h>
#include<stdlib.h>
struct Mab{
    int offset;
    int size;
    int allocated;
    struct Mab* next;
    struct Mab* prev;
};
typedef struct Mab mab;
typedef mab* mabptr;

mabptr memSplit(mabptr m , int size){
    mabptr newBlock = (mabptr) malloc(sizeof(mab));
    newBlock->offset = m->offset + size;
    newBlock->size = m->size - size;
    newBlock->prev = m;
    newBlock->next = m->next;
    newBlock->allocated = 0;
    if(m->next != NULL){
        m->next->prev = newBlock;
    }
    m->size = size;
    m->next = newBlock;
}

mabptr memMerge(mabptr m){
    if (m->next!=NULL && !m->next->allocated){
        m->size += m->next->size;
        m->next = m->next->next;
        if(m->next  != NULL){
            m->next->prev = m;
        }else if(m->prev!=NULL && !m->prev->allocated){
            m->size += m->prev->size;
            m->prev = m->prev->prev;
            if(m->prev != NULL){
                m->prev->next = m;
            }   
        }
    }
}

mabptr memchk(mabptr m , int size){
    mabptr  current = m;
    while(current != NULL){
        if(current->size > size){
            return current;
        }
        current = current->next;
    }
}

mabptr memFree(mabptr m){
    m->allocated = 0;
    return memMerge(m);
}

mabptr memAllocFCFS(mabptr m,int size){
    mabptr current = memchk(m,size);
    if(current != NULL){
        if(m->size == size){
            m->allocated = 1;
        }else{
            memSplit(m,size);
            m->allocated = 1;
        }
    }
    return m;
}

mabptr memAllocBestFit(mabptr m , int size){
    mabptr current = m;
    mabptr bestFit = NULL;
    int bestFitDifference = INT_MAX;
    while(current != NULL){
        current = memchk(current,size);
        if(size == current->size){
            return current;
        }else{
            if(bestFitDifference > (current->size - size)){
                bestFitDifference = current->size - size;
                bestFit = current;
            }
            current = current->next;
        }
        return bestFit;
    }
}