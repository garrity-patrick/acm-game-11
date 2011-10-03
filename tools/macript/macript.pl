#!/usr/bin/perl

use warnings;
use strict;
use Getopt::Long;
use Pod::Usage;

Getopt::Long::Configure('bundling');

my $prefix = '';
my @extensions = ();
my $warnings = 0;
my $force = '';
my $strip = 0;
my $begin = '';
my $end = '';
GetOptions("extensions|ext|x:s" => \@extensions,
           "prefix|p:s" => \$prefix,
           "warnings|warn|w" => \$warnings,
           "force|f:s" => \$force,
           "strip|s" => \$strip,
           "begin|b:s" => \$begin,
           "end|e:s" => \$end) or pod2usage(2);
@extensions = split(',', join(',', @extensions));
@extensions = ('', qw(pl py sh)) if (!@extensions);

if ($begin ne '' && $end eq ''
	|| $begin eq '' && $end ne '') {
	pod2usage(2);
}

my $name = qr{[A-Z_][0-9A-Z_]*}i;      # Name (1)
my $params = qr{(\(                    # Parens and contents (2)
                 ((?:                  # Just contents (3)
                   (?>"(?:[^"]|\\")+") # Quoted string
                   |(?>[^()]+)         # Non-parens (no backtracking)
                   |(?2))*)\))}ox;     # Nested parens (2)

my $macro = qr{\Q$prefix\E($name)$params};
my $active = $begin ne '';

while (<>) {
	if (/\Q$end\E/) {
		$active = 0;
	}
	if ($active) {
		while (/$macro/g) {
			my ($n, $a) = ($1, $3);
			if (my $s = find($n)) {
				s|$prefix($n)$params|`./$s $a`|e;
			} elsif ($strip) {
				s|$prefix($n)$params||;
			} elsif ($warnings) {
				print STDERR <<"EOF";
$ARGV:$.: Warning: Macro "$prefix$n" has no match.
$ARGV:$.: Note: Use --strip to erase macros without matches.
EOF
			}
		}
	} else {
		$active = 1 if /\Q$begin\E/;
	}
	print;
}

sub find {
	my $n = shift;
	my @t = map {"$n$_"} map {$_ eq '' ? '' : ".$_"} @extensions;
	my @g = grep {-e && -x _} @t;
	my @h = @g;
	return undef if (scalar(@g) == 0);
	if (scalar(@g) > 1 && $force ne '') {
		@h = grep { /.$force$/ } @g;
	}
	if (scalar(@h) > 1) {
		die <<"EOF";
$ARGV:$.: Error: Macro \"$prefix$n\" is ambiguous.
$ARGV:$.: Note: Candidates are: @g
EOF
	} elsif (scalar(@h) == 0) {
		die<<"EOF";
$ARGV:$.: Error: Macro \"$prefix$n\" is ambiguous.
$ARGV:$.: Note: No match can be forced with --force $force
$ARGV:$.: Note: Candidates are: @g
EOF
	}
	return $h[0];
}

__END__

=head1 NAME

Macript - A build tool for invoking scripts like macros.

=head1 SYNOPSIS

    macript.pl [OPTIONS] SOURCES...

=head2 Options

=over 4

=item B<--extensions>=I<LIST>, B<--ext>=I<LIST>, B<-x> I<LIST>

Specify a comma-separated list of script extensions to search for (e.g., B<-e pl>). Defaults to B<--extensions=pl,py,sh,>.

=item B<--prefix> I<PREFIX>, B<-p> I<PREFIX>

Specify a prefix to require on all macro invocations (e.g., B<-p @>). Defaults to empty.

=item B<--warnings>, B<--warn>, B<-w>

Print warnings to standard error when there is no matching executable for what appears to be a macro invocation.

=item B<--force> I<EXTENSION>, B<-f> I<EXTENSION>

Specify the extension to prefer if multiple executables match a macro.

=item B<--strip>, B<-s>

Erase invocations that have no matching executable, rather than leaving them in place.

=item B<--begin>=I<BEGIN>, B<--end>=I<END>; B<-b> I<BEGIN>, B<-e> I<END>

Only expand macro invocations that occur after a line containing I<BEGIN> and before a line containing I<END>. If one is given then the other is required.

=back

=head1 DESCRIPTIOIN

B<Macript> searches input sources for anything that looks like a macro invocation (C<NAME(PARAMS)>). It then replaces those invocations with the result of invoking the corresponding executable with the given arguments, if such an executable exists in the directory where B<macript> is invoked. Results are sent to standard output, presumably for piping to a compiler or interpreter.

=head1 CAVEATS

Be I<extremely> careful about what executables you have in your working directory when running this, and verify the output you get before it breaks your build; if you're crazy enough to use this in a makefile, you're going to have to use, e.g.:

    macript -e pl -p @ $< | gcc -x c++ - -o $@

I I<strongly recommend> that you require a prefix. The only reason there is no default prefix is so that Macript may be conveniently used with many languages.

=head1 COPYRIGHT

Copyright (c) 2011 Jon Purdy

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

=head1 AVAILABILITY

http://github.com/evincarofautumn/Macript

=head1 AUTHOR

Jon Purdy <evincarofautumn@gmail.com>

=cut
