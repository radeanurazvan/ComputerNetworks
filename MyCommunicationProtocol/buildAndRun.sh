#!/usr/bin/env bash

g++ -g                              \
    -o MyCommunicationProtocol.exe  \
    Adapters/*                      \
    Commands/*                      \
    Fork/*                          \
    File/*                          \
    Protocol/*                      \
    Entry.cpp

echo "Program started:"

./MyCommunicationProtocol.exe