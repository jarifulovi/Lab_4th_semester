#!/bin/bash

echo "enter directory path : "
read dirPath


if [ -d $dirPath ]; then

	files=$(find $dirPath -type f)
	
	totalFiles=0;
	totalSize=0;
	totalLine=0;
	for file in $files; do 
		
		if [ -f $file ]; then
		
		name=$(basename $file)
		size=$(du -b $file | cut -f1)
		info=$(stat $file)
		fileLine=$(wc -l < $file)

		echo "file name : $name"
		echo "file size : $size"
		echo "lines in the file : $fileLine"
		
		((totalFiles++))
                ((totalSize += size))
                ((totalLine +=fileLine))
                sleep 0.01
		clear
		fi

	done
	echo "total file : $totalFiles"
	echo "total size : $(($totalSize/1000)).$(($totalSize%1000)) mb"
	echo "total lines on those files : $totalLine"
fi
