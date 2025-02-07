## Notes from Yale floating point lesson
> Real numbers are represented in C by float, double and long double.They are always approzimations. Most of math fucntions return `double`s like 'double sin double' but there float versions as well, like 'float sinf(float)'

> Float number reprerentation is based on fixed point representation, written as

    - m*b^e where 
    - m is mantissa or fractional part
    - b is base which is always 2
    - e is exponant

> mantissa will be scaled between 1 and b by adjusting exponent. This past for basic humans

    1 = 1 * 2^0
    2 = 1 * 2^1
    0.375 = 1.5 *2^-2 // remember how we solve things!

> The mantissa is usually represented in base b, sa a binary fraction. This part is for us.

    1 = 1.000*2^0
    2 = 1.000*2^1
    0.375 = 1.100*2^-2 
    
    here base is not 10, it is 2
    Here first digit after decimal point caunts as 1/2
    second digit is 1/4, so 1.100 is 1 and 1/2.
    For regular people, 1.1 in base 2 is 1.5 in base 10.

> What if we already we using base 8 in our lifes. 1.4 would be enough. Evolution destroyed  us with 5 finger. We needed just 4. Lets keep going.

> Note that, the normalized floating point number in based to the digit before decimal point is always 1. For this reason it si usually dropped. Although this requires special representation for 0. Haha, remember that. There is no zero. Nobody can imagine it. TODO: lets talk about it later.

> For negative values we add a sign bit as 1.

> Any numbe has a digit after decimal counts as float. And for scientific notation we use e for exponent. 6.022e23 is a number we all know. Don't you know? Poor regular people, you deserve the best.

> Integer devision and floating point number devisions are different. Be careful regular poeple. 2/3 is 0 while 2.0/3 is the thing you ask. I hope you can estimate.

> We have force casting for getting float number devisions. Life is tradeoff. There is nothing free.
```c
/* return the average */
double
average (int n, int a[])
{
    int sum = 0;
    int i;

    for (i=0; i < n; i++){
        sum += a[i];
    }
    return (double) sum / n;
    // you don't want to truncate the fractional part!
}
```

## IEEE-754
> It is our standar to show floating numbers.

    bit 32 30.....23 22...................0
        S  EEEEEEEE  MMMMMMMMMMMMMMMMMMMMMM

> Bit numbers are counting from the least significant bit. The first bit is the sign(0 for positive 1 for negative). Next part is 8bits of exponent in `excess-127` notation. This means that the binary pattern

    01111111 = 127 represent an exponent of 0. 
    10000000 = 128 represents 1.
    01111110 = 126 represents -1. You got it

> The remaning mantissa 24 bits is mantissa, with its 1 stripped as you remember.

> As i asked you before. What about zero? Sign bit 0 makes it positive.

    0 00000000 0000000000000000000000 : +0
    1 00000000 0000000000000000000000 : -0, isn't it 128?
    0 01111111 0000000000000000000000 : 1
    // 01111111 is exponent of 0, remember 127 - 127.

    0 10000000 0000000000000000000000 : 2
    0 01111110 0000000000000000000000 : 0.5
    // 126 - 127 = -1, 2^-1 = 0.5
    // now you start thinking about
    01111110 goes like -1, resulting 0.5
    01111101 goes like -2, resulting 0.25
    01111100 goes like -3, resulting 0.125
    // seems like EEEEEEEE ^ 0x00 right ?

    // mantissa always zero, why ? Since it is multiplier
    // and all examples we used  was exact power of two
    // if you need 0.375 mantissa becomes like
    10000000000000000000000

    0 11111111 0000000000000000000000 : inf
    1 11111111 0000000000000000000000 : -inf
    0 11111111 1000000000000000000000 : NaN

> In practice a 32-bit floating number can represent any number between 1.17549435e-38 and 3.40282347e+38.

> Double one is 64 bit and hits a range 1.79e-308 to 2.22e+308.

> Rounding is our problem with floating numbers. We use a bit each time and it accumulates by calling operations with them. So to be safe using double instead of float helps to keep the lose small. And take a care for castings, and roundings going on. Nothing is free in this life.

> Integer calculations are must easier and much faster but limited like 2^32 for 32bit. If you need to count billions you double.

> Floating numbers are almost impossible to compare unless the number is not exact power of 2^-something.
```c
if(0.1 + 0.1 + 0.1 == 0.3) // this would work
for(f = 0.0; f <= 0.3; f += 0.1) // this is hard to predict.

// If you wanna gamble:
for(f = 0.0; f != 0.3; f += 0.1) 
// who knows when it will round enough to hit :)

// do not use floating numbers for comparisons.
```

> Do not use floating numbers for comparisons.

> If you have to use floats to compare something, remember newton-rapson. Don't you know regular people. No worries, you deserve the best. We work!

```c
// test operations when you compare floats
fabs(x-y) <= fabs(EPSILON * y)
// EPSILON, is tolerance. How come? Belive in Newton!
```

> Any constant that contains decimal point is treated as a double by default in C. 

> If you want to insist that a constant value is float you can append F on the end, as in `1.0F`. I have forgetten.

> For IO operations floating point values are most easily read and written using `scanf, fscanf, sscanf and printf`

> For scanf you need `"%lf"`, to read double value to double *. And you use `"%f"` to read float value to float *. They are exact same in printf.

> There are INFINITY and NAN const in <math.h> you can use if you need. There are also functions to check them like isinf() and isnan().

> To link math library in compiling we use `-lm` flag.

    gcc -o program program.c -lm

