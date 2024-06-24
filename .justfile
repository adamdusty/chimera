set windows-shell := ["pwsh.exe", "-NoLogo", "-NoProfileLoadTime", "-Command"]

alias i := integration
alias p := package

configure:
    cmake --preset dev -G Ninja

build:
    cmake --build --preset dev

test:
    ctest --preset dev

clean:
    cmake --build --preset dev --target clean

integration:
    build/dev/integration/chimera

package:
    build/dev/package/chimera