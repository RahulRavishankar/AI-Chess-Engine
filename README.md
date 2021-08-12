# AI-Chess-Engine

Language: C++\
Framework: Qt

#### Search tree generation using Min-max
Min-max algorithm is used to generate all possible moves a player can make. We follow each move to a certain depth(in my case it is 3), which in this instance is how many moves we want to look-head. Position evaluation is relative to a player, and the User (White) is trying to get the best score possible (maximize their score) and the AI Agent (Black) is trying to minimize the User's score.

#### Position evaluation
Position evaluation is done by adding up all the values of the white pieces and subtracting the values of the black pieces. Large values will favour white and small values will favour black.

![alt-text](https://github.com/RahulRavishankar/AI-Chess-Engine/blob/master/recording.gif)
