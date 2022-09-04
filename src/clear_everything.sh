#!/usr/bin/env bash

for dir in */
do
    cd $dir
    make clear
    cd ..
done

make clear
echo "done"
