# SimCity

Group Memebers: Aseel Shaheen, Kyilee Bell, Ronald Perez, Marcelo Gonzalez

## How to compile/run SimCity
### Method 1: Makefile
**NOTE: If the .o and simulation file is there, please run `rm *.o ./simulation` in Linux and/or CSE Machines to ensure makefile works correctly. If using powershell terminal, use del instead of rm. Additionally, if using Mingw64 and Visual Studio Code, use `mingw32-make` to build, and `mingw32-make run` to run the program.**

1. Type `make` in the terminial to make sure all files are updated.
2. Use `make run` to run the simulation.
3. Once ran, use `make clean` to remove the .o and simulation files for cleanliness.

### Method 2: g++ Command
Alternatively, you can run `g++ *.cpp -o simulation` to run the program, though makefile is suggested. 


Additionally, we implemented the bonus aswell.