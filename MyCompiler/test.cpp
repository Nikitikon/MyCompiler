int hanoi(int quantity, int from, int to, int buf_peg)
{
    if (quantity != 0)
    {
        hanoi(quantity-1, from, buf_peg, to);
        
        print(from);
        print(" -> ");
        print(to);
        print("\n");
        
        hanoi(quantity-1, buf_peg, to, from);
    }
    
    return 1;
}

int main (void){
    int star = 1;
    int des = 3;
    int buf = 2;
    int plate = 3;
    int i;
    i = hanoi(plate, star, des, buf);
    
    return 0;
}
