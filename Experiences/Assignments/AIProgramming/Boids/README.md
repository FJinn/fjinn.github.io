# [Boid Simulation](/Experiences/Assignments/AIProgramming/Boids/Boids.h)

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Assignments/AIProgramming/Images/BoidSimulation.gif?raw=true" width="800" height="450" />

The idea is to use Physics such as acceleration, velocity, and position to control boids behaviour in order to move the boids in a smooth and relatively nature way.

**Greed Triangle** = Attractor

**Pink Circle** = Obstacle avoidance

**Orance Circle** = Repeller

**Boids (Blue Triangle) Behaviours** = Separation, Alignment, and Coherence.

## Discussion

When I coded this simulation, I only had some basic understandings about AI movement.

So I Googled and implemented Attractor, Obstacle Avoidance, Repeller, Separation, Alignment, and Coherence without seeing the 'big picture'. That is why you might see some unnatural AI movement in the boid simulation.

Recently, I just finished reading AI Movement Chapter from the book 'Artificial Intelligence for Games' by Ian Millington and John Funge.

Including movement like arrival, future prediction, facing target(instead of velocity like implemented), steering pipeline(targeter, decomposer, constarint, actuator) etc. certainly will further complete the boid's AI and improve the movement to be more natural and smooth.

In addition, in this simulation, I only did a basic combining steering behaviour, which is weighted blending.

Weighted blending is basically combining all the velocities (each with its own weight) together and output the result as the final velocity for the AI. 

While this may be fine in several cases, problems arise when there are contraints. This is another reason why the boids in the gif sometimes flicker.

Arbitration may help in some of these cases by allowing one or multiple steering behaviours have total control over other and output its own result velocity as the final velocity.
