#!/bin/bash

usage(){ 
    printf -- "Usage: $0 \n" 1>&2; 
    printf -- "-s\tenables standard sorting of file\n" 1>&2; 
    printf -- "-f\tpass file to script.\n" 1>&2; 
    printf -- "-h\tdisplay this help message\n" 1>&2; 
    printf -- "\nBy default produces one 1M file\n" 1>&2; 
    exit 1; 
}

if [[ $# -eq 0 ]]; then 
   usage
fi

File=""
Sort=0
while getopts ":s:f:h:" opt
    do
        case "$opt" in 
            s) Sort=1
                ;;
            f) File=${OPTARG} 
                ;;
            h) usage
               exit 0
                ;;
            *) usage
               echo "getopt error while parsing: $OPTERR";
               exit $OPTERR
                ;;
        esac
    done

if [[ $Sort -eq 0 ]]; then 
    od -vtu4 -An -w4 $File
else
    od -vtu4 -An -w4 $File | sort -n
fi
