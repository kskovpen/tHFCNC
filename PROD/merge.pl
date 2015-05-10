#!/usr/bin/perl -w

################################################################################
#                                                                             ##
#                    MadGraph/MadEvent                                        ##
#                                                                             ##
# FILE : merge.pl                                                             ##
# VERSION : 1.2                                                               ##
# DATE : 12 April 2007                                                        ##
# AUTHOR : Michel Herquet (UCL-CP3)                                           ##
#                                                                             ##
# DESCRIPTION : script to merge to LHE events files                           ##
# USAGE :                                                                     ##
# ./merge.pl eventfile1.lhe.gz eventfile2.lhe.gz ... result.lhe.gz banner.txt ##
# Note that result can be eventfile1, eventfile2, ...                         ##
# OUTPUT : merged file, banner                                                ##
################################################################################


# Parse the command line arguments

if ( $#ARGV < 3 ) {
     die "This script must be called with at least four filenames as arguments!\n";
}

# Start by copying the first input file as result

print "Copying first file on output file ... \n";
system("cp ".$ARGV[0]." ".$ARGV[$#ARGV-1]);

my $infile2=$ARGV[$#ARGV-1];
my $outfile=$ARGV[$#ARGV-1];
my $bannerfile=$ARGV[$#ARGV];

# Unzip and open the input files
# print "Unzipping input files ... \n";
# system("gunzip $infile2")==0 || die "Error while unzipping $infile2, stopping\n";
$infile2=~ s/\.gz//;

# Loop over files starting from the second one, and merge each time with the result (initially the first)
for($count=1;$count<=$#ARGV-2;$count++) {

my $infile1=$ARGV[$count];

# system("gunzip $infile1")==0 || die "Error while unzipping $infile1, stopping\n";
$infile1=~ s/\.gz//;

print "Reading input files ... \n";
open(INFILE1,"$infile1") || die "Cannot open input file called $infile1, stopping\n";
open(INFILE2,"$infile2") || die "Cannot open input file called $infile2, stopping\n";

# Extract banner, init and events from event files

my $begin_tag='<header>'."\n";
my $end_tag='</header>';
my $begin_init='<init>'."\n";
my $end_init='</init>';
my $begin_events='</init>'."\n";
my $end_events='</LesHouchesEvents>';

my $fulltext1;
my $fulltext2;

while(<INFILE1>)
{
    $fulltext1 .= $_;
} 
($banner1)= $fulltext1=~ m/$begin_tag(.*)$end_tag/s;
($init1)= $fulltext1=~ m/$begin_init(.*)$end_init/s;
($events1)= $fulltext1=~ m/$begin_events(.*)$end_events/s;

while(<INFILE2>)
{
    $fulltext2 .= $_;
} 

($banner2)= $fulltext2=~ m/$begin_tag(.*)$end_tag/s;
#($init2)= $fulltext1=~ m/$begin_init(.*)$end_init/s;
($events2)= $fulltext2=~ m/$begin_events(.*)$end_events/s;

# Close input files
close(INFILE1);
close(INFILE2);

# Scan banners to extract number of events and cross sections

($num_events1)= $banner1=~ m/#  Number of Events\s*:(.*)\n/;
($xsec1)= $banner1=~ m/#  Integrated weight \(pb\)\s*:(.*)\n/;
$num_events1 =~ s/^\s*(\S*(?:\s+\S+)*)\s*$/$1/;
$xsec1 =~ s/^\s*(\S*(?:\s+\S+)*)\s*$/$1/;

($num_events2)= $banner2=~ m/#  Number of Events\s*:(.*)\n/;
($xsec2)= $banner2=~ m/#  Integrated weight \(pb\)\s*:(.*)\n/;
$num_events2 =~ s/^\s*(\S*(?:\s+\S+)*)\s*$/$1/;
$xsec2 =~ s/^\s*(\S*(?:\s+\S+)*)\s*$/$1/;

print "File $infile1 read with $num_events1 events and $xsec1 xsec\n";
print "File $infile2 read with $num_events2 events and $xsec2 xsec\n";

# Check that cross sections do not differ too much
if( abs(($xsec1-$xsec2)/$xsec1) > 0.05 ) { print "\nWARNING Cross sections do not agree with a 5\% precision!\n";}

# Compute total number of events and new unit weight 
$tot_events=$num_events1+$num_events2;
$xsec=($num_events1*$xsec1+$num_events2*$xsec2)/$tot_events;
$uwgt=sprintf('%0.5E',$xsec/$tot_events);
$disp_xsec=sprintf('%0.5E',$xsec);

# Print out the merged file
print "Creating the merged file with xsec=$disp_xsec, $tot_events events and $uwgt unit wgt ... \n";

my $banner=$banner1;
my $init=$init1;


$banner=~ s/#  Integrated weight \(pb\)\s*:(.*)\n/#  Integrated weight (pb)  :  $disp_xsec\n/;
$banner=~ s/#  Number of Events\s*:(.*)\n/#  Number of Events        :  $tot_events\n/;
$banner=~ s/#  Unit wgt\s*:(.*)\n/#  Unit wgt                :  $uwgt\n/;

$outfile=~ s/\.gz//;

open(OUTFILE,">$outfile") || die "Cannot open output file called $outfile for writing, stopping\n";

print "Updating unit weigth of all events... \n";


@events = split('\n',$events1.$events2);

#$i=0;

$newblock = 0;
$events_final='';
foreach (@events) {

$curr=$_;

#if($curr =~ m/^#/) {$events_final=$events_final.$curr.'\n'; next;}

if($newblock==1) {
    $curr =~ s/^\s+//;
    @param=split(/\s+/,$curr);
    
    if ($#param != 5) { die "Not right number of param in first line of event"; }
    $curr=" $param[0] $param[1] $uwgt $param[3] $param[4] $param[5]";
    $newblock=0;
    # $i++;
    # print $i."\n";
}

if($curr =~ m/<event>/) {$newblock=1;}

$events_final .= $curr."\n";
}


print OUTFILE "<LesHouchesEvents version=\"1.0\">\n";
print OUTFILE "<header>\n";
print OUTFILE $banner;
print OUTFILE "</header>\n";
print OUTFILE "<init>\n";
print OUTFILE $init;
print OUTFILE "</init>\n";
print OUTFILE $events_final;
print OUTFILE "</LesHouchesEvents>\n";

close(OUTFILE);

open(BANNER,">$bannerfile") || die "Cannot open output file called $bannerfile for writing, stopping\n";
print BANNER $banner;
close(BANNER);

# Zip all remaining unzipped files
# print "Zipping files ... \n";
# if( (-e $infile1) && !($infile1 =~ m/\.gz/) ) { system("gzip $infile1")==0 || die "Error while zipping $infile1\n"; }

}
# if( (-e $infile2) && !($infile2 =~ m/\.gz/) ) { system("gzip $infile2")==0 || die "Error while zipping $infile2\n"; }
# if( (-e $outfile) && !($outfile =~ m/\.gz/) ) { system("gzip $outfile")==0 || die "Error while zipping $outfile\n"; }
