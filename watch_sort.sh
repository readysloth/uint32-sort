#!/bin/bash

UINTS_CNT=$(($1/4))
watch -n0 -d "
echo 'Отступ от начала файла равен' $(($1/(1024**2))) 'MB';
od -vtu4 -An -w4 -j $1 copied.garbage | column
"

