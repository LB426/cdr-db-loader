#!/usr/bin/perl
use CGI;
use Archive::Tar;

my $tar = Archive::Tar->new;
my @files;
my $i=0;
my @fls;
my $fl;
$qw=new CGI;
print "Content-Type: text/html; charset=KOI8-R\n\n";
print "<html>";
print "<head>";
print "<title>Загрузка файлов</title>";
print "</head>";
print "<hr width=100% align=center>";
print "<body text=black bgcolor=99ccaa> ";
print "<CENTER>";
print "Файлы загружены!";
print "<BR>";
print "</body>";
print "</html>";



exit;

