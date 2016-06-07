local State     = require "state"
local Behaviors = require "behaviors"
local Common    = require "common"

local stage = 0

local function enter( entity )
    print( "I'm navigating!" )
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
    
    if ( XCmd and XCmd[1] == "next" ) then
        XCmd = nil
        stage = stage + 1
        pSyAction = Behaviors:LuaPlaneDataLinkMessage( entity.planeState, "ok" )
    end
    if ( stage == 0 ) then
        DIFF_HEADING  = ( 0 * math.pi/180 ) - entity.planeState.heading
        DIFF_ALTITUDE = ( 10000 * 0.3048 ) - entity.planeState.altitude
        pMaAction = Behaviors:LuaPlaneClimbDiveCurve( entity.planeState, 30000, 0 )
    elseif ( stage == 1 ) then
        DIFF_HEADING  = ( 90 * math.pi/180 ) - entity.planeState.heading
        DIFF_ALTITUDE = ( 5000 * 0.3048 ) - entity.planeState.altitude
        pMaAction = Behaviors:LuaPlaneClimbDiveCurve( entity.planeState, 15000, 90 )
    elseif ( stage == 2 ) then
        pMaAction = Behaviors:LuaPlaneFlyStraight( entity.planeState, -1 )
    else
        stage = 0
    end
    
    return pMaAction, pSyAction, pStAction
end

local function exit( entity )
    print("I'm stopping navigating!")
end

transitions = { 
        -- T12 = { newstate = "intercept" },
        T13 = { newstate = "evade" }
    }

local NavigateState = State:new( "navigate", enter, execute, exit, transitions )
return NavigateState