
docker run -it --rm \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v $PWD/lic.txt:/root/....... \
  -e DISPLAY=unix$DISPLAY \
  local/devel /root/clion-2017.3.4/bin/clion.sh 
