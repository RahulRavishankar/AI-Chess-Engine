# AI-Chess-Engine

Language: C++\
Framework: Qt

![alt-text](https://github.com/RahulRavishankar/AI-Chess-Engine/recording.gif)

#### Move generation and Position evaluation
Relative to the player for whom we want to evaluate the position, any of their own pieces will add to their score, and their opponent’s pieces will subtract.

#### Search tree generation using Min-max
Min-max is an algorithm we can use to evaluate all possible moves a player can make. I follow each move to a certain depth(in my case it is 3), which in this instance is how many moves ahead we want to look. Position evaluation will be relative to a player, and that player will be trying to get the best score possible (maximize their position). The opponent be doing the opposite: trying to minimize the original player’s value (which is, in essence, maximizing the opponent’s own value).

