# ES1D

[![Build status](https://ci.appveyor.com/api/projects/status/hu6jpwhl9m6q8dc8?svg=true)](https://ci.appveyor.com/project/RKalampattel/es1d)

An electrostatic 1D particle-in-cell (PIC) code to solve the two-stream instability problem. The code is based on [work done by Lubos Brieda](https://www.particleincell.com/2015/two-stream-instability/) in Javascript, however it has been converted to both Matlab and C++. 

The Matlab script, tested in MATLAB R2016a, produces graphical output which is can be saved as a GIF file. The C++ program, developed in Visual Studio 2015, produces no graphical output, and represents a first attempt at creating an "object-oriented" style C++ program (i.e. it is a lot more complicated than it needs to be!). 

![](https://github.com/RKalampattel/ES1D/blob/master/ES1D.png)
