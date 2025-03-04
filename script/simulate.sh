# Requires verilator
if [ -z "$1" ]
then
    echo "simulate.sh needs the name of a toplevel testbench from the rtl directory!"
else
    toplevel=$(basename -- "${1%.*}")
    mypath=$(pwd)
    tmp="$mypath/../tmp"
    mkdir -p $tmp
    rm -rf $tmp/*
    verilator_version=$(verilator --version)
    echo ==$verilator_version==
    { echo -e "#include \"obj_dir/V$toplevel.h\""; cat simulate.cpp; } > $tmp/simulate.cpp
    cd $tmp/
    rtl="../rtl"
    verilator_flags="--exe --build --timing -j 0 --trace --trace-structs -cc"
    cflags="-CFLAGS -DTARGET_TB=V$toplevel"
    defines="-DSIM_DEBUG"
    sv_std="--default-language 1800-2005"
    warn_options="--assert -Wno-fatal -Werror-USERERROR -Werror-USERFATAL"
    libdirlist=$(find $rtl/ -not -path */testbench -and -type d -exec bash -c 'echo "-y $1"' bash "{}" \; )
    toplevelfile="$(find $rtl/ -name $1)"
    verilator $verilator_flags $cflags $defines $sv_std $warn_options $libdirlist $toplevelfile simulate.cpp
    echo ==simulation==
    ./obj_dir/V$toplevel
    gtkwave -A --rcvar 'fontname_signals Monospace 13' --rcvar 'fontname_waves Monospace 12' sim.vcd
fi