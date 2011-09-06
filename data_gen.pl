use strict;

#file creation
open (MYFILE, '>data.txt');
print MYFILE "<data>\n";

# used for checking of which positions are filled
my %checkhash={};

#SIZE of PINCHGRIP
my $S_max = 200; my $S_levels = 3;

#WIDTH OF CIRCLE
my $W_max = 100; my $W_levels = 3;

#DIRECTION
my $D_max = 2; my $D_levels = 2;

#ANGLE
my $A_max=180; my $A_levels=3;

# note: resolution is 1920 x 1080, but we need to have a safety margin
#X-POSITION
my $XP_max=1920-$S_max-$W_max; 
my $XP_levels=3;
my $XY_offset=int($S_max/2+$W_max/2);

#Y-POSITION
my $YP_max=1080-$S_max-$W_max; 
my $YP_levels=3;

#REPETITIONS
my $REPS=2;

# count total number of trials by multiplying the factors
my $total_trials = $S_levels * $W_levels * $D_levels * $A_levels * $XP_levels * $YP_levels * $REPS;
print "total trials $total_trials\n";

# starting from trial number 1
my $current_trial = 1;

while ($current_trial <= $total_trials) {

	# randomize one position within all factor levels
	
	my $S=int(rand($S_levels));
	my $W=int(rand($W_levels));
	my $D=int(rand($D_levels));
	my $A=int(rand($A_levels));
	my $XP=int(rand($XP_levels));
	my $YP=int(rand($YP_levels));

	unless ($checkhash{"$S$W$D$A$XP$YP"}) {
		$checkhash{"$S$W$D$A$XP$YP"}=1;
		my $newS=int($S*$S_max/$S_levels)+int(rand($S_max/$S_levels));
		my $newW=int($W*$W_max/$W_levels)+int(rand($W_max/$W_levels));
		my $newD=int($D*$D_max/$D_levels)+int(rand($D_max/$D_levels));
		my $newA=int($A*$A_max/$A_levels)+int(rand($A_max/$A_levels));
		my $newXP=int($XP*$XP_max/$XP_levels)+int(rand($XP_max/$XP_levels))+$XY_offset;
		my $newYP=int($YP*$YP_max/$YP_levels)+int(rand($YP_max/$YP_levels))+$XY_offset;

		for (my $i=1; $i<=$REPS; $i++,$current_trial++) {
			print MYFILE "<trial id=\"$current_trial\" ";
			if ($newD==1 || $newD eq "clock") {$newD="clock"} else { $newD="anti" };
			print MYFILE "direction=\"$newD\" ";
			print MYFILE "angle=\"$newA\" ";
			print MYFILE "size=\"$newW\" ";
			print MYFILE "distance=\"$newS\" ";
			print MYFILE "x1=\"$newXP\" ";
			print MYFILE "y1=\"$newYP\" ><\/trial>\n";
		}

	}
}

print MYFILE "<\/data>\n";
close (MYFILE);

