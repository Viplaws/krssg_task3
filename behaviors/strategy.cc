#include "naobehavior.h"
#include "../rvdraw/rvdraw.h"

extern int agentBodyType;

/*
 * Real game beaming.
 * Filling params x y angle
 */
void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {
    beamX = -HALF_FIELD_X + worldModel->getUNum();
    beamY = 0;
    beamAngle = 0;
}


SkillType NaoBehavior::selectSkill() {
    // My position and angle
    // << worldModel->getUNum() << ": " << worldModel->getMyPosition() << ",\t" << worldModel->getMyAngDeg() << "\n";

    // Position of the ball
    //cout << worldModel->getBall() << "\n";

    // Example usage of the roboviz drawing system and RVSender in rvdraw.cc.
    // Agents draw the position of where they think the ball is
    // Also see example in naobahevior.cc for drawing agent position and
    // orientation.
    /*
    worldModel->getRVSender()->clear(); // erases drawings from previous cycle
    worldModel->getRVSender()->drawPoint("ball", ball.getX(), ball.getY(), 10.0f, RVSender::MAGENTA);
    */

    // ### Demo Behaviors ###

    // Walk in different directions
    //return goToTargetRelative(VecPosition(1,0,0), 0); // Forward
    //return goToTargetRelative(VecPosition(-1,0,0), 0); // Backward
    //return goToTargetRelative(VecPosition(0,1,0), 0); // Left
    //return goToTargetRelative(VecPosition(0,-1,0), 0); // Right
    //return goToTargetRelative(VecPosition(1,1,0), 0); // Diagonal
    //return goToTargetRelative(VecPosition(0,1,0), 90); // Turn counter-clockwise
    //return goToTargetRelative(VecPdosition(0,-1,0), -90); // Turn clockwise
    //return goToTargetRelative(VecPosition(1,0,0), 15); // Circle

    // Walk to the ball
    //return goToTarget(ball);

    // Turn in place to face ball
    /*double distance, angle;
    getTargetDistanceAndAngle(ball, distance, angle);
    if (abs(angle) > 10) {
      return goToTargetRelative(VecPosition(), angle);
    } else {
      return SKILL_STAND;
    }*/

    // Walk to ball while always facing forward
    //return goToTargetRelative(worldModel->g2l(ball), -worldModel->getMyAngDeg());

    // Dribble ball toward opponent's goal
    //return kickBall(KICK_DRIBBLE, VecPosition(HALF_FIELD_X, 0, 0));

    // Kick ball toward opponent's goal
    //return kickBall(KICK_FORWARD, VecPosition(HALF_FIELD_X, 0, 0)); // Basic kick
    //return kickBall(KICK_IK, VecPosition(HALF_FIELD_X, 0, 0)); // IK kick

    // Just stand in place
    //return SKILL_STAND;

    // Demo behavior where players form a rotating circle and kick the ball
    // back and forth
    return demoKickingCircle();
}


/*
 * Demo behavior where players form a rotating circle and kick the ball
 * back and forth
 */
SkillType NaoBehavior::demoKickingCircle() 
{
    // Parameters for circle
    VecPosition center = VecPosition(HALF_FIELD_X, 0, 0);
    //double circleRadius = 5.0;
    //double rotateRate = 2.5;

    VecPosition temp;

    // Find closest player to ball
    int playerClosestToBall = -1;
    double closestDistanceToBall = 10000;
    for(int i =WO_OPPONENT1; i < WO_OPPONENT1+NUM_AGENTS; ++i)
    {
        
        int playerNum = i - WO_OPPONENT1 + 1;
        if (worldModel->getUNum() == playerNum) {
            // This is us
            temp = worldModel->getMyPosition();
        } 
        else 
        {
            WorldObject* opponent = worldModel->getWorldObject( i );
            if (opponent->validPosition) 
            {
                temp = opponent->pos;
            } 
            else
            {
                continue;
            }
        }
        temp.setZ(0);

        double distanceToBall = temp.getDistanceTo(ball);
        if (distanceToBall < closestDistanceToBall) 
        {
            playerClosestToBall = playerNum;
            closestDistanceToBall = distanceToBall;
        }kickBall(KICK_DRIBBLE, newtarget);
    }
    //cout<<me.getDistanceTo(ball)<<endl;    
    if (me.getDistanceTo(temp)<0.25)
        {
            if(me.getDistanceTo(ball)<0.25)
            {
                return goToTargetRelative(VecPdosition(0,-1,0), -90); // Turn clockwise
            }
       return SKILL_STAND;
        }    

    if (me.getDistanceTo(ball)<0.5 && ball.getDistanceTo(center)<1)
    {
        return kickBall(KICK_FORWARD, VecPosition(FIELD_X, 0, 0));
    }
    else if (me.getDistanceTo(ball)<0.25 && me.getDistanceTo(temp)<5)
    {
        //goToTargetRelative(worldModel->g2l(ball), -worldModel->getMyAngDeg());
        return kickBall(KICK_DRIBBLE, VecPosition(HALF_FIELD_X, -temp.getY(), 0));
    }
    else if (me.getDistanceTo(ball)<10 && me.getDistanceTo(ball)>5)
    {
        VecPosition newtarget ;
        newtarget = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, temp, true/*keepDistance*/);
        return goToTargetRelative(worldModel->g2l(ball), -worldModel->getMyAngDeg());
    }
    else
    {
        return goToTargetRelative(worldModel->g2l(ball), -worldModel->getMyAngDeg());

    }
        
    }


