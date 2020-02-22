# Consistency In Control

Recently I was playing a new bought game, GTFO with my friends. It is in early access and yet decent enough for players to enjoy themselves.

## Weapons In GTFO

There are 4 type of weapons in GTFO:

- `Melee`

- `Main Weapon`

- `Special Weapon`

- `Tool`

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/UXDesign/Images/ConsistencyInControl/GTFO_LobbyWeaponsMenu.jpg?raw=true"/>

Screenshot of GTFO's game lobby where players choose their weapons.

## Control In GTFO

Just like any other First Person Shooter game, the control scheme for PC is `Left Mouse Button` for `Fire` and `E` key for interaction.

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/UXDesign/Images/ConsistencyInControl/GTFO_InGameLadderUI.jpg?raw=true"/>

## The Unexpected Bit

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/UXDesign/Images/ConsistencyInControl/GTFO_WeaponsMenu.jpg?raw=true"/>

As the screenshot showed, the `Tool` weapons such as `Shotgun Sentry` and `Burst Sentry` shares some similar appearance features with both `Main Weapon` and `Special Weapon`

Intuitively, my friends and I will press the `Left Mouse Button` to use the `Tool` weapon. However, the gun-like `Tool` (`Shotgun Sentry` and `Burst Sentry`) is binded to `E` key for deploy purpose.

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/UXDesign/Images/ConsistencyInControl/GTFO_InGameToolUI.jpg?raw=true"/>

Shreenshot of `Mine Deployer` with control UI.

It makes sense that the action of interacting with an item (In this case, deploying the sentry or mine) is binded to the 'official' interact key `E`. However, these are the reasons why we intuitively press the `Left Mouse Button` to activate the tool.

- In the game, like showed in above screenshot, the `Tool` looks very similar to a weapon where it supposes to fire out a projectile.

- When players start a match, they have to pre-select one of each weapons type which creates a sense of a category. In other words, since they are all 'weapons', they should be having similar functionality (in fact, they are) that helps players to survive. That mindset leads to the idea of all of them should be sharing the same control scheme too. 
  - This is an example of [how our knowledge can influence our perception.](/Experiences/UXDesign/NeuroscienceAndUX.md)
  - In GTFO scenario, one can easily adept to this little counter-intuitive issue as we learn after multiple playthroughs (rehearsal: bringing a knowledge from working memory to long term memory)

## ~~Solution~~ Discussion

Well, this isn't a game breaking issue and I believe most of the players do not even bothered by this. Therefore, this session cannot be called 'solution' but a discussion.

Since it does not affect the gameplay experience, does a developer need to take care of this issue when he/she is developing the next breathtaking game?

**Yes, we should be aware of it!**

There is no guarantee that the game we're making will turn out to be what we've expected in terms of the sales or gameplay experience. We only can do our best to develop a game that is able to provide the best experience to the players.

But, does it really matter?

**Yes and No. It depends.**

Personally, I think it will be best to take care of the issue when we're in the development process. However, in GTFO, it doesn't really matter as this particular issue isn't a big contributor to the game experience that players expect.

Imagine this, you are playing a First Person Shooter game with multiple tiers weapon and each of them is binded to a different key. Let's say the number keys, from 0 to 9. For the players, it may or may not be easy to remember but it certainly is hard to manage. **In GTFO, it is just two keys for a limited scenario, which is definitely managable.**

Memory overload issue aside, what are the possible actions?

**The sky is the limit.**

Someone out there has a better idea for sure, but I will go for the mentioned two points that lead to the issue: similar appearance and the weapon category.

Changing the appearance so the control key for projectile weapon and deployable tool can be easily differentiated by players may be a possible action to consider.

Create different category for different type of weapons. This does not mean it has to create two inventory system but to separate them such as using color, UI position or even a dedicated key.

This doesn't feel right for GTFO.

**As I meantioned, it varies for different games.**

In GTFO, the 'uncomfortable' bit may disappear as soon as players finish their first playthrough. Players do not need to remember tons of information in the game as it provides guide through UI text most of the time. In other words, no memory overload happens in GTFO.

But if it is a game with some complexity regarding to this issue, it certainly needs to be taken care of for a better gameplay experience. For example, in a MMORPG where players can scroll through tons of skill with `Middle Mouse Button` and each of them has a different binding key. `Healing skills` are binded to `Q` key, `damage skills` are binded to `Left Mouse Button`, `defensive skills` are binded to `R` key etc. It will be chaotic for the players to play the game which leads to a terrible gameplay experience.