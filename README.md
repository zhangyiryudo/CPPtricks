# CPPtricks

## std::function  VS  lambda
### lambda fast:(lambda, the compiler It is writing a unique, unnamed class (a functor))

- Unique Type: Because every lambda has a unique type, the compiler knows exactly which code to execute at compile-time.
- Inlining: Since the compiler sees the definition

### std::function: The Type-Erasure Wrapper
It can store, copy, and invoke any "Callable" (lambdas, function pointers, or member functions) that matches its signature.

### How it works (Type Erasure):
It hides the specific type of the callable behind interface:
- A pointer to the callable object.
- Virtual function calls (or function pointers) to trigger the operator(), copy, and destroy logic.

### The Cost of Flexibility:
+ Indirection: jumping through a pointer. This  prevents the compiler from inlining.
- Memory Allocation: std::function will likely allocate memory on the heap to store data.

----
![alt text](image.png)

### Small Object Optimization (SOO)
If your lambda is small , it will store the lambda inside its own internal buffer rather than hitting the heap.

### When to Use Which?
#### Use Lambdas when:
+ pass logics to STL algorithm (e.g., std::sort, std::find_if).
+ Performance is critical (inner loops).
#### Use std::function when:
+ You need to store a callable in a class member or a container (e.g., a std::vector<std::function<void()>> ).
+ The type needs to be explicitly named (e.g., "This function returns a function of type X").


## string_view
### 核心优势：为什么用它？
1. 零拷贝开销
无论字符串有多大，传递 string_view 的开销仅仅是传递两个字（指针 + 长度）。这在处理大型文档解析或高频函数调用时表现极佳。

2. 极其高效的子串操作
调用 sv.substr() 不会拷贝内存，它只是返回一个新的 string_view，调整了指针位置和长度。

### 生命周期管理（最致命的坑）
string_view 不负责管理内存。如果它指向的原始字符串被销毁了，string_view 就会变成悬空引用（Dangling Reference）。

```cpp
std::string_view get_view() {
    std::string s = "Hello World";
    return std::string_view(s); // 危险！s 在函数结束时析构，返回的 view 指向非法内存
}
```

### 最佳实践建议
- 作为函数参数：这是它的主战场。代替 const std::string& 可以让你的 API 更加通用且高效。
- 避免作为返回值：除非返回值指向的是全局常量（





## three  scenarios where must use 'this'
