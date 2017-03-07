Generator-Utils
===============

Overview
--------
A bunch of functions so you don't have to write them. The main purpose of the repo is to unify the most used tools and make them deterministic to the random seed.

Installation
------------
```sh
git clone https://github.com/establishment/generator-utils
cd generator-utils
make install
```

Design goals
------------
- All functions which take a range as parameter generate values in `[left, right)`. Adding a `x` in front of these functions makes the generated values `[left, right]`. For example, `Range(2)` returns a vector with `[0, 1]` while xRange(2) returns `[0, 1, 2]`.
- Nothing throws exceptions, just `assert(0)` for now

Short documentation overview
============================

Utils
-----
#####`vector<Type>` `Range(left, right, step)` 
* Returns a vector with `[left, left + step, .. right)`
Other versions `Range(left, right)`, `Range(right)` and all of these with `x`

#####`Sort` `RandomShuffle` `Reverse` `Unique`
* Applies basic stl function directly on containers(`vectors`)

Actual signature `Container<Type>& Sort(Container<Type>&)` `Container<Type>&& Sort(Container<Type>&&)` - for function call return values
```
vector<int> x = {1, 3, 2, 2, 3, 1, 1, 5};
Reverse(Unique(x)); // Unique sorts as well, because you want that
// x will be {5, 3, 2, 1}
auto v = Sort(FunctionThatReturnsAVector());
```

Random
------
#####`UniqueNumbers(left, right, num_elements)` 
* Returns a vector of `num_elements` numbers in range `[left, right)`
Other versions `UniqueNumbers(right, num_elements)` - all version work with `x` as well

Honorable mentions `UniqueNumbers(left, right, num_elements, const std::function<bool(Type)>& valid_number)` - returns random numbers, but only numbers for which the function returns true

#####`Partition::Uniform(num_elements, num_buckets, min_val)`
* Returns a vector of `num_buckets` elements. The sum of the elements is `num_elements` and each of them is `>= min_val`. Assuming that `min_val = 0`, the returned partition is a random, each possible valid partition having the same chance to be chosen.

#####`Rand` `RandLog` `RandLogScaled`
* Returns a random number in [left, right). The weight of the number depends on the function
* All `Rand` functions have a x version, for which the retured value will be in [left, right].

`Rand(left, right)`
* Basic rand in interval [left, right)
Other versions `Rand()` `Rand(right)`

`RandLog(left, right)`
* Give a random value in [left, right), value x having the weight equal to 1/x

`RandLogScaled(left, right)` 
* same as `RandLog` but element `i` has weight equal to `1 / (i - left + 1)`
