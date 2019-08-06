#!/bin/bash

UINTS_CNT=$(($1/4))
watch -n0 -d "
echo 'Отступ от начала файла равен' $(($1/(1024**2))) 'MB';
echo 'Файл ' $(ls -lh | cut -d' ' -f5 | sed -n '2p') '$2'
od -vtu4 -An -w4 -j $1 $2 | head -n 40
"

