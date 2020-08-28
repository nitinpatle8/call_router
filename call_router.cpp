#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

#define MAX_BASE 8
#define MAX_MOBILE 100

#define long long int lli

#define hashFunction(id_no, x) (id_no-8)*100 + x%100 

class Exchange{ // Consider Exchange and base station same
    private:
        int id_no;
        int set[MAX_BASE]; // points the starting index in the array 
    
        struct Node* left;
        struct Node* right;
    
    public:
        Exchange(){
            for(int i = 0; i<MAX_BASE; i++){
                this->set[i] = -1;
            }
            this->left = NULL;
            this->right = NULL;
        }
        int getId(){
            return this->id_no;
        }
        void setId(int id_no){
            this->id_no = id_no;
        }
}


void createTree(){
    int i = 0;
    queue<Exchange*> q;
    
    Exchange *e = new Exchange()

    
}





