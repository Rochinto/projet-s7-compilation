let x = 1;
let g(x,y) = let z = 3 in (x+y+z);
let y = 2;
let w(w) = if (w<2) then 1 else 0;
let z = g(x,w(x));