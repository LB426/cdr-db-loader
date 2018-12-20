 ак правило программа будет примен€тьс€ в скрипте оболочки типа bash в Linux или cmd.exe в Windows
дл€ перенаправлени€ вывода в /dev/null на Windows используем NUL, например так:
axecdr -d d:\CDRFILE\IN\ -s d:\CDRFILE\ARCHIVE\AXE10\ > NUL

#####################################################################################################
¬ начале каждой записи идЄт код типа записи, в документации этих кодов найти не удалось.
ѕривожу коды полученные по наследству:
00	-  NE	= Effective POTS calls
01	-  NI	= Ineffective POTS calls
02	-  NEI	= Effective ISDN calls
03	-  NII	= Ineffective ISDN calls
04	-  CDE	= Call diversion effective
05	-  CDI	= Call diversion ineffective
06	-  SP	= Subscriber procedure
07	-  NC	= Non-call related service
08	-  SSC	= Subscriber service command
09	-  NEIE	= Effective ISDN-E calls
10	-  NIIE	= Ineffective ISDN-E calls

#####################################################################################################
ƒл€ работы с пол€ми выходного файла - удалить,переставить,заменить добавить и т.д. будем использовать
SED и AWK
дл€ замены пробелов в выходном файле можно использовать sed.
Mac OS X 10.6.8:		sed -i '' 's/ /,/g' out.txt
GnuWin32 sed на Windows:	sed -e "s/ /,/g" -i out.txt
GnuWin32 sed на Windows:	sed -e "s/ /,/g" out.txt > res.txt

ѕреобразовать дату в формат TIMESTAMP, отбросить поле - врем€ завершени€ и сохранить результат в файл
c:\GnuWin32\bin\awk -f tocsv.awk c:\TEMP\xxx\res.txt > out2.txt
