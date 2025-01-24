#!/bin/bash

for i in {0..10000}
do
  ./a.out input.txt $i >> output.log
done