local State 	= require "state"
local Behaviors = require "behaviors"
local Common    = require "common"

local stage = 0

local function enter( entity )
    print( "LUA_Agent starting interception!" )
end

local function execute( entity )
    pMaAction = nil
    pSyAction = nil
    pStAction = nil
	
	dlmsg = entity.planeState.datalinkmessage
    msgtype = Common:GetMsgType( dlmsg )
    if ( msgtype == "command" ) then
        XCmd = Common:GetXCommand( dlmsg )
    elseif ( msgtype == "report" ) then
        XReport = Common:GetXReport( dlmsg )
    elseif ( msgtype == "message" ) then
        XMessage = Common:GetXMessage( dlmsg )
    end
	
	pMaAction = Behaviors:LuaPlaneFlyStraight (entity.planeState, entity.planeState.altitude)
	
	if ( stage == 0 ) then
		pMaAction = Behaviors:LuaPlaneTurn( entity.planeState, 0 ) -- in the future, the command message should declare the proposed heading 
        if (entity.planeState.isTracking == true ) then	
			pMaAction = Behaviors:LuaPlaneFollowEnemy( entity.planeState, 24000 )
			pSyAction = Behaviors:LuaPlaneDataLinkCommand( entity.planeState, "engaging" ) -- the report should declare the engagement
			stage = 1
        else
            pMaAction = Behaviors:LuaPlaneClimbDive( entity.planeState, entity.planeState.altitude + 10000 )           
        end
    elseif ( stage == 1 ) then
        entity.stateMachine:changeState( "engage" )
    end
    
    return pMaAction, pSyAction, pStAction
end


local function exit( entity )
    print("LUA_Agent stopping interception!")
end

transitions = {
        T21 = { newstate = "navigate" },
		T23 = { newstate = "engage" },
        T24 = { newstate = "evade" }
    }

local InterceptState = State:new( "intercept", enter, execute, exit, transitions )
return InterceptState