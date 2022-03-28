#include <iostream>
#include <algorithm>

int partition(int *tab,int l, int r){
    int i = l, j = r, key = tab[(l+r)/2];
    while(true){
        while (tab[j]>key) {
            j--;
        }
        while (tab[i]<key) {
            i++;
        }
        if (i<j){
            std::swap(tab[i++],tab[j--]);
        }
        else {
            return j;
        }
    }
}
void quick_sort(int *tab,int l,int r){
    if(l<r){
        int q = partition(tab,l,r);

        quick_sort(tab, l, q);

        quick_sort(tab, q+1, r);
    }
}
void quickS(int *tab, int *tmp, int l, int r, int mdepth){
    quick_sort(tab,l,r);
}
//
//
//
void merge(int *tab, int *tmp, int l,int m,int r){
    int i=l,j=m+1,k=l;
    for (int i = l; i <= r; i++){
        tmp[i]=tab[i];
    }
    while (i <= m && j <= r){
        if (tmp[i]<tmp[j]){
            tab[k++]=tmp[i++];
        }
        else{
            tab[k++]=tmp[j++];
        }
    }
    while (i <= m){
        tab[k++] = tmp[i++];
    }
}
void merge_sort(int *tab,int *tmp, int l,int r){
    if (l<r){
        int m=(r+l)/2;
        merge_sort(tab,tmp,l,m);
        merge_sort(tab,tmp,m+1,r);
        merge(tab,tmp,l,m,r);
    }
}
void mergeS(int *tab, int *tmp, int l, int r, int mdepth){
    merge_sort(tab,tmp,l,r);
}
//
//
//
void inssort(int *tab,int l,int r){
    for (int i = l + 1; i <= r; i++){
        int j = i;
        int k = tab[i];

        while (j>l && tab[j-1]>k){
            tab[j] = tab[j-1];
            j--;
        }
        tab[j]=k;
    }
}
void heapsort(int *l, int *r){
    std::make_heap(l,r);
    std::sort_heap(l,r);
}
void introsort(int *tab, int *l, int *r, int mdepth){
    if ((r-l) < 16){
        inssort(tab,l-tab,r-tab);
    }else if (mdepth == 0){
        heapsort(l,r+1);
    }else{
        int q = partition(tab,l-tab,r-tab);
        introsort(tab, l,tab+q,mdepth-1);
        introsort(tab, tab + q + 1,r,mdepth-1);
    }
}
void introS(int *tab, int *tmp, int l, int r, int mdepth){
    introsort(tab, tab, tab + r, mdepth);
}
