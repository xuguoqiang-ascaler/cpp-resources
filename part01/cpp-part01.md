# cpp基础

## 编程语言

### 过程式(Procedure Oriented Programming)

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

### 函数式(Functional programming)

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
\lambda, f, x, y, z, ... \in functions\tag{0.1}
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

### 对象式(Object Oriented Programming)

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

## c++与c

```c++

// StoreTensor.h

#ifndef __STORE_TENSOR_UTILS_H__
#define __STORE_TENSOR_UTILS_H__

#include <vector>
#include <string>
#include <cstddef>

class StoreTensor {
public:
    StoreTensor(std::vector<int> dims, int ele_size);
    ~StoreTensor();
    size_t Size() { return size_; };
    size_t MemSize() { return mem_size_; };
    int DataType() { return data_type_; }

    static Dump(StoreTensor &store_tensor, std::string file_name);

private:
    std::vector<char> mem_;
    std::vector<int> dims_;
    size_t size_;
    size_t mem_size_;
    int ele_size_;
};

#undef

```







