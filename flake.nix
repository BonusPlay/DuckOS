{
  description = "Operating System written in C++";
  nixConfig.bash-prompt = "\[duckos-develop\]$ ";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
        {
          devShell = pkgs.mkShell {
            buildInputs = with pkgs; [
              # build deps
              clang_14
              ninja
              cmake
              meson
              nasm
              llvmPackages_latest.bintools

              # run scripts
              grub2
              qemu
              parted

              # nvim
              ccls

              # testing
              cppcheck
            ];
            shellHook = ''
              export CC=clang
              export CXX=clang++
            '';
          };
        });
}
