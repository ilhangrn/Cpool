# The greatest STM32 engineer's coding style
> He is Majerle. If you like you can download clang-format file that he published. You can use it to format your code for this style

> Suggests 4 spaces for tab, 1 space for paranthesis start.
```c
do {} while(condition)
```

> Do not use space after functions
```c
int32_t a = sum(3,4); // ok
int32_t b = sum (3,4); // wrong
```

> Never use __ or _ prefix. This is reserved for C lang.

> Prefer prv_ for module-private(static) functions

> Prefer libname_int_ or libnamei_ prefix for library internal functions.

> Use lower case for variables/functions/types with _

> Openning curly brackets is always at the same line as keyword
```c
size_t i;
for (i = 0; i < 5; ++i) {   // ok

}
for (i = 0; i < 5; ++i){    // wrong

}
for (i = 0; i <5; ++i)
{                           // wrong

}
```
> Use space before-after commo, comp, assignment
```c
a = 3 + 4;  // ok
a = 3+4;    // wrong
func_name(5, 4);    // ok
func_name(4,5);     // wrong
```

> This one is contravertiol. Says that do not initilaze global to default value or NULL
```c
// i don't agree
static int32_t a;       // wrong
static int32_t b = 4;   // wrong
static int32_t a = 0;   // wrong
```

> Says that we need to call function to set them. Because linker may not set them during placing them to .data and .bss sections. Make sense but how?
```c
static int32_t a;       // ok
static int32_t b = 4;   // wrong, depends on linker
void
my_module_init(void){
    a = 0;
    b = 4;
}
```

> Says that we need to declare same variables in same line
```c
void
my_function(void){
    char a;     // ok

    char a,b;   // ok

    char a;
    char b;     // wrong, we already have char, put there.
}
```
> Declare local variables in order
1. Custom structure and enums
2. integer tyes, wider unsigned type first
3. single double floating
```c
int
my_func(void){
    // 1.
    my_struct_t my;
    my_struct_ptr_t *p;

    // 2.
    uin32_t a;
    int32_t b;
    uint16_t c;
    int16_t d;
    char e;

    // 3.
    double h;
    float j;
}
```

> Avoid functio calls in variable declerations
```c
int32_t a = sum(1, 2);  // wrong

int32_t a;
a = sum(1, 2);          // ok

uint8_t a = 3, b = 4;   // he says ok but i dont think
```

> Says do not use stdbool.h. Use 1 and 0 for true false.
```c
// ok
uint8_t status;
status = 0;

// wrong
#include <stdbool.h>
bool status = true;     // why is this wrong?
```

> Says never compare against true
```c
if (check_func() == 1) // wrong, but what is your logic and reason.
if (check_func())   // ok
```

> Always compare pointers against NULL
```c
void *ptr;

// ok
if(ptr == NULL || ptr != NULL){ // stupid example but ok

}

// wrong
if(ptr || !ptr){ // total mistake

}
```
> Always use preincrement ++a and predecriment --a

> Always use size_t for length or size

> Always use const for pointer if a pointer should not modify memory pointed

> Always use const for function parameter or variable if it should not be modified

```c
void
my_func(const coid *d){
    // we can modify d but not its location
}

void
my_func(const void* const d){ 
    // we can not modify d and its location 
}

// advise
void 
my_func(const size_t len){

}

void
my_func(void* const d){
    // we can not modify data but we can change its location
}
```

> Do not use VLA variable length array. Use dynamic memory with malloc and free. 
```c
// wrong
void
my_func(size_t size){
    int32_t arr[size]; // wrong, do not use VLA
}

int32_t *arr;
arr = malloc(sizeof(*arr) * n); // ok
// bla
// bla
free(arr);
```

> Always compare variable against zero
> Never compare boolean-treated variables agains t zero or one. use NOT(!) instead.
```c
size_t len = 5;     // counter
uint8_t is_ok = 0;  // boolean treated var
if (len)            // wrong
if (len > 0)        // ok
if (len == 0)       // ok

if(is_ok)           // ok
if(!is_ok)          // ok
if(is_ok == 1)      // wrrong, never compare against 1
if(is_ok == 0)      // wrong, use ! for negative check
```

> Always use /* ... */ style for comments. Even for single line.
> Always include check for **C++** with **extern** keyword in header file.
> Even if function is static, they must include doxygen comments
> Never cast function returning void *
```c
uint8_t *ptr = (uint8_t *) func_returning_void_ptr(); // wrong
// void * is safely promoted to any type, so use below
uint8_t *ptr = func_returning_void_ptr();
```

> Always put space before asterisk comment in multiline comments.
```c
/*
 * This is multi-line comment
 * which is correct
 */

/*
* Wrong, there is no space before asterisk
*/

/**
 * still wrong, double star is just for doxygen.
 * do not use it for normal comments.
 */

/*
 * single line comments like multi line, wrong.
 */

/* single line, correct one */ 
```

> Here is style i know but not that common
```c
void my_func(void); // correct

void MyFunc(void); // wrong
void myFunc(void); // wrong
```

> Align func names
```c
// ok
void        set(int32_t a);
my_ptr*     get_ptr(void);
my_type     get(void);
```

> He says function name should be on another line
```c
// ok
int32_t
foo(void) {
    return 0;
}

// ok
static const char*
get_string(void) {
    return "hello\n";
}

// wrong
int32_t foo(void) {
    return 0;
}
```

> Make variable names all lowercase with _

> Do not declare variable after first executable statement
```C
void
foo(void) {
    int32_t a;
    a = bar();
    int32_t b; // wrong
}
```

> You may declare new variables in next intent-scope
```C
int32_t a, b;
a = foo();
if(a) { // scope change
    int32_t c,d; // ok
    c = foo();
    int32_t e; // wrong after exec
}
```

> Declare pointer variables with asterisk aligned to type.
> I don't know why!
```C
// ok
char* a;

// wrong
char *a;
char * a; // this completely wrong but other one seems fine
```
> When declaring multiple pointers, you can place asterisks aligned to name
```C
char *p, *n; // you just said no, what changed ?!
```

> All structure members must be lowercase
> All enum members should be uppercase

> If a stuct is not typedef do not use _t
```C
struct st_name{
    char *a; // this is my style. i don't change *
    char b;
};

typedef enum {
    MY_TESTA,
    MY_TESTB,
} my_test_t;
```
> If struct has typedef it has to has _t
```C
typedef struct{
    char *a;
    char b;
} st_name_t;
```
> If struct has name and typedef, it must not contain _t for basic name
if has to contain _t suffic after its name for typedef part.
```C
typedef struct st_name { // no _t
    char *a;
    char b;
    char c;
} st_name_t; // _t here
```

> when initilazing structure on declaration use c99
```C
// ok
a_t a = {
    .a = 5,
    .b = 6,
};

// wrong
a_t a = {1,2}; // seems fine. why wrong?
```

> Every nesting must have curly brackets.
```C
// ok
if(c) {
    do_a();
} else {
    do_b();
}

// wrong
if (c)
    do_a();
else
    do_b();

// correct
if (a) {

} else if (b) {

} else {

}

//wrong
if (a)
{

}
else 
{

}
```

> do and while must be in same line as brackets
```C
// ok
do {
    int32_t a;
    a = do_b();
} while (check());

// wrong
do
{
    // ...
} while (check());
```
> Empty while loops has to have single line brackets
```C
volatile uint32_t* addr = HW_PEPIPH_REG_ADDR;

while (*addr & (1 << 13)) {}    // ok
while (*addr & (1 << 13)) { }   // wrong
while (*addr & (1 << 13)) {

} // wrong
```
> Prefer for loop to do while. While is last choise.
```C
int32_t a = 0;
while (a < 10){
    // .
    // ..
    ++a;
}

// better
for(size_t a = 0; a < 10; ++a){

}
```

> Inline if statement may be used only for assigment or function call ops
```C
// ok
int a = condition ? if_yes : if_no; // assignment
func_call(condition ? if_yes : if_no); // func call
switch (condition ? if_yes : if_no) { ...} // ok
// this one is strange, i didn't see before

// wrong, we cannot maintain
condition ? call_to_func_a() : call_to_func_b();

// rework
if(condition){
    call_to_func_a();
} else {
    call_to_func_b();
}
```

> He says we need to indent cases in switch
```c
// ok
switch (check()) {
    case 0:
        do_a();
        break;
    case 1:
        do_b();
        break;
    default:
        break;
}

// wrong, no indent for cases
switch (check()){
case 0:
    do_a();
    break;
case 1:
    do_b();
    break;
default:
    break;
}

// always include default statement
// ok
switch (var){
    case 0:
        do_job();
        break;
    default:
        break;
}
// wrong, where is default
switch(var) {
    case 0:
        do_job();
        break; 
}
```

> If local variables needed in cases, put curly brackets for them
```C
switch (a) {
    // ok
    case 0: {
        int32_t a, b;
        char c;
        a = 5;
        // blabla
        break;
    }

    // wrong, why is this wrong. You already do this for funcs.
    case 1:
    {
        int32_t a;
        break;
    }

    // wrong, i think so. Break is out. seems weird.
    case 2: {
        int32_t a;
    }
    break;
}

> Macros is always CAPITAL_LETTERS

> Always protect input parameters with parantheses
```c
// ok
#define MIN(a, b)   ((a) < (b) ? (x) : (y))

// wrong
#define MIN(x, y)   x < y ? x:y

int32_t x = 5 * SUM(3, 4); // 35 is expected, but will not

//becomes
int32_t y = 5 * (3) + (4); // which is 19.
```

> If you are going to define function macro use do while.
```C
typedef struct {
    int32_t px, py;
} point_t;
point_t p;

// this is valid but there is better way.
#define SET_POINT(p, x, y) (p)->px = (x); (p)->py = (y) // last line has no ; semicolon

// better way, and sounds very nice
#define SET_POINT(p, x, y) do { \  // this symbol is for 
    (p)-> px = (x);             \
    (p)-> py = (y);             \  // multi line macros
} while(0) // no semicolon after while here

> Avoid #ifdef or #ifndef. Use defined() or !defined() instead
```c
#ifdef XYZ
// do somethin
#endif

// better one is defined() and !defined()
#if defined(XYZ)
// blabla
#else
// blabla
#endif
```
> Do not sub indent #if statements
```C
// ok
#if defined(XYZ)
#if defined(XYZ)
// blabla
#endif
#else
// bla
#endif

// wrong
#if defined(XYZ)
    #if defined(XYZ)
        // bla
    #endif
#else
// blabla
#endif
```

> Use doxygen enabled documentation style for variables, functions,
and structures/enums.

> Always use ** \ ** for doxygen, do **not** use **@**

> Always use 5x4 spaces(5 tabs) offset for comments

```C
/**
 * \brief                   Holds pointer to first entry
 *                          Begins here after 20 spaces.
 */
static type_t *list;
```

> Every struct and enum must have doxygen
```C
/**
 * \brief                   This is point struct
 * \note                    It will calcualte color for
 *                          points
 */
typedef struct {
    int32_t x;              /*!< Point x coordinator */
    int32_t y;              /*!< Point y coordinator */
    int32_t size;           /*!< Point size.*/
} point_t;

/**
 * \brief                   Point color enum
 */
typedef enum {
    COLOR_RED,              /*!< red color */
    COLOR_GREEN,            /*!< green color */
    COLOR_BLUE,             /*!< blue color */
} print_color_t;
```

> Documentation for fucntions MUST be in function implementation: source file
> Function must include \brief and all parameters documentation
> Every parameter must be noted if it is `in` or `out`. 
> Must include `return` but this does not apply for `void` funcs.
```C
/**
 * \brief                   Sum of two number
 * \param[in]               a: first one
 * \param[in]               b: sec one
 * \return                  sum of them
 */
int32_t sum(int32_t a, int32_t b) {
    return a + b;
}

/**
 * \brief                   Sum of two
 * \note                    Will not return, uses pointer
 * \param[in]               a: first
 * \param[in]               b: sec
 * \param[out]              res: x variable to save result
*/
void void_sum(int32_t a, int32_t b, int32_t * res){
    *res = a + b;
}
```

> If function returns enum, use ref for details to specify
```C
/**
 * \brief                   My enum
 */
typedef enum {
    MY_ERR,                 /*!< Error val */
    MY_OK                   /*!< Ok val */
} my_enum_t;

/**
 * \brief                   Check some val
 * \return                  \ref MY_OK is success, \ref member of my_enum_t
 */
my_enum_t check_value(void) {
    return MY_OK;
}
```

> Here is an example header file
```C
#ifndef TEMPLATE_HDR_H
#define TEMPLATE_HDR_H

/* include headers */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* File content here */

/* keep going */


#ifdef __cplusplus
}

#endif /* TEMPLATE_HDR_H */
```

> Use `.clang-format`

> For eclipse based editors:
> Eclipse formatter you can use something like
`eclipse-ext-kr-format.xml` file that can be used with 
eclipse-based toolchains to set formatter options.

It is based on K&R formatter with modifications to respect above rules. 
You can import it within eclipse settings, 
Preferences -> LANGUAGE -> Code Style -> Formatter tab.