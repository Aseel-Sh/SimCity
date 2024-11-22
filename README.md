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

---

**SimCity** is a city simulation project that models the behavior and interactions of various urban zones—Residential, Commercial, and Industrial—within an evolving city environment.

---

## Features and Functionalities

### Core Functionalities

#### **Dynamic Growth Simulation**
- **Residential Zones**: Simulate population growth and contribute workers to other zones.
- **Commercial Zones**: Simulate economic activity, requiring workers and goods to grow.
- **Industrial Zones**: Simulate production by creating goods and spreading pollution while consuming workers.

#### **Resource Management**
- Tracks available workers and goods, updating based on zone growth.
- Zones can grow only when sufficient resources are available.

#### **Zone Interactions**
- Zones influence one another based on adjacency (e.g., powerlines enable growth, populated cells contribute to growth conditions).
- Industrial zones spread pollution that impacts nearby zones.

#### **Configurable Simulation**
- Simulation parameters (region layout, time limit, and refresh rate) are defined in configuration files.

#### **Sub-region Simulation**
- Allows for simulating specific areas independently.

---

## Project Structure

### Files Overview
- **`main.cpp`**: Initializes the simulation, parses configurations, and runs the simulation loop.
- **`Config.cpp` and `Config.h`**: Handles parsing configuration files for region layout, time limits, and refresh rates.
- **`Region.cpp` and `Region.h`**: Manages the city grid, zone interactions, and simulation logic.
- **`Residential.cpp` and `Residential.h`**: Models Residential zone behavior and growth rules.
- **`Commercial.cpp` and `Commercial.h`**: Models Commercial zone behavior and growth rules.
- **`Industrial.cpp` and `Industrial.h`**: Models Industrial zone behavior, growth rules, and pollution management.
- **`OtherRegion.h`**: Class to handle other regions.

### Configuration Files
1. **`config1.txt`**
   - Defines the simulation settings:
     - **Region Layout**: Path to the CSV file defining the initial city grid.
     - **Time Limit**: Maximum time steps for the simulation.
     - **Refresh Rate**: Interval for printing the simulation state.

2. **`region1.csv`**
   - Contains the initial grid layout, specifying zone types and placements.
        - `R` = Residential zone.
        - `C` = Commercial zone.
        - `I` = Industrial zone.
        - `T` = Powerline.
        - `#` = Powerline over road.
        - `P` = Power plant.
        - `-` = Road.

---

## How It Works

### Initialization
1. Reads configuration from `config1.txt` to set up the simulation.
2. Loads the city layout from `region1.csv`.

### Simulation Loop
- Zones attempt to grow based on:
  - Available resources.
  - Adjacency conditions.
  - Growth rules.
- Pollution spreads from Industrial zones, influencing adjacent cells.
- At specified refresh intervals, the current city state is printed.

### Resource and Growth Conditions
- Growth is contingent on resources like workers and goods.
  - Residential zones produce workers, which Commercial and Industrial zones consume.
- Adjacent populated cells and proximity to powerlines influence growth rates.

### Output
- Displays city population statistics, pollution levels, and the overall layout at various time steps.

### Sub-region Simulation
- Users can select a sub-region to simulate independently, allowing for targeted analysis.
