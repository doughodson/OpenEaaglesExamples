BEGIN { FS = ",[ \t]*|[ \t]+|[}]+" }

/#define/	{ print $3; continue; }

{ for (i=2; i < NF; i++) print $i; }
