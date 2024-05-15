# Dual-Arms
Dual arms in robotic club Tishreen univercity


1. make sure to install Qt5 libraries:
2. build libfreenect:

```bash
git clone https://github.com/OpenKinect/libfreenect 
cd libfreenect 
mkdir build && cd build 
cmake .. 
make 
sudo make insttall 
```

3. build the project
```bash
mkdir ws && cd ws
git clone https://github.com/AliJohn5/Dual-Arms.git
catkin_make
```

3. run the project
```bash
roscore
source devel/setup.bash
rosrun template_gui_package RCArms
```


