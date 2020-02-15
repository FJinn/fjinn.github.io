# C++ Unit Test In Unreal Engine 4

#### Why Unit Test?
Long story short, Unit Test allows us to check if the functionality of a piece of code is designed as intended. 

For example: After writing code for hours, we have to write a piece of code to add score to the game system. Instead of `+`, our tiring brain accidentally code `-`. 
```
void AddScore(int Score)
{
    MyScore -= Score;
}
```
Generally, there are tons of code in a project. So we may not spot the mistake straight away, especially after spending long hours on coding. In some extreme cases, bugs will show up without any clues for us.

With Unit Test, we could easily spot and fix the problem.

#### Automation Test In Unreal Engine 4
There are different type of tests under the name of Automation Tests such as Unit Test, Functional Test, Stress Test, Smoke Test, and so on. 
