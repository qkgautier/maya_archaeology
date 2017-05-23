#!/bin/bash

DATE=`date +%Y_%m_%d_%H_%M_%S`

source /home/e4e/cartographer_ws/install_isolated/setup.bash
rosservice call /finish_trajectory "cartog_$DATE"

