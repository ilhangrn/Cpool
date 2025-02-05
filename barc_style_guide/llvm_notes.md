## Tools like black, darker, clang-formatter

This note is from LLVM guide. I call these guys as them/they.

They use 'black' tool for pyhton code formatter

For python patches they use 'darker' tool

--line-length is normally 80 but they avoid

They use comment on top for file purpose

## Comments
```c
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Instruction class, which is the
/// base class for all of the VM instructions.
///
//===----------------------------------------------------------------------===//
```

there are two type of comments:

```c
/// for doxygen, which used for documents
// for normal comments
```
tag examples:

**\brief** can be used in first line

**\author** ilhan

## Guards

If we have 
```c 
#include "llvm/Analysis/Utils/Local.h"
```

Guard should be
```c
#ifndef LLVM_ANALYSIS_UTILS_LOCAL_H
#define LLVM_ANALYSIS_UTILS_LOCAL_H
```

> Class definitions should have a **doxygen** comment on top

> Methods and global functions also needs to be commented. The reader should understand how to use without reading code. Good things to understand here: Edge cases? Does this method returns **NULL**?

> /* blabla \*/ style is C style. If you work with **c89**, you use this. Or we your work is going to be included by C you use this /* */ style

> It is not suggested commenting out large blocks

> Use **\file** command to rutn the standart file heade rinto a file level comment

> **\brief** is to create abstract for things. Try to keep it as single sentence.

> Inside paragraph, when you refer to parameter use **/p** not **/arg**. We use this **/arg** in method-function comments, it will start a new paragraph for given parameter.

> Wrap non-inline code examples with **\code** ... **\endcode**

> To document functions we use **\param**. If there purpose is in-out, we use **\param [out]** or **\param [in]**.

> To describe return value, we use **\return**

### A great commenting:
```c
// ====== minimal one ======

/// Sets the xyzzy property to \p Baz.
void setXyzzy(bool Baz);

// ====== complete one ======

/// Does foo and bar.
///
/// Does not do foo the usual way if \p Baz is true.
///
/// Typical usage:
/// \code
///   fooBar(false, "quux", Res);
/// \endcode
///
/// \param Quux kind of foo to do.
/// \param [out] Result filled with bar sequence on foo success.
///
/// \returns true on success.
bool fooBar(bool Baz, StringRef Quux, std::vector<int> &Result);
```

> Don't duplicate documentation comments. They should be in header files for public functions. Docs for private functions can go to implementation(source file).

## AVOID THIS
```c
// Example.h:

// example - Does something important.
void example();

// Example.cpp:

// example - Does something important.
void example() { ... }
```

## DO THIS INSTEAD
```c
// Example.h:

/// Does something important
void example();

// Example.c:

/// Builds a B-tree in order to do foo. See paper by...
void example() { ... }
```

### Error messages
> For error messages. Start the first sentence with a lower-case letter and finish the last sentence with a period.

> A good error message:

    error: file.o: section header 3 is corrupt. Size is 10 when it should be 20.

> A bad error message:

    error: file.o: Corrupt section header.

> In llvm there is a header for error formats and colors. You can use **Support/WithColor.h** for right style.

### Include order
> Header file include order:
1. Main module headers
2. Local/private header
3. LLVM project headers(clang, lldb, llvm, etc)
4. System #includes

> For submodule example: LLDB depends on both clang and llvm, and clang depends on llvm. So LLDB source should include lldb first, followed by clang, followed by llvm.

### 80 columns
> Fit to 80 columns. Side to side windows should handle code. And printing will be available with this.

### Golden rule: adapt
> Golden rule: Follow the style of existing code if you are modifying.

### Whitespace
> Do not add trailing whitespace. It causes git appears on git diff and commit.

### Intend
> They say we need to avoid tab, instead we will use 2space intendation.

### Casting
> Use C++- style casting, use static_cast, reinterpret_cast and const_cast.
- When casting to void it can give unused variable warning, use c style casting for this case.
- When casting between integral types(including enums that are not strongly typed) functional style casting are permitted as an alternative to static_cast.

### Do not use static constructor
> It is haeavy. Do not use types has constructor or destructor in global.

### Structs
> In C++ classes has all variables private, structs has public by default. And call for them is same. No need to check type.
```c
// Avoid if `Example` is defined as a struct.
class Example;

// OK.
struct Example;

struct Example { ... };
```

> If there are members need to be private. Use classes.
```c
// Avoid using `struct` here, use `class` instead.
struct Foo {
private:
  int Data;
public:
  Foo() : Data(0) { }
  int getData() const { return Data; }
  void setData(int D) { Data = D; }
};

// OK to use `struct`: all members are public.
struct Bar {
  int Data;
  Bar() : Data(0) { }
};
```

> If you use a braced initializer list when initializing a variable, use an equals before the open curly brace:
```c
int data[] = {0,1,2,3}; // compiler knows size
int data[4] = {1,2,3,4}; // is also fine
```


### auto in C++
> Some says forever auto. It is very convenient but there is a cost. It has copy in it. Use auto & for values and auto * for pointers unless you need to make a copy.
```c
// Typically there is no reason to copy
for(const auto &Val : Container) observe(Val);
for(auto &Val : container) val.change();

// Remove the reference if you really want a new copy
for(auto Val : Container) { Val.change(); saveSomewhere(Val);}

// Copy pointers but make it clear that they are pointers
for(const auto *Ptr : Container) observe(*Ptr);
for(auto *Ptr : Container) Ptr-> change();
```

### Beware of non-determinism due to order of pointers
> Some containers are unordered like maps, sets. Iteration of them over pointer is risky. Use them after sorting or use vectors and its adaptations for them.

> std::sort function may give result without equal(==) oeprator. Beware of changes with sorting. You can use llvm::sort instead.

### #include as little as possible
> They if we are using pointers or reference, we don't need to include header file for type.

### Use early exits and continue
> Here is bad example:
```c
Value *doSomething(Instruction *I) {
  if (!I->isTerminator() &&
      I->hasOneUse() && doOtherThing(I)) {
    ... some long code ....
  }

  return 0;
}
```

> Here is better version:
```c
Value *doSomething(Instruction *I){
    // terminators never need something done to them
    if(I->isTerminator())
        return 0;

    // we conservatively avoid transforming instructions with multile uses because goats like cheese
    if(!I->hasOneUse())
        return 0;
    
    // This is really just here for example
    if(!doOtherThing(I))
        return 0;
    
    ... some long code ...
}
```

> We can fix our for loops in same way. Here is a bad one:
```c
for (Instruction &I : BB) {
  if (auto *BO = dyn_cast<BinaryOperator>(&I)) {
    Value *LHS = BO->getOperand(0);
    Value *RHS = BO->getOperand(1);
    if (LHS != RHS) {
      ...
    }
  }
}
```

> It seems okay to me, but when we have more lines it gets nested so easily and get complex. Lets see a wonderful version of it.
```c
for(Instruction &I : BB){
    auto *BO = dyn_cast<BinaryOperator>(&I);
    if(!BO) continue;

    Value *LHS = BO->getOperand(0);
    Value *RHS = BO->getOperand(1);
    if (LHS == RHS) continue;
}
```

### Do not use else after return
> Do not use else, else if after something that interrupts control flow like return, break, continue, goto, etc. Here is our bad example:
```c
case 'J':{
    if(signed) {
        Type = Context.getsijmp_bufType();
        if(Type.isNull()){
            Error = ASTContect::GE_Missing_sigjmp_buf;
            return QalType();
        } else{
            break; // unnecessary
        }
    } else {
        Type = Context.getsijmp_bufType();
        if(Type.isNull()){
            Error = ASTContect::GE_Missing_sigjmp_buf;
            return QalType();
        } else{
            break; // unnecessary
        }
    }
}
```

> Lets clear this code:
```c
case 'J':
    if(Signed)
        Type = Context.getsigjmp_bufType();
    else:
        Type = Context.getjmp_bufType();
    
    if(Type.isNull()){
        Error = Signed ? ASTContext::GE_Missing_sigjmp_buf:
                            ASTContext::GE_Missing_jmp_buf;
        return QualType();
    }
    break;
```

### Turn predicate loops into Prediate functions
> We all do this mistake. Avoid setting a value by loop operations. Set a function for it. Here is a bad one.

```c
bool FoundFoo = false;
for(unsigned I = 0, E = BarList.size(); I != E; ++I){
    if(BarList[I] -> isFoo()){
        FoundFoo = true;
        break;
    }
}

if(FoundFoo){
    // blablabla
}
```

> But ne need to improve and always.
```c
/// \return true if the specific list has an item that foo
static bool containsFoo(const std::vector<Bar*> &List){
    for(unsigned I= 0, E = List.size(); I!= E; ++I)
        if(List[I]->isFoo())
            return true;
    return false;
}

if(containsFoo(BarList)){
    //blablabla and more bla
}
```

### Naming
> **Type names** (including classes, structs, enums, typedefs, etc) should be nouns and start with an upper-case letter(e.g TextFileReader)

> **Variable names** should be nouns(as they represent state). The name should be camel case and start with an upper case letter ( e.g Leader or Boats). // TODO: I don't think we use camel case in C.

> **Function names** should be verb phrases(as they represent actions) and command like functions should be imperative. The name should be camel case and start with a lower case letter(e.g openFile() or isFoo()).

> **Emum** declarations. They say it needs to contain words imply or indicate subclass(e.g ValueKind). //TODO: in C we always put T or _t on the end.

> **Enumerators** is parts of enums. They say it needs to start with upper case like types. (e.g our ValueKind may have enumerators like VK_Argument, VK_BasicBlock, etc)

> Here is an example:
```c++
class VehicleMaker{
  ...
  Factory<Tire> F;            // Avoid: a non-descriptive.
  Factory<Tire> Factory;      // Better: more descriptive.
  Factory<Tire> TireFactory;  // Even better if there types
};

Vehicle makeVehicle(VehicleType Type) {
  VehicleMaker M;           // Might be OK in small scope
  Tire Tmp1 = M.makeTire(); // Avoid:'Tmp1' no info
  Light Headlight = M.makeLight("head");  // Good one
}
```

### Assert
> It is just one library and helps a lot to detect issues before happening. <cassert>

```c
assert(Ty->isPointerType() && "Cant use non pointer");
assert(Opcode == Sh1 || Opcode == Shr) && "invalid code");
assert(idx < get_num() && "out of range");
assert(v1.getType() == v2.getType && "same type");
```

> In past assert were used to indicate a code should not be reached.
```c
assert(0 && "invalid radix");
```

> In assertion when program hits it it will print and exit the program. when assertions disabled llvm_unreachable becomes a hint to compiler to skip generating code.

> Now we have something better: llvm_unreachable(). We use it to indicate that code has reach a point our code should never be reached.
```c
llvm_unreachable("radix invlaid")
```

> When we use variables for assertions and then disable them. Variables will cause unused warnings. They need to be void to pass this warning. Here is bad one:
```c
unsigned Size = V.size();
assert(Size > 42 && "vector has smaller limit");

bool NewToSet = Myset.insert(Value);
assert(NewToSet && "should not be in list");
```

> To solve compiler warnings:
```c
assert(V.size() > 42 && "vector size is smaller");
bool NewToSet = Myset.insert(Value); (void)NewToSet;
assert(NewToSet && " should not be inlist");
```

> They say do not use these:
- Do not run end() in each call of for loop.
- Do not use using namepsace std, instead mention std:: each time. It causes conflicts otherwise.
- Do not use <iostream>, use raw_ostream
- Avoid std::endl, it has flush call in it. Instead use '\n'.
```c++
std::cout << std::endl; // is equavalent with below
std::cout << '\n' << std::flush;
```

- Do not use inline word in classes, it is always inline. Here is bad one:
```c++
class Foo{
    public:
    inline void bar(){
        // ...
    }
};
```

> Here is good one
```c++
class Foo{
    public:
    void bar(){
        //..
    }
};
```

### Parantheses
> Put a space before them. But not in a function call.
```c
if (x) //...
for (I = 0; I != 100; I++) //...
while (LLVMRocks) //...

someFuncs(42);
assert(2 != 4 && "laws say no");

A = foo(42, 89) + bar(v);
```

### Prefer Preincrement
> preincrement(++X) can be much faster than posincrement (X++). First one just increments the value. Other one(X++) gets a copy of current variable and increses. If it is a complex type, it takes much more time.

### Avoid braces
```c
// Omit the braces since the body is simple and clearly associated with the
// `if`.
if (isa<FunctionDecl>(D))
  handleFunctionDecl(D);
else if (isa<VarDecl>(D))
  handleVarDecl(D);

// Here we document the condition itself and not the body.
if (isa<VarDecl>(D)) {
  // It is necessary that we explain the situation with this surprisingly long
  // comment, so it would be unclear without the braces whether the following
  // statement is in the scope of the `if`.
  // Because the condition is documented, we can't really hoist this
  // comment that applies to the body above the `if`.
  handleOtherDecl(D);
}

// Use braces on the outer `if` to avoid a potential dangling `else`
// situation.
if (isa<VarDecl>(D)) {
  if (shouldProcessAttr(A))
    handleAttr(A);
}

// Use braces for the `if` block to keep it uniform with the `else` block.
if (isa<FunctionDecl>(D)) {
  handleFunctionDecl(D);
} else {
  // In this `else` case, it is necessary that we explain the situation with
  // this surprisingly long comment, so it would be unclear without the braces
  // whether the following statement is in the scope of the `if`.
  handleOtherDecl(D);
}

// Use braces for the `else if` and `else` block to keep it uniform with the
// `if` block.
if (isa<FunctionDecl>(D)) {
  verifyFunctionDecl(D);
  handleFunctionDecl(D);
} else if (isa<GlobalVarDecl>(D)) {
  handleGlobalVarDecl(D);
} else {
  handleOtherDecl(D);
}

// This should also omit braces.  The `for` loop contains only a single
// statement, so it shouldn't have braces.  The `if` also only contains a
// single simple statement (the `for` loop), so it also should omit braces.
if (isa<FunctionDecl>(D))
  for (auto *A : D.attrs())
    handleAttr(A);

// Use braces for a `do-while` loop and its enclosing statement.
if (Tok->is(tok::l_brace)) {
  do {
    Tok = Tok->Next;
  } while (Tok);
}

// Use braces for the outer `if` since the nested `for` is braced.
if (isa<FunctionDecl>(D)) {
  for (auto *A : D.attrs()) {
    // In this `for` loop body, it is necessary that we explain the situation
    // with this surprisingly long comment, forcing braces on the `for` block.
    handleAttr(A);
  }
}

// Use braces on the outer block because there are more than two levels of
// nesting.
if (isa<FunctionDecl>(D)) {
  for (auto *A : D.attrs())
    for (ssize_t i : llvm::seq<ssize_t>(count))
      handleAttrOnDecl(D, A, i);
}

// Use braces on the outer block because of a nested `if`; otherwise the
// compiler would warn: `add explicit braces to avoid dangling else`
if (auto *D = dyn_cast<FunctionDecl>(D)) {
  if (shouldProcess(D))
    handleVarDecl(D);
  else
    markAsIgnored(D);
}
```