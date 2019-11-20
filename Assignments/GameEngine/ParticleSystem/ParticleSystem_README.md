# -> [Particle System](/Assignments/GameEngine/ParticleSystem/ParticleSystem.cpp) <-

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Assignments/GameEngine/Image/ParticleSystem.gif?raw=true" />

This is created using OpenGL.

The structure is simple.

It started with main loop which will run a sinlge class instance called Application.

In Application, objects or particles are created and updated.

There is a class called Particled System which is served as a platform to control particles with particle affectors (rotation, attractor, scale, color, movement etc).

Particle Object is a class that inherits from Game Object class which has the basic attributes for a game, such as sprite, position, rotation, blending mode, scale etc.

Particle Object has some attributes that helps to control itself. The most obvious one will be its lifetime as the performance of the game will be slowed down if all the particles are always alive and never removed from the game.

In this implementation, I put in a simple AABB box collision so when the particles touches the 'box' object in the middle, their lifetime is set to zero.
