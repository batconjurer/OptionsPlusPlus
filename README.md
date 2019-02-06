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

Options belong to the ``Options'' namespace and are implemented in Options.h

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
    std::cout << "Return None!" << std::endl;
  else
    std::cout << "Return:" << d << std::endl;
}
```

Compile:

```
g++ -o sample sample.cpp -Isrc
```

Result:

```
Return:5
```
