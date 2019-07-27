#!/bin/bash

usage(){ 
    printf -- "Usage: $0 \n" 1>&2; 
    printf -- "-s\tset size of the file. Args identical to 'head -c'.\n" 1>&2; 
    printf -- "-n\tset number of files to produce.\n" 1>&2; 
    printf -- "-h\tdisplay this help message\n" 1>&2; 
    printf -- "\nBy default produces one 1M file\n" 1>&2; 
    exit 1; 
}

if [[ $# -eq 0 ]]; then 
   usage
fi

S='1M'
N=1

while getopts ":s:n:h:" opt
    do
        case "$opt" in 
            s) S=${OPTARG} 
                ;;
            n) N=${OPTARG} 
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

for ((i=0;i<$N;i++))
do
head -c $S </dev/urandom > $i.garbage&
done

printf -- "Made $N files by $S size\n"
