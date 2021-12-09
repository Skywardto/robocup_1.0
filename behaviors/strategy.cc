#include "naobehavior.h"
#include "../rvdraw/rvdraw.h"

#include<algorithm>//quick sort

void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {
    beamX = -HALF_FIELD_X + worldModel->getUNum();
    beamY = 0;
    beamAngle = 0;
}
struct Min
{
   double distance;
   int num;
}leftMin[4],topMin[4],downMin[4],rightMin[4];

bool cmp (Min a ,Min b)
{
    if(a.distance>=b.distance)
    {
        return false;
    }
    else 
    {
        return true;
    }
}
SkillType NaoBehavior::selectSkill() 
{

    VecPosition goalLeft = ball+VecPosition(-0.5,0,0);
    VecPosition goalTop = ball+VecPosition(0,1,0);
    VecPosition goalDown = ball+VecPosition(0,-1,0);
    VecPosition goalRight = ball+VecPosition(4,0,0);
    VecPosition temp;
    bool isFallen;
    
    for(int i=WO_TEAMMATE1;i<WO_TEAMMATE1+4;++i)
    {
       
        if (worldModel->getUNum() == i) 
        {
             isFallen=worldModel->isFallen();
             leftMin[i-1].num=i;
             topMin[i-1].num=i;
              downMin[i-1].num=i;
               rightMin[i-1].num=i;
            leftMin[i-1].distance=me.getDistanceTo(goalLeft)+isFallen;
             topMin[i-1].distance=me.getDistanceTo(goalTop)+isFallen;
              downMin[i-1].distance=me.getDistanceTo(goalDown)+isFallen;
               rightMin[i-1].distance=me.getDistanceTo(goalRight)+isFallen;
        } 
        else 
        {
            WorldObject* teammate = worldModel->getWorldObject(i);
          
        if (teammate->validPosition) 
            {
            isFallen=worldModel->getFallenTeammate(i);
            temp=teammate->pos;
            leftMin[i-1].num=i;
             topMin[i-1].num=i;
              downMin[i-1].num=i;
               rightMin[i-1].num=i;
            leftMin[i-1].distance=temp.getDistanceTo(goalLeft)+isFallen;
             topMin[i-1].distance=temp.getDistanceTo(goalTop)+isFallen;
              downMin[i-1].distance=temp.getDistanceTo(goalDown)+isFallen;
               rightMin[i-1].distance=temp.getDistanceTo(goalRight)+isFallen;
            }
        else 
            {
            continue;      
            }
        }
    }
    sort(leftMin,leftMin+4,cmp);
    sort(topMin,topMin+4,cmp);
    sort(downMin,downMin+4,cmp);
    sort(rightMin,rightMin+4,cmp);

    int num[4]{};
    num[0]=leftMin[0].num;
    int i=0,j=0;

    if(num[0]==topMin[0].num)
    {
        num[1]=topMin[1].num;
    }
    else
    {
        num[1]=topMin[0].num;
    }

    for(;i<3&&j<3;)
    {
        if(num[i]==downMin[j].num)
            {
                j++;
                i++;
            }
            else i++;
    }
    num[2]=downMin[j].num;
    i=0;
    j=0;
    for(;i<4&&j<4;)
    {
        if(num[i]==rightMin[j].num)
            {
                j++;
                i++;
            }
            else i++;
    }
    num[3]=rightMin[j].num;


        if(worldModel->getUNum()==num[0])
        {
            VecPosition target = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, goalLeft, true/*keepDistance*/);
        return goToTarget(target);
        }
        else if (worldModel->getUNum()==num[1])
        {
           VecPosition target = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, goalTop, true/*keepDistance*/);
        return goToTarget(target);
        }
        else if(worldModel->getUNum()==num[2])
        {
            VecPosition target = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, goalDown, true/*keepDistance*/);
        return goToTarget(target);
        }
        else
        {
            VecPosition target = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, goalRight, true/*keepDistance*/);
        return goToTarget(target);
        }
}
   




