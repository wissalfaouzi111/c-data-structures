#include "set_dynamic.h"
 
static void test_set__print(void){
    printf("%s\n",__func__);
    int s[]={1,2,3,4,5};
    struct set s1={s,8,4};
    set__print(&s1);
}
int main(){
    test_set__print();
}