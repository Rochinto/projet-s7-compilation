let x = 5;
let g(x,y) = let z = 3 in (x+y+z);
let h(x) = let y = 5 in g(x,y);
let y = 2;
let z = h(y);
let r = 10;