# Options++

The point of this repository is to contain header files that implement memory safe alternatives
for certain objects (typically nullable) currently standard in C++. Apart from memory safety, these objects aim to provide protection against Segmentation Faults and to provide more accurate exceptions and error message to aid developers.

The current aims of are to implement a syntax to allow None-type objects for any C++ object as well as safe handling of null pointers.

## Options

Inspired by the Option type in Rust, we implement a C++ version. An Option is a template class, that stores objects but also safely allows a None-like behaviour if no object is specified.

In very simple terms, one can think of an Option as a polymorphic enum with template type Type (which it really isn't as such things are not supported in C++) with the following fields:

 * Some : Type Obj,
 * None : NoneType

An option can be checked to be None and if not, its value retrieved. A None type Option can be provided as a default option and safely checked, avoiding the need to pass null pointers as default options.

Options belong to the "Options" namespace and are implemented in Options.h

### Example uses

```cpp
#include <iostream>
#include "option.h"

std::Option<float> divide(float numerator, float denominator) {
  if (denominator == 0.0) {
    return std::None;
  } else {
    std::Option<float> result = numerator / denominator;
    return result;
  }
}

int main() {
  std::Option<float> d = divide(10.0, 2);
  if (d == std::None)
    std::cout << "Cannot divide by 0" << std::endl;
  else
    std::cout << "Result: " << d << std::endl;
}
```

Compile:

```
g++ -o sample sample.cpp -Isrc
```

Output:

```
Result: 5

Declaring and accessing an Option of type int.

```
Options::Option<int> int_option = 3; // A normal integer
Options::Options<int> int_none = Options::None; // A None-type object for ints.

int x = int_option.get(); // x is now equal to 3
int y = int_none.get(); // Raises an exception stating None types have no value

```

In the above example, one should try to avoid accessing the value of an Option unless it is known not to be None. The following example demonstrates this as well as using a None value as a default argument type. It is contrasted with the more traditional approach of null pointers.

```
// Using Options
void print_name(std::string first_name, std::string last_name, Options::Option<std::string> middle_name = Options::None) {
	if (middle_name != Options::None) {
		std::cout << first_name << " " << middle_name << " " << last_name << std::endl;
	} else {
		std::cout << first_name << " " << last_name << std::endl;
	}
}

// Traditional approach
void print_name(std::string first_name, std::string last_name, std::string* middle_name = nullptr) {	
	// Ugly!! Unsafe!!
	if (middle_name != nullptr) {
		std::cout << first_name << " " << *middle_name << " " << last_name << std::endl;
	} else {
		std::cout << first_name << " " << last_name << std::endl;
	}
}
```

Some additional uses of note:

```

Options::Option<MyStruct> very_big_struct1(input_struct); // Normal initialization
Options::Option<MyStruct> very_big_struct2(*input_struct); // Same as line above, isn't that clever?

bool x = very_big_struct1 == very_big_struct2; // x is now true

Options::Options<MyStruct*> very_big_struct(*input_struct); // Not the same, stores pointer to a pointer

x = very_big_struct1 == Options::None; // x is now false
x = very_big_struct1 == Options::Some; // x is now true

Options::Options<MyStruct*> very_big_struct(input_struct); // invalid, gives type error

Options::Options<MyStruct> null_struct1(); // This makes a None-type object
Options::Options<MyStruct> null_struct1(nullptr); // Same as line above
Options::Options<MyStruct> null_struct2(Options::None); // Same as line above

x = null_struc1 == null_struct2 // x is now true
x = null_struct1 == Options::None; // x is now true
x = null_struct1 == Options::Some; // x is now false

Options::Options<MyStruct> null_struct(Options::Some); // can't make a non-None object without a value, raises exception
```
