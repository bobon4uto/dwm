{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
buildInputs = with pkgs; [
    gcc
    libx11
    libxinerama
    libxft
  ];
}
