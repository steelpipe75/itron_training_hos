cd /d %~dp0

RMDIR /S /Q .\extension\sample\build
RMDIR /S /Q .\extension\aplfw\build
RMDIR /S /Q .\extension\sample_cli\build
RMDIR /S /Q .\extension\aplfw_cli\build

RMDIR /S /Q .\googletest\build
RMDIR /S /Q .\googlemock\build

cmd /k
