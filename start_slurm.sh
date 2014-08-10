#! /bin/bash

echo `hostname` 50000 >> /home/dzhao/fusionfs/src/zht/neighbor
sleep 5

/home/dzhao/fusionfs/start_service
/home/dzhao/fusionfs/start
sleep 3600
