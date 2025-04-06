#include <iostream>
using namespace std;

struct subforwardlist {
     int data;
     subforwardlist* next;
};

void init(subforwardlist **sfl){
    *sfl = NULL;
}
void push_back(subforwardlist **sfl, int d){
    if (*sfl == NULL){
        subforwardlist* new_list = new subforwardlist;
        new_list ->data =d;
        new_list ->next = NULL;
        *sfl = new_list;
    }
    else{
        subforwardlist* new_list = new subforwardlist;
        new_list->data = d;
        new_list->next = NULL;
        subforwardlist* tmp;
        tmp= *sfl;
        while (tmp->next != NULL){
            tmp=tmp->next;
        }
        tmp->next = new_list;
    }

}

int pop_back(subforwardlist **sfl){
    if (*sfl == NULL){
        return 0;
    }
    subforwardlist* tmp = *sfl;
    if (tmp->next == NULL) {
        int d1 = tmp->data;
        delete tmp;
        *sfl = NULL;
        return d1;
    }
   subforwardlist* tmp1 = *sfl;
    while (tmp1->next->next != NULL) {
        tmp1 = tmp1->next;
    }
    int d = tmp1->next->data;
    delete tmp1->next;
    tmp1->next = NULL;

    return d;     
}

void push_forward(subforwardlist **sfl, int d){
    subforwardlist* new_sfl= new subforwardlist;
    new_sfl->data = d;
    new_sfl->next = *sfl;
    *sfl = new_sfl;
}

int pop_forward(subforwardlist **sfl){
    if (*sfl == NULL){
        return 0;
    }
    else {
        subforwardlist* tmp;
        tmp= *sfl;
        int d;
        d = tmp->data;
        subforwardlist* new_sfl;
        new_sfl= tmp->next;
        delete tmp;
        *sfl = new_sfl;
        return d;
    }
}

unsigned int size(subforwardlist  *sfl){
    unsigned int a=0;
    if (sfl == NULL){
        return 0;
    }
    while (sfl != NULL){
        a++;
        sfl = sfl->next;
        
    }
    return a;
}

bool push_where(subforwardlist **sfl, unsigned int where, int d){
    if (where == 0){
        push_forward(sfl, d);
        return true;
    }
    subforwardlist* new_sfl = new subforwardlist;
    new_sfl->data = d;
    subforwardlist* tmp;
    tmp = *sfl;
    for (unsigned int i=1; i<where; i++){
        tmp=tmp->next;
    }
    if (tmp == NULL){
        cout << "Eblan: where > size" << endl;
        return false;
    }
    new_sfl->next = tmp->next;
    tmp->next = new_sfl;
    return true;
}

int erase_where(subforwardlist **sfl, unsigned int where){
    if (*sfl == NULL){
        return 0;
    }
    if (where == 0){
        return pop_forward(sfl);
    }
    subforwardlist* tmp = *sfl;
    for (int i=1; i<where; i++){
        tmp = tmp->next;
    }
    if (tmp == NULL || tmp->next == NULL){
        cout << "eblan: where > size" << endl;
        return 0;
    }
    int d=tmp->next->data;
    subforwardlist* tmp1 = tmp->next->next;
    delete tmp->next;
    tmp->next = tmp1;
    return d;
}

void clear(subforwardlist  **sfl){
    if (sfl == NULL || *sfl == NULL) {
        return;
    }
    subforwardlist* tmp = *sfl;
    while (tmp != NULL) {
        subforwardlist* to_delete = tmp;
        tmp = tmp->next;
        delete to_delete;
    }
    *sfl = NULL;
}