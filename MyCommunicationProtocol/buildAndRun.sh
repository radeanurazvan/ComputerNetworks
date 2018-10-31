#!/usr/bin/env bash

g++ -g                              \
    -o MyCommunicationProtocol.exe  \
    Adapters/*                      \
    Commands/*                      \
    Communication/*                 \
    Fork/*                          \
    File/*                          \
    Guards/*                        \
    Protocol/*                      \
    Entry.cpp

echo "Program started:"

./MyCommunicationProtocol.exe