# SimCity

in order to compile with no errors you need to use this line

g++ -std=c++11 main.cpp Config.cpp Region.cpp -o simulation

./simulation


Okay i Basically set up the whole program bases, all you need to do now is add the new zones to the Cell Class and then have
them update automatically based of the timeLimit and refresh rate thats given. 

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

If using Mingw64 and VsCode: mingw32-make run
If using anything else: make run

- Aseel

Master branch changes:
- Changed main.cpp to prompt user for config file name, instead of it being hardcoded into the program, tested and evverything.
- Created a makefile for easier compliation, with a make clean and make run commands, which creates object files and the simulation file. 

In order to now run the program, you can simply use make, and make run to compile, and make clean to get rid of all the object files.
-Kyi 
