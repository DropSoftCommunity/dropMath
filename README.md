<img src="./.res/icon.png" align="right" />

# dropMath

| dropMath is a simple single header math library intended to be used in games. |
|-------------------------------------------------------------------------------|

> :star: We are looking for more developers. Feel free to contribute!

[![CircleCI](https://circleci.com/gh/DropSoftCommunity/dropMath/tree/main.svg?style=svg)](https://circleci.com/gh/DropSoftCommunity/dropMath/tree/main)
![CPP](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

---

### Table of Contents
- [Description](#about)
- [Installation](#installation)
- [Usage Examples](#examples)
- [Documentation](#documentation)
- [Contact](#contact)

---

## About

dropMath is a single header C++ math library with a primary focus on
ease of use.

The main target audience for this library are game developers who want
to have a modern C++ interface for the math library they are using.

## Installation
### Using CPM.cmake

The preferred method of installing this library is through the cpm package manager that you can find here:

> https://github.com/cpm-cmake/CPM.cmake

Once you have CPM "installed" you can use dropMath like so:

```cmake
CPMAddPackage("gh:Erarnitox/dropMath#main")
target_link_libraries(your_executable PRIVATE dropMath::dropMath)
```

### Using CMake FetchContent

You can also install the library using the CMake built in function `FetchContent` directly, without using a package manager like so:

```cmake
include(FetchContent)

FetchContent_Declare(
    dropMath
    GIT_REPOSITORY https://github.com/Erarnitox/dropMath.git 
    GIT_TAG main
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(dropMath)

target_link_libraries(your_executable PRIVATE dropMath::dropMath)
```

### If you are not using CMake

To install and use dropMath, and you are not using CMake, you only need to include the header (header/dropMath) in this repository.

[![Installation](./.res/thumb.png)](https://youtu.be/SEkMLR5pExY)

### Download the header

In your project directory run:
```sh
wget https://raw.githubusercontent.com/DropSoftCommunity/dropMath/main/dropMath.hpp
```
You should now have the header file `dropMath.hpp` in your project directory.

### Using dropMath

You should now be able to include the header from the same directory in your
source files like this:
```C++
#include "dropMath.hpp" //include dropMath

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

![BezierExample](./.res/bezier_example.png)

You can find some example usage of the library in the [examples](./examples/) directory
of this repository.

We do also have a YouTube Playlist with usage examples:
[![ExamplePlaylist](./.res/thumb.png)](https://youtube.com/playlist?list=PLTjUlazALHSAA-VpiKxJCDdx2MRvEnBw1)

### Contact
**Discord:** `@erarnitox`
**X:** `@erarnitox`

