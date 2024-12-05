let fibo(n) = 
    if(n<=1) then 
        if(n<=0) then 
            0 
        else 1
    else 
        (fibo(n-2)+fibo(n-1))
    ;
let f7 = fibo(7);
let f8 = fibo(8);