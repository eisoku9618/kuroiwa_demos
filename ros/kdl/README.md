## preparation in local machine

```bash
xhost +
```

## run docker container
```bash
docker build -t test-kdl .
docker run --rm -it --env="DISPLAY" --volume src:/root/catkin_ws/src/ --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" -w /root/catkin_ws/ test-kdl
```
