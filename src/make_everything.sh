#!/usr/bin/env bash

for dir in */
do
    cd $dir
    make all
    cd ..
done

make all
echo "done"
