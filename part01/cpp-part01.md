# __cpp基础__

## __编程语言__

### __过程式(Procedure Oriented Programming)__

<ul>
    <li>c</li>
    <li>Fortan</li>
    <li>c++(function)</li>
    <li>java(function)</li>
</ul>

__主要是面向函数的编程。__

<ul>
    <li>通过对定义函数来对软件系统进行建模描述</li>
    <li>自顶向下</li>
    <li>父问题分解为子问题</li>
</ul>

c语言的系统库的实现。

### __函数式(Functional programming)__

<ul>
  <li>lisp</li>
  <li>ml</li>
  <li>scalar</li>
  <li>c++(lambda+template)</li>
  <li>java(lambda+generics)</li>
</ul>

***functions are first class objects(函数式一等公民)***
***higher order functions(高阶函数)***


$$
\lambda = f(x, y, z,...) \\
\lambda, f, x, y, z, ... \in functions \tag{0.1}
$$


在面向过程的语言(c语言)中，函数必须转换为变量对象(函数指针)才能被作为参数或返回值。

<ul>
  <li>functions are first class objects(函数式一等公民)</li>
  <li>higher order functions(高阶函数)s</li>
  <li>面向接口</li>
  <li>泛型</li>
</ul>

更注重接口的实现的功能而非如何实现接口。
STL库中通过定义iterator的行为，确保不同containner(容器)模块同algorithm(算法)模块的交互。

#### __Example(differential)__

$$
a, b, c, d = f(x, y, z, w) \\
a, b, c, d, x, y, z, w \in scalar \\
f \in function
$$

$$
differential := diff \\
diff \in function \\
J = diff(f, x, y, z, w) \\
J \in matrix(Jacobian)
$$

$$
differential := diff \\
diff \in function \\
J = diff(f) \\
J \in function
$$

$$
partial {-} differential \\
J(x) \\
J(x, y) \\
J(x, y, z)
$$

$$
partial {-} differential \\
J(x, y, z, w)
$$

$$
  differential, integral, grad, div, rot... \\
  Laplace, Fourier...\\
  Cybernetic, Singal...
$$

### __对象式(Object Oriented Programming)__

<ul>
  <li>c++(class)</li>
  <li>java(class)</li>
</ul>

__主要是实现对象__

<ul>
    <li>通过定义对象对系统进行描述</li>
    <li>对象是数据的组织者，是处理数据的动作(函数)的发起者。</li>
    <li>系统的逻辑关系是一张图。</li>
</ul>

STL标准库中的容器的实现。

__每一种思想都有局限，任何大型的软件工程系统都难以用一种模型完全描述，往往都要综合各种思想的优劣具体情况具体分析。__

<ul>
  <li>STL</li>
  <li>LLVM</li>
  <li>Matlab(Simulink)</li>
</ul>

注：graphical programming language(labview, scratch)

## __c++与c__

```c++

// store_tensor.h

#ifndef __MEM_OBJECT_H__
#define __MEM_OBJECT_H__

#include <cstddef>

class MemObject {
public:
    MemObject(size_t size);
    ~MemObject();

    void* GetMemPtr();
    size_t GetMemSize();

    static void Dump(MemObject &mem_object, char[] file_name);

private:

    void* data_ptr_;
    size_t size_;
};

#undef

```

```c

// store_tensor.h

#ifndef __MEM_OBJECT_H__
#define __MEM_OBJECT_H__

#include <stddef.h>

typedef struct {
  void* data_ptr_;
  size_t size_;
} MemObject;

void MemObjectConstructor(MemObject *this, size_t size);
void MemObjectDestructor(MemObject *this);
void* MemObjectGetMemPtr(MemObject *this);
size_t MemObjectGetMemSize(MemObject *this);
void MemObjectDump(MemObject *mem_object, char[] file_name);

#undef
```

```c++

#include "store_tensor.h"

#include <cstdio>

int main() {

  MemObject mem_object(1024);

  printf("addr:%p size:%lu\n", 
         mem_object.GetMemPtr(), 
         mem_object.GetMemSize());

  MemObject::Dump(mem_object, "./mem.txt");

  return 0;
}

```

```c

#include "store_tensor.h"

#include <stdio.h>

int main() {

  MemObject mem_object;
  MemObjectConstructor(&mem_object, 1024);

  printf("addr:%p size:%lu\n",
         MemObjectGetMemPtr(&mem_object),
         MemObjectGetMemSize(&mem_object));

  MemObjectDump(&mem_object, "./mem.txt");

  MemObjectDestructor(&mem_object);
  return 0;
}
```

c++符号修饰([c++ mangling](http://web.mit.edu/tibbetts/Public/inside-c/www/mangling.html#))

## __c++的构造函数__


### __默认构造函数__

	编译器自动生成该构造函数，在某些情况下会被编译器优化掉，不生成机器码。	

### __自定义构造函数__

#### __成员初始化列表(member initializer lists)__

```c++

#include <fstream>

struct Class {
    unsigned char x;
    unsigned char y;
    std::fstream f;
 
    Class(int x) : Base{123}, // initialize base class
        y{0},     // y initialized to 0
        f{"test.cc", std::ios::app}, // this takes place after x and y are initialized
        x(x),     // x (member) is initialized with x (parameter)
    {} 
};

```

<ol>
<li>If the constructor is for the most-derived class, virtual bases are initialized in the order in which they appear in depth-first left-to-right traversal of the base class declarations (left-to-right refers to the appearance in base-specifier lists) </li>
<li>Then, direct bases are initialized in left-to-right order as they appear in this class's base-specifier list </li>
<li>Then, non-static data member are initialized in order of declaration in the class definition.</li>
<li>Finally, the body of the constructor is executed</li>
</ol>

#### __explicit关键字__

防止隐式变换导致的非预想的结果。

### __拷贝构造函数__

A copy constructor of class T is a non-template constructor whose first parameter is T&, const T&, volatile T&, or const volatile T&, and either there are no other parameters, or the rest of the parameters all have default values.

#### __调用规则__

The copy constructor is called whenever an object is initialized (by direct-initialization or copy-initialization) from another object of the same type (unless overload resolution selects a better match or the call is elided), which includes

<ol>
<li>initialization: T a = b; or T a(b);, where b is of type T;</li>
<li>function argument passing: f(a);, where a is of type T and f is void f(T t);</li>
<li>function return: return a; inside a function such as T f(), where a is of type T, which has no move constructor.</li>
</ol>

#### __default关键字__

强制编译器自动生成拷贝构造函数

#### __delete构造函数__


