fusionfs-cache
==============

FusionFS is one of active projects of Data-Intensive Distributed Systems Laboratory in Department of Computer Science at IIT. It is an user-level distributed file system designed for extreme large scale high performance computing (HPC) systems to deal with millions of concurrent data accesses. Since the price of solid-state drive (SSD) is much higher than that of hard disk drive (HDD), FusionFS still deals with mechanical hard drives to read and write data, which will significantly reduce the performance of the HPC system. 
In order to mitigate the bottleneck of the data access channel, this project implemented a built-in SSD-caching middleware in the Fusion distributed file system, to manipulate data across heterogeneous storage devices (i.e. SSD and HDD) to achieve a scalable SSD level of I/O performance while keeping the HDD level of capacity and cost. Also implemented Clock, ARC caching algorithms to improve the caching effectiveness.
