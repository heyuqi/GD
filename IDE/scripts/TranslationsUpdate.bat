@echo off
echo Listing all sources files...

dir ..\*.cpp /L /b /s  |find /v /i "\bin\"  > %TEMP%\listfile.txt
dir ..\*.h /L /b /s  |find /v /i "\bin\"  >> %TEMP%\listfile.txt
dir ..\..\GDCpp\GDCpp\*.cpp /L /B /S >> %TEMP%\listfile.txt
dir ..\..\GDCpp\GDCpp\*.h /L /B /S >> %TEMP%\listfile.txt
dir ..\..\GDJS\GDJS\*.cpp /L /B /S >> %TEMP%\listfile.txt
dir ..\..\GDJS\GDJS\*.h /L /B /S >> %TEMP%\listfile.txt
dir ..\..\Extensions\*.cpp /L /B /S |find /v /i "\TileMapObject\"  >> %TEMP%\listfile.txt
dir ..\..\Extensions\*.h /L /B /S |find /v /i "\TileMapObject\"  >> %TEMP%\listfile.txt
dir ..\..\Core\GDCore\*.cpp /L /B /S >> %TEMP%\listfile.txt
dir ..\..\Core\GDCore\*.h /L /B /S >> %TEMP%\listfile.txt

echo Generating .POT file...
xgettext --from-code iso-8859-1  -o useMeToUpdateCatalogsWithPoEdit.pot --c++ --no-wrap -f %TEMP%\listfile.txt -k_

echo .POT file generated: Update now .po catalogs using poEdit (Open .po catalog with PoEdit, and choose Catalog:Update from .POT file)