#/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

if [ ! -d "build" ]; then
  echo -e "${RED} Build Directory not found, making one${NC}\n"
  mkdir build
fi

cd build
cmake ..
make
