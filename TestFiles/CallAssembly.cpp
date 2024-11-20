int add(int x,int y){
    return x+y;
}

int caller(){
    int temp1 = 125;
    int temp2 = 80;
    int sum = 0; 
    sum = add(temp1,temp2);
    return sum;
}

int main(){
    int a = 0xFF;
    caller();
    return 0;
}