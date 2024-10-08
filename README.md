
# VGU OT-07 Dust Traffic Project
Our group introduced a system that can count the number of vehicles read a series of sensor data and upload data directly on Alibaba cloud  storage [OSS](https://www.alibabacloud.com/en/product/object-storage-service?_p_lc=1).


## Arudino_code directory
The file is coded in Arduino programming language, but it complies with the ARM-based STM32 Blue Pill development board.
Here is a [link](https://www.youtube.com/watch?v=HnB7RTHa2Rw&t=129s) for preparing the coding environment for STM32F103C8T6. In addition, the chosen libraries are released by Adafruit. 

## Installation

You can install through [pip](https://pip.pypa.io/en/stable/) package manager and activate virtual environment
```bash
    pip install -r requirements.txt
    source ./.venv/bin/activate
```
    
## Set up cloud environment
In this section, we instruct some basic steps for setting up an environment. Firstly, you should register an account with [Alibaba](https://www.alibabacloud.com/en/product/object-storage-service?_p_lc=1). In Object Storage Service, you should create a bucket and choose a suitable region. Finally, you create .env in your project folder 
```bash
    OSS_ACCESS_KEY = YOUR-OSS_ACCESS_KEY
    OSS_ACCESS_KEY_SECRECT = YOUR-OSS_ACCESS_KEY_SECRECT
    OSS_ENDPOINT = YOUR-OSS_ENDPOINT
```

## Running Tests

To run the Oakd test, run the following command:
```bash
   python main_api.py -m last_tiny.blob -c last_tiny.json -r demo.avi
```
To run the sensor test, run the following command:
```bash
    python sensor.py

```

## Run Locally

Clone the project

```bash
     git clone https://github.com/leducthanhkim2004/VGU_Dust_Traffic_OT-07.git
```

Go to the project directory

```bash
  cd VGU_Dust_Traffic_OT_07
```

Install dependencies

```bash
  pip install -r requirements.txt
  source ./.venv/bin/activate
```
Set up Alibaba cloud environment [here](#set-up-cloud-environment)
    


Run system 

```bash
    python Run.py
```


 
 
