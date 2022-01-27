<img src="icon.png" align="right" />

# dropMath

| :warning:  This Library is under active development and not ready for production yet!   |
|-----------------------------------------------------------------------------------------|

> :star: We are looking for more developers. Feel free to contribute!


> :star: The simple single header math library

[![CircleCI](https://circleci.com/gh/DropSoftCommunity/dropMath/tree/main.svg?style=svg)](https://circleci.com/gh/DropSoftCommunity/dropMath/tree/main)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![CPP](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

---

### Table of Contents
- [Description](#About)
- [Installation](#Installation)
- [Usage Examples] (#Examples)
- [Documentation] (#Documentation)
- [Contact](#Contact)


---

## About

dropMath is a single header C++ math library with a primary focus on
ease of use.

The main target audience for this library are game developers who want
to have a modern C++ interface for the math library they are using.

## Installation

To install and use dropMath you only need to include the header (header/dropMath)
in this repository.

[![Installation](https://i9.ytimg.com/vi_webp/SEkMLR5pExY/mqdefault.webp)](https://youtu.be/SEkMLR5pExY)

### Download the header

In your project directory run:
```sh
wget https://raw.githubusercontent.com/DropSoftCommunity/dropMath/main/header/dropMath.hpp
```
You should now have the header file `dropMath.hpp` in your project directory.

### Use the dropMath header

You should now be able to include the header from the same directory in your
source files like this:
```C++
#include "dropMath.cpp" //include dropMath

int main(){
	/*Drop Math can now be used.
	  As an example I just created a Vector3 here
	*/
	drop::math::Vector3 vec{ 1.f, 2.f, 3.f };

	//...
	return 0;
}
```

## Examples

## Documentation

### Contact
[![Discord](https://badgen.net/discord/online-members/89K69wtz8F)](https://discord.gg/89K69wtz8F)
