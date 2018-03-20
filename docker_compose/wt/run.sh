#!/bin/bash
SLURMCONFIG="/etc/slurm-llnl/slurm.conf"
MUNGEKEY="/etc/munge/munge.key"
sWebView="`pwd`/../../..../../../sWebView"
docker run \
	--rm \
    --add-host mintuser-VirtualBox:10.0.2.15 \
	-v $SLURMCONFIG:/etc/slurm-llnl/slurm.conf \
	-v $MUNGEKEY:/etc/munge/munge.key \
	-v $sWebView:/sWebView \
	-p 8080:8080 \
	-ti /bin/bash \
    local/swebview
