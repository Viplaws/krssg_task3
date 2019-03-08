# krssg_task3

Main changes are done in strategy.cc and rest all files are same. And yes the opponents file player numbers needs to be changed to 4 and
our own to 1 and we simply use functions from naobehaviors.cc.And kickBall(KICK_DRIBBLE, VecPosition(HALF_FIELD_X, -temp.getY(), 0));
is the best function ever which makes life so easy for our humainoid bot.Although lot of functions were predefined such as the bot getting up on itself and we could improvise on a lot of factors using the worldmodel and my strategies are as follows:-

1)The bot avoids collision with the opponent bots
2)Then we calculate the nearest opponent bo using WO_OPPONENT
3)Then for most of the conditions when we are very near to the ball we use return goalkick with dribble and otherwise we use goto ball if the distance is more
4)if we come within near the goal i.e,HALF_FIELD_X then we use goalkick (forward)
