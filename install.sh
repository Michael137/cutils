#!/bin/bash
mkdir -p target/containers
chmod -R +rx target

cd src/containers
make all
cd ../..
