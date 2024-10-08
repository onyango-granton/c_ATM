#!/bin/bash
rm linuxOutput
gcc auth.c main.c system.c -o linuxOutput
./linuxOutput