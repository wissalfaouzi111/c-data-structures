#include "set_dynamic.h"

void set__print(const struct set* se){
    printf("{  .size = %ld, .capacity = %ld, .s = {",se->size,se->capacity);
    for (size_t i=0;i < se->size; i++){
        printf("%d",se->s[i]);
        if (i != se->size -1){
            printf(",");
        }
    }
    printf("}  }\n");
}


/*void s_D(struct set se){
    struct set* se=malloc()
    

    if (se.capacity==0){
        se.capacity=1;
    }
    else if (se.capacity==se.size){
        se.capacity*=2;
    }

}*/