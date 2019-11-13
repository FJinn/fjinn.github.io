# -> [ALIVE](https://kdu.itch.io/adt11presents-alive) <-

ALIVE is a 2-players platformer puzzle game.

This is my first experience with Unity engine. In this development process, I have been assigned to to code (C#) gameplay mechanics such as moving boxes, projectile motion (stone throwing), key pick-up, crawling, and some UI indicator.  

In order to hint players the hitting point of stone, I have to create a projectile indicator, one such as the projectile dots in Angry Bird. 

It is easily done with Physics and Mathematics. The basic idea is to utilize the formula below:

x position = x initial + x initial velocity * time

y position = y initial + y initial velocity * time + 0.5 * gravity * time * time
