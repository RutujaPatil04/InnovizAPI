<a href="https://innoviz.tech/">
    <img src="icons/Logo_Dark.png" alt="Innoviz Logo" title="Innoviz" align="right" height="60" />
</a>

# Innoviz API <!-- omit in toc -->

The Innoviz API is the application program interface used for (a) communicating with the software running on an InnovizOne™ LiDAR sensor system and (b) for viewing the point cloud that the LiDAR produces. Point clouds are saved in Innoviz’s proprietary .invz file format.  

The LiDAR uses TCP and UDP to transmit the point cloud and allow configuration: UDP is used to send the point cloud data continuously as a broadcast and TCP is used for command and control. All TCP and UDP parameters, including network settings, are configured in the Innoviz Web Server (under development) or sent to the unit via TCP. The LiDAR supports IPv4. 

The API is used by third-party visualization utilities to enable them to view Innoviz point clouds. 

### Table of Contents:
- [C++](#c)
  - [Building the example - Windows](#building-the-example---windows)
  - [Building the example - Linux](#building-the-example---linux)
  - [Running the example - Windows](#running-the-example---windows)
  - [Running the example - Linux](#running-the-example---linux)
- [Python](#python)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Examples](#examples)
- [ROS](#ros)
  - [Installation](#installation-1)
    - [ROS Melodic for Ubuntu 18.04](#ros-melodic-for-ubuntu-1804)
    - [Catkin for Ubuntu 18.04](#catkin-for-ubuntu-1804)
    - [ROS Noetic for Ubuntu 20.04](#ros-noetic-for-ubuntu-2004)
    - [Catkin for Ubuntu 20.04](#catkin-for-ubuntu-2004)
  - [Build ROS examples](#build-ros-examples)
  - [Stream a live point cloud from a device](#stream-a-live-point-cloud-from-a-device)
  - [Stream a point cloud from an Innoviz device recording](#stream-a-point-cloud-from-an-innoviz-device-recording)
- [Vertical Blooming](#vertical-blooming)


### Supported Operating Systems:
- Windows 10 
    - Requires [Npcap installation](https://nmap.org/npcap/) 
- Ubuntu 18.04


# C++
API documentation can be found [here](https://htmlpreview.github.io/?https://github.com/InnovizTechnologies/InnovizAPI/blob/main/docs/c%2B%2B/html/index.html).
To use the API, add the path of the [include](include) folder to the compiler's "Include Directories" list, and link against the appropriate innovizApi library in the [lib](lib) folder.

## Building the example - Windows
Go to the [examples/cpp](examples/cpp) folder and run:
```
cmake -G "Visual Studio 15 2017 Win64" -B "build"
```
This will create a Visual Studio solution in the "build" directory.
Open the solution and you will be able to build and run the various examples.

## Building the example - Linux
Go to the [examples/cpp](examples/cpp) folder and run:
```
cmake -G "Unix Makefiles" -B "build"
cd build
make all
```
This will build all of the examples.
These projects can be built by running the "make" command from their location.

## Running the example - Windows
The example needs to be able to find the innovizApi library in order to run.
For Windows this means adding the path of the library you wish to use to the PATH environment variable.
<br>
Once this is done, and the application is build, you should be able to run the various example applications from the Visual Studio solution. 

## Running the example - Linux
The example needs to be able to find the innovizApi library in order to run.
For Linux you must add the path to the LD_LIBRARY_PATH environment variable.
<br>
Once this is done, and the application is build, you should be able to run the various example applications. Run them from the "build" folder created [earlier](#building-the-example---linux).
<br>
Additionally, the API requires enhanced networking permissions to run, so the application must be run as sudo or specific priviliges need to be granted with setcap.
<br>
For Example:
```
sudo ./OM_Recording_Example/om_recording_example
```
Or:
```
sudo setcap cap_net_raw,cap_net_admin=eip ./OM_Recording_Example/om_recording_example
./OM_Recording_Example/om_recording_example
```

# Python
## Prerequisites
- Python >= 3.6.
- pybind11 python module.
- numpy python module.

<br>
On windows machines a the Visual Studio Build Tools are required.
This can be downloaded and installed from https://visualstudio.microsoft.com/visual-cpp-build-tools/.

## Installation
To install the module run the following command:
```
python -m pip install {path_to_module}
```
Where *{Path_to_module}* is the path to the ['python' directory](python).

<br>
To uninstall the python module run the following command:
```
python -m pip uninstall innopy
```
On linux distributions use 'python3' instead of 'python' in the commands above.

## Examples
Various examples that use the python interface can be found under [examples/python](examples/python).
The python interface requires enhanced networking permissions to run, so the python scripts must be run as sudo or specific priviliges need to be granted to python using setcap as shown [above](#running-the-example---linux).

# ROS
## Installation
### ROS Melodic for Ubuntu 18.04
To install ROS Melodic run the following commands:
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

sudo apt update

sudo apt install ros-melodic-desktop-full

echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
echo /opt/ros/melodic/lib | sudo tee /etc/ld.so.conf.d/ros.conf
sudo ldconfig

bash

source ~/.bashrc

sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
```
Additional information can be found at https://wiki.ros.org/melodic/Installation/Ubuntu.

### Catkin for Ubuntu 18.04
To install Catkin for Ubuntu 18.04 run the following commands:
```
sudo apt-get install ros-melodic-catkin

sudo apt-get install cmake python-catkin-pkg python-empy python-nose python-setuptools libgtest-dev build-essential
```
Additional information can be found at https://wiki.ros.org/catkin.

### ROS Noetic for Ubuntu 20.04
To install ROS Noetic run the following commands:
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

sudo apt update

sudo apt install ros-noetic-desktop-full

echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
echo /opt/ros/noetic/lib | sudo tee /etc/ld.so.conf.d/ros.conf
sudo ldconfig

bash

source ~/.bashrc

sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
```
Addition information can be found at https://wiki.ros.org/noetic/Installation/Ubuntu.

### Catkin for Ubuntu 20.04
To install Catkin for Ubuntu 20.04 run the following commands:
```
sudo apt-get install ros-melodic-catkin

sudo apt-get install cmake python3-catkin-pkg python3-empy python3-nose python3-setuptools libgtest-dev build-essential
```
Additional information can be found at https://wiki.ros.org/catkin.

## Build ROS examples
To build the ROS examples, go to the [ros/catkin_ws](ros/catkis_ws) directory and run the following commands:
```
bash

catkin_make -DCMAKE_BUILD_TYPE=Release && sudo setcap cap_net_raw,cap_net_admin=eip ./devel/lib/innoviz_ros/Innoviz_one_Device
```

## Stream a live point cloud from a device
To stream a live point cloud from a device, [build the examples](#build-ros-examples), go to the [ros/catkin_ws](ros/catkis_ws) directory, then run the following commands:
```
bash
source ./devel/setup.sh

roslaunch ./src/launch/innoviz_ros.launch
```
## Stream a point cloud from an Innoviz device recording
To stream a point cloud from an Innoviz device recording, [build the examples](#build-ros-examples), go to the [ros/catkin_ws](ros/catkis_ws) directory, then run the following commands:
```
bash
source ./devel/setup.sh

roslaunch ./src/launch/file_reader_ros.launch
```
# Vertical Blooming
The API can be configured to mark or remove pixels that are caused by vertical blooming. When running with this mode enabled the API will achieve a lower FPS.
<br>
This option can be configred by setting the 'vb_usage_mode' attributes in the configuration json file.
The legal values for this option are:
- **0** - Disabled.
- **1** - Mark vertical blooming pixels.
- **2** - Remove vertical blooming pixels.  

The following examples use this mode:
- [C++ OM Deblooming](examples/cpp/OM_DeBlooming_Example)
- [C++ Recording Deblooming](examples/cpp/OM_DeBlooming_Recording_Example)
- [Python OM Deblooming](examples/python/om_get_frame_example.py)
- [Python Recording Deblooming](examples/python/recording_get_frame_deblooming_example.py)