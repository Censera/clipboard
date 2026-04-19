{ pkgs }:

pkgs.stdenv.mkDerivation {
  pname = "clipboard";
  version = "1.0";

  src = ./.;

  nativeBuildInputs = [ 
    pkgs.gcc 
    pkgs.pkg-config 
  ];

  buildInputs = [
    pkgs.xorg.libxcb
  ];

  buildPhase = ''
    gcc main.c include/clipboard_x11.c $(pkg-config --cflags --libs xcb) -o clipboard
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp clipboard $out/bin/
  '';
}
