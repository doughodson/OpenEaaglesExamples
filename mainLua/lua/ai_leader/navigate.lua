local State     = require "state"
local Behaviors = require "behaviors"
local Common    = require "common"

local stage = 0

local function enter( entity )
    print( "LUA_Agent starting navigation!" )
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
    
    if ( stage == 0 ) then
        DIFF_HEADING  = ( 0 * math.pi/180 ) - entity.planeState.heading
        DIFF_ALTITUDE = ( 10000 * 0.3048 ) - entity.planeState.altitude
        if ( math.abs( DIFF_HEADING ) > 0.1 or math.abs( DIFF_ALTITUDE ) > 100 ) then
            pMaAction = Behaviors:LuaPlaneClimbDiveCurve( entity.planeState, 30000, math.abs( DIFF_HEADING ) )
        else
            stage = 1
            pSyAction = Behaviors:LuaPlaneDataLinkCommand( entity.planeState, "next" )
        end
    elseif ( stage == 1 ) then
        DIFF_HEADING  = ( 90 * math.pi/180 ) - entity.planeState.heading
        DIFF_ALTITUDE = ( 5000 * 0.3048 ) - entity.planeState.altitude
        if ( math.abs( DIFF_HEADING ) > 0.1 or math.abs( DIFF_ALTITUDE ) > 100 ) then
            pMaAction = Behaviors:LuaPlaneClimbDiveCurve( entity.planeState, 15000, math.abs( DIFF_HEADING ) )
        else
            stage = 2
            pSyAction = Behaviors:LuaPlaneDataLinkCommand( entity.planeState, "next" )
        end
    elseif ( stage == 2 ) then
        stage = 0
        pSyAction = Behaviors:LuaPlaneDataLinkCommand( entity.planeState, "next" )
    end
    
    return pMaAction, pSyAction, pStAction
end

local function exit( entity )
    print("LUA_Agent stopping navigation!")
end

transitions = { 
        T12 = { newstate = "engage" },
        T13 = { newstate = "evade" }
    }

local NavigateState = State:new( "navigate", enter, execute, exit, transitions )
return NavigateState