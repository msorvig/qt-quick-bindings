swig -java -outdir swig/ qmlbindings_java.i
mv qmlbindings_java_wrap.c swig/qmlbindings_java_wrap.c

swig -python -outdir swig/ qmlbindings.i
mv qmlbindings_wrap.c swig/qmlbindings_python_wrap.c

swig -go -intgosize 64 -outdir swig/ qmlbindings.i
mv qmlbindings_wrap.c swig/qmlbindings_go_wrap.c

swig -csharp -outdir swig/ qmlbindings.i
mv qmlbindings_wrap.c swig/qmlbindings_csharp_wrap.c
# We name the C library "qmlbindings_csharp" to differentiate from libraries
# for the the other languages. Modify the DllImport to match.
sed -i '' -e 's/DllImport("qmlbindings"/DllImport("qmlbindings_csharp"/' swig/qmlbindingsPINVOKE.cs 

swig -ruby -outdir swig/ qmlbindings.i
mv qmlbindings_wrap.c swig/qmlbindings_ruby_wrap.c

swig -r -outdir swig/ qmlbindings.i
mv qmlbindings_wrap.c swig/qmlbindings_r_wrap.c


#    -allegrocl      - Generate ALLEGROCL wrappers
#   -chicken        - Generate CHICKEN wrappers
#   -clisp          - Generate CLISP wrappers
#   -cffi           - Generate CFFI wrappers
#   -csharp         - Generate C# wrappers
#   -d              - Generate D wrappers
#   -go             - Generate Go wrappers
#   -guile          - Generate Guile wrappers
#   -java           - Generate Java wrappers
#   -lua            - Generate Lua wrappers
#   -modula3        - Generate Modula 3 wrappers
#   -mzscheme       - Generate Mzscheme wrappers
#   -ocaml          - Generate Ocaml wrappers
#   -octave         - Generate Octave wrappers
#   -perl           - Generate Perl wrappers
#   -php            - Generate PHP wrappers
#   -pike           - Generate Pike wrappers
#   -python         - Generate Python wrappers
#   -r              - Generate R (aka GNU S) wrappers
#   -ruby           - Generate Ruby wrappers
#   -sexp           - Generate Lisp S-Expressions wrappers
#   -tcl            - Generate Tcl wrappers
#   -uffi           - Generate Common Lisp / UFFI wrappers
#   -xml            - Generate XML wrappers
