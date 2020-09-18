int sqrt(int number)
{
    float temp, sqrt;

    sqrt = number / 2;
    temp = 0;

    while(sqrt != temp){
        
        temp = sqrt;
        sqrt = ( number/temp + temp) / 2;
    }
    return sqrt;
}

int prime(long int pr)
{
    int i, j;
    j = sqrt(pr);
    for(i = 2; i <= j; i++)
    {
    if(pr % i == 0)
        return 0;
    }
    return 1;
}


int pow(int arg1, int arg2)
{
    if (arg2 == 0) 
        return 1;
    
    else if (arg2 % 2 == 0) 
        return pow(arg1, arg2 / 2) * pow(arg1, arg2 / 2); 
    
    else
        return arg1 * pow(arg1, arg2 / 2) * pow(arg1, arg2 / 2); 
}
