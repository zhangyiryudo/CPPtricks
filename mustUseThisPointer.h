//0. Two-Phase Name Lookup.
// When a class template inherits from another class template, the compiler does not automatically look into the "base class" for names.
template <typename T>
class Base {
public:
    void foo() {}
};

template <typename T>
class Derived : public Base<T> {
public:
    void bar() {

        //foo(); // Error: 'foo' is not found because it's in the base class template
        this->foo(); // Correct: using 'this' to access the base class member function
    }
};

// 1. Template Disambiguation with this and template
// In very complex template inheritance, if you are calling a member function template of a base class, you might need both this and the template
template <typename T>
class Processor {
public:
    template <typename U>
    void compute() {std::cout << "Processing " << std::endl;}
};

template <typename T>
class MyScanner : public Processor<T> {
public:
    void run() {
        // Mandatory syntax for member template in dependent base
        this->template compute<int>();
    }
};

// 2. Disambiguating Member Names (Shadowing)
// when a function parameter/local variable has the exact same name as a class member variable

struct Player {
    int health;
    void setHealth(int health) {
        // 'health' refers to the parameter, not the member variable
        // health = health; // This does nothing to the member variable
        this->health = health;
    }
};

// 3. Returning the Current Object for Method Chaining

class Builder {
    std::string name;
public:
    Builder& append(const std::string& s) {
        this->name += s;
        return *this; // Return the current object to allow chaining
    }
};