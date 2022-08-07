# Tutorials on Ceres Solver for the RRC Summer School

This tutorial is intended to introduce beginners to the use of ceres solver to solve optimization problems. 

It consists of three simple examples. 

**Example1.cpp** is a Hello World program of Ceres, where an unconstrained optimization is performed to obtain the roots of a quadratic equation.

**Example2.cpp** is a further extension where Ceres is used to solve a system of equations.

**Example3.cpp** explanins the structure of the program, that can be followed to implement Bundle Adjustment. 


## Setup and Installation Instructions 

1. Install [ROS](http://wiki.ros.org/noetic/Installation) (We encourage students to setup their programs as a ROS package). 
2. Create a workspace
```
mkdir Ceres_ws
cd Ceres_ws
mkdir src
catkin_make
```
3. Follow Instructions [Here](http://ceres-solver.org/installation.html) to install Ceres Solver. 
4. Installation and Running the package
```
cd src
git clone https://github.com/sudarshan-s-harithas/Ceres_Tutorials.git
catkin_make 
```
5. Execution of the Program

Run the following commands from the **Ceres_ws** directory. 

```
source devel/setup.bash
rosrun ceres_tutorials Ceres_example1
rosrun ceres_tutorials Ceres_example2
rosrun ceres_tutorials Ceres_example3
```


