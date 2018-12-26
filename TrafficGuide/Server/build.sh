#!/usr/bin/env bash

g++ -g -pthread -fpermissive             \
    -o ../output/TrafficGuideServer.exe  \
    Infrastructure/*                     \
    Entry.cpp
