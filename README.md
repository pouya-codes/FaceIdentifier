# Real-time Car Occupant Detection and Counting System

This system is a real-time car occupant detection and counting system, which is developed using OpenCV and Qt. It utilizes IP-cameras for video capture and model training. The system includes an end-user interface and uses a relational data model for data storage.

## Demo
You can check out the demo [here](https://www.youtube.com/watch?v=3wgqI4NvuRM\&t=174s).

## Pre-requisites
- NVIDIA GPU (CUDA compatible)
- Qt

## Installation

### Step 1: Install CUDA 

CUDA can be installed by following the instructions on the [official NVIDIA page](https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html). 

### Step 2: Install NVIDIA Video Codec SDK

The NVIDIA Video Codec SDK can be obtained from the [official NVIDIA website](https://developer.nvidia.com/nvidia-video-codec-sdk/download). Follow the instructions provided for installation.

### Step 3: Install Qt

You can download and install Qt from their [official website](https://www.qt.io/download). 

## Building from source

After installing the above dependencies, you can build the project from source by following these steps:

1. Clone the repository: 

```bash
git clone https://github.com/pouya1991/FaceIdentifier.git
```

2. Navigate into the project directory:

```bash
cd FaceIdentifier
```

3. Build the project using Qt:

```bash
qmake FaceIdentifier.pro
make
```

## Usage

After successfully building the project, you can run the application. 

Please refer to the user manual for detailed instructions on how to use the system.
