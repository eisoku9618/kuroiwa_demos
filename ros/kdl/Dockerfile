FROM ros:melodic-ros-core

RUN apt update \
        && apt install -y --no-install-recommends ros-melodic-rviz ros-melodic-kdl-parser ros-melodic-pr2-description \
        && apt install -y --no-install-recommends libgl1-mesa-glx libgl1-mesa-dri \
        && rm -rf /var/lib/apt/lists/*
