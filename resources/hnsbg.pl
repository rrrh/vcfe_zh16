perl -lne 'for my $t (split /,/) { print ".word " . ($t == -1 ? "15" : ($t > 64 ? 2048 + $t : 9216 + $t)); }' < bg3_tileset.csv > bg3.map
