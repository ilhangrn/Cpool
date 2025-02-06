# Here is notes from AT&T C coding style
> The goal of this effort is increase portability, reduce maintainace, and improve clarity.

    - "To be clear is professional; not to be clear is unprofessional." -- Sir Ernest Gowers.

> Files are more than 1000 lines are cumbersome to handle. Keep it small.

    - "Be short, be simple, be human." -- Sir Ernest Gowers.

> File names should be less than 8 characters. I don't think this is possible.

> File extentions:
- c source files:           .c
- assembler source files:   .s
- object files:             .o
- include header files:     .h

> It is Makefile we use, not makefile. It is control file for `make`. `"README"` for summary of contents.

## Suggested order for file
> First file details, like auothor, license, reference, version.

> Then we place `#includes`. In most cases #include `stdio.h` cames first, then user include files.

> Next is typedefs and defines. `Const` macros first, function macros later. Then `typedefs` and enums.

> Next is global externs. In order: externs, non-static globals, static globals. If a define applies to a particular piece of global data declaration, defines comes just after it. Indented to put defines one level deeper than first keyword.

> Functions come last, should be in order. Related things should stay together. If there is a lot consider alphabetical order.

## Header files
> Declaration of different subsystems should be in different files. If a set of declarations is likely to change when we port to another machine, those should be in a separate header file.

> Avoid using names of standart libraries for your libraries.

> Do not use absolute paths for libraries. Use the `<name>` construction for getting them from a standard place.  Or define them `ralative` to current directory. `Include-path` option of the C compiler `I` is the best way to handle extensive private libraries.

> Do not declare anything in header files.

> Header files should not be nested.

## Comments
> `When the code and the comments disagree, both are probably wrong` --Norm Schryer

> If comments are rapidly get out of data, avoid. Short comments should be what comment like "compute mean value" instead of how comments like "sum of values divided by n".

> C is not assambler. Having 3 lines on top for summary is better than putting microcomments for each line.

> Block comments can be in two versions:
```c
/*
 * Here is our block comm.
 * this is form
 */

// second style

/*
** this is other style with two *-> **
** yes it is
*/

// Second one seems much better to me.
```
> Note that grep '^./*' will catch all block comments in file.

> Comments should on top of the thing they describe
```c
if (argc >1) {
    /* get input file rom cmd line */
    if(freopen(argv[1], "r", stding) == NULL){
        perror(argv[1]);
    }
}
```

> Single-short comments can be on same line. If there is more than one they should use same tabbing.
```c
if (a == EXPECTED) {
    b = TRUE;       /* special case */
} else {
    b = isprime(a);     /* works only for odd */    
}
```

## Declerations
> All external data declerations sould be preceded by `extern` keyword. If its array with explicit size, array bounds must be repeated unless size is decoded in array(e.g read only character array that is always null terminated)

> My winner, pointer * qualifier should be with name not type.
```c
char *a, *b, *c;
// instead of 
char* a, t, u;
```

> They say use tabs other than spaces to align structure. And opening brace `({)` should be on the same line as the structure tag. (This is great, someone supports me, thanks AT&T)
```c
struct boat {
    int wlength;    /* water line in meters */
    int type;   /* see below notes */
    long sailarea;  /* sail area in mm */
};
/* define boat type */ // we could use enums, why not?
#define KETCH(1)
#define YWAL(2)
```

> Haha, here is answwer. I was right. They say "enums might be better anyway."
```c
enum bt {KETCH, YWAL};

struct boat {
    int wlength;    /* water line in meters */
    enum bt type;   /* see below notes */
    long sailarea;  /* sail area in mm */
}
```
> Any variable whose initial value important should explicitly initialized. `Never use empty initializer {}`. Long numbers should be initialized explicityly with capital `L`.
```c
int x = 1;
char *c = "message";
struct boat winner [] = {
    {40, YAWL, 600000L},
    {28, MOTOR, 0L},
    {0},
};
```

> In any file which is part of a larger whole the maximum use of `static` keyword to make functions and variables local to single files. Variables should be accessed from another file just for particular special need for it that can not filled with another way. If you need to see static variables which are hided by debugger, declare them as `STATIC` and #define STATIC as needed.

> The most important types should be highlighted typedefing them even if they are integer. Structures may be typedeffed when they are declared. Give the struct and the typedef the same name.
```c
typedef struct splodge_t { // this is the style i was looking. Thanks AT&T. I like your guide.
    int sp_count;
    char *sp_name, *sp_alias;
} splodge_t; // here it is, my style.
```

> Return type of functions should always be declared. If function prototypes available use them. Common mistake is using math functions returning double by omitting declaration. Compiler assumes that it is int. And it becomes garbage by me :) Because:

    - C takes the point of view that the programmer is always right. --Michael Decorte

## Function Declarations
> They should be preceded by a block comment prologue that gives a short desc of what it does. Avoid dublication information clear from the code.

> The function return type should be alone on a line. Why?

> I asked gpt and got reply. It is to make it clear for reader when return type is complex and long.(part of Misra C and Nasa rules)
```c
static
const int *
get_values(void);
```
> We use `i` for iterations in loops, we `s` for string pointers, we use `c` for integer types and characters. Usign them with same purpose in different functions helps reader to follow and understand. Avoid using them with different purposes.

> Align comments by applying tabs for them.

> It is better to use functions with fixed number of argument. Avoid variable number of arguments `varargs`.

> If the function is going to use externs which are not declared in top of file, these functions should have their own declaratiosn in the function body for `extern` keyword.

> Avoid overriding declarations. Do not redeclare in inner scope. It is valid but makes complex. lint will complain when -h given.

## Whitespaces
> There should be at least two blank lines between the end of function and the comments for the next.

> Split long conditional lines onto separate lines.
```c
// indetation seems strange but idea is right.
if (foo->next == NULL 
    && totalcount < needed && needed <= MAX_ALLOT 
    && server_active(current_input))
    {
        // bla
    }
```

> Even for loops should split if they are long
```c
for(curr = *listp, trail = listp;
curr != NULL;
trail = &(curr->next), curr = curr->next)
{
    // blabla
}
```

> If tenary becomes complex split it onto lines
```c
// i don't think this is a good example, but they gave it
    c = (a == b)
    ? d + f(a)
    : f(b) - d;
```
> Macro definitions must not have blank between the name and parantheses, compiler will not recognize the argument list otherwise. For normal functions we place a blank between function name and parantheses.(except `sizeof()`)

> Here an example code:
```c
/*
 * Determine if  the sky blue by checking that it is night.
 * May return True when the answer is Fals. Consider
 * eclipse, clouds etc.
 * NOTE: Uses 'hour' from "hightime.c". Returns int.
 */ 
 int    /* true or false */ 
skyblue()
{ // int type has a space before it, strange ?
    extern int hour;
    return (hour >= MORNING && hour <= EVENING);
}

/*
 * Find the last element in the list
 * pointed by nodep
 * Return NULL if there is no last element
 */
 note_t * 
tail(nodep)
node_t *nodep;      /* pointer to head of list */
{ // what kind of order is this, 
// which one is func, 
// which input, 
// which output ???????????????????????
    register node_t *np;
    register node_t *lp;
    if(nodep == NULL)
        return (NULL)
    for (np = lp = nodep; 
    np != NULL;
    lp = np, np = np->next)
    ;   /* void */
    return(lp);
}
```

> In example above we have a NULL body. In the case we NULL body like this we will do it `; /* VOID */` in an separate line.

> They refer to same strcmp() again. Having a wrapper for it would be nice to handle errors better. 

> It is common to use typedef for booleans
```c
typedef int bool;
#define FALSE   0
#define TRUE    1

// or
typedef enum { NO = 0; YES} bool;
```

> With these declarations do not check a boolean for equality with 1(TRUE, YES, etc); instead test for inequality with 0(FALSE, NO, etc). Most functions guaranteed to return 0 if false, but non-zero if true.
```c
// wrong
if (func() == TRUE){
    // bla
}

// correct way
if (func() != FALSE){
    // blabla
}
// it is even better rename this call something like isvalid() and check it instead of call conparison with true or false !
```

> In embedded systems sometimes there is no clear way!
```c
while((c = getchar()) != EOF){
    // process the char
}
```

> Don't use goto if it is not must. If you need goto it means organization has mass. Fix your design first.

> K&R Style is default for most people:
```c
if (x == y) { // same in for and while
    foo();
    bar();
} // else here
```

> For most other styles(Like Allman style) parantheses is in next line.
```c
if (x == y) // same in for and while
{
    foo();
    bar();
}
// else here
```

> For switch cases default should be the last one. And if there is fallthtough we need to comment it.
```c
switch (c) {
    case 1:
    case 2:
        // Do some of the work ...
        /* FALLTHROUGH */
    case 17:
        // Do something ...
        break;
    case 5:
    case 43:
        // Do something else ...
        break; // this last one in not needed but it saves for fallthrough when we add one more case.
    default:
        // do something
        // no need for break, we always put it to last.
}
```

> Whenever if else has multi statements they have to be fully bracketed, both enclosed in braces.
```c
if (expr) {
    statement;
} else {
    statement;
    statement;
}
```

> When there is no second else, fully bracketed is must.
```c
if (ex1) {
    if (ex2) {
        funca();
    }
} else {
    funcb();
}
```

> Avoid using binary comma operator. (exp1, exp2) first done, then run second one and return its result. So weird. Never used, will never use.

> Avoid using multiple tenary ? operators together.

> Avoid using different types for tenary return. They has to be in same type.

## Naming
> #define is all CAPS
> enum is all CAPS
> func, typedef, var_name etc lowercase

> User macros all CAPS, some are not like `getchar` and `putchar`. They work exactly as function. So they are like function, lowercase.

> Avoid using names differ only in case like sum() - Sum(), or funca() - funcA() or getval() - get_val().

> Avoid using similar names for variables. Do not use l,1,I for them. They all look like each other.

> For global variables group them in a structure. And use prefix g_ for them.

> For typedefs use suffix _t

## Note for evolution
> We have something wrong with this evoltion story. We are not the best one. I don't know what has been tried before but it could be different absolutely different if evolution didn't destroy the people with 4 fingers. I don't know that even they tried this version or not. But if we were poeple fith four fingers today it would be great. Our number systems would based on 8. Which matches with 8bit and hex calcualtions. Which is the most effective way of operating with numbers. Multiply is just one shift and quite fast in hex. Even division is so fast. Just one shift. But we evolved with 10 fingers, we don't know how to do quick operations with this precision. An we put huge affort to handle this hex systems. We are idiots of life. As i read it is not clear that why most animals have five fingers. But there were some dynosors with four fingers. They could survive and develop numbers systems. But unfortunately meteors hit. We the animals with five fingers are here with stupid brain and logics.

## Constants
> Use #define and constants for numerical values. It helps to handle project and increase the readability for poeple. Enumeration is a better way of constants since there is type check for it.
```c
// this is valid
for(int i = 0; i < ARYBOUND; i++){
 // bla
}

// this is not good
doot_t *front_door = open(door[i], 7); // no magical numbers
// Do not compare pointers with 0. compare with NULL
if(fornt_door == 0) // wrong
    error("cant open door %s ", door[i]);
```
> NULL is part of stdio.h or stdlib.h depending on your version.

> Even 0 and 1 should be replaced with defines like TRUE and FALSE.

> If you have to use non-text characters they should be written with 3 digit octal rather than one.(e.g '\007'). It is machine dependent and should be treated as such.

## Macros
> Use parantheses for them.

> Some functions are macros in background. (like `getc` and `fgetc`). Care is needed when interchanging macros and fucntions since functions parameters are passed by value while macros parameters are passed by name substitution.

> Avoid usign globals in macros. You see macros working variables below but it is not suggested.

```c
#define OFF_A() (a_global + OFFSET)
#define BORK() (zork())
#define SP3() if(b) {int x; av = f (&x); bv += x;}
```

> When macro gets long, change it to functions. No benefit from long macros.

> Make sure for termination with semicolon when call macros.
```c
if (x==3)
    SP3();
else
    BORK();
```
> For safety for this cases use do-while to make sure it is compact and has semicolons properly.
```c
#define SP3() \\
do { if(b) { int x; av = f(&x); bv += x;}} while(0)
```
> Some compilers will complain for using 0 constant in while. To make it passing we us a macro like below:
```c
#ifdef lint
static int ZERO;
#else
#define ZERO 0
#endif

#define STMT(stuff) do{some_stuff} while(ZERO)

#define SP3() \\
STMT(if(b) {int x; av = f(&x); bv += x;})
// you see how we shape macro against compiler and easy mistakes. Nice touch with static STMT do while.
```

## Conditional compilation
> When you combine several of them it may easily combine in unforeseen ways. If you use machine dependencies make use there is #error for undefined machine dependency.

> If you use #ifdef for optimization, result should be unoptimized code if there is no parameter set instead of uncompilable program.

> Put #ifdefs in header files instead of source files. For example a header file for chekcing memory allocation might look like this:
```c
#ifdef DEBUG
extern void *mm_malloc();
#define MALLOC(size) (mm_malloc(size))
#else
extern void *malloc();
#define MALLOC(size) (malloc(size))
#endif
```

> Conditional compilations should be on feature basis not machine or system dependecies.
```c
#ifdef BSD4
long t = time((long *) NULL);
#endif
// this is poor, there may be 4BSD systems or non BSD systems.Instead use #define symbols such as TIME_LONG and TIME_STRUCT and define the appropriate one in a config file such as config.h
```

## Debugging
> Here is pain.

    - C Code. C code run. Run, code, run... PLEASE! --Barbara Tongue

> For enums first value should be a non-zero or error. But why?
```c
// i have a problem here, in c return 0 is success, not ERR
enum {STATE_ERR, STATE_START, STATE_NORMAL, STATE_END} state_t;
enum {VAL_NEW =1, VLA_NORMAL, VAL_DYING, VAL_DEAD} value_t;
```

> Check for all return error values, even it seems like can't fail. Write functions to test for errors and abort in a well-defined way.

> Include a lot of debugging and checking code and leave most of it in the finished product. Check even for impossible errors.

> Use `assert` facility to insist that each function is being passed well-defined values.

> Do not fill everywhere with ifdefs. Instead create a macro on top of project to call in DEBUG. Like a macro for malloc, for for printf.
```c
#ifdef DEBUG
#define MALLOC(size) (mm_malloc(size))
#else
#define MALLOC(size) (malloc(size))
#endif
```
> Always check boundaries. If there is no boundary it is problem. Set some. An return error for them.
```c
/*
 * INPUT: A null-terminated string source string 'src' to
 * copy from and 'dest' string to copy to. 'maxsize' is
 * limit or UINT_MAX if the size not known.
 * OUTPUT: The adr of dest or NULL if fails.
 */
 char *
copy(dest, maxsize, src)
 char *dest, *src; // this is 89 style, uff, older than me
 unsigned maxsize; // same old things happening, history.
{
    car *dp = dest;
    while (maxsize-- > 0)
        if ((*dp++ = *src++) == '\\0')
            return (dest);
    return (NULL);
}
```

## Portability
    - C combines the power of assembler with the portability of assembler. --Bill Thacker

> Generally new machine is different hardware, different OS, different compiler, and any combination of them.

> First things first, portability. Then you consider optimization if it is must. It can produce code in another machine. If you do, documentation is must for risks and why its needed.(e.g loop executes 6 zillion times)

> Some things are not portable. For example hardware registers. Impossible to port. But you can still port data structures, logics, routines and a lot more.

> Organize source code in sections like machine dependent and independent. That helps in porting.

> They say `void*` type is guaranteeed to have enough bit sof precision to hold a pointer to any data object.

> An they say `void(*)()` type is able to hold a pointer to any function.

> But be sure that you cast them back to the correct type before using them.

> Even `int*` and `char*` are the same size, they may have different formats.

> This fails:
```c
int *p = (int *) malloc ( sizeof(int));

// They say free expects char* and will fail with int*
// this information seems wrong, i think it is just old :)
free(p);
```

> If you don't know your biggest enemy you don't know who you are and you don't know why you fail. Learn malloc() and its mate free(). `TODO`

> Lets says you allocated memory for some integers, malloc gave you pointer for 32bit integers. Then you casted to chars in your functions. Then long. Blabla. Then in your loop you applied pointer arithmetic like p++ :) Welcome to hell, is it your first time here ?:)

> The integer constant zero may be cast to any pointer type. The resulting pointer is `null pointer`. Null pointer is different, always compares equal to the constant zero. A null pointer might not compare with a variable has the zero value.
--------------------
-> NO NO NO! Here is the sentence:
-------------------------------------------------------
Null pointers are not always stored with all bits zero `!!! WTF !!!`
> They say null pointers for two different types are sometimes different.
> I check it is old information. Modern systems and compilers use all-bits-zero null pointers. For very of systems and architectures we can see this problem. Be aware.

> Now imagine you are me. And you are able to walk inside memory. You are going to place some data to there. Getting closer to page's end, usually 4KB. You are very close and you have just a place for 2 bytes in your page. But they ask for uin32_t to be placed there. What do you do? 

    Answer: You can not please everybody. Chop it! or throw it! or ignore it! or tell them you are busy!

> Float numbers can have different results in different systems. Rounding and other logics may be different and give different results.

> Remember that characters can hold much more than 8 bits. Do not assume they are ASCII. And don't use signed if it is not must. `Go with unsigned` for all.

> Alignments can cause address change in different machines. Some use 4 byte integer some use 2 byte integer. They may start with multiple of four address while you are looking for multiple of two. And grouping a 32bit pointer and 8bit char in same structure will give different memory allocations in different machines.

> Endians may be problem. For larger objects and variables byte order will be different with Big endian and Little endian. Do not do concatenate any two variables. It is not portable. Bit fields in structure members will only be portable if two fields are never concatenated.

> Structures may have some holes in it. Do not retrive a type as another in struct and enums.

> Returning structure is just mass, each compiler may do it differently. Use reference or pointer.

```c
// lets see some problems
c = foo (getchar(), getchar());
char
foo(c1, c2, c3){
    char bar = *(&c1 + 1);
    return(bar); // what do you expect ? Really ?
    // this should be a joke, i don't use energy for it
    // do you that is stack growing up or down!
}
```

> Question of day:

    Do you know is stack growing up or down!!! Have fun!

    Okay, but do you know is your address for stack or heap. Still don't have fun?

    Hmm, Flash memory. Endians. Which one?

    No, no. Still in registers. Forget the fun!

> Null pointer of `((char *)0)` is not same as null string. Welcome frontend developer. It is late. Nobody can imagine learning these things. Yes i read books. Old books!

> As always notorious bad things are happening with chars, string.
```c
s = "/dev/tty??";
strcpy(&s[8], ttychars);

// lets add bonus
a[i] = b[i++]; // who knows?

// do we assing things rigt to left?
struct bar_t {struct bar_t *next;} bar;
bar->next = bar = tmp; // did you said right to where?
```

> A basic one, do not use variable names in macro strings.
```c
#define FOO(string) (printf("string = %s", (string)))
// bla
FOO(filename);
```

> Libraries can change, be aware which one you are using. And how it works. Some lib in ANSI and POSIX can be different.

> Use lints.

> C does promotions for pointers and castings. Always cast NULL when it appears in non-prototyped function calls. // What is non-prototyped one?

> Use explicit casting.

> A program can not execute code in the data segment. Even if it possible don't do that.

> Learn more about forward declarations. It is a need for embedded? `TODO`

> Which compilers are ANSI and which are not? `TODO`

> Automatic type promotion is called as `widening`. Learn it. It seems fun :) `TODO`

> Same pragma might mean different in different compilers. They should always be secured with #ifdefs

> Lint is a checker helps us to see incompatibilities, inconsistencies between fucntions and calls, potential bugs, etc.

> `strcpy` is deprecated, so use `strncpy`. The first one needs '\0' to stop, stupid, stop using it. `I pick memcpy` and go with that for all, for ever.

```c
int main(){
    char s[5] = {'s', 'a', '\0', 'c', 'h'};
    char strbuff[5];
    char membuff[5];
    strcpy(strbuff, s);
    memcpy(membuff, s, 5);
    printf("sacin p is [%s], t is [%s]", strbuff,membuff);

    dump5(membuff); // show what happened
    dump5(strbuff); // below you see, strcpy stops in \0
    return 0;
}
// it is going to print
// sachin p is [sa], t is [sa]

// but when we dump5
void dump5(char *str)
{
    char *p = str;
    for (int n = 0; n < 5; ++n)
    {
        printf("%2.2x ", *p);
        ++p;
    }

    printf("\t");

    p = str;
    for (int n = 0; n < 5; ++n)
    {
        printf("%c", *p ? *p : ' ');
        ++p;
    }

    printf("\n", str);
}
// output is 
// 73 61 00 63 68  sa ch
// 73 61 00 00 00  sa
'''