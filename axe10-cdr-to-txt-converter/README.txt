��� ������� ��������� ����� ����������� � ������� �������� ���� bash � Linux ��� cmd.exe � Windows
��� ��������������� ������ � /dev/null �� Windows ���������� NUL, �������� ���:
axecdr -d d:\CDRFILE\IN\ -s d:\CDRFILE\ARCHIVE\AXE10\ > NUL

#####################################################################################################
� ������ ������ ������ ��� ��� ���� ������, � ������������ ���� ����� ����� �� �������.
������� ���� ���������� �� ����������:
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
��� ������ � ������ ��������� ����� - �������,�����������,�������� �������� � �.�. ����� ������������
SED � AWK
��� ������ �������� � �������� ����� ����� ������������ sed.
Mac OS X 10.6.8:		sed -i '' 's/ /,/g' out.txt
GnuWin32 sed �� Windows:	sed -e "s/ /,/g" -i out.txt
GnuWin32 sed �� Windows:	sed -e "s/ /,/g" out.txt > res.txt

������������� ���� � ������ TIMESTAMP, ��������� ���� - ����� ���������� � ��������� ��������� � ����
c:\GnuWin32\bin\awk -f tocsv.awk c:\TEMP\xxx\res.txt > out2.txt
