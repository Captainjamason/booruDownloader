{pkgs ? import <nixpkgs> {} }:
pkgs.stdenv.mkDerivation {
    name = "boorudownloader";
    src = ./.;

    dontUnpack = true;
    dontUseMesonConfigure = true;

    PATH = "${pkgs.meson}/bin:${pkgs.ninja}/bin";

    nativeBuildInputs = [
        pkgs.meson
        pkgs.ninja
        pkgs.pkg-config
        pkgs.jsoncpp
        pkgs.curl
    ];

    buildInputs = [

    ];

    configurePhase = "
        meson setup $src $TMPDIR/build
    ";

    buildPhase = "
        meson compile -C $TMPDIR/build
    ";

    installPhase = "
        cp -rv $TMPDIR/build $out
    ";
}

