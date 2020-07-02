//Terry Bogard key key capture.

void main(){
   
    int  iPlIndex   = getlocalvar("player");                                            //Player index.
    void vSelf      = getlocalvar("self");                                              //Calling entity.
    int  iIndex     = getlocalvar("player");                                            //Calling Index.
    int  iAni       = getentityproperty(vSelf, "animationID");                          //Caller animation ID.
    int  iFlIdle    = getentityproperty(vSelf, "aiflag", "idling");                     //Self idling?
    int  iFlAttack  = getentityproperty(vSelf, "aiflag", "attacking");                  //Self attacking (freespecial, jumpattack, follow, or attack)?
    int  iFlJump    = getentityproperty(vSelf, "aiflag", "jumping");                    //Self jumping?
    int  iAttackR   = playerkeys(iPlIndex, 2, "attack");                                //Release attack?                              
    int  iUp		= playerkeys(iPlIndex, 0, "moveup");								//Hold  "Up".
    int  iETime;                                                                        //Elpased time.
    int  iKey1AT;                                                                       //Time of last key 1 press.
    int  iCost;                                                                         //Energycost.
    int  iMP;                                                                           //Current MP.
    int  iSeal;                                                                         //Current seal flag.

    if (iAttackR && iFlIdle && !iFlJump)                                                //Release attack while idle and not jumping?
    {
        if (iUp)																		//Holding up?
        {
            iETime  = openborvariant("Elapsed_time");                                   //Get elapsed time.
			iKey1AT = 0; // getentityvar(vSelf, KEY1AT) + 500;                          //Get last Attack press.

            if (iKey1AT < iETime)                                                       //Enough time passed?
            {
                iAni    = openborconstant("ANI_FREESPECIAL6");                         //Set ani to Zaneiken.
                iCost   = getentityproperty(vSelf, "energycost", iAni);                 //Get energy cost.
                iMP     = getentityproperty(vSelf, "mp");                               //Get current mp.
                iSeal   = getentityproperty(vSelf, "seal");                             //Get seal flag.
                
                if (iCost <= iMP && (!iSeal || iCost < iSeal))                          //Have enough MP and not sealed?
                {
                    performattack(vSelf, iAni, 0);                                      //Perform Rising Tackle.                    
                    changeentityproperty(vSelf, "mp", iMP - iCost);                     //Apply energycost.
                    changeplayerproperty(vSelf, "playkeys", 0);                         //Clear key event.
                    return;                                                             //Exit.
                }
            }
        }
    }   
}