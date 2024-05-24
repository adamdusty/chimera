set windows-shell := ["pwsh.exe", "-NoLogo", "-NoProfileLoadTime", "-Command"]

configure:
    cmake --preset dev -G Ninja

build:
    cmake --build --preset dev

test:
    ctest --preset dev

clean:
    cmake --build --preset dev --target clean
