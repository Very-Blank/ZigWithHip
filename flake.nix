{
  description = "Zig hip flake";

  # Info on development environments: https://nixos-and-flakes.thiscute.world/development/intro

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    zls = {
      url = "github:zigtools/zls";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    zig.url = "github:mitchellh/zig-overlay";

    nixnvim = {
      url = "github:Very-Blank/NixNvim";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    nmux = {
      url = "github:Very-Blank/Nmux";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {nixpkgs, ...} @ inputs: let
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {inherit system;};

      tmux = inputs.nmux.mkPackage {
        system = system;
        extraModule = {...}: {
          config.nmux.shell = pkgs.lib.getExe pkgs.zsh;
        };
      };
    in
      pkgs.mkShell {
        packages = [
          pkgs.rocmPackages.clr
          pkgs.clang-tools
          pkgs.gnumake
          pkgs.bear

          inputs.zig.packages.${system}.master
          inputs.zls.packages.${system}.default

          (
            inputs.nixnvim.packages.${pkgs.stdenv.system}.default.override {
              extraConfig = {...}: {
                config = {
                  vim = {
                    languages = {
                      clang = {
                        enable = true;
                        lsp.enable = true;
                        treesitter.enable = true;
                      };

                      zig = {
                        enable = true;
                        lsp.enable = true;
                        treesitter.enable = true;
                      };
                    };

                    lsp.servers.zls = {
                      filetypes = ["zig"];
                      cmd = pkgs.lib.mkForce [
                        (pkgs.lib.meta.getExe
                          inputs.zls.packages.${system}.default)
                      ];
                    };

                    # Make These local to c++
                    options = {
                      tabstop = pkgs.lib.mkForce 2;
                      shiftwidth = pkgs.lib.mkForce 2;
                    };
                  };
                };
              };
            }
          )
        ];

        LD_LIBRARY_PATH =
          pkgs.lib.makeLibraryPath [];

        # if [[ ! -f ./compile_commands.json ]]; then
        #   echo "Compile_commands file missing, creating it!"
        #   ${pkgs.lib.getExe pkgs.bear} -- make
        # fi

        shellHook = ''
          export CPLUS_INCLUDE_PATH=${pkgs.stdenv.cc.cc}/include/c++/${pkgs.stdenv.cc.cc.version}:${pkgs.stdenv.cc.cc}/include/c++/${pkgs.stdenv.cc.cc.version}/${pkgs.stdenv.hostPlatform.config}:$CPLUS_INCLUDE_PATH
          exec ${pkgs.lib.getExe' tmux "tmux"}
        '';
      };
  };
}
