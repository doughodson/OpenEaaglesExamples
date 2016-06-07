local Common = {}
local LuaXML = require "LuaXml"

function Common:GetXReport( textmsg )
    xreport = nil
    xmsg = LuaXML.eval( textmsg )
    if ( xmsg ) then
        xreport = xmsg:find("report")
    end
    return xreport
end

function Common:GetXMessage( textmsg )
    xmessage = nil
    xmsg = LuaXML.eval( textmsg )
    if ( xmsg ) then
        xmessage = xmsg:find("message")
    end
    return xmessage
end

function Common:GetXCommand( textmsg )
    xcommand = nil
    xmsg = LuaXML.eval( textmsg )
    if ( xmsg ) then
        xcommand = xmsg:find("command")
    end
    return xcommand
end

function Common:GetMsgType( textmsg )
    xmsg = LuaXML.eval( textmsg )
    if ( xmsg ) then
        return xmsg[0]
    end
    return nil
end

return Common