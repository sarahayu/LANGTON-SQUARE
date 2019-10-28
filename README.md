# Langton's Ant
This is a program to render Langton's Ant in real-time or calculate it instantly in per-pixel format or in a grid.

Wikipedia defines Langton's Ant as 

> a two-dimensional universal Turing machine with a very simple set of
> rules but complex emergent behavior

Rendering options can be chosen by editing the data.txt file to set grid size, cell size (irrelevant in pixel format), and iterations per frame (irrelevant in calculating mode). The rules for langton's ant can be chosen by editing the dir-sequence.txt file, given by integers representing the sequence of turns on consecutive colors. 

Here are some screenshots of various "ants":
![Original Langton's Ant in grid form](https://raw.githubusercontent.com/sarahayu/LANGTON-SQUARE/master/screenshots/default.png)
*Original Langton's Ant in grid form*
![Symmetric pattern in grid form](https://raw.githubusercontent.com/sarahayu/LANGTON-SQUARE/master/screenshots/symmetric.png)
*Symmetric pattern in grid form*
![Triangular ant in grid form](https://raw.githubusercontent.com/sarahayu/LANGTON-SQUARE/master/screenshots/triangle.png)
*Triangular ant in grid form*
![Square ant in pixel form](https://raw.githubusercontent.com/sarahayu/LANGTON-SQUARE/master/screenshots/square-pixel.png)
*Square ant in pixel form*

Library used was SFML