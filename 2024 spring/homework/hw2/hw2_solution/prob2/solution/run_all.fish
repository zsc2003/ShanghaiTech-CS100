#!/usr/bin/fish

for prog in {force, iterpow, qinjiushao, quickpow, usepow}
    gcc-13 $prog.c -o $prog -lm
    for i in (seq 10)
        ./$prog <../testcases/$i.in >"$prog"_"$i".out
        if string length -q $last_prog
            diff -s "$last_prog"_"$i".out "$prog"_"$i".out
        end
    end
    set last_prog $prog
end
