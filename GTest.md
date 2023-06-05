To use GoogleTest library first we have to construct it.

From the repository https://github.com/google/googletest/tree/main we have to download it in the version we want or the last code.

Once we have it, we go to googletest folder and read README.md which has instructions to build it.

In this case, I am using "Standalone CMake Project" section, which uses cmake.

We also have to look at the section "##### Visual Studio Dynamic vs Static Runtimes" since we are using Visual Studio.

So, as a summary, this are the steps:

1. Downloaded the repository
2. Modify googletest\CMakeLists.txt setting variable gtest_force_shared_crt to ON
3. Create a build directory at root, inside we open a cmd
4. Execute the command: run cmake .. -DBUILD_GMOCK=OFF (since we don't want GoogleMock)
5. Once it is compiled, in the build directory, there's a solution called "googletest-distribution.sln".
   We have to open it, and in the solution right clic -> build solution.
   With this the project will compile and generate a folder called lib. Inside we have a Debug folder and inside, the .lib generated (or .dll if we choose that option).
6. In the 3rdParty directory, we have to create a folder called google_test (or any name) with 2 folders inside (include and lib)
7. Copy the following contents:
   7.1. (googletest project folder)\googletest\include -> we copy gtest folder fully into the include folder
   7.2. (googletest project folder)\build\lib\Debug -> we copy the gtest.lib and gtest_main.lib files into the lib folder
8. Add the library to the visual studio project we want.
   8.1. Project options -> C/C++ -> General -> Additional include directories -> We add  $(SolutionDir)..\..\3rdParty\google_test\include
   8.2. Project options -> Linker -> General -> Additional library directories -> We add  $(SolutionDir)..\..\3rdParty\google_test\lib
   8.3. Project options -> Linker -> Input -> Additional dependencies -> We add  gtest.lib and gtes_main.lib

By defautl, Visual Studio includes googletest and we can create a project of this type to use it (https://learn.microsoft.com/en-us/visualstudio/test/how-to-use-google-test-for-cpp?view=vs-2022),
but in this case, since the path to the project is too long, we can't use this, so we use the library
externally.



