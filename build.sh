#!/usr/bin/bash
rm -rf build
bear -- make
cd build
w4 bundle cart.wasm --title "Shmup Wars" --html index.html
cd ..
rm -f docs/index.html
sed -e '/<\/style>/rResources/meta.html' build/index.html > docs/index.html
