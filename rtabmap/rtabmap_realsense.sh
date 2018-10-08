#!/bin/bash

dblink="/home/e4e/.ros/rtabmap.db"

DATE=`date +%Y_%m_%d_%H_%M_%S`
dbfilename="/media/e4e/Data2/.ros/rtabmap_$DATE.db"

if [ -f $dblink	]; then
    rm $dblink
fi

ln -fs ${dbfilename} ${dblink}

roslaunch rtabmap_realsense.launch "$@"

rm $dblink

echo "Database saved to $dbfilename"

