#!/usr/bin/perl
#
# print a graph with the gnuplot data files from the stdin
#
#
#
# without -with-labels enabled:
#    parse.pl file1 file2 file3
#
# with -with-labels enabled:
#    parse.pl file1 file2 file3 label1 label2 label3
#

@gnuplot_guesses = (
	'/usr/bin/gnuplot',
	'/usr/local/bin/gnuplot',
	'/usr/X11/bin/gnuplot',
	'/usr/X11R6/bin/gnuplot',
	'/opt/bin/gnuplot'
);

$gnuplot_bin = '';
foreach my $guess ( @gnuplot_guesses ) {
	if ( -x $guess ) {
		$gnuplot_bin = $guess;
		last;
	}
}

die "Could not find any gnuplot executable in default locations"
	if $gnuplot_bin eq '';

#
# PARSE OPTIONS
#

use Getopt::Long;

$xrange = " [] ";
$yrange = " [] ";

GetOptions (
	
		"with-xerrorbars" => \$with_xerrorbars,
		"with-yerrorbars" => \$with_yerrorbars,
		"with-labels"     => \$with_labels,
		"help"            => \$help,
		"smooth"          => \$smooth,
		"output=s"        => \$fileout,
		"xrange=s"        => \$xrange,
		"yrange=s"        => \$yrange,
		"xlabel=s"        => \$xlabel,
		"ylabel=s"        => \$ylabel,
		"title=s"         => \$title,
		"type=s"          => \$type,
		"point-size=s"    => \$point_size,
		"font=s"          => \$font,
		"font-size=s"     => \$font_size,
		"xlogscale"	      => \$xlogscale,	
		"ylogscale"	      => \$ylogscale,
		"nokey"           => \$nokey,
		"script=s"        => \$script,
		"mono"            => \$mono,
		"key=s"           => \$key_position,
		"style=s"         => \$style
		);

if ( $#ARGV < 0 || $help ) {
	print "usage: print.pl files..\n".
		   "\n".
		   "options:\n".
			"    [-help]\n".
			"    [-title graph_title]\n".
			"    [-output filename]\n".
			"    [-xrange [[xmin]:[xmax]]]\n".
			"    [-yrange [[ymin]:[ymax]]]\n".
			"    [-with-labels]\n".
			"    [-xlabel label]\n".
			"    [-ylabel label]\n".
			"    [-with-xerrorbars]\n".
			"    [-with-yerrorbars]\n".
			"    [-type outputtype]\n".
			"    [-font font]\n".
			"    [-font-size size]\n".
			"    [-nokey]\n".
			"    [-key key_position]\n".
			"    [-smooth]\n".
			"    [-xlogscale]\n".
			"    [-ylogscale]\n".
			"    [-script file_name]\n".
			"    [-mono]\n".
			"    [-style linespoints|points|imp]\n".
			"\n";
	exit -1;
}

$fileout = "out.eps" if ! defined $fileout;

if ( $with_xerrorbars and $with_yerrorbars ) {
	print "you should not specify both -with-xerrorbars AND -with-yerrorbars\n";
} elsif ( $with_xerrorbars ) {
	$bars = "with xerrorbars";
} elsif ( $with_yerrorbars ) {
	$bars = "with yerrorbars";
} else {
	$bars = "with points";
}

$type = 'x11' if ! defined $type;
$smooth = "smooth csplines" if defined $smooth;
$font = "Times-New-Roman" if ! defined $font;
$font_size = "18" if ! defined $font_size;

$title = "set title \"$title\" font \"$font,$font_size'\" tc lt 3\n"
	if defined $title;
$style = 'linespoints' if not defined $style;

#
# PRINT FILE
#

$script = "/tmp/print.pl.$$" if ! defined $script;

open FILEOUT, ">", $script or die ("could not open file '$script' for writing");

if ( $type eq 'eps' ) {
	$mono = 'mono' if defined $mono;
	$mono = 'color' if ! defined $mono;

	print FILEOUT "set terminal postscript eps enhanced $mono \"$font\" $font_size\n";
	
} elsif ( $type eq 'x11' ) {
	print FILEOUT "set terminal x11 persist font \"$font,$font_size\"\n";

} else {
	print FILEOUT "set terminal $type\n";
}
print FILEOUT "set grid\n".$title;
print FILEOUT "set logscale xy\n" if $xlogscale and $ylogscale;
print FILEOUT "set logscale y\n" if ! $xlogscale and $ylogscale;
print FILEOUT "set logscale x\n" if $xlogscale and ! $ylogscale;
print FILEOUT "set output \"$fileout\"\n" if $type ne 'x11';
print FILEOUT "set xlabel \"$xlabel\"\n" if $xlabel;
print FILEOUT "set ylabel \"$ylabel\"\n" if $ylabel;
print FILEOUT "set key $key_position\n" if $key_position;
print FILEOUT "set pointsize $point_size\n" if $point_size;
print FILEOUT "plot ";

my $linetype = 1;
my $pointtype = 1;
for my $i ( 0 .. $#ARGV ) {
	$title = $ARGV[$i];
	$title =~ s/_/ /g;
	$title =~ s/\.dat//;
	$title =~ s/\.gnuplot//;
	$title =~ s/\./ /g;

	if ( $with_labels ) {
		last if $i == (1+$#ARGV) / 2;
		$title = 'title "'.$ARGV[$i+(1+$#ARGV)/2].'"';
	}
		
	$title = "title \"$title\" " if ! $with_labels;
	$title = "notitle" if $nokey;

	print FILEOUT " $xrange $yrange " if  $i == 0 ;

	print FILEOUT "\"$ARGV[$i]\" $title $bars ps 0.7 pt $pointtype lt 1 lc $linetype" if $style ne 'imp';

	print FILEOUT "\"$ARGV[$i]\" $title w imp lw 5 lc $linetype" if $style eq 'imp';

	print FILEOUT ", \"$ARGV[$i]\" notitle with lines $smooth lt 1 lc $linetype"
		if $style eq 'linespoints';

	print FILEOUT " , " if ( ! defined $with_labels and $i != $#ARGV ) 
		or ( defined $with_labels and $i != ((1+$#ARGV)/2 - 1) );

	++$linetype;
	++$pointtype;
}

print FILEOUT "\n";
close FILEOUT;
system "$gnuplot_bin $script 2>/dev/null 1>/dev/null";

#
# CLEAN UP
#

unlink $script if $script eq "/tmp/print.pl.$$";
