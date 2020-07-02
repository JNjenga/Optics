# Vision



#### Introduction

This is a project to visualize things.

**Still very early in development .**

![grid screenshot](https://github.com/JNjenga/Vision/blob/master/screenshots/grid.jpg)

 The main aim is to provide a visual perspective of things like algorithms, graphs, mathematical operations, cellular automation etc.

#### Implementation

Uses openGL, specifically legacy openGL. I decided to use legacy because I really wanted to learn immediate mode rendering since I have somewhat knowledge of how retained mode works.

Uses nuklear for the controls.

#### How to build

###### Windows

```
git clone https://github.com/Jnjenga/vision
cd vision
.\premake\premake5 vs2017
```

A new directory ``` workspace ```  containing the project files will be created. 

Open the ```VisionWorkspace.sln``` build the project and run it using visual studio.

###### Linux

```
git clone https://github.com/Jnjenga/vision
cd vision
./premake/premake5 gmake2
./make_run
```
This will run the project
