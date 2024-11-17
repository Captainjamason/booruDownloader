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
    ];

    buildInputs = [

    ];

    #configurePhase = "
    #    meson setup $src $TMPDIR/build
    #";

    #buildPhase = "
    #    meson compile -C $TMPDIR/build
    #";

    #installPhase = "
    #    mkdir -p $out/lib
	#    cp -rv $TMPDIR/build/src/libopencxx-cli.so $out/lib/
    #    mkdir -p $out/include
    #    cp -rv $src/include $out/include
    #    cp -rv $TMPDIR/build/meson-private/opencxx-cli.pc $out/lib
    #";
}

