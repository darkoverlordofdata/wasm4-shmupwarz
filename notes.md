# notes

## deploy
cd build
w4 bundle cart.wasm --title "work brain" --html index.html

## splash
convert splash.png +dither -colors 4 -filter box -normalize png:splash.png
w4 png2src --c splash.png

convert title.png +dither -colors 4 -filter box -normalize png:title1.png
w4 png2src --c title1.png

## sprites
convert wormy.png +dither -colors 4 -filter box -normalize png:wormy.png
w4 png2src --c wormy.png

## menu
w4 png2src --c food.png
w4 png2src --c light.png
w4 png2src --c play.png
w4 png2src --c health.png
w4 png2src --c clean.png
w4 png2src --c meter.png
w4 png2src --c status.png
w4 png2src --c comm.png

convert clean.png +dither -colors 4 -filter box -normalize png:clean.png
convert food.png +dither -colors 4 -filter box -normalize png:food.png
convert light.png +dither -colors 4 -filter box -normalize png:light.png


convert health.png +dither -colors 4 -filter box -normalize png:health.png
convert meter.png +dither -colors 4 -filter box -normalize png:meter.png
convert status.png +dither -colors 4 -filter box -normalize png:status.png
convert comm.png +dither -colors 4 -filter box -normalize png:comm.png

thumbnail 600x335
      "-I/opt/wasi-sdk/share/wasi-sysroot/include/wasm32-wasi/",


[Standard source for entropy #534](https://github.com/aduros/wasm4/issues/534)

<!-- ![alt as seen on bluesky](https://github.com/darkoverlordofdata/demonic/blob/main/use-case-1.png?raw=true) -->

## start screen



```
make
w4 run build/cart.wasm
cd build
w4 bundle cart.wasm --title "Worm Brain" --html index.html
```