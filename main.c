#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define train_count 4
typedef float sample[3];
//or_gate
sample or_train[]={
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1}
};
//and_gate
sample and_train[]={
    {0,0,0},
    {0,1,0},
    {1,0,0},
    {1,1,1}
};
//Nand_gate
sample Nand_train[]={
    {0,0,1},
    {0,1,1},
    {1,0,1},
    {1,1,0}
};
sample *train=and_train;
float sigmoidf(float x){
    return 1.f/(1.f+expf(-x));
}
float cost(float W1,float W2, float b){
    float x1,x2,y,d;
    float result=0.0f;
    for(int i=0;i<train_count;i++){
        x1=train[i][0];
        x2=train[i][1];
        y=sigmoidf(x1*W1+x2*W2+b);
        d=train[i][2]-y;
        result+=d*d;
    }
    return result/train_count;
}
float rand_float(void){
    return (float) rand()/ (float) RAND_MAX;
}

int main(){
   
    srand(time(0));
    float w1=rand_float();
    float w2=rand_float();
    float b=rand_float();
    float eps=1e-1;
    float rate=1e-1;
    
    printf("%f %f\n", w1,w2);
    for(int i = 0; i < 10000; i++ ){
        float dw1= ( cost( w1+eps ,w2,b ) - cost(w1,w2,b) ) / eps;
        float dw2=( cost( w1, w2+eps,b ) - cost(w1,w2,b) ) / eps;
        float db=(cost(w1,w2,b+eps)-cost(w1,w2,b)) / eps;
        w1-= dw1*rate;
        w2-= dw2*rate;
        b-=db*rate;
    }
    printf("w1=%f w2=%f b=%f cost=%f\n", w1,w2,b,cost(w1,w2,b));
    printf("%f %f %f %f\n", sigmoidf(w1),sigmoidf(w2),sigmoidf(b),cost(w1,w2,b));
   for( int i=0;i<2;i++){
    for(int j=0;j<2;j++){
        printf("%zu | %zu = %f\n", i,j,sigmoidf(i*w1+j*w2+b));
    }
   }
}