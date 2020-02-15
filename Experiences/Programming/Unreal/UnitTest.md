# C++ Unit Test In Unreal Engine 4 (For Beginner)
I hope this page can help out someone like me who had totally no idea how to get his hand on C++ Unit Test in Unreal Engine 4. Although this is a basic intro, I assume who is reading this has fundamental knowledge of programming. This will mainly focus on C++ side and leave the set up or run test for you to figure out. Maybe [this Unreal page](https://docs.unrealengine.com/en-US/Programming/Automation/index.html) helps.

## Pages I Strongly Recommend To Have A Look At
[Zompi's blog](http://zompi.pl/unreal-engine-4-automation-tests-new-api/) - When I first searched for information on Unit Test in Unreal Engine 4, this blog was the best I could find. It gave me an introduction to Unit Test in Unreal Engine 4 and helped me a lot before I found the official page. 

[Ofiicial document](https://docs.unrealengine.com/en-US/Programming/Automation/AutomationSpec/index.html) - Provided by Unreal. I'm not sure if this was created before my touch on Unit Test or after. Anyways, I found it after I have been working on Unit Test for sometimes. It provides tons of information about the specs or funtionalities for writing C++ Unit Test in Unreal Engine 4. It also mentions the flow or the order of how the code and tests run in Unreal.

#### Why Unit Test?
Long story short, Unit Test allows us to check if the functionality of a piece of code is designed as intended. The test should be written as independent as possible. Means that it should not rely on anything so if an unrelated function is removed, the test will still pass. There are other tests for that. Unit Test focuses on testing just the functionality of a simple piece of code but not the system.

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
There are different type of tests under the name of Automation Tests such as Unit Test, Functional Test, Stress Test, Smoke Test, and so on. Since this is about Unit Test, let's leave the other aside for now. 

#### Sample For Reference
Personally, it will be easier for me to learn or understand if there is a reference. So I will go through it step by step, with a sample test `.cpp` file.

**Disclaimer: Due to confidentiality, I cannot copy and paste the project code here. So do not get confused if some errors pop out saying this header file or XXX doesn't exist. It's probably a grammar mistake or has a similar name to it. Do refer to the links I provided or search it up online. I will try my best to remember them but if it shows up error, I'm sorry about that.**
```
// This is an empty cpp file you just created for the test,  of course, link to Unreal Engine

#include "AutomationTest.h"
#include "AutomationCommon.h"
#include "World.h"
// Include the file that has the functions you want to test, maybe like a class that has functions about shooting
#include "ShootingClass.h"

// Unreal Automation Spec, I won't go into the naming convention area. You probably should refer to another page and test it out yourself. After all, I believe best way to learn is to practice.
BEGIN_DEFINE_SPEC(NameForTest, "ProjectName.NameThatHelpUnrealCategorize", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
// Global variables that are shared by all tests go here
UWorld* World = nullptr;
AShooterClass* ShooterA;
END_DEFINE_SPEC(NameForTest)

// Tests in this function will be executed. Generally, you only need this function to run test. Class is not needed.
void NameForTest::Define()
{
    // Code to run before each tests
    BeforeEach([this]()
    {
        // Normally I will initialize variables here
        // Note: Try not to do any test in this scope as `BeforeEach` is not meant to test any expectation,
        // do read the unreal link I provided for more information
        
        /** Function from Unreal Automation header file
        *   Basically, it opens up a map for your test to run in it
        */
        AutomationOpenMap("/Project/Path/TestMaps/ExampleMap");
        // Pointer to created world <- Something I can't really remember the details
        World = GetWorld();
        
        // Validation Check
        if (!IsValid(ShooterA))
        {
            // Can't remember if this is correct. But it should be quite easy to get the correct name from Unreal
            FSpawnParameter SpawnParams;
            // Spawn Actor in the world
            ShooterA = World->SpawnActor<AShooterClass>(FVector::ZeroVector, FVector::ZeroRotator, SpawnParams);
        }
    });

    // Code to run after each tests
    AfterEach([this]()
    {
        // Normally I would do any clean up here
        
        // Note: Again, try not to do any test in this scope as `AfterEach` is not meant to test any expectation,
        // do read the unreal link I provided for more information
        
        ShooterA->Destroy();
    });

    // Describe doesn't really do anything, literally just 'describe' the string in the output log
    Describe("Fire Function", [this]()
    {
        /* In Unreal Document, `It` is literally means it. In this case, `It` means "Fire Function".
        *  So in the log, this will show : Fire Function.Should shoot one bullet out.
        *  My practice is to describe the `It` in full sentence. Something like "ShootBullet should only fire one bullet out."
        */ It really depends on how you want to do it that will make thing easier to you and your team. At least in my opinion, there isn't any wrong or correct way to do it. 
        It("Should shoot one bullet out", [this]()
        {
            ShooterA->ShootBullet();
            
            // There are different TestX function provided. You may want to look at them in the AutomationTest file. Or maybe AutomationCommon file. Example: TestFalse, TestNotEqual, TestNull etc.
            // Assuming there are some variables created in ShooterClass
            TestEqual("ShootBullet should only creates one bullet", ShooterA->NumberOfBulletShot, 1);
            TestTrue("bIsBulletShot should be changed to true", ShooterA->bIsBulletShot);
            TestNotNull("Bullet reference in ShooterA should be valid", ShooterA->ShotBullet);
        });
        
        // Another test that related to the Fire Function can be put here. I will just leave it blank here
        It("", [this]()
        {
            
        });
    });
    
    Describe("Reload Function", [this]()
    {
        // Tests that related to the Reload Function can be put here. I will just leave it blank here
        It("", [this]()
        {
            
        });
    });
    
    
    Describe("Shoot Skill Function", [this]()
    {
        /** Latent function - Function that runs for few ticks
         *  Sometimes your function needs to runs for few frames, latent test can be used for its test
         *  Example: Skill that tells player how many enemies still alive
         *  Similar to `It` function with extra parameter that let you do something in another thread
         *  Generally I just do it in GameThread
         *  FDoneDelegate YourVariableName : basically just for the engine to know if the latent test finishes the job
         */
        LatentIt("HealthCheckSkill from Shoot Skill", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
        {
            // Because latent test runs on a separate thread we have to ensure that game logic tests run on a Game Thread. 
            AsyncTask(ENamedThreads::GameThread, [this]() 
            {
                ShooterA->UseSkill();

                TestTrue("Something something", ShooterA->bUsedSkill);
                // Some other test
            });

            // Wait for X second. Let's say 1.0f second.
            FPlatformProcess::Sleep(1.0f);

            // Again, GameThread
            AsyncTask(ENamedThreads::GameThread, [this]() 
            {
                // You may do something here
                // In this example, I will straight jump to the test part
                TestEqual("X number of enemies left.", ShooterA->NumberOfEnemiesLeft, X);
            });

            // This will delegate to inform Unreal Automation System that the latent function has finished.
            // So it will run other stuff. If I am not wrong, `latent functions` normally will only run after all the non-latent functions.
            TestDone.Execute();
        });
    });
}
```

After the code is compiled, assuming everything is set up correctly in the project, we should be able to see the test in Unreal Editor. We can find the Automation window tab in Windows->DeveloperTools->SessionFrontend. In the Automation window tab, we can run the test.

#### Conclusion
Basically that's it! Hope these basic intro can help somebody out. But do have a look at the links I provided as they provide much more details about the Automation Test in Unreal Engine 4.
