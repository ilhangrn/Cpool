## Here are notes we collected from another source: cmu.edu
> Use proper naming like check_for_error() instead of check_error(), dump_to_file instead of data_file().

> Common words we use
- max for maximum value
- cnt for current count of running count variable
- key for key value
- is, to ask something
- get, to get a value
- set, set a value

> If there is unit name it
```c
uint32_t timeout_msecs;
uint32_t my_weight_lbs;
```

> Major structures should be declared at the top of the file in which they are used, or in seperate header files if they are used in multiple source files.

> Now we have different approach, says put *close to name not type. I aggree.
```c
char *name = NULL;
char *street, city;
```

> Global variables should be provided with **g_**.
> Avoid global variables whenever its possible.
> Global constants should be CAPITAL with _
> Enums has same style
```c
Logger g_log;
Logger *g_plog;
const int A_GLOBAL_CONST = 5;

enum PinState{
    PIN_OFF,
    PIN_ON
};

// die mo..f.. die
enum {STATE_ERR, STATE_OPEN, STATE_RUNNIG, STATE_DYING};
```

> If there is a multiline macro use do {} while(0)

> Always use braces for if, for, while. Even if it is single line.
```c
 if (1 == some_val) {
    some_val = 2;
}
```

> Add comments to closing braces. This seems wrong. We usually place in beginning.
```c
while(1){
    if (valid) {
        // bla
    } // if valid
    else {
        // blabla
    } // not valid
} // end forever
```
> Be aware `enums` are not of a guaranteed size. So if you have a type that can take a known range of values and it is transported in a message you cant use an enum as the type. Use the correct integer size and use constants or `#define`. Casting between integers and enums is very error prone as you could cast a value not in the enum. 

> Do not use function returns in if statements. Fail return can be -1 can ve NULL, return can change and if can have problems. Always compare. Use != or ==.
```c
if(FAIL != f())
// is better than
if(f()) // this is non zero check, someone can change return value to -1

// another one
if(!(bufsize % sizeof(int)))

// should be like this:
if((bufsize % sizeof(int)) == 0) // we make it clear it is numeric, not boolean.
```

> A common problem with this comparisons is while using strcmp(). The nice way is making a macro for result check
```c
// this one is nice to be safe with strcmp return
#define STREQ(a, b) (strcmp((a), (b)) == 0)

// a better one
inline bool string_equal(char* a, char* b){
    (strcmp(a,b) == 0) ? return true : return false;
    // or more compactly
    return (strcmp(a,b) == 0);
}
```

> In somewher they said don't use embedded style ++ and -- things to handle things. Call library fucntions. Making it faster and more efficient is not needed. I left the document there.

> But they mentioned a good point which i need to place.
> Use #if macro not #ifdef macro. Let see why
```c
#ifdef DEBUG
    temp_debugger_break();
#endif
// For this code someone might compile it like
cc -c lurker.cc -DDEBUG=0

// I think it is problem. TODO: Check diff #ifdef and #if
// using #if will work even if DEBUG flag not defined.
```
> If you need to really check a symbol defined or not use `defined()`
```c
#if !defined(USER_NAME)
    #define USER_NAME "john"
#endif
```

> For large blocks of comments use #if(0) ... #endif. We can use /* .. */ it is fine but comments can not contain comments and large block of comment may have comments there. If we are going to comment a code block, #if(0) is the best way. Other people can not implement by #ifdef debug flags and cause problems. It is safe. And it tells people reading it there was code, dropped for bug or something else as lesson.

> Calling c function from c++
```c
extern "C" int strncpy(...);
extern "C" int my_great_func();
// this is other way i think, just together
extern "C"
{
    int strncpy(...);
    int my_great_func();
};
```

> Creating a C function in C++
```c
extern "C" void 
a_c_function_in_cpp(int a){
    //blabla
}
```

> If our code must compile with C and C++
```c
#ifdef __cplusplus
extern "C" some_func();
#else
extern some_func();
#endif
```

> `#define` don't get memory, it is replacement. But it doesn't help in debug. In debug we just see number, no label. Using `const` is better for our debug purpose, but it takes memory as normal variables takes. This is our tradeoff.

> For malloc and calloc, developers can make mistakes so easily. Create wrapper for them for people want to call them safely and with error check.