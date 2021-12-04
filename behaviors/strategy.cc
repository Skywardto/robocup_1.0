#include "naobehavior.h"
#include "../rvdraw/rvdraw.h"

extern int agentBodyType;

void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {
    beamX = -HALF_FIELD_X + worldModel->getUNum();
    beamY = 0;
    beamAngle = 0;
}


SkillType NaoBehavior::selectSkill() 
{

     VecPosition goal1 = VecPosition(3, 3, 0);//xie bu liao zhu shi !
    VecPosition goal2 = VecPosition(3, 4, 0);//zen me da zhong wen ?
    VecPosition goal3 = VecPosition(HALF_FIELD_X, 0, 0);
    VecPosition temp;
    bool s1=true;
    double distance;

    for(int i=WO_TEAMMATE1;i<WO_TEAMMATE1+2;++i)
    {
        VecPosition temp;
        int playerNum = i - WO_TEAMMATE1 + 1;
        if (worldModel->getUNum() == 2) {
            // This is us
            temp = worldModel->getMyPosition();
        } else {
            WorldObject* teammate = worldModel->getWorldObject( i );
            if (teammate->validPosition) {
                temp = teammate->pos;
            } else {
                continue;
            }
        }
        temp.setZ(0);
        double distanceToBall = temp.getDistanceTo(ball);
        if (distanceToBall >1.5) 
        {
            s1=true; 
        }
        else
        {
            s1=false;
        }
    }
    if(WO_TEAMMATE1 == worldModel->getUNum())
    {
        if(s1)
        {
            return kickBall(KICK_IK,goal1);
        }
           else
           return SKILL_STAND;
    }   
    else
    {
        if(!s1)
           {
            return kickBall(KICK_DRIBBLE,goal3);
           }
        else
        {
        goal2 = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, goal2, true/*keepDistance*/);
        return goToTarget(goal2);
        }
 
    }
}



