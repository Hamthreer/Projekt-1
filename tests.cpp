#include "sorts.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <cmath>

void is_open(std::ofstream &file){
    if (!file.is_open()){
        std::cout << "Not open";
        exit(1);
    }
}

using SortPointer = void (*)(int*,int*,int,int,int);

int *create_table(int n){
    return new int[n];
}

void delete_table(int *tab){
    delete[] tab;
}

void table_random(int *tab,int n){
    for (int i = 0; i < n; i++){
        tab[i] = rand();
    }
}

void table_percent(int *tab,int n,double percent){
    if (percent == 100){
        std::sort(tab, tab+n,std::greater<>());
        return;
    }
    std::sort(tab, tab + int(n*percent)/100);
}

void is_sorted(int *tab, int n){
    for (int i =0; i < n - 1; i++){
        if (tab[i]>tab[i + 1]){
            std::cout << "Not sorted";
            exit(1);
        }
    }
}

double sort(SortPointer sort, int n, int *tab, int *tmp){
    auto time_start = std::chrono::high_resolution_clock::now();
    sort(tab, tmp, 0, n-1, log(n)*2);
    auto time_stop = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double , std::milli>(time_stop-time_start).count();
}

int main(){
    int tables = 100;

    std::ofstream file("TimeOfSorts.txt");
    is_open(file);

    int sizeTab[5] = {10000,50000,100000,500000,1000000};
    double percentTab[8] = {0,25,50,75,95,99,99.7,100};

    SortPointer quickPointer = &quickS, mergePointer = &mergeS, introPointer = &introS;

    SortPointer pointTab[3] = {quickPointer,mergePointer,introPointer};
    std::string sortsTab[3] = {"QUICK_SORT", "MERGE_SORT", "INTRO_SORT"};

    int i = 0;
    double j = 0;
    for(SortPointer sortP : pointTab){
        std::cout<< sortsTab[i++] << std::endl;

        for (double percent : percentTab){
            std::cout << percent << " %" << std::endl;
            for (int n : sizeTab){
                int *tab = create_table(n);
                int *tmp = create_table(n);

                for (int i = 0; i < tables; ++i) {
                    table_random(tab,n);
                    table_percent(tab,n,percent);
                    j += sort(sortP,n,tab,tmp);
                    is_sorted(tab,n);
                }
                delete_table(tab);
                delete_table(tmp);
                
                std::cout << n << std::endl;

                file << j/tables << " ";


                j = 0;
            }
        }
        file << "\n";
    }
    std::cout << "endofsort";
    file.close();

    return 0;
}