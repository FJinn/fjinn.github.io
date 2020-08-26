# First Custom Shader in Unity

I learned about vertex shader and fragment shader in OpenGL during my university. I figured it would be a good experience to get my hands on Unity ShaderLab. To clarify, I didn't have any clear goal in mind but just playing around while learning. Which means there probably should have better implementation/visual effect somewhere online.

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Unity/ShaderLab/GIF/FadeOut.gif?raw=true"/>

To create above effect, I used 2 noise textures to randomize if the processing pixel should go in which directions.

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Unity/ShaderLab/GIF/Heart.gif?raw=true"/>

Instead of animation or put one sprite on top of another, I combine both textures with a parameter. This created the above effect. [Code](/Experiences/Programming/Unity/ShaderLab/FirstShader)

Continuing on shader experiment, I wanted to create an aura effect, such as a customized shadow indicating character presence.

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Unity/ShaderLab/GIF/Shadow01.gif?raw=true"/>

From the [Code](/Experiences/Programming/Unity/ShaderLab/FirstShader02), it shows that the created effect is kind of hardcoded. Therefore, I went online to do some googling which leads me to [this](https://gamedev.stackexchange.com/questions/152609/moving-texture-according-to-position-in-shader).

And I learnt about **Grab Pass** and **ComputeGrabScreenPos** by creating the following effects. [Code](/Experiences/Programming/Unity/ShaderLab/FirstShader03).

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Unity/ShaderLab/GIF/Shadow02.gif?raw=true"/>

"X-Ray" using **ComputeGrabScreenPos** and **tex2Dproj**.

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Unity/ShaderLab/GIF/Background01.gif?raw=true"/>

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Unity/ShaderLab/GIF/BackgroundParticle01.gif?raw=true"/>
