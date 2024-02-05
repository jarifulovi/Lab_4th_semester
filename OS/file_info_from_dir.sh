#!/bin/bash

echo "enter directory path : "

read dirPath

echo "enter a specific type : (empty for all file types)"

read -r file_type

if [ -d $dirPath ]; then

	files=$(find $dirPath -type f)
	
	totalFiles=0;
	totalSize=0;
	totalLine=0;
	for file in $files; do 
		
		if [ -f "$file" ] && { [ -z "$file_type" ] || [[ $file =~ \.($file_type)$ ]]; }; then
        
		
		name=$(basename $file)
		size=$(du -b $file | cut -f1)
		size_in_readable=$(du -h $file | cut -f1)
		info=$(stat $file)
		fileLine=$(wc -l < $file)

		echo "file name : $name"
		echo "file size : $size_in_readable"
		echo "lines in the file : $fileLine"
		
		((totalFiles++))
                ((totalSize += size))
                ((totalLine +=fileLine))
                sleep 0.01
		clear
		fi

	done
	
	totalSize_readable=$(echo "scale=2; $totalSize / 1024 / 1024" | bc)
	
	echo "total file : $totalFiles"
	echo "Total size: $totalSize_readable MB"
	echo "total lines on those files : $totalLine"
	
	read -p "Please hit enter to continue"
fi
