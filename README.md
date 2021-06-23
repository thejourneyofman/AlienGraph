# AlienGraph

### Keywords
### #evolutionary theory #graph theory #game theory

### Concept
To prove my guess, on the earth there is no alien or all aliens. There are three "instances" A, B and C who could be either human beings or alien, if A and B are communicating in alien language, and so do A and C next, then B and C will communicate in alien language too. Its mathematics description is, given N vertices (∀Vi ∈[0,1,...N-1]), two players start drawing lines with two different colors (green or red) in rotation following a simple rule, that is, if two edges of a triangle are painted with the same color(Cm, ∈[0,1]), the third edge will be painted in this color too. Here is a few examples with N=5.

![green is winner](https://github.com/thejourneyofman/AlienGraph/blob/main/images/green_win.gif)
![red is winner](https://github.com/thejourneyofman/AlienGraph/blob/main/images/red_win.gif)


```
STEP 1 [Player 1] 0,2 green
Player 1 (0,2)
Player 2
STEP 2 [Player 2] 3,4 red
Player 1 (0,2)
Player 2 (3,4)
STEP 3 [Player 1] 1,3 green
Player 1 (0,2)(1,3)
Player 2 (3,4)
STEP 4 [Player 2] 0,1 red
Player 1 (0,2)(1,3)
Player 2 (3,4)(0,1)
STEP 5 [Player 1] 1,4 green
Player 1 (0,2)(1,3)(1,4)(3,4)
Player 2 (0,1)
STEP 6 [Player 2] 2,3 red
Player 1 (0,2)(1,3)(1,4)(3,4)
Player 2 (0,1)(2,3)
STEP 8 [Player 1] 0,3 green
Player 1 (0,2)(1,3)(1,4)(3,4)(0,3)(2,3)(0,1)(0,4)(1,2)(2,4) green
Player 2 null red
```
(done！)

## My conjecture consists of three parts:
### 1, All evolutions will end at a complete graph of all the edges painted in the same color, in other words, winner takes all;
### 2, The first player who draws the first line holds the "absolute" advantage;
### 3, Given two strategies, "aggressive" and "passive", only when both players selected "passive" strategies, the second player could have chance to win.


## Bonus:
### 1, Prove its infinite version, where the number of verticies is infinite.
### 2, Prove its high dimensional version, where its dimension is greater than 2.

## Bonus of bonus
### To expand the infinite version in a specific case, given that the vertices are continuously being generated as the game goes on, the number of new vertices follows a function of Increment(t) which has a power law distribution, where new chances were granted to both players but less and less, we are going to derive the probability density function of whom would be a winner, as PDF(Increment, t), where t ∈[1, ∞].
