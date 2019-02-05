#!/usr/bin/perl

$language = $namespace = $ARGV[0];
$visitor = $ARGV[1];

#
# check whether the visitor contains an implementation for the given node
#
sub implementation_missing {
  my $visitor = shift;
  my $node = shift;
  open TARGET, "grep ::do_${node} targets/${visitor}.cpp |" or die "Visitor does not exist";
  $result = (<TARGET> eq "");
  close TARGET;
  return $result;
}

#
# generate missing visitor code for nodes in the given AST directory
#
sub mk_code {
  my $visitor = shift;
  my $language = shift;
  my $namespace = shift;
  my $dir = shift;
  my $code = '';
  open NODES, "find $dir -name \\*.h -exec grep -H 'accept' {} \\; | grep -v basic_node | cut -d: -f1 | sed -e 's=^.*/==g' | sed -e 's=\\.h==g' |"
    or die "Could not list node headers";
  while (<NODES>) {
    if (m/\ball\b/) { next; }
    chomp;
    $incl = $_;
  
    if (implementation_missing($visitor, $incl)) {
      $incl =~ s=([[:alnum:]_]+)=void ${language}::${visitor}::do_$1(${namespace}::$1 *const node, int lvl) {\n  // EMPTY\n}=;
      $code .= "$incl\n";
    }
  }
  close NODES;
  return $code;
}

if (!-e "targets/${visitor}.cpp") {
  print "File 'targets/${visitor}.cpp' does not exist. Exiting.\n";
  exit 1;
}

$code  = mk_code($visitor, $language, 'cdk',      '/usr/include/cdk/ast'); 
$code .= mk_code($visitor, $language, $namespace, 'ast');
$code  =~ s/^\s+|\s+$//g;

if ((length $code) ne 0) {
  print<<__EOF__;
//** AUTOMATICALLY GENERATED BY mk-visitor-skel.pl
//** Edit these methods to fit your specs and add them to "targets/${visitor}.cpp"

$code
__EOF__
} else {
  print "File 'targets/${visitor}.cpp' contains all methods. Exiting.\n";
  exit 0;
}

###########################################################################

0;

###########################################################################
