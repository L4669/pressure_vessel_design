# pressure_vessel_design
A console based tool for preliminary assessment on pressure vessels using analytical methods
## Code Structure
1. pvd.c - main program to interact with user
2. aux.c - all auxiliary functions needed are defined here
3. spherical.c - inputs, calculations specific to spherical vessels
## Compilation
1. Using makefile from terminal
`$ make`
2. Using gcc directly
`$ gcc -o pvd pvd.c aux.c spherical.c -I ./ -lm`
## Run
`$./pvd`
## ToDo
- [ ] Add support for different solution methods for spherical vessel
- [ ] Add verification module for spherical vessel
- [ ] Add design and verification modules for other shapes
- [ ] Update Readme file
- [ ] Clean the code of unnecssary printf
- [ ] Add better output features
- [ ] Robust freeing method for memory allocated in program
- [ ] Support for Unit conversion

