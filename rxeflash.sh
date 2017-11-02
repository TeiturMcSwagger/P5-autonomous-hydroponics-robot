echo Executing NeXTTool to upload test.rxe...
wineconsole /cygdrive/C/cygwin/nexttool/NeXTTool.exe /COM=usb -download=test.rxe
wineconsole /cygdrive/C/cygwin/nexttool/NeXTTool.exe /COM=usb -listfiles=test.rxe
echo NeXTTool is terminated.
