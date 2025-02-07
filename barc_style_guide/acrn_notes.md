# Here are notes from Acrn guides
> The ACRN hypervisor is a type 1 reference hypervisor stack, running directly on the bare-metal hardware and is suitable for a variety of iot and embedded devices.

> I don't know what this means :)

> It seems like kind of VM, maybe something like TVM.

## Preprocessors and macros
> Do not combine # and ## operators.
```c
//ok
#define CONCAT(x, y) x ## y
uint32_t ab = 32U;
printf("%d \n", CONCAT(a,b));

//wrong
#define CONCAT(x, y, z) x ## y ## z
```

> Replace function like macros with inline functions.
```c
// make this inline
#define SHOW(a,b) ((a) + (b))

// like this, ok
static inline uint32_t func_show(uint32_t a, uint32_t b){
    return a + b;
}
```

> We have to use guards for headers.
```c
#ifndef SHOW_H
#define SHOW_H

uint32_t func_show(uint32_t param);

#endif
```

> Parantheses is must for parameters in macros
```c
// ok
#define NEGATING(x) -(x)

// wrong
#define NEGATING(x) -x
```

## Compilation units
> Only one assignment shall be on a single line
```c
int a = d;
int b = d;
int c = d;
// not like 
int a = b = c = d;
```

> Only one return statement shall be in a function
```c
// ok
int32_t foo(char *p)
{
    int32_t ret;

    if(ptr == NULL){
        ret = -1
    } else{
        // bla
        ret = 0;
    }
    return ret;
}

// wrong
int32_t foo(char *ptr){
    if(ptr == NULL){
        return -1;
    }
    // bla
    return 0;
}
```

> All code shall be reachable
```c
//ok
uint32_t func_show(void)
{
    uint32_t showcase = 32U;

    printf("showcase is %d \n", showcase);
    return showcase;
}
// wrong
uint32_t func_show(void)
{
    uint32_t showcase = 32U;

    return showcase;
    // wrong
    printf("showcase: %d \n", showcase);
}
```

> Cyclomatic complexity shall be less than 20. It is a calculation based number of edges(possible flow), number of nodes(code blocks, methods) and number of connected components(classes). This evaluation runs for function level, M = E-N+2P. Standard max cyclomatic complexity is 10. Take it with a grain of salt(just like standart max of a function body should by no more than 20 lines rule)

> It helps for less complexity with less path(less branching). More readbility, easier to test, easier to debug.

```c
// here we have 9 edges, 7 nodes, 1 connected component
// 9 - 7 + 1 = 3
if(c1())
    f1();
else
    f2();

if(c2())
    f3();
else
    f4();
```

```c
// do not combine these two functions complexity index
bool is_even(uint32_t param)
{
    bool even = false;
    if(param & 0x01U) == 0U {
        even = true
    }

    return even;
}
// if you combine these to functions to one, complexity will high!
uint32_t func_show(uint32_t param)
{
    uint32_t ret;
    if(param >= 20U){
        ret = 20U;
    } else if (is_even(param)){
        ret = 10U;
    } else {
        ret = 0U;
    }
    return ret;
}
```

> Before using variables do initialize.
```c
// ok
uint32_t a,b;
a = 0U;
b = a;

// wrong
uint32_t a,b;
b = a;
```

> The plain integer constants in C represent signed integers. For example the constant 0 means signed integer zero(`signed octal zero`). But you can also make explicityly unsigned constant by providing suffix u or U. The suffixes `U` and `u` are also required by MISRA-C:2012.

> Initiliaziation of structs shall be enclosed with brackets.
```c
struct struct_show_sub{
    uint32_t t1;
    uint32_t t2;
};

struct struct_show{
    uint32_t t3;
    struct struct_show_sub temp;
};

// ok
struct struct_show show_case = {32u, {32u, 32u}};

//wrong
struct struct_show show_case = {32u, 32u, 32u};
```

> Array size should be specified explicityly
```c
//ok
uint32_t showcase[2] = {0u, 1u};

//wrong
uint32_t showcase[] = {0u, 1u};
```

> Global variables should be declared once and in source file.
```c
// in header file 'show.h'
extern uint32_t g_showcase;
// TODO master the extern usage for all use cases

// in source file 'show.c'
uint32_t g_showcase = 32u;

void func_show(void){
    g_showcase++;
}
```

> Arrays shall be fully initialized.
```c
//ok
uint32_t shows[5] = {1,2,3,4,5};

//wrong
uint32_t shows[5] = {1,2};
```

> Array size shall be a constant value.
```c
// ok
uint32_t arr_shows[10];

//wrong
uint32_t arr_size = 10;
uint32_t arr_shows[arr_size];

// it could be with const and macros
#define ARR_SIZE (10u)
// or
const uint32_t ARR_SIZE = 10u;
// both works with
uint32_t arr_shows[ARR_SIZE];
```

> Non void functions must have return
```c
// ok
uint32_t show(uint32_t param){
    printf("asd %d", param);
    return param;
    // return; -> is wrong, non-void can not just return;
    // they have to return something.
}
// wrong
uint32_t show(uint32_t param){
    printf("asd %d", param);
    // where is return ?
}
```

> Parameter passed by pointer shall not be reassigned
```c
// to be sure pass it const, now we didn't
void func_show(uint32_t *param_ptr){
    uint32_t *local_ptr = param_ptr;

    local_ptr++;
    printf("%d \n", local_ptr);

    //wrong param_ptr++, super wrong!
}
```

> A parameter passed by value shall not be modified directly.
```c
void func_show(uint32_t param){
    uint32_t local = param; 

    // ok
    local++;
    printf("%d \n", local);

    // wrong
    param++; // wrong
    printf("%d \n", param);
}
```

> Non static functions shall be declared in header file.

> Static function shall be used within the file in which it is declared. Source file.

> Instead of dynamic memory allocation use static memory allocation. Do not use malloc, calloc, realloc, free.

> Do no use va_arg, va_start, va_end if it is not must for function taking variable number of parameters like printf.
```c
// ok
uint32_t show_arr[32]; // better than below

// do no use malloc, etc.
uint32_t *show_ptr = (uint32_t *)malloc(32u * sizeof(uint32_t));
```

> Do not return a pointer to a local variable.

> Even if you return a copy of local variable be careful. If you try to reach its address it will be problem.

> Do not use assembly code c code together. Seperate as fucntions.
```c
void asm_hlt(void){
    asm volatile ("hlt");
}

void show(void){
    bool show_flag = true;
    if(show_flag){
        asm_hlt();
    }
}
```
> The last guide was saying to not use != in controls. Now it says we need to do.
```c
// ok
if(param != 0u){ // old compilers has no all bits 0 for 0
// okay but this one is suggested now :)
    printf("param : %d", param);
}

// wrong
if(false){
    printf("param : %d", param);
}
```

> Do not change the loop counter inside loop.

> Do not use goto

> Keep simple loop initializations. (bla; bla < bla; bla++)

> Do not apply negation for unsigned integers.
```c
// ok
int32_t show = -10;

// wrong
int32_t show = -10u;
```

> Do not assign global variable addresses to local addresses. The address with shorter lifetime would not be assigned to something with longer lifetime. It will be invalid in the end of function.
```c
uint32_t *show_glob_ptr;

void show(void){
    uint32_t show_local = 32u;
    uint32_t *show_local_ptr;

    // ok
    show_local_ptr = &show_local;
    printf("*show value %d \n", *show_local_ptr);

    // wrong
    show_glog_ptr = show_local_ptr;
}// glob_ptr becomes invalid here.
```

> Sizeof shall be used for arrays passed to function. It gives pointer size, not array size.
```c
#define SHOW_SIZE 32u

void show(uint32_t arr_src[SHOW_SIZE]){
    // ok
    uint32_t num_bytes = SHOW_SIZE * sizeof(uint32_t);
    printf("size is %d \n", num_bytes);

    //wrong
    uint32_t num_bytes = sizeof(arr_src); // wrong
    // it is so common. Nothing will give you array size.
    // just strlen can give lenght if there is '\0' in end.
}

> Argument of strlen has to end with '\0'
```c
uint32_t size;
char show[3] = {'0', '1', '\0'};
size = stlen(show); // ok

char show[3] = {'0', '1', '2'}; // doesnt work with strlen
// fail
size = strlen(show); // wrong
```

> Use strncpy for copy, n version with len-size
```c
char *str_src = "showcase";
char str_dest[20];
//ok
(void) strncpy(str_dest, str_src, 8u);
// we could use memcpy. there is just one difference.
// strncpy will stop when hits '\0', will not copy all size given if it hits end.
// memcpy copies all bytes in given size
```

> String literal shall not be modified
```c
const char *show = "showcase";
show[1] = 'H'; // wrong
```

> Do not use comma operator. Like a++, b++. Seperate them.

> Bit operands of bit operations shall be unsigned.
```c
// ok
uint32_t show = 32u;
uint32_t mask = 0xFFu;

show = show & mask;

//wrong
uint32_t show = 32u;
uint32_t mask = -1; // wrong, can not be like this
```
> Do not mix integers and boolean values. Arithmetics operations should be with integers. Logical operations shall be with booleans.
```c
//ok
bool show_flag = true;
uint32_t exp = 32u;
uint32_t cond_exp = 64u;

uint32_t showcase = show_flag ? exp : cond_exp;

//wrong
uint32_t flag = 1u;
uint32_t showcase = flag ? exp : cond_exp;
```

> Enum shall not be used for arithmetic operations.

> Do not use static keyword in array index declarations. like this arr[static size].

> Pointer has to be const if you do not modify.
```c
// ok
void func(const uint32_t *ptr){
    printf("value %d \n", *ptr);
}

//wrong
void func(uint32_t *ptr){
    printf("value %d \n", *ptr);
}
```

> Type in tenary should be consistent.
```c
// ok
bool flag = true;
uint32_t exp = 32u;
uint32_t cond_exp = 64u;

uint32_t case = flag ? exp : cond_exp;

// wrong
int exp1 = 1;
uint32_t case = flag ? exp : cond_exp; // types are different
```

> In declaration of struct types should match.
```c
struct show{
    uint32_t t32;
    uint64_t t64;
};

// ok
struct show show1 = {32u, 64ul};

// wrong
struct show show1 = {32, -1};
```
> Const qualifier shall not be dicarded in cast operation
```c
const uint32_t *show;

//ok
const uint32_t *case = show;

// seems like same operation, but wrong. We casted, and there is no const anymore.
uint32_t *case = (uint32_t *) show;
```
> If you use variable just in file, it has to be static.

> All type convertions has to be explicit.
```c
uint32_t case_32;
uint64_t case_64 = 64UL;

//ok
case_32 = (uint32_t) case_64;

//wrong
case_32 = case_64; // sound nice, expect good, but make it clear with explicit casting.
```

> Cast should be performed on operand rather than arithmetic expression
```c
uint32_t case1 = 10u;
uint32_t case2 = 10u;
uint64_t case3;

//ok
case3 = (uint64_t)case1 + (uint64_t)case2;

//wrong
case3 = (uint64_t)(case1 + case2); // seems nice but but about limits, passing them by sum? So, it is wrong.
```
> A pointer shall not be casted to any other types.
```c
//ok
uint32_t *show_ptr;
uint32_t case = *show_ptr;

//wrong
uint32_t case = (uint32_t) show_ptr; // seems fine, but last part is pointer. Became a number without notice.
```

> Pointer shall not be casted from something else.
```c
uint32_t case = 10UL;
uint32_t *case_ptr = &case;

// wrong
uint32_t *case_ptr = (uint32_t *)case; // seems great. Perfect, no issues. But still wrong. Last part is not a pointer or address to be casted to pointer.
```

> Array indexing shall be applied only for array type
```c
//ok
char case[4] = {'s', 'a', 'n','y'};
char c = case[1];

//wrong 
char *case = "asd ben";
char c = case[1]; // seems nice, but wrong. Still.
```

> Bitfield can be just integer, unsigned integer or bool.
```c
// ok
struct case{
    uint8_t func : 3;
    uint8_t dev : 5;
    uint8_t bus;
};

// wrong, i didnt know. TODO check this information.
struct case{
    int fun : 3;
    int dev : 5;
    int bus;
};
```
> Different object pointers can not be casted to each other.
```c
struct case{
    uint32_t *temp32;
    uint64_t *temp64;
};

uint32_t *case_ptr_32;
struct case *case_ptr_st;
//ok 
case_ptr_32 = case_ptr_st->temp32; // valid

//wrong
case_ptr_32 = (uint32_t *)case_ptr_st;
```

> Assignment of function pointer has to be in same type.
```c
typedef void(*func_ptr_t)(void);

func_ptr_t func_ptr_a;
func_ptr_t func_ptr_b;

// ok
func_ptr_a = func_ptr_b;

typedef uint32_t (*func_ptr_new)(uint32_t param);
func_ptr_c func_ptr_new;
//wrong
func_ptr_a = func_ptr_c; // one is void(void) other is uint32_t(uint32_t). There is no cast
```

> String literals must be const.
```c
//ok
const char *case = "abc case";

//wrong
char *case = "abc case";
```

> In arithmetic operations operands has to be in same type. Cast them.
```c
uint16_t case1 = 16u;
uint32_t case2 = 20U;
uint64_t case3 = 50UL;

//ok
uint32_t test = (uint32_t)case1 + case2 + (uint32_t)case3;

//wrong
uint32_t test = case1 + case2 + case3; // rolls somewhere
```

> Each line shall contain just one operation.
```c
// ok
if(cond){
    do_a();
} else{
    do_b();
}
// wrong
if(cond) { do_a();} else {do_b();}
```

> For non-function keywords and opening brackets put a single space. if, else, for, do. while, switch, return. For functions do not put space.
```c
//ok
uint32_t case;
if (case == 0) {
    case = 33;
}

//ok
size_t size = sizeof(struct case_st);

//wrong
if(case == 0){
    case = 33;
}

//wrong
size_t size = sizeof (struct case_st);
```

> Place * just next to name not type.
```c
//ok
uint32_t *show_ptr;
uint32_t *show_func(void);

//wrong
uint32_t* show_ptr;
uint32_t* show_func(void);
```

> Brackets for if,switch,for,do,while, always shall be on the same line
```c
uint32_t num = 32;
uint32_t den = 0;
uint32_t quot;

//ok
if (den != 0) {
    qot = num / den;
}

//wrong
if (den != 0)
{
    // haha they say this is wrong. I see it is wrong,
    // bur they apply different rule for functions.
}
```
> Functions shall start with a line containing a single oepning brace
```c
//ok
uint32_t show_func(uint32_t param)
{ // not like if, else, for, blabla
    return param;
}

// wrong
uint32_t show_func(uint32_t param){
    return param;
}
```

> For single line comment do not use //. Always use /* */

> Add doxygen for functions
    - /** is start.
    - */ is end
    -  * is space + asterisk for each line between
```c
/**
 * @brief Brief description of the function.
 *
 * Detailed description of the function. Detailed description of the function. Detailed description of the
 * function. Detailed description of the function.
 * Application Constraints: Detailed description of application constraint.
 *
 * @param param_1 Parameter description for param_1.
 * @param param_2 Parameter description for param_2.
 * @param param_3 Parameter description for param_3. Parameter description for param_3. Parameter description
 *                for param_3. Parameter description for param_3. Parameter description for param_3. Parameter
 *                description for param_3.
 *
 * @pre param_1 != NULL
 * @pre param_2 <= 255U
 *
 * @post retval <= 0
 *
 * @return Brief description of the return value.
 *
 * @retval 0 Success to handle specific case.
 * @retval -EINVAL Fail to handle specific case because the argument is invalid.
 * @retval -EBUSY Fail to handle specific case because the target is busy.
 *
 */
int32_t func_showcase(uint32_t *param_1, 
                    uint32_t param_2, 
                    uint32_t param_3);
```

> Data structures used by only module should be named with their name as prefix. Data structures for hw register should get suffix of reg.

> Function pointers shall be named with suffix fn.
```c
//ok
struct firmware_ops{
    void (*init_fn)(void);
    void *(*get_resp_fn)(void);
};

//wrong
struct firmware_ops{
    void (*init)(void);
    void *(*get_resp)(void);
};
```

> Function names shall be clear.
actions:
    - <verb>_<noun>        like init_uart
    - <verb>_<adj>_<noun>   like init_primary_spi
checks:
    - is_<noun>         like is_space
    - is_<noun>_<adj>   like is_spi_ready
convertions:
    - <noun>_to_<noun>  like irq_to_vector
    - <noun>2<noun>     like jpg2gpa
for module specifics
    - <moduleName>_<verb>  like uart_read
asm functions
    - <asm>_<verb>      like asm_halt

```c
uint32_t init_vmcs(uint32_t param);

uint32_t init_primary_pcpu(uint32_t param);

bool is_space(uint32_t param);

bool is_pcpu_active(uint32_t param);

uint32_t vie_read_mmio(uint32_t param);

uint32_t irq_to_vector(uint32_t param);

uint32_t gva2gpa(uint32_t param);

uint32_t asm_pause(uint32_t param);
```
> TODO: practise signed number representation like 2's compelement.

> TODO: Learn gcc atributes like align, packed, unused, section.

>

