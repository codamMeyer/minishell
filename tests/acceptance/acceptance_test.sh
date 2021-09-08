#!/bin/bash

function compileMinishell ()
{
    cd ../../
    make
    cd tests/acceptance
}


compileMinishell
./echo_feature_bash.sh