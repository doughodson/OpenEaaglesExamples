rem
call ..\makedefs.bat
rem
%mcpp% inputs/serverUdp.epp > serverUdp.edl 
%mcpp% inputs/serverTcpMulti.epp > serverTcpMulti.edl 
%mcpp% inputs/serverTcp.epp > serverTcp.edl 
%mcpp% inputs/serverMc.epp > serverMc.edl 
%mcpp% inputs/serverBc.epp > serverBc.edl 
%mcpp% inputs/clientUdp.epp > clientUdp.edl 
%mcpp% inputs/clientTcp.epp > clientTcp.edl 
%mcpp% inputs/clientMc.epp > clientMc.edl 
%mcpp% inputs/clientBc.epp > clientBc.edl 
   
