{
  description = "Operating System written in C++";
  nixConfig.bash-prompt = "\[duckos-develop\]$ ";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    devShell = pkgs.mkShell { buildInputs = with pkgs; [
      # build deps
      pkgs.clang_14
      pkgs.ninja
      pkgs.cmake
      pkgs.meson
      pkgs.nasm
      pkgs.llvmPackages_latest.bintools

      # run scripts
      pkgs.grub2
      pkgs.qemu
      pkgs.parted

      # nvim
      pkgs.ccls
    ]};
  };
}

