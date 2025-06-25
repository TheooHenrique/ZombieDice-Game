# Introduction

The main goal of this project is to develop a working version of the Zombie Dice&copy; dice game to run on a terminal emulator.

The development process involves the application of several programming concepts, including:
```
- Object-Oriented Modeling using classes.
- Generating random numbers for rolling dice.
- Implementing a software architecture based on the game-loop pattern.
- Creating an interactive user interface that runs on the terminal.
- Reading settings from an .ini file to customize the game.
```

The goal for the player in the game is to be the first to accumulate 13 or more brains. The game continues until all players have had an equal number of turns, and the winner is the one with the highest brain score at the end.
As a turn game, is pretty obvious that one of the best methods of implement a zombie_dice game is the `GameLoop` structure. Combining with states, a good plan can save a lot of time thinking about what is going to happen next in the project.


# Author(s)

Theo Henrique da Silva Borges: <theo123b@gmail.com>

Haniel Lucas Machado: <hani.lucas70@gmail.com>

```
- Theo: Made the diagrams, created program functions, created auxiliary functions the singleton class implementation, initializer reader, initializer error_treatment, the process_events() and the update() from Gameloop.

- Haniel: Defined the classes, created program functions, created auxiliary functions, doxygenned, made the interface. 
```

# Problems found or limitations
Here we are listing a lot of problems and limitations that this project certainly have.

## Problems Found:
This project cannot treat tie. That was authors' irresponsibility, but the game was supposed to show two winners if the round_limit were reached AND there are two or more players in the `possible_winner` list. 
This program also does not have the untie action.
A small detail, but this program does not ask the user if he is sure he want to quit when provides a blank space in the `inpu_player`.

## Difficulties:
The author's recognize that this project is incomplete by irresponsability, because we understimated this project power! It was very hard to understand the Gameloop structure, and we think we have a strong difficulty on make a good plan (a good diagram). Despite we did two diagrams (class diagram and state diagram), we used them just a bit compared to this project magnitude.

# Compiling and Running

To compile this code, we are using `g++` compiler. To compile, use this code in root directory of the project:

```shell
g++ ./src/main.cpp ./src/dicebag.cpp ./src/player.cpp ./src/reader.cpp ./src/zdice.cpp -o dice
```
To run the `dice` executable created, run this code

```shell
./dice 
```
Where:
` ./dice: Call the executable create`

If you want to play this game with customized config, change the `z_dice.ini` file and run this way:
```shell
./dice zdice.ini
```
There is no problem if you want to change the `initializer_file` name (but keep the .ini extension).