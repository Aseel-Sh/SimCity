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


<<<<<<< HEAD
Additionally, we implemented the bonus aswell.
=======
so in Cell class you would essentially add under zoneType and public:
int population
int pollution 
and so on

- Ronnie

Note: The changes below are only visible on my branch, not this main branch.

I created an "Output-And-Commercial" branch so I can work on my part without messing up main code.
The output wont work anymore temporarily (in my branch) as the code is now incomplete since we decided to go with the inheritance path. Once the Industrial and Residential Classes are added, and the loadRegion() in the region.cpp file is modified to reflect the added classes then the output should work normally.

Also I changed the 2D vector to be a pointer to the object rather than the object itself. I also added my file placeholders (no code in them yet)
I added comments where I changed or added stuff, and since this is a branch our main wont be affected so we can always revert back to the working version. 

Updated compile line:

If using Mingw64 and VsCode: 
1- To build: mingw32-make 
2- To Run: mingw32-make run

- Aseel

Master branch changes:
- Changed main.cpp to prompt user for config file name, instead of it being hardcoded into the program, tested and evverything.
- Created a makefile for easier compliation, with a make clean and make run commands, which creates object files and the simulation file. 

In order to now run the program, you can simply use make, and make run to compile, and make clean to get rid of all the object files.
-Kyi 

Note:
 if using powershell terminal. to clean using makefile edit the makefile file's clean from "rm" to "del"
>>>>>>> b831a51ceac332ed4dc7b3474ca04685b6394caf
