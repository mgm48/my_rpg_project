# my_rpg_project

Coding a simple rpg prototype by myself from 0 in C++ for fun. Project in progress but being actively worked on.

## Game design

### Player Character
+ **_Class:_** Cleric, Warrior, Rogue, Wizard.
+ **_Stats:_** HP, MP, Strength, Intellect, Agility, Armor, Element Resistance.
+ **_Abilities and Buffs_**
+ **_Exp and Level Up system_**
+ **_Player Inventory_** 
### Item System
+ **_Equipment:_** Armor and Weapons.
+ **_Useable Items:_** Potions.
### Gameplay
+ **_Enemies:_** Monsters.
+ **_Combat System:_** Turn based combat where actions are: Attacking, Using/Equipping in Inventory and Using Abilities.
+ **_Map and Movement_**
+ **_Inventory:_** Using/Equipping Items.
+ **_Character Sheet:_** Display Character information, including Equipment.

## Project structure

> my_rpg_project

The library that holds the logic for the game.

> rpg_prototype

The application that runs the program.
The main contains the gameplay loop, which includes the following:

> rpg_systems_unit_test

Includes tests for all the game logic and makes sure everything is working as intended.

## Future Updates

+ Monster improvement
+ Vendor/shop system
+ Chest/loot system
+ NPCs and other characters
+ Better game data management (ex. using files)
+ Graphic Interface
